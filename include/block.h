#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

#include "instruction.h"
#include <deque>
#include <iostream>
#include <set>
#include <vector>

class BasicBlock
{
public:
  std::string comment; // 调试信息
  int block_id = 0;
  std::deque<Instruction> Instruction_list{};

  void InsertInstruction(int pos, Instruction Ins);

  void printIR(std::ostream &s)
  {
    s << "L" << block_id << ":  " << comment << "\n";

    for (Instruction ins : Instruction_list)
    {
      s << "    ";
      ins->PrintIR(s); // 指令会自动添加换行符
    }
  }
  BasicBlock(int id) : block_id(id) {}
};
typedef BasicBlock *LLVMBlock;

class LLVMIR
{
public:
  std::vector<Instruction> global_def{};
  std::vector<Instruction> function_declare{};

  std::map<FuncDefInstruction, std::map<int, LLVMBlock>>
      function_block_map; // 函数到基本块的映射表

  void NewFunction(FuncDefInstruction I) { function_block_map[I] = {}; }
  LLVMBlock GetBlock(FuncDefInstruction I, int now_label)
  {
    return function_block_map[I][now_label];
  }
  LLVMBlock NewBlock(FuncDefInstruction I, int &max_label)
  {
    ++max_label;
    function_block_map[I][max_label] = new BasicBlock(max_label);
    return GetBlock(I, max_label);
  }
  void printIR(std::ostream &s)
  {
    // output lib func decl
    for (Instruction lib_func_decl : function_declare)
    {
      lib_func_decl->PrintIR(s);
    }

    // output global
    for (Instruction global_decl_ins : global_def)
    {
      global_decl_ins->PrintIR(s);
    }

    // output Functions
    for (auto Func_Block_item : function_block_map)
    { // 遍历每个函数
      FuncDefInstruction f = Func_Block_item.first;
      // 输出函数声明
      f->PrintIR(s);

      // 输出函数内的基本块
      s << "{\n";
      for (auto block : Func_Block_item.second)
      {
        block.second->printIR(s);
      }
      s << "}\n";
    }
  }
};

class IRgenerator : public ASTVisitor
{
public:
  LLVMIR llvmIR;
  Operand current_ptr;          // 当前指针操作数
  LLVMType current_llvm_type;   // 当前LLVM类型
  BaseType current_type;        // 跟踪当前变量声明类型
  int current_reg_counter = -1; // 函数内寄存器计数器

  // 获取生成的LLVM IR
  LLVMIR &getLLVMIR() { return llvmIR; }

  // 获取当前基本块
  LLVMBlock getCurrentBlock();

  // 分配新寄存器
  int newReg();

  // 分配新标签
  int newLabel();

  // 检查是否在全局作用域
  bool isGlobalScope();
  bool isPointer(int reg);

  std::optional<int> evaluateConstExpression(Exp *expr);
  std::optional<float> evaluateConstExpressionFloat(Exp *expr);
  std::shared_ptr<Type> inferExpressionType(Exp *expression);
  void handleArrayInitializer(InitVal *init, int base_reg, VarAttribute &attr, const std::vector<int> &dims, size_t dim_idx);

  void visit(CompUnit &node) override;
  void visit(ConstDecl &node) override;
  void visit(ConstDef &node) override;
  void visit(VarDecl &node) override;
  void visit(VarDef &node) override;
  void visit(FuncDef &node) override;
  void visit(FuncFParam &node) override;
  void visit(Block &node) override;
  void visit(IfStmt &node) override;
  void visit(WhileStmt &node) override;
  void visit(ExpStmt &node) override;
  void visit(AssignStmt &node) override;
  void visit(ReturnStmt &node) override;
  void visit(BreakStmt &node) override;
  void visit(ContinueStmt &node) override;
  void visit(UnaryExp &node) override;
  void visit(BinaryExp &node) override;
  void visit(LVal &node) override;
  void visit(FunctionCall &node) override;
  void visit(Number &node) override;
  void visit(StringLiteral &node) override;
  void visit(InitVal &node) override;
  void visit(ConstInitVal &node) override;
};

#endif