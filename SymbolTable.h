#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <variant>

namespace compiler {

class Type;

// 符号信息类，存储符号的基本信息
class SymbolInfo {
public:
    // 初期可以只存储类型信息，后续扩展
    std::shared_ptr<Type> type;
    
    // 构造函数
    explicit SymbolInfo(std::shared_ptr<Type> type) : type(std::move(type)) {}
};

class SymbolTable {
public:
    // 构造函数，创建全局作用域
    SymbolTable() { enterScope(); }
    
    // 查找符号，从内层作用域向外查找
    SymbolInfo* lookup(const std::string& name) const {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second.get();
            }
        }
        return nullptr;
    }
    
    // 在当前作用域中插入符号
    bool insert(const std::string& name, std::shared_ptr<SymbolInfo> info) {
        // 检查当前作用域是否已存在该符号
        auto& currentScope = scopes.back();
        if (currentScope.find(name) != currentScope.end()) {
            return false; // 插入失败，符号已存在
        }
        
        currentScope[name] = info;
        return true;
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

private:
    // 作用域栈，每个作用域是一个符号表
    std::vector<std::unordered_map<std::string, std::shared_ptr<SymbolInfo>>> scopes;
};

} // namespace compiler