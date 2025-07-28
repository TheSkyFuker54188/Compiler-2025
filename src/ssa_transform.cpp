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

    // 1. 构建控制流图
    ControlFlowGraph cfg = buildControlFlowGraph(blocks);

    // 2. 计算支配信息
    DominanceInfo dom_info = computeDominanceInfoFromCFG(blocks, cfg);

    // 3. 插入φ函数
    insertPhiFunctions(blocks, dom_info);

    // 4. 变量重命名
    renameVariables(blocks, dom_info);
  }

  return ssa_ir;
}

SSATransformer::ControlFlowGraph
SSATransformer::buildControlFlowGraph(const std::map<int, LLVMBlock> &blocks) {
  ControlFlowGraph cfg;

  // 初始化所有块的前驱和后继列表
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    cfg.predecessors[block_id] = std::vector<int>();
    cfg.successors[block_id] = std::vector<int>();
  }

  // 分析每个块的跳转指令来构建控制流
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    LLVMBlock block = block_pair.second;

    if (block->Instruction_list.empty()) {
      // 空块，假设顺序执行到下一块
      auto next_it = blocks.find(block_id + 1);
      if (next_it != blocks.end()) {
        cfg.successors[block_id].push_back(block_id + 1);
        cfg.predecessors[block_id + 1].push_back(block_id);
      }
      continue;
    }

    // 检查最后一条指令
    auto last_inst = block->Instruction_list.back();

    if (last_inst->GetOpcode() == BR_UNCOND) {
      // 无条件跳转：提取目标块
      // 这里需要根据具体的指令格式来解析目标
      // 暂时简化：假设跳转到下一个块
      auto next_it = blocks.find(block_id + 1);
      if (next_it != blocks.end()) {
        cfg.successors[block_id].push_back(block_id + 1);
        cfg.predecessors[block_id + 1].push_back(block_id);
      }
    } else if (last_inst->GetOpcode() == BR_COND) {
      // 条件跳转：有两个目标块
      // 这里需要根据具体的指令格式来解析目标
      // 暂时简化：假设跳转到下一个和下下个块
      auto next_it = blocks.find(block_id + 1);
      if (next_it != blocks.end()) {
        cfg.successors[block_id].push_back(block_id + 1);
        cfg.predecessors[block_id + 1].push_back(block_id);
      }
      auto next2_it = blocks.find(block_id + 2);
      if (next2_it != blocks.end()) {
        cfg.successors[block_id].push_back(block_id + 2);
        cfg.predecessors[block_id + 2].push_back(block_id);
      }
    } else if (last_inst->GetOpcode() == RET) {
      // 返回指令：没有后继
      // 不需要添加后继
    } else {
      // 其他指令：顺序执行到下一块
      auto next_it = blocks.find(block_id + 1);
      if (next_it != blocks.end()) {
        cfg.successors[block_id].push_back(block_id + 1);
        cfg.predecessors[block_id + 1].push_back(block_id);
      }
    }
  }

  return cfg;
}

SSATransformer::DominanceInfo SSATransformer::computeDominanceInfoFromCFG(
    const std::map<int, LLVMBlock> &blocks, const ControlFlowGraph &cfg) {
  DominanceInfo info;

  if (blocks.empty())
    return info;

  int entry_block = blocks.begin()->first;

  // 初始化支配关系
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    if (block_id == entry_block) {
      info.dominators[block_id].insert(block_id);
    } else {
      // 其他块初始时被所有块支配
      for (const auto &all_blocks : blocks) {
        info.dominators[block_id].insert(all_blocks.first);
      }
    }
  }

  // 迭代计算支配关系 - 使用更robust的算法
  bool changed = true;
  int max_iterations = blocks.size() * 2; // 更合理的迭代限制
  int iteration_count = 0;

  while (changed && iteration_count < max_iterations) {
    changed = false;
    iteration_count++;

    if (iteration_count % 10 == 0) {
      std::cout << "Dominator analysis iteration " << iteration_count
                << std::endl;
    }

    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;

      if (block_id == entry_block)
        continue;

      // 使用CFG中的前驱信息
      auto pred_it = cfg.predecessors.find(block_id);
      if (pred_it != cfg.predecessors.end() && !pred_it->second.empty()) {
        const std::vector<int> &predecessors = pred_it->second;

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

  if (iteration_count >= max_iterations) {
    std::cout << "Warning: Dominator analysis reached iteration limit ("
              << max_iterations << "), but continuing..." << std::endl;
  }

  // 计算直接支配者和支配边界（保持原有逻辑）
  computeImmediateDominators(info, blocks);
  computeDominanceFrontier(info, blocks, cfg);

  return info;
}

void SSATransformer::computeImmediateDominators(
    DominanceInfo &info, const std::map<int, LLVMBlock> &blocks) {
  int entry_block = blocks.begin()->first;

  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    if (block_id == entry_block) {
      info.idom[block_id] = -1;
      continue;
    }

    // 寻找直接支配者
    for (int dominator : info.dominators[block_id]) {
      if (dominator != block_id) {
        bool is_immediate = true;

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
}

void SSATransformer::computeDominanceFrontier(
    DominanceInfo &info, const std::map<int, LLVMBlock> &blocks,
    const ControlFlowGraph &cfg) {
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    auto pred_it = cfg.predecessors.find(block_id);
    if (pred_it != cfg.predecessors.end() && pred_it->second.size() >= 2) {
      for (int pred : pred_it->second) {
        int runner = pred;

        while (runner != -1 && !info.dominators[block_id].count(runner)) {
          info.dom_frontier[runner].insert(block_id);
          auto idom_it = info.idom.find(runner);
          runner = (idom_it != info.idom.end()) ? idom_it->second : -1;
        }
      }
    }
  }
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
  int max_iterations = 5; // 大幅降低迭代限制
  int iteration_count = 0;

  while (changed && iteration_count < max_iterations) {
    changed = false;
    iteration_count++;

    std::cout << "Dominator analysis iteration " << iteration_count
              << std::endl;

    // 对于复杂情况，提前退出
    if (blocks.size() > 10 && iteration_count > 2) {
      std::cout << "Early termination for complex control flow" << std::endl;
      break;
    }

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

  // 检查是否达到迭代限制
  if (iteration_count >= max_iterations) {
    std::cerr << "Warning: Dominator analysis reached iteration limit ("
              << max_iterations << "), results may be incomplete." << std::endl;
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

  // 重新构建CFG用于φ函数插入
  ControlFlowGraph cfg = buildControlFlowGraph(blocks);

  for (const std::string &var : all_vars) {
    // 收集定义该变量的基本块
    std::unordered_set<int> def_blocks;

    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;
      LLVMBlock block = block_pair.second;

      // 检查该块是否定义了变量var
      for (const auto &inst : block->Instruction_list) {
        // 从ALLOCA指令中提取变量名
        if (inst->GetOpcode() == ALLOCA) {
          auto alloca_inst = dynamic_cast<AllocaInstruction *>(inst);
          if (alloca_inst) {
            std::string var_name = alloca_inst->GetResult()->GetFullName();
            if (var_name == var) {
              def_blocks.insert(block_id);
            }
          }
        }
        // 从STORE指令中提取目标变量
        else if (inst->GetOpcode() == STORE) {
          auto store_inst = dynamic_cast<StoreInstruction *>(inst);
          if (store_inst) {
            std::string var_name = store_inst->GetPointer()->GetFullName();
            if (var_name == var) {
              def_blocks.insert(block_id);
            }
          }
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

            // 获取前驱块数量来创建φ函数的参数
            auto pred_it = cfg.predecessors.find(frontier_block);
            if (pred_it != cfg.predecessors.end() && !pred_it->second.empty()) {
              // 创建φ函数的结果操作数（临时变量）
              auto phi_result =
                  GetNewRegOperand(0); // 使用友元函数创建RegOperand

              // 创建φ指令（先创建空的，稍后在变量重命名阶段填充操作数）
              auto phi_inst = new PhiInstruction(I32, phi_result);

              // 插入到基本块开头
              auto frontier_block_it = blocks.find(frontier_block);
              if (frontier_block_it != blocks.end()) {
                LLVMBlock block = frontier_block_it->second;
                // 插入到指令列表的开头
                block->Instruction_list.insert(block->Instruction_list.begin(),
                                               phi_inst);
              }
            }

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
      // 从ALLOCA指令收集变量定义
      if (inst->GetOpcode() == ALLOCA) {
        auto alloca_inst = dynamic_cast<AllocaInstruction *>(inst);
        if (alloca_inst) {
          std::string var_name = alloca_inst->GetResult()->GetFullName();
          vars.insert(var_name);
        }
      }
      // 从STORE指令收集变量使用
      else if (inst->GetOpcode() == STORE) {
        auto store_inst = dynamic_cast<StoreInstruction *>(inst);
        if (store_inst) {
          std::string var_name = store_inst->GetPointer()->GetFullName();
          vars.insert(var_name);
        }
      }
    }
  }

  return vars;
}

std::vector<int>
SSATransformer::getPredecessors(int block_id,
                                const std::map<int, LLVMBlock> &blocks) {
  std::vector<int> predecessors;

  // 简化版本：对于复杂控制流，使用非常保守的估计
  if (block_id == blocks.begin()->first) {
    // 入口块没有前驱
    return predecessors;
  }

  // 只考虑直接的前一个块
  auto it = blocks.find(block_id - 1);
  if (it != blocks.end()) {
    predecessors.push_back(block_id - 1);
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
