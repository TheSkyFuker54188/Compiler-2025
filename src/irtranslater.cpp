#include "../include/irtranslater.h"
#include "../include/llvm_instruction.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

extern std::map<std::string, int> function_name_to_maxreg;
int next_virtual_reg_no = 0;

void RiscvBlock::InsertInstruction(int pos, RiscvInstruction *ins) {
  if (pos == 0)
    instruction_list.push_front(ins);
  else
    instruction_list.push_back(ins);
}

void RiscvBlock::print(std::ostream &s) {
  s << ".L" << block_id << ":\n";
  for (auto &inst : instruction_list)
    inst->PrintIR(s);
}

// 添加一个最小的Translator类实现
std::string Translator::translateToAssembly(const CompUnit &root) {
  // 最小实现，返回空字符串
  return "# Assembly translation not yet implemented\n";
}

// 添加其他必要的函数
std::string translateToAssembly(const CompUnit &root) {
  Translator translator;
  return translator.translateToAssembly(root);
}
