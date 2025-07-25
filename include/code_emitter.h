#ifndef CODE_EMITTER_H
#define CODE_EMITTER_H

#include "riscv_mir.h"
#include <iostream>
#include <string>

// ===--------------------------------------------------------------------=== //
// RISC-V 代码发射器
// ===--------------------------------------------------------------------=== //

class RISCVCodeEmitter {
private:
  std::ostream* output_stream;
  
public:
  RISCVCodeEmitter(std::ostream& os) : output_stream(&os) {}
  
  // 主要接口
  void emitModule(const MachineModule& module);
  void emitFunction(const MachineFunction& func);
  void emitBasicBlock(const MachineBasicBlock& block);
  void emitBasicBlockWithEpilogueHandling(const MachineBasicBlock& block, const MachineFunction& func);
  void emitInstruction(const MachineInstruction& inst);
  
  // 函数序言和尾声
  void emitFunctionPrologue(const MachineFunction& func);
  void emitFunctionEpilogue(const MachineFunction& func);
  
  // 汇编格式化方法
  void emitHeader();
  void emitFunctionLabel(const std::string& name);
  void emitBlockLabel(int block_id);
  
  // 指令格式化
  std::string formatInstruction(const MachineInstruction& inst);
  std::string formatOperand(const MachineOperand& operand);
  std::string formatRegister(const MachineRegister& reg);
  
  // 汇编指示符
  void emitTextSection();
  void emitDataSection();
  void emitGlobalDirective(const std::string& symbol);
  void emitComment(const std::string& comment);
  
private:
  // 指令特殊处理
  bool needsSpecialHandling(const MachineInstruction& inst);
  void handleSpecialInstruction(const MachineInstruction& inst);
  
  // 寄存器名称转换
  std::string getPhysicalRegisterName(int reg_num);
  
  // 立即数处理
  std::string formatImmediate(int64_t value);
  std::string formatFloatImmediate(float value);
  
  // 地址格式化
  std::string formatAddress(const MachineOperand& base, const MachineOperand& offset);
};

#endif // CODE_EMITTER_H 