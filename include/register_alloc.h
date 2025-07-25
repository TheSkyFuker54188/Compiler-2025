#ifndef REGISTER_ALLOC_H
#define REGISTER_ALLOC_H

#include "riscv_mir.h"
#include <map>
#include <vector>
#include <set>

// ===--------------------------------------------------------------------=== //
// 简单的寄存器分配器
// ===--------------------------------------------------------------------=== //

class SimpleRegisterAllocator {
private:
  MachineFunction* current_function;
  std::map<MachineRegister*, int> virtual_to_physical;  // 虚拟寄存器到物理寄存器的映射
  std::set<int> allocated_registers;                    // 已分配的物理寄存器
  int next_stack_slot;                                  // 下一个栈槽编号
  
  // RISC-V 寄存器定义
  static const std::vector<int> caller_saved_regs;      // 调用者保存寄存器
  static const std::vector<int> callee_saved_regs;      // 被调用者保存寄存器
  static const std::vector<int> argument_regs;          // 参数寄存器
  static const std::vector<int> temp_regs;              // 临时寄存器
  
public:
  SimpleRegisterAllocator() : current_function(nullptr), next_stack_slot(0) {}
  
  // 主要接口
  bool allocateRegisters(MachineFunction& func);
  
  // 专门处理函数参数的寄存器分配
  void allocateFunctionParameters(MachineFunction& func);
  
  // 分配物理寄存器
  int allocatePhysicalRegister(MachineRegister* vreg);
  
  // 释放物理寄存器
  void deallocatePhysicalRegister(int physical_reg);
  
  // 获取映射的物理寄存器
  int getPhysicalRegister(MachineRegister* vreg);
  
  // 溢出到栈
  int spillToStack(MachineRegister* vreg);
  
  // 插入spill代码
  void insertSpillCode(MachineBasicBlock* block, 
                      std::vector<std::unique_ptr<MachineInstruction>>::iterator pos,
                      MachineRegister* vreg, int stack_slot);
  
  // 插入reload代码
  void insertReloadCode(MachineBasicBlock* block,
                       std::vector<std::unique_ptr<MachineInstruction>>::iterator pos,
                       MachineRegister* vreg, int stack_slot);
  
private:
  // 选择要溢出的寄存器
  MachineRegister* selectSpillCandidate();
  
  // 更新指令中的寄存器
  void updateInstructionRegisters(MachineInstruction& inst);
  
  // 检查寄存器是否可用
  bool isRegisterAvailable(int physical_reg);
  
  // 获取寄存器名称
  std::string getRegisterName(int physical_reg);
};

#endif // REGISTER_ALLOC_H 