#include "../include/riscv_mir.h"
#include <sstream>

// ===--------------------------------------------------------------------=== //
// MachineRegister 实现
// ===--------------------------------------------------------------------=== //

std::string MachineRegister::getName() const {
  if (type == MRegType::VIRTUAL) {
    return "%v" + std::to_string(reg_num);
  } else if (type == MRegType::PHYSICAL) {
    if (reg_class == RISCVRegClass::GPR) {
      return "x" + std::to_string(reg_num);
    } else if (reg_class == RISCVRegClass::FPR) {
      return "f" + std::to_string(reg_num);
    }
  }
  return "unknown";
}

// ===--------------------------------------------------------------------=== //
// MachineOperand 实现
// ===--------------------------------------------------------------------=== //

std::string MachineOperand::toString() const {
  switch (type) {
    case REG: return reg->getName();
    case IMM: return std::to_string(imm);
    case FIMM: return std::to_string(fimm) + "f";
    case LABEL: return ".L" + std::to_string(label_id);
    case GLOBAL: return "@" + *global_name;
    case STACK_SLOT: return "[sp+" + std::to_string(stack_slot) + "]";
  }
  return "unknown";
}

// ===--------------------------------------------------------------------=== //
// MachineInstruction 实现
// ===--------------------------------------------------------------------=== //

void MachineInstruction::addOperand(const MachineOperand& op) {
  operands.push_back(op);
}

void MachineInstruction::setOperands(const std::vector<MachineOperand>& ops) {
  operands = ops;
}

std::string MachineInstruction::toString() const {
  std::string result = opcodeToString(opcode);
  for (size_t i = 0; i < operands.size(); ++i) {
    if (i == 0) result += " ";
    else result += ", ";
    result += operands[i].toString();
  }
  return result;
}

// 专门用于MIR格式的输出方法
std::string MachineInstruction::toMIRString() const {
  std::string result = "[MIR] " + opcodeToString(opcode);
  for (size_t i = 0; i < operands.size(); ++i) {
    if (i == 0) result += " ";
    else result += ", ";
    
    // 在MIR格式中，显示更多调试信息
    if (operands[i].isReg() && operands[i].reg) {
      if (operands[i].reg->isVirtual()) {
        result += "%" + std::to_string(operands[i].reg->reg_num) + "(virt)";
      } else {
        result += "x" + std::to_string(operands[i].reg->reg_num) + "(phys)";
      }
    } else {
      result += operands[i].toString();
    }
  }
  return result;
}

std::string MachineInstruction::opcodeToString(RISCVOpcode op) const {
  switch (op) {
    // 通用操作码
    case RISCVOpcode::G_ADD: return "G_ADD";
    case RISCVOpcode::G_SUB: return "G_SUB";
    case RISCVOpcode::G_MUL: return "G_MUL";
    case RISCVOpcode::G_DIV: return "G_DIV";
    case RISCVOpcode::G_AND: return "G_AND";
    case RISCVOpcode::G_OR: return "G_OR";
    case RISCVOpcode::G_XOR: return "G_XOR";
    case RISCVOpcode::G_SHL: return "G_SHL";
    case RISCVOpcode::G_SHR: return "G_SHR";
    case RISCVOpcode::G_LOAD: return "G_LOAD";
    case RISCVOpcode::G_STORE: return "G_STORE";
    case RISCVOpcode::G_ICMP: return "G_ICMP";
case RISCVOpcode::G_FCMP: return "G_FCMP";

// 浮点运算指令
case RISCVOpcode::G_FADD: return "G_FADD";
case RISCVOpcode::G_FSUB: return "G_FSUB";
case RISCVOpcode::G_FMUL: return "G_FMUL";
case RISCVOpcode::G_FDIV: return "G_FDIV";

case RISCVOpcode::G_BR: return "G_BR";
    case RISCVOpcode::G_PHI: return "G_PHI";
    case RISCVOpcode::G_COPY: return "G_COPY";
    case RISCVOpcode::G_CONSTANT: return "G_CONSTANT";
    case RISCVOpcode::G_CALL: return "G_CALL";
    case RISCVOpcode::G_RET: return "G_RET";
case RISCVOpcode::G_STACK_ADDR: return "G_STACK_ADDR";
case RISCVOpcode::G_GEP: return "G_GEP";
    
    // RISC-V 特定指令
    case RISCVOpcode::ADD: return "add";
    case RISCVOpcode::ADDI: return "addi";
    case RISCVOpcode::SUB: return "sub";
    case RISCVOpcode::SUBI: return "subi";
    case RISCVOpcode::MUL: return "mul";
    case RISCVOpcode::MULW: return "mulw";
    case RISCVOpcode::DIV: return "div";
    case RISCVOpcode::DIVW: return "divw";
    case RISCVOpcode::REM: return "rem";
    case RISCVOpcode::REMW: return "remw";
    
    case RISCVOpcode::AND: return "and";
    case RISCVOpcode::ANDI: return "andi";
    case RISCVOpcode::OR: return "or";
    case RISCVOpcode::ORI: return "ori";
    case RISCVOpcode::XOR: return "xor";
    case RISCVOpcode::XORI: return "xori";
    
    case RISCVOpcode::SLL: return "sll";
    case RISCVOpcode::SLLI: return "slli";
    case RISCVOpcode::SRL: return "srl";
    case RISCVOpcode::SRLI: return "srli";
    case RISCVOpcode::SRA: return "sra";
case RISCVOpcode::SRAI: return "srai";

// 比较指令
case RISCVOpcode::SLT: return "slt";
case RISCVOpcode::SLTI: return "slti";
case RISCVOpcode::SLTU: return "sltu";
case RISCVOpcode::SLTIU: return "sltiu";

// 浮点运算指令
case RISCVOpcode::FADD_S: return "fadd.s";
case RISCVOpcode::FSUB_S: return "fsub.s";
case RISCVOpcode::FMUL_S: return "fmul.s";
case RISCVOpcode::FDIV_S: return "fdiv.s";
    case RISCVOpcode::FEQ_S: return "feq.s";
    case RISCVOpcode::FLT_S: return "flt.s";
    case RISCVOpcode::FLE_S: return "fle.s";
    
    case RISCVOpcode::LW: return "lw";
    case RISCVOpcode::LH: return "lh";
    case RISCVOpcode::LB: return "lb";
    case RISCVOpcode::SW: return "sw";
    case RISCVOpcode::SH: return "sh";
    case RISCVOpcode::SB: return "sb";
    
    case RISCVOpcode::BEQ: return "beq";
    case RISCVOpcode::BNE: return "bne";
    case RISCVOpcode::BLT: return "blt";
    case RISCVOpcode::BGE: return "bge";
    case RISCVOpcode::BLTU: return "bltu";
    case RISCVOpcode::BGEU: return "bgeu";
    
    case RISCVOpcode::JAL: return "jal";
    case RISCVOpcode::JALR: return "jalr";
    case RISCVOpcode::FLW: return "flw";
    case RISCVOpcode::FSW: return "fsw";
    
    // 伪指令
    case RISCVOpcode::LI: return "li";
    case RISCVOpcode::LA: return "la";
    case RISCVOpcode::MV: return "mv";
    case RISCVOpcode::NOP: return "nop";
    
    default: return "unknown";
  }
}

// ===--------------------------------------------------------------------=== //
// MachineBasicBlock 实现
// ===--------------------------------------------------------------------=== //

void MachineBasicBlock::addInstruction(std::unique_ptr<MachineInstruction> inst) {
  instructions.push_back(std::move(inst));
}

void MachineBasicBlock::addSuccessor(MachineBasicBlock* succ) {
  successors.push_back(succ);
  succ->predecessors.push_back(this);
}

void MachineBasicBlock::print(std::ostream& os) const {
  os << ".LBB" << block_id << ":\n";
  for (const auto& inst : instructions) {
    os << "  " << inst->toString() << "\n";
  }
}

void MachineBasicBlock::printMIR(std::ostream& os) const {
  os << "[MIR Block " << block_id << "]\n";
  for (const auto& inst : instructions) {
    os << "  " << inst->toMIRString() << "\n";
  }
}

// ===--------------------------------------------------------------------=== //
// MachineFunction 实现
// ===--------------------------------------------------------------------=== //

MachineBasicBlock* MachineFunction::createBasicBlock() {
  auto block = std::make_unique<MachineBasicBlock>(next_block_id++);
  MachineBasicBlock* ptr = block.get();
  block_map[ptr->block_id] = ptr;
  basic_blocks.push_back(std::move(block));
  return ptr;
}

MachineRegister* MachineFunction::createVirtualRegister(RISCVRegClass reg_class) {
  return new MachineRegister(MRegType::VIRTUAL, reg_class, next_vreg_num++);
}

int MachineFunction::allocateStackSlot(int size) {
  // RISC-V ABI要求栈对齐到16字节边界
  // 为了支持函数序言中保存ra和s0寄存器，我们需要预留空间
  
  // 如果这是第一次分配栈槽，需要为保存寄存器预留空间
  if (next_stack_slot == 0) {
    // 预留8字节用于保存ra (4字节) 和 s0 (4字节)
    next_stack_slot = 8;
  }
  
  // 对齐到4字节边界（RISC-V字对齐要求）
  int aligned_size = (size + 3) & ~3;
  int offset = next_stack_slot;
  next_stack_slot += aligned_size;
  
  // 确保总栈大小对齐到16字节边界
  stack_size = (next_stack_slot + 15) & ~15;
  
  return offset;
}

void MachineFunction::print(std::ostream& os) const {
  os << name << ":\n";
  for (const auto& block : basic_blocks) {
    block->print(os);
  }
}

void MachineFunction::printMIR(std::ostream& os) const {
  os << "[MIR Function: " << name << "] (VRegs: " << next_vreg_num << ")\n";
  for (const auto& block : basic_blocks) {
    block->printMIR(os);
  }
}

// ===--------------------------------------------------------------------=== //
// MachineModule 实现
// ===--------------------------------------------------------------------=== //

MachineFunction* MachineModule::createFunction(const std::string& name) {
  auto func = std::make_unique<MachineFunction>(name);
  MachineFunction* ptr = func.get();
  function_map[name] = ptr;
  functions.push_back(std::move(func));
  return ptr;
}

void MachineModule::addGlobalVariable(const std::string& name, int64_t value) {
  global_variables.emplace_back(name, value);
}

void MachineModule::addGlobalVariable(const std::string& name, float value) {
  global_variables.emplace_back(name, value);
}

void MachineModule::print(std::ostream& os) const {
  for (const auto& func : functions) {
    func->print(os);
    os << "\n";
  }
}

void MachineModule::printMIR(std::ostream& os) const {
  os << "=== Machine IR Module ===\n";
  for (const auto& func : functions) {
    func->printMIR(os);
    os << "\n";
  }
  os << "=== End of MIR Module ===\n";
} 