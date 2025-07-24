#include "machine_ir.h"
#include <sstream>

// RegisterOperand toString实现
std::string RegisterOperand::toString() const {
    // 如果是虚拟寄存器，返回虚拟寄存器标识
    if (isVirtualReg) {
        return "v" + std::to_string(virtualRegNum);
    }
    
    std::string regNames[] = {
        // X寄存器 (通用寄存器)
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };
    
    std::string floatRegNames[] = {
        // F寄存器 (浮点寄存器)
        "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7",
        "fs0", "fs1", "fa0", "fa1", "fa2", "fa3", "fa4", "fa5",
        "fa6", "fa7", "fs2", "fs3", "fs4", "fs5", "fs6", "fs7",
        "fs8", "fs9", "fs10", "fs11", "ft8", "ft9", "ft10", "ft11"
    };
    
    if (isFloat) {
        int regIndex = static_cast<int>(reg) - 32; // F寄存器从32开始
        if (regIndex >= 0 && regIndex < 32) {
            return floatRegNames[regIndex];
        }
    } else {
        int regIndex = static_cast<int>(reg);
        if (regIndex >= 0 && regIndex < 32) {
            return regNames[regIndex];
        }
    }
    
    return "invalid_reg";
}

// MachineInstruction toString实现
std::string MachineInstruction::toString() const {
    std::stringstream ss;
    
    // 操作码到字符串的映射
    std::string opcodeStr;
    switch (opcode) {
        case RISCVOpcode::ADD: opcodeStr = "add"; break;
        case RISCVOpcode::ADDI: opcodeStr = "addi"; break;
        case RISCVOpcode::SUB: opcodeStr = "sub"; break;
        case RISCVOpcode::MUL: opcodeStr = "mul"; break;
        case RISCVOpcode::DIV: opcodeStr = "div"; break;
        case RISCVOpcode::REM: opcodeStr = "rem"; break;
        
        case RISCVOpcode::FADD_S: opcodeStr = "fadd.s"; break;
        case RISCVOpcode::FSUB_S: opcodeStr = "fsub.s"; break;
        case RISCVOpcode::FMUL_S: opcodeStr = "fmul.s"; break;
        case RISCVOpcode::FDIV_S: opcodeStr = "fdiv.s"; break;
        
        case RISCVOpcode::AND: opcodeStr = "and"; break;
        case RISCVOpcode::ANDI: opcodeStr = "andi"; break;
        case RISCVOpcode::OR: opcodeStr = "or"; break;
        case RISCVOpcode::ORI: opcodeStr = "ori"; break;
        case RISCVOpcode::XOR: opcodeStr = "xor"; break;
        case RISCVOpcode::XORI: opcodeStr = "xori"; break;
        
        case RISCVOpcode::SLL: opcodeStr = "sll"; break;
        case RISCVOpcode::SLLI: opcodeStr = "slli"; break;
        case RISCVOpcode::SRL: opcodeStr = "srl"; break;
        case RISCVOpcode::SRLI: opcodeStr = "srli"; break;
        case RISCVOpcode::SRA: opcodeStr = "sra"; break;
        case RISCVOpcode::SRAI: opcodeStr = "srai"; break;
        
        case RISCVOpcode::SLT: opcodeStr = "slt"; break;
        case RISCVOpcode::SLTI: opcodeStr = "slti"; break;
        case RISCVOpcode::SLTU: opcodeStr = "sltu"; break;
        case RISCVOpcode::SLTIU: opcodeStr = "sltiu"; break;
        
        case RISCVOpcode::FEQ_S: opcodeStr = "feq.s"; break;
        case RISCVOpcode::FLT_S: opcodeStr = "flt.s"; break;
        case RISCVOpcode::FLE_S: opcodeStr = "fle.s"; break;
        
        case RISCVOpcode::LW: opcodeStr = "lw"; break;
        case RISCVOpcode::LB: opcodeStr = "lb"; break;
        case RISCVOpcode::LH: opcodeStr = "lh"; break;
        case RISCVOpcode::LBU: opcodeStr = "lbu"; break;
        case RISCVOpcode::LHU: opcodeStr = "lhu"; break;
        case RISCVOpcode::SW: opcodeStr = "sw"; break;
        case RISCVOpcode::SB: opcodeStr = "sb"; break;
        case RISCVOpcode::SH: opcodeStr = "sh"; break;
        case RISCVOpcode::FLW: opcodeStr = "flw"; break;
        case RISCVOpcode::FSW: opcodeStr = "fsw"; break;
        
        case RISCVOpcode::BEQ: opcodeStr = "beq"; break;
        case RISCVOpcode::BNE: opcodeStr = "bne"; break;
        case RISCVOpcode::BLT: opcodeStr = "blt"; break;
        case RISCVOpcode::BGE: opcodeStr = "bge"; break;
        case RISCVOpcode::BLTU: opcodeStr = "bltu"; break;
        case RISCVOpcode::BGEU: opcodeStr = "bgeu"; break;
        
        case RISCVOpcode::JAL: opcodeStr = "jal"; break;
        case RISCVOpcode::JALR: opcodeStr = "jalr"; break;
        
        case RISCVOpcode::ECALL: opcodeStr = "ecall"; break;
        case RISCVOpcode::EBREAK: opcodeStr = "ebreak"; break;
        
        case RISCVOpcode::LI: opcodeStr = "li"; break;
        case RISCVOpcode::LA: opcodeStr = "la"; break;
        case RISCVOpcode::MV: opcodeStr = "mv"; break;
        case RISCVOpcode::NOP: opcodeStr = "nop"; break;
        case RISCVOpcode::RET: opcodeStr = "ret"; break;
        
        case RISCVOpcode::FCVT_S_W: opcodeStr = "fcvt.s.w"; break;
        case RISCVOpcode::FCVT_W_S: opcodeStr = "fcvt.w.s"; break;
        
        case RISCVOpcode::FMV_S: opcodeStr = "fmv.s"; break;
        
        case RISCVOpcode::LUI: opcodeStr = "lui"; break;
        case RISCVOpcode::AUIPC: opcodeStr = "auipc"; break;
        
        default: opcodeStr = "unknown"; break;
    }
    
    ss << "\t" << opcodeStr;
    
    // 输出操作数
    for (size_t i = 0; i < operands.size(); ++i) {
        if (i == 0) ss << "\t";
        else ss << ", ";
        ss << operands[i]->toString();
    }
    
    // 添加注释
    if (!comment.empty()) {
        ss << "\t# " << comment;
    }
    
    return ss.str();
}

// MachineBasicBlock print实现
void MachineBasicBlock::print(std::ostream& os) const {
    os << label << ":\n";
    for (const auto& inst : instructions) {
        os << inst->toString() << "\n";
    }
}

// MachineFunction print实现
void MachineFunction::print(std::ostream& os) const {
    os << "\n.globl " << name << "\n";
    os << ".type " << name << ", @function\n";
    os << name << ":\n";
    
    for (const auto& block : blocks) {
        if (block->getId() != 1) { // 第一个块不需要标签
            block->print(os);
        } else {
            // 第一个块只输出指令，不输出标签
            for (const auto& inst : block->getInstructions()) {
                os << inst->toString() << "\n";
            }
        }
    }
    
    os << ".size " << name << ", .-" << name << "\n";
}

// MachineModule print实现
void MachineModule::print(std::ostream& os) const {
    // 输出汇编头部信息
    os << "\t.file\t\"source.sy\"\n";
    os << "\t.option pic\n";
    os << "\t.attribute arch, \"rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0\"\n";
    os << "\t.attribute unaligned_access, 0\n";
    os << "\t.attribute stack_align, 16\n";
    
    // 输出全局数据
    if (!globalData.empty()) {
        os << "\n.section .data\n";
        for (const auto& data : globalData) {
            os << data << "\n";
        }
    }
    
    // 输出代码段
    os << "\n.text\n";
    
    // 输出函数
    for (const auto& func : functions) {
        func->print(os);
    }
} 