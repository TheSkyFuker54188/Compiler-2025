#pragma once

#include <memory>
#include <string>
#include <vector>

enum class BaseType { INT, FLOAT, VOID, STRING };
enum class UnaryOp { PLUS, MINUS, NOT };
enum class BinaryOp {
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  GT,
  GTE,
  LT,
  LTE,
  EQ,
  NEQ,
  AND,
  OR
};

inline std::string baseTypeToString(BaseType type) {
  switch (type) {
  case BaseType::INT:
    return "int";
  case BaseType::FLOAT:
    return "float";
  case BaseType::VOID:
    return "void";
  default:
    return "unknown";
  }
}

inline std::string unaryOpToString(UnaryOp op) {
  switch (op) {
  case UnaryOp::PLUS:
    return "+";
  case UnaryOp::MINUS:
    return "-";
  case UnaryOp::NOT:
    return "!";
  default:
    return "?";
  }
}

inline std::string binaryOpToString(BinaryOp op) {
  switch (op) {
  case BinaryOp::ADD:
    return "+";
  case BinaryOp::SUB:
    return "-";
  case BinaryOp::MUL:
    return "*";
  case BinaryOp::DIV:
    return "/";
  case BinaryOp::MOD:
    return "%";
  case BinaryOp::GT:
    return ">";
  case BinaryOp::GTE:
    return ">=";
  case BinaryOp::LT:
    return "<";
  case BinaryOp::LTE:
    return "<=";
  case BinaryOp::EQ:
    return "==";
  case BinaryOp::NEQ:
    return "!=";
  case BinaryOp::AND:
    return "&&";
  case BinaryOp::OR:
    return "||";
  default:
    return "?";
  }
}

class Type {
public:
  BaseType type;               // 基本类型
  bool is_const;               // 是否为常量
  std::vector<int> dimensions; // 各维度大小
  Type(BaseType t, bool is_const = false) : type(t), is_const(is_const) {}
  virtual ~Type() = default;
  bool equals(Type &other) {
    return type == other.type && dimensions == other.dimensions &&
           is_const == other.is_const;
  }
  bool equals(Type &other, bool is_param = false) {
    for (size_t i = is_param ? 1 : 0; i < dimensions.size(); ++i) {
      if (dimensions[i] != other.dimensions[i])
        return false;
    }
    return true;
  }
  std::string toString() const {
    std::string result = baseTypeToString(type);
    if (is_const)
      result = "const " + result;
    for (int dim : dimensions) {
      result += "[" + std::to_string(dim) + "]";
    }
    return result;
  }
};