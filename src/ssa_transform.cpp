#include "../include/ssa.h"
#include <algorithm>
#include <iostream>
#include <queue>

LLVMIR SSATransformer::transform(const LLVMIR &ir) {
  LLVMIR ssa_ir = ir; // 复制原始IR

  // 对每个函数分别进行SSA变换
  for (auto &func_pair : ssa_ir.function_block_map) {
    FuncDefInstruction func = func_pair.first;
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    std::cout << "Converting function to SSA form..." << std::endl;

    // 1. 计算支配信息
    DominanceInfo dom_info = computeDominanceInfo(blocks);

    // 2. 插入φ函数
    insertPhiFunctions(blocks, dom_info);

    // 3. 变量重命名
    renameVariables(blocks, dom_info);
  }

  return ssa_ir;
}

SSATransformer::DominanceInfo
SSATransformer::computeDominanceInfo(const std::map<int, LLVMBlock> &blocks) {

  DominanceInfo info;

  if (blocks.empty())
    return info;

  // 获取入口块（假设是第一个块）
  int entry_block = blocks.begin()->first;

  // 初始化支配关系
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    if (block_id == entry_block) {
      // 入口块只被自己支配
      info.dominators[block_id].insert(block_id);
    } else {
      // 其他块初始时被所有块支配
      for (const auto &all_blocks : blocks) {
        info.dominators[block_id].insert(all_blocks.first);
      }
    }
  }

  // 迭代计算支配关系
  bool changed = true;
  while (changed) {
    changed = false;

    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;

      if (block_id == entry_block)
        continue;

      // 计算前驱的支配关系交集
      std::vector<int> predecessors = getPredecessors(block_id, blocks);
      if (!predecessors.empty()) {
        std::unordered_set<int> new_dominators;

        // 初始化为第一个前驱的支配者
        new_dominators = info.dominators[predecessors[0]];

        // 与其他前驱的支配者求交集
        for (size_t i = 1; i < predecessors.size(); ++i) {
          std::unordered_set<int> intersection;
          std::set_intersection(
              new_dominators.begin(), new_dominators.end(),
              info.dominators[predecessors[i]].begin(),
              info.dominators[predecessors[i]].end(),
              std::inserter(intersection, intersection.begin()));
          new_dominators = intersection;
        }

        // 添加自己
        new_dominators.insert(block_id);

        // 检查是否有变化
        if (new_dominators != info.dominators[block_id]) {
          info.dominators[block_id] = new_dominators;
          changed = true;
        }
      }
    }
  }

  // 计算直接支配者
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    if (block_id == entry_block) {
      info.idom[block_id] = -1; // 入口块没有直接支配者
      continue;
    }

    // 寻找直接支配者
    for (int dominator : info.dominators[block_id]) {
      if (dominator != block_id) {
        bool is_immediate = true;

        // 检查是否有其他支配者在dominator和block_id之间
        for (int other_dom : info.dominators[block_id]) {
          if (other_dom != block_id && other_dom != dominator) {
            if (info.dominators[other_dom].count(dominator)) {
              is_immediate = false;
              break;
            }
          }
        }

        if (is_immediate) {
          info.idom[block_id] = dominator;
          break;
        }
      }
    }
  }

  // 计算支配边界
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    std::vector<int> predecessors = getPredecessors(block_id, blocks);

    if (predecessors.size() >= 2) { // 汇合点
      for (int pred : predecessors) {
        int runner = pred;

        // 沿支配树向上直到找到block_id的支配者
        while (runner != -1 && !info.dominators[block_id].count(runner)) {
          info.dom_frontier[runner].insert(block_id);
          runner = info.idom[runner];
        }
      }
    }
  }

  return info;
}

void SSATransformer::insertPhiFunctions(std::map<int, LLVMBlock> &blocks,
                                        const DominanceInfo &dom_info) {

  // 收集所有变量定义
  std::unordered_set<std::string> all_vars = collectDefinedVariables(blocks);

  for (const std::string &var : all_vars) {
    // 收集定义该变量的基本块
    std::unordered_set<int> def_blocks;

    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;
      LLVMBlock block = block_pair.second;

      // 检查该块是否定义了变量var
      for (const auto &inst : block->Instruction_list) {
        // 这里需要根据具体指令格式来判断是否定义了变量
        // 简化处理：假设store指令定义变量，load指令使用变量
        if (inst->GetOpcode() == STORE || inst->GetOpcode() == ALLOCA) {
          // 这里需要提取变量名，暂时简化处理
          def_blocks.insert(block_id);
        }
      }
    }

    // 为每个定义点的支配边界插入φ函数
    std::queue<int> work_list;
    std::unordered_set<int> has_phi;

    for (int def_block : def_blocks) {
      work_list.push(def_block);
    }

    while (!work_list.empty()) {
      int block_id = work_list.front();
      work_list.pop();

      // 为该块支配边界中的每个块插入φ函数
      auto df_it = dom_info.dom_frontier.find(block_id);
      if (df_it != dom_info.dom_frontier.end()) {
        for (int frontier_block : df_it->second) {
          if (has_phi.find(frontier_block) == has_phi.end()) {
            // 在frontier_block的开头插入φ函数
            // TODO: 创建φ指令并插入到块的开头

            has_phi.insert(frontier_block);

            if (def_blocks.find(frontier_block) == def_blocks.end()) {
              work_list.push(frontier_block);
            }
          }
        }
      }
    }
  }
}

void SSATransformer::renameVariables(std::map<int, LLVMBlock> &blocks,
                                     const DominanceInfo &dom_info) {

  RenameInfo rename_info;

  // 初始化所有变量的计数器
  std::unordered_set<std::string> all_vars = collectDefinedVariables(blocks);
  for (const std::string &var : all_vars) {
    rename_info.var_counter[var] = 0;
    rename_info.var_stack[var].push_back(0);
  }

  // 从入口块开始递归重命名
  if (!blocks.empty()) {
    int entry_block = blocks.begin()->first;
    renameVariablesRecursive(entry_block, blocks, dom_info, rename_info);
  }
}

std::unordered_set<std::string> SSATransformer::collectDefinedVariables(
    const std::map<int, LLVMBlock> &blocks) {

  std::unordered_set<std::string> vars;

  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    for (const auto &inst : block->Instruction_list) {
      // 根据指令类型收集定义的变量
      // 这里需要根据具体的指令格式来实现
      // 暂时简化处理
    }
  }

  return vars;
}

std::vector<int>
SSATransformer::getPredecessors(int block_id,
                                const std::map<int, LLVMBlock> &blocks) {
  std::vector<int> predecessors;

  for (const auto &block_pair : blocks) {
    int other_block_id = block_pair.first;
    LLVMBlock other_block = block_pair.second;

    if (other_block_id == block_id)
      continue;

    // 检查该块是否有跳转到目标块的指令
    for (const auto &inst : other_block->Instruction_list) {
      if (inst->GetOpcode() == BR_COND || inst->GetOpcode() == BR_UNCOND) {
        // 这里需要检查跳转目标，暂时简化处理
        // 假设所有跳转都指向下一个块
        if (other_block_id + 1 == block_id) {
          predecessors.push_back(other_block_id);
        }
      }
    }
  }

  return predecessors;
}

std::vector<int>
SSATransformer::getSuccessors(int block_id,
                              const std::map<int, LLVMBlock> &blocks) {
  std::vector<int> successors;

  auto it = blocks.find(block_id);
  if (it == blocks.end())
    return successors;

  LLVMBlock block = it->second;

  // 检查跳转指令
  for (const auto &inst : block->Instruction_list) {
    if (inst->GetOpcode() == BR_COND || inst->GetOpcode() == BR_UNCOND) {
      // 这里需要根据指令格式提取跳转目标
      // 暂时简化处理
    }
  }

  return successors;
}

void SSATransformer::renameVariablesRecursive(
    int block_id, const std::map<int, LLVMBlock> &blocks,
    const DominanceInfo &dom_info, RenameInfo &rename_info) {

  auto it = blocks.find(block_id);
  if (it == blocks.end())
    return;

  LLVMBlock block = it->second;

  // 记录在这个块中修改的变量，以便稍后恢复
  std::vector<std::string> modified_vars;

  // 重命名该块中的指令
  for (auto &inst : block->Instruction_list) {
    // 根据指令类型进行重命名
    // 这里需要根据具体的指令格式来实现
  }

  // 递归处理支配的子块
  for (const auto &child_block : blocks) {
    int child_id = child_block.first;
    auto idom_it = dom_info.idom.find(child_id);

    if (idom_it != dom_info.idom.end() && idom_it->second == block_id) {
      renameVariablesRecursive(child_id, blocks, dom_info, rename_info);
    }
  }

  // 恢复变量栈
  for (const std::string &var : modified_vars) {
    if (!rename_info.var_stack[var].empty()) {
      rename_info.var_stack[var].pop_back();
    }
  }
}

std::string SSATransformer::getNewVariableName(const std::string &var_name,
                                               RenameInfo &rename_info) {
  int &counter = rename_info.var_counter[var_name];
  ++counter;
  rename_info.var_stack[var_name].push_back(counter);

  return var_name + "_" + std::to_string(counter);
}

std::string
SSATransformer::getCurrentVariableVersion(const std::string &var_name,
                                          const RenameInfo &rename_info) {
  auto it = rename_info.var_stack.find(var_name);
  if (it != rename_info.var_stack.end() && !it->second.empty()) {
    int version = it->second.back();
    return var_name + "_" + std::to_string(version);
  }

  return var_name + "_0"; // 默认版本
}
