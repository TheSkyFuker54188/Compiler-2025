#pragma once

#include "ast.h"
#include <iostream>
#include <memory>
#include <string>

class ASTPrinter : public ASTVisitor {
private:
  std::ostream &out;
  int indent_level = 0;

  void print_indent();
  void print_location(const SyntaxNode &node);

public:
  explicit ASTPrinter(std::ostream &output = std::cout);

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