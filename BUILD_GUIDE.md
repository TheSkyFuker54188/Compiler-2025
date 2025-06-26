# 构建说明文档

## 关于自动生成文件的重要说明

### 为什么要这样做？

我们的项目中有两个重要的文件：
- `yacc/parser.cpp` - 由Bison从`parser.y`自动生成
- `yacc/scanner.cpp` - 由Flex从`lex.l`自动生成

这些自动生成的文件在不同项目间会有很高的相似度，可能影响查重检测。

### 我们的解决方案

**重要：我们不再将自动生成的文件提交到Git仓库中！**

相反，我们在构建时动态生成这些文件。这样：
1. ✅ 避免了查重问题
2. ✅ 保持了代码仓库的简洁
3. ✅ 确保每次构建都使用最新的语法规则

### 构建要求

在构建之前，请确保你的系统安装了：
- `bison` (语法分析器生成工具)
- `flex` (词法分析器生成工具)

#### 在Ubuntu/Debian上安装：
```bash
sudo apt-get install bison flex
```

#### 在macOS上安装：
```bash
brew install bison flex
```

#### 在Windows上安装：
可以通过MSYS2或者WSL安装。

### 构建方法

#### 方法1：使用Make（推荐）
```bash
# 清理之前的构建
make clean

# 构建项目（会自动生成parser.cpp和scanner.cpp）
make

# 运行
./frontend_parser test.sy
```

#### 方法2：使用CMake
```bash
# 配置（会自动查找bison和flex）
cmake -B build

# 构建（会自动生成所需文件）
cmake --build build

# 运行
./build/frontend_parser test.sy
```

### 清理选项

```bash
# 清理所有构建产物（包括自动生成的文件）
make clean

# 只清理自动生成的文件
make clean-generated

# 完全重新构建
make rebuild
```

### 故障排除

**问题：找不到bison或flex**
- 确保已正确安装bison和flex
- 确保它们在系统PATH中

**问题：编译错误提到找不到parser.hpp**
- 这通常意味着parser.cpp还没有生成
- 运行`make clean`然后重新`make`

**问题：语法规则更改后没有生效**
- 删除旧的生成文件：`make clean-generated`
- 重新构建：`make`

### 给小组成员的提醒

1. **永远不要手动编辑** `parser.cpp` 或 `scanner.cpp`
2. **要修改语法规则**，请编辑 `parser.y` 和 `lex.l`
3. **提交代码时**，确保没有提交自动生成的文件
4. **clone项目后**，直接运行`make`或`cmake --build build`即可
