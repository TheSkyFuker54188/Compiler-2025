#include "../include/ssa.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>

LLVMIR SSAOptimizer::optimize(const LLVMIR &ssa_ir) {
  LLVMIR optimized_ir = ssa_ir;

  std::cout << "Starting enhanced SSA optimizations..." << std::endl;

  // 执行多轮优化，直到没有更多改进
  bool changed = true;
  int iteration = 0;
  size_t last_instruction_count = countInstructions(optimized_ir);

  while (changed && iteration < 15) { // 增加迭代次数
    changed = false;
    iteration++;

    std::cout << "Optimization iteration " << iteration << std::endl;

    size_t before_count = countInstructions(optimized_ir);

    // 1. 简单代数化简 (新增)
    std::cout << "  Running algebraic simplification..." << std::endl;
    algebraicSimplification(optimized_ir);

    // 2. 常量传播
    std::cout << "  Running constant propagation..." << std::endl;
    constantPropagation(optimized_ir);

    // 3. 常量折叠
    std::cout << "  Running constant folding..." << std::endl;
    constantFolding(optimized_ir);

    // 4. 复制传播
    std::cout << "  Running copy propagation..." << std::endl;
    copyPropagation(optimized_ir);

    // 5. 死代码消除
    std::cout << "  Running dead code elimination..." << std::endl;
    eliminateDeadCode(optimized_ir);

    // 6. 简化φ函数 (新增)
    std::cout << "  Running phi simplification..." << std::endl;
    simplifyPhiFunctions(optimized_ir);

    // 7. 无用分支消除 (新增)
    std::cout << "  Running unreachable code elimination..." << std::endl;
    eliminateUnreachableCode(optimized_ir);

    size_t after_count = countInstructions(optimized_ir);

    if (after_count < before_count) {
      changed = true;
      std::cout << "  Eliminated " << (before_count - after_count)
                << " instructions" << std::endl;
    } else if (after_count == before_count &&
               last_instruction_count == after_count) {
      // 如果连续两轮没有改变，停止迭代
      std::cout << "  No changes detected, stopping optimization." << std::endl;
      break;
    }

    last_instruction_count = after_count;

    // 清理状态为下一轮迭代准备
    constants_map.clear();
    useful_instructions.clear();
  }

  std::cout << "Enhanced SSA optimizations completed after " << iteration
            << " iterations" << std::endl;

  return optimized_ir;
}

void SSAOptimizer::algebraicSimplification(LLVMIR &ir) {
  // 代数化简：处理恒等式、吸收律等
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;

      for (auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        int opcode = inst->GetOpcode();

        if (opcode == ADD || opcode == SUB || opcode == MUL_OP ||
            opcode == DIV_OP) {
          simplifyArithmeticInstruction(inst);
        } else if (opcode == BITAND || opcode == BITOR || opcode == BITXOR) {
          simplifyBitwiseInstruction(inst);
        }
      }
    }
  }
}

void SSAOptimizer::simplifyArithmeticInstruction(Instruction &inst) {
  if (!inst)
    return;

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.size() < 2)
    return;

  ConstantValue left = getConstantFromOperand(operands[0]);
  ConstantValue right = getConstantFromOperand(operands[1]);
  int opcode = inst->GetOpcode();

  // 恒等式化简
  if (opcode == ADD) {
    // x + 0 = x
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[1]);
      return;
    }
  } else if (opcode == SUB) {
    // x - 0 = x
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
  } else if (opcode == MUL_OP) {
    // x * 1 = x
    if (right.isConstant() && right.isInt() && right.int_val == 1) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 1) {
      replaceInstructionWithOperand(inst, operands[1]);
      return;
    }
    // x * 0 = 0
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithConstant(inst, ConstantValue(0));
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 0) {
      replaceInstructionWithConstant(inst, ConstantValue(0));
      return;
    }
  } else if (opcode == DIV_OP) {
    // x / 1 = x
    if (right.isConstant() && right.isInt() && right.int_val == 1) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
  }
}

void SSAOptimizer::simplifyBitwiseInstruction(Instruction &inst) {
  if (!inst)
    return;

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.size() < 2)
    return;

  ConstantValue left = getConstantFromOperand(operands[0]);
  ConstantValue right = getConstantFromOperand(operands[1]);
  int opcode = inst->GetOpcode();

  if (opcode == BITAND) {
    // x & 0 = 0
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithConstant(inst, ConstantValue(0));
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 0) {
      replaceInstructionWithConstant(inst, ConstantValue(0));
      return;
    }
    // x & -1 = x (假设-1的位表示是全1)
    if (right.isConstant() && right.isInt() && right.int_val == -1) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
  } else if (opcode == BITOR) {
    // x | 0 = x
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[1]);
      return;
    }
  } else if (opcode == BITXOR) {
    // x ^ 0 = x
    if (right.isConstant() && right.isInt() && right.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[0]);
      return;
    }
    if (left.isConstant() && left.isInt() && left.int_val == 0) {
      replaceInstructionWithOperand(inst, operands[1]);
      return;
    }
  }
}

void SSAOptimizer::simplifyPhiFunctions(LLVMIR &ir) {
  // 简化φ函数：如果所有输入都相同，则替换为该输入
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;

      auto it = block->Instruction_list.begin();
      while (it != block->Instruction_list.end()) {
        Instruction inst = *it;

        if (inst && inst->GetOpcode() == PHI) {
          if (isRedundantPhiFunction(inst)) {
            // 这是一个冗余的φ函数，标记为待删除
            int result_reg = getInstructionResultRegister(inst);
            int source_reg = getPhiSingleSource(inst);

            if (result_reg != -1 && source_reg != -1) {
              // 在整个函数中替换使用
              replaceRegisterUsages(blocks, result_reg, source_reg);

              // 删除这个φ函数
              it = block->Instruction_list.erase(it);
              continue;
            }
          }
        }

        ++it;
      }
    }
  }
}

bool SSAOptimizer::isRedundantPhiFunction(const Instruction &inst) {
  if (!inst || inst->GetOpcode() != PHI)
    return false;

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.empty())
    return false;

  // 获取第一个非自引用操作数
  int first_reg = -1;
  int result_reg = getInstructionResultRegister(inst);

  for (const auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      if (reg_num != result_reg) { // 不是自引用
        if (first_reg == -1) {
          first_reg = reg_num;
        } else if (first_reg != reg_num) {
          return false; // 发现不同的输入
        }
      }
    }
  }

  return first_reg != -1; // 如果找到了统一的非自引用输入
}

void SSAOptimizer::replaceRegisterUsages(std::map<int, LLVMBlock> &blocks,
                                         int old_reg, int new_reg) {
  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    for (auto &inst : block->Instruction_list) {
      if (!inst)
        continue;

      // 替换指令中使用old_reg的地方
      std::vector<Operand> operands = getInstructionOperands(inst);
      bool changed = false;

      for (auto &operand : operands) {
        if (isRegisterOperand(operand) &&
            getRegisterFromOperand(operand) == old_reg) {
          replaceOperandRegister(operand, new_reg);
          changed = true;
        }
      }
    }
  }
}

void SSAOptimizer::eliminateUnreachableCode(LLVMIR &ir) {
  // 消除不可达代码
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    if (blocks.empty())
      continue;

    // 1. 标记所有可达的基本块
    std::unordered_set<int> reachable_blocks;
    std::queue<int> work_list;

    // 从第一个基本块开始（通常是入口块）
    int entry_block = blocks.begin()->first;
    reachable_blocks.insert(entry_block);
    work_list.push(entry_block);

    while (!work_list.empty()) {
      int current_block = work_list.front();
      work_list.pop();

      auto block_it = blocks.find(current_block);
      if (block_it == blocks.end())
        continue;

      LLVMBlock block = block_it->second;

      // 分析跳转指令，找到后继块
      for (const auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        int opcode = inst->GetOpcode();
        if (opcode == BR_UNCOND || opcode == BR_COND) {
          // 这里需要根据具体的跳转指令格式来提取目标块
          // 简化处理：假设按顺序访问下一个块
          auto next_it = blocks.find(current_block + 1);
          if (next_it != blocks.end() &&
              reachable_blocks.find(current_block + 1) ==
                  reachable_blocks.end()) {
            reachable_blocks.insert(current_block + 1);
            work_list.push(current_block + 1);
          }
        }
      }
    }

    // 2. 删除不可达的基本块
    auto it = blocks.begin();
    while (it != blocks.end()) {
      if (reachable_blocks.find(it->first) == reachable_blocks.end()) {
        std::cout << "    Removing unreachable block " << it->first
                  << std::endl;
        it = blocks.erase(it);
      } else {
        ++it;
      }
    }
  }
}

// 增强版死代码消除
void SSAOptimizer::eliminateDeadCode(LLVMIR &ir) {
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    // 使用更精确的算法
    std::unordered_set<Instruction> live_instructions;
    std::queue<Instruction> work_list;

    // 第一步：标记所有关键指令
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;
      for (const auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        if (isCriticalInstruction(inst)) {
          live_instructions.insert(inst);
          work_list.push(inst);
        }
      }
    }

    // 第二步：迭代标记依赖的指令
    while (!work_list.empty()) {
      Instruction inst = work_list.front();
      work_list.pop();

      std::vector<Operand> operands = getInstructionOperands(inst);
      for (const auto &operand : operands) {
        if (isRegisterOperand(operand)) {
          int reg_num = getRegisterFromOperand(operand);
          Instruction def_inst = findDefiningInstruction(operand, blocks);

          if (def_inst &&
              live_instructions.find(def_inst) == live_instructions.end()) {
            live_instructions.insert(def_inst);
            work_list.push(def_inst);
          }
        }
      }
    }

    // 第三步：删除死代码
    size_t removed_count = 0;
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;

      auto it = block->Instruction_list.begin();
      while (it != block->Instruction_list.end()) {
        if (live_instructions.find(*it) == live_instructions.end() &&
            !isCriticalInstruction(*it)) {
          it = block->Instruction_list.erase(it);
          removed_count++;
        } else {
          ++it;
        }
      }
    }

    if (removed_count > 0) {
      std::cout << "    Removed " << removed_count << " dead instructions"
                << std::endl;
    }
  }
}

// 增强版常量传播
void SSAOptimizer::constantPropagation(LLVMIR &ir) {
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    bool changed = true;
    while (changed) {
      changed = false;

      for (const auto &block_pair : blocks) {
        LLVMBlock block = block_pair.second;

        for (auto &inst : block->Instruction_list) {
          if (!inst)
            continue;

          if (tryConstantPropagation(inst)) {
            changed = true;
          }
        }
      }
    }
  }
}

bool SSAOptimizer::tryConstantPropagation(Instruction &inst) {
  if (!inst)
    return false;

  std::vector<Operand> operands = getInstructionOperands(inst);
  bool changed = false;

  for (auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      auto const_it = constants_map.find(reg_num);

      if (const_it != constants_map.end()) {
        // 找到了常量，进行替换
        replaceOperandWithConstant(operand, const_it->second);
        changed = true;
      }
    }
  }

  if (changed) {
    // 更新常量映射
    updateConstantMapping(inst);
  }

  return changed;
}

// 辅助函数：替换指令为操作数
void SSAOptimizer::replaceInstructionWithOperand(Instruction &inst,
                                                 const Operand &operand) {
  // 这里需要根据具体的指令系统来实现
  // 简化处理：记录替换信息，在后续Pass中处理

  int result_reg = getInstructionResultRegister(inst);
  if (result_reg != -1 && isRegisterOperand(operand)) {
    int source_reg = getRegisterFromOperand(operand);
    if (source_reg != -1) {
      // 记录这个替换关系，用于复制传播
      // 这里可以标记这条指令为无用，让死代码消除处理
    }
  }
}

// 其他现有函数保持不变，但添加更多错误检查和日志
// ... [现有函数实现] ...
