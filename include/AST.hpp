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

// 源代码位置信息
struct SourceLocation {
  int line = 0;
};

// 基本数据类型
enum class BaseType {
  INT,
  FLOAT,
  VOID,
};

// 一元运算符
enum class UnaryOp {
  PLUS,  // +
  MINUS, // -
  NOT    // !
};

// 二元运算符
enum class BinaryOp {
  ADD,    // +
  SUB,    // -
  MUL,    // *
  DIV,    // /
  MOD,    // %
  GT,     // >
  GTE,    // >=
  LT,     // <
  LTE,    // <=
  EQ,     // ==
  NEQ,    // !=
  AND,    // &&
  OR,     // ||
  ASSIGN, // =
};

// ===--------------------------------------------------------------------=== //
// AST节点前向声明
// ===--------------------------------------------------------------------=== //

// 访问者
class ASTVisitor;

// 基类
class SyntaxNode;
class DeclarationNode;
class StatementNode;
class ExpressionNode;
class InitializerNode;

// 顶层
class TranslationUnit;

// 声明
class ConstDeclaration;
class ConstDefinition;
class VariableDeclaration;
class VariableDefinition;
class FunctionDefinition;
class FunctionParameter;

// 语句
class BlockStatement;
class IfStatement;
class WhileStatement;
class ExpressionStatement;
class ReturnStatement;
class BreakStatement;
class ContinueStatement;

// 表达式
class UnaryExpression;
class BinaryExpression;
class VariableAccess;
class ArrayAccess;
class FunctionCall;
class IntegerLiteral;
class FloatLiteral;

// 初始化
class ExpressionInitializer;
class InitializerList;

// ===--------------------------------------------------------------------=== //
// 访问者模式接口 (AST Visitor Interface)
// ===--------------------------------------------------------------------=== //

class ASTVisitor {
public:
  virtual ~ASTVisitor() = default;

  // 每个具体的AST节点都需要一个visit方法
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

// 所有节点的根基类
class SyntaxNode {
public:
  SourceLocation location;
  virtual ~SyntaxNode() = default;
  virtual void accept(ASTVisitor &visitor) = 0;
};

// 声明节点的基类
class DeclarationNode : public SyntaxNode {};

// 语句节点的基类
class StatementNode : public SyntaxNode {};

// 表达式节点的基类
class ExpressionNode : public SyntaxNode {};

// 初始化器节点的基类
class InitializerNode : public SyntaxNode {};

// ===--------------------------------------------------------------------=== //
// 具体AST节点定义
// ===--------------------------------------------------------------------=== //

// 1. 顶层结构
// CompUnit -> (Decl | FuncDef)*
class TranslationUnit : public SyntaxNode {
public:
  std::vector<std::unique_ptr<DeclarationNode>> declarations;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 2. 声明 (Declarations)
// ConstDecl -> 'const' BType ConstDef {',' ConstDef} ';'
class ConstDeclaration : public DeclarationNode {
public:
  BaseType type;
  std::vector<std::unique_ptr<ConstDefinition>> definitions;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// ConstDef -> Ident {'[' ConstExp ']'} '=' ConstInitVal
class ConstDefinition : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions; // 空表示非数组
  std::unique_ptr<InitializerNode> initializer;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// VarDecl -> BType VarDef {',' VarDef} ';'
class VariableDeclaration : public DeclarationNode {
public:
  BaseType type;
  std::vector<std::unique_ptr<VariableDefinition>> definitions;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// VarDef -> Ident {'[' ConstExp ']'} [ '=' InitVal ]
class VariableDefinition : public SyntaxNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions;
  std::optional<std::unique_ptr<InitializerNode>> initializer;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// FuncDef -> FuncType Ident '(' [FuncFParamList] ')' Block
class FunctionDefinition : public DeclarationNode {
public:
  BaseType return_type;
  std::string name;
  std::vector<std::unique_ptr<FunctionParameter>> parameters;
  std::unique_ptr<BlockStatement> body;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// FuncFParam -> BType Ident ['[' ']' {'[' Exp ']'}]
class FunctionParameter : public SyntaxNode {
public:
  BaseType type;
  std::string name;
  // SysY中，函数参数的第一个维度是未定长的指针，后续维度是定长的
  // is_array_pointer 为 true 表示 `int a[]`
  bool is_array_pointer = false;
  std::vector<std::unique_ptr<ExpressionNode>> array_dimensions;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 3. 语句 (Statements)
// Stmt -> LVal '=' Exp ';' | Block | 'if' ... | ...
class BlockStatement : public StatementNode {
public:
  // 使用 variant 来区分语句和声明
  std::vector<std::variant<std::unique_ptr<StatementNode>,
                           std::unique_ptr<DeclarationNode>>>
      items;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class IfStatement : public StatementNode {
public:
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<StatementNode> then_statement;
  std::optional<std::unique_ptr<StatementNode>> else_statement;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class WhileStatement : public StatementNode {
public:
  std::unique_ptr<ExpressionNode> condition;
  std::unique_ptr<StatementNode> body;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 对应 `[Exp];` 形式的语句
class ExpressionStatement : public StatementNode {
public:
  std::optional<std::unique_ptr<ExpressionNode>> expression; // Exp可以为空，即 `;`

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ReturnStatement : public StatementNode {
public:
  std::optional<std::unique_ptr<ExpressionNode>> expression;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BreakStatement : public StatementNode {
public:
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ContinueStatement : public StatementNode {
public:
  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 4. 表达式 (Expressions)
class UnaryExpression : public ExpressionNode {
public:
  UnaryOp op;
  std::unique_ptr<ExpressionNode> operand;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BinaryExpression : public ExpressionNode {
public:
  BinaryOp op;
  std::unique_ptr<ExpressionNode> lhs; // Left-hand side
  std::unique_ptr<ExpressionNode> rhs; // Right-hand side

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 普通变量访问
class VariableAccess : public ExpressionNode {
public:
  std::string name;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 数组元素访问
class ArrayAccess : public ExpressionNode {
public:
  std::string name;
  std::vector<std::unique_ptr<ExpressionNode>> indices;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FunctionCall : public ExpressionNode {
public:
  std::string function_name;
  std::vector<std::unique_ptr<ExpressionNode>> arguments;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class IntegerLiteral : public ExpressionNode {
public:
  int value;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class FloatLiteral : public ExpressionNode {
public:
  float value;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 5. 初始化 (Initializers)
// ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'

// 单个表达式初始化
class ExpressionInitializer : public InitializerNode {
public:
  std::unique_ptr<ExpressionNode> expression;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// 列表初始化: `{ ... }`
class InitializerList : public InitializerNode {
public:
  std::vector<std::unique_ptr<InitializerNode>> initializers;

  void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

// } // namespace compiler