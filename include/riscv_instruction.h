#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// RISC-V 指令操作码
enum class RiscvOpcode {
  ADDI, // 立即数加法
  ADD,  // 寄存器加法
  SUB,
  MUL,
  DIV,
  MOD,
  FADD,
  FSUB,
  FMUL,
  FDIV,
  FMV,
  FMVWX,
  FADXW,
  SD,
  LI,
  LD,
  LW,
  SW,
  FLW,
  FSW,
  MV,
  LA,
  CALL,
  JR,
  BNEZ,
  SNEZ,
  SEQZ,
  AND,
  ANDI,
  OR,
  XOR,
  XORI,
  SLT,
  FEQ,
  FLT,
  FLE,
  FCVTSW,
  FCVTWS,
  GLOBAL_VAR,
  GLOBAL_STR,
};

class RiscvOperand {
public:
  enum operand_type {
    REG = 1,
    IMMI32 = 2,
    IMMF32 = 3,
    GLOBAL = 4,
    LABEL = 5,
    PTR = 6
  } operandType;
  virtual ~RiscvOperand() = default;
  virtual std::string GetFullName() = 0;
  virtual RiscvOperand *CopyOperand() = 0;
  operand_type GetOperandType() { return operandType; }
};

class RiscvRegOperand : public RiscvOperand {
public:
  int reg_no;
  RiscvRegOperand(int RegNo) {
    operandType = REG;
    reg_no = RegNo;
  }
  int GetRegNo() { return reg_no; }
  std::string GetFullName() override {
    // 负数表示物理寄存器
    if (reg_no < 0) {
      int physical_reg = -reg_no;
      // RISC-V 物理寄存器命名
      if (physical_reg == 1)
        return "zero";
      if (physical_reg == 2)
        return "ra";
      if (physical_reg == 3)
        return "sp";
      if (physical_reg == 4)
        return "gp";
      if (physical_reg == 5)
        return "tp";
      if (physical_reg >= 6 && physical_reg <= 8)
        return "t" + std::to_string(physical_reg - 6);
      if (physical_reg >= 9 && physical_reg <= 10)
        return "s" + std::to_string(physical_reg - 9);
      if (physical_reg >= 11 && physical_reg <= 18)
        return "a" + std::to_string(physical_reg - 11);
      if (physical_reg >= 19 && physical_reg <= 28)
        return "s" + std::to_string(physical_reg - 17);
      if (physical_reg >= 29 && physical_reg <= 32)
        return "t" + std::to_string(physical_reg - 26);
      if (physical_reg >= 33 && physical_reg <= 40)
        return "ft" + std::to_string(physical_reg - 33);
      if (physical_reg >= 41 && physical_reg <= 42)
        return "fs" + std::to_string(physical_reg - 41);
      if (physical_reg >= 43 && physical_reg <= 50)
        return "fa" + std::to_string(physical_reg - 43);
      if (physical_reg >= 51 && physical_reg <= 60)
        return "fs" + std::to_string(physical_reg - 49);
      if (physical_reg >= 61 && physical_reg <= 64)
        return "ft" + std::to_string(physical_reg - 53);
      return "x" + std::to_string(physical_reg);
    } else {
      // 虚拟寄存器使用%r前缀
      return "%r" + std::to_string(reg_no);
    }
  }
  RiscvOperand *CopyOperand() override { return new RiscvRegOperand(reg_no); }
};

class RiscvImmI32Operand : public RiscvOperand {
public:
  int immVal;
  RiscvImmI32Operand(int val) {
    operandType = IMMI32;
    immVal = val;
  }
  int GetIntImmVal() { return immVal; }
  std::string GetFullName() override { return std::to_string(immVal); }
  RiscvOperand *CopyOperand() override {
    return new RiscvImmI32Operand(immVal);
  }
};

class RiscvImmF32Operand : public RiscvOperand {
public:
  float immVal;
  RiscvImmF32Operand(float val) {
    operandType = IMMF32;
    immVal = val;
  }
  float GetFloatVal() { return immVal; }
  std::string GetFullName() override {
    unsigned long long byte_val = Float_to_Byte(immVal);
    std::ostringstream oss;
    oss << "0x" << std::hex << byte_val << std::dec;
    return oss.str();
  }
  RiscvOperand *CopyOperand() override {
    return new RiscvImmF32Operand(immVal);
  }
};

class RiscvGlobalOperand : public RiscvOperand {
public:
  std::string global_name;
  RiscvGlobalOperand(std::string name) {
    operandType = GLOBAL;
    global_name = std::move(name);
  }
  std::string GetGlobalName() { return global_name; }
  std::string GetFullName() override { return global_name; }
  RiscvOperand *CopyOperand() override {
    return new RiscvGlobalOperand(global_name);
  }
};

class RiscvLabelOperand : public RiscvOperand {
public:
  std::string label_name;
  RiscvLabelOperand(std::string name) {
    operandType = LABEL;
    label_name = std::move(name);
  }
  std::string GetLabelName() { return label_name; }
  std::string GetFullName() override { return label_name; }
  RiscvOperand *CopyOperand() override {
    return new RiscvLabelOperand(label_name);
  }
};

class RiscvPtrOperand : public RiscvOperand {
public:
  int offset;
  RiscvOperand *base_reg;
  RiscvPtrOperand(int offset, RiscvOperand *base) {
    operandType = PTR;
    this->offset = offset;
    this->base_reg = base;
  }
  std::string GetFullName() override {
    return std::to_string(offset) + "(" + base_reg->GetFullName() + ")";
  }
  RiscvOperand *CopyOperand() override {
    return new RiscvPtrOperand(offset, base_reg->CopyOperand());
  }
};

class RiscvInstruction {
public:
  RiscvOpcode opcode;
  virtual ~RiscvInstruction() = default;
  virtual void PrintIR(std::ostream &s) = 0;
  virtual RiscvOpcode GetOpcode() { return opcode; }
};

class RiscvAddiInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  int immediate;
  RiscvAddiInstruction(RiscvOperand *rd, RiscvOperand *rs1, int imm) {
    opcode = RiscvOpcode::ADDI;
    this->rd = rd;
    this->rs1 = rs1;
    this->immediate = imm;
  }
  void PrintIR(std::ostream &s) override {
    s << "  addi  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << immediate << "\n";
  }
};

class RiscvAddInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;

  RiscvAddInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::ADD;
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  add  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvSubInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvSubInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::SUB; // 使用SUB伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  sub  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvMulInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvMulInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::MUL; // 使用ADD伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  mul  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvDivInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvDivInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::DIV; // 使用DIV伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  div  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvModInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvModInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::MOD; // 使用MOD伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  rem  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFAddInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFAddInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FADD; // 使用ADD伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fadd.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFSubInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFSubInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FSUB; // 使用SUB伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fsub.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFMulInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFMulInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FMUL; // 使用MUL伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fmul.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFDivInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFDivInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FDIV; // 使用DIV伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fdiv.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFmvInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvFmvInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::FMV; // 使用FMV伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fmv.w.x  " << rd->GetFullName() << "," << rs1->GetFullName()
      << "\n";
  }
};

class RiscvSdInstruction : public RiscvInstruction {
public:
  RiscvOperand *reg, *address;
  RiscvSdInstruction(RiscvOperand *reg, RiscvOperand *address) {
    opcode = RiscvOpcode::SD;
    this->reg = reg;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  sd  " << reg->GetFullName() << "," << address->GetFullName()
      << "\n";
  }
};

class RiscvLiInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd;
  int imm;
  float float_val; // 用于浮点数立即数
  bool is_float;   // 是否是浮点数
  RiscvLiInstruction(RiscvOperand *rd, int imm) {
    opcode = RiscvOpcode::LI; // 使用LI伪指令
    this->rd = rd;
    this->imm = imm;
    this->is_float = false;
  }
  RiscvLiInstruction(RiscvOperand *rd, float float_val) {
    opcode = RiscvOpcode::LI; // 使用LI伪指令
    this->rd = rd;
    this->float_val = float_val;
    this->is_float = true;
  }
  void PrintIR(std::ostream &s) override {
    s << "  li  " << rd->GetFullName() << ",";
    if (is_float) {
      s << Float_to_Byte(float_val) << std::dec;
    } else {
      s << imm;
    }
    s << "\n";
  }
};

class RiscvLdInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *address;
  RiscvLdInstruction(RiscvOperand *rd, RiscvOperand *address) {
    opcode = RiscvOpcode::LD; // 使用LD伪指令
    this->rd = rd;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  ld  " << rd->GetFullName() << "," << address->GetFullName() << "\n";
  }
};

class RiscvLwInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *address;
  RiscvLwInstruction(RiscvOperand *rd, RiscvOperand *address) {
    opcode = RiscvOpcode::LW; // 使用LW伪指令
    this->rd = rd;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  lw  " << rd->GetFullName() << "," << address->GetFullName() << "\n";
  }
};

class RiscvSwInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs, *address;
  RiscvSwInstruction(RiscvOperand *rs, RiscvOperand *address) {
    opcode = RiscvOpcode::SW; // 使用SW伪指令
    this->rs = rs;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  sw  " << rs->GetFullName() << "," << address->GetFullName() << "\n";
  }
};

class RiscvFlwInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *address;
  RiscvFlwInstruction(RiscvOperand *rd, RiscvOperand *address) {
    opcode = RiscvOpcode::FLW; // 使用FLW伪指令
    this->rd = rd;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  flw  " << rd->GetFullName() << "," << address->GetFullName()
      << "\n";
  }
};

class RiscvFswInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs, *address;
  RiscvFswInstruction(RiscvOperand *rs, RiscvOperand *address) {
    opcode = RiscvOpcode::FSW; // 使用FSW伪指令
    this->rs = rs;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fsw  " << rs->GetFullName() << "," << address->GetFullName()
      << "\n";
  }
};

class RiscvLaInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *address;
  RiscvLaInstruction(RiscvOperand *rd, RiscvOperand *address) {
    opcode = RiscvOpcode::LA; // 使用LA伪指令
    this->rd = rd;
    this->address = address;
  }
  void PrintIR(std::ostream &s) override {
    s << "  la  " << rd->GetFullName() << "," << address->GetFullName() << "\n";
  }
};

class RiscvJrInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd;
  RiscvJrInstruction(RiscvOperand *rd) {
    opcode = RiscvOpcode::JR; // 使用JR伪指令
    this->rd = rd;
  }
  void PrintIR(std::ostream &s) override {
    s << "  jr  " << rd->GetFullName() << "\n";
  }
};

class RiscvMvInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvMvInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::MV; // 使用MV伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  mv  " << rd->GetFullName() << "," << rs1->GetFullName() << "\n";
  }
};

// 分支指令类
class RiscvBranchInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs1, *rs2, *label;
  RiscvBranchInstruction(RiscvOpcode op, RiscvOperand *rs1, RiscvOperand *rs2,
                         RiscvOperand *label) {
    opcode = op;
    this->rs1 = rs1;
    this->rs2 = rs2;
    this->label = label;
  }
  void PrintIR(std::ostream &s) override {
    std::cerr << "Branch not implemented\n";
  }
};

// 跳转指令类
class RiscvJumpInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *target;
  RiscvJumpInstruction(RiscvOpcode op, RiscvOperand *rd, RiscvOperand *target) {
    opcode = op;
    this->rd = rd;
    this->target = target;
  }
  void PrintIR(std::ostream &s) override {
    std::cerr << "Jump not implemented\n";
  }
};

// 全局变量定义指令类
class RiscvGlobalVarInstruction : public RiscvInstruction {
public:
  std::string var_name;
  std::string var_type;
  std::vector<int> init_vals;
  std::vector<float> init_float_vals;
  RiscvGlobalVarInstruction(std::string name, std::string type) {
    opcode = RiscvOpcode::GLOBAL_VAR;
    var_name = std::move(name);
    var_type = std::move(type);
  }
  void PrintIR(std::ostream &s) override {
    s << "  .globl " << var_name << "\n";
    s << "  .type " << var_name << ", @object\n";
    s << var_name << ":\n";
    if (var_type == "i32") {
      if (init_vals.empty())
        s << "  .word 0\n";
      else {
        for (int val : init_vals)
          s << "  .word " << val << "\n";
      }
    } else if (var_type == "float") {
      if (init_float_vals.empty())
        s << "  .word 0\n";
      else {
        for (float val : init_float_vals) {
          // 将浮点数转换为字节表示
          union {
            float f;
            uint32_t i;
          } converter;
          converter.f = val;
          s << "  .word 0x" << std::hex << converter.i << std::dec << "\n";
        }
      }
    } else if (var_type == "string")
      s << "  .asciz \"" << var_name << "\"\n";
  }
};

class RiscvStringConstInstruction : public RiscvInstruction {
public:
  std::string str_name;
  std::string str_value;
  RiscvStringConstInstruction(std::string name, std::string value) {
    opcode = RiscvOpcode::GLOBAL_STR;
    str_name = std::move(name);
    str_value = std::move(value);
  }
  void PrintIR(std::ostream &s) override {
    s << str_name << ": .string \"" << str_value << "\"\n";
  }
};

// 函数调用指令类
class RiscvCallInstruction : public RiscvInstruction {
public:
  std::string function_name;
  std::vector<RiscvOperand *> args;
  RiscvCallInstruction(std::string name) {
    opcode = RiscvOpcode::CALL;
    function_name = std::move(name);
  }
  void AddArg(RiscvOperand *arg) { args.push_back(arg); }
  void PrintIR(std::ostream &s) override {
    s << "    call  " << function_name << "\n";
  }
};

class RiscvFcvtswInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvFcvtswInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::FCVTSW; // 使用FCVTSW伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fcvts.w.s  " << rd->GetFullName() << "," << rs1->GetFullName()
      << "\n";
  }
};

class RiscvFcvtwsInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvFcvtwsInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::FCVTWS; // 使用FCVTWS伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fcvt.w.s  " << rd->GetFullName() << "," << rs1->GetFullName()
      << ",rtz"
      << "\n";
  }
};

class RiscvBnezInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs1;
  RiscvOperand *label;
  RiscvBnezInstruction(RiscvOperand *rs1, RiscvOperand *label) {
    opcode = RiscvOpcode::BNEZ; // 使用BNEZ伪指令
    this->rs1 = rs1;
    this->label = label;
  }
  void PrintIR(std::ostream &s) override {
    s << "  bnez  " << rs1->GetFullName() << "," << label->GetFullName()
      << "\n";
  }
};

class RiscvSnezInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs1, *rs2;
  RiscvSnezInstruction(RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::SNEZ; // 使用SNEZ伪指令
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  snez  " << rs1->GetFullName() << "," << rs2->GetFullName() << "\n";
  }
};

class RiscvSeqzInstruction : public RiscvInstruction {
public:
  RiscvOperand *rs1, *rs2;
  RiscvSeqzInstruction(RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::SEQZ; // 使用SEQZ伪指令
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  seqz  " << rs1->GetFullName() << "," << rs2->GetFullName() << "\n";
  }
};

class RiscvFmvxwInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvFmvxwInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::FMVWX; // 使用FMVWX伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fmv.x.w  " << rd->GetFullName() << "," << rs1->GetFullName()
      << "\n";
  }
};

class RiscvFmvwxInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  RiscvFmvwxInstruction(RiscvOperand *rd, RiscvOperand *rs1) {
    opcode = RiscvOpcode::FADXW; // 使用FADXW伪指令
    this->rd = rd;
    this->rs1 = rs1;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fmv.w.x  " << rd->GetFullName() << "," << rs1->GetFullName()
      << "\n";
  }
};

class RiscvAndInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvAndInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::AND;
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  and  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvOrInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvOrInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::OR;
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  or  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvXorInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvXorInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::XOR;
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  xor  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvSltInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvSltInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::SLT; // 使用SLT伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  slt  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvXoriInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  int immediate;
  RiscvXoriInstruction(RiscvOperand *rd, RiscvOperand *rs1, int imm) {
    opcode = RiscvOpcode::XORI; // 使用XORI伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->immediate = imm;
  }
  void PrintIR(std::ostream &s) override {
    s << "  xori  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << immediate << "\n";
  }
};

class RiscvFeqInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFeqInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FEQ; // 使用FEQ伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  feq.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFltInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFltInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FLT; // 使用FLT伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  flt.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvFleInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1, *rs2;
  RiscvFleInstruction(RiscvOperand *rd, RiscvOperand *rs1, RiscvOperand *rs2) {
    opcode = RiscvOpcode::FLE; // 使用FLE伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->rs2 = rs2;
  }
  void PrintIR(std::ostream &s) override {
    s << "  fle.s  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << rs2->GetFullName() << "\n";
  }
};

class RiscvAndiInstruction : public RiscvInstruction {
public:
  RiscvOperand *rd, *rs1;
  int immediate;
  RiscvAndiInstruction(RiscvOperand *rd, RiscvOperand *rs1, int imm) {
    opcode = RiscvOpcode::ANDI; // 使用ANDI伪指令
    this->rd = rd;
    this->rs1 = rs1;
    this->immediate = imm;
  }
  void PrintIR(std::ostream &s) override {
    s << "  andi  " << rd->GetFullName() << "," << rs1->GetFullName() << ","
      << immediate << "\n";
  }
};
