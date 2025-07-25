#include "../include/register_alloc.h"
#include "../include/riscv_mir.h"
#include <algorithm>
#include <iostream>

// ===--------------------------------------------------------------------=== //
// RISC-V 寄存器定义
// ===--------------------------------------------------------------------=== //

const std::vector<int> SimpleRegisterAllocator::caller_saved_regs = {
  5, 6, 7,        // t0-t2
  10, 11, 12, 13, 14, 15, 16, 17,  // a0-a7
  28, 29, 30, 31  // t3-t6
};

const std::vector<int> SimpleRegisterAllocator::callee_saved_regs = {
  8, 9,           // s0-s1
  18, 19, 20, 21, 22, 23, 24, 25, 26, 27  // s2-s11
};

const std::vector<int> SimpleRegisterAllocator::argument_regs = {
  10, 11, 12, 13, 14, 15, 16, 17  // a0-a7
};

const std::vector<int> SimpleRegisterAllocator::temp_regs = {
  5, 6, 7, 28, 29, 30, 31  // t0-t2, t3-t6
};

// ===--------------------------------------------------------------------=== //
// 寄存器分配器实现
// ===--------------------------------------------------------------------=== //

bool SimpleRegisterAllocator::allocateRegisters(MachineFunction& func) {
  current_function = &func;
  
  // 重置状态
  virtual_to_physical.clear();
  allocated_registers.clear();
  next_stack_slot = 0;  // 这个变量现在将被废弃，使用函数的栈分配
  
  // 第一步：处理函数参数虚拟寄存器，将它们映射到正确的参数寄存器(a0-a7)
  allocateFunctionParameters(func);
  
  // 第二步：为每个基本块中的其他虚拟寄存器分配物理寄存器
  for (auto& block : func.basic_blocks) {
    for (auto& inst : block->instructions) {
      updateInstructionRegisters(*inst);
    }
  }
  
  return true;
}

void SimpleRegisterAllocator::allocateFunctionParameters(MachineFunction& func) {
  // 分析函数以识别参数虚拟寄存器
  // 策略：在函数的第一个基本块中，找到虚拟寄存器编号最小的几个，
  // 假设它们按顺序对应函数参数
  
  if (func.basic_blocks.empty()) return;
  
  std::set<MachineRegister*> all_vregs;
  MachineBasicBlock* first_block = func.basic_blocks[0].get();
  
  // 收集第一个基本块中使用的所有虚拟寄存器
  for (const auto& inst : first_block->instructions) {
    for (const auto& operand : inst->operands) {
      if (operand.isReg() && operand.reg && operand.reg->isVirtual()) {
        all_vregs.insert(operand.reg);
      }
    }
  }
  
  // 将虚拟寄存器按编号排序
  std::vector<MachineRegister*> sorted_vregs(all_vregs.begin(), all_vregs.end());
  std::sort(sorted_vregs.begin(), sorted_vregs.end(), 
            [](MachineRegister* a, MachineRegister* b) {
              return a->reg_num < b->reg_num;
            });
  
  // 将前几个虚拟寄存器映射到参数寄存器(a0-a7)
  size_t max_params = std::min(sorted_vregs.size(), argument_regs.size());
  for (size_t i = 0; i < max_params; ++i) {
    MachineRegister* vreg = sorted_vregs[i];
    int physical_reg = argument_regs[i];
    
    // 直接建立映射关系
    virtual_to_physical[vreg] = physical_reg;
    allocated_registers.insert(physical_reg);
    
    // 调试输出
    // std::cout << "Parameter mapping: v" << vreg->reg_num 
    //           << " -> " << getRegisterName(physical_reg) << std::endl;
  }
}

int SimpleRegisterAllocator::allocatePhysicalRegister(MachineRegister* vreg) {
  if (!vreg || !vreg->isVirtual()) return -1;
  
  // 检查是否已经分配过
  auto it = virtual_to_physical.find(vreg);
  if (it != virtual_to_physical.end()) {
    return it->second;
  }
  
  // 尝试分配临时寄存器
  for (int reg : temp_regs) {
    if (isRegisterAvailable(reg)) {
      virtual_to_physical[vreg] = reg;
      allocated_registers.insert(reg);
      return reg;
    }
  }
  
  // 尝试分配调用者保存寄存器
  for (int reg : caller_saved_regs) {
    if (isRegisterAvailable(reg)) {
      virtual_to_physical[vreg] = reg;
      allocated_registers.insert(reg);
      return reg;
    }
  }
  
  // 如果没有可用寄存器，溢出到栈
  return spillToStack(vreg);
}

void SimpleRegisterAllocator::deallocatePhysicalRegister(int physical_reg) {
  allocated_registers.erase(physical_reg);
}

int SimpleRegisterAllocator::getPhysicalRegister(MachineRegister* vreg) {
  auto it = virtual_to_physical.find(vreg);
  if (it != virtual_to_physical.end()) {
    return it->second;
  }
  return allocatePhysicalRegister(vreg);
}

int SimpleRegisterAllocator::spillToStack(MachineRegister* vreg) {
  // 使用MachineFunction的allocateStackSlot方法来分配栈空间
  int stack_offset = current_function->allocateStackSlot(4);  // 假设每个寄存器需要4字节
  
  // 将栈偏移编码为特殊的"寄存器号"，使用负数来区分
  // 这样可以在后续处理中识别这是栈位置而不是物理寄存器
  virtual_to_physical[vreg] = -(stack_offset + 1);  // 使用负数表示栈偏移，+1避免0值
  
  return virtual_to_physical[vreg];
}

void SimpleRegisterAllocator::insertSpillCode(MachineBasicBlock* block,
                                             std::vector<std::unique_ptr<MachineInstruction>>::iterator pos,
                                             MachineRegister* vreg, int stack_slot) {
  // 创建spill指令：sw reg, offset(sp)
  auto spill_inst = std::make_unique<MachineInstruction>(RISCVOpcode::SW);
  // 这里简化处理，实际需要更复杂的栈管理
}

void SimpleRegisterAllocator::insertReloadCode(MachineBasicBlock* block,
                                              std::vector<std::unique_ptr<MachineInstruction>>::iterator pos,
                                              MachineRegister* vreg, int stack_slot) {
  // 创建reload指令：lw reg, offset(sp)
  auto reload_inst = std::make_unique<MachineInstruction>(RISCVOpcode::LW);
  // 这里简化处理，实际需要更复杂的栈管理
}

MachineRegister* SimpleRegisterAllocator::selectSpillCandidate() {
  // 简单选择策略：选择第一个已分配的虚拟寄存器
  if (!virtual_to_physical.empty()) {
    return virtual_to_physical.begin()->first;
  }
  return nullptr;
}

void SimpleRegisterAllocator::updateInstructionRegisters(MachineInstruction& inst) {
  // 遍历指令的所有操作数，将虚拟寄存器替换为物理寄存器或栈位置
  for (auto& operand : inst.operands) {
    if (operand.isReg() && operand.reg && operand.reg->isVirtual()) {
      int mapped_value = getPhysicalRegister(operand.reg);
      
             if (mapped_value < 0) {
         // 负值表示这是栈偏移，需要转换为栈槽操作数
         int stack_offset = -(mapped_value + 1);  // 恢复原始偏移值
         operand = MachineOperand::createStackSlot(stack_offset);
      } else if (mapped_value >= 0 && mapped_value < 32) {
        // 正值表示物理寄存器
        MachineRegister* phys_reg = new MachineRegister(
          MRegType::PHYSICAL, 
          operand.reg->reg_class, 
          mapped_value
        );
        operand.reg = phys_reg;
      }
    }
  }
}

bool SimpleRegisterAllocator::isRegisterAvailable(int physical_reg) {
  // 检查寄存器是否已被分配，并且不是保留寄存器
  if (allocated_registers.find(physical_reg) != allocated_registers.end()) {
    return false;
  }
  
  // 保留一些特殊寄存器
  if (physical_reg == 0 ||  // zero register
      physical_reg == 1 ||  // ra
      physical_reg == 2 ||  // sp
      physical_reg == 3 ||  // gp
      physical_reg == 4) {  // tp
    return false;
  }
  
  return true;
}

std::string SimpleRegisterAllocator::getRegisterName(int physical_reg) {
  static const std::string gpr_names[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
  };
  
  if (physical_reg >= 0 && physical_reg < 32) {
    return gpr_names[physical_reg];
  }
  return "unknown";
} 