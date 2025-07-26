#pragma once

#include "block.h"
#include "riscv_instruction.h"
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>

class RiscvBlock {
public:
  std::string comment; // used for debug
  int block_id = 0;
  int stack_size = 0; // Stack size for this block
  std::deque<std::unique_ptr<RiscvInstruction>> instruction_list;

  void InsertInstruction(int pos, std::unique_ptr<RiscvInstruction> ins);
  void print(std::ostream &s);
  RiscvBlock(int id) : block_id(id) {}
};

// 栈帧信息结构
struct StackFrameInfo {
  int local_vars_size = 16;  // 局部变量占用的栈空间
  int call_args_size = 0;    // 函数调用参数传递区大小
  int alignment_padding = 0; // 对齐填充
  int total_frame_size = 0;  // 总栈帧大小

  // 局部变量信息
  std::map<int, int> var_offsets; // 虚拟寄存器到栈偏移的映射

  void calculateTotalSize() {
    // RISC-V要求栈指针16字节对齐
    int unaligned_size = local_vars_size + call_args_size;
    alignment_padding = (16 - (unaligned_size % 16)) % 16;
    total_frame_size = unaligned_size + alignment_padding;
  }
};

class Riscv {
public:
  std::string file_name; // 输出文件名
  std::vector<std::unique_ptr<RiscvInstruction>> global_def;
  std::vector<std::unique_ptr<RiscvInstruction>> function_declare;
  std::map<std::string, std::map<int, std::unique_ptr<RiscvBlock>>>
      function_block_map; //<function,<id,block> >
  void print(std::ostream &s);
};

class Translator {
public:
  Translator(std::string file) { riscv.file_name = std::move(file); }
  Riscv riscv;
  void translate(const LLVMIR &llvmir);

private:
  // 当前正在翻译的函数
  std::string current_function;
  // 栈帧管理
  std::map<std::string, StackFrameInfo>
      function_stack_frames;                     // 每个函数的栈帧信息
  StackFrameInfo *current_stack_frame = nullptr; // 当前函数的栈帧信息

  // 翻译方法
  void translateGlobal(const std::vector<Instruction> &global_def);
  void translateFunctions(const LLVMIR &llvmir);
  void translateFunction(FuncDefInstruction func,
                         const std::map<int, LLVMBlock> &blocks);
  void analyzeFunction(const std::map<int, LLVMBlock> &blocks);
  void analyzeInstruction(Instruction inst);
  void translateBlock(LLVMBlock block, RiscvBlock *riscv_block);
  void translateInstruction(Instruction inst, RiscvBlock *riscv_block);

  // 操作数翻译
  std::unique_ptr<RiscvOperand> translateOperand(Operand op);

  // 物理寄存器创建辅助方法
  std::unique_ptr<RiscvRegOperand> createVirtualReg();
  std::unique_ptr<RiscvRegOperand> createVirtualReg(int reg_no);

  // 指令翻译
  void translateLoad(LoadInstruction *inst, RiscvBlock *block);
  void translateStore(StoreInstruction *inst, RiscvBlock *block);
  void translateBranch(Instruction inst, RiscvBlock *block);
  void translateCall(CallInstruction *inst, RiscvBlock *block);
  void translateReturn(RetInstruction *inst, RiscvBlock *block);
  void translateIcmp(IcmpInstruction *inst, RiscvBlock *block);
  void translateFcmp(FcmpInstruction *inst, RiscvBlock *block);
  void translateAdd(Instruction inst, RiscvBlock *block);
  void translateSub(Instruction inst, RiscvBlock *block);
  void translateMul(Instruction inst, RiscvBlock *block);
  void translateDiv(Instruction inst, RiscvBlock *block);
  void translateMod(Instruction inst, RiscvBlock *block);
  void translateFadd(Instruction inst, RiscvBlock *block);
  void translateFsub(Instruction inst, RiscvBlock *block);
  void translateFmul(Instruction inst, RiscvBlock *block);
  void translateFdiv(Instruction inst, RiscvBlock *block);

  // 工具方法
  std::string getLLVMTypeString(LLVMType type);

  // 栈帧管理方法
  void initFunctionStackFrame(const std::string &func_name);
  void addLocalVariable(int virtual_reg, LLVMType type);
  void addLocalArray(int virtual_reg, LLVMType type,
                     const std::vector<int> &dims);
  void updateCallArgsSize(int num_args);
  void finalizeFunctionStackFrame();
  void generateStackFrameProlog(RiscvBlock *entry_block);
  void generateStackFrameEpilog(RiscvBlock *exit_block);
  int getLocalVariableOffset(int virtual_reg);
  int getTypeSize(LLVMType type);

public:
  // 栈帧信息查询（公开API）
  const StackFrameInfo *
  getFunctionStackFrame(const std::string &func_name) const;
  int getCurrentFrameSize() const;
};