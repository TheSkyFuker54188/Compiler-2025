<<<<<<< HEAD
#include "../include/register_allocator.h"
#include <algorithm>
#include <iostream>

RegisterAllocator::RegisterAllocator()
    : next_spill_slot(0), current_frame(nullptr) {
  initializePhysicalRegisters();
}

void RegisterAllocator::initializePhysicalRegisters() {
  // RISC-V寄存器分配策略：
  // - t0-t6: 临时寄存器，调用方保存
  // - s0-s11: 保存寄存器，被调用方保存
  // - a0-a7: 参数寄存器，a0,a1也是返回值寄存器

  // 临时寄存器 (caller-saved)
  available_registers.emplace_back(5, "t0", false);  // x5
  available_registers.emplace_back(6, "t1", false);  // x6
  available_registers.emplace_back(7, "t2", false);  // x7
  available_registers.emplace_back(28, "t3", false); // x28
  available_registers.emplace_back(29, "t4", false); // x29
  available_registers.emplace_back(30, "t5", false); // x30
  available_registers.emplace_back(31, "t6", false); // x31

  // 保存寄存器 (callee-saved) - 优先级较低，因为需要保存恢复
  available_registers.emplace_back(8, "s0", true);   // x8
  available_registers.emplace_back(9, "s1", true);   // x9
  available_registers.emplace_back(18, "s2", true);  // x18
  available_registers.emplace_back(19, "s3", true);  // x19
  available_registers.emplace_back(20, "s4", true);  // x20
  available_registers.emplace_back(21, "s5", true);  // x21
  available_registers.emplace_back(22, "s6", true);  // x22
  available_registers.emplace_back(23, "s7", true);  // x23
  available_registers.emplace_back(24, "s8", true);  // x24
  available_registers.emplace_back(25, "s9", true);  // x25
  available_registers.emplace_back(26, "s10", true); // x26
  available_registers.emplace_back(27, "s11", true); // x27

  // 参数寄存器a2-a7可以用作临时寄存器（a0,a1保留用于返回值）
  available_registers.emplace_back(12, "a2", false); // x12
  available_registers.emplace_back(13, "a3", false); // x13
  available_registers.emplace_back(14, "a4", false); // x14
  available_registers.emplace_back(15, "a5", false); // x15
  available_registers.emplace_back(16, "a6", false); // x16
  available_registers.emplace_back(17, "a7", false); // x17
}

void RegisterAllocator::allocateRegistersForFunction(
    const std::string &func_name,
    std::map<int, std::unique_ptr<RiscvBlock>> &blocks,
    StackFrameInfo *frame_info) {
  // std::cout << "开始为函数 " << func_name << " 分配寄存器..." << std::endl;

  if (!frame_info) {
    throw std::runtime_error("StackFrameInfo is null for function: " + func_name);
  }

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
  for (auto &reg : available_registers) {
    reg.is_available = true;
  }

  try {
  // 1. 计算生存期
  computeLiveRanges(blocks);

  // 2. 预分配特殊寄存器
  preAllocateSpecialRegisters(blocks);

  // 3. 执行线性扫描分配
  performLinearScanAllocation();

    // 4. 插入溢出代码
  insertSpillCode(blocks);

    // 5. 重写指令，替换虚拟寄存器为物理寄存器
  rewriteInstructions(blocks);

    // 6. 更新栈帧大小（考虑溢出）
  if (!spilled_virtuals.empty()) {
    int spill_area_size = next_spill_slot * 4; // 每个溢出槽4字节
    current_frame->local_vars_size += spill_area_size;
    current_frame->calculateTotalSize();
      
      // 检查栈帧大小是否合理
      if (current_frame->total_frame_size > 1024 * 1024) { // 1MB限制
        throw std::runtime_error("Stack frame too large: " + 
                                std::to_string(current_frame->total_frame_size) + 
                                " bytes for function: " + func_name);
      }

    // 更新所有基本块中的栈帧大小显示和相关指令
    for (auto &block_pair : blocks) {
      auto &block = block_pair.second;
      if (block->stack_size > 0) { // 只更新已设置过栈帧大小的块
        int old_size = block->stack_size;
        block->stack_size = current_frame->total_frame_size;

        // 更新栈指针调整指令
        for (auto &inst : block->instruction_list) {
          if (auto *imm_inst =
                  dynamic_cast<RiscvImmediateInstruction *>(inst.get())) {
            if (imm_inst->GetOpcode() == RiscvOpcode::ADDI) {
              // 检查是否是栈指针调整指令
              if (auto *rd_reg =
                      dynamic_cast<RiscvRegOperand *>(imm_inst->rd.get())) {
                if (auto *rs1_reg =
                        dynamic_cast<RiscvRegOperand *>(imm_inst->rs1.get())) {
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

    // 7. 输出分配结果
  // printAllocationResult();
    
  } catch (const std::exception& e) {
    std::cerr << "Error in register allocation for function " << func_name 
              << ": " << e.what() << std::endl;
    throw;
  }
}

void RegisterAllocator::computeLiveRanges(
    const std::map<int, std::unique_ptr<RiscvBlock>> &blocks) {
  // 第一步：构建控制流图
  std::map<int, std::vector<int>> successors;
  std::map<int, std::vector<int>> predecessors;
  
  // 初始化控制流图
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    successors[block_id] = {};
    predecessors[block_id] = {};
  }
  
  // 分析跳转指令构建控制流
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    const auto &block = block_pair.second;
    
    if (block->instruction_list.empty()) {
      // 空块，顺序执行到下一块
      if (block_id + 1 < blocks.size()) {
        successors[block_id].push_back(block_id + 1);
        predecessors[block_id + 1].push_back(block_id);
      }
      continue;
    }
    
    // 检查最后一条指令
    const auto &last_inst = block->instruction_list.back();
    
    // 根据指令类型确定后继块
    if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction*>(last_inst.get())) {
      // 无条件跳转
      // 尝试解析跳转目标
      if (auto *label_operand = dynamic_cast<RiscvLabelOperand*>(jump_inst->target.get())) {
        std::string label_name = label_operand->GetFullName();
        // 解析标签名称，格式应该是 ".L" + block_id
        if (label_name.substr(0, 2) == ".L") {
          try {
            int target_block = std::stoi(label_name.substr(2));
            if (blocks.find(target_block) != blocks.end()) {
              successors[block_id].push_back(target_block);
              predecessors[target_block].push_back(block_id);
            }
          } catch (const std::exception&) {
            // 解析失败，使用简化处理
            if (block_id + 1 < blocks.size()) {
              successors[block_id].push_back(block_id + 1);
              predecessors[block_id + 1].push_back(block_id);
            }
          }
        }
      } else {
        // 无法解析标签，使用简化处理
        if (block_id + 1 < blocks.size()) {
          successors[block_id].push_back(block_id + 1);
          predecessors[block_id + 1].push_back(block_id);
        }
      }
    } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction*>(last_inst.get())) {
      // 条件跳转，有两个后继
      if (block_id + 1 < blocks.size()) {
        successors[block_id].push_back(block_id + 1);
        predecessors[block_id + 1].push_back(block_id);
      }
      // 尝试解析跳转目标
      if (auto *label_operand = dynamic_cast<RiscvLabelOperand*>(branch_inst->label.get())) {
        std::string label_name = label_operand->GetFullName();
        if (label_name.substr(0, 2) == ".L") {
          try {
            int target_block = std::stoi(label_name.substr(2));
            if (blocks.find(target_block) != blocks.end()) {
              successors[block_id].push_back(target_block);
              predecessors[target_block].push_back(block_id);
            }
          } catch (const std::exception&) {
            // 解析失败，使用简化处理
            if (block_id + 2 < blocks.size()) {
              successors[block_id].push_back(block_id + 2);
              predecessors[block_id + 2].push_back(block_id);
            }
          }
        }
      } else {
        // 无法解析标签，使用简化处理
        if (block_id + 2 < blocks.size()) {
          successors[block_id].push_back(block_id + 2);
          predecessors[block_id + 2].push_back(block_id);
        }
      }
    } else {
      // 其他指令，顺序执行
      if (block_id + 1 < blocks.size()) {
        successors[block_id].push_back(block_id + 1);
        predecessors[block_id + 1].push_back(block_id);
      }
    }
  }
  
  // 第二步：计算每个基本块的liveIn和liveOut
  std::map<int, std::set<int>> block_live_in;
  std::map<int, std::set<int>> block_live_out;
  
  // 初始化
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    block_live_in[block_id] = {};
    block_live_out[block_id] = {};
  }
  
  // 迭代计算直到收敛
  bool changed = true;
  while (changed) {
    changed = false;
    
    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;
      const auto &block = block_pair.second;
      
      // 计算当前块的use和def集合
      std::set<int> use_set, def_set;
      
      for (const auto &inst : block->instruction_list) {
        std::vector<int> used_regs = extractVirtualRegisters(inst.get());
        
        for (int reg : used_regs) {
          if (def_set.find(reg) == def_set.end()) {
            use_set.insert(reg);
          }
        }
        
        // 检查定义 - 修复定义检测逻辑
        for (int reg : used_regs) {
          if (definesVirtualRegister(inst.get(), reg)) {
            def_set.insert(reg);
          }
        }
      }
      
      // 计算新的liveOut：所有后继块的liveIn的并集
      std::set<int> new_live_out;
      for (int succ : successors[block_id]) {
        new_live_out.insert(block_live_in[succ].begin(), block_live_in[succ].end());
      }
      
      // 计算新的liveIn：use ∪ (liveOut - def)
      std::set<int> new_live_in = use_set;
      for (int reg : new_live_out) {
        if (def_set.find(reg) == def_set.end()) {
          new_live_in.insert(reg);
        }
      }
      
      // 检查是否有变化
      if (new_live_in != block_live_in[block_id] || 
          new_live_out != block_live_out[block_id]) {
        block_live_in[block_id] = new_live_in;
        block_live_out[block_id] = new_live_out;
        changed = true;
      }
    }
  }
  
  // 第三步：计算指令级别的生存期
  std::map<int, int> virtual_first_def;
  std::map<int, int> virtual_last_use;

  int position = 0;

  for (const auto &block_pair : blocks) {
    const auto &block = block_pair.second;

    for (const auto &inst : block->instruction_list) {
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

  // 创建生存期对象
  live_ranges.reserve(virtual_first_def.size());

  for (const auto &def_pair : virtual_first_def) {
    int virtual_reg = def_pair.first;
    int start_pos = def_pair.second;
    int end_pos = virtual_last_use[virtual_reg];

    live_ranges.emplace_back(virtual_reg, start_pos, end_pos);
    virtual_to_range[virtual_reg] = &live_ranges.back();
  }

  // 按开始位置排序
  std::sort(live_ranges.begin(), live_ranges.end(),
            [](const LiveRange &a, const LiveRange &b) {
              return a.start_pos < b.start_pos;
            });
}

std::vector<int>
RegisterAllocator::extractVirtualRegisters(RiscvInstruction *inst) {
  std::vector<int> virtuals;

  // 从指令的操作数中提取虚拟寄存器
  auto extractFromOperand = [&](const std::unique_ptr<RiscvOperand> &operand) {
    if (operand) {
      if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(operand.get())) {
        int reg_no = reg_operand->GetRegNo();
        if (reg_no >= 0) { // 虚拟寄存器是非负数（包含%r0）
          virtuals.push_back(reg_no);
        }
      } else if (auto *ptr_operand =
                     dynamic_cast<RiscvPtrOperand *>(operand.get())) {
        if (ptr_operand->base_reg) {
          if (auto *base_reg = dynamic_cast<RiscvRegOperand *>(
                  ptr_operand->base_reg.get())) {
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
  if (auto *arith_inst = dynamic_cast<RiscvArithmeticInstruction *>(inst)) {
    extractFromOperand(arith_inst->rd);
    extractFromOperand(arith_inst->rs1);
    extractFromOperand(arith_inst->rs2);
  } else if (auto *imm_inst = dynamic_cast<RiscvImmediateInstruction *>(inst)) {
    extractFromOperand(imm_inst->rd);
    extractFromOperand(imm_inst->rs1);
  } else if (auto *mem_inst = dynamic_cast<RiscvMemoryInstruction *>(inst)) {
    extractFromOperand(mem_inst->reg);
    extractFromOperand(mem_inst->address);
  } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction *>(inst)) {
    extractFromOperand(branch_inst->rs1);
    extractFromOperand(branch_inst->rs2);
  } else if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction *>(inst)) {
    extractFromOperand(jump_inst->rd);
  } else if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
    for (auto &arg : call_inst->args) {
      extractFromOperand(arg);
    }
  } else if (auto *pseudo_inst = dynamic_cast<RiscvPseudoInstruction *>(inst)) {
    extractFromOperand(pseudo_inst->rd);
    extractFromOperand(pseudo_inst->operand);
  } else if (auto *fadd_inst = dynamic_cast<RiscvFAddInstruction *>(inst)) {
    extractFromOperand(fadd_inst->rd);
    extractFromOperand(fadd_inst->rs1);
    extractFromOperand(fadd_inst->rs2);
  } else if (auto *fsub_inst = dynamic_cast<RiscvFSubInstruction *>(inst)) {
    extractFromOperand(fsub_inst->rd);
    extractFromOperand(fsub_inst->rs1);
    extractFromOperand(fsub_inst->rs2);
  } else if (auto *fmul_inst = dynamic_cast<RiscvFMulInstruction *>(inst)) {
    extractFromOperand(fmul_inst->rd);
    extractFromOperand(fmul_inst->rs1);
    extractFromOperand(fmul_inst->rs2);
  } else if (auto *fdiv_inst = dynamic_cast<RiscvFDivInstruction *>(inst)) {
    extractFromOperand(fdiv_inst->rd);
    extractFromOperand(fdiv_inst->rs1);
    extractFromOperand(fdiv_inst->rs2);
  }
  // 具体指令类型支持
  else if (auto *add_inst = dynamic_cast<RiscvAddInstruction *>(inst)) {
    extractFromOperand(add_inst->rd);
    extractFromOperand(add_inst->rs1);
    extractFromOperand(add_inst->rs2);
  } else if (auto *sub_inst = dynamic_cast<RiscvSubInstruction *>(inst)) {
    extractFromOperand(sub_inst->rd);
    extractFromOperand(sub_inst->rs1);
    extractFromOperand(sub_inst->rs2);
  } else if (auto *mul_inst = dynamic_cast<RiscvMulInstruction *>(inst)) {
    extractFromOperand(mul_inst->rd);
    extractFromOperand(mul_inst->rs1);
    extractFromOperand(mul_inst->rs2);
  } else if (auto *div_inst = dynamic_cast<RiscvDivInstruction *>(inst)) {
    extractFromOperand(div_inst->rd);
    extractFromOperand(div_inst->rs1);
    extractFromOperand(div_inst->rs2);
  } else if (auto *mod_inst = dynamic_cast<RiscvModInstruction *>(inst)) {
    extractFromOperand(mod_inst->rd);
    extractFromOperand(mod_inst->rs1);
    extractFromOperand(mod_inst->rs2);
  } else if (auto *addi_inst = dynamic_cast<RiscvAddiInstruction *>(inst)) {
    extractFromOperand(addi_inst->rd);
    extractFromOperand(addi_inst->rs1);
  } else if (auto *li_inst = dynamic_cast<RiscvLiInstruction *>(inst)) {
    extractFromOperand(li_inst->rd);
  } else if (auto *ld_inst = dynamic_cast<RiscvLdInstruction *>(inst)) {
    extractFromOperand(ld_inst->rd);
    extractFromOperand(ld_inst->address);
  } else if (auto *sd_inst = dynamic_cast<RiscvSdInstruction *>(inst)) {
    extractFromOperand(sd_inst->reg);
    extractFromOperand(sd_inst->address);
  } else if (auto *jr_inst = dynamic_cast<RiscvJrInstruction *>(inst)) {
    extractFromOperand(jr_inst->rd);
  }

  return virtuals;
}

void RegisterAllocator::performLinearScanAllocation() {
  std::vector<LiveRange *> active; // 当前活跃的生存期

  for (auto &range : live_ranges) {
    // 跳过已经预分配的虚拟寄存器
    if (virtual_to_physical.find(range.virtual_reg) !=
        virtual_to_physical.end()) {
      continue;
    }
    // 移除已过期的生存期
    active.erase(std::remove_if(active.begin(), active.end(),
                                [&](LiveRange *active_range) {
                                  if (active_range->end_pos < range.start_pos) {
                                    // 释放物理寄存器（只有当虚拟寄存器确实有物理寄存器分配时）
                                    auto it = virtual_to_physical.find(
                                        active_range->virtual_reg);
                                    if (it != virtual_to_physical.end()) {
                                      int physical_reg = it->second;
                                      physical_to_virtual.erase(physical_reg);
                                    }
                                    return true;
                                  }
                                  return false;
                                }),
                 active.end());

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
  // 第一优先级：临时寄存器（caller-saved，不需要保存恢复）
  for (auto &reg : available_registers) {
    if (reg.is_available && !reg.is_callee_saved &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  // 第二优先级：参数寄存器a2-a7（caller-saved）
  for (auto &reg : available_registers) {
    if (reg.is_available && reg.reg_no >= 12 && reg.reg_no <= 17 &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  // 第三优先级：保存寄存器（callee-saved，需要保存恢复）
  for (auto &reg : available_registers) {
    if (reg.is_available && reg.is_callee_saved &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  return -1; // 没有可用寄存器
}

int RegisterAllocator::selectVictimRegister(int current_pos) {
  int victim = -1;
  int latest_end = current_pos;
  int victim_priority = -1;

  // 选择结束位置最晚且优先级最低的寄存器作为受害者
  for (const auto &pair : physical_to_virtual) {
    int physical_reg = pair.first;
    int virtual_reg = pair.second;

    auto it = virtual_to_range.find(virtual_reg);
    if (it != virtual_to_range.end()) {
      LiveRange *range = it->second;
      if (range && range->end_pos > latest_end) {
        // 计算寄存器优先级（临时寄存器 > 参数寄存器 > 保存寄存器）
        int priority = 0;
        for (const auto &reg : available_registers) {
          if (reg.reg_no == physical_reg) {
            if (!reg.is_callee_saved) {
              priority = 1; // 临时寄存器
            } else {
              priority = 0; // 保存寄存器
            }
            break;
          }
        }
        
        // 优先选择优先级低的寄存器作为受害者
        if (range->end_pos > latest_end || 
            (range->end_pos == latest_end && priority < victim_priority)) {
        latest_end = range->end_pos;
        victim = physical_reg;
          victim_priority = priority;
        }
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
    LiveRange *range = range_it->second;
    range->is_spilled = true;
    spilled_virtuals.insert(virtual_reg);
    spill_slots[virtual_reg] = next_spill_slot++;

    // std::cout << "溢出虚拟寄存器 %r" << virtual_reg << " 到溢出槽 "
    //           << spill_slots[virtual_reg] << std::endl;
  }

  // 释放物理寄存器
  virtual_to_physical.erase(virtual_reg);
  physical_to_virtual.erase(physical_reg);
}

void RegisterAllocator::insertSpillCode(
    std::map<int, std::unique_ptr<RiscvBlock>> &blocks) {
  // 为每个溢出的虚拟寄存器插入load/store代码
  for (int virtual_reg : spilled_virtuals) {
    int offset = getSpillOffset(virtual_reg);
    
    // 遍历所有基本块
    for (auto &block_pair : blocks) {
      auto &block = block_pair.second;
      
      // 收集需要插入load指令的位置（使用点）
      std::vector<std::pair<std::unique_ptr<RiscvInstruction>*, size_t>> load_points;
      // 收集需要插入store指令的位置（定义点）
      std::vector<std::pair<std::unique_ptr<RiscvInstruction>*, size_t>> store_points;
      
      // 分析指令列表，找到使用和定义点
      for (size_t i = 0; i < block->instruction_list.size(); i++) {
        auto &inst = block->instruction_list[i];
        
        // 检查指令是否使用该虚拟寄存器
        if (usesVirtualRegister(inst.get(), virtual_reg)) {
          load_points.emplace_back(&inst, i);
        }
        
        // 检查指令是否定义该虚拟寄存器
        if (definesVirtualRegister(inst.get(), virtual_reg)) {
          store_points.emplace_back(&inst, i);
        }
      }
      
      // 插入load指令（在使用前）
      for (auto &[inst_ptr, pos] : load_points) {
        // 创建临时物理寄存器用于load
        int temp_reg = findFreeRegister();
        if (temp_reg == -1) {
          // 如果没有可用寄存器，使用t6作为临时寄存器
          temp_reg = 31; // t6
        }
        
        // 创建load指令：ld temp_reg, offset(sp)
        auto sp_reg = std::make_unique<RiscvRegOperand>(-2); // sp寄存器
        auto addr = std::make_unique<RiscvPtrOperand>(offset, std::move(sp_reg));
        auto temp_reg_operand = std::make_unique<RiscvRegOperand>(-temp_reg);
        
        auto load_inst = std::make_unique<RiscvLdInstruction>(
            std::move(temp_reg_operand), std::move(addr));
        
        // 在指令前插入load
        block->instruction_list.insert(block->instruction_list.begin() + pos, 
                                      std::move(load_inst));
        
        // 更新后续指令的位置
        for (auto &[other_inst, other_pos] : load_points) {
          if (other_pos > pos) other_pos++;
        }
        for (auto &[other_inst, other_pos] : store_points) {
          if (other_pos > pos) other_pos++;
        }
      }
      
      // 插入store指令（在定义后）
      for (auto &[inst_ptr, pos] : store_points) {
        // 创建store指令：sd temp_reg, offset(sp)
        auto sp_reg = std::make_unique<RiscvRegOperand>(-2); // sp寄存器
        auto addr = std::make_unique<RiscvPtrOperand>(offset, std::move(sp_reg));
        
        // 找到对应的临时寄存器（这里简化处理，实际需要跟踪）
        int temp_reg = 31; // 使用t6作为临时寄存器
        auto temp_reg_operand = std::make_unique<RiscvRegOperand>(-temp_reg);
        
        auto store_inst = std::make_unique<RiscvSdInstruction>(
            std::move(temp_reg_operand), std::move(addr));
        
        // 在指令后插入store
        block->instruction_list.insert(block->instruction_list.begin() + pos + 1, 
                                      std::move(store_inst));
        
        // 更新后续指令的位置
        for (auto &[other_inst, other_pos] : load_points) {
          if (other_pos > pos) other_pos++;
        }
        for (auto &[other_inst, other_pos] : store_points) {
          if (other_pos > pos) other_pos++;
        }
      }
    }
  }
}

// 辅助函数：检查指令是否使用虚拟寄存器
bool RegisterAllocator::usesVirtualRegister(RiscvInstruction* inst, int virtual_reg) {
  std::vector<int> used_regs = extractVirtualRegisters(inst);
  return std::find(used_regs.begin(), used_regs.end(), virtual_reg) != used_regs.end();
}

// 辅助函数：检查指令是否定义虚拟寄存器
bool RegisterAllocator::definesVirtualRegister(RiscvInstruction* inst, int virtual_reg) {
  // 根据指令类型检查目标寄存器
  if (auto *arith_inst = dynamic_cast<RiscvArithmeticInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(arith_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *imm_inst = dynamic_cast<RiscvImmediateInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(imm_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *mem_inst = dynamic_cast<RiscvMemoryInstruction *>(inst)) {
    if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(mem_inst->reg.get())) {
      return reg_operand->GetRegNo() == virtual_reg;
    }
  } else if (auto *pseudo_inst = dynamic_cast<RiscvPseudoInstruction *>(inst)) {
    if (pseudo_inst->rd) {
      if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(pseudo_inst->rd.get())) {
        return rd_reg->GetRegNo() == virtual_reg;
      }
    }
  } else if (auto *ld_inst = dynamic_cast<RiscvLdInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(ld_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *sd_inst = dynamic_cast<RiscvSdInstruction *>(inst)) {
    // sd指令不定义寄存器，只使用寄存器
    return false;
  } else if (auto *li_inst = dynamic_cast<RiscvLiInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(li_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *jr_inst = dynamic_cast<RiscvJrInstruction *>(inst)) {
    // jr指令不定义寄存器
    return false;
  } else if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
    // call指令不直接定义寄存器（返回值通过后续mv指令处理）
    return false;
  } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction *>(inst)) {
    // 分支指令不定义寄存器
    return false;
  } else if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(jump_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fadd_inst = dynamic_cast<RiscvFAddInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fadd_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fsub_inst = dynamic_cast<RiscvFSubInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fsub_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fmul_inst = dynamic_cast<RiscvFMulInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fmul_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fdiv_inst = dynamic_cast<RiscvFDivInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fdiv_inst->rd.get())) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  }
  return false;
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
  for (const auto &pair : virtual_to_physical) {
    std::string phys_name = "unknown";
    for (const auto &reg : available_registers) {
      if (reg.reg_no == pair.second) {
        phys_name = reg.name;
        break;
      }
    }
    std::cout << "  %r" << pair.first << " -> " << phys_name << " (x"
              << pair.second << ")" << std::endl;
  }

  if (!spilled_virtuals.empty()) {
    std::cout << "溢出到内存的虚拟寄存器:" << std::endl;
    for (int virtual_reg : spilled_virtuals) {
      std::cout << "  %r" << virtual_reg << " -> 溢出槽 "
                << spill_slots[virtual_reg] << " (偏移 "
                << getSpillOffset(virtual_reg) << ")" << std::endl;
    }
  }

  std::cout << "分配统计:" << std::endl;
  std::cout << "  已分配寄存器: " << virtual_to_physical.size() << std::endl;
  std::cout << "  溢出寄存器: " << spilled_virtuals.size() << std::endl;
  std::cout << "  溢出槽使用: " << next_spill_slot << " 个 ("
            << next_spill_slot * 4 << " 字节)" << std::endl;
}

void RegisterAllocator::printLiveRanges() {
  std::cout << "\n=== 虚拟寄存器生存期 ===" << std::endl;
  for (const auto &range : live_ranges) {
    std::cout << "%r" << range.virtual_reg << ": [" << range.start_pos << ", "
              << range.end_pos << "]";
    if (range.is_spilled) {
      std::cout << " (溢出)";
    }
    std::cout << std::endl;
  }
}

// 集成接口
void RegisterAllocationPass::applyToTranslator(Translator &translator) {
  // std::cout << "\n=== 开始寄存器分配阶段 ===" << std::endl;

  RegisterAllocator allocator;

  // 为每个函数执行寄存器分配
  for (auto &func_pair : translator.riscv.function_block_map) {
    const std::string &func_name = func_pair.first;
    auto &blocks = func_pair.second;

    // 获取函数的栈帧信息
    StackFrameInfo *frame_info = translator.getFunctionStackFrame(func_name);
    if (frame_info) {
      allocator.allocateRegistersForFunction(func_name, blocks, frame_info);
    } else {
      std::cerr << "Warning: No stack frame info found for function: " << func_name << std::endl;
    }
  }

  // std::cout << "寄存器分配完成！" << std::endl;
}

void RegisterAllocator::rewriteInstructions(
    std::map<int, std::unique_ptr<RiscvBlock>> &blocks) {
  // std::cout << "重写指令，替换虚拟寄存器为物理寄存器..." << std::endl;

  for (auto &block_pair : blocks) {
    auto &block = block_pair.second;

    for (auto &inst : block->instruction_list) {
      // 根据指令类型重写操作数
      if (auto *arith_inst =
              dynamic_cast<RiscvArithmeticInstruction *>(inst.get())) {
        rewriteOperand(arith_inst->rd);
        rewriteOperand(arith_inst->rs1);
        rewriteOperand(arith_inst->rs2);
      } else if (auto *imm_inst =
                     dynamic_cast<RiscvImmediateInstruction *>(inst.get())) {
        rewriteOperand(imm_inst->rd);
        rewriteOperand(imm_inst->rs1);
      } else if (auto *mem_inst =
                     dynamic_cast<RiscvMemoryInstruction *>(inst.get())) {
        rewriteOperand(mem_inst->reg);
        rewriteOperand(mem_inst->address);
      } else if (auto *branch_inst =
                     dynamic_cast<RiscvBranchInstruction *>(inst.get())) {
        rewriteOperand(branch_inst->rs1);
        rewriteOperand(branch_inst->rs2);
        // label不需要重写
      } else if (auto *jump_inst =
                     dynamic_cast<RiscvJumpInstruction *>(inst.get())) {
        rewriteOperand(jump_inst->rd);
        // target不需要重写（是label）
      } else if (auto *call_inst =
                     dynamic_cast<RiscvCallInstruction *>(inst.get())) {
        // 函数调用的参数重写
        for (auto &arg : call_inst->args) {
          rewriteOperand(arg);
        }
      } else if (auto *pseudo_inst =
                     dynamic_cast<RiscvPseudoInstruction *>(inst.get())) {
        if (pseudo_inst->rd) {
          rewriteOperand(pseudo_inst->rd);
        }
        if (pseudo_inst->operand) {
          rewriteOperand(pseudo_inst->operand);
        }
      } else if (auto *fadd_inst =
                     dynamic_cast<RiscvFAddInstruction *>(inst.get())) {
        rewriteOperand(fadd_inst->rd);
        rewriteOperand(fadd_inst->rs1);
        rewriteOperand(fadd_inst->rs2);
      } else if (auto *fsub_inst =
                     dynamic_cast<RiscvFSubInstruction *>(inst.get())) {
        rewriteOperand(fsub_inst->rd);
        rewriteOperand(fsub_inst->rs1);
        rewriteOperand(fsub_inst->rs2);
      } else if (auto *fmul_inst =
                     dynamic_cast<RiscvFMulInstruction *>(inst.get())) {
        rewriteOperand(fmul_inst->rd);
        rewriteOperand(fmul_inst->rs1);
        rewriteOperand(fmul_inst->rs2);
      } else if (auto *fdiv_inst =
                     dynamic_cast<RiscvFDivInstruction *>(inst.get())) {
        rewriteOperand(fdiv_inst->rd);
        rewriteOperand(fdiv_inst->rs1);
        rewriteOperand(fdiv_inst->rs2);
      } else if (auto *add_inst =
                     dynamic_cast<RiscvAddInstruction *>(inst.get())) {
        rewriteOperand(add_inst->rd);
        rewriteOperand(add_inst->rs1);
        rewriteOperand(add_inst->rs2);
      } else if (auto *sub_inst =
                     dynamic_cast<RiscvSubInstruction *>(inst.get())) {
        rewriteOperand(sub_inst->rd);
        rewriteOperand(sub_inst->rs1);
        rewriteOperand(sub_inst->rs2);
      } else if (auto *mul_inst =
                     dynamic_cast<RiscvMulInstruction *>(inst.get())) {
        rewriteOperand(mul_inst->rd);
        rewriteOperand(mul_inst->rs1);
        rewriteOperand(mul_inst->rs2);
      } else if (auto *div_inst =
                     dynamic_cast<RiscvDivInstruction *>(inst.get())) {
        rewriteOperand(div_inst->rd);
        rewriteOperand(div_inst->rs1);
        rewriteOperand(div_inst->rs2);
      } else if (auto *mod_inst =
                     dynamic_cast<RiscvModInstruction *>(inst.get())) {
        rewriteOperand(mod_inst->rd);
        rewriteOperand(mod_inst->rs1);
        rewriteOperand(mod_inst->rs2);
      } else if (auto *addi_inst =
                     dynamic_cast<RiscvAddiInstruction *>(inst.get())) {
        rewriteOperand(addi_inst->rd);
        rewriteOperand(addi_inst->rs1);
      } else if (auto *li_inst =
                     dynamic_cast<RiscvLiInstruction *>(inst.get())) {
        rewriteOperand(li_inst->rd);
      } else if (auto *ld_inst =
                     dynamic_cast<RiscvLdInstruction *>(inst.get())) {
        rewriteOperand(ld_inst->rd);
        rewriteOperand(ld_inst->address);
      } else if (auto *sd_inst =
                     dynamic_cast<RiscvSdInstruction *>(inst.get())) {
        rewriteOperand(sd_inst->reg);
        rewriteOperand(sd_inst->address);
      } else if (auto *jr_inst =
                     dynamic_cast<RiscvJrInstruction *>(inst.get())) {
        rewriteOperand(jr_inst->rd);
      }
    }
  }

  // std::cout << "指令重写完成" << std::endl;
}

void RegisterAllocator::rewriteOperand(std::unique_ptr<RiscvOperand> &operand) {
  if (!operand)
    return;

  // 只处理寄存器操作数
  if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(operand.get())) {
    int virtual_reg = reg_operand->GetRegNo();

    // 如果是虚拟寄存器（非负数）且有分配的物理寄存器
    if (virtual_reg >= 0) {
      auto it = virtual_to_physical.find(virtual_reg);
      if (it != virtual_to_physical.end()) {
        int physical_reg = it->second;
        // 替换为物理寄存器（使用负数表示物理寄存器）
        operand = std::make_unique<RiscvRegOperand>(-physical_reg);
      } else if (isSpilled(virtual_reg)) {
        // 处理溢出寄存器：替换为内存访问
        int offset = getSpillOffset(virtual_reg);
        auto sp_reg = std::make_unique<RiscvRegOperand>(-2); // sp寄存器
        operand = std::make_unique<RiscvPtrOperand>(offset, std::move(sp_reg));
      }
    }
  } else if (auto *ptr_operand =
                 dynamic_cast<RiscvPtrOperand *>(operand.get())) {
    // 重写PTR操作数的基址寄存器
    rewriteOperand(ptr_operand->base_reg);
  }
}

void RegisterAllocator::preAllocateSpecialRegisters(
    const std::map<int, std::unique_ptr<RiscvBlock>> &blocks) {
  // std::cout << "预分配特殊寄存器..." << std::endl;

  for (const auto &block_pair : blocks) {
    const auto &block = block_pair.second;

    for (const auto &inst : block->instruction_list) {
      // 查找函数调用指令
      if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst.get())) {
        // 查找紧接着的 mv 指令，这通常是 call 的返回值赋值
        // 在指令列表中查找当前指令的位置
        auto it = std::find_if(
            block->instruction_list.begin(), block->instruction_list.end(),
            [&](const std::unique_ptr<RiscvInstruction> &ptr) {
              return ptr.get() == call_inst;
            });

        if (it != block->instruction_list.end()) {
          auto next_it = std::next(it);
          if (next_it != block->instruction_list.end()) {
            // 检查下一条指令是否是 mv 指令
            if (auto *mv_inst =
                    dynamic_cast<RiscvPseudoInstruction *>(next_it->get())) {
              if (mv_inst->GetOpcode() == RiscvOpcode::MV && mv_inst->operand) {
                // 检查源操作数是否是 a0 寄存器
                if (auto *src_reg = dynamic_cast<RiscvRegOperand *>(
                        mv_inst->operand.get())) {
                  if (src_reg->GetRegNo() ==
                      -10) { // a0 是 x10，使用负数表示物理寄存器
                    // 检查目标寄存器是否是虚拟寄存器
                    if (auto *dst_reg = dynamic_cast<RiscvRegOperand *>(
                            mv_inst->rd.get())) {
                      int virtual_reg = dst_reg->GetRegNo();
                      if (virtual_reg >= 0) { // 虚拟寄存器
                        // 预分配 a0 寄存器给这个虚拟寄存器
                        virtual_to_physical[virtual_reg] = 10; // a0 是 x10
                        physical_to_virtual[10] = virtual_reg;
                        // std::cout << "  预分配虚拟寄存器 %r" << virtual_reg
                        //           << " -> a0 (x10)" << std::endl;
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
      if (auto *mv_inst = dynamic_cast<RiscvPseudoInstruction *>(inst.get())) {
        if (mv_inst->GetOpcode() == RiscvOpcode::MV && mv_inst->rd &&
            mv_inst->operand) {
          // 检查目标是否是 a0 寄存器
          if (auto *dst_reg =
                  dynamic_cast<RiscvRegOperand *>(mv_inst->rd.get())) {
            if (dst_reg->GetRegNo() == -10) { // a0 是 x10
              // 检查源是否是虚拟寄存器
              if (auto *src_reg =
                      dynamic_cast<RiscvRegOperand *>(mv_inst->operand.get())) {
                int virtual_reg = src_reg->GetRegNo();
                if (virtual_reg >= 0) { // 虚拟寄存器
                  // 预分配 a0 寄存器给这个虚拟寄存器
                  virtual_to_physical[virtual_reg] = 10; // a0 是 x10
                  physical_to_virtual[10] = virtual_reg;
                  // std::cout << "  预分配虚拟寄存器 %r" << virtual_reg
                  //           << " -> a0 (x10)" << std::endl;
                }
              }
            }
          }
        }
      }
    }
  }
=======
#include "../include/register_allocator.h"
#include <algorithm>
#include <iostream>

// Comparator for sorting LiveRange pointers by their end position.
struct LiveRangeEndPosComparator {
    bool operator()(const LiveRange* a, const LiveRange* b) const {
        if (a->end_pos != b->end_pos) {
            return a->end_pos < b->end_pos;
        }
        return a->virtual_reg < b->virtual_reg; // Use virtual_reg for stable ordering
    }
};

RegisterAllocator::RegisterAllocator()
    : next_spill_slot(0), current_frame(nullptr) {
  initializePhysicalRegisters();
}

void RegisterAllocator::initializePhysicalRegisters() {
  // RISC-V寄存器分配策略：
  // - t0-t6: 临时寄存器，调用方保存
  // - s0-s11: 保存寄存器，被调用方保存
  // - a0-a7: 参数寄存器，a0,a1也是返回值寄存器

  // 临时寄存器 (caller-saved) - 注意：不使用x5(tp)，从x6开始
  available_registers.emplace_back(6, "t0", false);  // x6
  available_registers.emplace_back(7, "t1", false);  // x7
  available_registers.emplace_back(28, "t3", false); // x28
  available_registers.emplace_back(29, "t4", false); // x29
  available_registers.emplace_back(30, "t5", false); // x30
  available_registers.emplace_back(31, "t6", false); // x31

  // 保存寄存器 (callee-saved) - 优先级较低，因为需要保存恢复
  available_registers.emplace_back(8, "s0", true);   // x8
  available_registers.emplace_back(9, "s1", true);   // x9
  available_registers.emplace_back(18, "s2", true);  // x18
  available_registers.emplace_back(19, "s3", true);  // x19
  available_registers.emplace_back(20, "s4", true);  // x20
  available_registers.emplace_back(21, "s5", true);  // x21
  available_registers.emplace_back(22, "s6", true);  // x22
  available_registers.emplace_back(23, "s7", true);  // x23
  available_registers.emplace_back(24, "s8", true);  // x24
  available_registers.emplace_back(25, "s9", true);  // x25
  available_registers.emplace_back(26, "s10", true); // x26
  available_registers.emplace_back(27, "s11", true); // x27

  // 参数寄存器a2-a7可以用作临时寄存器（a0,a1保留用于返回值）
  available_registers.emplace_back(12, "a2", false); // x12
  available_registers.emplace_back(13, "a3", false); // x13
  available_registers.emplace_back(14, "a4", false); // x14
  available_registers.emplace_back(15, "a5", false); // x15
  available_registers.emplace_back(16, "a6", false); // x16
  available_registers.emplace_back(17, "a7", false); // x17
}

void RegisterAllocator::allocateRegistersForFunction(
    const std::string &func_name,
    std::map<int, RiscvBlock *> &blocks,
    StackFrameInfo *frame_info) {
  if (!frame_info) {
    throw std::runtime_error("StackFrameInfo is null for function: " + func_name);
  }

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
  for (auto &reg : available_registers) {
    reg.is_available = true;
  }

  try {
    // 1. 计算生存期
    computeLiveRanges(blocks);

    // 2. 按变量类型分类分配寄存器
    allocateByCategory();

    // 3. 插入溢出代码
    insertSpillCode(blocks);

    // 4. 重写指令，替换虚拟寄存器为物理寄存器
    rewriteInstructions(blocks);

    // 5. 更新栈帧大小（考虑溢出）
    if (!spilled_virtuals.empty()) {
      int spill_area_size = next_spill_slot * 8; // 每个溢出槽8字节
      current_frame->local_vars_size += spill_area_size;
      current_frame->calculateTotalSize();
      
      // 检查栈帧大小是否合理
      if (current_frame->total_frame_size > 1024 * 1024) { // 1MB限制
        throw std::runtime_error("Stack frame too large: " + 
                                std::to_string(current_frame->total_frame_size) + 
                                " bytes for function: " + func_name);
      }
    }

    // 6. 输出分配结果
    printAllocationResult();

    // 更新所有基本块中的栈帧大小显示和相关指令
    for (auto &block_pair : blocks) {
      auto &block = block_pair.second;
      if (block->stack_size > 0) { // 只更新已设置过栈帧大小的块
        int old_size = block->stack_size;
        block->stack_size = current_frame->total_frame_size;

        // 更新栈指针调整指令
        for (auto &inst : block->instruction_list) {
          if (auto *addi_inst = dynamic_cast<RiscvAddiInstruction *>(inst)) {
            // 检查是否是栈指针调整指令
            if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(addi_inst->rd)) {
              if (auto *rs1_reg = dynamic_cast<RiscvRegOperand *>(addi_inst->rs1)) {
                // sp寄存器是x2，在我们的系统中表示为-2
                if (rd_reg->GetRegNo() == -2 && rs1_reg->GetRegNo() == -2) {
                  // 这是栈指针调整指令
                  if (addi_inst->immediate == -old_size) {
                    // 栈分配指令 (负数)
                    addi_inst->immediate = -current_frame->total_frame_size;
                  } else if (addi_inst->immediate == old_size) {
                    // 栈释放指令 (正数)
                    addi_inst->immediate = current_frame->total_frame_size;
                  }
                }
              }
            }
          }
        }
      }
    }
  
  } catch (const std::exception& e) {
    std::cerr << "Error in register allocation for function " << func_name 
              << ": " << e.what() << std::endl;
    throw;
  }
}

// 新增：按类型分配寄存器
void RegisterAllocator::allocateByCategory() {
  // 分类虚拟寄存器：局部vs全局，整数vs浮点
  std::vector<LiveRange*> global_int_ranges;
  std::vector<LiveRange*> local_int_ranges;
  // 暂时不区分浮点，因为当前实现主要是整数
  
  for (auto &range : live_ranges) {
    if (isLocalVariable(range.virtual_reg)) {
      local_int_ranges.push_back(&range);
    } else {
      global_int_ranges.push_back(&range);
    }
  }
  
  // 为全局变量分配保存寄存器(s0-s11) - 注意：s0通常用作帧指针，从s1开始
  std::set<int> global_regs = {9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
  allocateRangesWithRegisters(global_int_ranges, global_regs);
  
  // 为局部变量分配临时寄存器(t0-t6)和参数寄存器(a2-a7) - 不包括x5(tp)
  std::set<int> local_regs = {6, 7, 28, 29, 30, 31, 12, 13, 14, 15, 16, 17};
  allocateRangesWithRegisters(local_int_ranges, local_regs);
}

// 判断是否为局部变量（简化版本）
bool RegisterAllocator::isLocalVariable(int virtual_reg) {
  // 简化判断：如果生存期跨度较小，认为是局部变量
  auto range_it = virtual_to_range.find(virtual_reg);
  if (range_it != virtual_to_range.end()) {
    LiveRange* range = range_it->second;
    return (range->end_pos - range->start_pos) < 10; // 简化阈值
  }
  return true; // 默认认为是局部变量
}

// 为特定范围分配特定寄存器集合
void RegisterAllocator::allocateRangesWithRegisters(
    std::vector<LiveRange*> &ranges,
    std::set<int> &reg_set) {
    
  // 按开始位置排序
  std::sort(ranges.begin(), ranges.end(),
            [](const LiveRange* a, const LiveRange* b) {
              return a->start_pos < b->start_pos;
            });

  std::set<LiveRange *, LiveRangeEndPosComparator> active;
  std::set<int> available_regs = reg_set;

  for (auto *range : ranges) {
    // Skip already allocated ranges
    if (virtual_to_physical.find(range->virtual_reg) != virtual_to_physical.end()) {
      continue;
    }
    
    // Expire old intervals
    auto it = active.begin();
    while (it != active.end() && (*it)->end_pos < range->start_pos) {
        auto map_it = virtual_to_physical.find((*it)->virtual_reg);
        if (map_it != virtual_to_physical.end()) {
            int physical_reg = map_it->second;
            if (reg_set.find(physical_reg) != reg_set.end()) {
                available_regs.insert(physical_reg);
                physical_to_virtual.erase(physical_reg);
            }
        }
        it = active.erase(it);
    }

    if (!available_regs.empty()) {
      // Allocate register
      int physical_reg = *available_regs.begin();
      available_regs.erase(physical_reg);
      virtual_to_physical[range->virtual_reg] = physical_reg;
      physical_to_virtual[physical_reg] = range->virtual_reg;
      active.insert(range);
    } else {
      // Spill
      if (!active.empty()) {
        auto last_active = std::prev(active.end());
        LiveRange* victim_range = *last_active;
        
        if (victim_range->end_pos > range->end_pos) {
          // Spill victim
          int victim_phys_reg = virtual_to_physical.at(victim_range->virtual_reg);
          spillRegister(victim_phys_reg, range->start_pos);
          active.erase(last_active);
          available_regs.insert(victim_phys_reg);
          
          // Allocate to current range
          int physical_reg = *available_regs.begin();
          available_regs.erase(physical_reg);
          virtual_to_physical[range->virtual_reg] = physical_reg;
          physical_to_virtual[physical_reg] = range->virtual_reg;
          active.insert(range);
        } else {
          // Spill current
          range->is_spilled = true;
          spilled_virtuals.insert(range->virtual_reg);
          spill_slots[range->virtual_reg] = next_spill_slot++;
        }
      } else {
        // No active intervals, spill current
        range->is_spilled = true;
        spilled_virtuals.insert(range->virtual_reg);
        spill_slots[range->virtual_reg] = next_spill_slot++;
      }
    }
  }
}

void RegisterAllocator::computeLiveRanges(
    const std::map<int, RiscvBlock *> &blocks) {
  // 第一步：构建控制流图
  std::map<int, std::vector<int>> successors;
  std::map<int, std::vector<int>> predecessors;
  
  // 初始化控制流图
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    successors[block_id] = {};
    predecessors[block_id] = {};
  }
  
  // 分析跳转指令构建控制流
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    const auto &block = block_pair.second;
    
    if (block->instruction_list.empty()) {
      // 空块，顺序执行到下一块
      auto next_it = blocks.upper_bound(block_id);
      if (next_it != blocks.end()) {
        int next_block_id = next_it->first;
        successors[block_id].push_back(next_block_id);
        predecessors[next_block_id].push_back(block_id);
      }
      continue;
    }
    
    // 检查最后一条指令
    const auto &last_inst = block->instruction_list.back();
    
    // 根据指令类型确定后继块
    if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction*>(last_inst)) {
      // 无条件跳转
      // 尝试解析跳转目标
      if (auto *label_operand = dynamic_cast<RiscvLabelOperand*>(jump_inst->target)) {
        std::string label_name = label_operand->GetFullName();
        // 解析标签名称，格式应该是 ".L" + block_id
        if (label_name.substr(0, 2) == ".L") {
          try {
            int target_block = std::stoi(label_name.substr(2));
            if (blocks.find(target_block) != blocks.end()) {
              successors[block_id].push_back(target_block);
              predecessors[target_block].push_back(block_id);
            }
          } catch (const std::exception&) {
            // 解析失败，使用简化处理
            auto next_it = blocks.upper_bound(block_id);
            if (next_it != blocks.end()) {
              int next_block_id = next_it->first;
              successors[block_id].push_back(next_block_id);
              predecessors[next_block_id].push_back(block_id);
            }
          }
        }
      } else {
        // 无法解析标签，使用简化处理
        auto next_it = blocks.upper_bound(block_id);
        if (next_it != blocks.end()) {
          int next_block_id = next_it->first;
          successors[block_id].push_back(next_block_id);
          predecessors[next_block_id].push_back(block_id);
        }
      }
    } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction*>(last_inst)) {
      // 条件跳转，有两个后继
      auto next_it = blocks.upper_bound(block_id);
      if (next_it != blocks.end()) {
        int next_block_id = next_it->first;
        successors[block_id].push_back(next_block_id);
        predecessors[next_block_id].push_back(block_id);
      }
      // 尝试解析跳转目标
      if (auto *label_operand = dynamic_cast<RiscvLabelOperand*>(branch_inst->label)) {
        std::string label_name = label_operand->GetFullName();
        if (label_name.substr(0, 2) == ".L") {
          try {
            int target_block = std::stoi(label_name.substr(2));
            if (blocks.find(target_block) != blocks.end()) {
              successors[block_id].push_back(target_block);
              predecessors[target_block].push_back(block_id);
            }
          } catch (const std::exception&) {
            // 解析失败，跳过
          }
        }
      }
    } else {
      // 其他指令，顺序执行
      auto next_it = blocks.upper_bound(block_id);
      if (next_it != blocks.end()) {
        int next_block_id = next_it->first;
        successors[block_id].push_back(next_block_id);
        predecessors[next_block_id].push_back(block_id);
      }
    }
  }
  
  // 第二步：计算每个基本块的liveIn和liveOut
  std::map<int, std::set<int>> block_live_in;
  std::map<int, std::set<int>> block_live_out;
  
  // 初始化
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    block_live_in[block_id] = {};
    block_live_out[block_id] = {};
  }
  
  // 迭代计算直到收敛
  bool changed = true;
  int iteration = 0;
  while (changed) {
    changed = false;
    
    for (const auto &block_pair : blocks) {
      int block_id = block_pair.first;
      const auto &block = block_pair.second;
      
      // 计算当前块的use和def集合
      std::set<int> use_set, def_set;
      
      for (size_t i = 0; i < block->instruction_list.size(); i++) {
        const auto &inst = block->instruction_list[i];
        
        if (!inst) {
          std::cerr << "错误: 基本块 " << block_id << " 中第 " << i << " 条指令为空!" << std::endl;
          continue;
        }
        
        std::vector<int> used_regs = extractVirtualRegisters(inst);
        
        // 先处理使用，再处理定义（按照指令中的顺序）
        for (int reg : used_regs) {
          // 如果这个寄存器不是被当前指令定义的，且之前没有被定义过，则是使用
          if (!definesVirtualRegister(inst, reg) && def_set.find(reg) == def_set.end()) {
            use_set.insert(reg);
          }
        }
        
        // 再处理定义
        for (int reg : used_regs) {
          if (definesVirtualRegister(inst, reg)) {
            def_set.insert(reg);
          }
        }
      }
      
      // 计算新的liveOut：所有后继块的liveIn的并集
      std::set<int> new_live_out;
      for (int succ : successors[block_id]) {
        new_live_out.insert(block_live_in[succ].begin(), block_live_in[succ].end());
      }
      
      // 计算新的liveIn：use ∪ (liveOut - def)
      std::set<int> new_live_in = use_set;
      for (int reg : new_live_out) {
        if (def_set.find(reg) == def_set.end()) {
          new_live_in.insert(reg);
        }
      }
      
      // 检查是否有变化
      if (new_live_in != block_live_in[block_id] || 
          new_live_out != block_live_out[block_id]) {
        block_live_in[block_id] = new_live_in;
        block_live_out[block_id] = new_live_out;
        changed = true;
      }
    }
  }
  
  // 第三步：计算指令级别的生存期
  std::map<int, int> virtual_first_def;
  std::map<int, int> virtual_last_use;

  int position = 0;
  std::map<int, int> block_start_pos;
  std::map<int, int> block_end_pos;

  // 首先记录每个基本块的起始和结束位置
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    const auto &block = block_pair.second;
    
    block_start_pos[block_id] = position;
    position += block->instruction_list.size();
    block_end_pos[block_id] = position - 1;
  }

  // 重新遍历基本块，为每个虚拟寄存器计算正确的生存期
  position = 0;
  
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    const auto &block = block_pair.second;

    for (size_t i = 0; i < block->instruction_list.size(); i++) {
      const auto &inst = block->instruction_list[i];
      
      if (!inst) {
        std::cerr << "错误: 在生存期计算中发现空指令!" << std::endl;
        position++;
        continue;
      }
      
      // 分别处理使用和定义
      std::vector<int> used_virtuals = extractVirtualRegisters(inst);

      // 先处理使用（在定义之前）
      for (int virtual_reg : used_virtuals) {
        // 只有不是被定义的寄存器才算使用
        if (!definesVirtualRegister(inst, virtual_reg)) {
          virtual_last_use[virtual_reg] = position;
          // 如果还没有首次定义记录，说明是参数或全局变量，从位置0开始
          if (virtual_first_def.find(virtual_reg) == virtual_first_def.end()) {
            virtual_first_def[virtual_reg] = 0;
          }
        }
      }

      // 再处理定义
      for (int virtual_reg : used_virtuals) {
        if (definesVirtualRegister(inst, virtual_reg)) {
          // 首次定义位置
          if (virtual_first_def.find(virtual_reg) == virtual_first_def.end()) {
            virtual_first_def[virtual_reg] = position;
          }
          // 定义也算最后使用（自己使用）
          virtual_last_use[virtual_reg] = position;
        }
      }

      position++;
    }
  }

  // 扩展跨基本块使用的变量的生存期
  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    
    // 对于在此基本块liveOut中的变量，扩展其生存期到块末尾
    for (int virtual_reg : block_live_out[block_id]) {
      if (virtual_last_use.find(virtual_reg) != virtual_last_use.end()) {
        virtual_last_use[virtual_reg] = std::max(virtual_last_use[virtual_reg], 
                                                  block_end_pos[block_id]);
      }
    }
    
    // 对于在此基本块liveIn中的变量，扩展其生存期到块开始
    for (int virtual_reg : block_live_in[block_id]) {
      if (virtual_first_def.find(virtual_reg) == virtual_first_def.end() ||
          virtual_first_def[virtual_reg] > block_start_pos[block_id]) {
        virtual_first_def[virtual_reg] = block_start_pos[block_id];
      }
    }
  }

  // 创建生存期对象
  live_ranges.reserve(virtual_first_def.size());

  for (const auto &def_pair : virtual_first_def) {
    int virtual_reg = def_pair.first;
    int start_pos = def_pair.second;
    
    int end_pos = virtual_last_use.find(virtual_reg) != virtual_last_use.end() 
                    ? virtual_last_use[virtual_reg] 
                    : start_pos; // 如果没有使用，生存期就是定义点

    // 确保生存期至少有一个位置
    if (end_pos < start_pos) {
      end_pos = start_pos;
    }

    live_ranges.emplace_back(virtual_reg, start_pos, end_pos);
  }

  // 按开始位置排序
  std::sort(live_ranges.begin(), live_ranges.end(),
            [](const LiveRange &a, const LiveRange &b) {
              return a.start_pos < b.start_pos;
            });

  // 重新建立映射（排序后指针才是正确的）
  virtual_to_range.clear();
  for (auto &range : live_ranges) {
    virtual_to_range[range.virtual_reg] = &range;
  }
}

std::vector<int>
RegisterAllocator::extractVirtualRegisters(RiscvInstruction *inst) {
  std::vector<int> virtuals;

  if (!inst) {
    std::cerr << "错误: 空指令指针!" << std::endl;
    return virtuals;
  }

  // 从指令的操作数中提取虚拟寄存器
  auto extractFromOperand = [&](RiscvOperand *operand) {
    if (operand) {
      if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(operand)) {
        int reg_no = reg_operand->GetRegNo();
        if (reg_no >= 0) { // 虚拟寄存器是非负数（包含%r0）
          virtuals.push_back(reg_no);
        }
      } else if (auto *ptr_operand =
                     dynamic_cast<RiscvPtrOperand *>(operand)) {
        if (ptr_operand->base_reg) {
          if (auto *base_reg = dynamic_cast<RiscvRegOperand *>(
                  ptr_operand->base_reg)) {
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
  if (auto *add_inst = dynamic_cast<RiscvAddInstruction *>(inst)) {
    extractFromOperand(add_inst->rd);
    extractFromOperand(add_inst->rs1);
    extractFromOperand(add_inst->rs2);
  } else if (auto *sub_inst = dynamic_cast<RiscvSubInstruction *>(inst)) {
    extractFromOperand(sub_inst->rd);
    extractFromOperand(sub_inst->rs1);
    extractFromOperand(sub_inst->rs2);
  } else if (auto *mul_inst = dynamic_cast<RiscvMulInstruction *>(inst)) {
    extractFromOperand(mul_inst->rd);
    extractFromOperand(mul_inst->rs1);
    extractFromOperand(mul_inst->rs2);
  } else if (auto *div_inst = dynamic_cast<RiscvDivInstruction *>(inst)) {
    extractFromOperand(div_inst->rd);
    extractFromOperand(div_inst->rs1);
    extractFromOperand(div_inst->rs2);
  } else if (auto *mod_inst = dynamic_cast<RiscvModInstruction *>(inst)) {
    extractFromOperand(mod_inst->rd);
    extractFromOperand(mod_inst->rs1);
    extractFromOperand(mod_inst->rs2);
  } else if (auto *addi_inst = dynamic_cast<RiscvAddiInstruction *>(inst)) {
    extractFromOperand(addi_inst->rd);
    extractFromOperand(addi_inst->rs1);
  } else if (auto *li_inst = dynamic_cast<RiscvLiInstruction *>(inst)) {
    extractFromOperand(li_inst->rd);
  } else if (auto *ld_inst = dynamic_cast<RiscvLdInstruction *>(inst)) {
    extractFromOperand(ld_inst->rd);
    extractFromOperand(ld_inst->address);
  } else if (auto *lw_inst = dynamic_cast<RiscvLwInstruction *>(inst)) {
    extractFromOperand(lw_inst->rd);
    extractFromOperand(lw_inst->address);
  } else if (auto *sd_inst = dynamic_cast<RiscvSdInstruction *>(inst)) {
    extractFromOperand(sd_inst->reg);
    extractFromOperand(sd_inst->address);
  } else if (auto *sw_inst = dynamic_cast<RiscvSwInstruction *>(inst)) {
    extractFromOperand(sw_inst->rs);
    extractFromOperand(sw_inst->address);
  } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction *>(inst)) {
    extractFromOperand(branch_inst->rs1);
    extractFromOperand(branch_inst->rs2);
  } else if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction *>(inst)) {
    extractFromOperand(jump_inst->rd);
  } else if (auto *jr_inst = dynamic_cast<RiscvJrInstruction *>(inst)) {
    extractFromOperand(jr_inst->rd);
  } else if (auto *mv_inst = dynamic_cast<RiscvMvInstruction *>(inst)) {
    extractFromOperand(mv_inst->rd);
    extractFromOperand(mv_inst->rs1);
  } else if (auto *la_inst = dynamic_cast<RiscvLaInstruction *>(inst)) {
    extractFromOperand(la_inst->rd);
    extractFromOperand(la_inst->address);
  } else if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
    for (auto &arg : call_inst->args) {
      extractFromOperand(arg);
    }
  } else if (auto *fadd_inst = dynamic_cast<RiscvFAddInstruction *>(inst)) {
    extractFromOperand(fadd_inst->rd);
    extractFromOperand(fadd_inst->rs1);
    extractFromOperand(fadd_inst->rs2);
  } else if (auto *fsub_inst = dynamic_cast<RiscvFSubInstruction *>(inst)) {
    extractFromOperand(fsub_inst->rd);
    extractFromOperand(fsub_inst->rs1);
    extractFromOperand(fsub_inst->rs2);
  } else if (auto *fmul_inst = dynamic_cast<RiscvFMulInstruction *>(inst)) {
    extractFromOperand(fmul_inst->rd);
    extractFromOperand(fmul_inst->rs1);
    extractFromOperand(fmul_inst->rs2);
  } else if (auto *fdiv_inst = dynamic_cast<RiscvFDivInstruction *>(inst)) {
    extractFromOperand(fdiv_inst->rd);
    extractFromOperand(fdiv_inst->rs1);
    extractFromOperand(fdiv_inst->rs2);
  } else if (auto *fmv_inst = dynamic_cast<RiscvFmvInstruction *>(inst)) {
    extractFromOperand(fmv_inst->rd);
    extractFromOperand(fmv_inst->rs1);
  } else if (auto *flw_inst = dynamic_cast<RiscvFlwInstruction *>(inst)) {
    extractFromOperand(flw_inst->rd);
    extractFromOperand(flw_inst->address);
  } else if (auto *fsw_inst = dynamic_cast<RiscvFswInstruction *>(inst)) {
    extractFromOperand(fsw_inst->rs);
    extractFromOperand(fsw_inst->address);
  } else if (auto *fcvtsw_inst = dynamic_cast<RiscvFcvtswInstruction *>(inst)) {
    extractFromOperand(fcvtsw_inst->rd);
    extractFromOperand(fcvtsw_inst->rs1);
  } else if (auto *fcvtws_inst = dynamic_cast<RiscvFcvtwsInstruction *>(inst)) {
    extractFromOperand(fcvtws_inst->rd);
    extractFromOperand(fcvtws_inst->rs1);
  } else if (auto *bnez_inst = dynamic_cast<RiscvBnezInstruction *>(inst)) {
    extractFromOperand(bnez_inst->rs1);
    // label不需要提取
  } else if (auto *snez_inst = dynamic_cast<RiscvSnezInstruction *>(inst)) {
    extractFromOperand(snez_inst->rs1);
    extractFromOperand(snez_inst->rs2);
  } else if (auto *xor_inst = dynamic_cast<RiscvXorInstruction *>(inst)) {
    extractFromOperand(xor_inst->rd);
    extractFromOperand(xor_inst->rs1);
    extractFromOperand(xor_inst->rs2);
  } else if (auto *seqz_inst = dynamic_cast<RiscvSeqzInstruction *>(inst)) {
    // 基于当前的SEQZ指令定义：rs1是目标，rs2是源
    extractFromOperand(seqz_inst->rs1); // 目标寄存器
    extractFromOperand(seqz_inst->rs2); // 源寄存器
  } else if (auto *and_inst = dynamic_cast<RiscvAndInstruction *>(inst)) {
    extractFromOperand(and_inst->rd);
    extractFromOperand(and_inst->rs1);
    extractFromOperand(and_inst->rs2);
  } else if (auto *or_inst = dynamic_cast<RiscvOrInstruction *>(inst)) {
    extractFromOperand(or_inst->rd);
    extractFromOperand(or_inst->rs1);
    extractFromOperand(or_inst->rs2);
  } else if (auto *slt_inst = dynamic_cast<RiscvSltInstruction *>(inst)) {
    extractFromOperand(slt_inst->rd);
    extractFromOperand(slt_inst->rs1);
    extractFromOperand(slt_inst->rs2);
  } else if (auto *xori_inst = dynamic_cast<RiscvXoriInstruction *>(inst)) {
    extractFromOperand(xori_inst->rd);
    extractFromOperand(xori_inst->rs1);
    // imm不需要提取
  } else if (auto *andi_inst = dynamic_cast<RiscvAndiInstruction *>(inst)) {
    extractFromOperand(andi_inst->rd);
    extractFromOperand(andi_inst->rs1);
    // imm不需要提取
  } else if (auto *fmvxw_inst = dynamic_cast<RiscvFmvxwInstruction *>(inst)) {
    extractFromOperand(fmvxw_inst->rd);
    extractFromOperand(fmvxw_inst->rs1);
  } else if (auto *fmvwx_inst = dynamic_cast<RiscvFmvwxInstruction *>(inst)) {
    extractFromOperand(fmvwx_inst->rd);
    extractFromOperand(fmvwx_inst->rs1);
  } else if (auto *feq_inst = dynamic_cast<RiscvFeqInstruction *>(inst)) {
    extractFromOperand(feq_inst->rd);
    extractFromOperand(feq_inst->rs1);
    extractFromOperand(feq_inst->rs2);
  } else if (auto *flt_inst = dynamic_cast<RiscvFltInstruction *>(inst)) {
    extractFromOperand(flt_inst->rd);
    extractFromOperand(flt_inst->rs1);
    extractFromOperand(flt_inst->rs2);
  } else if (auto *fle_inst = dynamic_cast<RiscvFleInstruction *>(inst)) {
    extractFromOperand(fle_inst->rd);
    extractFromOperand(fle_inst->rs1);
    extractFromOperand(fle_inst->rs2);
  } else if (auto *j_inst = dynamic_cast<RiscvJInstruction *>(inst)) {
    // J: unconditional jump, no registers to extract
  }

  return virtuals;
}

void RegisterAllocator::performLinearScanAllocation() {
  std::set<LiveRange *, LiveRangeEndPosComparator> active; // Active list sorted by end_pos

  for (auto &range : live_ranges) {
    // Skip pre-colored ranges
    if (virtual_to_physical.find(range.virtual_reg) !=
        virtual_to_physical.end()) {
      continue;
    }
    
    // Expire old intervals that end before current interval starts
    auto it = active.begin();
    while (it != active.end() && (*it)->end_pos < range.start_pos) {
        auto map_it = virtual_to_physical.find((*it)->virtual_reg);
        if (map_it != virtual_to_physical.end()) {
            int physical_reg = map_it->second;
            physical_to_virtual.erase(physical_reg);
            
            // 将释放的寄存器标记为可用
            for (auto &reg : available_registers) {
              if (reg.reg_no == physical_reg) {
                reg.is_available = true;
                break;
              }
            }
        }
        it = active.erase(it);
    }

    // Try to find a free register
    int physical_reg = findFreeRegister();

    if (physical_reg != -1) {
      // Found a free register, mark it as unavailable
      for (auto &reg : available_registers) {
        if (reg.reg_no == physical_reg) {
          reg.is_available = false;
          break;
        }
      }
      
      virtual_to_physical[range.virtual_reg] = physical_reg;
      physical_to_virtual[physical_reg] = range.virtual_reg;
      active.insert(&range);

    } else {
      // No free registers, must spill
      // Find the interval in active list that ends latest
      if (!active.empty()) {
        auto last_active = std::prev(active.end());
        LiveRange* victim_range = *last_active;
        
        // Only spill if victim ends after current interval
        if (victim_range->end_pos > range.end_pos) {
          // Spill the victim
          int victim_phys_reg = virtual_to_physical.at(victim_range->virtual_reg);
          spillRegister(victim_phys_reg, range.start_pos);
          active.erase(last_active);

          // Allocate the register to the current range
          virtual_to_physical[range.virtual_reg] = victim_phys_reg;
          physical_to_virtual[victim_phys_reg] = range.virtual_reg;
          active.insert(&range);
        } else {
          // Spill the current range
          range.is_spilled = true;
          spilled_virtuals.insert(range.virtual_reg);
          spill_slots[range.virtual_reg] = next_spill_slot++;
        }
      } else {
        // No active intervals, spill current
        range.is_spilled = true;
        spilled_virtuals.insert(range.virtual_reg);
        spill_slots[range.virtual_reg] = next_spill_slot++;
      }
    }
  }
}

int RegisterAllocator::findFreeRegister() {
  // 第一优先级：临时寄存器（caller-saved，不需要保存恢复）
  for (auto &reg : available_registers) {
    if (reg.is_available && !reg.is_callee_saved &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  // 第二优先级：参数寄存器a2-a7（caller-saved）
  for (auto &reg : available_registers) {
    if (reg.is_available && reg.reg_no >= 12 && reg.reg_no <= 17 &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  // 第三优先级：保存寄存器（callee-saved，需要保存恢复）
  for (auto &reg : available_registers) {
    if (reg.is_available && reg.is_callee_saved &&
        physical_to_virtual.find(reg.reg_no) == physical_to_virtual.end()) {
      return reg.reg_no;
    }
  }

  return -1; // 没有可用寄存器
}

int RegisterAllocator::selectVictimRegister(int current_pos) {
    LiveRange* victim_range = nullptr;
    int victim_physical_reg = -1;

    // Find the active range that ends last
    for (const auto& pair : physical_to_virtual) {
        int physical_reg = pair.first;
        int virtual_reg = pair.second;
        LiveRange* range = virtual_to_range.at(virtual_reg);

        if (victim_range == nullptr || range->end_pos > victim_range->end_pos) {
            victim_range = range;
            victim_physical_reg = physical_reg;
        }
    }

    return victim_physical_reg;
}

void RegisterAllocator::spillRegister(int physical_reg, int current_pos) {
  auto phys_it = physical_to_virtual.find(physical_reg);
  if (phys_it == physical_to_virtual.end()) {
    return; // 
  }

  int virtual_reg = phys_it->second;

  // 标记为溢出
  auto range_it = virtual_to_range.find(virtual_reg);
  if (range_it != virtual_to_range.end() && range_it->second) {
    LiveRange *range = range_it->second;
    range->is_spilled = true;
    spilled_virtuals.insert(virtual_reg);
    spill_slots[virtual_reg] = next_spill_slot++;

    // std::cout << "溢出虚拟寄存器 %r" << virtual_reg << " 到溢出槽 "
    //           << spill_slots[virtual_reg] << std::endl;
  }

  // 释放物理寄存器
  virtual_to_physical.erase(virtual_reg);
  physical_to_virtual.erase(physical_reg);
}

void RegisterAllocator::insertSpillCode(
    std::map<int, RiscvBlock *> &blocks) {
  // 此函数的逻辑已移至 rewriteInstructions，以更精细地处理溢出。
  // 保留空函数体以维持现有调用结构。
}

// 辅助函数：检查指令是否使用虚拟寄存器
bool RegisterAllocator::usesVirtualRegister(RiscvInstruction* inst, int virtual_reg) {
  std::vector<int> used_regs = extractVirtualRegisters(inst);
  return std::find(used_regs.begin(), used_regs.end(), virtual_reg) != used_regs.end();
}

// 辅助函数：检查指令是否定义虚拟寄存器
bool RegisterAllocator::definesVirtualRegister(RiscvInstruction* inst, int virtual_reg) {
  if (!inst) {
    std::cerr << "错误: definesVirtualRegister 收到空指令指针!" << std::endl;
    return false;
  }
  
  // 根据指令类型检查目标寄存器
  if (auto *add_inst = dynamic_cast<RiscvAddInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(add_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *sub_inst = dynamic_cast<RiscvSubInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(sub_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *mul_inst = dynamic_cast<RiscvMulInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(mul_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *div_inst = dynamic_cast<RiscvDivInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(div_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *addi_inst = dynamic_cast<RiscvAddiInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(addi_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *li_inst = dynamic_cast<RiscvLiInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(li_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *ld_inst = dynamic_cast<RiscvLdInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(ld_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *sd_inst = dynamic_cast<RiscvSdInstruction *>(inst)) {
    // sd指令不定义寄存器，只使用寄存器
    return false;
  } else if (auto *sw_inst = dynamic_cast<RiscvSwInstruction *>(inst)) {
    // sw指令不定义寄存器，只使用寄存器
    return false;
  } else if (auto *lw_inst = dynamic_cast<RiscvLwInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(lw_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *mv_inst = dynamic_cast<RiscvMvInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(mv_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *la_inst = dynamic_cast<RiscvLaInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(la_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fmv_inst = dynamic_cast<RiscvFmvInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fmv_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *flw_inst = dynamic_cast<RiscvFlwInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(flw_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fsw_inst = dynamic_cast<RiscvFswInstruction *>(inst)) {
    // fsw指令不定义寄存器，只使用寄存器
    return false;
  } else if (auto *fcvtsw_inst = dynamic_cast<RiscvFcvtswInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fcvtsw_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fcvtws_inst = dynamic_cast<RiscvFcvtwsInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fcvtws_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *bnez_inst = dynamic_cast<RiscvBnezInstruction *>(inst)) {
    // bnez指令不定义寄存器
    return false;
  } else if (auto *snez_inst = dynamic_cast<RiscvSnezInstruction *>(inst)) {
    if (auto *rs1_reg = dynamic_cast<RiscvRegOperand *>(snez_inst->rs1)) {
      return rs1_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *jr_inst = dynamic_cast<RiscvJrInstruction *>(inst)) {
    // jr指令不定义寄存器
    return false;
  } else if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
    // call指令不直接定义寄存器（返回值通过后续mv指令处理）
    return false;
  } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction *>(inst)) {
    // 分支指令不定义寄存器
    return false;
  } else if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(jump_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fadd_inst = dynamic_cast<RiscvFAddInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fadd_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fsub_inst = dynamic_cast<RiscvFSubInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fsub_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fmul_inst = dynamic_cast<RiscvFMulInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fmul_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fdiv_inst = dynamic_cast<RiscvFDivInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fdiv_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *xor_inst = dynamic_cast<RiscvXorInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(xor_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *seqz_inst = dynamic_cast<RiscvSeqzInstruction *>(inst)) {
    // seqz指令定义第一个操作数（目标寄存器），读取第二个操作数
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(seqz_inst->rs1)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *and_inst = dynamic_cast<RiscvAndInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(and_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *or_inst = dynamic_cast<RiscvOrInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(or_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *slt_inst = dynamic_cast<RiscvSltInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(slt_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *xori_inst = dynamic_cast<RiscvXoriInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(xori_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *andi_inst = dynamic_cast<RiscvAndiInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(andi_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fmvxw_inst = dynamic_cast<RiscvFmvxwInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fmvxw_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fmvwx_inst = dynamic_cast<RiscvFmvwxInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fmvwx_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *feq_inst = dynamic_cast<RiscvFeqInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(feq_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *flt_inst = dynamic_cast<RiscvFltInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(flt_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *fle_inst = dynamic_cast<RiscvFleInstruction *>(inst)) {
    if (auto *rd_reg = dynamic_cast<RiscvRegOperand *>(fle_inst->rd)) {
      return rd_reg->GetRegNo() == virtual_reg;
    }
  } else if (auto *j_inst = dynamic_cast<RiscvJInstruction *>(inst)) {
    // J指令不定义寄存器
    return false;
  }
  return false;
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
    // 计算相对于帧指针s0的负偏移
    // 溢出槽位于栈帧的底部，所以是负偏移
    return -(current_frame->local_vars_size + it->second * 8);  // 负偏移，相对于s0
  }
  return -1;
}

void RegisterAllocator::printAllocationResult() {
  std::cout << "=== 寄存器分配结果 ===" << std::endl;
  std::cout << "虚拟寄存器到物理寄存器映射:" << std::endl;
  for (const auto &pair : virtual_to_physical) {
    std::cout << "  %r" << pair.first << " -> x" << pair.second << std::endl;
  }
  
  std::cout << "溢出的虚拟寄存器:" << std::endl;
  for (int vreg : spilled_virtuals) {
    auto slot_it = spill_slots.find(vreg);
    if (slot_it != spill_slots.end()) {
      std::cout << "  %r" << vreg << " -> 溢出槽 " << slot_it->second << std::endl;
    }
  }
  
  std::cout << "生存期信息:" << std::endl;
  for (const auto &range : live_ranges) {
    std::cout << "  %r" << range.virtual_reg << ": [" << range.start_pos 
              << ", " << range.end_pos << "]" << std::endl;
  }
}

void RegisterAllocator::printLiveRanges() {
  // 调试输出已禁用
  // 如果需要输出生存期信息，可以重新启用这里的代码
}

// 集成接口
void RegisterAllocationPass::applyToTranslator(Translator &translator) {
  std::cout << "\n=== 开始寄存器分配阶段 ===" << std::endl;

  RegisterAllocator allocator;

  // 为每个函数执行寄存器分配
  for (auto &func_pair : translator.riscv.function_block_map) {
    const std::string &func_name = func_pair.first;
    auto &blocks = func_pair.second;

    std::cout << "为函数 " << func_name << " 分配寄存器..." << std::endl;

    // 获取函数的栈帧信息
    const StackFrameInfo *frame_info = translator.getFunctionStackFrame(func_name);
    if (frame_info) {
      allocator.allocateRegistersForFunction(func_name, blocks, const_cast<StackFrameInfo*>(frame_info));
    } else {
      std::cerr << "Warning: No stack frame info found for function: " << func_name << std::endl;
    }
  }

  std::cout << "寄存器分配完成！" << std::endl;
}

void RegisterAllocator::rewriteInstructions(
    std::map<int, RiscvBlock *> &blocks) {
  for (auto &block_pair : blocks) {
    auto &block = block_pair.second;
    auto &instruction_list = block->instruction_list;
    std::deque<RiscvInstruction *> new_instruction_list;

    for (auto &inst : instruction_list) {
      if (!inst) continue;

      std::vector<RiscvOperand **> operands_to_rewrite;
      // 收集所有需要重写的操作数指针
      if (auto *add_inst = dynamic_cast<RiscvAddInstruction *>(inst)) {
        operands_to_rewrite.push_back(&add_inst->rd);
        operands_to_rewrite.push_back(&add_inst->rs1);
        operands_to_rewrite.push_back(&add_inst->rs2);
      } else if (auto *sub_inst = dynamic_cast<RiscvSubInstruction *>(inst)) {
        operands_to_rewrite.push_back(&sub_inst->rd);
        operands_to_rewrite.push_back(&sub_inst->rs1);
        operands_to_rewrite.push_back(&sub_inst->rs2);
      } else if (auto *mul_inst = dynamic_cast<RiscvMulInstruction *>(inst)) {
        operands_to_rewrite.push_back(&mul_inst->rd);
        operands_to_rewrite.push_back(&mul_inst->rs1);
        operands_to_rewrite.push_back(&mul_inst->rs2);
      } else if (auto *div_inst = dynamic_cast<RiscvDivInstruction *>(inst)) {
        operands_to_rewrite.push_back(&div_inst->rd);
        operands_to_rewrite.push_back(&div_inst->rs1);
        operands_to_rewrite.push_back(&div_inst->rs2);
      } else if (auto *addi_inst = dynamic_cast<RiscvAddiInstruction *>(inst)) {
        operands_to_rewrite.push_back(&addi_inst->rd);
        operands_to_rewrite.push_back(&addi_inst->rs1);
      } else if (auto *li_inst = dynamic_cast<RiscvLiInstruction *>(inst)) {
        operands_to_rewrite.push_back(&li_inst->rd);
      } else if (auto *ld_inst = dynamic_cast<RiscvLdInstruction *>(inst)) {
        operands_to_rewrite.push_back(&ld_inst->rd);
        operands_to_rewrite.push_back(&ld_inst->address);
      } else if (auto *sd_inst = dynamic_cast<RiscvSdInstruction *>(inst)) {
        operands_to_rewrite.push_back(&sd_inst->reg);
        operands_to_rewrite.push_back(&sd_inst->address);
      } else if (auto *branch_inst = dynamic_cast<RiscvBranchInstruction *>(inst)) {
        operands_to_rewrite.push_back(&branch_inst->rs1);
        operands_to_rewrite.push_back(&branch_inst->rs2);
      } else if (auto *jump_inst = dynamic_cast<RiscvJumpInstruction *>(inst)) {
        operands_to_rewrite.push_back(&jump_inst->rd);
      } else if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
        for (auto &arg : call_inst->args) {
          operands_to_rewrite.push_back(&arg);
        }
      } else if (auto *fadd_inst = dynamic_cast<RiscvFAddInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fadd_inst->rd);
        operands_to_rewrite.push_back(&fadd_inst->rs1);
        operands_to_rewrite.push_back(&fadd_inst->rs2);
      } else if (auto *fsub_inst = dynamic_cast<RiscvFSubInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fsub_inst->rd);
        operands_to_rewrite.push_back(&fsub_inst->rs1);
        operands_to_rewrite.push_back(&fsub_inst->rs2);
      } else if (auto *fmul_inst = dynamic_cast<RiscvFMulInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fmul_inst->rd);
        operands_to_rewrite.push_back(&fmul_inst->rs1);
        operands_to_rewrite.push_back(&fmul_inst->rs2);
      } else if (auto *fdiv_inst = dynamic_cast<RiscvFDivInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fdiv_inst->rd);
        operands_to_rewrite.push_back(&fdiv_inst->rs1);
        operands_to_rewrite.push_back(&fdiv_inst->rs2);
      } else if (auto *mod_inst = dynamic_cast<RiscvModInstruction *>(inst)) {
        operands_to_rewrite.push_back(&mod_inst->rd);
        operands_to_rewrite.push_back(&mod_inst->rs1);
        operands_to_rewrite.push_back(&mod_inst->rs2);
      } else if (auto *jr_inst = dynamic_cast<RiscvJrInstruction *>(inst)) {
        operands_to_rewrite.push_back(&jr_inst->rd);
      } else if (auto *sw_inst = dynamic_cast<RiscvSwInstruction *>(inst)) {
        operands_to_rewrite.push_back(&sw_inst->rs);
        operands_to_rewrite.push_back(&sw_inst->address);
      } else if (auto *lw_inst = dynamic_cast<RiscvLwInstruction *>(inst)) {
        operands_to_rewrite.push_back(&lw_inst->rd);
        operands_to_rewrite.push_back(&lw_inst->address);
      } else if (auto *mv_inst = dynamic_cast<RiscvMvInstruction *>(inst)) {
        operands_to_rewrite.push_back(&mv_inst->rd);
        operands_to_rewrite.push_back(&mv_inst->rs1);
      } else if (auto *la_inst = dynamic_cast<RiscvLaInstruction *>(inst)) {
        operands_to_rewrite.push_back(&la_inst->rd);
        operands_to_rewrite.push_back(&la_inst->address);
      } else if (auto *fmv_inst = dynamic_cast<RiscvFmvInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fmv_inst->rd);
        operands_to_rewrite.push_back(&fmv_inst->rs1);
      } else if (auto *flw_inst = dynamic_cast<RiscvFlwInstruction *>(inst)) {
        operands_to_rewrite.push_back(&flw_inst->rd);
        operands_to_rewrite.push_back(&flw_inst->address);
      } else if (auto *fsw_inst = dynamic_cast<RiscvFswInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fsw_inst->rs);
        operands_to_rewrite.push_back(&fsw_inst->address);
      } else if (auto *fcvtsw_inst = dynamic_cast<RiscvFcvtswInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fcvtsw_inst->rd);
        operands_to_rewrite.push_back(&fcvtsw_inst->rs1);
      } else if (auto *fcvtws_inst = dynamic_cast<RiscvFcvtwsInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fcvtws_inst->rd);
        operands_to_rewrite.push_back(&fcvtws_inst->rs1);
      } else if (auto *bnez_inst = dynamic_cast<RiscvBnezInstruction *>(inst)) {
        operands_to_rewrite.push_back(&bnez_inst->rs1);
      } else if (auto *snez_inst = dynamic_cast<RiscvSnezInstruction *>(inst)) {
        operands_to_rewrite.push_back(&snez_inst->rs1);
        operands_to_rewrite.push_back(&snez_inst->rs2);
      } else if (auto *xor_inst = dynamic_cast<RiscvXorInstruction *>(inst)) {
        operands_to_rewrite.push_back(&xor_inst->rd);
        operands_to_rewrite.push_back(&xor_inst->rs1);
        operands_to_rewrite.push_back(&xor_inst->rs2);
      } else if (auto *seqz_inst = dynamic_cast<RiscvSeqzInstruction *>(inst)) {
        operands_to_rewrite.push_back(&seqz_inst->rs1);
        operands_to_rewrite.push_back(&seqz_inst->rs2);
      } else if (auto *and_inst = dynamic_cast<RiscvAndInstruction *>(inst)) {
        operands_to_rewrite.push_back(&and_inst->rd);
        operands_to_rewrite.push_back(&and_inst->rs1);
        operands_to_rewrite.push_back(&and_inst->rs2);
      } else if (auto *or_inst = dynamic_cast<RiscvOrInstruction *>(inst)) {
        operands_to_rewrite.push_back(&or_inst->rd);
        operands_to_rewrite.push_back(&or_inst->rs1);
        operands_to_rewrite.push_back(&or_inst->rs2);
      } else if (auto *slt_inst = dynamic_cast<RiscvSltInstruction *>(inst)) {
        operands_to_rewrite.push_back(&slt_inst->rd);
        operands_to_rewrite.push_back(&slt_inst->rs1);
        operands_to_rewrite.push_back(&slt_inst->rs2);
      } else if (auto *xori_inst = dynamic_cast<RiscvXoriInstruction *>(inst)) {
        operands_to_rewrite.push_back(&xori_inst->rd);
        operands_to_rewrite.push_back(&xori_inst->rs1);
      } else if (auto *andi_inst = dynamic_cast<RiscvAndiInstruction *>(inst)) {
        operands_to_rewrite.push_back(&andi_inst->rd);
        operands_to_rewrite.push_back(&andi_inst->rs1);
      } else if (auto *fmvxw_inst = dynamic_cast<RiscvFmvxwInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fmvxw_inst->rd);
        operands_to_rewrite.push_back(&fmvxw_inst->rs1);
      } else if (auto *fmvwx_inst = dynamic_cast<RiscvFmvwxInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fmvwx_inst->rd);
        operands_to_rewrite.push_back(&fmvwx_inst->rs1);
      } else if (auto *feq_inst = dynamic_cast<RiscvFeqInstruction *>(inst)) {
        operands_to_rewrite.push_back(&feq_inst->rd);
        operands_to_rewrite.push_back(&feq_inst->rs1);
        operands_to_rewrite.push_back(&feq_inst->rs2);
      } else if (auto *flt_inst = dynamic_cast<RiscvFltInstruction *>(inst)) {
        operands_to_rewrite.push_back(&flt_inst->rd);
        operands_to_rewrite.push_back(&flt_inst->rs1);
        operands_to_rewrite.push_back(&flt_inst->rs2);
      } else if (auto *fle_inst = dynamic_cast<RiscvFleInstruction *>(inst)) {
        operands_to_rewrite.push_back(&fle_inst->rd);
        operands_to_rewrite.push_back(&fle_inst->rs1);
        operands_to_rewrite.push_back(&fle_inst->rs2);
      }

      std::vector<int> used_spilled_vregs;
      int defined_spilled_vreg = -1;
      int temp_reg_idx = 0; // 0 for t5 (-30), 1 for t6 (-31)
      std::map<int, int> vreg_to_temp_phys_reg;

      // 预处理：为溢出的操作数生成加载指令
      for (auto &operand_ptr : operands_to_rewrite) {
        if (auto *reg_op = dynamic_cast<RiscvRegOperand *>(*operand_ptr)) {
          int vreg = reg_op->GetRegNo();
          if (vreg >= 0 && isSpilled(vreg)) {
            bool is_def = definesVirtualRegister(inst, vreg);
            if (!is_def) { // 只为使用的寄存器加载
              if (vreg_to_temp_phys_reg.find(vreg) == vreg_to_temp_phys_reg.end()) {
                int temp_phys_reg = (temp_reg_idx++ == 0) ? -30 : -31;
                vreg_to_temp_phys_reg[vreg] = temp_phys_reg;
                int offset = getSpillOffset(vreg);
                auto s0_reg = new RiscvRegOperand(-8);  // Use frame pointer s0 instead of sp
                auto addr = new RiscvPtrOperand(offset, s0_reg);
                auto temp_reg_operand = new RiscvRegOperand(temp_phys_reg);
                new_instruction_list.push_back(new RiscvLdInstruction(temp_reg_operand, addr));
              }
            } else {
                defined_spilled_vreg = vreg;
                if (vreg_to_temp_phys_reg.find(vreg) == vreg_to_temp_phys_reg.end()) {
                    int temp_phys_reg = (temp_reg_idx++ == 0) ? -30 : -31;
                    vreg_to_temp_phys_reg[vreg] = temp_phys_reg;
                }
            }
          }
        }
      }

      // 重写指令本身
      for (auto &operand_ptr : operands_to_rewrite) {
        rewriteOperandNew(*operand_ptr, vreg_to_temp_phys_reg);
      }
      new_instruction_list.push_back(inst);

      // 后处理：为溢出的定义寄存器生成存储指令
      if (defined_spilled_vreg != -1) {
        int temp_phys_reg = vreg_to_temp_phys_reg[defined_spilled_vreg];
        int offset = getSpillOffset(defined_spilled_vreg);
        auto s0_reg = new RiscvRegOperand(-8);  // Use frame pointer s0 instead of sp
        auto addr = new RiscvPtrOperand(offset, s0_reg);
        auto temp_reg_operand = new RiscvRegOperand(temp_phys_reg);
        new_instruction_list.push_back(new RiscvSdInstruction(temp_reg_operand, addr));
      }
    }
    block->instruction_list = new_instruction_list;
  }
}

void RegisterAllocator::rewriteOperandNew(RiscvOperand *&operand, const std::map<int, int> &vreg_to_temp_phys_reg) {
  if (!operand) {
    return;
  }

  if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(operand)) {
    int virtual_reg = reg_operand->GetRegNo();
    
    if (virtual_reg >= 0) {
      auto it_phys = virtual_to_physical.find(virtual_reg);
      if (it_phys != virtual_to_physical.end()) {
        // 分配到物理寄存器，使用负数表示物理寄存器
        std::cout << "重写 %r" << virtual_reg << " -> x" << it_phys->second << " (负数:" << (-it_phys->second) << ")" << std::endl;
        // delete operand;
        operand = new RiscvRegOperand(-it_phys->second);
      } else if (isSpilled(virtual_reg)) {
        // 溢出，使用临时物理寄存器
        auto it_temp = vreg_to_temp_phys_reg.find(virtual_reg);
        if (it_temp != vreg_to_temp_phys_reg.end()) {
          std::cout << "重写溢出 %r" << virtual_reg << " -> 临时寄存器 x" << (-it_temp->second) << std::endl;
          // delete operand;
          operand = new RiscvRegOperand(it_temp->second);
        }
      }
    }
  } else if (auto *ptr_operand = dynamic_cast<RiscvPtrOperand *>(operand)) {
    rewriteOperandNew(ptr_operand->base_reg, vreg_to_temp_phys_reg);
  }
}

void RegisterAllocator::rewriteOperand(RiscvOperand *&operand) {
  if (!operand) {
    return;
  }

  // 只处理寄存器操作数
  if (auto *reg_operand = dynamic_cast<RiscvRegOperand *>(operand)) {
    int virtual_reg = reg_operand->GetRegNo();

    // 如果是虚拟寄存器（非负数）且有分配的物理寄存器
    if (virtual_reg >= 0) {
      auto it = virtual_to_physical.find(virtual_reg);
      if (it != virtual_to_physical.end()) {
        int physical_reg = it->second;
        
        // 检查是否已经被替换过（避免重复删除）
        if (virtual_reg >= 0) {  // 只有虚拟寄存器才需要替换
          // 替换为物理寄存器（使用负数表示物理寄存器）
          delete operand;  // 删除旧操作数
          operand = new RiscvRegOperand(-physical_reg);
        }
      } else if (isSpilled(virtual_reg)) {
        // 溢出的寄存器在这里应该已经被替换为t6了
        // 因为insertSpillCode已经插入了相应的load/store指令
        // 这里直接替换为t6寄存器
        delete operand;  // 删除旧操作数
        operand = new RiscvRegOperand(-31); // t6寄存器
      }
    }
  } else if (auto *ptr_operand = dynamic_cast<RiscvPtrOperand *>(operand)) {
    // 重写PTR操作数的基址寄存器
    rewriteOperand(ptr_operand->base_reg);
  }
}

void RegisterAllocator::preAllocateSpecialRegisters(
    const std::map<int, RiscvBlock*> &blocks) {
  // // std::cout << "预分配特殊寄存器..." << std::endl;

  // for (const auto &block_pair : blocks) {
  //   const auto &block = block_pair.second;

  //   for (const auto &inst : block->instruction_list) {
  //     // 查找函数调用指令
  //     if (auto *call_inst = dynamic_cast<RiscvCallInstruction *>(inst)) {
  //       // 查找紧接着的 mv 指令，这通常是 call 的返回值赋值
  //       // 在指令列表中查找当前指令的位置
  //       auto it = std::find_if(
  //           block->instruction_list.begin(), block->instruction_list.end(),
  //           [&](RiscvInstruction* ptr) {
  //             return ptr == call_inst;
  //           });

  //       if (it != block->instruction_list.end()) {
  //         auto next_it = std::next(it);
  //         if (next_it != block->instruction_list.end()) {
  //           // 由于RiscvPseudoInstruction不存在，跳过mv指令检查
  //           // TODO: 如果需要支持mv指令，需要确认正确的指令类型
  //         }
  //       }
  //     }

  //     // 由于RiscvPseudoInstruction不存在，跳过返回指令前的mv检查  
  //     // TODO: 如果需要支持mv指令，需要确认正确的指令类型
  //   }
  // }
>>>>>>> ceca8424055cda7bda7cea9e86b747d72df9d7b5
}