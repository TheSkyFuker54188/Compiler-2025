#include "../include/astprinter.h"
#include <iomanip>
#include <variant>

ASTPrinter::ASTPrinter(std::ostream &output) : out(output) {}

void ASTPrinter::print_indent() {
  for (int i = 0; i < indent_level; ++i)
    out << "  ";
}

void ASTPrinter::print_location(const SyntaxNode &node) {
  out << " @L" << node.line;
}

void ASTPrinter::visit(CompUnit &node) {
  print_indent();
  out << "CompUnit";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  for (size_t i = 0; i < node.items.size(); ++i) {
    print_indent();
    std::visit([this](auto &ptr) { ptr->accept(*this); }, node.items[i]);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(ConstDecl &node) {
  out << "ConstDecl";
  out << "<" << baseTypeToString(node.type) << ">";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  for (size_t i = 0; i < node.definitions.size(); ++i) {
    print_indent();
    node.definitions[i]->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(ConstDef &node) {
  out << "ConstDef(\"" << node.name << "\")";

  if (!node.dimensions.empty()) {
    out << "[";
    for (size_t i = 0; i < node.dimensions.size(); ++i) {
      if (i > 0)
        out << ",";
      out << "dim" << i;
    }
    out << "]";
  }

  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  // 打印数组维度详细信息
  if (!node.dimensions.empty()) {
    print_indent();
    out << "dimensions: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.dimensions.size(); ++i) {
      print_indent();
      node.dimensions[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
  }

  if (node.initializer) {
    print_indent();
    out << "initializer: ";
    node.initializer->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(VarDecl &node) {
  out << "VarDecl";
  out << "<" << baseTypeToString(node.type) << ">";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  for (size_t i = 0; i < node.definitions.size(); ++i) {
    print_indent();
    node.definitions[i]->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(VarDef &node) {
  out << "VarDef(\"" << node.name << "\")";

  if (!node.array_dimensions.empty()) {
    out << "[";
    for (size_t i = 0; i < node.array_dimensions.size(); ++i) {
      if (i > 0)
        out << ",";
      out << "dim" << i;
    }
    out << "]";
  }

  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (!node.array_dimensions.empty()) {
    print_indent();
    out << "dimensions: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.array_dimensions.size(); ++i) {
      print_indent();
      node.array_dimensions[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
  }

  if (node.initializer) {
    print_indent();
    out << "initializer: ";
    (*node.initializer)->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(FuncDef &node) {
  out << "FuncDef(\"" << node.name << "\")";
  out << "<" << baseTypeToString(node.return_type) << ">";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (!node.parameters.empty()) {
    print_indent();
    out << "parameters: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.parameters.size(); ++i) {
      print_indent();
      node.parameters[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
  }

  if (node.body) {
    print_indent();
    out << "body: ";
    node.body->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(FuncFParam &node) {
  out << "FuncFParam(\"" << node.name << "\")";
  out << "<" << baseTypeToString(node.type) << ">";

  if (!node.array_dimensions.empty()) {
    out << "[";
    for (size_t i = 0; i < node.array_dimensions.size(); ++i) {
      if (i > 0)
        out << ",";
      out << "dim" << i;
    }
    out << "]";
  }

  print_location(node);

  // 如果有数组维度，显示详细信息
  if (!node.array_dimensions.empty()) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "dimensions: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.array_dimensions.size(); ++i) {
      print_indent();
      node.array_dimensions[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  } else {
    out << std::endl;
  }
}

void ASTPrinter::visit(Block &node) {
  out << "Block";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  for (size_t i = 0; i < node.items.size(); ++i) {
    print_indent();
    std::visit([this](auto &ptr) { ptr->accept(*this); }, node.items[i]);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(IfStmt &node) {
  out << "IfStmt";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (node.condition) {
    print_indent();
    out << "condition: ";
    node.condition->accept(*this);
  }

  if (node.then_statement) {
    print_indent();
    out << "then: ";
    node.then_statement->accept(*this);
  }

  if (node.else_statement) {
    print_indent();
    out << "else: ";
    (*node.else_statement)->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(WhileStmt &node) {
  out << "WhileStmt";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (node.condition) {
    print_indent();
    out << "condition: ";
    node.condition->accept(*this);
  }

  if (node.body) {
    print_indent();
    out << "body: ";
    node.body->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(ExpStmt &node) {
  out << "ExpStmt";
  print_location(node);
  if (node.expression) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "expression: ";
    (*node.expression)->accept(*this);
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  } else {
    out << " { empty }" << std::endl;
  }
}

void ASTPrinter::visit(AssignStmt &node) {
  out << "AssignStmt";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (node.lvalue) {
    print_indent();
    out << "lvalue: ";
    node.lvalue->accept(*this);
  }

  if (node.rvalue) {
    print_indent();
    out << "rvalue: ";
    node.rvalue->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(ReturnStmt &node) {
  out << "ReturnStmt";
  print_location(node);
  if (node.expression) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "expression: ";
    (*node.expression)->accept(*this);
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  } else {
    out << " { void }" << std::endl;
  }
}

void ASTPrinter::visit(BreakStmt &node) {
  out << "BreakStmt";
  print_location(node);
  out << std::endl;
}

void ASTPrinter::visit(ContinueStmt &node) {
  out << "ContinueStmt";
  print_location(node);
  out << std::endl;
}

void ASTPrinter::visit(UnaryExp &node) {
  out << "UnaryExp(" << unaryOpToString(node.op) << ")";
  print_location(node);
  if (node.operand) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "operand: ";
    node.operand->accept(*this);
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  }
}

void ASTPrinter::visit(BinaryExp &node) {
  out << "BinaryExp(" << binaryOpToString(node.op) << ")";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  if (node.lhs) {
    print_indent();
    out << "left: ";
    node.lhs->accept(*this);
  }

  if (node.rhs) {
    print_indent();
    out << "right: ";
    node.rhs->accept(*this);
  }

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(LVal &node) {
  out << "LVal(\"" << node.name << "\")";

  if (!node.indices.empty()) {
    out << "[";
    for (size_t i = 0; i < node.indices.size(); ++i) {
      if (i > 0)
        out << ",";
      out << "idx" << i;
    }
    out << "]";
  }

  print_location(node);

  // 如果有数组索引，显示详细信息
  if (!node.indices.empty()) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "indices: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.indices.size(); ++i) {
      print_indent();
      node.indices[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  } else {
    out << std::endl;
  }
}

void ASTPrinter::visit(FunctionCall &node) {
  out << "FunctionCall(\"" << node.function_name << "\")";
  print_location(node);

  if (!node.arguments.empty()) {
    out << " {" << std::endl;
    indent_level++;
    print_indent();
    out << "arguments: [" << std::endl;
    indent_level++;
    for (size_t i = 0; i < node.arguments.size(); ++i) {
      print_indent();
      node.arguments[i]->accept(*this);
    }
    indent_level--;
    print_indent();
    out << "]" << std::endl;
    indent_level--;
    print_indent();
    out << "}" << std::endl;
  } else {
    out << " { no_args }" << std::endl;
  }
}

void ASTPrinter::visit(Number &node) {
  out << "Number(";
  std::visit([this](auto &&arg) { out << arg; }, node.v);
  out << ")";
  print_location(node);
  out << std::endl;
}

void ASTPrinter::visit(StringLiteral &node) {
  out << "StringLiteral(\"" << node.v << "\")";
  print_location(node);
  out << std::endl;
}

void ASTPrinter::visit(InitVal &node) {
  out << "InitVal";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  std::visit(
      [this](auto &val) {
        if constexpr (std::is_same_v<std::decay_t<decltype(val)>,
                                     std::unique_ptr<Exp>>) {
          print_indent();
          out << "expression: ";
          val->accept(*this);
        } else {
          print_indent();
          out << "list: [" << std::endl;
          indent_level++;
          for (size_t i = 0; i < val.size(); ++i) {
            print_indent();
            val[i]->accept(*this);
          }
          indent_level--;
          print_indent();
          out << "]" << std::endl;
        }
      },
      node.value);

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}

void ASTPrinter::visit(ConstInitVal &node) {
  out << "ConstInitVal";
  print_location(node);
  out << " {" << std::endl;
  indent_level++;

  std::visit(
      [this](auto &val) {
        if constexpr (std::is_same_v<std::decay_t<decltype(val)>,
                                     std::unique_ptr<Exp>>) {
          print_indent();
          out << "expression: ";
          val->accept(*this);
        } else {
          print_indent();
          out << "list: [" << std::endl;
          indent_level++;
          for (size_t i = 0; i < val.size(); ++i) {
            print_indent();
            val[i]->accept(*this);
          }
          indent_level--;
          print_indent();
          out << "]" << std::endl;
        }
      },
      node.value);

  indent_level--;
  print_indent();
  out << "}" << std::endl;
}