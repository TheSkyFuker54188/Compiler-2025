#include "../include/ssa.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>

LLVMIR SSAOptimizer::optimize(const LLVMIR &ssa_ir) {
  LLVMIR optimized_ir = ssa_ir;

  std::cout << "Starting SSA optimizations..." << std::endl;

  // 执行多轮优化，直到没有更多改进
  bool changed = true;
  int iteration = 0;

  while (changed && iteration < 10) { // 限制迭代次数防止无限循环
    changed = false;
    iteration++;

    std::cout << "Optimization iteration " << iteration << std::endl;

    size_t before_count = countInstructions(optimized_ir);

    // 1. 常量传播
    std::cout << "  Running constant propagation..." << std::endl;
    constantPropagation(optimized_ir);

    // 2. 常量折叠
    std::cout << "  Running constant folding..." << std::endl;
    constantFolding(optimized_ir);

    // 3. 死代码消除
    std::cout << "  Running dead code elimination..." << std::endl;
    eliminateDeadCode(optimized_ir);

    // 4. 复制传播
    std::cout << "  Running copy propagation..." << std::endl;
    copyPropagation(optimized_ir);

    size_t after_count = countInstructions(optimized_ir);

    if (after_count < before_count) {
      changed = true;
      std::cout << "  Eliminated " << (before_count - after_count)
                << " instructions" << std::endl;
    }

    // 清理状态为下一轮迭代准备
    constants_map.clear();
    useful_instructions.clear();
  }

  std::cout << "SSA optimizations completed after " << iteration
            << " iterations" << std::endl;

  return optimized_ir;
}

void SSAOptimizer::eliminateDeadCode(LLVMIR &ir) {
  // 对每个函数进行死代码消除
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    // 第一步：建立完整的指令映射和依赖关系
    std::unordered_map<int, Instruction> reg_to_inst;
    std::unordered_map<Instruction, std::vector<int>> inst_to_defined_regs;
    std::unordered_map<Instruction, std::vector<int>> inst_to_used_regs;

    // 建立寄存器到指令的映射
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;
      for (const auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        // 记录指令定义的寄存器
        int result_reg = getInstructionResultRegister(inst);
        if (result_reg != -1) {
          reg_to_inst[result_reg] = inst;
          inst_to_defined_regs[inst].push_back(result_reg);
        }

        // 记录指令使用的寄存器
        std::vector<Operand> operands = getInstructionOperands(inst);
        for (const auto &operand : operands) {
          if (isRegisterOperand(operand)) {
            int reg_num = getRegisterFromOperand(operand);
            if (reg_num != -1) {
              inst_to_used_regs[inst].push_back(reg_num);
            }
          }
        }
      }
    }

    // 第二步：标记所有有用的指令
    useful_instructions.clear();
    std::queue<Instruction> work_list;
    std::unordered_set<Instruction> in_worklist;

    // 标记所有关键指令为有用
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;
      for (const auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        if (isCriticalInstruction(inst)) {
          if (useful_instructions.find(inst) == useful_instructions.end()) {
            markInstructionAsUseful(inst);
            if (in_worklist.find(inst) == in_worklist.end()) {
              work_list.push(inst);
              in_worklist.insert(inst);
            }
          }
        }
      }
    }

    // 第三步：传播有用性（使用更强健的算法）
    while (!work_list.empty()) {
      Instruction inst = work_list.front();
      work_list.pop();
      in_worklist.erase(inst);

      // 标记该指令使用的所有寄存器的定义指令为有用
      auto used_regs_it = inst_to_used_regs.find(inst);
      if (used_regs_it != inst_to_used_regs.end()) {
        for (int reg_num : used_regs_it->second) {
          auto def_inst_it = reg_to_inst.find(reg_num);
          if (def_inst_it != reg_to_inst.end()) {
            Instruction def_inst = def_inst_it->second;
            if (def_inst && useful_instructions.find(def_inst) ==
                                useful_instructions.end()) {
              markInstructionAsUseful(def_inst);
              if (in_worklist.find(def_inst) == in_worklist.end()) {
                work_list.push(def_inst);
                in_worklist.insert(def_inst);
              }
            }
          }
        }
      }

      // 对于φ函数和控制流相关指令，标记控制依赖
      int opcode = inst->GetOpcode();
      if (opcode == PHI || opcode == BR_COND || opcode == BR_UNCOND) {
        markControlDependencies(inst, blocks, work_list);
        // 将新加入工作列表的指令标记
        while (!work_list.empty()) {
          Instruction control_inst = work_list.front();
          work_list.pop();
          if (in_worklist.find(control_inst) == in_worklist.end()) {
            work_list.push(control_inst);
            in_worklist.insert(control_inst);
          }
        }
      }
    }

    // 第四步：保守地保留所有地址计算指令
    // 这是为了确保我们不会删除任何可能被间接使用的指令
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;
      for (const auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        int opcode = inst->GetOpcode();
        if (opcode == GETELEMENTPTR || opcode == ALLOCA) {
          if (useful_instructions.find(inst) == useful_instructions.end()) {
            // 检查是否有任何指令使用这个结果
            int result_reg = getInstructionResultRegister(inst);
            if (result_reg != -1) {
              bool is_used = false;
              for (const auto &check_block_pair : blocks) {
                LLVMBlock check_block = check_block_pair.second;
                for (const auto &check_inst : check_block->Instruction_list) {
                  if (!check_inst || check_inst == inst)
                    continue;

                  std::vector<Operand> operands =
                      getInstructionOperands(check_inst);
                  for (const auto &operand : operands) {
                    if (isRegisterOperand(operand) &&
                        getRegisterFromOperand(operand) == result_reg) {
                      is_used = true;
                      break;
                    }
                  }
                  if (is_used)
                    break;
                }
                if (is_used)
                  break;
              }

              if (is_used) {
                markInstructionAsUseful(inst);
                // 递归标记其依赖
                std::queue<Instruction> conservative_worklist;
                conservative_worklist.push(inst);
                while (!conservative_worklist.empty()) {
                  Instruction cons_inst = conservative_worklist.front();
                  conservative_worklist.pop();

                  auto used_regs_it = inst_to_used_regs.find(cons_inst);
                  if (used_regs_it != inst_to_used_regs.end()) {
                    for (int reg_num : used_regs_it->second) {
                      auto def_inst_it = reg_to_inst.find(reg_num);
                      if (def_inst_it != reg_to_inst.end()) {
                        Instruction def_inst = def_inst_it->second;
                        if (def_inst && useful_instructions.find(def_inst) ==
                                            useful_instructions.end()) {
                          markInstructionAsUseful(def_inst);
                          conservative_worklist.push(def_inst);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // 第五步：删除所有无用指令
    size_t removed_count = 0;
    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;

      auto it = block->Instruction_list.begin();
      while (it != block->Instruction_list.end()) {
        if (useful_instructions.find(*it) == useful_instructions.end()) {
          // 这条指令是无用的，删除它
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

void SSAOptimizer::constantPropagation(LLVMIR &ir) {
  // 对每个函数进行常量传播
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    // 工作列表算法进行常量传播
    std::queue<std::pair<int, size_t>>
        work_list; // (block_id, instruction_index)
    std::unordered_set<std::string> visited;

    // 初始化：将所有指令加入工作列表
    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;
      LLVMBlock block = block_pair.second;

      for (size_t i = 0; i < block->Instruction_list.size(); ++i) {
        work_list.push({block_id, i});
      }
    }

    // 处理工作列表
    while (!work_list.empty()) {
      auto [block_id, inst_idx] = work_list.front();
      work_list.pop();

      auto block_it = blocks.find(block_id);
      if (block_it == blocks.end() ||
          inst_idx >= block_it->second->Instruction_list.size()) {
        continue;
      }

      LLVMBlock block = block_it->second;
      Instruction inst = block->Instruction_list[inst_idx];

      if (!inst)
        continue;

      int opcode = inst->GetOpcode();

      // 处理不同类型的指令
      switch (opcode) {
      case LOAD: {
        // load指令：检查是否从常量地址加载
        // 这里需要根据具体的load指令格式来实现
        // 暂时跳过复杂的load常量传播
        break;
      }

      case ADD:
      case SUB:
      case MUL_OP:
      case DIV_OP:
      case FADD:
      case FSUB:
      case FMUL:
      case FDIV: {
        // 算术指令：检查操作数是否为常量
        if (canPropagateConstants(inst)) {
          propagateConstantsInInstruction(inst);

          // 更新常量映射
          updateConstantMapping(inst);

          // 将使用该结果的指令加入工作列表
          int result_reg = getInstructionResultRegister(inst);
          if (result_reg != -1) {
            addUsersToWorkList(result_reg, blocks, work_list);
          }
        }
        break;
      }

      case ICMP:
      case FCMP: {
        // 比较指令
        if (canPropagateConstants(inst)) {
          propagateConstantsInInstruction(inst);
          updateConstantMapping(inst);

          int result_reg = getInstructionResultRegister(inst);
          if (result_reg != -1) {
            addUsersToWorkList(result_reg, blocks, work_list);
          }
        }
        break;
      }

      case PHI: {
        // φ函数：检查所有操作数是否为相同常量
        if (canPropagateConstants(inst)) {
          propagateConstantsInInstruction(inst);
          updateConstantMapping(inst);

          int result_reg = getInstructionResultRegister(inst);
          if (result_reg != -1) {
            addUsersToWorkList(result_reg, blocks, work_list);
          }
        }
        break;
      }

      default:
        // 其他指令：更新常量映射但不传播
        updateConstantMapping(inst);
        break;
      }
    }
  }
}

void SSAOptimizer::constantFolding(LLVMIR &ir) {
  // 对每个函数进行常量折叠
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    for (const auto &block_pair : blocks) {
      LLVMBlock block = block_pair.second;

      for (auto &inst : block->Instruction_list) {
        if (!inst)
          continue;

        int opcode = inst->GetOpcode();

        // 检查是否是可以折叠的指令
        switch (opcode) {
        case ADD:
        case SUB:
        case MUL_OP:
        case DIV_OP:
        case MOD_OP: {
          // 整数算术运算
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case FADD:
        case FSUB:
        case FMUL:
        case FDIV: {
          // 浮点算术运算
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case ICMP: {
          // 整数比较
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case FCMP: {
          // 浮点比较
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case BITAND:
        case BITOR:
        case BITXOR:
        case SHL: {
          // 位运算
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case ZEXT:
        case SITOFP:
        case FPTOSI: {
          // 类型转换
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        case SELECT: {
          // select指令：select i1 %cond, type %val1, type %val2
          if (canFoldConstants(inst)) {
            foldConstantsInInstruction(inst);
          }
          break;
        }

        default:
          // 不支持折叠的指令类型
          break;
        }
      }
    }
  }
}

void SSAOptimizer::copyPropagation(LLVMIR &ir) {
  // 对每个函数进行复制传播
  for (auto &func_pair : ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    // 建立复制关系映射 (目标寄存器 -> 源寄存器)
    std::unordered_map<int, int> copy_map;
    std::unordered_map<int, int> value_map; // 寄存器到其最终值的映射

    bool changed = true;
    int iteration = 0;

    while (changed && iteration < 5) {
      changed = false;
      iteration++;

      // 按照支配顺序处理基本块（简化：按ID顺序）
      for (const auto &block_pair : blocks) {
        LLVMBlock block = block_pair.second;

        for (auto &inst : block->Instruction_list) {
          if (!inst)
            continue;

          int opcode = inst->GetOpcode();

          // 识别复制指令
          if (isCopyInstruction(inst)) {
            int dest_reg, src_reg;
            if (extractCopyRegisters(inst, dest_reg, src_reg)) {
              // 传递复制关系：如果src已经是其他值的复制，则传递
              int final_src = src_reg;
              auto src_it = value_map.find(src_reg);
              if (src_it != value_map.end()) {
                final_src = src_it->second;
              }

              // 避免循环复制
              if (final_src != dest_reg) {
                copy_map[dest_reg] = src_reg;
                value_map[dest_reg] = final_src;
              }
            }
          }

          // 处理φ函数的特殊情况
          else if (opcode == PHI) {
            // φ函数可能产生复制机会
            if (isPhiCopyCandidate(inst)) {
              int dest_reg = getInstructionResultRegister(inst);
              int src_reg = getPhiSingleSource(inst);
              if (dest_reg != -1 && src_reg != -1 && dest_reg != src_reg) {
                int final_src = src_reg;
                auto src_it = value_map.find(src_reg);
                if (src_it != value_map.end()) {
                  final_src = src_it->second;
                }

                copy_map[dest_reg] = src_reg;
                value_map[dest_reg] = final_src;
              }
            }
          }

          // 替换指令中使用的寄存器
          if (replaceCopyUsages(inst, value_map)) {
            changed = true;
          }
        }
      }
    }

    // 移除变成无用的复制指令
    removeTrivialCopies(blocks, copy_map);
  }
}

void SSAOptimizer::commonSubexpressionElimination(LLVMIR &ir) {
  // 暂时跳过公共子表达式消除的详细实现
  // 这个优化比较复杂，需要值编号或哈希表等技术
  std::cout << "  Common subexpression elimination (placeholder)" << std::endl;
  (void)ir; // 避免未使用参数警告
}

// ============================================================================
// 辅助函数实现
// ============================================================================

bool SSAOptimizer::isCriticalInstruction(const Instruction &inst) {
  if (!inst)
    return false;

  int opcode = inst->GetOpcode();

  // 关键指令：有副作用的指令，控制流指令，函数调用等
  switch (opcode) {
  case CALL:      // 函数调用
  case RET:       // 返回
  case STORE:     // 存储（可能有副作用）
  case BR_COND:   // 条件分支
  case BR_UNCOND: // 无条件分支
  case ALLOCA:    // 内存分配（绝对不能删除）
    return true;

  // 某些内在函数可能有副作用
  case LOAD:
    // 对于load，我们保守地认为它是关键的
    // 实际应该检查是否从volatile内存加载
    return true;

  default:
    return false;
  }
}

size_t SSAOptimizer::countInstructions(const LLVMIR &ir) {
  size_t count = 0;
  for (const auto &func_pair : ir.function_block_map) {
    for (const auto &block_pair : func_pair.second) {
      count += block_pair.second->Instruction_list.size();
    }
  }
  return count;
}

std::vector<Operand>
SSAOptimizer::getInstructionOperands(const Instruction &inst) {
  std::vector<Operand> operands;

  if (!inst)
    return operands;

  // 根据指令类型提取操作数
  int opcode = inst->GetOpcode();

  switch (opcode) {
  case ADD:
  case SUB:
  case MUL_OP:
  case DIV_OP:
  case MOD_OP:
  case FADD:
  case FSUB:
  case FMUL:
  case FDIV:
  case ICMP:
  case FCMP:
  case BITAND:
  case BITOR:
  case BITXOR:
  case SHL: {
    // 二元运算指令通常有两个或三个操作数
    ArithmeticInstruction *arith_inst =
        dynamic_cast<ArithmeticInstruction *>(inst);
    if (arith_inst) {
      Operand op1 = arith_inst->GetOp1();
      Operand op2 = arith_inst->GetOp2();
      Operand op3 = arith_inst->GetOp3();
      if (op1)
        operands.push_back(op1);
      if (op2)
        operands.push_back(op2);
      if (op3)
        operands.push_back(op3);
    }
    break;
  }

  case LOAD: {
    // load指令有一个地址操作数
    LoadInstruction *load_inst = dynamic_cast<LoadInstruction *>(inst);
    if (load_inst) {
      Operand ptr = load_inst->GetPointer();
      if (ptr)
        operands.push_back(ptr);
    }
    break;
  }

  case STORE: {
    // store指令有值和地址两个操作数
    StoreInstruction *store_inst = dynamic_cast<StoreInstruction *>(inst);
    if (store_inst) {
      Operand value = store_inst->GetValue();
      Operand ptr = store_inst->GetPointer();
      if (value)
        operands.push_back(value);
      if (ptr)
        operands.push_back(ptr);
    }
    break;
  }

  case PHI: {
    // φ函数有多个值-标签对操作数
    PhiInstruction *phi_inst = dynamic_cast<PhiInstruction *>(inst);
    if (phi_inst) {
      auto &phi_list = phi_inst->phi_list;
      for (const auto &phi_pair : phi_list) {
        if (phi_pair.first)
          operands.push_back(phi_pair.first);
      }
    }
    break;
  }

  case RET: {
    // return指令可能有一个返回值操作数
    RetInstruction *ret_inst = dynamic_cast<RetInstruction *>(inst);
    if (ret_inst) {
      Operand ret_val = ret_inst->GetRetVal();
      if (ret_val)
        operands.push_back(ret_val);
    }
    break;
  }

  case BR_COND: {
    // 条件分支指令有一个条件操作数
    BrCondInstruction *br_inst = dynamic_cast<BrCondInstruction *>(inst);
    if (br_inst) {
      Operand cond = br_inst->GetCond();
      if (cond)
        operands.push_back(cond);
    }
    break;
  }

  case CALL: {
    // 函数调用指令有多个参数操作数
    CallInstruction *call_inst = dynamic_cast<CallInstruction *>(inst);
    if (call_inst) {
      auto &args = call_inst->GetArgs();
      for (const auto &arg : args) {
        if (arg.second)
          operands.push_back(arg.second);
      }
    }
    break;
  }

  case GETELEMENTPTR: {
    // getelementptr指令有基础指针和索引操作数
    GetElementptrInstruction *gep_inst =
        dynamic_cast<GetElementptrInstruction *>(inst);
    if (gep_inst) {
      Operand ptr = gep_inst->GetPtrVal();
      if (ptr)
        operands.push_back(ptr);

      const auto &indexes = gep_inst->GetIndexes();
      for (const auto &index : indexes) {
        if (index)
          operands.push_back(index);
      }
    }
    break;
  }

  case ZEXT:
  case SITOFP:
  case FPTOSI:
  case FPEXT:
  case BITCAST: {
    // 类型转换指令通常有一个操作数
    if (opcode == SITOFP) {
      SitofpInstruction *sitofp_inst = dynamic_cast<SitofpInstruction *>(inst);
      if (sitofp_inst && sitofp_inst->value) {
        operands.push_back(sitofp_inst->value);
      }
    } else if (opcode == FPTOSI) {
      FptosiInstruction *fptosi_inst = dynamic_cast<FptosiInstruction *>(inst);
      if (fptosi_inst && fptosi_inst->value) {
        operands.push_back(fptosi_inst->value);
      }
    } else if (opcode == FPEXT) {
      FpextInstruction *fpext_inst = dynamic_cast<FpextInstruction *>(inst);
      if (fpext_inst && fpext_inst->value) {
        operands.push_back(fpext_inst->value);
      }
    } else if (opcode == BITCAST) {
      BitCastInstruction *bitcast_inst =
          dynamic_cast<BitCastInstruction *>(inst);
      if (bitcast_inst && bitcast_inst->src) {
        operands.push_back(bitcast_inst->src);
      }
    } else {
      // 其他类型转换指令的通用处理
      std::vector<Operand> generic_operands =
          getGenericInstructionOperands(inst);
      operands.insert(operands.end(), generic_operands.begin(),
                      generic_operands.end());
    }
    break;
  }

  case SELECT: {
    // select指令：select i1 %cond, type %val1, type %val2
    SelectInstruction *select_inst = dynamic_cast<SelectInstruction *>(inst);
    if (select_inst) {
      if (select_inst->cond)
        operands.push_back(select_inst->cond);
      if (select_inst->op1)
        operands.push_back(select_inst->op1);
      if (select_inst->op2)
        operands.push_back(select_inst->op2);
    }
    break;
  }

  default:
    // 对于未明确处理的指令类型，尝试通用方法
    std::vector<Operand> generic_operands = getGenericInstructionOperands(inst);
    operands.insert(operands.end(), generic_operands.begin(),
                    generic_operands.end());
    break;
  }

  return operands;
}

bool SSAOptimizer::isRegisterOperand(const Operand operand) {
  if (!operand)
    return false;

  // 检查操作数类型是否为寄存器
  return operand->GetOperandType() == BasicOperand::REG;
}

Instruction
SSAOptimizer::findDefiningInstruction(const Operand operand,
                                      const std::map<int, LLVMBlock> &blocks) {
  if (!operand || !isRegisterOperand(operand)) {
    return nullptr;
  }

  int reg_num = getRegisterFromOperand(operand);
  if (reg_num == -1)
    return nullptr;

  // 在所有基本块中查找定义该寄存器的指令
  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    for (const auto &inst : block->Instruction_list) {
      if (!inst)
        continue;

      int result_reg = getInstructionResultRegister(inst);
      if (result_reg == reg_num) {
        return inst;
      }
    }
  }

  return nullptr;
}

bool SSAOptimizer::canPropagateConstants(const Instruction &inst) {
  if (!inst)
    return false;

  // 检查指令的所有操作数是否都是常量
  std::vector<Operand> operands = getInstructionOperands(inst);

  for (const auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      if (constants_map.find(reg_num) == constants_map.end()) {
        return false; // 有非常量操作数
      }
    }
    // 立即数操作数已经是常量，跳过
  }

  return !operands.empty(); // 至少要有操作数才能传播
}

void SSAOptimizer::propagateConstantsInInstruction(Instruction &inst) {
  if (!inst)
    return;

  std::vector<Operand> operands = getInstructionOperands(inst);

  // 将所有寄存器操作数替换为对应的常量
  for (auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      auto const_it = constants_map.find(reg_num);
      if (const_it != constants_map.end()) {
        replaceOperandWithConstant(operand, const_it->second);
      }
    }
  }
}

void SSAOptimizer::updateConstantMapping(const Instruction &inst) {
  if (!inst)
    return;

  int result_reg = getInstructionResultRegister(inst);
  if (result_reg == -1)
    return;

  int opcode = inst->GetOpcode();

  // 根据指令类型更新常量映射
  switch (opcode) {
  case ADD:
  case SUB:
  case MUL_OP:
  case DIV_OP:
  case MOD_OP:
  case FADD:
  case FSUB:
  case FMUL:
  case FDIV: {
    // 算术运算：如果操作数都是常量，计算结果
    if (canFoldConstants(inst)) {
      ConstantValue result = computeArithmeticResult(inst);
      if (result.isConstant()) {
        constants_map[result_reg] = result;
      }
    } else {
      // 移除可能存在的映射
      constants_map.erase(result_reg);
    }
    break;
  }

  case ICMP:
  case FCMP: {
    // 比较运算
    if (canFoldConstants(inst)) {
      ConstantValue result = computeComparisonResult(inst);
      if (result.isConstant()) {
        constants_map[result_reg] = result;
      }
    } else {
      constants_map.erase(result_reg);
    }
    break;
  }

  case PHI: {
    // φ函数：检查所有输入是否为相同常量
    ConstantValue phi_result = computePhiResult(inst);
    if (phi_result.isConstant()) {
      constants_map[result_reg] = phi_result;
    } else {
      constants_map.erase(result_reg);
    }
    break;
  }

  default:
    // 其他指令：保守地移除常量信息
    constants_map.erase(result_reg);
    break;
  }
}

bool SSAOptimizer::canFoldConstants(const Instruction &inst) {
  if (!inst)
    return false;

  // 检查指令是否可以进行常量折叠
  std::vector<Operand> operands = getInstructionOperands(inst);

  if (operands.empty())
    return false;

  // 检查所有操作数是否都是常量
  for (const auto &operand : operands) {
    ConstantValue const_val = getConstantFromOperand(operand);
    if (!const_val.isConstant()) {
      return false;
    }
  }

  return true;
}

void SSAOptimizer::foldConstantsInInstruction(Instruction &inst) {
  if (!inst || !canFoldConstants(inst))
    return;

  int opcode = inst->GetOpcode();
  std::vector<Operand> operands = getInstructionOperands(inst);

  if (operands.size() < 2)
    return; // 需要至least两个操作数

  ConstantValue left = getConstantFromOperand(operands[0]);
  ConstantValue right = getConstantFromOperand(operands[1]);

  ConstantValue result;

  // 根据操作码计算结果
  if (isArithmeticInstruction(inst)) {
    result =
        evaluateArithmeticOp(static_cast<LLVMIROpcode>(opcode), left, right);
  } else if (isComparisonInstruction(inst)) {
    result =
        evaluateComparisonOp(static_cast<LLVMIROpcode>(opcode), left, right);
  }

  if (result.isConstant()) {
    // 将整个指令替换为常量赋值
    replaceInstructionWithConstant(inst, result);

    // 更新常量映射
    int result_reg = getInstructionResultRegister(inst);
    if (result_reg != -1) {
      constants_map[result_reg] = result;
    }
  }
}

bool SSAOptimizer::isCopyInstruction(const Instruction &inst) {
  if (!inst)
    return false;

  // 检查是否是复制指令
  // 在SSA中，复制可能以多种形式出现：
  // 1. 简单的load/store序列
  // 2. φ函数只有一个有效输入
  // 3. 类型转换指令（如果不改变值）

  int opcode = inst->GetOpcode();

  switch (opcode) {
  case PHI: {
    // φ函数如果所有输入都是同一个值，则为复制
    return isPhiCopyCandidate(inst);
  }

  case BITCAST: {
    // 位转换在某些情况下相当于复制
    return true;
  }

  case ZEXT:
  case SITOFP:
  case FPTOSI: {
    // 类型转换可能是复制（需要更细致的分析）
    return false; // 暂时保守处理
  }

  default:
    return false;
  }
}

bool SSAOptimizer::extractCopyRegisters(const Instruction &inst, int &dest_reg,
                                        int &src_reg) {
  if (!inst || !isCopyInstruction(inst))
    return false;

  dest_reg = getInstructionResultRegister(inst);
  if (dest_reg == -1)
    return false;

  int opcode = inst->GetOpcode();

  switch (opcode) {
  case PHI: {
    src_reg = getPhiSingleSource(inst);
    return src_reg != -1 && src_reg != dest_reg;
  }

  case BITCAST: {
    std::vector<Operand> operands = getInstructionOperands(inst);
    if (!operands.empty() && isRegisterOperand(operands[0])) {
      src_reg = getRegisterFromOperand(operands[0]);
      return src_reg != -1 && src_reg != dest_reg;
    }
    return false;
  }

  default:
    return false;
  }
}

bool SSAOptimizer::replaceCopyUsages(
    Instruction &inst, const std::unordered_map<int, int> &copy_map) {
  if (!inst)
    return false;

  bool changed = false;
  std::vector<Operand> operands = getInstructionOperands(inst);

  for (auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      auto copy_it = copy_map.find(reg_num);
      if (copy_it != copy_map.end()) {
        // 替换为复制的源
        replaceOperandRegister(operand, copy_it->second);
        changed = true;
      }
    }
  }

  return changed;
}

void SSAOptimizer::markInstructionAsUseful(const Instruction &inst) {
  if (inst) {
    useful_instructions.insert(inst);
  }
}

void SSAOptimizer::markOperandDefAsUseful(
    const Operand operand, const std::map<int, LLVMBlock> &blocks) {
  if (!operand || !isRegisterOperand(operand))
    return;

  Instruction def_inst = findDefiningInstruction(operand, blocks);
  if (def_inst) {
    markInstructionAsUseful(def_inst);
  }
}

// ============================================================================
// 新增的具体实现函数
// ============================================================================

int SSAOptimizer::getRegisterFromOperand(const Operand operand) {
  if (!operand)
    return -1;

  // 检查操作数是否为寄存器类型
  if (operand->GetOperandType() == BasicOperand::REG) {
    RegOperand *reg_operand = dynamic_cast<RegOperand *>(operand);
    if (reg_operand) {
      return reg_operand->GetRegNo();
    }
  }

  return -1; // 不是寄存器操作数
}

ConstantValue SSAOptimizer::getConstantFromOperand(const Operand operand) {
  if (!operand)
    return ConstantValue();

  // 检查操作数是否是立即数
  // 这里需要根据具体的操作数类型来判断和提取值

  // 如果是寄存器操作数，检查常量映射
  if (isRegisterOperand(operand)) {
    int reg_num = getRegisterFromOperand(operand);
    auto const_it = constants_map.find(reg_num);
    if (const_it != constants_map.end()) {
      return const_it->second;
    }
  }

  // 如果是立即数操作数，直接提取值
  // 需要根据具体的操作数类型来实现

  return ConstantValue(); // 返回未定义常量
}

void SSAOptimizer::replaceOperandWithConstant(Operand &operand,
                                              const ConstantValue &constant) {
  if (!operand || !constant.isConstant())
    return;

  // 根据常量类型创建新的立即数操作数
  // 这里需要根据具体的操作数类系统来实现

  // 简化处理：暂时不替换，实际需要创建ImmI32Operand或ImmF32Operand等
}

ConstantValue SSAOptimizer::evaluateArithmeticOp(LLVMIROpcode op,
                                                 const ConstantValue &left,
                                                 const ConstantValue &right) {
  if (!left.isConstant() || !right.isConstant()) {
    return ConstantValue();
  }

  // 类型匹配检查
  if (left.type != right.type) {
    return ConstantValue(); // 类型不匹配，无法计算
  }

  switch (op) {
  case ADD:
    if (left.isInt())
      return ConstantValue(left.int_val + right.int_val);
    break;

  case SUB:
    if (left.isInt())
      return ConstantValue(left.int_val - right.int_val);
    break;

  case MUL_OP:
    if (left.isInt())
      return ConstantValue(left.int_val * right.int_val);
    break;

  case DIV_OP:
    if (left.isInt() && right.int_val != 0)
      return ConstantValue(left.int_val / right.int_val);
    break;

  case MOD_OP:
    if (left.isInt() && right.int_val != 0)
      return ConstantValue(left.int_val % right.int_val);
    break;

  case FADD:
    if (left.isFloat())
      return ConstantValue(left.float_val + right.float_val);
    break;

  case FSUB:
    if (left.isFloat())
      return ConstantValue(left.float_val - right.float_val);
    break;

  case FMUL:
    if (left.isFloat())
      return ConstantValue(left.float_val * right.float_val);
    break;

  case FDIV:
    if (left.isFloat() && right.float_val != 0.0f)
      return ConstantValue(left.float_val / right.float_val);
    break;

  case BITAND:
    if (left.isInt())
      return ConstantValue(left.int_val & right.int_val);
    break;

  case BITOR:
    if (left.isInt())
      return ConstantValue(left.int_val | right.int_val);
    break;

  case BITXOR:
    if (left.isInt())
      return ConstantValue(left.int_val ^ right.int_val);
    break;

  case SHL:
    if (left.isInt())
      return ConstantValue(left.int_val << right.int_val);
    break;

  default:
    break;
  }

  return ConstantValue();
}

ConstantValue SSAOptimizer::evaluateComparisonOp(LLVMIROpcode op,
                                                 const ConstantValue &left,
                                                 const ConstantValue &right) {
  if (!left.isConstant() || !right.isConstant() || left.type != right.type) {
    return ConstantValue();
  }

  bool result = false;

  if (op == ICMP) {
    // 整数比较 - 这里简化处理，实际需要根据比较条件
    if (left.isInt()) {
      // 假设默认为相等比较
      result = (left.int_val == right.int_val);
    }
  } else if (op == FCMP) {
    // 浮点比较
    if (left.isFloat()) {
      result = (left.float_val == right.float_val);
    }
  }

  return ConstantValue(result ? 1 : 0);
}

bool SSAOptimizer::isArithmeticInstruction(const Instruction &inst) {
  if (!inst)
    return false;

  int opcode = inst->GetOpcode();
  return opcode == ADD || opcode == SUB || opcode == MUL_OP ||
         opcode == DIV_OP || opcode == MOD_OP || opcode == FADD ||
         opcode == FSUB || opcode == FMUL || opcode == FDIV ||
         opcode == BITAND || opcode == BITOR || opcode == BITXOR ||
         opcode == SHL;
}

bool SSAOptimizer::isComparisonInstruction(const Instruction &inst) {
  if (!inst)
    return false;

  int opcode = inst->GetOpcode();
  return opcode == ICMP || opcode == FCMP;
}

int SSAOptimizer::getInstructionResultRegister(const Instruction &inst) {
  if (!inst)
    return -1;

  // 根据指令类型获取结果寄存器
  int opcode = inst->GetOpcode();

  switch (opcode) {
  case ADD:
  case SUB:
  case MUL_OP:
  case DIV_OP:
  case MOD_OP:
  case FADD:
  case FSUB:
  case FMUL:
  case FDIV:
  case BITAND:
  case BITOR:
  case BITXOR:
  case SHL: {
    ArithmeticInstruction *arith_inst =
        dynamic_cast<ArithmeticInstruction *>(inst);
    if (arith_inst) {
      Operand result = arith_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case LOAD: {
    LoadInstruction *load_inst = dynamic_cast<LoadInstruction *>(inst);
    if (load_inst) {
      Operand result = load_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case ICMP:
  case FCMP: {
    IcmpInstruction *icmp_inst = dynamic_cast<IcmpInstruction *>(inst);
    if (icmp_inst) {
      Operand result = icmp_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case PHI: {
    PhiInstruction *phi_inst = dynamic_cast<PhiInstruction *>(inst);
    if (phi_inst) {
      Operand result = phi_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case CALL: {
    CallInstruction *call_inst = dynamic_cast<CallInstruction *>(inst);
    if (call_inst) {
      Operand result = call_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case GETELEMENTPTR: {
    GetElementptrInstruction *gep_inst =
        dynamic_cast<GetElementptrInstruction *>(inst);
    if (gep_inst) {
      Operand result = gep_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case ALLOCA: {
    AllocaInstruction *alloca_inst = dynamic_cast<AllocaInstruction *>(inst);
    if (alloca_inst) {
      Operand result = alloca_inst->GetResult();
      return getRegisterFromOperand(result);
    }
    break;
  }

  case ZEXT:
  case SITOFP:
  case FPTOSI:
  case FPEXT:
  case BITCAST: {
    // 类型转换指令通常有结果寄存器
    if (opcode == SITOFP) {
      SitofpInstruction *sitofp_inst = dynamic_cast<SitofpInstruction *>(inst);
      if (sitofp_inst) {
        return getRegisterFromOperand(sitofp_inst->result);
      }
    } else if (opcode == FPTOSI) {
      FptosiInstruction *fptosi_inst = dynamic_cast<FptosiInstruction *>(inst);
      if (fptosi_inst) {
        return getRegisterFromOperand(fptosi_inst->result);
      }
    } else if (opcode == FPEXT) {
      FpextInstruction *fpext_inst = dynamic_cast<FpextInstruction *>(inst);
      if (fpext_inst) {
        return getRegisterFromOperand(fpext_inst->result);
      }
    } else if (opcode == BITCAST) {
      BitCastInstruction *bitcast_inst =
          dynamic_cast<BitCastInstruction *>(inst);
      if (bitcast_inst) {
        return getRegisterFromOperand(bitcast_inst->dst);
      }
    }
    return getGenericInstructionResultRegister(inst);
  }

  case SELECT: {
    // select指令有结果寄存器
    SelectInstruction *select_inst = dynamic_cast<SelectInstruction *>(inst);
    if (select_inst) {
      return getRegisterFromOperand(select_inst->result);
    }
    return getGenericInstructionResultRegister(inst);
  }

  // 这些指令通常没有结果寄存器
  case STORE:
  case RET:
  case BR_COND:
  case BR_UNCOND:
    return -1;

  default:
    // 对于未知指令类型，尝试通用方法
    return getGenericInstructionResultRegister(inst);
  }

  return -1; // 没有结果寄存器
}

// ============================================================================
// 新增的高级辅助函数
// ============================================================================

void SSAOptimizer::addUsersToWorkList(
    int reg_num, const std::map<int, LLVMBlock> &blocks,
    std::queue<std::pair<int, size_t>> &work_list) {
  // 找到所有使用该寄存器的指令并加入工作列表
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    LLVMBlock block = block_pair.second;

    for (size_t i = 0; i < block->Instruction_list.size(); ++i) {
      Instruction inst = block->Instruction_list[i];
      if (!inst)
        continue;

      std::vector<Operand> operands = getInstructionOperands(inst);
      for (const auto &operand : operands) {
        if (isRegisterOperand(operand) &&
            getRegisterFromOperand(operand) == reg_num) {
          work_list.push({block_id, i});
          break;
        }
      }
    }
  }
}

bool SSAOptimizer::isPhiCopyCandidate(const Instruction &inst) {
  if (!inst || inst->GetOpcode() != PHI)
    return false;

  // φ函数如果所有输入都是同一个值，则为复制候选
  std::vector<Operand> operands = getInstructionOperands(inst);

  if (operands.empty())
    return false;

  // 获取第一个值作为参考
  int first_reg = -1;
  for (const auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      first_reg = getRegisterFromOperand(operand);
      break;
    }
  }

  if (first_reg == -1)
    return false;

  // 检查是否所有值都相同
  for (const auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      int reg_num = getRegisterFromOperand(operand);
      if (reg_num != first_reg) {
        return false;
      }
    }
  }

  return true;
}

int SSAOptimizer::getPhiSingleSource(const Instruction &inst) {
  if (!inst || inst->GetOpcode() != PHI)
    return -1;

  std::vector<Operand> operands = getInstructionOperands(inst);

  for (const auto &operand : operands) {
    if (isRegisterOperand(operand)) {
      return getRegisterFromOperand(operand);
    }
  }

  return -1;
}

void SSAOptimizer::removeTrivialCopies(
    std::map<int, LLVMBlock> &blocks,
    const std::unordered_map<int, int> &copy_map) {
  // 移除变成无用的复制指令
  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    auto it = block->Instruction_list.begin();
    while (it != block->Instruction_list.end()) {
      Instruction inst = *it;

      if (inst && isCopyInstruction(inst)) {
        int dest_reg, src_reg;
        if (extractCopyRegisters(inst, dest_reg, src_reg)) {
          // 检查这个复制是否已经被传播，如果是则删除
          auto copy_it = copy_map.find(dest_reg);
          if (copy_it != copy_map.end() && copy_it->second == src_reg) {
            // 检查是否还有其他地方使用dest_reg
            if (!hasOtherUsers(dest_reg, blocks, inst)) {
              it = block->Instruction_list.erase(it);
              continue;
            }
          }
        }
      }

      ++it;
    }
  }
}

bool SSAOptimizer::hasOtherUsers(int reg_num,
                                 const std::map<int, LLVMBlock> &blocks,
                                 const Instruction &excluding_inst) {
  // 检查除了指定指令外是否还有其他使用者
  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    for (const auto &inst : block->Instruction_list) {
      if (!inst || inst == excluding_inst)
        continue;

      std::vector<Operand> operands = getInstructionOperands(inst);
      for (const auto &operand : operands) {
        if (isRegisterOperand(operand) &&
            getRegisterFromOperand(operand) == reg_num) {
          return true;
        }
      }
    }
  }

  return false;
}

void SSAOptimizer::markControlDependencies(
    const Instruction &phi_inst, const std::map<int, LLVMBlock> &blocks,
    std::queue<Instruction> &work_list) {
  // 对于φ函数，标记其控制依赖的分支指令为有用
  // 这里简化处理：假设所有分支指令都是必要的

  for (const auto &block_pair : blocks) {
    LLVMBlock block = block_pair.second;

    for (const auto &inst : block->Instruction_list) {
      if (!inst)
        continue;

      int opcode = inst->GetOpcode();
      if (opcode == BR_COND &&
          useful_instructions.find(inst) == useful_instructions.end()) {
        markInstructionAsUseful(inst);
        work_list.push(inst);
      }
    }
  }
}

ConstantValue SSAOptimizer::computeArithmeticResult(const Instruction &inst) {
  if (!inst)
    return ConstantValue();

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.size() < 2)
    return ConstantValue();

  ConstantValue left = getConstantFromOperand(operands[0]);
  ConstantValue right = getConstantFromOperand(operands[1]);

  return evaluateArithmeticOp(static_cast<LLVMIROpcode>(inst->GetOpcode()),
                              left, right);
}

ConstantValue SSAOptimizer::computeComparisonResult(const Instruction &inst) {
  if (!inst)
    return ConstantValue();

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.size() < 2)
    return ConstantValue();

  ConstantValue left = getConstantFromOperand(operands[0]);
  ConstantValue right = getConstantFromOperand(operands[1]);

  return evaluateComparisonOp(static_cast<LLVMIROpcode>(inst->GetOpcode()),
                              left, right);
}

ConstantValue SSAOptimizer::computePhiResult(const Instruction &inst) {
  if (!inst || inst->GetOpcode() != PHI)
    return ConstantValue();

  std::vector<Operand> operands = getInstructionOperands(inst);
  if (operands.empty())
    return ConstantValue();

  // 检查所有输入是否为相同常量
  ConstantValue first_const;
  bool first_set = false;

  for (const auto &operand : operands) {
    ConstantValue const_val = getConstantFromOperand(operand);
    if (!const_val.isConstant()) {
      return ConstantValue(); // 有非常量输入
    }

    if (!first_set) {
      first_const = const_val;
      first_set = true;
    } else {
      // 检查是否与第一个常量相同
      if (first_const.type != const_val.type)
        return ConstantValue();

      if (first_const.isInt() && first_const.int_val != const_val.int_val) {
        return ConstantValue();
      }

      if (first_const.isFloat() &&
          first_const.float_val != const_val.float_val) {
        return ConstantValue();
      }
    }
  }

  return first_const;
}

void SSAOptimizer::replaceInstructionWithConstant(
    Instruction &inst, const ConstantValue &constant) {
  // 将指令替换为常量赋值
  // 这里需要根据具体的指令系统来实现
  // 简化处理：暂时不做实际替换，只更新常量映射

  // 实际实现中，可能需要：
  // 1. 创建新的常量赋值指令
  // 2. 替换原指令
  // 3. 更新所有引用
}

void SSAOptimizer::replaceOperandRegister(Operand &operand, int new_reg) {
  // 替换操作数中的寄存器编号
  // 这里需要根据具体的操作数类系统来实现

  // 简化处理：暂时不做实际替换
}

// 新增的通用操作数提取方法
std::vector<Operand>
SSAOptimizer::getGenericInstructionOperands(const Instruction &inst) {
  std::vector<Operand> operands;

  if (!inst)
    return operands;

  // 这里可以添加更通用的操作数提取逻辑
  // 例如通过反射或者指令基类的通用接口
  // 目前返回空向量作为占位符

  return operands;
}

// 新增的通用结果寄存器提取方法
int SSAOptimizer::getGenericInstructionResultRegister(const Instruction &inst) {
  if (!inst)
    return -1;

  // 这里可以添加更通用的结果寄存器提取逻辑
  // 例如通过指令基类的通用接口
  // 目前返回-1作为占位符

  return -1;
}
