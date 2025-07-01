#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "types.h"

// 符号种类
enum class SymbolKind {
  VARIABLE,    // 变量
  CONSTANT,    // 常量
  FUNCTION,    // 函数
  PARAMETER    // 函数参数
};

// 符号信息类，存储符号的详细信息
class SymbolInfo {
public:
  SymbolKind kind;                    // 符号种类
  std::shared_ptr<Type> type;         // 类型信息
  std::string name;                   // 符号名称
  bool is_initialized;                // 是否已初始化
  
  // 对于常量，存储其值（可选）
  std::optional<std::variant<int, float>> constant_value;
  
  // 对于数组，存储维度信息
  std::vector<int> array_dimensions;
  
  // 对于函数参数，标记是否为数组指针
  bool is_array_pointer = false;
  
  // 构造函数
  SymbolInfo(SymbolKind k, std::shared_ptr<Type> t, std::string n, 
            bool init = false)
      : kind(k), type(std::move(t)), name(std::move(n)), 
        is_initialized(init) {}
  
  // 设置常量值
  void setConstantValue(int value) {
    constant_value = value;
  }
  
  void setConstantValue(float value) {
    constant_value = value;
  }
  
  // 获取常量值
  template<typename T>
  std::optional<T> getConstantValue() const {
    if (!constant_value.has_value()) return std::nullopt;
    
    if (auto* val = std::get_if<T>(&constant_value.value())) {
      return *val;
    }
    return std::nullopt;
  }
  
  // 设置数组维度
  void setArrayDimensions(std::vector<int> dims) {
    array_dimensions = std::move(dims);
  }
  
  // 判断是否为数组
  bool isArray() const {
    return !array_dimensions.empty() || is_array_pointer;
  }
  
  // 获取类型字符串表示
  std::string getTypeString() const {
    return type->toString();
  }
};

using Scope = std::unordered_map<std::string, std::shared_ptr<SymbolInfo>>;

class SymbolTable {
public:
  // 构造函数，创建全局作用域
  SymbolTable() { 
    enterScope(); 
    // 预定义一些内置函数
    initBuiltinFunctions();
  }
  
  // 查找符号，从内层作用域向外查找
  SymbolInfo *lookup(const std::string &name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto found = it->find(name);
      if (found != it->end()) {
        return found->second.get();
      }
    }
    return nullptr;
  }
  
  // 在当前作用域中查找符号（不向外查找）
  SymbolInfo *lookupCurrent(const std::string &name) const {
    if (scopes.empty()) return nullptr;
    
    auto &currentScope = scopes.back();
    auto found = currentScope.find(name);
    if (found != currentScope.end()) {
      return found->second.get();
    }
    return nullptr;
  }
  
  // 在当前作用域中插入符号
  bool insert(const std::string &name, std::shared_ptr<SymbolInfo> info) {
    // 检查当前作用域是否已存在该符号
    auto &currentScope = scopes.back();
    if (currentScope.find(name) != currentScope.end()) {
      return false; // 插入失败，符号已存在
    }
    currentScope[name] = info;
    return true;
  }
  
  // 强制插入符号（用于内置函数等）
  void forceInsert(const std::string &name, std::shared_ptr<SymbolInfo> info) {
    auto &currentScope = scopes.back();
    currentScope[name] = info;
  }
  
  // 进入新的作用域
  void enterScope() { 
    scopes.emplace_back(); 
  }
  
  // 退出当前作用域
  void exitScope() {
    if (!scopes.empty()) {
      scopes.pop_back();
    }
  }
  
  // 获取当前作用域深度
  size_t getScopeDepth() const { 
    return scopes.size(); 
  }
  
  // 判断是否在全局作用域
  bool isGlobalScope() const {
    return scopes.size() == 1;
  }
  
  // 打印符号表（调试用）
  void print() const {
    for (size_t i = 0; i < scopes.size(); ++i) {
      std::cout << "Scope " << i << ":\n";
      for (const auto& [name, info] : scopes[i]) {
        std::cout << "  " << name << ": " << info->getTypeString();
        switch (info->kind) {
          case SymbolKind::VARIABLE: std::cout << " (variable)"; break;
          case SymbolKind::CONSTANT: std::cout << " (constant)"; break;
          case SymbolKind::FUNCTION: std::cout << " (function)"; break;
          case SymbolKind::PARAMETER: std::cout << " (parameter)"; break;
        }
        std::cout << "\n";
      }
    }
  }

private:
  // 作用域栈，每个作用域是一个符号表
  std::vector<Scope> scopes;
  
  // 初始化内置函数
  void initBuiltinFunctions() {
    // 可以在这里添加内置函数，如printf等
    // 例如：void putint(int)
    auto putint_type = makeFunctionType(
      makeBasicType(BaseType::VOID),
      {makeBasicType(BaseType::INT)}
    );
    auto putint_info = std::make_shared<SymbolInfo>(
      SymbolKind::FUNCTION, putint_type, "putint", true
    );
    forceInsert("putint", putint_info);
    
    // void putfloat(float)
    auto putfloat_type = makeFunctionType(
      makeBasicType(BaseType::VOID),
      {makeBasicType(BaseType::FLOAT)}
    );
    auto putfloat_info = std::make_shared<SymbolInfo>(
      SymbolKind::FUNCTION, putfloat_type, "putfloat", true
    );
    forceInsert("putfloat", putfloat_info);
    
    // int getint()
    auto getint_type = makeFunctionType(
      makeBasicType(BaseType::INT),
      {}
    );
    auto getint_info = std::make_shared<SymbolInfo>(
      SymbolKind::FUNCTION, getint_type, "getint", true
    );
    forceInsert("getint", getint_info);
    
    // float getfloat()
    auto getfloat_type = makeFunctionType(
      makeBasicType(BaseType::FLOAT),
      {}
    );
    auto getfloat_info = std::make_shared<SymbolInfo>(
      SymbolKind::FUNCTION, getfloat_type, "getfloat", true
    );
    forceInsert("getfloat", getfloat_info);
  }
};
