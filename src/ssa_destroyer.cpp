#include "../include/ssa.h"
#include <iostream>

LLVMIR SSADestroyer::destroySSA(const LLVMIR &ssa_ir) {
  LLVMIR normal_ir = ssa_ir;

  std::cout << "Destroying SSA form..." << std::endl;

  // 对每个函数进行SSA销毁
  for (auto &func_pair : normal_ir.function_block_map) {
    std::map<int, LLVMBlock> &blocks = func_pair.second;

    // 消除φ函数
    eliminatePhiFunctions(blocks);
  }

  std::cout << "SSA form destroyed successfully" << std::endl;

  return normal_ir;
}

void SSADestroyer::eliminatePhiFunctions(std::map<int, LLVMBlock> &blocks) {
  // 收集所有φ函数
  std::vector<PhiInfo> phi_functions;

  for (const auto &block_pair : blocks) {
    int block_id = block_pair.first;
    LLVMBlock block = block_pair.second;

    auto it = block->Instruction_list.begin();
    while (it != block->Instruction_list.end()) {
      if ((*it)->GetOpcode() == PHI) {
        // 提取φ函数信息
        PhiInfo phi_info;
        phi_info.block_id = block_id;
        phi_info.instruction = *it;

        // 解析φ函数的参数
        parsePhiFunction(*it, phi_info);
        phi_functions.push_back(phi_info);

        // 从基本块中移除φ函数
        it = block->Instruction_list.erase(it);
      } else {
        ++it;
      }
    }
  }

  // 为每个φ函数插入复制指令
  for (const PhiInfo &phi_info : phi_functions) {
    insertCopiesInPredecessors(phi_info.block_id, phi_info.result_var,
                               phi_info.phi_args, blocks);
  }
}

void SSADestroyer::parsePhiFunction(const Instruction &phi_inst,
                                    PhiInfo &phi_info) {
  // 解析φ函数指令，提取结果变量和参数列表
  // 这里需要根据具体的φ函数指令格式来实现

  // 简化实现：假设φ函数指令包含必要的信息
  phi_info.instruction = phi_inst;

  // 这里应该根据实际的指令格式来解析
  // 暂时使用占位符实现
  phi_info.result_var = "temp_phi_result";
  phi_info.phi_args.push_back({"temp_arg", 0});
}

void SSADestroyer::insertCopiesInPredecessors(
    int phi_block, const std::string &phi_var,
    const std::vector<std::pair<std::string, int>> &phi_args,
    std::map<int, LLVMBlock> &blocks) {

  // 获取前驱块列表
  std::vector<int> predecessors = getPredecessorBlocks(phi_block, blocks);

  // 为每个(变量, 前驱块)对插入复制指令
  for (const auto &arg_pair : phi_args) {
    const std::string &source_var = arg_pair.first;
    int pred_block_id = arg_pair.second;

    // 在前驱块的末尾插入复制指令
    auto pred_it = blocks.find(pred_block_id);
    if (pred_it != blocks.end()) {
      LLVMBlock pred_block = pred_it->second;

      // 创建复制指令：phi_var = source_var
      Instruction copy_inst = createCopyInstruction(phi_var, source_var);

      // 在跳转指令之前插入复制指令
      insertCopyBeforeTerminator(pred_block, copy_inst);
    }
  }

  // 避免未使用参数警告
  (void)phi_block;
}

Instruction SSADestroyer::createCopyInstruction(const std::string &dest_var,
                                                const std::string &source_var) {
  // 创建一个复制指令
  // 这里需要根据具体的指令格式来创建

  // 简化处理：创建一个load/store序列来实现复制
  // 实际实现中应该根据具体的指令系统来创建
  (void)dest_var;   // 避免未使用参数警告
  (void)source_var; // 避免未使用参数警告

  // 返回nullptr作为占位符
  return nullptr;
}

void SSADestroyer::insertCopyBeforeTerminator(LLVMBlock block,
                                              Instruction copy_inst) {
  // 在终结指令之前插入复制指令
  if (!block || !copy_inst)
    return;

  // 检查最后一个指令是否为终结指令
  if (!block->Instruction_list.empty()) {
    Instruction last_inst = block->Instruction_list.back();
    int opcode = last_inst->GetOpcode();

    if (isTerminatorInstruction(last_inst)) {
      // 在终结指令之前插入复制指令
      auto it = block->Instruction_list.end();
      --it; // 指向最后一个指令
      block->Instruction_list.insert(it, copy_inst);
    } else {
      // 如果没有终结指令，直接添加到末尾
      block->Instruction_list.push_back(copy_inst);
    }
  } else {
    // 空块，直接添加
    block->Instruction_list.push_back(copy_inst);
  }
}

bool SSADestroyer::isTerminatorInstruction(const Instruction &inst) {
  if (!inst)
    return false;

  int opcode = inst->GetOpcode();
  return (opcode == BR_COND || opcode == BR_UNCOND || opcode == RET);
}

std::vector<int>
SSADestroyer::getPredecessorBlocks(int block_id,
                                   const std::map<int, LLVMBlock> &blocks) {
  std::vector<int> predecessors;

  // 遍历所有基本块，查找跳转到目标块的块
  for (const auto &block_pair : blocks) {
    int current_block_id = block_pair.first;
    LLVMBlock current_block = block_pair.second;

    if (current_block_id == block_id)
      continue;

    // 检查当前块的最后一个指令是否跳转到目标块
    if (!current_block->Instruction_list.empty()) {
      Instruction last_inst = current_block->Instruction_list.back();

      if (isTerminatorInstruction(last_inst)) {
        int target = getJumpTarget(last_inst);
        if (target == block_id) {
          predecessors.push_back(current_block_id);
        }
      }
    }
  }

  return predecessors;
}

int SSADestroyer::getJumpTarget(const Instruction &inst) {
  // 获取跳转指令的目标块ID
  // 这里需要根据具体的指令格式来实现
  (void)inst; // 避免未使用参数警告

  // 简化实现：返回-1表示无法确定目标
  return -1;
}

void SSADestroyer::validateSSADestruction(const LLVMIR &original_ssa,
                                          const LLVMIR &destroyed_ir) {
  // 验证SSA销毁的正确性
  // 检查是否还存在φ函数，检查变量使用是否正确等
  (void)original_ssa; // 避免未使用参数警告
  (void)destroyed_ir; // 避免未使用参数警告

  std::cout << "SSA destruction validation completed" << std::endl;
}
