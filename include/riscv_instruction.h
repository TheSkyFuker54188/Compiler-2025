#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// RISC-V 指令操作码
enum class RiscvOpcode {
  // 算术运算指令
  ADDI, // 立即数加法
  ADD,  // 寄存器加法
  SUB,  // 减法
  SUBI, // 立即数减法
  MUL,  // 乘法
  MULW, // 32位乘法
  DIV,  // 除法
  DIVW, // 32位除法
  REM,  // 求余
  REMW, // 32位求余

  // 逻辑运算指令
  AND,  // 按位与
  ANDI, // 立即数按位与
  OR,   // 按位或
  ORI,  // 立即数按位或
  XOR,  // 按位异或
  XORI, // 立即数按位异或

  // 移位指令
  SLL,  // 逻辑左移
  SLLI, // 立即数逻辑左移
  SRL,  // 逻辑右移
  SRLI, // 立即数逻辑右移
  SRA,  // 算术右移
  SRAI, // 立即数算术右移

  // 比较指令
  SLT,   // 有符号小于
  SLTI,  // 有符号小于立即数
  SLTU,  // 无符号小于
  SLTIU, // 无符号小于立即数

  // 浮点运算指令
  FADD_S, // 单精度浮点加法
  FSUB_S, // 单精度浮点减法
  FMUL_S, // 单精度浮点乘法
  FDIV_S, // 单精度浮点除法

  // 浮点比较指令
  FEQ_S, // 单精度浮点相等比较
  FLT_S, // 单精度浮点小于比较
  FLE_S, // 单精度浮点小于等于比较

  // 内存访问指令
  LW, // 加载字
  LH, // 加载半字
  LB, // 加载字节
  SW, // 存储字
  SH, // 存储半字
  SB, // 存储字节
  FLW, // 浮点加载字
  FSW, // 浮点存储字

  // 分支指令
  BEQ,  // 相等分支
  BNE,  // 不等分支
  BLT,  // 小于分支
  BGE,  // 大于等于分支
  BLTU, // 无符号小于分支
  BGEU, // 无符号大于等于分支

  // 跳转指令
  JAL,  // 跳转并链接
  JALR, // 寄存器跳转并链接

  // 类型转换指令
  FCVT_S_W, // 整数转单精度浮点
  FCVT_W_S, // 单精度浮点转整数

  // 伪指令
  LI,  // 加载立即数
  LA,  // 加载地址
  MV,  // 移动
  NOP, // 空操作

  // 全局变量定义
  GLOBAL_VAR,
  GLOBAL_STR,

  // 函数相关
  CALL,   // 函数调用
  RET     // 返回
};

class RiscvOperand {
public:
  enum operand_type {
    REG = 1,
    IMMI32 = 2,
    IMMF32 = 3,
    GLOBAL = 4,
    LABEL = 5,
    DRAM = 6
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
      if (physical_reg == 0) return "zero";
      if (physical_reg == 1) return "ra";
      if (physical_reg == 2) return "sp";
      if (physical_reg == 3) return "gp";
      if (physical_reg == 4) return "tp";
      if (physical_reg >= 5 && physical_reg <= 7) return "t" + std::to_string(physical_reg - 5);
      if (physical_reg >= 8 && physical_reg <= 9) return "s" + std::to_string(physical_reg - 8);
      if (physical_reg >= 10 && physical_reg <= 17) return "a" + std::to_string(physical_reg - 10);
      if (physical_reg >= 18 && physical_reg <= 27) return "s" + std::to_string(physical_reg - 16);
      if (physical_reg >= 28 && physical_reg <= 31) return "t" + std::to_string(physical_reg - 25);
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
  
  std::string GetFullName() override {
    return std::to_string(immVal);
  }
  
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
  
  std::string GetFullName() override {
    return std::to_string(immVal);
  }
  
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
  
  std::string GetFullName() override {
    return global_name;
  }
  
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
  
  std::string GetFullName() override {
    return label_name;
  }
  
  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvLabelOperand>(label_name);
  }
};

class RiscvDramOperand : public RiscvOperand {
public:
  int offset;
  std::unique_ptr<RiscvOperand> base_reg;
  
  RiscvDramOperand(int offset, std::unique_ptr<RiscvOperand> base) {
    operandType = DRAM;
    this->offset = offset;
    this->base_reg = std::move(base);
  }
  
  std::string GetFullName() override {
    return std::to_string(offset) + "(" + base_reg->GetFullName() + ")";
  }
  
  std::unique_ptr<RiscvOperand> CopyOperand() override {
    return std::make_unique<RiscvDramOperand>(offset, base_reg->CopyOperand());
  }
};

class RiscvInstruction {
public:
  RiscvOpcode opcode;
  
  virtual ~RiscvInstruction() = default;
  virtual void PrintIR(std::ostream &s) = 0;
  virtual RiscvOpcode GetOpcode() { return opcode; }
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
  
  void PrintIR(std::ostream &s) override;
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
  
  void PrintIR(std::ostream &s) override;
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