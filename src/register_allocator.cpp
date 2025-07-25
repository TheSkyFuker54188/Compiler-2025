#include "../include/register_allocator.h"
#include <iostream>
#include <algorithm>

RegisterAllocator::RegisterAllocator() : next_spill_slot(0), current_frame(nullptr) {
  initializePhysicalRegisters();
}

void RegisterAllocator::initializePhysicalRegisters() {
  // RISC-V寄存器分配策略：
  // - t0-t6: 临时寄存器，调用方保存
  // - s0-s11: 保存寄存器，被调用方保存  
  // - a0-a7: 参数寄存器，a0,a1也是返回值寄存器
  
  // 临时寄存器 (caller-saved)
  available_registers.emplace_back(5, "t0", false);   // x5
  available_registers.emplace_back(6, "t1", false);   // x6  
  available_registers.emplace_back(7, "t2", false);   // x7
  available_registers.emplace_back(28, "t3", false);  // x28
  available_registers.emplace_back(29, "t4", false);  // x29
  available_registers.emplace_back(30, "t5", false);  // x30
  available_registers.emplace_back(31, "t6", false);  // x31
  
  // 保存寄存器 (callee-saved) - 优先级较低，因为需要保存恢复
  available_registers.emplace_back(8, "s0", true);    // x8
  available_registers.emplace_back(9, "s1", true);    // x9
  available_registers.emplace_back(18, "s2", true);   // x18
  available_registers.emplace_back(19, "s3", true);   // x19
  available_registers.emplace_back(20, "s4", true);   // x20
  available_registers.emplace_back(21, "s5", true);   // x21
  available_registers.emplace_back(22, "s6", true);   // x22
  available_registers.emplace_back(23, "s7", true);   // x23
  available_registers.emplace_back(24, "s8", true);   // x24
  available_registers.emplace_back(25, "s9", true);   // x25
  available_registers.emplace_back(26, "s10", true);  // x26
  available_registers.emplace_back(27, "s11", true);  // x27
  
  // 参数寄存器a2-a7可以用作临时寄存器（a0,a1保留用于返回值）
  available_registers.emplace_back(12, "a2", false);  // x12
  available_registers.emplace_back(13, "a3", false);  // x13
  available_registers.emplace_back(14, "a4", false);  // x14
  available_registers.emplace_back(15, "a5", false);  // x15
  available_registers.emplace_back(16, "a6", false);  // x16
  available_registers.emplace_back(17, "a7", false);  // x17
}

void RegisterAllocator::allocateRegistersForFunction(const std::string& func_name, 
                                                     std::map<int, std::unique_ptr<RiscvBlock>>& blocks,
                                                     StackFrameInfo* frame_info) {
  std::cout << "开始为函数 " << func_name << " 分配寄存器..." << std::endl;
  
  current_frame = frame_info;
  
  // 清空之前的分配状态
  virtual_to_physical.clear();
  physical_to_virtual.clear();
  spilled_virtuals.clear();
  spill_slots.clear();
  live_ranges.clear();
  virtual_to_range.clear();
  next_spill_slot = 0;
  
  // 重置物理寄存器可用状态
  for (auto& reg : available_registers) {
    reg.is_available = true;
  }
  
  // 1. 计算生存期
  computeLiveRanges(blocks);
  
  // 2. 预分配特殊寄存器
  preAllocateSpecialRegisters(blocks);
  
  // 3. 执行线性扫描分配
  performLinearScanAllocation();
  
  // 3. 插入溢出代码
  insertSpillCode(blocks);
  
  // 4. 重写指令，替换虚拟寄存器为物理寄存器
  rewriteInstructions(blocks);
  
  // 5. 更新栈帧大小（考虑溢出）
  if (!spilled_virtuals.empty()) {
    int spill_area_size = next_spill_slot * 4; // 每个溢出槽4字节
    current_frame->local_vars_size += spill_area_size;
    current_frame->calculateTotalSize();
    std::cout << "添加溢出区域: " << spill_area_size << " 字节，总栈帧: " << current_frame->total_frame_size << " 字节" << std::endl;
    
    // 更新所有基本块中的栈帧大小显示和相关指令
    for (auto& block_pair : blocks) {
      auto& block = block_pair.second;
      if (block->stack_size > 0) {  // 只更新已设置过栈帧大小的块
        int old_size = block->stack_size;
        block->stack_size = current_frame->total_frame_size;
        
        // 更新栈指针调整指令
        for (auto& inst : block->instruction_list) {
          if (auto* imm_inst = dynamic_cast<RiscvImmediateInstruction*>(inst.get())) {
            if (imm_inst->GetOpcode() == RiscvOpcode::ADDI) {
              // 检查是否是栈指针调整指令
              if (auto* rd_reg = dynamic_cast<RiscvRegOperand*>(imm_inst->rd.get())) {
                if (auto* rs1_reg = dynamic_cast<RiscvRegOperand*>(imm_inst->rs1.get())) {
                  // sp寄存器是x2，在我们的系统中表示为-2
                  if (rd_reg->GetRegNo() == -2 && rs1_reg->GetRegNo() == -2) {
                    // 这是栈指针调整指令
                    if (imm_inst->immediate == -old_size) {
                      // 栈分配指令 (负数)
                      imm_inst->immediate = -current_frame->total_frame_size;
                    } else if (imm_inst->immediate == old_size) {
                      // 栈释放指令 (正数)
                      imm_inst->immediate = current_frame->total_frame_size;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  
  // 5. 输出分配结果
  printAllocationResult();
}

void RegisterAllocator::computeLiveRanges(const std::map<int, std::unique_ptr<RiscvBlock>>& blocks) {
  std::map<int, int> virtual_first_def;   // 虚拟寄存器的第一次定义位置
  std::map<int, int> virtual_last_use;    // 虚拟寄存器的最后一次使用位置
  
  int position = 0;
  
  // 遍历所有指令，记录虚拟寄存器的定义和使用
  for (const auto& block_pair : blocks) {
    const auto& block = block_pair.second;
    
    for (const auto& inst : block->instruction_list) {
      // 分析指令中的虚拟寄存器使用
      std::vector<int> used_virtuals = extractVirtualRegisters(inst.get());
      
      for (int virtual_reg : used_virtuals) {
        if (virtual_first_def.find(virtual_reg) == virtual_first_def.end()) {
          virtual_first_def[virtual_reg] = position;
        }
        virtual_last_use[virtual_reg] = position;
      }
      
      position++;
    }
  }
  
  // 预分配空间避免指针失效
  live_ranges.reserve(virtual_first_def.size());
  
  // 创建生存期对象
  for (const auto& def_pair : virtual_first_def) {
    int virtual_reg = def_pair.first;
    int start_pos = def_pair.second;
    int end_pos = virtual_last_use[virtual_reg];
    
    live_ranges.emplace_back(virtual_reg, start_pos, end_pos);
    virtual_to_range[virtual_reg] = &live_ranges.back();
  }
  
  // 按开始位置排序，用于线性扫描
  std::sort(live_ranges.begin(), live_ranges.end(), 
            [](const LiveRange& a, const LiveRange& b) {
              return a.start_pos < b.start_pos;
            });
  
  std::cout << "计算出 " << live_ranges.size() << " 个虚拟寄存器的生存期" << std::endl;
}

std::vector<int> RegisterAllocator::extractVirtualRegisters(RiscvInstruction* inst) {
  std::vector<int> virtuals;
  
  // 从指令的操作数中提取虚拟寄存器
  auto extractFromOperand = [&](const std::unique_ptr<RiscvOperand>& operand) {
    if (operand) {
      if (auto* reg_operand = dynamic_cast<RiscvRegOperand*>(operand.get())) {
        int reg_no = reg_operand->GetRegNo();
        if (reg_no >= 0) { // 虚拟寄存器是非负数（包含%r0）
          virtuals.push_back(reg_no);
        }
      }
      else if (auto* dram_operand = dynamic_cast<RiscvDramOperand*>(operand.get())) {
        if (dram_operand->base_reg) {
          if (auto* base_reg = dynamic_cast<RiscvRegOperand*>(dram_operand->base_reg.get())) {
            int reg_no = base_reg->GetRegNo();
            if (reg_no >= 0) {
              virtuals.push_back(reg_no);
            }
          }
        }
      }
    }
  };
  
  // 根据指令类型提取操作数中的虚拟寄存器
  if (auto* arith_inst = dynamic_cast<RiscvArithmeticInstruction*>(inst)) {
    extractFromOperand(arith_inst->rd);
    extractFromOperand(arith_inst->rs1);
    extractFromOperand(arith_inst->rs2);
  }
  else if (auto* imm_inst = dynamic_cast<RiscvImmediateInstruction*>(inst)) {
    extractFromOperand(imm_inst->rd);
    extractFromOperand(imm_inst->rs1);
  }
  else if (auto* mem_inst = dynamic_cast<RiscvMemoryInstruction*>(inst)) {
    extractFromOperand(mem_inst->reg);
    extractFromOperand(mem_inst->address);
  }
  else if (auto* branch_inst = dynamic_cast<RiscvBranchInstruction*>(inst)) {
    extractFromOperand(branch_inst->rs1);
    extractFromOperand(branch_inst->rs2);
  }
  else if (auto* jump_inst = dynamic_cast<RiscvJumpInstruction*>(inst)) {
    extractFromOperand(jump_inst->rd);
  }
  else if (auto* call_inst = dynamic_cast<RiscvCallInstruction*>(inst)) {
    for (auto& arg : call_inst->args) {
      extractFromOperand(arg);
    }
  }
  else if (auto* pseudo_inst = dynamic_cast<RiscvPseudoInstruction*>(inst)) {
    extractFromOperand(pseudo_inst->rd);
    extractFromOperand(pseudo_inst->operand);
  }
  
  return virtuals;
}

void RegisterAllocator::performLinearScanAllocation() {
  std::vector<LiveRange*> active; // 当前活跃的生存期
  
  for (auto& range : live_ranges) {
    // 跳过已经预分配的虚拟寄存器
    if (virtual_to_physical.find(range.virtual_reg) != virtual_to_physical.end()) {
      continue;
    }
    // 移除已过期的生存期
    active.erase(std::remove_if(active.begin(), active.end(),
                                [&](LiveRange* active_range) {
                                  if (active_range->end_pos < range.start_pos) {
                                    // 释放物理寄存器（只有当虚拟寄存器确实有物理寄存器分配时）
                                    auto it = virtual_to_physical.find(active_range->virtual_reg);
                                    if (it != virtual_to_physical.end()) {
                                      int physical_reg = it->second;
                                      physical_to_virtual.erase(physical_reg);
                                    }
                                    return true;
                                  }
                                  return false;
                                }), active.end());
    
    // 尝试分配物理寄存器
    int physical_reg = findFreeRegister();
    
    if (physical_reg != -1) {
      // 成功分配
      virtual_to_physical[range.virtual_reg] = physical_reg;
      physical_to_virtual[physical_reg] = range.virtual_reg;
      active.push_back(&range);
    } else {
      // 需要溢出
      int victim_reg = selectVictimRegister(range.start_pos);
      if (victim_reg != -1) {
        spillRegister(victim_reg, range.start_pos);
        virtual_to_physical[range.virtual_reg] = victim_reg;
        physical_to_virtual[victim_reg] = range.virtual_reg;
        active.push_back(&range);
      } else {
        // 当前范围被溢出
        range.is_spilled = true;
        spilled_virtuals.insert(range.virtual_reg);
        spill_slots[range.virtual_reg] = next_spill_slot++;
      }
    }
  }
}

int RegisterAllocator::findFreeRegister() {
  // 优先分配临时寄存器（caller-saved）
  for (auto& reg : available_registers) {
    if (reg.is_available && !reg.is_callee_saved && 
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }
  
  // 如果没有临时寄存器，分配保存寄存器
  for (auto& reg : available_registers) {
    if (reg.is_available && 
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }
  
  return -1; // 没有可用寄存器
}

int RegisterAllocator::selectVictimRegister(int current_pos) {
  int victim = -1;
  int latest_end = current_pos;
  
  // 选择结束位置最晚的寄存器作为受害者
  for (const auto& pair : physical_to_virtual) {
    int physical_reg = pair.first;
    int virtual_reg = pair.second;
    
    auto it = virtual_to_range.find(virtual_reg);
    if (it != virtual_to_range.end()) {
      LiveRange* range = it->second;
      if (range && range->end_pos > latest_end) {
        latest_end = range->end_pos;
        victim = physical_reg;
      }
    }
  }
  
  return victim;
}

void RegisterAllocator::spillRegister(int physical_reg, int current_pos) {
  auto phys_it = physical_to_virtual.find(physical_reg);
  if (phys_it == physical_to_virtual.end()) {
    return; // 物理寄存器没有映射，无需溢出
  }
  
  int virtual_reg = phys_it->second;
  
  // 标记为溢出
  auto range_it = virtual_to_range.find(virtual_reg);
  if (range_it != virtual_to_range.end() && range_it->second) {
    LiveRange* range = range_it->second;
    range->is_spilled = true;
    spilled_virtuals.insert(virtual_reg);
    spill_slots[virtual_reg] = next_spill_slot++;
    
    std::cout << "溢出虚拟寄存器 %r" << virtual_reg << " 到溢出槽 " << spill_slots[virtual_reg] << std::endl;
  }
  
  // 释放物理寄存器
  virtual_to_physical.erase(virtual_reg);
  physical_to_virtual.erase(physical_reg);
}

void RegisterAllocator::insertSpillCode(std::map<int, std::unique_ptr<RiscvBlock>>& blocks) {
  // 简化实现：插入溢出加载和存储代码
  // 在实际实现中，需要在适当的位置插入spill/reload指令
  
  for (int virtual_reg : spilled_virtuals) {
    std::cout << "需要为虚拟寄存器 %r" << virtual_reg << " 插入溢出代码" << std::endl;
  }
  
  // TODO: 实现具体的溢出代码插入逻辑
}

int RegisterAllocator::getPhysicalRegister(int virtual_reg) {
  auto it = virtual_to_physical.find(virtual_reg);
  return (it != virtual_to_physical.end()) ? it->second : -1;
}

bool RegisterAllocator::isSpilled(int virtual_reg) {
  return spilled_virtuals.find(virtual_reg) != spilled_virtuals.end();
}

int RegisterAllocator::getSpillOffset(int virtual_reg) {
  auto it = spill_slots.find(virtual_reg);
  if (it != spill_slots.end()) {
    return current_frame->local_vars_size + it->second * 4;
  }
  return -1;
}

void RegisterAllocator::printAllocationResult() {
  std::cout << "\n=== 寄存器分配结果 ===" << std::endl;
  
  std::cout << "虚拟寄存器 -> 物理寄存器映射:" << std::endl;
  for (const auto& pair : virtual_to_physical) {
    std::string phys_name = "unknown";
    for (const auto& reg : available_registers) {
      if (reg.reg_no == pair.second) {
        phys_name = reg.name;
        break;
      }
    }
    std::cout << "  %r" << pair.first << " -> " << phys_name << " (x" << pair.second << ")" << std::endl;
  }
  
  if (!spilled_virtuals.empty()) {
    std::cout << "溢出到内存的虚拟寄存器:" << std::endl;
    for (int virtual_reg : spilled_virtuals) {
      std::cout << "  %r" << virtual_reg << " -> 溢出槽 " << spill_slots[virtual_reg] 
                << " (偏移 " << getSpillOffset(virtual_reg) << ")" << std::endl;
    }
  }
  
  std::cout << "分配统计:" << std::endl;
  std::cout << "  已分配寄存器: " << virtual_to_physical.size() << std::endl;
  std::cout << "  溢出寄存器: " << spilled_virtuals.size() << std::endl;
  std::cout << "  溢出槽使用: " << next_spill_slot << " 个 (" << next_spill_slot * 4 << " 字节)" << std::endl;
}

void RegisterAllocator::printLiveRanges() {
  std::cout << "\n=== 虚拟寄存器生存期 ===" << std::endl;
  for (const auto& range : live_ranges) {
    std::cout << "%r" << range.virtual_reg << ": [" << range.start_pos << ", " << range.end_pos << "]";
    if (range.is_spilled) {
      std::cout << " (溢出)";
    }
    std::cout << std::endl;
  }
}

// 集成接口
void RegisterAllocationPass::applyToTranslator(Translator& translator) {
  std::cout << "\n=== 开始寄存器分配阶段 ===" << std::endl;
  
  RegisterAllocator allocator;
  
  // 为每个函数执行寄存器分配
  for (auto& func_pair : translator.riscv.function_block_map) {
    const std::string& func_name = func_pair.first;
    auto& blocks = func_pair.second;
    
    // 获取函数的栈帧信息
    const StackFrameInfo* frame_info = translator.getFunctionStackFrame(func_name);
    if (frame_info) {
      // 创建可修改的副本
      StackFrameInfo* mutable_frame = const_cast<StackFrameInfo*>(frame_info);
      allocator.allocateRegistersForFunction(func_name, blocks, mutable_frame);
    }
  }
  
  std::cout << "寄存器分配完成！" << std::endl;
}

void RegisterAllocator::rewriteInstructions(std::map<int, std::unique_ptr<RiscvBlock>>& blocks) {
  std::cout << "重写指令，替换虚拟寄存器为物理寄存器..." << std::endl;
  
  for (auto& block_pair : blocks) {
    auto& block = block_pair.second;
    
    for (auto& inst : block->instruction_list) {
      // 根据指令类型重写操作数
      if (auto* arith_inst = dynamic_cast<RiscvArithmeticInstruction*>(inst.get())) {
        rewriteOperand(arith_inst->rd);
        rewriteOperand(arith_inst->rs1);
        rewriteOperand(arith_inst->rs2);
      }
      else if (auto* imm_inst = dynamic_cast<RiscvImmediateInstruction*>(inst.get())) {
        rewriteOperand(imm_inst->rd);
        rewriteOperand(imm_inst->rs1);
      }
      else if (auto* mem_inst = dynamic_cast<RiscvMemoryInstruction*>(inst.get())) {
        rewriteOperand(mem_inst->reg);
        rewriteOperand(mem_inst->address);
      }
      else if (auto* branch_inst = dynamic_cast<RiscvBranchInstruction*>(inst.get())) {
        rewriteOperand(branch_inst->rs1);
        rewriteOperand(branch_inst->rs2);
        // label不需要重写
      }
      else if (auto* jump_inst = dynamic_cast<RiscvJumpInstruction*>(inst.get())) {
        rewriteOperand(jump_inst->rd);
        // target不需要重写（是label）
      }
      else if (auto* call_inst = dynamic_cast<RiscvCallInstruction*>(inst.get())) {
        // 函数调用的参数重写
        for (auto& arg : call_inst->args) {
          rewriteOperand(arg);
        }
      }
      else if (auto* pseudo_inst = dynamic_cast<RiscvPseudoInstruction*>(inst.get())) {
        if (pseudo_inst->rd) {
          rewriteOperand(pseudo_inst->rd);
        }
        if (pseudo_inst->operand) {
          rewriteOperand(pseudo_inst->operand);
        }
      }
    }
  }
  
  std::cout << "指令重写完成" << std::endl;
}

void RegisterAllocator::rewriteOperand(std::unique_ptr<RiscvOperand>& operand) {
  if (!operand) return;
  
  // 只处理寄存器操作数
  if (auto* reg_operand = dynamic_cast<RiscvRegOperand*>(operand.get())) {
    int virtual_reg = reg_operand->GetRegNo();
    
    // 如果是虚拟寄存器（非负数）且有分配的物理寄存器
    if (virtual_reg >= 0) {
      auto it = virtual_to_physical.find(virtual_reg);
      if (it != virtual_to_physical.end()) {
        int physical_reg = it->second;
        // 替换为物理寄存器（使用负数表示物理寄存器）
        operand = std::make_unique<RiscvRegOperand>(-physical_reg);
      }
      else if (isSpilled(virtual_reg)) {
        // TODO: 处理溢出寄存器的情况
        std::cout << "  虚拟寄存器 %r" << virtual_reg << " 已溢出，需要特殊处理" << std::endl;
      }
    }
  }
  else if (auto* dram_operand = dynamic_cast<RiscvDramOperand*>(operand.get())) {
    // 重写DRAM操作数的基址寄存器
         rewriteOperand(dram_operand->base_reg);
   }
 }

void RegisterAllocator::preAllocateSpecialRegisters(const std::map<int, std::unique_ptr<RiscvBlock>>& blocks) {
  std::cout << "预分配特殊寄存器..." << std::endl;
  
  for (const auto& block_pair : blocks) {
    const auto& block = block_pair.second;
    
    for (const auto& inst : block->instruction_list) {
      // 查找函数调用指令
      if (auto* call_inst = dynamic_cast<RiscvCallInstruction*>(inst.get())) {
        // 查找紧接着的 mv 指令，这通常是 call 的返回值赋值
        // 在指令列表中查找当前指令的位置
        auto it = std::find_if(block->instruction_list.begin(), block->instruction_list.end(),
                              [&](const std::unique_ptr<RiscvInstruction>& ptr) {
                                return ptr.get() == call_inst;
                              });
        
        if (it != block->instruction_list.end()) {
          auto next_it = std::next(it);
          if (next_it != block->instruction_list.end()) {
            // 检查下一条指令是否是 mv 指令
            if (auto* mv_inst = dynamic_cast<RiscvPseudoInstruction*>(next_it->get())) {
              if (mv_inst->GetOpcode() == RiscvOpcode::MV && mv_inst->operand) {
                // 检查源操作数是否是 a0 寄存器
                if (auto* src_reg = dynamic_cast<RiscvRegOperand*>(mv_inst->operand.get())) {
                  if (src_reg->GetRegNo() == -10) { // a0 是 x10，使用负数表示物理寄存器
                    // 检查目标寄存器是否是虚拟寄存器
                    if (auto* dst_reg = dynamic_cast<RiscvRegOperand*>(mv_inst->rd.get())) {
                      int virtual_reg = dst_reg->GetRegNo();
                      if (virtual_reg >= 0) { // 虚拟寄存器
                        // 预分配 a0 寄存器给这个虚拟寄存器
                        virtual_to_physical[virtual_reg] = 10; // a0 是 x10
                        physical_to_virtual[10] = virtual_reg;
                        std::cout << "  预分配虚拟寄存器 %r" << virtual_reg << " -> a0 (x10)" << std::endl;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      
      // 查找返回指令前的 mv a0, %rx 模式
      if (auto* mv_inst = dynamic_cast<RiscvPseudoInstruction*>(inst.get())) {
        if (mv_inst->GetOpcode() == RiscvOpcode::MV && mv_inst->rd && mv_inst->operand) {
          // 检查目标是否是 a0 寄存器
          if (auto* dst_reg = dynamic_cast<RiscvRegOperand*>(mv_inst->rd.get())) {
            if (dst_reg->GetRegNo() == -10) { // a0 是 x10
              // 检查源是否是虚拟寄存器
              if (auto* src_reg = dynamic_cast<RiscvRegOperand*>(mv_inst->operand.get())) {
                int virtual_reg = src_reg->GetRegNo();
                if (virtual_reg >= 0) { // 虚拟寄存器
                  // 预分配 a0 寄存器给这个虚拟寄存器
                  virtual_to_physical[virtual_reg] = 10; // a0 是 x10
                  physical_to_virtual[10] = virtual_reg;
                  std::cout << "  预分配虚拟寄存器 %r" << virtual_reg << " -> a0 (x10)" << std::endl;
                }
              }
            }
          }
        }
      }
    }
  }
} 