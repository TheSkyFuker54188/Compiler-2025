#pragma once

#include "types.h"
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

class ASTVisitor;
class SyntaxNode;
class Decl;
class Stmt;
class Exp;
class InitValBase;
class InitVal;
class CompUnit;
class ConstDecl;
class ConstDef;
class VarDecl;
class VarDef;
class FuncDef;
class FuncFParam;
class Block;
class IfStmt;
class WhileStmt;
class ExpStmt;
class AssignStmt;
class ReturnStmt;
class BreakStmt;
class ContinueStmt;
class UnaryExp;
class BinaryExp;
class LVal;
class FunctionCall;
class Number;
class StringLiteral;
class ConstInitVal;

class ASTVisitor {
public:
  virtual ~ASTVisitor() = default;
  virtual void visit(CompUnit &node) = 0;
  virtual void visit(ConstDecl &node) = 0;
  virtual void visit(ConstDef &node) = 0;
  virtual void visit(VarDecl &node) = 0;
  virtual void visit(VarDef &node) = 0;
  virtual void visit(FuncDef &node) = 0;
  virtual void visit(FuncFParam &node) = 0;
  virtual void visit(Block &node) = 0;
  virtual void visit(IfStmt &node) = 0;
  virtual void visit(WhileStmt &node) = 0;
  virtual void visit(ExpStmt &node) = 0;
  virtual void visit(AssignStmt &node) = 0;
  virtual void visit(ReturnStmt &node) = 0;
  virtual void visit(BreakStmt &node) = 0;
  virtual void visit(ContinueStmt &node) = 0;
  virtual void visit(UnaryExp &node) = 0;
  virtual void visit(BinaryExp &node) = 0;
  virtual void visit(LVal &node) = 0;
  virtual void visit(FunctionCall &node) = 0;
  virtual void visit(Number &node) = 0;
  virtual void visit(StringLiteral &node) = 0;
  virtual void visit(InitVal &node) = 0;
  virtual void visit(ConstInitVal &node) = 0;
};

class SyntaxNode {
public:
  int line;
  explicit SyntaxNode(int l) : line(l) {}
  virtual ~SyntaxNode() = default;
  virtual void accept(ASTVisitor &visitor) = 0;
};

class Decl : public SyntaxNode {
  using SyntaxNode::SyntaxNode;
};
class Stmt : public SyntaxNode {
  using SyntaxNode::SyntaxNode;
};
class Exp : public SyntaxNode {
  using SyntaxNode::SyntaxNode;

public:
  std::optional<std::variant<int, float, std::string>> value;
  std::unique_ptr<Type> type;
  bool is_const = false;
};
class InitValBase : public SyntaxNode {
public:
  using SyntaxNode::SyntaxNode;
};

// CompUnit → CompUnit (Decl | FuncDef) | (Decl | FuncDef)
class CompUnit : public SyntaxNode {
public:
  std::vector<std::variant<std::unique_ptr<Decl>, std::unique_ptr<FuncDef>>>
      items;
  explicit CompUnit(int loc) : SyntaxNode(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
class ConstDecl : public Decl {
public:
  BaseType type;
  std::vector<std::unique_ptr<ConstDef>> definitions;
  ConstDecl(BaseType type, std::vector<std::unique_ptr<ConstDef>> defs, int loc)
      : Decl(loc), type(type), definitions(std::move(defs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// ConstDef → Ident {'[' ConstExp ']'} '=' ConstInitVal
class ConstDef : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<Exp>> dimensions;
  std::unique_ptr<ConstInitVal> initializer;
  ConstDef(std::string name, std::vector<std::unique_ptr<Exp>> dims,
           std::unique_ptr<ConstInitVal> init, int loc)
      : SyntaxNode(loc), name(std::move(name)), dimensions(std::move(dims)),
        initializer(std::move(init)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// VarDecl → BType VarDef { ',' VarDef } ';'
class VarDecl : public Decl {
public:
  BaseType type;
  std::vector<std::unique_ptr<VarDef>> definitions;
  VarDecl(BaseType type, std::vector<std::unique_ptr<VarDef>> defs, int loc)
      : Decl(loc), type(type), definitions(std::move(defs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// VarDef → Ident {'[' ConstExp ']'} | Ident {'[' ConstExp ']'} '=' InitVal
class VarDef : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<Exp>> array_dimensions;
  std::optional<std::unique_ptr<InitVal>> initializer;
  VarDef(std::string name, std::vector<std::unique_ptr<Exp>> dims,
         std::optional<std::unique_ptr<InitVal>> init, int loc)
      : SyntaxNode(loc), name(std::move(name)),
        array_dimensions(std::move(dims)), initializer(std::move(init)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
class FuncDef : public SyntaxNode {
public:
  BaseType return_type;
  std::string name;
  std::vector<std::unique_ptr<FuncFParam>> parameters;
  std::unique_ptr<Block> body;
  FuncDef(BaseType ret_type, std::string name,
          std::vector<std::unique_ptr<FuncFParam>> params,
          std::unique_ptr<Block> body, int loc)
      : SyntaxNode(loc), return_type(ret_type), name(std::move(name)),
        parameters(std::move(params)), body(std::move(body)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// FuncFParam → BType Ident ['[' ']' { '[' Exp ']' }]
class FuncFParam : public SyntaxNode {
public:
  BaseType type;
  std::string name;
  std::vector<std::unique_ptr<Exp>> array_dimensions;
  FuncFParam(BaseType type, std::string name,
             std::vector<std::unique_ptr<Exp>> dims, int loc)
      : SyntaxNode(loc), type(type), name(std::move(name)),
        array_dimensions(std::move(dims)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// Block → '{' { BlockItem } '}'
// BlockItem → Decl | Stmt
class Block : public Stmt {
public:
  std::vector<std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>>> items;
  explicit Block(int loc) : Stmt(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
class IfStmt : public Stmt {
public:
  std::unique_ptr<Exp> condition;
  std::unique_ptr<Stmt> then_statement;
  std::optional<std::unique_ptr<Stmt>> else_statement;
  IfStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> then_stmt,
         std::optional<std::unique_ptr<Stmt>> else_stmt, int loc)
      : Stmt(loc), condition(std::move(cond)),
        then_statement(std::move(then_stmt)),
        else_statement(std::move(else_stmt)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 'while' '(' Cond ')' Stmt
class WhileStmt : public Stmt {
public:
  std::unique_ptr<Exp> condition;
  std::unique_ptr<Stmt> body;
  WhileStmt(std::unique_ptr<Exp> cond, std::unique_ptr<Stmt> body, int loc)
      : Stmt(loc), condition(std::move(cond)), body(std::move(body)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// [Exp] ';'
class ExpStmt : public Stmt {
public:
  std::optional<std::unique_ptr<Exp>> expression;
  explicit ExpStmt(std::optional<std::unique_ptr<Exp>> expr, int loc)
      : Stmt(loc), expression(std::move(expr)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// LVal '=' Exp ';'
class AssignStmt : public Stmt {
public:
  std::unique_ptr<LVal> lvalue;
  std::unique_ptr<Exp> rvalue;

  AssignStmt(std::unique_ptr<LVal> lval, std::unique_ptr<Exp> rval, int loc)
      : Stmt(loc), lvalue(std::move(lval)), rvalue(std::move(rval)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 'return' [Exp] ';'
class ReturnStmt : public Stmt {
public:
  std::optional<std::unique_ptr<Exp>> expression;
  explicit ReturnStmt(std::optional<std::unique_ptr<Exp>> expr, int loc)
      : Stmt(loc), expression(std::move(expr)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 'break' ';'
class BreakStmt : public Stmt {
public:
  explicit BreakStmt(int loc) : Stmt(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 'continue' ';'
class ContinueStmt : public Stmt {
public:
  explicit ContinueStmt(int loc) : Stmt(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
class UnaryExp : public Exp {
public:
  UnaryOp op;
  std::unique_ptr<Exp> operand;
  UnaryExp(UnaryOp op, std::unique_ptr<Exp> operand, int loc)
      : Exp(loc), op(op), operand(std::move(operand)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 二元表达式 - 涵盖 AddExp, MulExp, RelExp, EqExp, LAndExp, LOrExp
class BinaryExp : public Exp {
public:
  BinaryOp op;
  std::unique_ptr<Exp> lhs;
  std::unique_ptr<Exp> rhs;
  BinaryExp(BinaryOp op, std::unique_ptr<Exp> lhs, std::unique_ptr<Exp> rhs,
            int loc)
      : Exp(loc), op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// LVal → Ident {'[' Exp ']'}
class LVal : public Exp {
public:
  std::string name;
  std::vector<std::unique_ptr<Exp>> indices;
  LVal(std::string name, std::vector<std::unique_ptr<Exp>> indices, int loc)
      : Exp(loc), name(std::move(name)), indices(std::move(indices)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// Ident '(' [FuncRParams] ')'
class FunctionCall : public Exp {
public:
  std::string function_name;
  std::vector<std::unique_ptr<Exp>> arguments;
  FunctionCall(std::string name, std::vector<std::unique_ptr<Exp>> args,
               int loc)
      : Exp(loc), function_name(std::move(name)), arguments(std::move(args)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// Number → IntConst | floatConst
class Number : public Exp {
public:
  std::variant<int, float> v;
  explicit Number(int val, int loc) : Exp(loc), v(val) {}
  explicit Number(float val, int loc) : Exp(loc), v(val) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// StringLiteral → StringConst
class StringLiteral : public Exp {
public:
  std::string v;
  explicit StringLiteral(std::string val, int loc)
      : Exp(loc), v(std::move(val)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// ConstInitVal → ConstExp | '{' [ConstInitVal { ',' ConstInitVal }] '}'
class ConstInitVal : public InitValBase {
public:
  // 单个表达式或初始化列表
  std::variant<std::unique_ptr<Exp>, std::vector<std::unique_ptr<ConstInitVal>>>
      value;
  std::vector<std::variant<int, float, std::string>> v;
  explicit ConstInitVal(std::unique_ptr<Exp> expr, int loc)
      : InitValBase(loc), value(std::move(expr)) {}
  explicit ConstInitVal(std::vector<std::unique_ptr<ConstInitVal>> inits,
                        int loc)
      : InitValBase(loc), value(std::move(inits)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// InitVal → Exp | '{' [InitVal { ',' InitVal }] '}'
class InitVal : public InitValBase {
public:
  // 单个表达式或初始化列表
  std::variant<std::unique_ptr<Exp>, std::vector<std::unique_ptr<InitVal>>>
      value;
  explicit InitVal(std::unique_ptr<Exp> expr, int loc)
      : InitValBase(loc), value(std::move(expr)) {}
  explicit InitVal(std::vector<std::unique_ptr<InitVal>> inits, int loc)
      : InitValBase(loc), value(std::move(inits)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};
