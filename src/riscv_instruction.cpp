#include "../include/riscv_instruction.h"
#include <sstream>

void RiscvArithmeticInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  bool use_immediate = false;
  
  // 检查是否可以使用立即数指令
  auto *imm_op = dynamic_cast<RiscvImmI32Operand*>(rs2.get());
  
  switch (opcode) {
    case RiscvOpcode::ADD: 
      if (imm_op) {
        op_str = "addi"; 
        use_immediate = true;
      } else {
        op_str = "add"; 
      }
      break;
    case RiscvOpcode::SUB: op_str = "sub"; break;
    case RiscvOpcode::MUL: op_str = "mul"; break;
    case RiscvOpcode::DIV: op_str = "div"; break;
    case RiscvOpcode::REM: op_str = "rem"; break;
    case RiscvOpcode::AND: 
      if (imm_op) {
        op_str = "andi"; 
        use_immediate = true;
      } else {
        op_str = "and"; 
      }
      break;
    case RiscvOpcode::OR: 
      if (imm_op) {
        op_str = "ori"; 
        use_immediate = true;
      } else {
        op_str = "or"; 
      }
      break;
    case RiscvOpcode::XOR: 
      if (imm_op) {
        op_str = "xori"; 
        use_immediate = true;
      } else {
        op_str = "xor"; 
      }
      break;
    case RiscvOpcode::SLL: op_str = "sll"; break;
    case RiscvOpcode::SRL: op_str = "srl"; break;
    case RiscvOpcode::SRA: op_str = "sra"; break;
    case RiscvOpcode::SLT: 
      if (imm_op) {
        op_str = "slti"; 
        use_immediate = true;
      } else {
        op_str = "slt"; 
      }
      break;
    case RiscvOpcode::SLTU: 
      if (imm_op) {
        op_str = "sltiu"; 
        use_immediate = true;
      } else {
        op_str = "sltu"; 
      }
      break;
    case RiscvOpcode::FADD_S: op_str = "fadd.s"; break;
    case RiscvOpcode::FSUB_S: op_str = "fsub.s"; break;
    case RiscvOpcode::FMUL_S: op_str = "fmul.s"; break;
    case RiscvOpcode::FDIV_S: op_str = "fdiv.s"; break;
    case RiscvOpcode::FEQ_S: op_str = "feq.s"; break;
    case RiscvOpcode::FLT_S: op_str = "flt.s"; break;
    case RiscvOpcode::FLE_S: op_str = "fle.s"; break;
    default: op_str = "unknown"; break;
  }
  
  if (use_immediate && imm_op) {
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << rs1->GetFullName() << ", " << imm_op->GetIntImmVal() << "\n";
  } else {
    // 对于浮点立即数，添加注释
    auto *float_imm1 = dynamic_cast<RiscvImmF32Operand*>(rs1.get());
    auto *float_imm2 = dynamic_cast<RiscvImmF32Operand*>(rs2.get());
    
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << rs1->GetFullName() << ", " << rs2->GetFullName();
    
    if (float_imm1 || float_imm2) {
      s << "  # 注意：浮点立即数需要先加载到寄存器";
    }
    s << "\n";
  }
}

void RiscvImmediateInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  switch (opcode) {
    case RiscvOpcode::ADDI: op_str = "addi"; break;
    case RiscvOpcode::SUBI: op_str = "subi"; break;
    case RiscvOpcode::ANDI: op_str = "andi"; break;
    case RiscvOpcode::ORI: op_str = "ori"; break;
    case RiscvOpcode::XORI: op_str = "xori"; break;
    case RiscvOpcode::SLLI: op_str = "slli"; break;
    case RiscvOpcode::SRLI: op_str = "srli"; break;
    case RiscvOpcode::SRAI: op_str = "srai"; break;
    case RiscvOpcode::SLTI: op_str = "slti"; break;
    case RiscvOpcode::SLTIU: op_str = "sltiu"; break;
    default: op_str = "unknown"; break;
  }
  
  s << "    " << op_str << " " << rd->GetFullName() << ", " 
    << rs1->GetFullName() << ", " << immediate << "\n";
}

void RiscvMemoryInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  switch (opcode) {
    case RiscvOpcode::LW: op_str = "lw"; break;
    case RiscvOpcode::LH: op_str = "lh"; break;
    case RiscvOpcode::LB: op_str = "lb"; break;
    case RiscvOpcode::SW: op_str = "sw"; break;
    case RiscvOpcode::SH: op_str = "sh"; break;
    case RiscvOpcode::SB: op_str = "sb"; break;
    case RiscvOpcode::FLW: op_str = "flw"; break;
    case RiscvOpcode::FSW: op_str = "fsw"; break;
    default: op_str = "unknown"; break;
  }
  
  if (opcode == RiscvOpcode::LW || opcode == RiscvOpcode::LH || 
      opcode == RiscvOpcode::LB || opcode == RiscvOpcode::FLW) {
    // 加载指令: lw rd, offset(rs1)
    s << "    " << op_str << " " << reg->GetFullName() << ", " 
      << address->GetFullName() << "\n";
  } else {
    // 存储指令: sw rs2, offset(rs1)
    s << "    " << op_str << " " << reg->GetFullName() << ", " 
      << address->GetFullName() << "\n";
  }
}

void RiscvBranchInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  switch (opcode) {
    case RiscvOpcode::BEQ: op_str = "beq"; break;
    case RiscvOpcode::BNE: op_str = "bne"; break;
    case RiscvOpcode::BLT: op_str = "blt"; break;
    case RiscvOpcode::BGE: op_str = "bge"; break;
    case RiscvOpcode::BLTU: op_str = "bltu"; break;
    case RiscvOpcode::BGEU: op_str = "bgeu"; break;
    default: op_str = "unknown"; break;
  }
  
  s << "    " << op_str << " " << rs1->GetFullName() << ", " 
    << rs2->GetFullName() << ", " << label->GetFullName() << "\n";
}

void RiscvJumpInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  switch (opcode) {
    case RiscvOpcode::JAL: op_str = "jal"; break;
    case RiscvOpcode::JALR: op_str = "jalr"; break;
    default: op_str = "unknown"; break;
  }
  
  if (opcode == RiscvOpcode::JAL) {
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << target->GetFullName() << "\n";
  } else {
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << target->GetFullName() << ", 0\n";
  }
}

void RiscvGlobalVarInstruction::PrintIR(std::ostream &s) {
  s << ".data\n";
  s << var_name << ":\n";
  
  if (var_type == "i32") {
    if (init_vals.empty()) {
      s << "    .word 0\n";
    } else {
      for (int val : init_vals) {
        s << "    .word " << val << "\n";
      }
    }
  } else if (var_type == "float") {
    if (init_float_vals.empty()) {
      s << "    .word 0\n";
    } else {
      for (float val : init_float_vals) {
        // 将浮点数转换为字节表示
        union { float f; uint32_t i; } converter;
        converter.f = val;
        s << "    .word 0x" << std::hex << converter.i << std::dec << "\n";
      }
    }
  } else if (var_type == "string") {
    s << "    .asciz \"" << var_name << "\"\n";
  }
  s << "\n";
}

void RiscvCallInstruction::PrintIR(std::ostream &s) {
  // 简化的函数调用实现
  s << "    jal ra, " << function_name << "\n";
}

void RiscvPseudoInstruction::PrintIR(std::ostream &s) {
  std::string op_str;
  switch (opcode) {
    case RiscvOpcode::LI: op_str = "li"; break;
    case RiscvOpcode::LA: op_str = "la"; break;
    case RiscvOpcode::MV: op_str = "mv"; break;
    case RiscvOpcode::NOP: op_str = "nop"; break;
    case RiscvOpcode::RET: op_str = "ret"; break;
    case RiscvOpcode::FCVT_S_W: op_str = "fcvt.s.w"; break;
    case RiscvOpcode::FCVT_W_S: op_str = "fcvt.w.s"; break;
    default: op_str = "unknown"; break;
  }
  
  if (opcode == RiscvOpcode::NOP || opcode == RiscvOpcode::RET) {
    s << "    " << op_str << "\n";
  } else if (opcode == RiscvOpcode::MV) {
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << operand->GetFullName() << "\n";
  } else {
    s << "    " << op_str << " " << rd->GetFullName() << ", " 
      << operand->GetFullName() << "\n";
  }
} 