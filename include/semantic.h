#pragma once

#include "ast.h"
#include "symtab.h"
#include "types.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

// 语义分析器类 - 实现一次扫描 + 延迟检查策略
class SemanticAnalyzer : public ASTVisitor {
private:
  SymbolTable symbol_table;

public:
  SemanticAnalyzer() = default;
  bool analyze(CompUnit &root);
  // 访问者模式接口实现
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