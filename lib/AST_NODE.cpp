#include "../include/lib/AST_NODE.hpp"
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

// --- 辅助函数 ---

// 将C++类型名转换为可读的输出，用于调试
static std::string demangle_cpp_typename(const char *mangled_name)
{
    int status = 0;
    // abi::__cxa_demangle是GCC的扩展，用来获取真正的类型名
    char *demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    if (status == 0 && demangled)
    {
        std::string result(demangled);
        free(demangled);
        return result;
    }
    return mangled_name; // 如果解析失败就返回原始名称
}

// 通用的辅助函数，用适当的缩进打印节点的类型和名称
static void print_node_info(SyntaxNode *node, int indent_level, const std::string &node_name)
{
    for (int i = 0; i < indent_level; ++i)
    {
        std::cout << "  ";
    }
    // 打印解析后的C++类名和给定的实例名(比如变量名)
    std::cout << demangle_cpp_typename(typeid(*node).name()) << " (" << node_name << ")\n";
}

// --- 具体AST节点的实现 ---

// 这个文件必须为"AST_NODE.hpp"中定义的每个具体AST节点类
// 提供实现。`print_node`的实现用于调试和可视化，
// 而`accept`方法是为后端访问者准备的。

// 所有与后端逻辑相关的方法(比如`codegen`、`GetInst`、`GetOperand`)
// 都已经被移除，确保前后端完全解耦。

// TODO: 对于每个类，你都必须实现`print_node`和`accept`方法

/*
 * --- 假设节点的实现示例 ---
 *
 * // 在AST_NODE.hpp中:
 * class MyStatementNode : public StatementNode {
 * public:
 *     std::string name;
 *     ExpressionNode* value;
 *     MyStatementNode(const std::string& n, ExpressionNode* v) : name(n), value(v) {}
 *     void print_node(int indent) override;
 *     void accept(ASTVisitor& visitor) override;
 * };
 *
 * // 在AST_NODE.cpp中:
 * void MyStatementNode::print_node(int indent) {
 *     print_node_info(this, indent, name);
 *     if (value) {
 *         value->print_node(indent + 1);
 *     }
 * }
 *
 * void MyStatementNode::accept(ASTVisitor& visitor) {
 *     // 这里会调用后端访问者的实现
 *     // visitor.visit(*this);
 * }
 *
 */

// --- TranslationUnit的实现 ---

void TranslationUnit::print_node(int indent_level)
{
    print_node_info(this, indent_level, "程序根节点");
    for (auto &declaration : declarations)
    {
        if (declaration)
        {
            declaration->print_node(indent_level + 1);
        }
    }
}

void TranslationUnit::accept(ASTVisitor &visitor)
{
    // TODO: 后端访问者将从这里开始遍历AST
    // visitor.visit(*this);
    // for (auto& declaration : declarations) {
    //     if (declaration) declaration->accept(visitor);
    // }
}

// 注意: 由于ExpressionChain是模板类，它的实现
// (声明和定义)必须完全位于头文件(.hpp)中。
// 这是C++模板的要求，否则会出现链接错误。

// 原始文件中所有与后端相关的类和方法都已经从这个文件中移除。
// 这个重构后的文件现在只包含前端特定的逻辑。
