#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// RISC-V 指令操作码
enum class RiscvOpcode {
  ADDI, // 立即数加法
  ADD,  // 寄存器加法
  SD,
  LI,
  GLOBAL_VAR,
  CALL,
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
  virtual std::unique_ptr<RiscvOperand> CopyOperand() = 0;
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
      if (physical_reg == 0)
        return "zero";
      if (physical_reg == 1)
        return "ra";
      if (physical_reg == 2)
        return "sp";
      if (physical_reg == 3)
        return "gp";
      if (physical_reg == 4)
        return "tp";
      if (physical_reg >= 5 && physical_reg <= 7)
        return "t" + std::to_string(physical_reg - 5);
      if (physical_reg >= 8 && physical_reg <= 9)
        return "s" + std::to_string(physical_reg - 8);
      if (physical_reg >= 10 && physical_reg <= 17)
        return "a" + std::to_string(physical_reg - 10);
      if (physical_reg >= 18 && physical_reg <= 27)
        return "s" + std::to_string(physical_reg - 16);
      if (physical_reg >= 28 && physical_reg <= 31)
        return "t" + std::to_string(physical_reg - 25);
      return "x" + std::to_string(physical_reg);
    } else {
      // 虚拟寄存器使用%r前缀
      return "%r" + std::to_string(reg_no);
    }
  }

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvRegOperand>(reg_no);
  }
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

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvImmI32Operand>(immVal);
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

  std::string GetFullName() override { return std::to_string(immVal); }

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvImmF32Operand>(immVal);
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

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvGlobalOperand>(global_name);
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

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvLabelOperand>(label_name);
  }
};

class RiscvPtrOperand : public RiscvOperand {
public:
  int offset;
  std::unique_ptr<RiscvOperand> base_reg;

  RiscvPtrOperand(int offset, std::unique_ptr<RiscvOperand> base) {
    operandType = PTR;
    this->offset = offset;
    this->base_reg = std::move(base);
  }

  std::string GetFullName() override {
    return std::to_string(offset) + "(" + base_reg->GetFullName() + ")";
  }

  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvPtrOperand>(offset, base_reg->CopyOperand());
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
  std::unique_ptr<RiscvOperand> rd, rs1;
  int immediate;

  RiscvAddiInstruction(std::unique_ptr<RiscvOperand> rd,
                       std::unique_ptr<RiscvOperand> rs1, int imm) {
    opcode = RiscvOpcode::ADDI;
    this->rd = std::move(rd);
    this->rs1 = std::move(rs1);
    this->immediate = imm;
  }

  void PrintIR(std::ostream &s) override {
    s << "addi " << rd->GetFullName() << ", " << rs1->GetFullName() << ", "
      << immediate << "\n";
  }
};

class RiscvAddInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd, rs1, rs2;

  RiscvAddInstruction(std::unique_ptr<RiscvOperand> rd,
                      std::unique_ptr<RiscvOperand> rs1,
                      std::unique_ptr<RiscvOperand> rs2) {
    opcode = RiscvOpcode::ADD;
    this->rd = std::move(rd);
    this->rs1 = std::move(rs1);
    this->rs2 = std::move(rs2);
  }

  void PrintIR(std::ostream &s) override {
    s << "add " << rd->GetFullName() << ", " << rs1->GetFullName() << ", "
      << rs2->GetFullName() << "\n";
  }
};

class RiscvSdInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> reg;
  std::unique_ptr<RiscvOperand> address;

  RiscvSdInstruction(std::unique_ptr<RiscvOperand> reg,
                     std::unique_ptr<RiscvOperand> address) {
    opcode = RiscvOpcode::SD;
    this->reg = std::move(reg);
    this->address = std::move(address);
  }

  void PrintIR(std::ostream &s) override {
    s << "sd " << reg->GetFullName() << ", " << address->GetFullName() << "\n";
  }
};

class RiscvLiInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd;
  int imm;
  RiscvLiInstruction(std::unique_ptr<RiscvOperand> rd, int imm) {
    opcode = RiscvOpcode::LI; // 使用LI伪指令
    this->rd = std::move(rd);
    this->imm = imm;
  }
};

// 算术指令类
class RiscvArithmeticInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd, rs1, rs2;

  RiscvArithmeticInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> rd,
                             std::unique_ptr<RiscvOperand> rs1,
                             std::unique_ptr<RiscvOperand> rs2) {
    opcode = op;
    this->rd = std::move(rd);
    this->rs1 = std::move(rs1);
    this->rs2 = std::move(rs2);
  }

  void PrintIR(std::ostream &s) override;
};

// 立即数算术指令类
class RiscvImmediateInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd, rs1;
  int immediate;

  RiscvImmediateInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> rd,
                            std::unique_ptr<RiscvOperand> rs1, int imm) {
    opcode = op;
    this->rd = std::move(rd);
    this->rs1 = std::move(rs1);
    this->immediate = imm;
  }

  void PrintIR(std::ostream &s) override;
};

// 内存访问指令类
class RiscvMemoryInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> reg;
  std::unique_ptr<RiscvOperand> address;

  RiscvMemoryInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> reg,
                         std::unique_ptr<RiscvOperand> addr) {
    opcode = op;
    this->reg = std::move(reg);
    this->address = std::move(addr);
  }

  void PrintIR(std::ostream &s) override;
};

// 分支指令类
class RiscvBranchInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rs1, rs2;
  std::unique_ptr<RiscvOperand> label;

  RiscvBranchInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> rs1,
                         std::unique_ptr<RiscvOperand> rs2,
                         std::unique_ptr<RiscvOperand> label) {
    opcode = op;
    this->rs1 = std::move(rs1);
    this->rs2 = std::move(rs2);
    this->label = std::move(label);
  }

  void PrintIR(std::ostream &s) override;
};

// 跳转指令类
class RiscvJumpInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd;
  std::unique_ptr<RiscvOperand> target;

  RiscvJumpInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> rd,
                       std::unique_ptr<RiscvOperand> target) {
    opcode = op;
    this->rd = std::move(rd);
    this->target = std::move(target);
  }

  void PrintIR(std::ostream &s) override;
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
    s << ".globl " << var_name << "\n";
    s << var_name << ":\n";
    if (var_type == "i32") {
      if (init_vals.empty())
        s << "    .word 0\n";
      else {
        for (int val : init_vals)
          s << "    .word " << val << "\n";
      }
    } else if (var_type == "float") {
      if (init_float_vals.empty())
        s << "    .word 0\n";
      else {
        for (float val : init_float_vals) {
          // 将浮点数转换为字节表示
          union {
            float f;
            uint32_t i;
          } converter;
          converter.f = val;
          s << "    .word 0x" << std::hex << converter.i << std::dec << "\n";
        }
      }
    } else if (var_type == "string")
      s << "    .asciz \"" << var_name << "\"\n";
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
};

// 函数调用指令类
class RiscvCallInstruction : public RiscvInstruction {
public:
  std::string function_name;
  std::vector<std::unique_ptr<RiscvOperand>> args;

  RiscvCallInstruction(std::string name) {
    opcode = RiscvOpcode::CALL;
    function_name = std::move(name);
  }

  void AddArg(std::unique_ptr<RiscvOperand> arg) {
    args.push_back(std::move(arg));
  }

  void PrintIR(std::ostream &s) override {
    s << "    call " << function_name << "\n";
  }
};

// 伪指令类
class RiscvPseudoInstruction : public RiscvInstruction {
public:
  std::unique_ptr<RiscvOperand> rd;
  std::unique_ptr<RiscvOperand> operand;

  RiscvPseudoInstruction(RiscvOpcode op, std::unique_ptr<RiscvOperand> rd,
                         std::unique_ptr<RiscvOperand> operand = nullptr) {
    opcode = op;
    this->rd = std::move(rd);
    this->operand = std::move(operand);
  }

  void PrintIR(std::ostream &s) override;
};