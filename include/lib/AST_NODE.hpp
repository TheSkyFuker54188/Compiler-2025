#pragma once
#include <memory>
#include <list>
#include <string>
#include <cassert>
#include <iostream>
#include "./include/lib/List.hpp"
#include "MagicEnum.hpp"

// 访问者模式的前向声明，这样AST节点就可以接受访问者而不会产生循环依赖
class ASTVisitor;

// 表示源代码中某个token或AST节点的位置信息
class SourceLocation
{
public:
    int start_line = 0;
    int end_line = 0;
    void set(const SourceLocation &loc) { *this = loc; }
    SourceLocation() = default;
    SourceLocation(int line) : start_line(line), end_line(line) {}
};

// 抽象语法树(AST)中所有节点的基类
// 提供基本功能：源代码位置信息 + 访问者模式的accept方法
class SyntaxNode : public SourceLocation
{
public:
    virtual ~SyntaxNode() = default;

    // 把AST子树打印到控制台，用于调试
    // indent_level控制缩进层级，让输出更好看
    virtual void print_node(int indent_level) = 0;

    // 访问者模式的入口点
    // TODO: 每个具体的节点类型都要实现这个方法，调用访问者对应的visit方法
    virtual void accept(ASTVisitor &visitor) = 0;
};

// AST中所有语句节点的基类
class StatementNode : public SyntaxNode
{
public:
    // TODO: 后端通过访问者模式实现这个方法，生成对应的中间代码
    //       例如: visitor.visit(*this);
    void accept(ASTVisitor &visitor) override = 0;
};

// AST中所有表达式节点的基类
class ExpressionNode : public SyntaxNode
{
public:
    // TODO: 后端通过访问者模式实现这个方法，生成计算这个表达式的中间代码
    //       计算结果(比如值、寄存器)由访问者来处理
    //       例如: visitor.visit(*this);
    void accept(ASTVisitor &visitor) override = 0;
};

// 二元和一元运算符的枚举类型
// 从原来的AST_Type重命名，避免太泛化的名字
enum class OperatorType
{
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,    // %
    OP_GT,     // >
    OP_GTE,    // >=
    OP_LT,     // <
    OP_LTE,    // <=
    OP_EQ,     // ==
    OP_NEQ,    // !=
    OP_ASSIGN, // =
    OP_NOT,    // !
    OP_AND,    // &&
    OP_OR      // ||
};

// 表达式链的模板类，用来表示像 `a + b * c` 这样的表达式
// T是操作数的类型（比如另一个表达式链或者基本表达式）
template <typename T>
class ExpressionChain : public ExpressionNode
{
private:
    std::list<OperatorType> op_list; // 运算符列表
    List<T> operand_list;            // 操作数列表

public:
    explicit ExpressionChain(T *first_operand)
    {
        operand_list.push_back(first_operand);
    }

    void add_operand(OperatorType op, T *operand)
    {
        op_list.push_back(op);
        operand_list.push_back(operand);
    }

    void print_node(int indent_level) final
    {
        if (!op_list.empty())
        {
            for (int i = 0; i < indent_level; ++i)
                std::cout << "  ";
            std::cout << magic_enum::enum_name(op_list.front()) << " 层表达式\n";
        }
        for (auto &operand : operand_list)
        {
            operand->print_node(indent_level + !op_list.empty());
        }
    }

    void accept(ASTVisitor &visitor) override
    {
        // TODO: 实现访问表达式链的逻辑
        // 这里需要访问每个操作数并应用运算符
        // visitor.visit(*this);
    }

    // TODO: 后端需要访问操作数和运算符，提供getter方法供后端处理
    const std::list<OperatorType> &get_operators() const { return op_list; }
    const List<T> &get_operands() const { return operand_list; }
};

// 所有具体AST节点类型的前向声明
// 这有助于定义ASTVisitor接口
class TranslationUnit;     // 翻译单元(整个程序)
class ConstDeclaration;    // 常量声明
class VariableDeclaration; // 变量声明
class FunctionDefinition;  // 函数定义
class LValue;              // 左值
class FunctionCall;        // 函数调用
class ConstantValue;       // 常量值
// ... (这里添加所有其他节点类型)

// ASTVisitor接口
// 使用访问者设计模式将操作与AST结构解耦
// 后端(IR生成器、类型检查器等)需要实现这个接口
class ASTVisitor
{
public:
    virtual ~ASTVisitor() = default;

    // TODO: 为每个具体的AST节点类型添加visit方法
    // 示例:
    // virtual void visit(TranslationUnit& node) = 0;
    // virtual void visit(ConstDeclaration& node) = 0;
    // virtual void visit(VariableDeclaration& node) = 0;
    // virtual void visit(FunctionDefinition& node) = 0;
    // virtual void visit(LValue& node) = 0;
    // virtual void visit(FunctionCall& node) = 0;
    // virtual void visit(ConstantValue& node) = 0;
    // ... 对所有其他节点类型都要这样做
};

// --- 具体的AST节点定义 ---
// (文件的其余部分会定义实际的AST节点类，比如
//  TranslationUnit、FunctionDefinition、IfStatement等，
//  它们都继承自SyntaxNode、StatementNode或ExpressionNode)

// 具体节点的示例(用项目中的实际节点替换)
class TranslationUnit : public SyntaxNode
{
public:
    List<SyntaxNode> declarations; // 声明列表
    void add_declaration(SyntaxNode *decl) { declarations.push_back(decl); }
    void print_node(int indent_level) override
    {
        for (auto &decl : declarations)
            decl->print_node(indent_level);
    }
    void accept(ASTVisitor &visitor) override
    {
        // visitor.visit(*this);
    }
};

// Placeholder for other definitions that were in the original file
// to show where they would go.

// ... (rest of the class definitions like ConstDecl, VarDecl, FuncDef, etc.)
// All these classes should be refactored to:
// 1. Inherit from SyntaxNode, StatementNode, or ExpressionNode.
// 2. Remove any `codegen`, `GetInst`, or `GetOperand` methods.
// 3. Implement the `print_node` and `accept` methods.
// 4. Rename classes and members for clarity and to reduce similarity.
//    (e.g., CompUnit -> TranslationUnit, ConstDecl -> ConstDeclaration)