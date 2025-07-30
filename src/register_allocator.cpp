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
  }

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

    // 7. 输出分配结果
  // printAllocationResult();
  
  } catch (const std::exception& e) {
    std::cerr << "Error in register allocation for function " << func_name 
              << ": " << e.what() << std::endl;
    throw;
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

  for (const auto &block_pair : blocks) {
    const auto &block = block_pair.second;

    for (size_t i = 0; i < block->instruction_list.size(); i++) {
      const auto &inst = block->instruction_list[i];
      
      if (!inst) {
        std::cerr << "错误: 在生存期计算中发现空指令!" << std::endl;
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

// Comparator for sorting LiveRange pointers by their end position.
struct LiveRangeEndPosComparator {
    bool operator()(const LiveRange* a, const LiveRange* b) const {
        if (a->end_pos != b->end_pos) {
            return a->end_pos < b->end_pos;
        }
        return a->virtual_reg < b->virtual_reg; // Use virtual_reg for stable ordering
    }
};

void RegisterAllocator::performLinearScanAllocation() {
  std::set<LiveRange *, LiveRangeEndPosComparator> active; // Active list sorted by end_pos

  for (auto &range : live_ranges) {
    // Skip pre-colored ranges
    if (virtual_to_physical.find(range.virtual_reg) !=
        virtual_to_physical.end()) {
      continue;
    }
    
    // Expire old intervals
    auto it = active.begin();
    while (it != active.end() && (*it)->end_pos <= range.start_pos) {
        auto map_it = virtual_to_physical.find((*it)->virtual_reg);
        if (map_it != virtual_to_physical.end()) {
            int physical_reg = map_it->second;
            physical_to_virtual.erase(physical_reg);
        }
        it = active.erase(it);
    }

    // Try to find a free register
    int physical_reg = findFreeRegister();

    if (physical_reg != -1) {
      // Found a free register
      virtual_to_physical[range.virtual_reg] = physical_reg;
      physical_to_virtual[physical_reg] = range.virtual_reg;
      active.insert(&range);

    } else {
      // No free registers, must spill
      int victim_reg = selectVictimRegister(range.start_pos);
      if (victim_reg != -1) {
        int victim_vreg = physical_to_virtual.at(victim_reg);
        LiveRange* victim_range = virtual_to_range.at(victim_vreg);
        
        // Spill the victim
        spillRegister(victim_reg, range.start_pos);
        active.erase(victim_range);

        // Allocate the register to the current range
        virtual_to_physical[range.virtual_reg] = victim_reg;
        physical_to_virtual[victim_reg] = range.virtual_reg;
        active.insert(&range);
      } else {
        // Spill the current range as a fallback
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
    return current_frame->local_vars_size + it->second * 4;
  }
  return -1;
}

void RegisterAllocator::printAllocationResult() {
  // 调试输出已禁用
  // 如果需要输出分配结果，可以重新启用这里的代码
}

void RegisterAllocator::printLiveRanges() {
  // 调试输出已禁用
  // 如果需要输出生存期信息，可以重新启用这里的代码
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
    const StackFrameInfo *frame_info = translator.getFunctionStackFrame(func_name);
    if (frame_info) {
      allocator.allocateRegistersForFunction(func_name, blocks, const_cast<StackFrameInfo*>(frame_info));
    } else {
      std::cerr << "Warning: No stack frame info found for function: " << func_name << std::endl;
    }
  }

  // std::cout << "寄存器分配完成！" << std::endl;
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
                auto sp_reg = new RiscvRegOperand(-2);
                auto addr = new RiscvPtrOperand(offset, sp_reg);
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
        auto sp_reg = new RiscvRegOperand(-2);
        auto addr = new RiscvPtrOperand(offset, sp_reg);
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
        // 分配到物理寄存器
        // delete operand;
        operand = new RiscvRegOperand(-it_phys->second);
      } else if (isSpilled(virtual_reg)) {
        // 溢出，使用临时物理寄存器
        auto it_temp = vreg_to_temp_phys_reg.find(virtual_reg);
        if (it_temp != vreg_to_temp_phys_reg.end()) {
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
}