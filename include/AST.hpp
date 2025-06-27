#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

// namespace compiler {

// ===--------------------------------------------------------------------=== //
// 辅助定义
// ===--------------------------------------------------------------------=== //

struct SourceLocation {
  int line = 0;
};

enum class BaseType { INT, FLOAT, VOID };
enum class UnaryOp { PLUS, MINUS, NOT };
enum class BinaryOp {
  ADD, SUB, MUL, DIV, MOD,
  GT, GTE, LT, LTE, EQ, NEQ,
  AND, OR, ASSIGN
};

// ===--------------------------------------------------------------------=== //
// AST节点前向声明
// ===--------------------------------------------------------------------=== //

class ASTVisitor;
class SyntaxNode;
class DeclarationNode;
class StatementNode;
class ExpressionNode;
class InitializerNode;
class TranslationUnit;
class ConstDeclaration;
class ConstDefinition;
class VariableDeclaration;
class VariableDefinition;
class FunctionDefinition;
class FunctionParameter;
class BlockStatement;
class IfStatement;
class WhileStatement;
class ExpressionStatement;
class ReturnStatement;
class BreakStatement;
class ContinueStatement;
class UnaryExpression;
class BinaryExpression;
class VariableAccess;
class ArrayAccess;
class FunctionCall;
class IntegerLiteral;
class FloatLiteral;
class ExpressionInitializer;
class InitializerList;

// ===--------------------------------------------------------------------=== //
// 访问者模式接口
// ===--------------------------------------------------------------------=== //

class ASTVisitor {
public:
  virtual ~ASTVisitor() = default;
  virtual void visit(TranslationUnit &node) = 0;
  virtual void visit(ConstDeclaration &node) = 0;
  virtual void visit(ConstDefinition &node) = 0;
  virtual void visit(VariableDeclaration &node) = 0;
  virtual void visit(VariableDefinition &node) = 0;
  virtual void visit(FunctionDefinition &node) = 0;
  virtual void visit(FunctionParameter &node) = 0;
  virtual void visit(BlockStatement &node) = 0;
  virtual void visit(IfStatement &node) = 0;
  virtual void visit(WhileStatement &node) = 0;
  virtual void visit(ExpressionStatement &node) = 0;
  virtual void visit(ReturnStatement &node) = 0;
  virtual void visit(BreakStatement &node) = 0;
  virtual void visit(ContinueStatement &node) = 0;
  virtual void visit(UnaryExpression &node) = 0;
  virtual void visit(BinaryExpression &node) = 0;
  virtual void visit(VariableAccess &node) = 0;
  virtual void visit(ArrayAccess &node) = 0;
  virtual void visit(FunctionCall &node) = 0;
  virtual void visit(IntegerLiteral &node) = 0;
  virtual void visit(FloatLiteral &node) = 0;
  virtual void visit(ExpressionInitializer &node) = 0;
  virtual void visit(InitializerList &node) = 0;
};

// ===--------------------------------------------------------------------=== //
// AST节点基类
// ===--------------------------------------------------------------------=== //

class SyntaxNode {
public:
  SourceLocation location;
  explicit SyntaxNode(SourceLocation loc = {}) : location(loc) {}
  virtual ~SyntaxNode() = default;
  virtual void accept(ASTVisitor &visitor) = 0;
};

class DeclarationNode : public SyntaxNode { using SyntaxNode::SyntaxNode; };
class StatementNode : public SyntaxNode { using SyntaxNode::SyntaxNode; };
class ExpressionNode : public SyntaxNode { using SyntaxNode::SyntaxNode; };
class InitializerNode : public SyntaxNode { using SyntaxNode::SyntaxNode; };

// ===--------------------------------------------------------------------=== //
// 具体AST节点定义
// ===--------------------------------------------------------------------=== //

class TranslationUnit : public SyntaxNode {
public:
  std::vector<std::unique_ptr<DeclarationNode>> declarations;
  explicit TranslationUnit(SourceLocation loc = {}) : SyntaxNode(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ConstDeclaration : public DeclarationNode {
public:
  BaseType type;
  std::vector<std::unique_ptr<ConstDefinition>> definitions;
  ConstDeclaration(BaseType type, std::vector<std::unique_ptr<ConstDefinition>> defs, SourceLocation loc = {})
      : DeclarationNode(loc), type(type), definitions(std::move(defs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ConstDefinition : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions;
  std::unique_ptr<InitializerNode> initializer;
  ConstDefinition(std::string name, std::vector<std::unique_ptr<ExpressionNode>> dims,
                    std::unique_ptr<InitializerNode> init, SourceLocation loc = {})
      : SyntaxNode(loc), name(std::move(name)), array_dimensions(std::move(dims)),
        initializer(std::move(init)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class VariableDeclaration : public DeclarationNode {
public:
  BaseType type;
  std::vector<std::unique_ptr<VariableDefinition>> definitions;
  VariableDeclaration(BaseType type, std::vector<std::unique_ptr<VariableDefinition>> defs, SourceLocation loc = {})
      : DeclarationNode(loc), type(type), definitions(std::move(defs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class VariableDefinition : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions;
  std::optional<std::unique_ptr<InitializerNode>> initializer;
  VariableDefinition(std::string name, std::vector<std::unique_ptr<ExpressionNode>> dims,
                       std::optional<std::unique_ptr<InitializerNode>> init, SourceLocation loc = {})
      : SyntaxNode(loc), name(std::move(name)), array_dimensions(std::move(dims)),
        initializer(std::move(init)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FunctionDefinition : public DeclarationNode {
public:
  BaseType return_type;
  std::string name;
  std::vector<std::unique_ptr<FunctionParameter>> parameters;
  std::unique_ptr<BlockStatement> body;
  FunctionDefinition(BaseType ret_type, std::string name,
                       std::vector<std::unique_ptr<FunctionParameter>> params,
                       std::unique_ptr<BlockStatement> body, SourceLocation loc = {})
      : DeclarationNode(loc), return_type(ret_type), name(std::move(name)),
        parameters(std::move(params)), body(std::move(body)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FunctionParameter : public SyntaxNode {
public:
  BaseType type;
  std::string name;
  bool is_array_pointer;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions;
  FunctionParameter(BaseType type, std::string name, bool is_array_ptr,
                      std::vector<std::unique_ptr<ExpressionNode>> dims, SourceLocation loc = {})
      : SyntaxNode(loc), type(type), name(std::move(name)), is_array_pointer(is_array_ptr),
        array_dimensions(std::move(dims)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BlockStatement : public StatementNode {
public:
  std::vector<std::variant<std::unique_ptr<StatementNode>,
                           std::unique_ptr<DeclarationNode>>> items;
  explicit BlockStatement(SourceLocation loc = {}) : StatementNode(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class IfStatement : public StatementNode {
public:
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<StatementNode> then_statement;
  std::optional<std::unique_ptr<StatementNode>> else_statement;
  IfStatement(std::unique_ptr<ExpressionNode> cond, std::unique_ptr<StatementNode> then_stmt,
                std::optional<std::unique_ptr<StatementNode>> else_stmt, SourceLocation loc = {})
      : StatementNode(loc), condition(std::move(cond)), then_statement(std::move(then_stmt)),
        else_statement(std::move(else_stmt)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class WhileStatement : public StatementNode {
public:
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<StatementNode> body;
  WhileStatement(std::unique_ptr<ExpressionNode> cond, std::unique_ptr<StatementNode> body,
                   SourceLocation loc = {})
      : StatementNode(loc), condition(std::move(cond)), body(std::move(body)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ExpressionStatement : public StatementNode {
public:
  std::optional<std::unique_ptr<ExpressionNode>> expression;
  explicit ExpressionStatement(std::optional<std::unique_ptr<ExpressionNode>> expr,
                                 SourceLocation loc = {})
      : StatementNode(loc), expression(std::move(expr)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ReturnStatement : public StatementNode {
public:
  std::optional<std::unique_ptr<ExpressionNode>> expression;
  explicit ReturnStatement(std::optional<std::unique_ptr<ExpressionNode>> expr,
                             SourceLocation loc = {})
      : StatementNode(loc), expression(std::move(expr)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BreakStatement : public StatementNode {
public:
  explicit BreakStatement(SourceLocation loc = {}) : StatementNode(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ContinueStatement : public StatementNode {
public:
  explicit ContinueStatement(SourceLocation loc = {}) : StatementNode(loc) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class UnaryExpression : public ExpressionNode {
public:
  UnaryOp op;
  std::unique_ptr<ExpressionNode> operand;
  UnaryExpression(UnaryOp op, std::unique_ptr<ExpressionNode> operand, SourceLocation loc = {})
      : ExpressionNode(loc), op(op), operand(std::move(operand)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BinaryExpression : public ExpressionNode {
public:
  BinaryOp op;
  std::unique_ptr<ExpressionNode> lhs;
  std::unique_ptr<ExpressionNode> rhs;
  BinaryExpression(BinaryOp op, std::unique_ptr<ExpressionNode> lhs,
                   std::unique_ptr<ExpressionNode> rhs, SourceLocation loc = {})
      : ExpressionNode(loc), op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class VariableAccess : public ExpressionNode {
public:
  std::string name;
  explicit VariableAccess(std::string name, SourceLocation loc = {})
      : ExpressionNode(loc), name(std::move(name)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ArrayAccess : public ExpressionNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> indices;
  ArrayAccess(std::string name, std::vector<std::unique_ptr<ExpressionNode>> indices,
                SourceLocation loc = {})
      : ExpressionNode(loc), name(std::move(name)), indices(std::move(indices)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FunctionCall : public ExpressionNode {
public:
  std::string function_name;
  std::vector<std::unique_ptr<ExpressionNode>> arguments;
  FunctionCall(std::string name, std::vector<std::unique_ptr<ExpressionNode>> args,
                 SourceLocation loc = {})
      : ExpressionNode(loc), function_name(std::move(name)), arguments(std::move(args)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class IntegerLiteral : public ExpressionNode {
public:
  int value;
  explicit IntegerLiteral(int val, SourceLocation loc = {}) : ExpressionNode(loc), value(val) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FloatLiteral : public ExpressionNode {
public:
  float value;
  explicit FloatLiteral(float val, SourceLocation loc = {}) : ExpressionNode(loc), value(val) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ExpressionInitializer : public InitializerNode {
public:
  std::unique_ptr<ExpressionNode> expression;
  explicit ExpressionInitializer(std::unique_ptr<ExpressionNode> expr, SourceLocation loc = {})
      : InitializerNode(loc), expression(std::move(expr)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class InitializerList : public InitializerNode {
public:
  std::vector<std::unique_ptr<InitializerNode>> initializers;
  explicit InitializerList(std::vector<std::unique_ptr<InitializerNode>> inits,
                             SourceLocation loc = {})
      : InitializerNode(loc), initializers(std::move(inits)) {}
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// } // namespace compiler