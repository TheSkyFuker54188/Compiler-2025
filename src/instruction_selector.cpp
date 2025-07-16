#include "../include/instruction_selector.h"
#include <sstream>
#include <iomanip>

namespace riscv {

// ===================================================================
// 工具函数实现
// ===================================================================

std::string riscvRegisterName(RISCVRegister reg) {
    static const std::map<RISCVRegister, std::string> reg_names = {
        {RISCVRegister::ZERO, "zero"}, {RISCVRegister::RA, "ra"}, {RISCVRegister::SP, "sp"},
        {RISCVRegister::GP, "gp"}, {RISCVRegister::TP, "tp"},
        {RISCVRegister::T0, "t0"}, {RISCVRegister::T1, "t1"}, {RISCVRegister::T2, "t2"},
        {RISCVRegister::S0, "s0"}, {RISCVRegister::S1, "s1"},
        {RISCVRegister::A0, "a0"}, {RISCVRegister::A1, "a1"}, {RISCVRegister::A2, "a2"},
        {RISCVRegister::A3, "a3"}, {RISCVRegister::A4, "a4"}, {RISCVRegister::A5, "a5"},
        {RISCVRegister::A6, "a6"}, {RISCVRegister::A7, "a7"},
        {RISCVRegister::S2, "s2"}, {RISCVRegister::S3, "s3"}, {RISCVRegister::S4, "s4"},
        {RISCVRegister::S5, "s5"}, {RISCVRegister::S6, "s6"}, {RISCVRegister::S7, "s7"},
        {RISCVRegister::S8, "s8"}, {RISCVRegister::S9, "s9"}, {RISCVRegister::S10, "s10"},
        {RISCVRegister::S11, "s11"}, {RISCVRegister::T3, "t3"}, {RISCVRegister::T4, "t4"},
        {RISCVRegister::T5, "t5"}, {RISCVRegister::T6, "t6"},
        
        // 浮点寄存器
        {RISCVRegister::FT0, "ft0"}, {RISCVRegister::FT1, "ft1"}, {RISCVRegister::FT2, "ft2"},
        {RISCVRegister::FT3, "ft3"}, {RISCVRegister::FT4, "ft4"}, {RISCVRegister::FT5, "ft5"},
        {RISCVRegister::FT6, "ft6"}, {RISCVRegister::FT7, "ft7"},
        {RISCVRegister::FS0, "fs0"}, {RISCVRegister::FS1, "fs1"},
        {RISCVRegister::FA0, "fa0"}, {RISCVRegister::FA1, "fa1"}, {RISCVRegister::FA2, "fa2"},
        {RISCVRegister::FA3, "fa3"}, {RISCVRegister::FA4, "fa4"}, {RISCVRegister::FA5, "fa5"},
        {RISCVRegister::FA6, "fa6"}, {RISCVRegister::FA7, "fa7"},
        {RISCVRegister::FS2, "fs2"}, {RISCVRegister::FS3, "fs3"}, {RISCVRegister::FS4, "fs4"},
        {RISCVRegister::FS5, "fs5"}, {RISCVRegister::FS6, "fs6"}, {RISCVRegister::FS7, "fs7"},
        {RISCVRegister::FS8, "fs8"}, {RISCVRegister::FS9, "fs9"}, {RISCVRegister::FS10, "fs10"},
        {RISCVRegister::FS11, "fs11"}, {RISCVRegister::FT8, "ft8"}, {RISCVRegister::FT9, "ft9"},
        {RISCVRegister::FT10, "ft10"}, {RISCVRegister::FT11, "ft11"}
    };
    
    auto it = reg_names.find(reg);
    return (it != reg_names.end()) ? it->second : "unknown";
}

bool isIntegerType(LLVMType type) {
    return type == LLVMType::I32 || type == LLVMType::I1 || type == LLVMType::I8 || type == LLVMType::I64;
}

bool isFloatType(LLVMType type) {
    return type == LLVMType::FLOAT32 || type == LLVMType::DOUBLE;
}

std::string getTypeSize(LLVMType type) {
    switch (type) {
        case LLVMType::I32: return "4";
        case LLVMType::FLOAT32: return "4";
        case LLVMType::I64: return "8";
        case LLVMType::DOUBLE: return "8";
        case LLVMType::I8: return "1";
        case LLVMType::I1: return "1";
        case LLVMType::PTR: return "8";
        default: return "4";
    }
}

// ===================================================================
// 指令选择器实现
// ===================================================================

std::string InstructionSelector::getRegisterName(RISCVRegister reg) const {
    return riscvRegisterName(reg);
}

std::string InstructionSelector::getVirtualRegName(int llvm_reg) {
    auto it = llvm_to_virtual_.find(llvm_reg);
    if (it != llvm_to_virtual_.end()) {
        return vreg_manager_.getVirtualRegName(it->second);
    }
    
    // 创建新的虚拟寄存器映射
    int virtual_reg = vreg_manager_.allocateVirtualReg();
    llvm_to_virtual_[llvm_reg] = virtual_reg;
    return vreg_manager_.getVirtualRegName(virtual_reg);
}

std::string InstructionSelector::getOperandString(Operand op) {
    if (auto reg_op = dynamic_cast<RegOperand*>(op)) {
        return getVirtualRegName(reg_op->GetRegNo());
    } else if (auto imm_i32 = dynamic_cast<ImmI32Operand*>(op)) {
        return std::to_string(imm_i32->GetIntImmVal());
    } else if (auto imm_f32 = dynamic_cast<ImmF32Operand*>(op)) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6) << imm_f32->GetFloatVal();
        return oss.str();
    } else if (auto label_op = dynamic_cast<LabelOperand*>(op)) {
        return getLabelName(label_op->GetLabelNo());
    } else if (auto global_op = dynamic_cast<GlobalOperand*>(op)) {
        return global_op->GetName();
    }
    return "unknown";
}

std::string InstructionSelector::getLabelName(int label_id) {
    return ".L" + std::to_string(label_id);
}

void InstructionSelector::selectInstructions(const LLVMIR& ir) {
    emitHeader();
    emitLibraryDeclarations();
    
    // 处理全局变量
    for (const auto& global_inst : ir.global_def) {
        if (auto global_var = dynamic_cast<GlobalVarDefineInstruction*>(global_inst)) {
            translateGlobalVar(*global_var);
        } else if (auto global_str = dynamic_cast<GlobalStringConstInstruction*>(global_inst)) {
            translateGlobalString(*global_str);
        }
    }
    
    emitGlobalData();
    
    // 处理函数
    for (const auto& func_entry : ir.function_block_map) {
        processFunction(func_entry.first, func_entry.second);
    }
}

void InstructionSelector::emitHeader() {
    output_ << "# Generated RISC-V assembly\n";
    output_ << ".text\n";
    output_ << ".align 2\n\n";
}

void InstructionSelector::emitGlobalData() {
    if (!global_data_.empty()) {
        output_ << ".data\n";
        for (const auto& data : global_data_) {
            output_ << data << "\n";
        }
        output_ << "\n.text\n";
    }
}

void InstructionSelector::emitLibraryDeclarations() {
    // 常用的库函数声明
    output_ << "# Library function declarations\n";
    output_ << ".extern getint\n";
    output_ << ".extern putint\n";
    output_ << ".extern getfloat\n";
    output_ << ".extern putfloat\n";
    output_ << ".extern getarray\n";
    output_ << ".extern putarray\n";
    output_ << ".extern getfarray\n";
    output_ << ".extern putfarray\n";
    output_ << ".extern putch\n";
    output_ << ".extern getch\n";
    output_ << ".extern starttime\n";
    output_ << ".extern stoptime\n\n";
}

void InstructionSelector::processFunction(FuncDefInstruction func_def, 
                                        const std::map<int, LLVMBlock>& blocks) {
    // 重置状态
    vreg_manager_.reset();
    llvm_to_virtual_.clear();
    
    // 创建函数
    auto func = std::make_unique<RISCVFunction>(func_def->Func_name);
    current_function_ = func.get();
    
    // 处理函数序言
    processFunctionProlog(func_def->Func_name);
    
    // 处理所有基本块
    for (const auto& block_entry : blocks) {
        processBasicBlock(block_entry.second, block_entry.first);
    }
    
    // 处理函数尾声
    processFunctionEpilog();
    
    // 输出函数
    func->emit(output_);
}

void InstructionSelector::processFunctionProlog(const std::string& func_name) {
    current_block_ = current_function_->createBlock(func_name);
    
    // 函数序言：保存ra和设置栈帧
    current_block_->addInstruction(RISCVInstruction("addi", {"sp", "sp", "-16"}));
    current_block_->addInstruction(RISCVInstruction("sd", {"ra", "8(sp)"}));
    current_block_->addInstruction(RISCVInstruction("sd", {"s0", "0(sp)"}));
    current_block_->addInstruction(RISCVInstruction("addi", {"s0", "sp", "16"}));
}

void InstructionSelector::processFunctionEpilog() {
    // 这里可以添加函数尾声的通用处理
    // 具体的返回指令在translateReturn中处理
}

void InstructionSelector::processBasicBlock(LLVMBlock block, int block_id) {
    // 为基本块创建标签（除了函数入口块）
    if (block_id != 0) {
        current_block_ = current_function_->createBlock(getLabelName(block_id));
    }
    
    // 处理基本块中的所有指令
    for (const auto& inst : block->Instruction_list) {
        switch (inst->GetOpcode()) {
            case LOAD:
                if (auto load_inst = dynamic_cast<LoadInstruction*>(inst)) {
                    translateLoad(*load_inst);
                }
                break;
            case STORE:
                if (auto store_inst = dynamic_cast<StoreInstruction*>(inst)) {
                    translateStore(*store_inst);
                }
                break;
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
            case SHL:
                if (auto arith_inst = dynamic_cast<ArithmeticInstruction*>(inst)) {
                    translateArithmetic(*arith_inst);
                }
                break;
            case ICMP:
                if (auto icmp_inst = dynamic_cast<IcmpInstruction*>(inst)) {
                    translateIcmp(*icmp_inst);
                }
                break;
            case FCMP:
                if (auto fcmp_inst = dynamic_cast<FcmpInstruction*>(inst)) {
                    translateFcmp(*fcmp_inst);
                }
                break;
            case BR_COND:
                if (auto br_inst = dynamic_cast<BrCondInstruction*>(inst)) {
                    translateBranch(*br_inst);
                }
                break;
            case BR_UNCOND:
                if (auto br_inst = dynamic_cast<BrUncondInstruction*>(inst)) {
                    translateBranch(*br_inst);
                }
                break;
            case RET:
                if (auto ret_inst = dynamic_cast<RetInstruction*>(inst)) {
                    translateReturn(*ret_inst);
                }
                break;
            case CALL:
                if (auto call_inst = dynamic_cast<CallInstruction*>(inst)) {
                    translateCall(*call_inst);
                }
                break;
            case ALLOCA:
                if (auto alloca_inst = dynamic_cast<AllocaInstruction*>(inst)) {
                    translateAlloca(*alloca_inst);
                }
                break;
            case GETELEMENTPTR:
                if (auto gep_inst = dynamic_cast<GetElementptrInstruction*>(inst)) {
                    translateGetelementptr(*gep_inst);
                }
                break;
            case SITOFP:
            case FPTOSI:
            case ZEXT:
            case BITCAST:
                translateConvert(*inst);
                break;
            default:
                // 处理其他指令或忽略
                break;
        }
    }
}

void InstructionSelector::translateLoad(const LoadInstruction& inst) {
    std::string dest = getOperandString(inst.GetResult());
    std::string addr = getOperandString(inst.GetPointer());
    
    if (isIntegerType(inst.GetType())) {
        if (inst.GetType() == LLVMType::I32) {
            current_block_->addInstruction(RISCVInstruction("lw", {dest, "0(" + addr + ")"}));
        } else if (inst.GetType() == LLVMType::I64) {
            current_block_->addInstruction(RISCVInstruction("ld", {dest, "0(" + addr + ")"}));
        } else {
            current_block_->addInstruction(RISCVInstruction("lb", {dest, "0(" + addr + ")"}));
        }
    } else if (isFloatType(inst.GetType())) {
        if (inst.GetType() == LLVMType::FLOAT32) {
            current_block_->addInstruction(RISCVInstruction("flw", {dest, "0(" + addr + ")"}));
        } else {
            current_block_->addInstruction(RISCVInstruction("fld", {dest, "0(" + addr + ")"}));
        }
    }
}

void InstructionSelector::translateStore(const StoreInstruction& inst) {
    std::string value = getOperandString(inst.GetValue());
    std::string addr = getOperandString(inst.GetPointer());
    
    if (isIntegerType(inst.GetType())) {
        if (inst.GetType() == LLVMType::I32) {
            current_block_->addInstruction(RISCVInstruction("sw", {value, "0(" + addr + ")"}));
        } else if (inst.GetType() == LLVMType::I64) {
            current_block_->addInstruction(RISCVInstruction("sd", {value, "0(" + addr + ")"}));
        } else {
            current_block_->addInstruction(RISCVInstruction("sb", {value, "0(" + addr + ")"}));
        }
    } else if (isFloatType(inst.GetType())) {
        if (inst.GetType() == LLVMType::FLOAT32) {
            current_block_->addInstruction(RISCVInstruction("fsw", {value, "0(" + addr + ")"}));
        } else {
            current_block_->addInstruction(RISCVInstruction("fsd", {value, "0(" + addr + ")"}));
        }
    }
}

void InstructionSelector::translateArithmetic(const ArithmeticInstruction& inst) {
    std::string dest = getOperandString(inst.GetResult());
    std::string op1 = getOperandString(inst.GetOp1());
    std::string op2 = getOperandString(inst.GetOp2());
    
    switch (inst.GetOpcode()) {
        case ADD:
            current_block_->addInstruction(RISCVInstruction("add", {dest, op1, op2}));
            break;
        case SUB:
            current_block_->addInstruction(RISCVInstruction("sub", {dest, op1, op2}));
            break;
        case MUL_OP:
            current_block_->addInstruction(RISCVInstruction("mul", {dest, op1, op2}));
            break;
        case DIV_OP:
            current_block_->addInstruction(RISCVInstruction("div", {dest, op1, op2}));
            break;
        case MOD_OP:
            current_block_->addInstruction(RISCVInstruction("rem", {dest, op1, op2}));
            break;
        case FADD:
            current_block_->addInstruction(RISCVInstruction("fadd.s", {dest, op1, op2}));
            break;
        case FSUB:
            current_block_->addInstruction(RISCVInstruction("fsub.s", {dest, op1, op2}));
            break;
        case FMUL:
            current_block_->addInstruction(RISCVInstruction("fmul.s", {dest, op1, op2}));
            break;
        case FDIV:
            current_block_->addInstruction(RISCVInstruction("fdiv.s", {dest, op1, op2}));
            break;
        case BITAND:
            current_block_->addInstruction(RISCVInstruction("and", {dest, op1, op2}));
            break;
        case BITOR:
            current_block_->addInstruction(RISCVInstruction("or", {dest, op1, op2}));
            break;
        case BITXOR:
            current_block_->addInstruction(RISCVInstruction("xor", {dest, op1, op2}));
            break;
        case SHL:
            current_block_->addInstruction(RISCVInstruction("sll", {dest, op1, op2}));
            break;
        default:
            break;
    }
}

void InstructionSelector::translateIcmp(const IcmpInstruction& inst) {
    std::string dest = getOperandString(inst.GetResult());
    std::string op1 = getOperandString(inst.GetOp1());
    std::string op2 = getOperandString(inst.GetOp2());
    
    switch (inst.GetCond()) {
        case eq:
            current_block_->addInstruction(RISCVInstruction("sub", {dest, op1, op2}));
            current_block_->addInstruction(RISCVInstruction("seqz", {dest, dest}));
            break;
        case ne:
            current_block_->addInstruction(RISCVInstruction("sub", {dest, op1, op2}));
            current_block_->addInstruction(RISCVInstruction("snez", {dest, dest}));
            break;
        case slt:
            current_block_->addInstruction(RISCVInstruction("slt", {dest, op1, op2}));
            break;
        case sle:
            current_block_->addInstruction(RISCVInstruction("slt", {dest, op2, op1}));
            current_block_->addInstruction(RISCVInstruction("xori", {dest, dest, "1"}));
            break;
        case sgt:
            current_block_->addInstruction(RISCVInstruction("slt", {dest, op2, op1}));
            break;
        case sge:
            current_block_->addInstruction(RISCVInstruction("slt", {dest, op1, op2}));
            current_block_->addInstruction(RISCVInstruction("xori", {dest, dest, "1"}));
            break;
        default:
            break;
    }
}

void InstructionSelector::translateFcmp(const FcmpInstruction& inst) {
    std::string dest = getOperandString(inst.GetResult());
    std::string op1 = getOperandString(inst.GetOp1());
    std::string op2 = getOperandString(inst.GetOp2());
    
    switch (inst.GetCond()) {
        case OEQ:
            current_block_->addInstruction(RISCVInstruction("feq.s", {dest, op1, op2}));
            break;
        case ONE:
            current_block_->addInstruction(RISCVInstruction("feq.s", {dest, op1, op2}));
            current_block_->addInstruction(RISCVInstruction("xori", {dest, dest, "1"}));
            break;
        case OLT:
            current_block_->addInstruction(RISCVInstruction("flt.s", {dest, op1, op2}));
            break;
        case OLE:
            current_block_->addInstruction(RISCVInstruction("fle.s", {dest, op1, op2}));
            break;
        case OGT:
            current_block_->addInstruction(RISCVInstruction("flt.s", {dest, op2, op1}));
            break;
        case OGE:
            current_block_->addInstruction(RISCVInstruction("fle.s", {dest, op2, op1}));
            break;
        default:
            break;
    }
}

void InstructionSelector::translateBranch(const BrCondInstruction& inst) {
    std::string cond = getOperandString(inst.GetCond());
    std::string true_label = getOperandString(inst.GetTrueLabel());
    std::string false_label = getOperandString(inst.GetFalseLabel());
    
    current_block_->addInstruction(RISCVInstruction("bnez", {cond, true_label}));
    current_block_->addInstruction(RISCVInstruction("j", {false_label}));
}

void InstructionSelector::translateBranch(const BrUncondInstruction& inst) {
    std::string label = getOperandString(inst.GetLabel());
    current_block_->addInstruction(RISCVInstruction("j", {label}));
}

void InstructionSelector::translateReturn(const RetInstruction& inst) {
    if (inst.GetType() != LLVMType::VOID_TYPE) {
        std::string ret_val = getOperandString(inst.GetRetVal());
        if (isIntegerType(inst.GetType())) {
            current_block_->addInstruction(RISCVInstruction("mv", {"a0", ret_val}));
        } else if (isFloatType(inst.GetType())) {
            current_block_->addInstruction(RISCVInstruction("fmv.s", {"fa0", ret_val}));
        }
    }
    
    // 函数尾声：恢复寄存器并返回
    current_block_->addInstruction(RISCVInstruction("ld", {"ra", "8(sp)"}));
    current_block_->addInstruction(RISCVInstruction("ld", {"s0", "0(sp)"}));
    current_block_->addInstruction(RISCVInstruction("addi", {"sp", "sp", "16"}));
    current_block_->addInstruction(RISCVInstruction("ret", {}));
}

void InstructionSelector::translateCall(const CallInstruction& inst) {
    // 处理函数参数
    const auto& args = inst.GetArgs();
    int int_arg_count = 0;
    int float_arg_count = 0;
    
    for (const auto& arg : args) {
        std::string arg_val = getOperandString(arg.second);
        
        if (isIntegerType(arg.first)) {
            if (int_arg_count < 8) {
                std::string arg_reg = "a" + std::to_string(int_arg_count);
                current_block_->addInstruction(RISCVInstruction("mv", {arg_reg, arg_val}));
                int_arg_count++;
            } else {
                // 参数过多，需要通过栈传递
                // 这里简化处理，实际需要更复杂的栈管理
            }
        } else if (isFloatType(arg.first)) {
            if (float_arg_count < 8) {
                std::string arg_reg = "fa" + std::to_string(float_arg_count);
                current_block_->addInstruction(RISCVInstruction("fmv.s", {arg_reg, arg_val}));
                float_arg_count++;
            }
        }
    }
    
    // 调用函数
    current_block_->addInstruction(RISCVInstruction("call", {inst.GetFuncName()}));
    
    // 处理返回值
    if (inst.GetType() != LLVMType::VOID_TYPE && inst.GetResult()) {
        std::string result = getOperandString(inst.GetResult());
        if (isIntegerType(inst.GetType())) {
            current_block_->addInstruction(RISCVInstruction("mv", {result, "a0"}));
        } else if (isFloatType(inst.GetType())) {
            current_block_->addInstruction(RISCVInstruction("fmv.s", {result, "fa0"}));
        }
    }
}

void InstructionSelector::translateAlloca(const AllocaInstruction& inst) {
    std::string result = getOperandString(inst.GetResult());
    std::string size = getTypeSize(inst.GetType());
    
    // 简化的alloca实现：在栈上分配空间
    current_block_->addInstruction(RISCVInstruction("addi", {"sp", "sp", "-" + size}));
    current_block_->addInstruction(RISCVInstruction("mv", {result, "sp"}));
}

void InstructionSelector::translateGetelementptr(const GetElementptrInstruction& inst) {
    std::string result = getOperandString(inst.GetResult());
    std::string base = getOperandString(inst.GetPtrVal());
    
    // 简化的GEP实现：假设只有一个索引
    const auto& indices = inst.GetIndexes();
    if (!indices.empty()) {
        std::string index = getOperandString(indices[0]);
        std::string size = getTypeSize(inst.GetType());
        
        // 计算偏移量
        std::string temp = vreg_manager_.getVirtualRegName(vreg_manager_.allocateVirtualReg());
        current_block_->addInstruction(RISCVInstruction("li", {temp, size}));
        current_block_->addInstruction(RISCVInstruction("mul", {temp, index, temp}));
        current_block_->addInstruction(RISCVInstruction("add", {result, base, temp}));
    } else {
        current_block_->addInstruction(RISCVInstruction("mv", {result, base}));
    }
}

void InstructionSelector::translateGlobalVar(const GlobalVarDefineInstruction& inst) {
    std::string var_name = inst.GetName();
    std::string type_size = getTypeSize(inst.GetType());
    
    std::string data_decl = ".globl " + var_name + "\n";
    data_decl += ".align 4\n";
    data_decl += var_name + ":\n";
    
    const auto& attr = inst.GetAttr();
    if (attr.IntInitVals.empty() && attr.FloatInitVals.empty()) {
        data_decl += "    .space " + type_size;
    } else {
        // 处理初始值
        if (!attr.IntInitVals.empty()) {
            data_decl += "    .word " + std::to_string(attr.IntInitVals[0]);
        } else if (!attr.FloatInitVals.empty()) {
            data_decl += "    .float " + std::to_string(attr.FloatInitVals[0]);
        }
    }
    
    global_data_.push_back(data_decl);
}

void InstructionSelector::translateGlobalString(const GlobalStringConstInstruction& inst) {
    std::string str_name = inst.GetName();
    std::string str_value = inst.GetValue();
    
    std::string data_decl = ".globl " + str_name + "\n";
    data_decl += str_name + ":\n";
    data_decl += "    .asciz \"" + str_value + "\"";
    
    global_data_.push_back(data_decl);
}

void InstructionSelector::translateConvert(const BasicInstruction& inst) {
    // 简化的类型转换实现
    // 实际需要根据具体的转换类型进行不同的处理
    
    // 这里只是一个占位符，实际实现需要更详细
    switch (inst.GetOpcode()) {
        case SITOFP:
            // 整数转浮点
            break;
        case FPTOSI:
            // 浮点转整数
            break;
        case ZEXT:
            // 零扩展
            break;
        case BITCAST:
            // 位转换
            break;
        default:
            break;
    }
}

} // namespace riscv
