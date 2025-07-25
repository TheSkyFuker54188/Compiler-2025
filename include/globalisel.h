#ifndef GLOBALISEL_H
#define GLOBALISEL_H

#include "riscv_mir.h"
#include "instruction.h"
#include "block.h"
#include "register_alloc.h"
#include <map>
#include <unordered_map>

// ===--------------------------------------------------------------------=== //
// GlobalISel 框架定义
// ===--------------------------------------------------------------------=== //

// 寄存器组定义
enum class RISCVRegBank {
  GPR_BANK,   // 通用寄存器组
  FPR_BANK,   // 浮点寄存器组
  INVALID_BANK
};

// 操作数大小（以位为单位）
enum class OperandSize {
  s8,    // 8位
  s16,   // 16位  
  s32,   // 32位
  s64,   // 64位
  s128   // 128位
};

// 类型合法化操作
enum class LegalizeAction {
  Legal,      // 操作是合法的
  Expand,     // 展开为多个操作
  Lower,      // 降低为更简单的操作
  Custom,     // 自定义处理
  Libcall     // 使用库调用
};

// 合法化信息
struct LegalizeInfo {
  LegalizeAction action;
  RISCVOpcode new_opcode;
  OperandSize operand_size;
};

// ===--------------------------------------------------------------------=== //
// IRTranslator - 将LLVM IR转换为Generic MIR
// ===--------------------------------------------------------------------=== //

class IRTranslator {
private:
  MachineModule* machine_module;
  MachineFunction* current_function;
  MachineBasicBlock* current_block;
  std::map<int, MachineRegister*> vreg_map;  // LLVM寄存器到机器寄存器的映射
  std::map<int, MachineBasicBlock*> block_map;  // LLVM块ID到机器块的映射
  int next_mir_reg;

public:
  IRTranslator() : machine_module(nullptr), current_function(nullptr), 
                   current_block(nullptr), next_mir_reg(0) {}
  
  // 主要接口
  bool translateModule(const LLVMIR& llvm_ir, MachineModule& mir_module);
  
private:
  // 翻译函数
  bool translateFunction(const FuncDefInstruction& func, 
                        const std::map<int, LLVMBlock>& blocks);
  
  // 翻译基本块
  bool translateBasicBlock(LLVMBlock llvm_block);
  
  // 翻译指令
  bool translateInstruction(const Instruction& inst);
  
  // 具体指令翻译
  void translateAdd(const BasicInstruction* inst);
  void translateSub(const BasicInstruction* inst);
  void translateMul(const BasicInstruction* inst);
  void translateDiv(const BasicInstruction* inst);
  
  // 浮点运算翻译方法
  void translateFadd(const BasicInstruction* inst);
  void translateFsub(const BasicInstruction* inst);
  void translateFmul(const BasicInstruction* inst);
  void translateFdiv(const BasicInstruction* inst);
  void translateLoad(const LoadInstruction* inst);
  void translateStore(const StoreInstruction* inst);
  void translateCall(const CallInstruction* inst);
  void translateRet(const RetInstruction* inst);
  void translateIcmp(const IcmpInstruction* inst);
  void translateFcmp(const FcmpInstruction* inst);
  void translateBr(const BasicInstruction* inst);
  void translateAlloca(const Instruction& inst);
  void translateGep(const GetElementptrInstruction* inst);
  void translateAnd(const BasicInstruction* inst);
  void translateOr(const BasicInstruction* inst);
  void translateXor(const BasicInstruction* inst);
  void translateMod(const BasicInstruction* inst);
  void translateZext(const BasicInstruction* inst);
  void translateFptosi(const BasicInstruction* inst);
  void translateSitofp(const BasicInstruction* inst);
  
  // 辅助方法
  MachineRegister* getOrCreateVReg(int llvm_reg, RISCVRegClass reg_class);
  MachineRegister* getOrCreateVRegForOperand(Operand llvm_operand);
  MachineOperand translateOperand(Operand llvm_operand);
  RISCVRegClass getRegClassForType(LLVMType type);
  RISCVOpcode getGenericOpcode(LLVMIROpcode llvm_op);
  int getOperandRegNumber(Operand operand);
  void setupFunctionParameters(const FuncDefInstruction& func);
  int calculateArraySize(const AllocaInstruction* alloca_inst);
  int inferElementSize(LLVMType type);
  int getTypeAlignment(LLVMType type);
};

// ===--------------------------------------------------------------------=== //
// Legalizer - 将不合法的操作和类型合法化
// ===--------------------------------------------------------------------=== //

class RISCVLegalizer {
private:
  MachineFunction* current_function;
  std::map<std::pair<RISCVOpcode, OperandSize>, LegalizeInfo> legalize_table;
  
public:
  RISCVLegalizer();
  
  // 主要接口
  bool legalizeFunction(MachineFunction& func);
  
  // 判断操作是否合法
  bool isLegal(RISCVOpcode opcode, OperandSize size) const;
  LegalizeInfo getLegalizeInfo(RISCVOpcode opcode, OperandSize size) const;
  
private:
  // 初始化合法化表
  void initLegalizeTable();
  
  // 合法化操作
  bool legalizeInstruction(MachineInstruction& inst);
  bool expandInstruction(MachineInstruction& inst);
  bool lowerInstruction(MachineInstruction& inst);
  
  // 类型合法化
  OperandSize getTypeSize(RISCVOpcode opcode) const;
  bool needsPromotion(OperandSize current, OperandSize target) const;
  bool needsTruncation(OperandSize current, OperandSize target) const;
};

// ===--------------------------------------------------------------------=== //
// RegBankSelect - 为操作数选择寄存器组
// ===--------------------------------------------------------------------=== //

class RISCVRegBankSelect {
private:
  MachineFunction* current_function;
  std::map<MachineRegister*, RISCVRegBank> reg_bank_map;
  
public:
  RISCVRegBankSelect() : current_function(nullptr) {}
  
  // 主要接口
  bool assignRegBanks(MachineFunction& func);
  
  // 获取寄存器组
  RISCVRegBank getRegBank(MachineRegister* reg) const;
  void setRegBank(MachineRegister* reg, RISCVRegBank bank);
  
private:
  // 为指令选择寄存器组
  bool selectRegBankForInstruction(MachineInstruction& inst);
  
  // 操作码到寄存器组的映射
  RISCVRegBank getDefaultRegBank(RISCVOpcode opcode) const;
  bool isFloatingPointOp(RISCVOpcode opcode) const;
  
  // 插入寄存器组转换指令（如果需要）
  void insertCopyIfNeeded(MachineRegister* src, MachineRegister* dst);
};

// ===--------------------------------------------------------------------=== //
// InstructionSelect - 将通用操作转换为RISC-V特定指令
// ===--------------------------------------------------------------------=== //

class RISCVInstructionSelect {
private:
  MachineFunction* current_function;
  MachineBasicBlock* current_block;
  std::map<RISCVOpcode, std::vector<RISCVOpcode>> selection_patterns;
  
public:
  RISCVInstructionSelect() : current_function(nullptr), current_block(nullptr) {}
  
  // 主要接口
  bool selectInstructions(MachineFunction& func);
  
private:
  // 初始化选择模式
  void initSelectionPatterns();
  
  // 选择具体指令
  bool selectInstruction(MachineInstruction& inst);
  
  // 具体指令选择方法
  bool selectAdd(MachineInstruction& inst);
  bool selectSub(MachineInstruction& inst);
  bool selectMul(MachineInstruction& inst);
  bool selectDiv(MachineInstruction& inst);
  bool selectLoad(MachineInstruction& inst);
  bool selectStore(MachineInstruction& inst);
  bool selectBranch(MachineInstruction& inst);
  bool selectCall(MachineInstruction& inst);
  bool selectRet(MachineInstruction& inst);
  bool selectCmp(MachineInstruction& inst);
  bool selectIntCmp(MachineInstruction& inst, IcmpCond condition);
  bool selectFloatCmp(MachineInstruction& inst, FcmpCond condition);
  bool calculateMultiDimOffset(const std::vector<MachineOperand>& indexes, 
                               const std::vector<int64_t>& dims,
                               const MachineOperand& element_size,
                               int64_t& total_offset);
  bool selectConstant(MachineInstruction& inst);
  bool selectCopy(MachineInstruction& inst);
  bool selectStackAddr(MachineInstruction& inst);
  bool selectGep(MachineInstruction& inst);
  bool selectAnd(MachineInstruction& inst);
  bool selectOr(MachineInstruction& inst);
  bool selectXor(MachineInstruction& inst);
  bool selectShl(MachineInstruction& inst);
  bool selectShr(MachineInstruction& inst);
  
  // 浮点指令选择方法
  bool selectFadd(MachineInstruction& inst);
  bool selectFsub(MachineInstruction& inst);
  bool selectFmul(MachineInstruction& inst);
  bool selectFdiv(MachineInstruction& inst);
  
  // 立即数优化
  bool canUseImmediate(int64_t value, RISCVOpcode opcode) const;
  bool is12BitImm(int64_t value) const;
  bool is20BitImm(int64_t value) const;
  
  // 地址模式选择
  bool selectAddressingMode(MachineOperand& addr, MachineOperand& base, 
                           MachineOperand& offset);
};

// ===--------------------------------------------------------------------=== //
// RISC-V 物理寄存器定义
// ===--------------------------------------------------------------------=== //

class RISCVPhysicalRegisters {
public:
  // 通用寄存器
  static const int X0 = 0;   // 零寄存器
  static const int X1 = 1;   // 返回地址
  static const int X2 = 2;   // 栈指针
  static const int X3 = 3;   // 全局指针
  static const int X4 = 4;   // 线程指针
  static const int X5 = 5;   // 临时寄存器
  static const int X6 = 6;   // 临时寄存器
  static const int X7 = 7;   // 临时寄存器
  static const int X8 = 8;   // 保存寄存器/帧指针
  static const int X9 = 9;   // 保存寄存器
  static const int X10 = 10; // 参数/返回值寄存器
  static const int X11 = 11; // 参数/返回值寄存器
  static const int X12 = 12; // 参数寄存器
  static const int X13 = 13; // 参数寄存器
  static const int X14 = 14; // 参数寄存器
  static const int X15 = 15; // 参数寄存器
  static const int X16 = 16; // 参数寄存器
  static const int X17 = 17; // 参数寄存器
  
  // 浮点寄存器
  static const int F0 = 0;   // 临时寄存器
  static const int F1 = 1;   // 临时寄存器
  static const int F10 = 10; // 参数/返回值寄存器
  static const int F11 = 11; // 参数/返回值寄存器
  
  // 寄存器别名
  static const int ZERO = X0; // 零寄存器
  static const int RA = X1;   // 返回地址
  static const int SP = X2;   // 栈指针
  static const int GP = X3;   // 全局指针
  static const int TP = X4;   // 线程指针
  static const int FP = X8;   // 帧指针
  
  // 获取寄存器名称
  static std::string getGPRName(int reg_num);
  static std::string getFPRName(int reg_num);
  
  // 寄存器分类
  static bool isCallerSaved(int reg_num);
  static bool isCalleeSaved(int reg_num);
  static bool isArgumentReg(int reg_num);
  static bool isReturnReg(int reg_num);
};

// ===--------------------------------------------------------------------=== //
// GlobalISel 主控制器
// ===--------------------------------------------------------------------=== //

class RISCVGlobalISel {
private:
  IRTranslator translator;
  RISCVLegalizer legalizer;
  RISCVRegBankSelect reg_bank_selector;
  RISCVInstructionSelect instruction_selector;
  SimpleRegisterAllocator register_allocator;
  
public:
  RISCVGlobalISel() = default;
  
  // 主要接口 - 执行完整的GlobalISel流程
  bool runGlobalISel(const LLVMIR& llvm_ir, MachineModule& mir_module);
  
  // 执行到InstructionSelect阶段（用于生成MIR文件）
  bool runGlobalISelToInstructionSelect(const LLVMIR& llvm_ir, MachineModule& mir_module);
  
  // 分阶段执行
  bool runIRTranslation(const LLVMIR& llvm_ir, MachineModule& mir_module);
  bool runLegalizer(MachineModule& mir_module);
  bool runRegBankSelect(MachineModule& mir_module);
  bool runInstructionSelect(MachineModule& mir_module);
  bool runRegisterAllocation(MachineModule& mir_module);
  
  // 调试和验证
  void dumpMIR(const MachineModule& mir_module, const std::string& stage) const;
  bool verifyMIR(const MachineModule& mir_module) const;
};

#endif // GLOBALISEL_H 