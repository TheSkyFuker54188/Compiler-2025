# SYS Language Compiler Makefile
# Author: SYS Compiler Team
# Description: Build system for SYS language compiler

# ===--------------------------------------------------------------------=== #
# 编译器设置
# ===--------------------------------------------------------------------=== #

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -Iinclude
LDFLAGS = -lfl

# Debug/Release modes
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g -O0 -DDEBUG
    BUILD_DIR = build/debug
else
    CXXFLAGS += -O2 -DNDEBUG
    BUILD_DIR = build/release
endif

# ===--------------------------------------------------------------------=== #
# 目录设置
# ===--------------------------------------------------------------------=== #

LEXER_DIR = lexer
PARSER_DIR = parser
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

# ===--------------------------------------------------------------------=== #
# 源文件和目标文件
# ===--------------------------------------------------------------------=== #

# 生成的文件
LEX_SRC = $(LEXER_DIR)/lex.yy.c
PARSER_SRC = $(PARSER_DIR)/parser.tab.c
PARSER_HDR = $(PARSER_DIR)/parser.tab.h

# 源文件
MAIN_SRC = main.cpp
ASTPRINTER_SRC = $(SRC_DIR)/astprinter.cpp
SEMANTIC_SRC = $(SRC_DIR)/semantic.cpp
IRGENERATE_SRC = $(SRC_DIR)/irgenerate.cpp
# SSA模块源文件
SSA_TRANSFORM_SRC = $(SRC_DIR)/ssa_transform.cpp
SSA_OPTIMIZER_SRC = $(SRC_DIR)/ssa_optimizer.cpp  
SSA_DESTROYER_SRC = $(SRC_DIR)/ssa_destroyer.cpp

RISCV_MIR_SRC = $(SRC_DIR)/riscv_mir.cpp
GLOBALISEL_SRC = $(SRC_DIR)/globalisel.cpp
REGISTER_ALLOC_SRC = $(SRC_DIR)/register_alloc.cpp
CODE_EMITTER_SRC = $(SRC_DIR)/code_emitter.cpp

# 目标文件
MAIN_OBJ = $(BUILD_DIR)/main.o
ASTPRINTER_OBJ = $(BUILD_DIR)/astprinter.o
SEMANTIC_OBJ = $(BUILD_DIR)/semantic.o
IRGENERATE_OBJ = $(BUILD_DIR)/irgenerate.o
SSA_TRANSFORM_OBJ = $(BUILD_DIR)/ssa_transform.o
SSA_OPTIMIZER_OBJ = $(BUILD_DIR)/ssa_optimizer.o
SSA_DESTROYER_OBJ = $(BUILD_DIR)/ssa_destroyer.o
RISCV_MIR_OBJ = $(BUILD_DIR)/riscv_mir.o
GLOBALISEL_OBJ = $(BUILD_DIR)/globalisel.o
REGISTER_ALLOC_OBJ = $(BUILD_DIR)/register_alloc.o
CODE_EMITTER_OBJ = $(BUILD_DIR)/code_emitter.o
LEX_OBJ = $(BUILD_DIR)/lex.yy.o
PARSER_OBJ = $(BUILD_DIR)/parser.tab.o

# 所有目标文件
OBJS = $(MAIN_OBJ) $(ASTPRINTER_OBJ) $(SEMANTIC_OBJ) $(IRGENERATE_OBJ) $(RISCV_MIR_OBJ) $(GLOBALISEL_OBJ) $(REGISTER_ALLOC_OBJ) $(CODE_EMITTER_OBJ) $(SSA_TRANSFORM_OBJ) $(SSA_OPTIMIZER_OBJ) $(SSA_DESTROYER_OBJ) $(GLOBAL_ISEL_OBJ) $(LINEAR_SCAN_OBJ) $(LEX_OBJ) $(PARSER_OBJ) 

# 可执行文件
TARGET = compiler

# ===--------------------------------------------------------------------=== #
# 主要目标
# ===--------------------------------------------------------------------=== #

.PHONY: all clean test debug release help install

# 默认目标
all: $(TARGET)

# 可执行文件构建
$(TARGET): $(OBJS) | $(BUILD_DIR)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# ===--------------------------------------------------------------------=== #
# 编译规则
# ===--------------------------------------------------------------------=== #

# 主程序编译
$(MAIN_OBJ): $(MAIN_SRC) $(PARSER_HDR) | $(BUILD_DIR)
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# AST打印器编译
$(ASTPRINTER_OBJ): $(ASTPRINTER_SRC) $(INCLUDE_DIR)/astprinter.h $(INCLUDE_DIR)/ast.h | $(BUILD_DIR)
	@echo "Compiling astprinter.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 语义分析器编译
$(SEMANTIC_OBJ): $(SEMANTIC_SRC) $(INCLUDE_DIR)/semantic.h $(INCLUDE_DIR)/ast.h $(INCLUDE_DIR)/symtab.h $(INCLUDE_DIR)/types.h | $(BUILD_DIR)
	@echo "Compiling semantic.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# IR生成器编译
$(IRGENERATE_OBJ): $(IRGENERATE_SRC) $(INCLUDE_DIR)/block.h $(INCLUDE_DIR)/ast.h $(INCLUDE_DIR)/symtab.h | $(BUILD_DIR)
	@echo "Compiling irgenerate.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# RISC-V MIR编译
$(RISCV_MIR_OBJ): $(RISCV_MIR_SRC) $(INCLUDE_DIR)/riscv_mir.h | $(BUILD_DIR)
	@echo "Compiling riscv_mir.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# SSA变换器编译
$(SSA_TRANSFORM_OBJ): $(SSA_TRANSFORM_SRC) $(INCLUDE_DIR)/ssa.h $(INCLUDE_DIR)/block.h $(INCLUDE_DIR)/instruction.h | $(BUILD_DIR)
	@echo "Compiling ssa_transform.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# SSA优化器编译
$(SSA_OPTIMIZER_OBJ): $(SSA_OPTIMIZER_SRC) $(INCLUDE_DIR)/ssa.h $(INCLUDE_DIR)/block.h $(INCLUDE_DIR)/instruction.h | $(BUILD_DIR)
	@echo "Compiling ssa_optimizer.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# SSA销毁器编译
$(SSA_DESTROYER_OBJ): $(SSA_DESTROYER_SRC) $(INCLUDE_DIR)/ssa.h $(INCLUDE_DIR)/block.h $(INCLUDE_DIR)/instruction.h | $(BUILD_DIR)
	@echo "Compiling ssa_destroyer.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# GlobalISel编译
$(GLOBALISEL_OBJ): $(GLOBALISEL_SRC) $(INCLUDE_DIR)/globalisel.h $(INCLUDE_DIR)/riscv_mir.h $(INCLUDE_DIR)/instruction.h $(INCLUDE_DIR)/block.h | $(BUILD_DIR)
	@echo "Compiling globalisel.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 寄存器分配器编译
$(REGISTER_ALLOC_OBJ): $(REGISTER_ALLOC_SRC) $(INCLUDE_DIR)/register_alloc.h $(INCLUDE_DIR)/riscv_mir.h $(INCLUDE_DIR)/globalisel.h | $(BUILD_DIR)
	@echo "Compiling register_alloc.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 代码发射器编译
$(CODE_EMITTER_OBJ): $(CODE_EMITTER_SRC) $(INCLUDE_DIR)/code_emitter.h $(INCLUDE_DIR)/riscv_mir.h | $(BUILD_DIR)
	@echo "Compiling code_emitter.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 词法分析器编译
$(LEX_OBJ): $(LEX_SRC) $(PARSER_HDR) | $(BUILD_DIR)
	@echo "Compiling lexer..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 语法分析器编译
$(PARSER_OBJ): $(PARSER_SRC) | $(BUILD_DIR)
	@echo "Compiling parser..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===--------------------------------------------------------------------=== #
# 生成器规则
# ===--------------------------------------------------------------------=== #

# 生成词法分析器
$(LEX_SRC): $(LEXER_DIR)/lex.l
	@echo "Generating lexer with flex..."
	cd $(LEXER_DIR) && flex lex.l

# 生成语法分析器
$(PARSER_SRC) $(PARSER_HDR): $(PARSER_DIR)/parser.y
	@echo "Generating parser with bison..."
	cd $(PARSER_DIR) && bison -d parser.y

# ===--------------------------------------------------------------------=== #
# 目录创建
# ===--------------------------------------------------------------------=== #

$(BUILD_DIR):
	@echo "Creating build directory..."
	mkdir -p $(BUILD_DIR)

# ===--------------------------------------------------------------------=== #
# 特殊目标
# ===--------------------------------------------------------------------=== #

# Debug 构建
debug:
	$(MAKE) DEBUG=1

# Release 构建
release:
	$(MAKE) DEBUG=0

# 测试目标
test: $(TARGET)
	@echo "Running tests..."
	@chmod +x test_batch.sh
	@./test_batch.sh

# 单个测试
test-single: $(TARGET)
	@if [ -n "$(FILE)" ]; then \
		echo "Testing single file: $(FILE)"; \
		./$(TARGET) $(FILE); \
	else \
		echo "Usage: make test-single FILE=path/to/test.sy"; \
	fi

# ===--------------------------------------------------------------------=== #
# 清理规则
# ===--------------------------------------------------------------------=== #

# 清理编译产物
clean:
	@echo "Cleaning build files..."
	rm -rf build/
	rm -f $(TARGET)
	rm -f tests/h_functional/*.ll
	rm -f tests/functional/*.ll
	rm -f tests/h_functional/*.ast
	rm -f tests/functional/*.ast
	rm -f tests/h_functional/*.mir
	rm -f tests/functional/*.mir
	rm -f tests/h_functional/*.s
	rm -f tests/functional/*.s
	rm -rf test_logs/

# 深度清理（包括生成的词法分析器和语法分析器）
distclean: clean
	@echo "Deep cleaning generated files..."
	rm -f $(LEX_SRC)
	rm -f $(PARSER_SRC) $(PARSER_HDR)
	rm -f $(PARSER_DIR)/parser.output

# ===--------------------------------------------------------------------=== #
# 开发辅助目标
# ===--------------------------------------------------------------------=== #

# 重新构建
rebuild: clean all

# 检查语法分析器冲突
check-conflicts: $(PARSER_SRC)
	@echo "Checking parser conflicts..."
	@if [ -f $(PARSER_DIR)/parser.output ]; then \
		grep -E "(conflict|error)" $(PARSER_DIR)/parser.output || echo "No conflicts found!"; \
	else \
		echo "Parser output file not found"; \
	fi

# 显示构建信息
info:
	@echo "SYS Language Compiler Build Information"
	@echo "======================================="
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Target: $(TARGET)"
	@echo "Build Dir: $(BUILD_DIR)"
	@echo "Debug Mode: $(DEBUG)"
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build the compiler"
	@echo "  debug        - Build debug version"
	@echo "  release      - Build release version"
	@echo "  test         - Run test suite"
	@echo "  test-single  - Test single file (use FILE=...)"
	@echo "  clean        - Remove build files"
	@echo "  distclean    - Remove all generated files"
	@echo "  rebuild      - Clean and build"
	@echo "  help         - Show this help"

# 帮助信息
help: info

# ===--------------------------------------------------------------------=== #
# 依赖关系
# ===--------------------------------------------------------------------=== #

# 确保头文件改变时重新编译
$(MAIN_OBJ): $(INCLUDE_DIR)/ast.h $(INCLUDE_DIR)/astprinter.h
$(ASTPRINTER_OBJ): $(INCLUDE_DIR)/ast.h $(INCLUDE_DIR)/astprinter.h

# 确保语法分析器改变时重新编译词法分析器
$(LEX_OBJ): $(PARSER_HDR)

# ===--------------------------------------------------------------------=== #
# 文件模式匹配（防止与文件名冲突）
# ===--------------------------------------------------------------------=== #

# 防止目标名与文件名冲突
.PHONY: all clean test debug release help rebuild check-conflicts info distclean test-single 