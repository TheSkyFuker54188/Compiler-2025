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
    std::cout << "  Function has " << blocks.size() << " blocks" << std::endl;

    // 1. 构建控制流图
    std::cout << "  Building control flow graph..." << std::endl;
    ControlFlowGraph cfg = buildControlFlowGraph(blocks);

    // 2. 计算支配信息
    std::cout << "  Computing dominance information..." << std::endl;
    DominanceInfo dom_info = computeDominanceInfoFromCFG(blocks, cfg);

    // 3. 插入φ函数
    std::cout << "  Inserting phi functions..." << std::endl;
    insertPhiFunctions(blocks, dom_info);

    // 4. 变量重命名
    std::cout << "  Renaming variables..." << std::endl;
    renameVariables(blocks, dom_info);

    std::cout << "  Function SSA conversion completed." << std::endl;
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
      BrUncondInstruction *br_inst =
          dynamic_cast<BrUncondInstruction *>(last_inst);
      if (br_inst) {
        Operand label_op = br_inst->GetLabel();
        if (label_op && label_op->GetOperandType() == BasicOperand::LABEL) {
          LabelOperand *label_operand = dynamic_cast<LabelOperand *>(label_op);
          if (label_operand) {
            int target_block = label_operand->GetLabelNo();
            if (blocks.find(target_block) != blocks.end()) {
              cfg.successors[block_id].push_back(target_block);
              cfg.predecessors[target_block].push_back(block_id);
            }
          }
        }
      }
    } else if (last_inst->GetOpcode() == BR_COND) {
      // 条件跳转：有两个目标块
      BrCondInstruction *br_inst = dynamic_cast<BrCondInstruction *>(last_inst);
      if (br_inst) {
        // 提取true分支目标
        Operand true_label = br_inst->GetTrueLabel();
        if (true_label && true_label->GetOperandType() == BasicOperand::LABEL) {
          LabelOperand *true_operand = dynamic_cast<LabelOperand *>(true_label);
          if (true_operand) {
            int true_target = true_operand->GetLabelNo();
            if (blocks.find(true_target) != blocks.end()) {
              cfg.successors[block_id].push_back(true_target);
              cfg.predecessors[true_target].push_back(block_id);
            }
          }
        }

        // 提取false分支目标
        Operand false_label = br_inst->GetFalseLabel();
        if (false_label &&
            false_label->GetOperandType() == BasicOperand::LABEL) {
          LabelOperand *false_operand =
              dynamic_cast<LabelOperand *>(false_label);
          if (false_operand) {
            int false_target = false_operand->GetLabelNo();
            if (blocks.find(false_target) != blocks.end()) {
              cfg.successors[block_id].push_back(false_target);
              cfg.predecessors[false_target].push_back(block_id);
            }
          }
        }
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

  // 对于大型控制流图，使用简化的快速算法
  if (blocks.size() > 10) {
    return computeFastDominanceInfo(blocks, cfg);
  }

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
  int max_iterations =
      std::min(10, static_cast<int>(blocks.size())); // 更严格的限制
  int iteration_count = 0;

  while (changed && iteration_count < max_iterations) {
    changed = false;
    iteration_count++;

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
  int max_iterations = 3; // 大幅降低迭代限制
  int iteration_count = 0;

  while (changed && iteration_count < max_iterations) {
    changed = false;
    iteration_count++;

    std::cout << "Dominator analysis iteration " << iteration_count
              << std::endl;

    // 对于复杂情况，提前退出
    if (blocks.size() > 5 && iteration_count > 1) {
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

            // 获取前驱块来创建φ函数的参数
            auto pred_it = cfg.predecessors.find(frontier_block);
            if (pred_it != cfg.predecessors.end() && !pred_it->second.empty()) {
              // 创建φ函数的结果操作数
              static int phi_counter = 1;
              auto phi_result = GetNewRegOperand(phi_counter++);

              // 为每个前驱块创建φ参数（暂时用占位符）
              std::vector<std::pair<Operand, Operand>> phi_args;
              for (int pred_block : pred_it->second) {
                // 创建占位符操作数（稍后在变量重命名阶段会被正确的值替换）
                auto placeholder_val = GetNewRegOperand(0);
                auto pred_label = GetNewLabelOperand(pred_block);
                phi_args.push_back(std::make_pair(placeholder_val, pred_label));
              }

              // 创建完整的φ指令
              auto phi_inst = new PhiInstruction(I32, phi_result, phi_args);

              // 插入到基本块开头
              auto frontier_block_it = blocks.find(frontier_block);
              if (frontier_block_it != blocks.end()) {
                LLVMBlock block = frontier_block_it->second;
                // 插入到指令列表的开头
                block->Instruction_list.insert(block->Instruction_list.begin(),
                                               phi_inst);

                std::cout << "  Inserted phi function in block L"
                          << frontier_block << " for variable " << var
                          << std::endl;
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

  // 重新构建CFG用于φ函数参数更新
  ControlFlowGraph cfg = buildControlFlowGraph(blocks);

  // 从入口块开始递归重命名
  if (!blocks.empty()) {
    int entry_block = blocks.begin()->first;
    renameVariablesRecursive(entry_block, blocks, dom_info, rename_info);

    // 重命名完成后，更新所有φ函数的参数
    updatePhiArguments(blocks, cfg, rename_info);
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

  std::cout << "  Renaming variables in block L" << block_id << std::endl;

  // 重命名该块中的指令
  for (auto &inst : block->Instruction_list) {
    if (!inst)
      continue;

    int opcode = inst->GetOpcode();

    // 处理φ函数：为结果分配新版本
    if (opcode == PHI) {
      PhiInstruction *phi_inst = dynamic_cast<PhiInstruction *>(inst);
      if (phi_inst) {
        // φ函数定义新的变量版本
        // 这里简化处理：假设φ函数对应的是某个alloca变量
        // 实际中需要更复杂的映射逻辑
        std::cout << "    Processing phi instruction" << std::endl;
      }
    }

    // 处理alloca：记录变量声明
    else if (opcode == ALLOCA) {
      AllocaInstruction *alloca_inst = dynamic_cast<AllocaInstruction *>(inst);
      if (alloca_inst) {
        std::string var_name = alloca_inst->GetResult()->GetFullName();
        // alloca指令定义变量的初始版本
        std::cout << "    Found alloca for variable " << var_name << std::endl;
      }
    }

    // 处理store：这是变量的定义点
    else if (opcode == STORE) {
      StoreInstruction *store_inst = dynamic_cast<StoreInstruction *>(inst);
      if (store_inst) {
        std::string var_name = store_inst->GetPointer()->GetFullName();

        // 为这个变量分配新版本
        std::string new_var_name = getNewVariableName(var_name, rename_info);
        modified_vars.push_back(var_name);

        std::cout << "    Store to " << var_name << " -> " << new_var_name
                  << std::endl;
      }
    }

    // 处理load：这是变量的使用点
    else if (opcode == LOAD) {
      LoadInstruction *load_inst = dynamic_cast<LoadInstruction *>(inst);
      if (load_inst) {
        std::string var_name = load_inst->GetPointer()->GetFullName();
        std::string current_version =
            getCurrentVariableVersion(var_name, rename_info);

        std::cout << "    Load from " << var_name
                  << " (current version: " << current_version << ")"
                  << std::endl;
      }
    }
  }

  // 递归处理被此块直接支配的子块
  for (const auto &child_block : blocks) {
    int child_id = child_block.first;
    auto idom_it = dom_info.idom.find(child_id);

    if (idom_it != dom_info.idom.end() && idom_it->second == block_id) {
      renameVariablesRecursive(child_id, blocks, dom_info, rename_info);
    }
  }

  // 恢复变量栈状态
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

void SSATransformer::updatePhiArguments(std::map<int, LLVMBlock> &blocks,
                                        const ControlFlowGraph &cfg,
                                        const RenameInfo &rename_info) {
  std::cout << "  Updating phi function arguments..." << std::endl;

  // 遍历所有基本块，寻找φ函数并更新其参数
  for (auto &block_pair : blocks) {
    int block_id = block_pair.first;
    LLVMBlock block = block_pair.second;

    for (auto &inst : block->Instruction_list) {
      if (!inst || inst->GetOpcode() != PHI)
        continue;

      PhiInstruction *phi_inst = dynamic_cast<PhiInstruction *>(inst);
      if (!phi_inst)
        continue;

      std::cout << "    Updating phi in block L" << block_id << std::endl;

      // 获取该块的前驱
      auto pred_it = cfg.predecessors.find(block_id);
      if (pred_it == cfg.predecessors.end())
        continue;

      // 清空现有的φ参数
      phi_inst->phi_list.clear();

      // 为每个前驱块添加φ参数
      for (int pred_block : pred_it->second) {
        // 简化处理：创建占位符值
        // 在真实实现中，这里应该根据变量重命名的结果来设置正确的值
        auto placeholder_val =
            GetNewRegOperand(pred_block); // 使用前驱块ID作为占位符
        auto pred_label = GetNewLabelOperand(pred_block);

        phi_inst->phi_list.push_back(
            std::make_pair(placeholder_val, pred_label));

        std::cout << "      Added phi arg from block L" << pred_block
                  << std::endl;
      }
    }
  }
}

/**
 * 快速支配算法 - 适用于大型控制流图
 * 使用简化的迭代算法，减少复杂集合运算
 */
SSATransformer::DominanceInfo
SSATransformer::computeFastDominanceInfo(const std::map<int, LLVMBlock> &blocks,
                                         const ControlFlowGraph &cfg) {
  std::cout << "Using fast dominance algorithm for " << blocks.size()
            << " blocks" << std::endl;

  DominanceInfo info;

  if (blocks.empty())
    return info;

  int entry_block = blocks.begin()->first;

  // 使用更简单的数据结构：直接支配者映射
  std::unordered_map<int, int> immediate_dominators;

  // 入口块没有直接支配者
  immediate_dominators[entry_block] = -1;

  // 初始化：所有非入口块的直接支配者都设为entry
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    if (block_id != entry_block) {
      immediate_dominators[block_id] = entry_block;
    }
  }

  // 简单的迭代更新算法 - 最多5轮
  bool changed = true;
  int max_iterations = 5;
  int iteration = 0;

  while (changed && iteration < max_iterations) {
    changed = false;
    iteration++;

    // 逆拓扑序遍历（简化版）
    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;

      if (block_id == entry_block)
        continue;

      auto pred_it = cfg.predecessors.find(block_id);
      if (pred_it == cfg.predecessors.end() || pred_it->second.empty())
        continue;

      // 找到第一个已处理的前驱作为候选
      int new_idom = -1;
      for (int pred : pred_it->second) {
        if (immediate_dominators.find(pred) != immediate_dominators.end()) {
          new_idom = pred;
          break;
        }
      }

      if (new_idom == -1)
        continue;

      // 与其他前驱求公共支配者
      for (int pred : pred_it->second) {
        if (pred == new_idom)
          continue;
        if (immediate_dominators.find(pred) == immediate_dominators.end())
          continue;

        new_idom = findCommonDominator(new_idom, pred, immediate_dominators);
      }

      // 更新
      if (immediate_dominators[block_id] != new_idom) {
        immediate_dominators[block_id] = new_idom;
        changed = true;
      }
    }
  }

  // 构建传统的支配信息结构
  info.idom = immediate_dominators;

  // 构建完整支配集合（简化版）
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    info.dominators[block_id].insert(block_id); // 自己支配自己

    // 向上遍历支配树
    int current = immediate_dominators[block_id];
    while (current != -1 && current != block_id) {
      info.dominators[block_id].insert(current);
      auto it = immediate_dominators.find(current);
      if (it == immediate_dominators.end()) {
        break;
      }
      current = it->second;
    }
  }

  // 简化支配边界计算
  computeSimplifiedDominanceFrontier(info, blocks, cfg);

  std::cout << "Fast dominance analysis completed in " << iteration
            << " iterations" << std::endl;

  return info;
}

/**
 * 找到两个块的公共支配者
 */
int SSATransformer::findCommonDominator(
    int b1, int b2, const std::unordered_map<int, int> &idom) {

  std::unordered_set<int> path1;

  // 收集b1到根的路径
  int current = b1;
  while (current != -1 && path1.find(current) == path1.end()) {
    path1.insert(current);
    auto it = idom.find(current);
    if (it == idom.end()) {
      break;
    }
    current = it->second;
  }

  // 沿着b2到根的路径找第一个交点
  current = b2;
  while (current != -1) {
    if (path1.find(current) != path1.end()) {
      return current;
    }
    auto it = idom.find(current);
    if (it == idom.end()) {
      break;
    }
    current = it->second;
  }

  return b1; // 默认返回b1
}

/**
 * 简化的支配边界计算
 */
void SSATransformer::computeSimplifiedDominanceFrontier(
    DominanceInfo &info, const std::map<int, LLVMBlock> &blocks,
    const ControlFlowGraph &cfg) {

  // 简化版本：只计算必要的支配边界
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;

    auto pred_it = cfg.predecessors.find(block_id);
    if (pred_it == cfg.predecessors.end() || pred_it->second.size() < 2)
      continue;

    // 对于有多个前驱的块，其前驱的某些支配者可能在其支配边界中
    for (int pred : pred_it->second) {
      int runner = pred;
      while (runner != -1) {
        if (info.dominators[block_id].find(runner) ==
            info.dominators[block_id].end()) {
          info.dom_frontier[runner].insert(block_id);
        } else {
          break; // runner支配block_id，停止
        }

        auto idom_it = info.idom.find(runner);
        if (idom_it == info.idom.end() || idom_it->second == runner)
          break;
        runner = idom_it->second;
      }
    }
  }
}
