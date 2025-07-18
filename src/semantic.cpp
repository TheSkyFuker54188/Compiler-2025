#include "semantic.h"
#include <iostream>
#include <sstream>

extern std::vector<std::string> errors;
bool has_main = false;
int in_loop = 0;

void flatten(BaseType t, std::unique_ptr<ConstInitVal> &init,
             std::vector<int> &dim, ASTVisitor *visitor, int depth) {
  if (std::holds_alternative<std::unique_ptr<Exp>>(init->value)) {
    auto &exp = std::get<std::unique_ptr<Exp>>(init->value);
    if (exp) {
      exp->accept(*visitor);
      if (exp->value.has_value()) {
        if (std::holds_alternative<int>(exp->value.value())) {
          int val = std::get<int>(exp->value.value());
          if (t == BaseType::FLOAT)
            init->v.push_back(static_cast<float>(val));
          else
            init->v.push_back(val);
        } else if (std::holds_alternative<float>(exp->value.value())) {
          float val = std::get<float>(exp->value.value());
          if (t == BaseType::FLOAT)
            init->v.push_back(val);
          else
            init->v.push_back(static_cast<int>(val));
        } else {
          errors.push_back("Error: Invalid constant expression at line " +
                           std::to_string(init->line));
          return;
        }
      }
    }
  } else if (std::holds_alternative<std::vector<std::unique_ptr<ConstInitVal>>>(
                 init->value)) {
    if (depth >= (int)dim.size()) {
      std::cerr << "ERROR INIT" << std::endl;
      return;
    }
    for (auto &item :
         std::get<std::vector<std::unique_ptr<ConstInitVal>>>(init->value)) {
      flatten(t, item, dim, visitor, depth + 1);
      for (auto &v : item->v) {
        if (std::holds_alternative<int>(v)) {
          int val = std::get<int>(v);
          if (t == BaseType::FLOAT)
            init->v.push_back(static_cast<float>(val));
          else
            init->v.push_back(val);
        } else if (std::holds_alternative<float>(v)) {
          float val = std::get<float>(v);
          if (t == BaseType::FLOAT)
            init->v.push_back(val);
          else
            init->v.push_back(static_cast<int>(val));
        }
      }
    }
  }
  if (!dim.empty()) {
    for (int i = init->v.size(); i < dim[depth]; ++i) {
      if (t == BaseType::INT) {
        init->v.push_back(0);
      } else if (t == BaseType::FLOAT) {
        init->v.push_back(0.0f);
      } else {
        errors.push_back(
            "Error: Invalid type for constant initialization at line " +
            std::to_string(init->line));
        return;
      }
    }
  }
}

bool SemanticAnalyzer::analyze(CompUnit &root) {
  // try {
  //   root.accept(*this);
  // } catch (const std::exception &e) {
  //   errors.push_back("Internal error during analysis: " +
  //                    std::string(e.what()));
  //   return false;
  // }
  root.accept(*this);
  return errors.empty();
}

void SemanticAnalyzer::visit(CompUnit &node) {
  symbol_table.enterScope();
  symbol_table.initBuiltinFunctions();
  for (auto &item : node.items)
    std::visit([this](auto &ptr) { ptr->accept(*this); }, item);
  if (!has_main)
    errors.push_back("Error: No 'main' function defined in the program.");
  symbol_table.exitScope();
}

void SemanticAnalyzer::visit(ConstDecl &node) {
  for (auto &def : node.definitions) {
    if (symbol_table.lookupCurrent(def->name)) {
      errors.push_back("Error: Constant '" + def->name +
                       "' redefined in line " + std::to_string(def->line));
      continue;
    }
    std::unique_ptr<Type> type;
    std::unique_ptr<SymbolInfo> symbol;
    SymbolKind kind;
    if (def->dimensions.empty()) {
      type = std::make_unique<Type>(node.type, true);
      kind = SymbolKind::VARIABLE;
    } else {
      type = std::make_unique<Type>(node.type, true);
      for (auto &dim : def->dimensions) {
        dim->accept(*this);
        if (dim->value.has_value() &&
            std::holds_alternative<int>(dim->value.value())) {
          type->dimensions.push_back(std::get<int>(dim->value.value()));
        } else {
          errors.push_back("Error: Constant dimension must be an integer.");
          return;
        }
      }
      kind = SymbolKind::ARRAY;
    }
    flatten(node.type, def->initializer, type->dimensions, this, 0);
    symbol = std::make_unique<SymbolInfo>(kind, def->name, std::move(type));
    if (node.type == BaseType::INT) {
      for (auto &val : def->initializer->v) {
        symbol->value.emplace_back(std::get<int>(val));
      }
    } else if (node.type == BaseType::FLOAT) {
      for (auto &val : def->initializer->v) {
        symbol->value.emplace_back(std::get<float>(val));
      }
    }
    symbol_table.insert(def->name, std::move(symbol));
  }
}

void SemanticAnalyzer::visit(ConstDef &) {}

void SemanticAnalyzer::visit(VarDecl &node) {
  for (auto &def : node.definitions) {
    if (symbol_table.lookupCurrent(def->name)) {
      errors.push_back("Error: Variable '" + def->name +
                       "' redefined in line " + std::to_string(def->line));
      continue;
    }
    std::unique_ptr<Type> type;
    std::unique_ptr<SymbolInfo> symbol;
    if (def->array_dimensions.empty()) {
      type = std::make_unique<Type>(node.type, false);
      symbol = std::make_unique<SymbolInfo>(SymbolKind::VARIABLE, def->name,
                                            std::move(type));
    } else {
      type = std::make_unique<Type>(node.type, false);
      for (auto &dim : def->array_dimensions) {
        dim->accept(*this);
        if (dim->value.has_value()) {
          type->dimensions.push_back(std::get<int>(dim->value.value()));
        } else {
          errors.push_back("Error: Array dimension must be an integer.");
          return;
        }
      }
      symbol = std::make_unique<SymbolInfo>(SymbolKind::ARRAY, def->name,
                                            std::move(type));
    }
    if (def->initializer.has_value())
      def->initializer->get()->accept(*this);
    symbol_table.insert(def->name, std::move(symbol));
  }
}

void SemanticAnalyzer::visit(VarDef &) {}

void SemanticAnalyzer::visit(FuncDef &node) {
  if (symbol_table.lookupCurrent(node.name)) {
    errors.push_back("Error: Function '" + node.name + "' redefined in line " +
                     std::to_string(node.line));
    return;
  }
  symbol_table.enterScope();
  if (node.name == "main")
    has_main = true;
  std::unique_ptr<Type> type1 = std::make_unique<Type>(node.return_type, false),
                        type2 = std::make_unique<Type>(node.return_type, false);
  std::unique_ptr<SymbolInfo> symbol1 = std::make_unique<SymbolInfo>(
                                  SymbolKind::FUNCTION, node.name,
                                  std::move(type1)),
                              symbol2 = std::make_unique<SymbolInfo>(
                                  SymbolKind::FUNCTION, node.name,
                                  std::move(type2));
  for (auto &param : node.parameters) {
    param->accept(*this);
    std::unique_ptr<Type> t1 = std::make_unique<Type>(param->type, false),
                          t2 = std::make_unique<Type>(param->type, false),
                          t3 = std::make_unique<Type>(param->type, false);
    SymbolKind kind = SymbolKind::VARIABLE;
    if (!param->array_dimensions.empty()) {
      kind = SymbolKind::ARRAY;
      for (auto &dim : param->array_dimensions) {
        dim->accept(*this);
        if (dim->value.has_value()) {
          t1->dimensions.push_back(std::get<int>(dim->value.value()));
          t2->dimensions.push_back(std::get<int>(dim->value.value()));
          t3->dimensions.push_back(std::get<int>(dim->value.value()));
        } else {
          errors.push_back("Error: Array dimension must be an integer.");
          return;
        }
      }
    }
    symbol1->parameter_types.push_back(std::move(t1));
    symbol2->parameter_types.push_back(std::move(t2));
    std::unique_ptr<SymbolInfo> param_symbol =
        std::make_unique<SymbolInfo>(kind, param->name, std::move(t3));
    symbol_table.insert(param->name, std::move(param_symbol));
  }
  symbol_table.insert(node.name, std::move(symbol1));
  node.body->accept(*this);
  symbol_table.exitScope();
  symbol_table.insert(node.name, std::move(symbol2));
}

void SemanticAnalyzer::visit(FuncFParam &node) {
  for (size_t i = 1; i < node.array_dimensions.size(); ++i) {
    node.array_dimensions[i]->accept(*this);
    if (!node.array_dimensions[i]->value.has_value()) {
      errors.push_back("Error: Array dimension must be an integer.");
      return;
    }
  }
}

void SemanticAnalyzer::visit(Block &node) {
  symbol_table.enterScope();
  for (auto &item : node.items)
    std::visit([this](auto &ptr) { ptr->accept(*this); }, item);
  symbol_table.exitScope();
}

void SemanticAnalyzer::visit(IfStmt &node) {
  if (node.condition) {
    node.condition->accept(*this);
  } else {
    errors.push_back("Error: If statement condition cannot be empty at line " +
                     std::to_string(node.line));
    return;
  }
  if (node.then_statement)
    node.then_statement->accept(*this);
  if (node.else_statement.has_value())
    node.else_statement->get()->accept(*this);
}

void SemanticAnalyzer::visit(WhileStmt &node) {
  if (node.condition) {
    node.condition->accept(*this);
  } else {
    errors.push_back(
        "Error: While statement condition cannot be empty at line " +
        std::to_string(node.line));
    return;
  }
  in_loop++;
  if (node.body)
    node.body->accept(*this);
  in_loop--;
}

void SemanticAnalyzer::visit(ExpStmt &node) {
  if (node.expression)
    (*node.expression)->accept(*this);
}

void SemanticAnalyzer::visit(AssignStmt &node) {
  node.lvalue->accept(*this);
  if (node.lvalue->type->is_const) {
    errors.push_back("Error: Cannot assign to constant variable '" +
                     node.lvalue->name + "' at line " +
                     std::to_string(node.line));
    return;
  }
  node.rvalue->accept(*this);
}

void SemanticAnalyzer::visit(ReturnStmt &node) {
  if (node.expression.has_value())
    node.expression->get()->accept(*this);
}

void SemanticAnalyzer::visit(BreakStmt &node) {
  if (!in_loop)
    errors.push_back(
        "Error: 'break' statement can only be used inside a loop at "
        "line " +
        std::to_string(node.line));
}

void SemanticAnalyzer::visit(ContinueStmt &node) {
  if (!in_loop)
    errors.push_back(
        "Error: 'continue' statement can only be used inside a loop at "
        "line " +
        std::to_string(node.line));
}

void SemanticAnalyzer::visit(UnaryExp &node) {
  if (node.operand)
    node.operand->accept(*this);
  if (node.operand && node.operand->value.has_value()) {
    if (node.op == UnaryOp::PLUS) {
      node.value = node.operand->value;
    } else if (node.op == UnaryOp::MINUS) {
      if (std::holds_alternative<int>(node.operand->value.value()))
        node.value = -std::get<int>(node.operand->value.value());
      else if (std::holds_alternative<float>(node.operand->value.value()))
        node.value = -std::get<float>(node.operand->value.value());
    } else if (node.op == UnaryOp::NOT) {
      if (std::holds_alternative<int>(node.operand->value.value()))
        node.value = !std::get<int>(node.operand->value.value());
      else if (std::holds_alternative<float>(node.operand->value.value()))
        node.value = !std::get<float>(node.operand->value.value());
    }
  }
  node.type = std::make_unique<Type>(node.operand->type->type, false);
  node.type->dimensions = node.operand->type->dimensions;
}

void SemanticAnalyzer::visit(BinaryExp &node) {
  if (node.lhs)
    node.lhs->accept(*this);
  if (node.rhs)
    node.rhs->accept(*this);
  if (node.lhs->value.has_value() && node.rhs->value.has_value()) {
    if (node.op == BinaryOp::ADD) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) +
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) +
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) +
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) +
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::SUB) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) -
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) -
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) -
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) -
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::MUL) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) *
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) *
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) *
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) *
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::DIV) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) /
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) /
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) /
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) /
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::MOD) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) %
                     std::get<int>(node.rhs->value.value());
      } else {
        errors.push_back(
            "Error: Modulus operator can only be used with integers.");
        return;
      }
    } else if (node.op == BinaryOp::GT) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) >
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) >
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) >
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) >
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::GTE) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) >=
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) >=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) >=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) >=
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::LT) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) <
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) <
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) <
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) <
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::LTE) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) <=
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) <=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) <=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) <=
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::EQ) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) ==
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) ==
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) ==
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) ==
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::NEQ) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) !=
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) !=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) !=
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) !=
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::AND) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) &&
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) &&
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) &&
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) &&
                     std::get<int>(node.rhs->value.value());
      }
    } else if (node.op == BinaryOp::OR) {
      if (std::holds_alternative<int>(node.lhs->value.value()) &&
          std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) ||
                     std::get<int>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) ||
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<int>(node.lhs->value.value()) &&
                 std::holds_alternative<float>(node.rhs->value.value())) {
        node.value = std::get<int>(node.lhs->value.value()) ||
                     std::get<float>(node.rhs->value.value());
      } else if (std::holds_alternative<float>(node.lhs->value.value()) &&
                 std::holds_alternative<int>(node.rhs->value.value())) {
        node.value = std::get<float>(node.lhs->value.value()) ||
                     std::get<int>(node.rhs->value.value());
      }
    }
  }
  BaseType type = (node.lhs->type->type == BaseType::FLOAT ||
                   node.lhs->type->type == BaseType::FLOAT)
                      ? BaseType::FLOAT
                      : BaseType::INT;
  node.type = std::make_unique<Type>(type, false);
}

void SemanticAnalyzer::visit(LVal &node) {
  auto symbol = symbol_table.lookup(node.name);
  if (!symbol) {
    errors.push_back("Error: Undefined variable '" + node.name + "' at line " +
                     std::to_string(node.line));
    return;
  }
  int d = 1;
  for (auto &index : node.indices) {
    index->accept(*this);
    if (node.is_const)
      d *= (std::get<int>(index->value.value()) + 1);
  }
  d--;
  node.type =
      std::make_unique<Type>(symbol->type->type, symbol->type->is_const);
  if (node.is_const ||
      (symbol->kind == SymbolKind::VARIABLE && symbol->type->is_const)) {
    if (node.type->type == BaseType::INT)
      node.value = std::get<int>(symbol->value[d]);
    else if (node.type->type == BaseType::FLOAT)
      node.value = std::get<float>(symbol->value[d]);
    else {
      errors.push_back("Error: Invalid constant type for variable '" +
                       node.name + "' at line " + std::to_string(node.line));
      return;
    }
  }
}

void SemanticAnalyzer::visit(FunctionCall &node) {
  auto symbol = symbol_table.lookup(node.function_name);
  if (!symbol) {
    errors.push_back("Error: Undefined function '" + node.function_name +
                     "' at line " + std::to_string(node.line));
    return;
  }
  if (node.function_name == "putf") {
    for (size_t i = 0; i < node.arguments.size(); ++i)
      node.arguments[i]->accept(*this);
  }
  auto &param_types = symbol->parameter_types;
  if (node.arguments.size() != param_types.size()) {
    errors.push_back("Error: Function '" + node.function_name +
                     "' called with incorrect number of arguments at line " +
                     std::to_string(node.line));
    return;
  }
  for (size_t i = 0; i < node.arguments.size(); ++i) {
    node.arguments[i]->accept(*this);
    if (!node.arguments[i]->type->equals(*param_types[i], true)) {
      errors.push_back("Error: Argument type mismatch for function '" +
                       node.function_name + "' at line " +
                       std::to_string(node.line));
      return;
    }
  }
  node.type = std::make_unique<Type>(symbol->type->type, false);
}

void SemanticAnalyzer::visit(Number &node) {
  if (std::holds_alternative<int>(node.v)) {
    node.value = std::get<int>(node.v);
    node.type = std::make_unique<Type>(BaseType::INT, false);
  } else if (std::holds_alternative<float>(node.v)) {
    node.value = std::get<float>(node.v);
    node.type = std::make_unique<Type>(BaseType::FLOAT, false);
  } else {
    errors.push_back("Error: Invalid number type at line " +
                     std::to_string(node.line));
  }
}

void SemanticAnalyzer::visit(StringLiteral &node) {
  node.value = node.v;
  node.type = std::make_unique<Type>(BaseType::STRING, false);
}

void SemanticAnalyzer::visit(InitVal &node) {
  std::visit(
      [this](auto &value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>,
                                     std::unique_ptr<Exp>>) {
          if (value)
            value->accept(*this);
        } else {
          for (auto &item : value) {
            if (item)
              item->accept(*this);
          }
        }
      },
      node.value);
}

void SemanticAnalyzer::visit(ConstInitVal &) {}