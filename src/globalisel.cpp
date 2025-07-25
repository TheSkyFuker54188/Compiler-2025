#include "../include/globalisel.h"
#include "../include/riscv_mir.h"
#include <iostream>
#include <cassert>

// ===--------------------------------------------------------------------=== //
// IRTranslator 实现
// ===--------------------------------------------------------------------=== //

bool IRTranslator::translateModule(const LLVMIR& llvm_ir, MachineModule& mir_module) {
  machine_module = &mir_module;
  
  // 遍历所有函数并翻译
  for (const auto& func_block_pair : llvm_ir.function_block_map) {
    const FuncDefInstruction& func = func_block_pair.first;
    const std::map<int, LLVMBlock>& blocks = func_block_pair.second;
    
    if (!translateFunction(func, blocks)) {
      return false;
    }
  }
  
  return true;
}

bool IRTranslator::translateFunction(const FuncDefInstruction& func, 
                                   const std::map<int, LLVMBlock>& blocks) {
  // 创建机器函数
  current_function = machine_module->createFunction(func->Func_name);
  
  // 重置状态
  vreg_map.clear();
  block_map.clear();
  next_mir_reg = 0;
  
  // 首先创建所有基本块
  for (const auto& block_pair : blocks) {
    int block_id = block_pair.first;
    MachineBasicBlock* mir_block = current_function->createBasicBlock();
    block_map[block_id] = mir_block;
  }
  
  // 处理函数参数：为参数创建虚拟寄存器并与a0-a7关联
  setupFunctionParameters(func);
  
  // 翻译所有基本块
  for (const auto& block_pair : blocks) {
    LLVMBlock llvm_block = block_pair.second;
    current_block = block_map[block_pair.first];
    
    if (!translateBasicBlock(llvm_block)) {
      return false;
    }
  }
  
  return true;
}

void IRTranslator::setupFunctionParameters(const FuncDefInstruction& func) {
  // 在IRTranslation阶段，我们只创建虚拟寄存器来表示函数参数
  // 参数与物理寄存器的映射将在RegisterAllocation阶段处理
  
  auto& params = func->formals;
  auto& param_regs_llvm = func->formals_reg;
  
  if (params.empty()) {
    return; // 没有参数
  }
  
  // 为每个函数参数创建虚拟寄存器，并建立映射关系
  for (size_t i = 0; i < params.size(); ++i) {
    // 为每个参数创建虚拟寄存器
    MachineRegister* param_vreg = current_function->createVirtualRegister(RISCVRegClass::GPR);
    
    // 将LLVM IR中的参数操作数与我们创建的虚拟寄存器关联
    if (i < param_regs_llvm.size()) {
      // 建立LLVM IR参数寄存器到MIR虚拟寄存器的映射
      // 这样后续翻译LLVM IR指令时可以找到正确的虚拟寄存器
      int llvm_reg_num = getOperandRegNumber(param_regs_llvm[i]);
      if (llvm_reg_num >= 0) {
        vreg_map[llvm_reg_num] = param_vreg;
      }
    }
    
    // 注意：参数虚拟寄存器与物理寄存器(a0-a7)的映射关系
    // 将在RegisterAllocation阶段处理，那时会确保：
    // - 第一个参数虚拟寄存器映射到a0(x10)
    // - 第二个参数虚拟寄存器映射到a1(x11)
    // - 以此类推...
  }
}

bool IRTranslator::translateBasicBlock(LLVMBlock llvm_block) {
  // 翻译块中的所有指令
  for (const auto& inst : llvm_block->Instruction_list) {
    if (!translateInstruction(inst)) {
      return false;
    }
  }
  return true;
}

bool IRTranslator::translateInstruction(const Instruction& inst) {
  LLVMIROpcode opcode = static_cast<LLVMIROpcode>(inst->GetOpcode());
  
  switch (opcode) {
    case ADD:
      translateAdd(inst);
      break;
    case FADD:
      translateFadd(inst);
      break;
    case SUB:
      translateSub(inst);
      break;
    case FSUB:
      translateFsub(inst);
      break;
    case MUL_OP:
      translateMul(inst);
      break;
    case FMUL:
      translateFmul(inst);
      break;
    case DIV_OP:
      translateDiv(inst);
      break;
    case FDIV:
      translateFdiv(inst);
      break;
    case LOAD:
      translateLoad(dynamic_cast<const LoadInstruction*>(inst));
      break;
    case STORE:
      translateStore(dynamic_cast<const StoreInstruction*>(inst));
      break;
    case CALL:
      translateCall(dynamic_cast<const CallInstruction*>(inst));
      break;
    case RET:
      translateRet(dynamic_cast<const RetInstruction*>(inst));
      break;
    case ICMP:
      translateIcmp(dynamic_cast<const IcmpInstruction*>(inst));
      break;
    case FCMP:
      translateFcmp(dynamic_cast<const FcmpInstruction*>(inst));
      break;
    case BR_COND:
    case BR_UNCOND:
      translateBr(inst);
      break;
    case ALLOCA:
      translateAlloca(inst);
      break;
    case GETELEMENTPTR:
      translateGep(dynamic_cast<const GetElementptrInstruction*>(inst));
      break;
    case BITAND:
      translateAnd(inst);
      break;
    case BITOR:
      translateOr(inst);
      break;
    case BITXOR:
      translateXor(inst);
      break;
    case MOD_OP:
      translateMod(inst);
      break;
    case ZEXT:
      translateZext(inst);
      break;
    case FPTOSI:
      translateFptosi(inst);
      break;
    case SITOFP:
      translateSitofp(inst);
      break;
    default:
      std::cerr << "未支持的指令类型: " << static_cast<int>(opcode) << " (应该在枚举中查找对应值)" << std::endl;
      return false;
  }
  
  return true;
}

void IRTranslator::translateAdd(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  
  // 获取源操作数
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  // 创建通用加法指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_ADD);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateSub(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_SUB);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateMul(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_MUL);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateDiv(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_DIV);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFadd(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  
  // 获取源操作数
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  // 创建浮点加法指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_FADD);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFsub(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  
  // 获取源操作数
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  // 创建浮点减法指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_FSUB);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFmul(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  
  // 获取源操作数
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  // 创建浮点乘法指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_FMUL);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFdiv(const BasicInstruction* inst) {
  const ArithmeticInstruction* arith_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!arith_inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(arith_inst->GetResult());
  
  // 获取源操作数
  MachineOperand src1_op = translateOperand(arith_inst->GetOp1());
  MachineOperand src2_op = translateOperand(arith_inst->GetOp2());
  
  // 创建浮点除法指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_FDIV);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateLoad(const LoadInstruction* inst) {
  if (!inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(inst->GetResult());
  
  // 获取地址操作数
  MachineOperand addr_op = translateOperand(inst->GetPointer());
  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_LOAD);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(addr_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateStore(const StoreInstruction* inst) {
  if (!inst) return;
  
  // 获取值和地址操作数
  MachineOperand value_op = translateOperand(inst->GetValue());
  MachineOperand addr_op = translateOperand(inst->GetPointer());
  
  // 如果存储的值是立即数，需要先将其加载到虚拟寄存器中
  if (value_op.isImm()) {
    // 创建虚拟寄存器来保存立即数
    MachineRegister* temp_reg = current_function->createVirtualRegister(RISCVRegClass::GPR);
    
    // 生成G_CONSTANT指令：将立即数加载到寄存器
    auto constant_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_CONSTANT);
    constant_inst->addOperand(MachineOperand(temp_reg));  // 目标寄存器
    constant_inst->addOperand(value_op);                  // 立即数值
    current_block->addInstruction(std::move(constant_inst));
    
    // 更新value_op为寄存器操作数
    value_op = MachineOperand(temp_reg);
  }
  
  // 生成G_STORE指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_STORE);
  mir_inst->addOperand(value_op);
  mir_inst->addOperand(addr_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateCall(const CallInstruction* inst) {
  if (!inst) return;
  
  // RISC-V ABI: 参数通过a0-a7寄存器传递，返回值通过a0寄存器返回
  const std::vector<int> param_regs = {10, 11, 12, 13, 14, 15, 16, 17}; // a0-a7 对应 x10-x17
  
  // 第一步：为每个参数生成移动指令，将参数移动到正确的寄存器
  auto args = inst->GetArgs();
  for (size_t i = 0; i < args.size() && i < param_regs.size(); ++i) {
    // 创建参数寄存器(a0, a1, ...)
    MachineRegister* param_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, param_regs[i]);
    
    // 获取参数操作数
    MachineOperand arg_op = translateOperand(args[i].second);
    
    // 生成移动指令：mov a0, arg1; mov a1, arg2; ...
    auto move_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY);
    move_inst->addOperand(MachineOperand(param_reg));  // 目标：参数寄存器
    move_inst->addOperand(arg_op);                     // 源：参数值
    
    current_block->addInstruction(std::move(move_inst));
  }
  
  // 第二步：创建函数调用指令  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_CALL);
  
  // 添加函数名作为全局符号
  mir_inst->addOperand(MachineOperand(inst->GetFuncName()));
  
  // 第三步：处理返回值
  MachineRegister* result_reg = nullptr;
  if (inst->GetType() != LLVMType::VOID_TYPE) {
    result_reg = getOrCreateVRegForOperand(inst->GetResult());
    // 将返回值寄存器作为第一个操作数
    mir_inst->operands.insert(mir_inst->operands.begin(), MachineOperand(result_reg));
  }
  
  current_block->addInstruction(std::move(mir_inst));
  
  // 第四步：如果有返回值，生成从a0复制到结果寄存器的指令
  if (result_reg) {
    MachineRegister* a0_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 10); // a0 = x10
    
    auto copy_ret_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY);
    copy_ret_inst->addOperand(MachineOperand(result_reg));  // 目标：结果寄存器
    copy_ret_inst->addOperand(MachineOperand(a0_reg));      // 源：a0寄存器
    
    current_block->addInstruction(std::move(copy_ret_inst));
  }
}

void IRTranslator::translateRet(const RetInstruction* inst) {
  if (!inst) return;
  
  // 如果有返回值，需要先将其移动到a0寄存器
  if (inst->GetRetVal()) {
    MachineOperand ret_op = translateOperand(inst->GetRetVal());
    
    // 创建a0物理寄存器
    MachineRegister* a0_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 10); // x10 = a0
    
    // 生成G_COPY指令：将返回值移动到a0
    auto copy_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY);
    copy_inst->addOperand(MachineOperand(a0_reg));  // 目标：a0
    copy_inst->addOperand(ret_op);                  // 源：返回值
    current_block->addInstruction(std::move(copy_inst));
  }
  
  // 生成G_RET指令（不带操作数，因为返回值已经在a0中）
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_RET);
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateIcmp(const IcmpInstruction* inst) {
  if (!inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(inst->GetResult());
  
  // 获取比较操作数
  MachineOperand src1_op = translateOperand(inst->GetOp1());
  MachineOperand src2_op = translateOperand(inst->GetOp2());
  
  // 获取比较条件
  IcmpCond cond = inst->GetCond();
  
  // 创建G_ICMP指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_ICMP);
  mir_inst->addOperand(MachineOperand(result_reg));  // 结果寄存器
  mir_inst->addOperand(src1_op);                     // 操作数1
  mir_inst->addOperand(src2_op);                     // 操作数2
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(cond))); // 比较条件
  
  // 添加操作数类型信息，用于后续指令选择
  LLVMType op_type = inst->GetType();
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(op_type))); // 操作数类型
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFcmp(const FcmpInstruction* inst) {
  if (!inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(inst->GetResult());
  
  // 获取比较操作数
  MachineOperand src1_op = translateOperand(inst->GetOp1());
  MachineOperand src2_op = translateOperand(inst->GetOp2());
  
  // 获取浮点比较条件
  FcmpCond cond = inst->GetCond();
  
  // 创建G_FCMP指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_FCMP);
  mir_inst->addOperand(MachineOperand(result_reg));  // 结果寄存器
  mir_inst->addOperand(src1_op);                     // 操作数1
  mir_inst->addOperand(src2_op);                     // 操作数2
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(cond))); // 比较条件
  
  // 添加操作数类型信息
  LLVMType op_type = inst->GetType();
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(op_type))); // 操作数类型
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateBr(const BasicInstruction* inst) {
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_BR);
  
  // 尝试转换为条件分支
  const BrCondInstruction* br_cond = dynamic_cast<const BrCondInstruction*>(inst);
  if (br_cond) {
    // 条件分支：br condition, true_label, false_label
    MachineOperand cond_op = translateOperand(br_cond->GetCond());
    mir_inst->addOperand(cond_op);
    
    // 添加分支目标（使用标签操作数）
    MachineOperand true_op = translateOperand(br_cond->GetTrueLabel());
    MachineOperand false_op = translateOperand(br_cond->GetFalseLabel());
    mir_inst->addOperand(true_op);
    mir_inst->addOperand(false_op);
  } else {
    // 尝试转换为无条件分支
    const BrUncondInstruction* br_uncond = dynamic_cast<const BrUncondInstruction*>(inst);
    if (br_uncond) {
      // 无条件分支：br label
      MachineOperand dest_op = translateOperand(br_uncond->GetLabel());
      mir_inst->addOperand(dest_op);
    }
  }
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateAlloca(const Instruction& inst) {
  const AllocaInstruction* alloca_inst = dynamic_cast<const AllocaInstruction*>(inst);
  if (!alloca_inst) return;
  
  // 创建结果寄存器 - alloca返回指针
  MachineRegister* result_reg = getOrCreateVRegForOperand(alloca_inst->GetResult());
  
  // 计算数组大小
  int array_size = calculateArraySize(alloca_inst);
  
  // calculateArraySize现在可以精确计算基于类型和维度的数组大小
  
  // 分配栈槽
  int stack_slot = current_function->allocateStackSlot(array_size);
  
  // 创建栈地址计算指令：result = stack_base + offset
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_STACK_ADDR);
  mir_inst->addOperand(MachineOperand(result_reg));           // 目标寄存器
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(stack_slot))); // 栈偏移
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateGep(const GetElementptrInstruction* inst) {
  if (!inst) return;
  
  // 获取结果寄存器
  MachineRegister* result_reg = getOrCreateVRegForOperand(inst->GetResult());
  
  // 获取基指针操作数
  MachineOperand base_op = translateOperand(inst->GetPtrVal());
  
  // 获取所有索引和维度信息
  auto indexes = inst->GetIndexes();
  auto dims = inst->GetDims();
  
  // 创建GEP指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_GEP);
  mir_inst->addOperand(MachineOperand(result_reg));  // 结果
  mir_inst->addOperand(base_op);                     // 基指针
  
  // 添加索引数量
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(indexes.size())));
  
  // 添加所有索引操作数
  for (const auto& index : indexes) {
    MachineOperand index_op = translateOperand(index);
    mir_inst->addOperand(index_op);
  }
  
  // 推断元素大小（基于类型）
  int element_size = inferElementSize(inst->GetType());
  mir_inst->addOperand(MachineOperand(static_cast<int64_t>(element_size)));
  
  // 添加从类型信息中提取的维度大小
  if (!dims.empty()) {
    // 添加维度数量
    mir_inst->addOperand(MachineOperand(static_cast<int64_t>(dims.size())));
    
    // 添加每个维度的大小
    for (int dim_size : dims) {
      mir_inst->addOperand(MachineOperand(static_cast<int64_t>(dim_size)));
    }
  } else {
    // 没有维度信息的情况（如指针算术）
    mir_inst->addOperand(MachineOperand(static_cast<int64_t>(0))); // 维度数量为0
  }
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateAnd(const BasicInstruction* inst) {
  const ArithmeticInstruction* and_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!and_inst) return;
  
  // 获取结果寄存器和操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(and_inst->GetResult());
  MachineOperand src1_op = translateOperand(and_inst->GetOp1());
  MachineOperand src2_op = translateOperand(and_inst->GetOp2());
  
  // 创建位与指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_AND);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateOr(const BasicInstruction* inst) {
  const ArithmeticInstruction* or_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!or_inst) return;
  
  // 获取结果寄存器和操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(or_inst->GetResult());
  MachineOperand src1_op = translateOperand(or_inst->GetOp1());
  MachineOperand src2_op = translateOperand(or_inst->GetOp2());
  
  // 创建位或指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_OR);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateXor(const BasicInstruction* inst) {
  const ArithmeticInstruction* xor_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!xor_inst) return;
  
  // 获取结果寄存器和操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(xor_inst->GetResult());
  MachineOperand src1_op = translateOperand(xor_inst->GetOp1());
  MachineOperand src2_op = translateOperand(xor_inst->GetOp2());
  
  // 创建位异或指令
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_XOR);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateMod(const BasicInstruction* inst) {
  const ArithmeticInstruction* mod_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!mod_inst) return;
  
  // 获取结果寄存器和操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(mod_inst->GetResult());
  MachineOperand src1_op = translateOperand(mod_inst->GetOp1());
  MachineOperand src2_op = translateOperand(mod_inst->GetOp2());
  
  // 创建取模指令 (RISC-V使用REM指令)
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_DIV); // 暂时用G_DIV，后续会添加G_REM
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src1_op);
  mir_inst->addOperand(src2_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateZext(const BasicInstruction* inst) {
  const ArithmeticInstruction* zext_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!zext_inst) return;
  
  // 获取结果寄存器和源操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(zext_inst->GetResult());
  MachineOperand src_op = translateOperand(zext_inst->GetOp1());
  
  // 零扩展通常通过COPY实现（RISC-V寄存器自然零扩展）
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY);
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateFptosi(const BasicInstruction* inst) {
  const ArithmeticInstruction* fptosi_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!fptosi_inst) return;
  
  // 获取结果寄存器和源操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(fptosi_inst->GetResult());
  MachineOperand src_op = translateOperand(fptosi_inst->GetOp1());
  
  // 浮点转整数指令 (需要在指令选择阶段转换为具体的RISC-V指令)
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY); // 暂时用G_COPY
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

void IRTranslator::translateSitofp(const BasicInstruction* inst) {
  const ArithmeticInstruction* sitofp_inst = dynamic_cast<const ArithmeticInstruction*>(inst);
  if (!sitofp_inst) return;
  
  // 获取结果寄存器和源操作数
  MachineRegister* result_reg = getOrCreateVRegForOperand(sitofp_inst->GetResult());
  MachineOperand src_op = translateOperand(sitofp_inst->GetOp1());
  
  // 整数转浮点指令 (需要在指令选择阶段转换为具体的RISC-V指令)  
  auto mir_inst = std::make_unique<MachineInstruction>(RISCVOpcode::G_COPY); // 暂时用G_COPY
  mir_inst->addOperand(MachineOperand(result_reg));
  mir_inst->addOperand(src_op);
  
  current_block->addInstruction(std::move(mir_inst));
}

MachineRegister* IRTranslator::getOrCreateVReg(int llvm_reg, RISCVRegClass reg_class) {
  auto it = vreg_map.find(llvm_reg);
  if (it != vreg_map.end()) {
    return it->second;
  }
  
  MachineRegister* new_reg = current_function->createVirtualRegister(reg_class);
  vreg_map[llvm_reg] = new_reg;
  return new_reg;
}

MachineRegister* IRTranslator::getOrCreateVRegForOperand(Operand llvm_operand) {
  if (!llvm_operand) return nullptr;
  
  // 尝试从操作数中提取寄存器编号
  int reg_num = getOperandRegNumber(llvm_operand);
  if (reg_num >= 0) {
    return getOrCreateVReg(reg_num, RISCVRegClass::GPR);
  }
  
  // 如果无法提取寄存器编号，创建新的虚拟寄存器
  return current_function->createVirtualRegister(RISCVRegClass::GPR);
}

MachineOperand IRTranslator::translateOperand(Operand llvm_operand) {
  if (!llvm_operand) {
    // 返回一个默认的虚拟寄存器
    MachineRegister* reg = current_function->createVirtualRegister(RISCVRegClass::GPR);
    return MachineOperand(reg);
  }
  
  // 检查是否是立即数
  if (auto* imm_i32 = dynamic_cast<ImmI32Operand*>(llvm_operand)) {
    return MachineOperand(static_cast<int64_t>(imm_i32->GetIntImmVal()));
  }
  
  if (auto* imm_f32 = dynamic_cast<ImmF32Operand*>(llvm_operand)) {
    // 正确处理浮点立即数，保持浮点精度
    return MachineOperand(imm_f32->GetFloatVal());
  }
  
  // 检查是否是标签操作数
  if (auto* label_op = dynamic_cast<LabelOperand*>(llvm_operand)) {
    int llvm_label = label_op->GetLabelNo();
    // 通过block_map获取正确的MIR基本块ID
    auto it = block_map.find(llvm_label);
    if (it != block_map.end()) {
      return MachineOperand(it->second->block_id);
    }
    // 如果找不到，使用原始标签号作为fallback
    return MachineOperand(llvm_label);
  }
  
  // 检查是否是全局变量操作数
  if (auto* global_op = dynamic_cast<GlobalOperand*>(llvm_operand)) {
    std::string global_name = global_op->GetName();
    return MachineOperand(global_name);
  }
  
  // 其他情况创建或获取虚拟寄存器
  MachineRegister* reg = getOrCreateVRegForOperand(llvm_operand);
  return MachineOperand(reg);
}

int IRTranslator::getOperandRegNumber(Operand operand) {
  if (!operand) return -1;
  
  // 尝试从RegOperand中获取寄存器编号
  if (auto* reg_op = dynamic_cast<RegOperand*>(operand)) {
    return reg_op->GetRegNo();
  }
  
  // 对于其他类型的操作数，返回-1表示无法获取寄存器编号
  return -1;
}

int IRTranslator::calculateArraySize(const AllocaInstruction* alloca_inst) {
  if (!alloca_inst) return 4; // 默认单个元素大小
  
  // 获取类型和维度信息
  LLVMType element_type = alloca_inst->GetType();
  const std::vector<int>& dims = alloca_inst->GetDims();
  
  // 计算基础元素大小
  int element_size = inferElementSize(element_type);
  
  // 如果没有维度信息，这是单个变量
  if (dims.empty()) {
    return element_size;
  }
  
  // 计算多维数组的总大小
  int total_elements = 1;
  for (int dim : dims) {
    if (dim <= 0) {
      // 无效维度，使用默认大小
      return element_size * 10; // 假设默认数组大小为10
    }
    total_elements *= dim;
  }
  
  int total_size = total_elements * element_size;
  
  // 高级内存对齐：根据元素类型选择对齐策略
  int alignment = getTypeAlignment(element_type);
  if (total_size % alignment != 0) {
    total_size = ((total_size / alignment) + 1) * alignment;
  }
  
  // 安全检查：防止过大的分配
  const int MAX_ARRAY_SIZE = 1024 * 1024; // 1MB限制
  if (total_size > MAX_ARRAY_SIZE) {
    // 对于过大的数组，提供警告并使用最大允许大小
    total_size = MAX_ARRAY_SIZE;
  }
  
  // 最小大小检查：确保至少分配4字节
  if (total_size < 4) {
    total_size = 4;
  }
  
  return total_size;
}

int IRTranslator::inferElementSize(LLVMType type) {
  // 根据LLVM类型推断元素大小
  switch (type) {
    case I32:
      return 4;  // int: 4 bytes
    case FLOAT32:
      return 4;  // float: 4 bytes  
    case I64:
      return 8;  // int64: 8 bytes
    case DOUBLE:
      return 8;  // double: 8 bytes
    case VOID_TYPE:
      return 1;  // void*: 1 byte (for pointer arithmetic)
    case PTR:
      return 8;  // pointer: 8 bytes (64-bit)
    case I8:
      return 1;  // byte: 1 byte
    case I1:
      return 1;  // bool: 1 byte
    default:
      return 4;  // 默认4字节
  }
}

int IRTranslator::getTypeAlignment(LLVMType type) {
  // 根据LLVM类型返回推荐的内存对齐字节数
  switch (type) {
    case I32:
    case FLOAT32:
      return 4;  // 32位类型：4字节对齐
    case I64:
    case DOUBLE:
    case PTR:
      return 8;  // 64位类型：8字节对齐
    case I8:
    case I1:
      return 1;  // 字节类型：1字节对齐
    case VOID_TYPE:
      return 4;  // void*按指针大小对齐
    default:
      return 4;  // 默认4字节对齐
  }
}

RISCVRegClass IRTranslator::getRegClassForType(LLVMType type) {
  switch (type) {
    case I32:
    case I64:
    case I8:
    case I1:
    case PTR:
      return RISCVRegClass::GPR;
    case FLOAT32:
    case DOUBLE:
      return RISCVRegClass::FPR;
    default:
      return RISCVRegClass::GPR;
  }
}

RISCVOpcode IRTranslator::getGenericOpcode(LLVMIROpcode llvm_op) {
  switch (llvm_op) {
    case ADD: return RISCVOpcode::G_ADD;
    case SUB: return RISCVOpcode::G_SUB;
    case MUL_OP: return RISCVOpcode::G_MUL;
    case DIV_OP: return RISCVOpcode::G_DIV;
    case LOAD: return RISCVOpcode::G_LOAD;
    case STORE: return RISCVOpcode::G_STORE;
    case ICMP: return RISCVOpcode::G_ICMP;
    case CALL: return RISCVOpcode::G_CALL;
    case RET: return RISCVOpcode::G_RET;
    default: return RISCVOpcode::G_COPY; // 默认
  }
}

// ===--------------------------------------------------------------------=== //
// RISCVLegalizer 实现
// ===--------------------------------------------------------------------=== //

RISCVLegalizer::RISCVLegalizer() : current_function(nullptr) {
  initLegalizeTable();
}

void RISCVLegalizer::initLegalizeTable() {
  // 整数运算 - 32位是合法的
  legalize_table[{RISCVOpcode::G_ADD, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_ADD, OperandSize::s32};
  legalize_table[{RISCVOpcode::G_SUB, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_SUB, OperandSize::s32};
  legalize_table[{RISCVOpcode::G_MUL, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_MUL, OperandSize::s32};
  legalize_table[{RISCVOpcode::G_DIV, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_DIV, OperandSize::s32};
  
  // 64位运算也是合法的（对于RV64）
  legalize_table[{RISCVOpcode::G_ADD, OperandSize::s64}] = {LegalizeAction::Legal, RISCVOpcode::G_ADD, OperandSize::s64};
  legalize_table[{RISCVOpcode::G_SUB, OperandSize::s64}] = {LegalizeAction::Legal, RISCVOpcode::G_SUB, OperandSize::s64};
  legalize_table[{RISCVOpcode::G_MUL, OperandSize::s64}] = {LegalizeAction::Legal, RISCVOpcode::G_MUL, OperandSize::s64};
  legalize_table[{RISCVOpcode::G_DIV, OperandSize::s64}] = {LegalizeAction::Legal, RISCVOpcode::G_DIV, OperandSize::s64};
  
  // 8位和16位需要扩展到32位
  legalize_table[{RISCVOpcode::G_ADD, OperandSize::s8}] = {LegalizeAction::Expand, RISCVOpcode::G_ADD, OperandSize::s32};
  legalize_table[{RISCVOpcode::G_ADD, OperandSize::s16}] = {LegalizeAction::Expand, RISCVOpcode::G_ADD, OperandSize::s32};
  
  // 内存操作
  legalize_table[{RISCVOpcode::G_LOAD, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_LOAD, OperandSize::s32};
  legalize_table[{RISCVOpcode::G_STORE, OperandSize::s32}] = {LegalizeAction::Legal, RISCVOpcode::G_STORE, OperandSize::s32};
}

bool RISCVLegalizer::legalizeFunction(MachineFunction& func) {
  current_function = &func;
  
  for (auto& block : func.basic_blocks) {
    for (auto& inst : block->instructions) {
      if (!legalizeInstruction(*inst)) {
        return false;
      }
    }
  }
  
  return true;
}

bool RISCVLegalizer::isLegal(RISCVOpcode opcode, OperandSize size) const {
  auto it = legalize_table.find({opcode, size});
  if (it != legalize_table.end()) {
    return it->second.action == LegalizeAction::Legal;
  }
  return false;
}

LegalizeInfo RISCVLegalizer::getLegalizeInfo(RISCVOpcode opcode, OperandSize size) const {
  auto it = legalize_table.find({opcode, size});
  if (it != legalize_table.end()) {
    return it->second;
  }
  return {LegalizeAction::Legal, opcode, size}; // 默认合法
}

bool RISCVLegalizer::legalizeInstruction(MachineInstruction& inst) {
  OperandSize size = getTypeSize(inst.opcode);
  
  if (isLegal(inst.opcode, size)) {
    return true; // 已经合法
  }
  
  LegalizeInfo info = getLegalizeInfo(inst.opcode, size);
  
  switch (info.action) {
    case LegalizeAction::Legal:
      return true;
    case LegalizeAction::Expand:
      return expandInstruction(inst);
    case LegalizeAction::Lower:
      return lowerInstruction(inst);
    case LegalizeAction::Custom:
    case LegalizeAction::Libcall:
      // 自定义处理或库调用
      return true;
  }
  
  return false;
}

bool RISCVLegalizer::expandInstruction(MachineInstruction& inst) {
  // 简化实现：将小于32位的操作扩展为32位
  // 实际实现中需要根据具体指令类型进行处理
  return true;
}

bool RISCVLegalizer::lowerInstruction(MachineInstruction& inst) {
  // 将复杂操作降低为更简单的操作
  return true;
}

OperandSize RISCVLegalizer::getTypeSize(RISCVOpcode opcode) const {
  // 简化实现，实际需要根据指令的操作数类型确定
  return OperandSize::s32;
}

bool RISCVLegalizer::needsPromotion(OperandSize current, OperandSize target) const {
  return static_cast<int>(current) < static_cast<int>(target);
}

bool RISCVLegalizer::needsTruncation(OperandSize current, OperandSize target) const {
  return static_cast<int>(current) > static_cast<int>(target);
}

// ===--------------------------------------------------------------------=== //
// RISCVRegBankSelect 实现
// ===--------------------------------------------------------------------=== //

bool RISCVRegBankSelect::assignRegBanks(MachineFunction& func) {
  current_function = &func;
  
  for (auto& block : func.basic_blocks) {
    for (auto& inst : block->instructions) {
      if (!selectRegBankForInstruction(*inst)) {
        return false;
      }
    }
  }
  
  return true;
}

RISCVRegBank RISCVRegBankSelect::getRegBank(MachineRegister* reg) const {
  auto it = reg_bank_map.find(reg);
  if (it != reg_bank_map.end()) {
    return it->second;
  }
  return RISCVRegBank::INVALID_BANK;
}

void RISCVRegBankSelect::setRegBank(MachineRegister* reg, RISCVRegBank bank) {
  reg_bank_map[reg] = bank;
}

bool RISCVRegBankSelect::selectRegBankForInstruction(MachineInstruction& inst) {
  RISCVRegBank bank = getDefaultRegBank(inst.opcode);
  
  // 为所有寄存器操作数分配寄存器组
  for (auto& operand : inst.operands) {
    if (operand.isReg()) {
      setRegBank(operand.reg, bank);
    }
  }
  
  return true;
}

RISCVRegBank RISCVRegBankSelect::getDefaultRegBank(RISCVOpcode opcode) const {
  if (isFloatingPointOp(opcode)) {
    return RISCVRegBank::FPR_BANK;
  }
  return RISCVRegBank::GPR_BANK;
}

bool RISCVRegBankSelect::isFloatingPointOp(RISCVOpcode opcode) const {
  switch (opcode) {
    case RISCVOpcode::FADD_S:
    case RISCVOpcode::FSUB_S:
    case RISCVOpcode::FMUL_S:
    case RISCVOpcode::FDIV_S:
    case RISCVOpcode::FLW:
    case RISCVOpcode::FSW:
      return true;
    default:
      return false;
  }
}

void RISCVRegBankSelect::insertCopyIfNeeded(MachineRegister* src, MachineRegister* dst) {
  // 如果源寄存器和目标寄存器在不同的寄存器组，插入转换指令
  RISCVRegBank src_bank = getRegBank(src);
  RISCVRegBank dst_bank = getRegBank(dst);
  
  if (src_bank != dst_bank && src_bank != RISCVRegBank::INVALID_BANK && 
      dst_bank != RISCVRegBank::INVALID_BANK) {
    // 插入寄存器组转换指令
    // 这里简化处理，实际需要根据具体的转换类型生成相应指令
  }
} 

// ===--------------------------------------------------------------------=== //
// RISCVInstructionSelect 实现
// ===--------------------------------------------------------------------=== //

bool RISCVInstructionSelect::selectInstructions(MachineFunction& func) {
  current_function = &func;
  initSelectionPatterns();
  
  for (auto& block : func.basic_blocks) {
    current_block = block.get();  // 设置当前基本块
    for (auto& inst : block->instructions) {
      if (!selectInstruction(*inst)) {
        return false;
      }
    }
  }
  
  return true;
}

void RISCVInstructionSelect::initSelectionPatterns() {
  // 初始化指令选择模式
  // 通用操作到RISC-V特定指令的映射
  selection_patterns[RISCVOpcode::G_ADD] = {RISCVOpcode::ADD, RISCVOpcode::ADDI};
  selection_patterns[RISCVOpcode::G_SUB] = {RISCVOpcode::SUB};
  selection_patterns[RISCVOpcode::G_MUL] = {RISCVOpcode::MUL, RISCVOpcode::MULW};
  selection_patterns[RISCVOpcode::G_DIV] = {RISCVOpcode::DIV, RISCVOpcode::DIVW};
  selection_patterns[RISCVOpcode::G_LOAD] = {RISCVOpcode::LW, RISCVOpcode::LH, RISCVOpcode::LB};
  selection_patterns[RISCVOpcode::G_STORE] = {RISCVOpcode::SW, RISCVOpcode::SH, RISCVOpcode::SB};
  selection_patterns[RISCVOpcode::G_CONSTANT] = {RISCVOpcode::LI};
  selection_patterns[RISCVOpcode::G_SHL] = {RISCVOpcode::SLL, RISCVOpcode::SLLI};
  selection_patterns[RISCVOpcode::G_SHR] = {RISCVOpcode::SRL, RISCVOpcode::SRLI};
}

bool RISCVInstructionSelect::selectInstruction(MachineInstruction& inst) {
  switch (inst.opcode) {
    case RISCVOpcode::G_ADD:
      return selectAdd(inst);
    case RISCVOpcode::G_SUB:
      return selectSub(inst);
    case RISCVOpcode::G_MUL:
      return selectMul(inst);
    case RISCVOpcode::G_DIV:
      return selectDiv(inst);
    case RISCVOpcode::G_LOAD:
      return selectLoad(inst);
    case RISCVOpcode::G_STORE:
      return selectStore(inst);
    case RISCVOpcode::G_BR:
      return selectBranch(inst);
    case RISCVOpcode::G_CALL:
      return selectCall(inst);
    case RISCVOpcode::G_RET:
      return selectRet(inst);
    case RISCVOpcode::G_ICMP:
    case RISCVOpcode::G_FCMP:
      return selectCmp(inst);
    case RISCVOpcode::G_CONSTANT:
      return selectConstant(inst);
    case RISCVOpcode::G_COPY:
      return selectCopy(inst);
    case RISCVOpcode::G_STACK_ADDR:
      return selectStackAddr(inst);
    case RISCVOpcode::G_GEP:
      return selectGep(inst);
    case RISCVOpcode::G_AND:
      return selectAnd(inst);
    case RISCVOpcode::G_OR:
      return selectOr(inst);
    case RISCVOpcode::G_XOR:
      return selectXor(inst);
    case RISCVOpcode::G_SHL:
      return selectShl(inst);
    case RISCVOpcode::G_SHR:
      return selectShr(inst);
    case RISCVOpcode::G_FADD:
      return selectFadd(inst);
    case RISCVOpcode::G_FSUB:
      return selectFsub(inst);
    case RISCVOpcode::G_FMUL:
      return selectFmul(inst);
    case RISCVOpcode::G_FDIV:
      return selectFdiv(inst);
    default:
      // 已经是目标特定指令，不需要选择
      return true;
  }
}

bool RISCVInstructionSelect::selectAdd(MachineInstruction& inst) {
  // 检查第二个操作数是否是立即数
  if (inst.operands.size() >= 3 && inst.operands[2].isImm()) {
    int64_t imm_value = inst.operands[2].imm;
    if (is12BitImm(imm_value)) {
      // 使用 ADDI 指令
      inst.opcode = RISCVOpcode::ADDI;
      return true;
    }
  }
  
  // 使用 ADD 指令
  inst.opcode = RISCVOpcode::ADD;
  return true;
}

bool RISCVInstructionSelect::selectSub(MachineInstruction& inst) {
  // RISC-V 没有 SUBI 指令，但可以使用 ADDI 负值
  if (inst.operands.size() >= 3 && inst.operands[2].isImm()) {
    int64_t imm_value = -inst.operands[2].imm;
    if (is12BitImm(imm_value)) {
      // 转换为 ADDI 负值
      inst.opcode = RISCVOpcode::ADDI;
      inst.operands[2] = MachineOperand(imm_value);
      return true;
    }
  }
  
  // 使用 SUB 指令
  inst.opcode = RISCVOpcode::SUB;
  return true;
}

bool RISCVInstructionSelect::selectMul(MachineInstruction& inst) {
  // 选择 MUL 或 MULW
  // 这里简化处理，根据操作数大小选择
  inst.opcode = RISCVOpcode::MUL;
  return true;
}

bool RISCVInstructionSelect::selectDiv(MachineInstruction& inst) {
  // 选择 DIV 或 DIVW
  inst.opcode = RISCVOpcode::DIV;
  return true;
}

bool RISCVInstructionSelect::selectLoad(MachineInstruction& inst) {
  // G_LOAD 格式: G_LOAD dest_reg, addr_operand
  if (inst.operands.size() < 2) {
    return false;
  }
  
  MachineOperand dest_op = inst.operands[0];
  MachineOperand addr_op = inst.operands[1];
  
  // 检查地址操作数是否是全局变量
  if (addr_op.type == MachineOperand::GLOBAL) {
    // 对于全局变量，直接设置为LW指令，代码生成器会处理全局变量地址
    inst.opcode = RISCVOpcode::LW;
    // 保持操作数不变，让代码生成器处理全局变量
    return true;
  }
  
  // 对于其他类型的地址（寄存器），设置为标准的LW指令
  inst.opcode = RISCVOpcode::LW;
  
  // 如果地址是寄存器，转换为 lw dest, 0(addr_reg) 格式
  if (addr_op.isReg()) {
    inst.operands.clear();
    inst.operands.push_back(dest_op);                                  // 目标寄存器
    inst.operands.push_back(MachineOperand(static_cast<int64_t>(0)));  // 偏移为0
    inst.operands.push_back(addr_op);                                  // 基址寄存器
  }
  
  return true;
}

bool RISCVInstructionSelect::selectStore(MachineInstruction& inst) {
  // G_STORE 格式: G_STORE value, ptr
  // RISC-V SW 格式: SW src_reg, offset(base_reg)
  
  if (inst.operands.size() < 2) {
    return false;
  }
  
  MachineOperand value_op = inst.operands[0];
  MachineOperand ptr_op = inst.operands[1];
  
  // 设置为SW指令
  inst.opcode = RISCVOpcode::SW;
  
  // 重新组织操作数为 SW src_reg, offset(base_reg) 格式
  inst.operands.clear();
  inst.operands.push_back(value_op);     // 源寄存器/立即数
  inst.operands.push_back(MachineOperand(static_cast<int64_t>(0))); // 偏移量为0
  inst.operands.push_back(ptr_op);       // 基址寄存器
  
  return true;
}

bool RISCVInstructionSelect::selectCall(MachineInstruction& inst) {
  // 处理函数调用：JAL ra, function_name
  inst.opcode = RISCVOpcode::JAL;
  
  // JAL指令格式：jal ra, function_name
  // 我们需要重新组织操作数：[return_reg(optional), function_name, args...]
  // 最终格式应该是：[ra, function_name]
  
  if (inst.operands.size() >= 2) {
    // 找到函数名（应该是GLOBAL类型的操作数）
    std::string function_name;
    std::vector<MachineOperand> new_operands;
    
    // ra寄存器
    MachineRegister* ra_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 1); // x1 = ra
    new_operands.push_back(MachineOperand(ra_reg));
    
    // 查找函数名
    for (const auto& operand : inst.operands) {
      if (operand.type == MachineOperand::GLOBAL) {
        new_operands.push_back(operand); // 添加函数名
        break;
      }
    }
    
    // 重新设置操作数为只包含ra和函数名
    inst.operands = new_operands;
    
    // 参数将由调用约定处理器在其他地方处理（应该在调用前移动到a0-a7）
  }
  
  return true;
}

bool RISCVInstructionSelect::selectRet(MachineInstruction& inst) {
  // 函数返回：返回值处理已在translateRet阶段完成
  // 这里只需要生成简单的ret指令
  
  // 设置返回指令：使用ret伪指令 (等价于 jalr x0, x1, 0)
  inst.opcode = RISCVOpcode::JALR;
  
  // 清除所有操作数并设置正确的返回指令格式
  inst.operands.clear();
  
  // jalr x0, ra, 0 (ret伪指令的展开)
  MachineRegister* zero_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 0); // x0
  MachineRegister* ra_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 1);   // x1 = ra
  
  inst.operands.push_back(MachineOperand(zero_reg));  // 目标寄存器
  inst.operands.push_back(MachineOperand(ra_reg));    // 基址寄存器
  inst.operands.push_back(MachineOperand(static_cast<int64_t>(0))); // 偏移
  
  return true;
}

bool RISCVInstructionSelect::selectCmp(MachineInstruction& inst) {
  // G_ICMP/G_FCMP result, src1, src2, condition [, type] -> RISC-V比较指令
  if (inst.operands.size() < 4) return false;
  
  // 获取比较条件
  if (!inst.operands[3].isImm()) return false;
  int condition = static_cast<int>(inst.operands[3].imm);
  
  // 检查是否是浮点比较
  bool is_float_cmp = (inst.opcode == RISCVOpcode::G_FCMP);
  
  if (is_float_cmp) {
    // 浮点比较处理
    return selectFloatCmp(inst, static_cast<FcmpCond>(condition));
  } else {
    // 整数比较处理
    return selectIntCmp(inst, static_cast<IcmpCond>(condition));
  }
}

bool RISCVInstructionSelect::selectIntCmp(MachineInstruction& inst, IcmpCond condition) {
  // 整数比较指令选择
  // G_ICMP result, src1, src2, condition -> RISC-V比较指令
  
  MachineOperand result_op = inst.operands[0];
  MachineOperand src1_op = inst.operands[1];
  MachineOperand src2_op = inst.operands[2];
  
  // 根据IcmpCond选择RISC-V指令
  switch (condition) {
    case eq:  // 相等：a == b
      // 使用 xor + seqz 序列，但简化为 slt
      // TODO: 实现精确的相等比较
      inst.opcode = RISCVOpcode::SLT;
      break;
      
    case ne:  // 不等：a != b
      // 使用 xor + snez 序列，但简化为 slt
      // TODO: 实现精确的不等比较
      inst.opcode = RISCVOpcode::SLT;
      break;
      
    case slt: // 有符号小于：a < b
      inst.opcode = RISCVOpcode::SLT;
      break;
      
    case sle: // 有符号小于等于：a <= b -> !(a > b) -> !(b < a)
      inst.opcode = RISCVOpcode::SLT;
      // 交换操作数，然后需要取反结果
      std::swap(src1_op, src2_op);
      break;
      
    case sgt: // 有符号大于：a > b -> b < a
      inst.opcode = RISCVOpcode::SLT;
      // 交换操作数
      std::swap(src1_op, src2_op);
      break;
      
    case sge: // 有符号大于等于：a >= b -> !(a < b)
      inst.opcode = RISCVOpcode::SLT;
      // 需要取反结果
      break;
      
    case ult: // 无符号小于：a < b
      inst.opcode = RISCVOpcode::SLTU;
      break;
      
    case ule: // 无符号小于等于：a <= b -> !(a > b) -> !(b < a)
      inst.opcode = RISCVOpcode::SLTU;
      std::swap(src1_op, src2_op);
      break;
      
    case ugt: // 无符号大于：a > b -> b < a
      inst.opcode = RISCVOpcode::SLTU;
      std::swap(src1_op, src2_op);
      break;
      
    case uge: // 无符号大于等于：a >= b -> !(a < b)
      inst.opcode = RISCVOpcode::SLTU;
      break;
      
    default:
      // 未知条件，使用默认的有符号小于
      inst.opcode = RISCVOpcode::SLT;
      break;
  }
  
  // 重新设置操作数
  inst.operands.clear();
  inst.operands.push_back(result_op);
  inst.operands.push_back(src1_op);
  inst.operands.push_back(src2_op);
  
  return true;
}

bool RISCVInstructionSelect::selectFloatCmp(MachineInstruction& inst, FcmpCond condition) {
  // 浮点比较指令选择
  // G_FCMP result, src1, src2, condition -> RISC-V浮点比较指令
  
  MachineOperand result_op = inst.operands[0];
  MachineOperand src1_op = inst.operands[1];
  MachineOperand src2_op = inst.operands[2];
  
  // 根据FcmpCond选择RISC-V浮点比较指令
  switch (condition) {
    case OEQ:  // 有序相等
      inst.opcode = RISCVOpcode::FEQ_S;
      break;
      
    case OLT:  // 有序小于
      inst.opcode = RISCVOpcode::FLT_S;
      break;
      
    case OLE:  // 有序小于等于
      inst.opcode = RISCVOpcode::FLE_S;
      break;
      
    case OGT:  // 有序大于：a > b -> b < a
      inst.opcode = RISCVOpcode::FLT_S;
      std::swap(src1_op, src2_op);
      break;
      
    case OGE:  // 有序大于等于：a >= b -> b <= a
      inst.opcode = RISCVOpcode::FLE_S;
      std::swap(src1_op, src2_op);
      break;
      
    case ONE:  // 有序不等
      // 需要使用 !feq 逻辑，暂时用 flt
      inst.opcode = RISCVOpcode::FLT_S;
      break;
      
    case UEQ:  // 无序相等
    case ULT:  // 无序小于
    case ULE:  // 无序小于等于
    case UGT:  // 无序大于
    case UGE:  // 无序大于等于
    case UNE:  // 无序不等
    case ORD:  // 有序
    case UNO:  // 无序
    case FALSE: // 总是假
    case TRUE:  // 总是真
    default:
      // 复杂的浮点条件，暂时使用基本的小于比较
      inst.opcode = RISCVOpcode::FLT_S;
      break;
  }
  
  // 重新设置操作数
  inst.operands.clear();
  inst.operands.push_back(result_op);
  inst.operands.push_back(src1_op);
  inst.operands.push_back(src2_op);
  
  return true;
}

bool RISCVInstructionSelect::selectConstant(MachineInstruction& inst) {
  // G_CONSTANT 指令格式: G_CONSTANT dest_reg, immediate_value
  if (inst.operands.size() < 2) return false;
  
  // 检查立即数是否是12位范围内（可以用ADDI实现）
  if (inst.operands[1].isImm()) {
    int64_t imm_value = inst.operands[1].imm;
    if (is12BitImm(imm_value)) {
      // 使用 ADDI rd, x0, imm (等价于 LI rd, imm)
      inst.opcode = RISCVOpcode::ADDI;
      // 插入零寄存器作为源操作数
      inst.operands.insert(inst.operands.begin() + 1, MachineOperand(static_cast<int64_t>(0)));
      return true;
    }
  }
  
  // 对于较大的立即数，使用LI伪指令
  inst.opcode = RISCVOpcode::LI;
  return true;
}

bool RISCVInstructionSelect::selectCopy(MachineInstruction& inst) {
  // G_COPY 转换为 MV 伪指令 (等价于 addi rd, rs, 0)
  if (inst.operands.size() >= 2) {
    // 检查源和目标是否是同一个寄存器
    if (inst.operands[0].isReg() && inst.operands[1].isReg()) {
      MachineRegister* dst = inst.operands[0].reg;
      MachineRegister* src = inst.operands[1].reg;
      
      // 如果源和目标相同，可以删除这个指令（优化）
      if (dst->reg_num == src->reg_num && dst->type == src->type) {
        // 将指令转换为NOP或者标记为删除
        inst.opcode = RISCVOpcode::NOP;
        inst.operands.clear();
        return true;
      }
    }
    
    // 转换为MV指令
    inst.opcode = RISCVOpcode::MV;
    return true;
  }
  
  return false;
}

bool RISCVInstructionSelect::selectStackAddr(MachineInstruction& inst) {
  // G_STACK_ADDR %dest, offset -> addi %dest, sp, offset
  if (inst.operands.size() >= 2) {
    // 转换为ADDI指令
    inst.opcode = RISCVOpcode::ADDI;
    
    // 插入栈指针寄存器作为源操作数
    // 在RISC-V中，栈指针是x2 (sp)
    MachineRegister* sp_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 2); // x2 = sp
    inst.operands.insert(inst.operands.begin() + 1, MachineOperand(sp_reg));
    
    return true;
  }
  
  return false;
}

bool RISCVInstructionSelect::selectBranch(MachineInstruction& inst) {
  // G_BR condition, true_label, false_label -> 条件分支
  // G_BR label -> 无条件分支
  
  if (inst.operands.size() == 1) {
    // 无条件分支：G_BR label -> JAL x0, label (伪指令 j label)
    inst.opcode = RISCVOpcode::JAL;
    
    // 插入x0作为目标寄存器（对于无条件跳转）
    MachineRegister* zero_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 0); // x0
    inst.operands.insert(inst.operands.begin(), MachineOperand(zero_reg));
    
    return true;
  } else if (inst.operands.size() == 3) {
    // 条件分支：G_BR condition, true_label, false_label
    // 转换为：BNE condition, x0, true_label (如果condition != 0，跳转到true_label)
    
    inst.opcode = RISCVOpcode::BNE;
    
    // 重新组织操作数：BNE rs1, rs2, offset
    // 我们需要：BNE condition_reg, x0, true_label
    MachineRegister* zero_reg = new MachineRegister(MRegType::PHYSICAL, RISCVRegClass::GPR, 0); // x0
    
    // 操作数变为：[condition_reg, x0, true_label]
    auto condition_op = inst.operands[0];  // 保存条件
    auto true_label_op = inst.operands[1]; // 保存真分支标签
    auto false_label_op = inst.operands[2]; // 保存假分支标签
    
    inst.operands.clear();
    inst.operands.push_back(condition_op);                    // 条件寄存器
    inst.operands.push_back(MachineOperand(zero_reg));        // x0
    inst.operands.push_back(true_label_op);                   // 真分支标签
    
    // 处理假分支：如果条件为假，需要跳转到false_label
    // 策略：当前BNE处理true分支，需要在当前基本块后插入无条件跳转到false_label
    // 但这需要修改基本块结构，暂时使用反向逻辑：使用BEQ跳转到false_label
    
    // 改用BEQ：如果条件为0（假），跳转到false_label
    inst.opcode = RISCVOpcode::BEQ;
    inst.operands[2] = false_label_op;  // 改为跳转到false_label
    
    return true;
  }
  
  return false;
}

bool RISCVInstructionSelect::selectGep(MachineInstruction& inst) {
  // 新格式：G_GEP result, base, index_count, idx1, idx2, ..., element_size, dim_count, dim1, dim2, ...
  // 转换为RISC-V地址计算指令序列
  
  if (inst.operands.size() < 5) return false; // 至少需要 result, base, index_count, idx1, element_size
  
  MachineOperand result_op = inst.operands[0];   // 结果寄存器
  MachineOperand base_op = inst.operands[1];     // 基地址
  
  // 检查索引数量
  if (!inst.operands[2].isImm()) return false;
  int index_count = inst.operands[2].imm;
  
  if (index_count < 1) return false; // 至少需要1个索引
  
  // 解析索引
  std::vector<MachineOperand> indexes;
  for (int i = 0; i < index_count; ++i) {
    if (static_cast<size_t>(3 + i) >= inst.operands.size()) return false;
    indexes.push_back(inst.operands[3 + i]);
  }
  
  // 获取元素大小
  int element_size_idx = 3 + index_count;
  if (static_cast<size_t>(element_size_idx) >= inst.operands.size()) return false;
  MachineOperand element_size = inst.operands[element_size_idx];
  
  // 获取维度信息
  int dim_count_idx = element_size_idx + 1;
  int dim_count = 0;
  std::vector<int64_t> dims;
  
  if (static_cast<size_t>(dim_count_idx) < inst.operands.size() && inst.operands[dim_count_idx].isImm()) {
    dim_count = inst.operands[dim_count_idx].imm;
    
    // 获取所有维度大小
    for (int i = 0; i < dim_count; ++i) {
      int dim_idx = dim_count_idx + 1 + i;
      if (static_cast<size_t>(dim_idx) < inst.operands.size() && inst.operands[dim_idx].isImm()) {
        dims.push_back(inst.operands[dim_idx].imm);
      }
    }
  }
  
  // 计算多维数组偏移量
  int64_t total_offset = 0;
  if (calculateMultiDimOffset(indexes, dims, element_size, total_offset)) {
    // 成功计算偏移量，使用ADDI指令
    inst.opcode = RISCVOpcode::ADDI;
    inst.operands.clear();
    inst.operands.push_back(result_op);
    inst.operands.push_back(base_op);
    inst.operands.push_back(MachineOperand(total_offset));
  } else {
    // 动态索引或复杂情况，简化处理
    inst.opcode = RISCVOpcode::ADD;
    inst.operands.clear();
    inst.operands.push_back(result_op);
    inst.operands.push_back(base_op);
    // 简化：只使用第一个索引
    if (!indexes.empty()) {
      inst.operands.push_back(indexes[0]);
    } else {
      inst.operands.push_back(MachineOperand(static_cast<int64_t>(0)));
    }
  }
  
  return true;
}

bool RISCVInstructionSelect::calculateMultiDimOffset(const std::vector<MachineOperand>& indexes, 
                                                      const std::vector<int64_t>& dims,
                                                      const MachineOperand& element_size,
                                                      int64_t& total_offset) {
  // 检查是否所有索引都是常数
  for (const auto& idx : indexes) {
    if (!idx.isImm()) {
      return false;  // 有动态索引，无法静态计算
    }
  }
  
  if (!element_size.isImm()) {
    return false;  // 元素大小不是常数
  }
  
  total_offset = 0;
  int64_t elem_size = element_size.imm;
  
  if (indexes.size() == 2) {
    // 一维数组：base + type_index + array_index * element_size
    // 第一个索引通常是类型索引（0），第二个是真正的数组索引
    total_offset = indexes[1].imm * elem_size;
    
  } else if (indexes.size() == 3 && dims.size() >= 2) {
    // 二维数组：base + type_index + row_index * col_size * elem_size + col_index * elem_size
    int64_t row_idx = indexes[1].imm;
    int64_t col_idx = indexes[2].imm; 
    int64_t col_size = dims[1]; // 第二个维度是列数 (dims = [rows, cols])
    
    total_offset = row_idx * col_size * elem_size + col_idx * elem_size;
    
  } else if (indexes.size() == 4 && dims.size() >= 3) {
    // 三维数组：base + type_index + dim1*dim2*dim3*elem_size + dim2*dim3*elem_size + dim3*elem_size
    int64_t dim1_idx = indexes[1].imm;
    int64_t dim2_idx = indexes[2].imm;
    int64_t dim3_idx = indexes[3].imm;
    int64_t dim2_size = dims[1]; // 第二维大小 (dims = [dim1, dim2, dim3])
    int64_t dim3_size = dims[2]; // 第三维大小
    
    total_offset = dim1_idx * dim2_size * dim3_size * elem_size + 
                   dim2_idx * dim3_size * elem_size + 
                   dim3_idx * elem_size;
    
  } else {
    // 其他情况暂不支持
    return false;
  }
  
  return true;
}

bool RISCVInstructionSelect::selectAnd(MachineInstruction& inst) {
  // G_AND -> AND (寄存器) 或 ANDI (立即数)
  if (inst.operands.size() >= 3) {
    // 检查第二个操作数是否是立即数
    if (inst.operands[2].type == MachineOperand::IMM) {
      inst.opcode = RISCVOpcode::ANDI;
    } else {
      inst.opcode = RISCVOpcode::AND;
    }
    return true;
  }
  return false;
}

bool RISCVInstructionSelect::selectOr(MachineInstruction& inst) {
  // G_OR -> OR (寄存器) 或 ORI (立即数)
  if (inst.operands.size() >= 3) {
    // 检查第二个操作数是否是立即数
    if (inst.operands[2].type == MachineOperand::IMM) {
      inst.opcode = RISCVOpcode::ORI;
    } else {
      inst.opcode = RISCVOpcode::OR;
    }
    return true;
  }
  return false;
}

bool RISCVInstructionSelect::selectXor(MachineInstruction& inst) {
  // G_XOR -> XOR (寄存器) 或 XORI (立即数)
  if (inst.operands.size() >= 3) {
    // 检查第二个操作数是否是立即数
    if (inst.operands[2].type == MachineOperand::IMM) {
      inst.opcode = RISCVOpcode::XORI;
    } else {
      inst.opcode = RISCVOpcode::XOR;
    }
    return true;
  }
  return false;
}

bool RISCVInstructionSelect::selectShl(MachineInstruction& inst) {
  // G_SHL -> SLL (寄存器) 或 SLLI (立即数)
  if (inst.operands.size() >= 3) {
    // 检查第二个操作数是否是立即数
    if (inst.operands[2].type == MachineOperand::IMM) {
      inst.opcode = RISCVOpcode::SLLI;
    } else {
      inst.opcode = RISCVOpcode::SLL;
    }
    return true;
  }
  return false;
}

bool RISCVInstructionSelect::selectShr(MachineInstruction& inst) {
  // G_SHR -> SRL (寄存器) 或 SRLI (立即数)
  if (inst.operands.size() >= 3) {
    // 检查第二个操作数是否是立即数
    if (inst.operands[2].type == MachineOperand::IMM) {
      inst.opcode = RISCVOpcode::SRLI;
    } else {
      inst.opcode = RISCVOpcode::SRL;
    }
    return true;
  }
  return false;
}

bool RISCVInstructionSelect::selectFadd(MachineInstruction& inst) {
  // G_FADD -> FADD.S
  inst.opcode = RISCVOpcode::FADD_S;
  return true;
}

bool RISCVInstructionSelect::selectFsub(MachineInstruction& inst) {
  // G_FSUB -> FSUB.S
  inst.opcode = RISCVOpcode::FSUB_S;
  return true;
}

bool RISCVInstructionSelect::selectFmul(MachineInstruction& inst) {
  // G_FMUL -> FMUL.S
  inst.opcode = RISCVOpcode::FMUL_S;
  return true;
}

bool RISCVInstructionSelect::selectFdiv(MachineInstruction& inst) {
  // G_FDIV -> FDIV.S
  inst.opcode = RISCVOpcode::FDIV_S;
  return true;
}

bool RISCVInstructionSelect::canUseImmediate(int64_t value, RISCVOpcode opcode) const {
  switch (opcode) {
    case RISCVOpcode::ADDI:
    case RISCVOpcode::ANDI:
    case RISCVOpcode::ORI:
    case RISCVOpcode::XORI:
      return is12BitImm(value);
    case RISCVOpcode::SLLI:
    case RISCVOpcode::SRLI:
    case RISCVOpcode::SRAI:
      return value >= 0 && value < 64; // 移位量
    default:
      return false;
  }
}

bool RISCVInstructionSelect::is12BitImm(int64_t value) const {
  return value >= -2048 && value <= 2047;
}

bool RISCVInstructionSelect::is20BitImm(int64_t value) const {
  return value >= -524288 && value <= 524287;
}

bool RISCVInstructionSelect::selectAddressingMode(MachineOperand& addr, 
                                                 MachineOperand& base, 
                                                 MachineOperand& offset) {
  // RISC-V 使用基址+偏移寻址模式
  // 这里简化实现
  return true;
}

// ===--------------------------------------------------------------------=== //
// RISCVPhysicalRegisters 实现
// ===--------------------------------------------------------------------=== //

std::string RISCVPhysicalRegisters::getGPRName(int reg_num) {
  static const std::string gpr_names[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
  };
  
  if (reg_num >= 0 && reg_num < 32) {
    return gpr_names[reg_num];
  }
  return "unknown";
}

std::string RISCVPhysicalRegisters::getFPRName(int reg_num) {
  static const std::string fpr_names[] = {
    "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7",
    "fs0", "fs1", "fa0", "fa1", "fa2", "fa3", "fa4", "fa5",
    "fa6", "fa7", "fs2", "fs3", "fs4", "fs5", "fs6", "fs7",
    "fs8", "fs9", "fs10", "fs11", "ft8", "ft9", "ft10", "ft11"
  };
  
  if (reg_num >= 0 && reg_num < 32) {
    return fpr_names[reg_num];
  }
  return "unknown";
}

bool RISCVPhysicalRegisters::isCallerSaved(int reg_num) {
  // 临时寄存器和参数寄存器是调用者保存
  return (reg_num >= 5 && reg_num <= 7) ||   // t0-t2
         (reg_num >= 10 && reg_num <= 17) ||  // a0-a7
         (reg_num >= 28 && reg_num <= 31);    // t3-t6
}

bool RISCVPhysicalRegisters::isCalleeSaved(int reg_num) {
  // 保存寄存器是被调用者保存
  return (reg_num >= 8 && reg_num <= 9) ||   // s0-s1
         (reg_num >= 18 && reg_num <= 27);    // s2-s11
}

bool RISCVPhysicalRegisters::isArgumentReg(int reg_num) {
  // a0-a7 是参数寄存器
  return reg_num >= 10 && reg_num <= 17;
}

bool RISCVPhysicalRegisters::isReturnReg(int reg_num) {
  // a0-a1 是返回值寄存器
  return reg_num == 10 || reg_num == 11;
}

// ===--------------------------------------------------------------------=== //
// RISCVGlobalISel 主控制器实现
// ===--------------------------------------------------------------------=== //

bool RISCVGlobalISel::runGlobalISel(const LLVMIR& llvm_ir, MachineModule& mir_module) {
  std::cout << "开始 GlobalISel 指令选择..." << std::endl;
  
  // 阶段1: IR翻译
  if (!runIRTranslation(llvm_ir, mir_module)) {
    std::cerr << "IR翻译失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "IRTranslation");
  
  // 阶段2: 合法化
  if (!runLegalizer(mir_module)) {
    std::cerr << "合法化失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "Legalizer");
  
  // 阶段3: 寄存器组选择
  if (!runRegBankSelect(mir_module)) {
    std::cerr << "寄存器组选择失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "RegBankSelect");
  
  // 阶段4: 指令选择
  if (!runInstructionSelect(mir_module)) {
    std::cerr << "指令选择失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "InstructionSelect");
  
  // 阶段5: 寄存器分配
  if (!runRegisterAllocation(mir_module)) {
    std::cerr << "寄存器分配失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "RegisterAllocation");
  
  // 验证结果
  if (!verifyMIR(mir_module)) {
    std::cerr << "MIR验证失败!" << std::endl;
    return false;
  }
  
  std::cout << "GlobalISel 指令选择完成!" << std::endl;
  return true;
}

bool RISCVGlobalISel::runGlobalISelToInstructionSelect(const LLVMIR& llvm_ir, MachineModule& mir_module) {
  std::cout << "开始 GlobalISel 指令选择（到InstructionSelect阶段）..." << std::endl;
  
  // 阶段1: IR翻译
  if (!runIRTranslation(llvm_ir, mir_module)) {
    std::cerr << "IR翻译失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "IRTranslation");
  
  // 阶段2: 合法化
  if (!runLegalizer(mir_module)) {
    std::cerr << "合法化失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "Legalizer");
  
  // 阶段3: 寄存器组选择
  if (!runRegBankSelect(mir_module)) {
    std::cerr << "寄存器组选择失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "RegBankSelect");
  
  // 阶段4: 指令选择
  if (!runInstructionSelect(mir_module)) {
    std::cerr << "指令选择失败!" << std::endl;
    return false;
  }
  // dumpMIR(mir_module, "InstructionSelect");
  
  std::cout << "GlobalISel 指令选择（到InstructionSelect）完成!" << std::endl;
  return true;
}

bool RISCVGlobalISel::runIRTranslation(const LLVMIR& llvm_ir, MachineModule& mir_module) {
  return translator.translateModule(llvm_ir, mir_module);
}

bool RISCVGlobalISel::runLegalizer(MachineModule& mir_module) {
  for (auto& func : mir_module.functions) {
    if (!legalizer.legalizeFunction(*func)) {
      return false;
    }
  }
  return true;
}

bool RISCVGlobalISel::runRegBankSelect(MachineModule& mir_module) {
  for (auto& func : mir_module.functions) {
    if (!reg_bank_selector.assignRegBanks(*func)) {
      return false;
    }
  }
  return true;
}

bool RISCVGlobalISel::runInstructionSelect(MachineModule& mir_module) {
  for (auto& func : mir_module.functions) {
    if (!instruction_selector.selectInstructions(*func)) {
      return false;
    }
  }
  return true;
}

bool RISCVGlobalISel::runRegisterAllocation(MachineModule& mir_module) {
  for (auto& func : mir_module.functions) {
    if (!register_allocator.allocateRegisters(*func)) {
      return false;
    }
  }
  return true;
}

void RISCVGlobalISel::dumpMIR(const MachineModule& mir_module, const std::string& stage) const {
  std::cout << "\n=== MIR after " << stage << " ===" << std::endl;
  if (stage == "RegisterAllocation") {
    // 寄存器分配后，显示汇编格式以便对比
    mir_module.print(std::cout);
  } else {
    // 其他阶段显示MIR格式
    mir_module.printMIR(std::cout);
  }
  std::cout << "=== End of " << stage << " ===" << std::endl;
}

bool RISCVGlobalISel::verifyMIR(const MachineModule& mir_module) const {
  // 基本验证：检查所有指令是否有效
  for (const auto& func : mir_module.functions) {
    for (const auto& block : func->basic_blocks) {
      for (const auto& inst : block->instructions) {
        // 检查指令操作码是否有效
        if (inst->opcode == RISCVOpcode::G_ADD && inst->operands.size() < 3) {
          return false;
        }
        // 添加更多验证逻辑...
      }
    }
  }
  return true;
} 