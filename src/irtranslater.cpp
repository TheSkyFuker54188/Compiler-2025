#include "../include/irtranslater.h"
#include "../include/llvm_instruction.h"
#include <algorithm>

void RiscvBlock::InsertInstruction(int pos,
                                   std::unique_ptr<RiscvInstruction> ins) {
  if (pos == 0)
    instruction_list.push_front(std::move(ins));
  else
    instruction_list.push_back(std::move(ins));
}

void RiscvBlock::print(std::ostream &s) {
  s << ".L" << block_id << ":\n";
  for (auto &inst : instruction_list)
    inst->PrintIR(s);
}

void Riscv::print(std::ostream &s) {
  // 输出全局变量定义
  s << ".data\n";
  for (auto &global : global_def)
    global->PrintIR(s);
  // 输出代码段
  s << ".text\n";
  // 输出函数
  for (auto &func_pair : function_block_map) {
    s << ".globl " << func_pair.first << "\n";
    s << func_pair.first << ":";
    s << "\n";

    // 输出函数的所有基本块
    for (auto &block_pair : func_pair.second)
      block_pair.second->print(s);
    s << "\n";
  }
}

void Translator::translate(const LLVMIR &llvmir) {
  translateGlobal(llvmir.global_def);
  translateFunctions(llvmir);
}

void Translator::translateGlobal(const std::vector<Instruction> &global_def) {
  for (const auto &ins : global_def) {
    if (ins->GetOpcode() == LLVMIROpcode::GLOBAL_VAR) {
      auto *global_var = dynamic_cast<GlobalVarDefineInstruction *>(ins);
      if (global_var) {
        auto riscv_global = std::make_unique<RiscvGlobalVarInstruction>(
            global_var->GetName(), getLLVMTypeString(global_var->GetType()));
        const auto &attr = global_var->GetAttr();
        riscv_global->init_vals = attr.IntInitVals;
        riscv_global->init_float_vals = attr.FloatInitVals;
        riscv.global_def.push_back(std::move(riscv_global));
      }
    } else if (ins->GetOpcode() == LLVMIROpcode::GLOBAL_STR) {
      auto *global_str = dynamic_cast<GlobalStringConstInstruction *>(ins);
      if (global_str) {
        auto riscv_global = std::make_unique<RiscvStringConstInstruction>(
            global_str->GetName(), "string");
      }
    }
  }
}

void Translator::translateFunctions(const LLVMIR &llvmir) {
  for (const auto &func_pair : llvmir.function_block_map)
    translateFunction(func_pair.first, func_pair.second);
}

void Translator::translateFunction(FuncDefInstruction func,
                                   const std::map<int, LLVMBlock> &blocks) {
  current_function = func->Func_name;
  // 初始化栈帧信息
  initFunctionStackFrame(current_function);
  // 为函数创建块映射
  riscv.function_block_map[current_function] =
      std::map<int, std::unique_ptr<RiscvBlock>>();
  // 第一步：分析函数，收集栈帧信息
  analyzeFunction(blocks);
  // 第二步：完成栈帧计算
  finalizeFunctionStackFrame();
  // 第三步：翻译每个基本块
  RiscvBlock *entry_block = nullptr;
  for (const auto &block_pair : blocks) {
    auto riscv_block = std::make_unique<RiscvBlock>(block_pair.first);
    RiscvBlock *block_ptr = riscv_block.get();
    // 记录入口块
    if (entry_block == nullptr)
      entry_block = block_ptr;
    riscv.function_block_map[current_function][block_pair.first] =
        std::move(riscv_block);
    translateBlock(block_pair.second, block_ptr);
  }

  if (entry_block) {
    // 设置入口块的栈帧大小信息
    entry_block->stack_size = current_stack_frame->total_frame_size;
    if (current_stack_frame->total_frame_size > 0)
      generateStackFrameProlog(entry_block);
  }
}

void Translator::analyzeFunction(const std::map<int, LLVMBlock> &blocks) {
  // 分析所有指令，收集栈帧信息
  for (const auto &block_pair : blocks) {
    for (const auto &inst : block_pair.second->Instruction_list) {
      analyzeInstruction(inst);
    }
  }
}

void Translator::analyzeInstruction(Instruction inst) {
  switch (inst->GetOpcode()) {
  case LLVMIROpcode::ALLOCA: {
    auto *alloca_inst = dynamic_cast<AllocaInstruction *>(inst);
    if (alloca_inst) {
      // 将BasicOperand转换为RegOperand以获取寄存器号
      auto *reg_operand = dynamic_cast<RegOperand *>(alloca_inst->GetResult());
      if (reg_operand) {
        if (!alloca_inst->GetDims().empty()) {
          addLocalArray(reg_operand->GetRegNo(), alloca_inst->GetType(),
                        alloca_inst->GetDims());
        } else {
          addLocalVariable(reg_operand->GetRegNo(), alloca_inst->GetType());
        }
      }
    }
    break;
  }
  case LLVMIROpcode::CALL: {
    auto *call_inst = dynamic_cast<CallInstruction *>(inst);
    if (call_inst) {
      updateCallArgsSize(call_inst->GetArgs().size());
    }
    break;
  }
  default:
    // 其他指令不影响栈帧大小
    break;
  }
}

void Translator::translateBlock(LLVMBlock block, RiscvBlock *riscv_block) {
  for (const auto &inst : block->Instruction_list)
    translateInstruction(inst, riscv_block);
}

void Translator::translateInstruction(Instruction inst,
                                      RiscvBlock *riscv_block) {
  switch (inst->GetOpcode()) {
  case LLVMIROpcode::ADD:
    translateAdd(inst, riscv_block);
    break;
  case LLVMIROpcode::SUB:
    translateSub(inst, riscv_block);
    break;
  case LLVMIROpcode::MUL_OP:
    translateMul(inst, riscv_block);
    break;
  case LLVMIROpcode::DIV_OP:
    translateDiv(inst, riscv_block);
    break;
  case LLVMIROpcode::FADD:
    translateFadd(inst, riscv_block);
    break;
  case LLVMIROpcode::FSUB:
    translateFsub(inst, riscv_block);
    break;
  case LLVMIROpcode::FMUL:
    translateFmul(inst, riscv_block);
    break;
  case LLVMIROpcode::FDIV:
    translateArithmetic(dynamic_cast<ArithmeticInstruction *>(inst),
                        riscv_block);
    break;
  case LLVMIROpcode::LOAD:
    translateLoad(dynamic_cast<LoadInstruction *>(inst), riscv_block);
    break;

  case LLVMIROpcode::STORE:
    translateStore(dynamic_cast<StoreInstruction *>(inst), riscv_block);
    break;

  case LLVMIROpcode::BR_COND:
  case LLVMIROpcode::BR_UNCOND:
    translateBranch(inst, riscv_block);
    break;

  case LLVMIROpcode::CALL:
    translateCall(dynamic_cast<CallInstruction *>(inst), riscv_block);
    break;

  case LLVMIROpcode::RET:
    translateReturn(dynamic_cast<RetInstruction *>(inst), riscv_block);
    break;

  case LLVMIROpcode::ICMP:
    translateIcmp(dynamic_cast<IcmpInstruction *>(inst), riscv_block);
    break;

  case LLVMIROpcode::FCMP:
    translateFcmp(dynamic_cast<FcmpInstruction *>(inst), riscv_block);
    break;

  default:
    break;
  }
}

void Translator::translateArithmetic(ArithmeticInstruction *inst,
                                     RiscvBlock *block) {
  if (!inst)
    return;

  RiscvOpcode riscv_op =
      llvmToRiscvOpcode(static_cast<LLVMIROpcode>(inst->GetOpcode()),
                        inst->GetType() == LLVMType::FLOAT32);

  auto rd = translateOperand(inst->GetResult());
  auto rs1 = translateOperand(inst->GetOp1());
  auto rs2 = translateOperand(inst->GetOp2());

  auto riscv_inst = std::make_unique<RiscvArithmeticInstruction>(
      riscv_op, std::move(rd), std::move(rs1), std::move(rs2));

  block->InsertInstruction(1, std::move(riscv_inst));
}

void Translator::translateLoad(LoadInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  RiscvOpcode op = (inst->GetType() == LLVMType::FLOAT32) ? RiscvOpcode::FLW
                                                          : RiscvOpcode::LW;

  auto rd = translateOperand(inst->GetResult());
  auto addr = translateOperand(inst->GetPointer());

  auto riscv_inst = std::make_unique<RiscvMemoryInstruction>(op, std::move(rd),
                                                             std::move(addr));

  block->InsertInstruction(1, std::move(riscv_inst));
}

void Translator::translateStore(StoreInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  RiscvOpcode op = (inst->GetType() == LLVMType::FLOAT32) ? RiscvOpcode::FSW
                                                          : RiscvOpcode::SW;

  auto rs = translateOperand(inst->GetValue());
  auto addr = translateOperand(inst->GetPointer());

  auto riscv_inst = std::make_unique<RiscvMemoryInstruction>(op, std::move(rs),
                                                             std::move(addr));

  block->InsertInstruction(1, std::move(riscv_inst));
}

void Translator::translateBranch(Instruction inst, RiscvBlock *block) {
  if (inst->GetOpcode() == LLVMIROpcode::BR_UNCOND) {
    auto *br_inst = dynamic_cast<BrUncondInstruction *>(inst);
    if (br_inst) {
      auto label_op = dynamic_cast<LabelOperand *>(br_inst->GetLabel());
      auto target = std::make_unique<RiscvLabelOperand>(
          ".L" + std::to_string(label_op->GetLabelNo()));
      auto riscv_inst = std::make_unique<RiscvJumpInstruction>(
          RiscvOpcode::JAL, getZeroReg(), std::move(target));
      block->InsertInstruction(1, std::move(riscv_inst));
    }
  } else if (inst->GetOpcode() == LLVMIROpcode::BR_COND) {
    auto *br_inst = dynamic_cast<BrCondInstruction *>(inst);
    if (br_inst) {
      auto cond = translateOperand(br_inst->GetCond());
      auto zero = getZeroReg(); // zero register
      auto true_label_op =
          dynamic_cast<LabelOperand *>(br_inst->GetTrueLabel());
      auto true_label = std::make_unique<RiscvLabelOperand>(
          ".L" + std::to_string(true_label_op->GetLabelNo()));

      auto riscv_inst = std::make_unique<RiscvBranchInstruction>(
          RiscvOpcode::BNE, std::move(cond), std::move(zero),
          std::move(true_label));
      block->InsertInstruction(1, std::move(riscv_inst));

      // 为false分支添加无条件跳转
      auto false_label_op =
          dynamic_cast<LabelOperand *>(br_inst->GetFalseLabel());
      auto false_label = std::make_unique<RiscvLabelOperand>(
          ".L" + std::to_string(false_label_op->GetLabelNo()));
      auto jump_inst = std::make_unique<RiscvJumpInstruction>(
          RiscvOpcode::JAL, getZeroReg(), std::move(false_label));
      block->InsertInstruction(1, std::move(jump_inst));
    }
  }
}

void Translator::translateCall(CallInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  auto call_inst = std::make_unique<RiscvCallInstruction>(inst->GetFuncName());

  // 简化实现：暂时不处理参数传递的细节
  block->InsertInstruction(1, std::move(call_inst));
}

void Translator::translateReturn(RetInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  if (inst->GetRetVal()) {
    // 将返回值移动到a0寄存器
    auto ret_val = translateOperand(inst->GetRetVal());
    auto a0 = getReturnValueReg(); // a0

    auto mv_inst = std::make_unique<RiscvPseudoInstruction>(
        RiscvOpcode::MV, std::move(a0), std::move(ret_val));
    block->InsertInstruction(1, std::move(mv_inst));
  }

  // 生成栈帧尾声代码
  if (current_stack_frame && current_stack_frame->total_frame_size > 0) {
    generateStackFrameEpilog(block);
  }

  auto ret_inst =
      std::make_unique<RiscvPseudoInstruction>(RiscvOpcode::RET, nullptr);
  block->InsertInstruction(1, std::move(ret_inst));
}

void Translator::translateIcmp(IcmpInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  RiscvOpcode op;
  switch (inst->GetCond()) {
  case IcmpCond::eq:
    op = RiscvOpcode::BEQ;
    break;
  case IcmpCond::ne:
    op = RiscvOpcode::BNE;
    break;
  case IcmpCond::slt:
    op = RiscvOpcode::SLT;
    break;
  case IcmpCond::sgt: // 通过交换操作数实现
  case IcmpCond::sge:
  case IcmpCond::sle:
  default:
    op = RiscvOpcode::SLT;
    break;
  }

  auto rd = translateOperand(inst->GetResult());
  auto rs1 = translateOperand(inst->GetOp1());
  auto rs2 = translateOperand(inst->GetOp2());

  auto riscv_inst = std::make_unique<RiscvArithmeticInstruction>(
      op, std::move(rd), std::move(rs1), std::move(rs2));

  block->InsertInstruction(1, std::move(riscv_inst));
}

void Translator::translateFcmp(FcmpInstruction *inst, RiscvBlock *block) {
  if (!inst)
    return;

  RiscvOpcode op;
  switch (inst->GetCond()) {
  case FcmpCond::OEQ:
    op = RiscvOpcode::FEQ_S;
    break;
  case FcmpCond::OLT:
    op = RiscvOpcode::FLT_S;
    break;
  case FcmpCond::OLE:
    op = RiscvOpcode::FLE_S;
    break;
  default:
    op = RiscvOpcode::FEQ_S;
    break;
  }

  auto rd = translateOperand(inst->GetResult());
  auto rs1 = translateOperand(inst->GetOp1());
  auto rs2 = translateOperand(inst->GetOp2());

  auto riscv_inst = std::make_unique<RiscvArithmeticInstruction>(
      op, std::move(rd), std::move(rs1), std::move(rs2));

  block->InsertInstruction(1, std::move(riscv_inst));
}

void Translator::translateAdd(Instruction inst, RiscvBlock *block) {
  auto *add_inst = dynamic_cast<ArithmeticInstruction *>(inst);
  if (!add_inst)
    return;
  if (add_inst->GetOp1()->isIMM() && add_inst->GetOp2()->isIMM()) {
    auto result = translateOperand(add_inst->GetResult());
    auto op1 = dynamic_cast<RiscvImmI32Operand *>(
        translateOperand(add_inst->GetOp1()).get());
    auto op2 = dynamic_cast<RiscvImmI32Operand *>(
        translateOperand(add_inst->GetOp2()).get());
    auto li_inst = std::make_unique<RiscvLiInstruction>(
        std::move(result), op1->GetIntImmVal() + op2->GetIntImmVal());
    block->InsertInstruction(1, std::move(li_inst));
  } else if (add_inst->GetOp2()->isIMM()) {
    // 如果第二个操作数是立即数，使用ADDI指令
    auto result = translateOperand(add_inst->GetResult());
    auto rs1 = translateOperand(add_inst->GetOp1());
    auto imm = dynamic_cast<RiscvImmI32Operand *>(
        translateOperand(add_inst->GetOp2()).get());
    auto addi_inst = std::make_unique<RiscvAddiInstruction>(
        std::move(result), std::move(rs1), imm);
    block->InsertInstruction(1, std::move(addi_inst));
  } else {
    // 否则使用ADD指令
    auto result = translateOperand(add_inst->GetResult());
    auto rs1 = translateOperand(add_inst->GetOp1());
    auto rs2 = translateOperand(add_inst->GetOp2());
    auto add_inst = std::make_unique<RiscvAddInstruction>(
        std::move(result), std::move(rs1), std::move(rs2));
    block->InsertInstruction(1, std::move(add_inst));
  }
}

// 物理寄存器创建辅助方法
std::unique_ptr<RiscvRegOperand>
Translator::createPhysicalReg(int physical_reg_no) {
  return std::make_unique<RiscvRegOperand>(
      -physical_reg_no); // 负数表示物理寄存器
}

std::unique_ptr<RiscvRegOperand>
Translator::createVirtualReg(int virtual_reg_no) {
  return std::make_unique<RiscvRegOperand>(
      virtual_reg_no); // 正数表示虚拟寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getZeroReg() {
  return createPhysicalReg(0); // zero寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getReturnAddressReg() {
  return createPhysicalReg(1); // ra寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getStackPointerReg() {
  return createPhysicalReg(2); // sp寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getReturnValueReg() {
  return createPhysicalReg(10); // a0寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getFramePointerReg() {
  return createPhysicalReg(8); // s0寄存器
}

std::unique_ptr<RiscvRegOperand> Translator::getArgReg(int arg_index) {
  if (arg_index >= 0 && arg_index <= 7) {
    return createPhysicalReg(10 + arg_index); // a0-a7寄存器
  }
  return getZeroReg(); // 超出范围返回zero寄存器
}

std::unique_ptr<RiscvOperand> Translator::translateOperand(Operand op) {
  if (auto *reg_op = dynamic_cast<RegOperand *>(op)) {
    // 保持虚拟寄存器编号不变
    return createVirtualReg(reg_op->GetRegNo());
  } else if (auto *imm_i32 = dynamic_cast<ImmI32Operand *>(op)) {
    return std::make_unique<RiscvImmI32Operand>(imm_i32->GetIntImmVal());
  } else if (auto *imm_f32 = dynamic_cast<ImmF32Operand *>(op)) {
    return std::make_unique<RiscvImmF32Operand>(imm_f32->GetFloatVal());
  } else if (auto *global_op = dynamic_cast<GlobalOperand *>(op)) {
    return std::make_unique<RiscvGlobalOperand>(global_op->GetName());
  } else if (auto *label_op = dynamic_cast<LabelOperand *>(op)) {
    return std::make_unique<RiscvLabelOperand>(
        ".L" + std::to_string(label_op->GetLabelNo()));
  }

  // 默认返回zero寄存器
  return getZeroReg();
}

RiscvOpcode Translator::llvmToRiscvOpcode(LLVMIROpcode llvm_op, bool is_float) {
  switch (llvm_op) {
  case LLVMIROpcode::ADD:
    return is_float ? RiscvOpcode::FADD_S : RiscvOpcode::ADD;
  case LLVMIROpcode::SUB:
    return is_float ? RiscvOpcode::FSUB_S : RiscvOpcode::SUB;
  case LLVMIROpcode::MUL_OP:
    return is_float ? RiscvOpcode::FMUL_S : RiscvOpcode::MUL;
  case LLVMIROpcode::DIV_OP:
    return is_float ? RiscvOpcode::FDIV_S : RiscvOpcode::DIV;
  case LLVMIROpcode::BITAND:
    return RiscvOpcode::AND;
  case LLVMIROpcode::BITOR:
    return RiscvOpcode::OR;
  case LLVMIROpcode::BITXOR:
    return RiscvOpcode::XOR;
  default:
    return RiscvOpcode::ADD; // 默认
  }
}

std::string Translator::getLLVMTypeString(LLVMType type) {
  switch (type) {
  case LLVMType::I32:
    return "i32";
  case LLVMType::FLOAT32:
    return "float";
  case LLVMType::PTR:
    return "ptr";
  case LLVMType::VOID_TYPE:
    return "void";
  default:
    return "unknown";
  }
}

// 栈帧管理方法实现

void Translator::initFunctionStackFrame(const std::string &func_name) {
  function_stack_frames[func_name] = StackFrameInfo();
  current_stack_frame = &function_stack_frames[func_name];
}

int Translator::getTypeSize(LLVMType type) {
  switch (type) {
  case LLVMType::I32:
  case LLVMType::FLOAT32:
  case LLVMType::PTR:
    return 4; // RISC-V 32位架构，所有基本类型都是4字节
  case LLVMType::I1:
    return 1; // 布尔类型1字节
  case LLVMType::I64:
  case LLVMType::DOUBLE:
    return 8; // 64位类型
  default:
    return 4; // 默认4字节
  }
}

void Translator::addLocalVariable(int virtual_reg, LLVMType type) {
  if (!current_stack_frame)
    return;

  int var_size = getTypeSize(type);
  int offset = current_stack_frame->local_vars_size;

  // 变量按4字节对齐
  if (offset % 4 != 0)
    offset += 4 - (offset % 4);

  current_stack_frame->var_offsets[virtual_reg] = offset;
  current_stack_frame->local_vars_size = offset + var_size;
}

void Translator::addLocalArray(int virtual_reg, LLVMType type,
                               const std::vector<int> &dims) {
  if (!current_stack_frame)
    return;

  int element_size = getTypeSize(type);
  int total_elements = 1;
  for (int dim : dims)
    total_elements *= dim;

  int array_size = element_size * total_elements;
  int offset = current_stack_frame->local_vars_size;

  // 数组按8字节对齐
  if (offset % 8 != 0)
    offset += 8 - (offset % 8);

  current_stack_frame->var_offsets[virtual_reg] = offset;
  current_stack_frame->local_vars_size = offset + array_size;
}

void Translator::updateCallArgsSize(int num_args) {
  if (!current_stack_frame)
    return;

  // RISC-V调用约定：前8个参数通过寄存器传递(a0-a7)，其余通过栈传递
  if (num_args > 8) {
    int stack_args = num_args - 8;
    int args_size = stack_args * 4; // 每个参数4字节
    current_stack_frame->call_args_size =
        std::max(current_stack_frame->call_args_size, args_size);
  }
}

void Translator::finalizeFunctionStackFrame() {
  if (!current_stack_frame)
    return;

  current_stack_frame->calculateTotalSize();
}

void Translator::generateStackFrameProlog(RiscvBlock *entry_block) {
  if (!current_stack_frame || current_stack_frame->total_frame_size == 0)
    return;
  // 生成栈帧分配代码
  // addi sp, sp, -frame_size
  auto sp = getStackPointerReg();
  auto alloc_inst = std::make_unique<RiscvAddiInstruction>(
      sp->CopyOperand(), sp->CopyOperand(),
      -current_stack_frame->total_frame_size);
  entry_block->InsertInstruction(0, std::move(alloc_inst));

  auto s0 = getFramePointerReg();
  auto sp_copy = getStackPointerReg();
  auto addr = std::make_unique<RiscvPtrOperand>(
      current_stack_frame->total_frame_size - 8, std::move(sp_copy));
  auto save_fp =
      std::make_unique<RiscvSdInstruction>(std::move(s0), std::move(addr));
  entry_block->InsertInstruction(1, std::move(save_fp));

  auto s0_copy = getFramePointerReg();
  auto sp_copy2 = getStackPointerReg();
  auto save_s0_addr = std::make_unique<RiscvAddiInstruction>(
      s0_copy->CopyOperand(), sp_copy2->CopyOperand(),
      current_stack_frame->total_frame_size);
  entry_block->InsertInstruction(1, std::move(save_s0_addr));
}

void Translator::generateStackFrameEpilog(RiscvBlock *exit_block) {
  if (!current_stack_frame || current_stack_frame->total_frame_size == 0)
    return;

  // 如果保存了ra寄存器，需要恢复
  if (current_stack_frame->max_call_args > 0) {
    auto ra = getReturnAddressReg();
    auto sp_copy = getStackPointerReg();
    auto addr = std::make_unique<RiscvDramOperand>(
        current_stack_frame->total_frame_size - 4, std::move(sp_copy));

    auto restore_ra = std::make_unique<RiscvMemoryInstruction>(
        RiscvOpcode::LW, std::move(ra), std::move(addr));

    exit_block->InsertInstruction(1, std::move(restore_ra));
  }

  // 生成栈帧释放代码
  // addi sp, sp, frame_size
  auto sp = getStackPointerReg();

  auto dealloc_inst = std::make_unique<RiscvImmediateInstruction>(
      RiscvOpcode::ADDI, sp->CopyOperand(), sp->CopyOperand(),
      current_stack_frame->total_frame_size);

  exit_block->InsertInstruction(1, std::move(dealloc_inst));
}

int Translator::getLocalVariableOffset(int virtual_reg) {
  if (!current_stack_frame)
    return 0;

  auto it = current_stack_frame->var_offsets.find(virtual_reg);
  if (it != current_stack_frame->var_offsets.end()) {
    return it->second;
  }
  return 0;
}

const StackFrameInfo *
Translator::getFunctionStackFrame(const std::string &func_name) const {
  auto it = function_stack_frames.find(func_name);
  if (it != function_stack_frames.end()) {
    return &it->second;
  }
  return nullptr;
}

int Translator::getCurrentFrameSize() const {
  if (current_stack_frame) {
    return current_stack_frame->total_frame_size;
  }
  return 0;
}