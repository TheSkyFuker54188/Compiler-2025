#pragma once

#include "types.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

enum class SymbolKind {
  VARIABLE, // 变量
  ARRAY,    // 数组
  FUNCTION, // 函数
};

class SymbolInfo {
public:
  SymbolKind kind;            // 符号类型
  std::string name;           // 符号名
  std::unique_ptr<Type> type; // 符号类型
  std::vector<std::variant<int, float>> value;
  std::vector<std::unique_ptr<Type>> parameter_types; // 参数类型列表
  SymbolInfo(SymbolKind k, std::string n, std::unique_ptr<Type> t)
      : kind(k), name(std::move(n)), type(std::move(t)) {}
  virtual ~SymbolInfo() = default;
};

using Scope = std::unordered_map<std::string, std::unique_ptr<SymbolInfo>>;

class SymbolTable {
public:
  SymbolTable() {}

  SymbolInfo *lookup(const std::string &name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto found = it->find(name);
      if (found != it->end())
        return found->second.get();
    }
    return nullptr;
  }

  // 在当前作用域中查找符号（不向外查找）
  SymbolInfo *lookupCurrent(const std::string &name) const {
    if (scopes.empty())
      return nullptr;
    auto &currentScope = scopes.back();
    auto found = currentScope.find(name);
    if (found != currentScope.end())
      return found->second.get();
    return nullptr;
  }

  // 在当前作用域中插入符号
  bool insert(const std::string &name, std::unique_ptr<SymbolInfo> info) {
    auto &currentScope = scopes.back();
    if (currentScope.find(name) != currentScope.end())
      return false; // 插入失败，符号已存在
    currentScope[name] = std::move(info);
    return true;
  }

  void enterScope() { scopes.emplace_back(); }

  // 退出当前作用域
  void exitScope() {
    if (!scopes.empty())
      scopes.pop_back();
  }
  size_t size() const { return scopes.empty() ? 0 : scopes.size(); }
  void initBuiltinFunctions() {
    std::unique_ptr<Type> type = std::make_unique<Type>(BaseType::INT, false);
    std::unique_ptr<SymbolInfo> symbol = std::make_unique<SymbolInfo>(
        SymbolKind::FUNCTION, "getint", std::move(type));
    std::vector<std::unique_ptr<Type>> parameter_types;
    insert("getint", std::move(symbol));
    type = std::make_unique<Type>(BaseType::INT, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "getch",
                                          std::move(type));
    insert("getch", std::move(symbol));
    type = std::make_unique<Type>(BaseType::FLOAT, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "getfloat",
                                          std::move(type));
    insert("getfloat", std::move(symbol));
    type = std::make_unique<Type>(BaseType::INT, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "getarray",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    type->dimensions.push_back(0);
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("getarray", std::move(symbol));
    type = std::make_unique<Type>(BaseType::INT, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "getfarray",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::FLOAT, false);
    type->dimensions.push_back(0);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("getfarray", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putint",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putint", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putch",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putch", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putfloat",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::FLOAT, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putfloat", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putarray",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    type->dimensions.push_back(0);
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putarray", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putfarray",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::INT, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    type = std::make_unique<Type>(BaseType::FLOAT, false);
    type->dimensions.push_back(0);
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putfarray", std::move(symbol));
    type = std::make_unique<Type>(BaseType::VOID, false);
    symbol = std::make_unique<SymbolInfo>(SymbolKind::FUNCTION, "putf",
                                          std::move(type));
    type = std::make_unique<Type>(BaseType::STRING, false);
    parameter_types.clear();
    parameter_types.push_back(std::move(type));
    symbol->parameter_types = std::move(parameter_types);
    insert("putf", std::move(symbol));
  };

private:
  std::vector<Scope> scopes;
};
