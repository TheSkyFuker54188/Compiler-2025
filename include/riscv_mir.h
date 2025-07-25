#ifndef RISCV_MIR_H
#define RISCV_MIR_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <cstring>

// RISC-V Machine IR 基础定义

// Machine Register 类型
enum class MRegType {
  VIRTUAL,      // 虚拟寄存器
  PHYSICAL,     // 物理寄存器
  IMMEDIATE     // 立即数
};

// RISC-V 寄存器类别
enum class RISCVRegClass {
  GPR,    // General Purpose Registers (x0-x31)
  FPR,    // Floating Point Registers (f0-f31)
  CSR     // Control and Status Registers
};

// RISC-V 指令操作码
enum class RISCVOpcode {
  // 通用机器操作码
  G_ADD,        // 通用加法
  G_SUB,        // 通用减法
  G_MUL,        // 通用乘法
  G_DIV,        // 通用除法
  G_AND,        // 通用与
  G_OR,         // 通用或
  G_XOR,        // 通用异或
  G_SHL,        // 通用左移
  G_SHR,        // 通用右移
  G_LOAD,       // 通用加载
  G_STORE,      // 通用存储
  G_ICMP,       // 通用整数比较
  G_FCMP,       // 通用浮点比较
  
  // 浮点运算指令
  G_FADD,       // 浮点加法
  G_FSUB,       // 浮点减法
  G_FMUL,       // 浮点乘法
  G_FDIV,       // 浮点除法
  G_BR,         // 通用分支
  G_PHI,        // 通用PHI节点
  G_COPY,       // 通用拷贝
  G_CONSTANT,   // 通用常量
  G_CALL,       // 通用函数调用
  G_RET,        // 通用返回
  G_STACK_ADDR, // 栈地址计算
  G_GEP,        // 通用地址计算 (GetElementPtr)
  
  // RISC-V 特定指令
  ADDI,         // 立即数加法
  ADD,          // 寄存器加法
  SUB,          // 减法
  SUBI,         // 立即数减法
  MUL,          // 乘法
  MULW,         // 32位乘法
  DIV,          // 除法
  DIVW,         // 32位除法
  REM,          // 求余
  REMW,         // 32位求余
  
  AND,          // 按位与
  ANDI,         // 立即数按位与
  OR,           // 按位或
  ORI,          // 立即数按位或
  XOR,          // 按位异或
  XORI,         // 立即数按位异或
  
  SLL,          // 逻辑左移
  SLLI,         // 立即数逻辑左移
  SRL,          // 逻辑右移
  SRLI,         // 立即数逻辑右移
  SRA,          // 算术右移
  SRAI,         // 立即数算术右移
  
  // 比较指令
  SLT,          // 有符号小于
  SLTI,         // 有符号小于立即数
  SLTU,         // 无符号小于
  SLTIU,        // 无符号小于立即数
  
  // 浮点运算指令
  FADD_S,       // 单精度浮点加法
  FSUB_S,       // 单精度浮点减法
  FMUL_S,       // 单精度浮点乘法
  FDIV_S,       // 单精度浮点除法
  FLW,          // 浮点加载字
  FSW,          // 浮点存储字
  
  // 浮点比较指令
  FEQ_S,        // 单精度浮点相等比较
  FLT_S,        // 单精度浮点小于比较
  FLE_S,        // 单精度浮点小于等于比较
  
  LW,           // 加载字
  LH,           // 加载半字
  LB,           // 加载字节
  SW,           // 存储字
  SH,           // 存储半字
  SB,           // 存储字节
  
  BEQ,          // 相等分支
  BNE,          // 不等分支
  BLT,          // 小于分支
  BGE,          // 大于等于分支
  BLTU,         // 无符号小于分支
  BGEU,         // 无符号大于等于分支
  
  JAL,          // 跳转并链接
  JALR,         // 寄存器跳转并链接
  
  // 伪指令
  LI,           // 加载立即数
  LA,           // 加载地址
  MV,           // 移动
  NOP           // 空操作
};

// Machine Register 表示
class MachineRegister {
public:
  MRegType type;
  RISCVRegClass reg_class;
  int reg_num;
  
  MachineRegister(MRegType t, RISCVRegClass rc, int num) 
    : type(t), reg_class(rc), reg_num(num) {}
  
  std::string getName() const;
  bool isVirtual() const { return type == MRegType::VIRTUAL; }
  bool isPhysical() const { return type == MRegType::PHYSICAL; }
};

// Machine Operand 表示
class MachineOperand {
public:
  enum Type {
    REG,        // 寄存器操作数
    IMM,        // 整数立即数操作数
    FIMM,       // 浮点立即数操作数
    LABEL,      // 标签操作数
    GLOBAL,     // 全局变量操作数
    STACK_SLOT  // 栈槽操作数
  } type;
  
  union {
    MachineRegister* reg;
    int64_t imm;
    float fimm;
    int label_id;
    std::string* global_name;
    int stack_slot;
  };
  
  MachineOperand(MachineRegister* r) : type(REG), reg(r) {}
  MachineOperand(int64_t i) : type(IMM), imm(i) {}
  MachineOperand(float f) : type(FIMM), fimm(f) {}
  MachineOperand(const std::string& name) : type(GLOBAL), global_name(new std::string(name)) {}
  MachineOperand(int label) : type(LABEL), label_id(label) {}
  
  // 栈槽构造函数
  static MachineOperand createStackSlot(int slot) {
    MachineOperand operand(static_cast<int64_t>(0));  // 临时初始化
    operand.type = STACK_SLOT;
    operand.stack_slot = slot;
    return operand;
  }
  
  std::string toString() const;
  bool isReg() const { return type == REG; }
  bool isImm() const { return type == IMM; }
  bool isFimm() const { return type == FIMM; }
  bool isLabel() const { return type == LABEL; }
};

// Machine Instruction 表示
class MachineInstruction {
public:
  RISCVOpcode opcode;
  std::vector<MachineOperand> operands;
  int instruction_id;
  
  MachineInstruction(RISCVOpcode op, int id = -1) : opcode(op), instruction_id(id) {}
  
  void addOperand(const MachineOperand& op);
  void setOperands(const std::vector<MachineOperand>& ops);
  std::string toString() const;
  std::string toMIRString() const;  // 专门用于MIR调试输出
  
private:
  std::string opcodeToString(RISCVOpcode op) const;
};

// Machine Basic Block 表示
class MachineBasicBlock {
public:
  int block_id;
  std::vector<std::unique_ptr<MachineInstruction>> instructions;
  std::vector<MachineBasicBlock*> predecessors;
  std::vector<MachineBasicBlock*> successors;
  
  MachineBasicBlock(int id) : block_id(id) {}
  
  void addInstruction(std::unique_ptr<MachineInstruction> inst);
  void addSuccessor(MachineBasicBlock* succ);
  void print(std::ostream& os) const;
  void printMIR(std::ostream& os) const;  // MIR专用打印
};

// Machine Function 表示
class MachineFunction {
public:
  std::string name;
  std::vector<std::unique_ptr<MachineBasicBlock>> basic_blocks;
  std::map<int, MachineBasicBlock*> block_map;
  int next_vreg_num;
  int next_block_id;
  
  // 栈管理
  int stack_size;           // 当前栈帧大小
  int next_stack_slot;      // 下一个可用栈槽偏移
  
  MachineFunction(const std::string& func_name) 
    : name(func_name), next_vreg_num(0), next_block_id(0), 
      stack_size(0), next_stack_slot(0) {}
  
  MachineBasicBlock* createBasicBlock();
  MachineRegister* createVirtualRegister(RISCVRegClass reg_class);
  
  // 栈管理方法
  int allocateStackSlot(int size);  // 分配栈槽，返回偏移量
  
  void print(std::ostream& os) const;
  void printMIR(std::ostream& os) const;  // MIR专用打印
};

// Machine Module 表示
class MachineModule {
public:
  std::vector<std::unique_ptr<MachineFunction>> functions;
  std::map<std::string, MachineFunction*> function_map;
  
  // 全局变量存储
  struct GlobalVariable {
    std::string name;
    int64_t value;  // 支持整数初始化值
    enum { INT, FLOAT } type;
    
    GlobalVariable(const std::string& n, int64_t v) : name(n), value(v), type(INT) {}
    GlobalVariable(const std::string& n, float v) : name(n), type(FLOAT) {
      // 将float转换为int64_t存储（位级别转换）
      memcpy(&value, &v, sizeof(float));
    }
  };
  
  std::vector<GlobalVariable> global_variables;
  
  MachineFunction* createFunction(const std::string& name);
  void addGlobalVariable(const std::string& name, int64_t value);
  void addGlobalVariable(const std::string& name, float value);
  void print(std::ostream& os) const;
  void printMIR(std::ostream& os) const;  // MIR专用打印
};

#endif // RISCV_MIR_H