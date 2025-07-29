#!/bin/bash

# SSA优化测试脚本
# 测试SSA变换和优化功能的正确性

echo "=== SSA优化功能测试 ==="

# 编译编译器
echo "编译SSA编译器..."
make clean
make

if [ $? -ne 0 ]; then
    echo "编译失败!"
    exit 1
fi

echo "编译成功!"

# 测试文件
TEST_FILES=(
    "tests/functional/00_main.sy"
    "tests/functional/01_var_defn2.sy" 
    "tests/functional/11_add2.sy"
    "tests/functional/21_if_test2.sy"
    "tests/functional/25_while_if.sy"
    "tests/functional/100_test_ssa_optimization.sy"
)

# 创建测试结果目录
mkdir -p test_results/ssa

echo ""
echo "开始SSA优化功能测试..."

# 统计变量
total_tests=0
passed_tests=0
optimization_stats=""

for test_file in "${TEST_FILES[@]}"; do
    echo ""
    echo "测试文件: $test_file"
    total_tests=$((total_tests + 1))
    
    if [ ! -f "$test_file" ]; then
        echo "  警告: 测试文件不存在，跳过"
        continue
    fi
    
    # 运行编译器 - 添加SSA参数
    ./compiler --ssa -S -o "test_results/ssa/$(basename ${test_file%.sy}).s" "$test_file" > "test_results/ssa/$(basename ${test_file%.sy}).log" 2>&1
    
    if [ $? -eq 0 ]; then
        echo "  ✓ 编译成功"
        passed_tests=$((passed_tests + 1))
        
        # 检查生成的文件
        base_name=$(basename ${test_file%.sy})
        
        echo "  生成的文件:"
        ls -la "${test_file%.sy}"*.ll "${test_file%.sy}"*.s "test_results/ssa/${base_name}.s" 2>/dev/null | sed 's/^/    /'
        
        # 分析优化效果
        echo "  优化分析:"
        
        # 统计原始IR指令数
        if [ -f "${test_file%.sy}.ll" ]; then
            original_count=$(grep -c "^\s*%" "${test_file%.sy}.ll" 2>/dev/null | tr -d '\n' || echo "0")
            echo "    原始IR指令数: $original_count"
        fi
        
        # 统计SSA形式IR指令数
        if [ -f "${test_file%.sy}_ssa.ll" ]; then
            ssa_count=$(grep -c "^\s*%" "${test_file%.sy}_ssa.ll" 2>/dev/null | tr -d '\n' || echo "0")
            echo "    SSA形式IR指令数: $ssa_count"
            echo "    ✓ SSA形式IR文件已生成"
        else
            echo "    ⚠ SSA形式IR文件未找到"
        fi
        
        # 统计优化后IR指令数
        if [ -f "${test_file%.sy}_opt.ll" ]; then
            opt_count=$(grep -c "^\s*%" "${test_file%.sy}_opt.ll" 2>/dev/null | tr -d '\n' || echo "0")
            echo "    优化后IR指令数: $opt_count"
            echo "    ✓ 优化后IR文件已生成"
            
            # 计算优化效果
            if [ "$original_count" -gt 0 ] && [ "$opt_count" -lt "$original_count" ]; then
                reduction=$((original_count - opt_count))
                percentage=$(echo "scale=1; $reduction * 100 / $original_count" | bc -l 2>/dev/null || echo "N/A")
                echo "    ✓ 优化效果: 减少 $reduction 条指令 (${percentage}%)"
                optimization_stats="$optimization_stats\n$base_name: $original_count -> $opt_count (-$reduction)"
            elif [ "$opt_count" -eq "$original_count" ]; then
                echo "    = 无优化空间或已经是最优"
            else
                echo "    - 指令数增加或分析有误"
            fi
        else
            echo "    ⚠ 优化后IR文件未找到"
        fi
        
        # 检查编译日志中的优化信息
        if [ -f "test_results/ssa/${base_name}.log" ]; then
            echo "  优化日志摘要:"
            grep -E "(SSA|optimization|eliminated|removed|folded)" "test_results/ssa/${base_name}.log" | head -5 | sed 's/^/    /'
        fi
        
        # 验证语法正确性
        if [ -f "test_results/ssa/${base_name}.s" ]; then
            echo "  ✓ 汇编文件已生成"
            
            # 简单的汇编语法检查
            if grep -q "\.text\|\.data\|\.globl" "test_results/ssa/${base_name}.s"; then
                echo "    ✓ 汇编文件包含基本段标识"
            fi
        fi
        
    else
        echo "  ✗ 编译失败"
        
        # 显示错误信息
        if [ -f "test_results/ssa/$(basename ${test_file%.sy}).log" ]; then
            echo "  错误信息:"
            tail -10 "test_results/ssa/$(basename ${test_file%.sy}).log" | sed 's/^/    /'
        fi
    fi
done

echo ""
echo "=== SSA测试结果汇总 ==="

echo "测试统计:"
echo "  总测试数: $total_tests"
echo "  通过测试: $passed_tests"
echo "  成功率: $(echo "scale=1; $passed_tests * 100 / $total_tests" | bc -l 2>/dev/null || echo "N/A")%"

echo ""
echo "文件生成统计:"
echo "  原始IR文件: $(find . -name "*.ll" -not -name "*_ssa.ll" -not -name "*_opt.ll" | wc -l)"
echo "  SSA形式IR文件: $(find . -name "*_ssa.ll" | wc -l)" 
echo "  优化后IR文件: $(find . -name "*_opt.ll" | wc -l)"
echo "  汇编文件: $(find test_results/ssa -name "*.s" 2>/dev/null | wc -l)"

if [ -n "$optimization_stats" ]; then
    echo ""
    echo "优化效果汇总:"
    echo -e "$optimization_stats"
fi
echo "=== ssa批量测试 ==="
echo

# 创建输出目录
mkdir -p test_logs_ssa

# 初始化日志文件
> test_logs_ssa/ssa_validation.log
> test_logs_ssa/ssa_execution_test.log

passed=0
failed=0

for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        if ./compiler --ast "$file"; then
            echo "通过"
            ((passed++))
        else
            echo "失败"
            ((failed++))
        fi
    else
        echo "跳过 $file (文件不存在)"
        ((failed++))
    fi
done

for file in tests/functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        if ./compiler --ast "$file"; then
            echo "通过"
            ((passed++))
        else
            echo "失败"
            ((failed++))
        fi
    else
        echo "跳过 $file (文件不存在)"
        ((failed++))
    fi
done

true=0
false=0

# LLVM IR验证测试 - 输出到日志文件
echo "=== SSA验证测试开始 ===" >> test_logs_ssa/ssa_validation.log
for file in tests/h_functional/*.ll; do
    # 跳过特殊文件
    if [[ "$file" != *_ssa.ll ]]; then
        continue
    fi
    
    # 在日志文件中记录测试信息
    echo "验证 $file ... " >> test_logs_ssa/ssa_validation.log
    
    # 运行验证并将输出重定向到日志文件
    #if opt -p=verify "$file" -S >> test_logs_ssa/ssa_validation.log 2>&1; then
    if opt -opaque-pointers -verify "$file" -S >> test_logs_ssa/ssa_validation.log 2>&1; then
        echo "测试 $file 通过" | tee -a test_logs_ssa/ssa_validation.log
        ((true++))
    else
        echo "测试 $file 失败" | tee -a test_logs_ssa/ssa_validation.log
        ((false++))
    fi
    
    # 添加分隔线
    echo "----------------------------------------" >> test_logs_ssa/ssa_validation.log
done

for file in tests/functional/*.ll; do
    # 跳过特殊文件
    if [[ "$file" != *_ssa.ll ]]; then
        continue
    fi
    
    # 在日志文件中记录测试信息
    echo "验证 $file ... " >> test_logs_ssa/ssa_validation.log
    
    # 运行验证并将输出重定向到日志文件
    #if opt -p=verify "$file" -S >> test_logs_ssa/ssa_validation.log 2>&1; then
    if opt -opaque-pointers -verify "$file" -S >> test_logs_ssa/ssa_validation.log 2>&1; then
        echo "测试 $file 通过" | tee -a test_logs_ssa/ssa_validation.log
        ((true++))
    else
        echo "测试 $file 失败" | tee -a test_logs_ssa/ssa_validation.log
        ((false++))
    fi
    
    # 添加分隔线
    echo "----------------------------------------" >> test_logs_ssa/ssa_validation.log
done
echo "=== SSA测试结束 ===" >> test_logs_ssa/ssa_validation.log

# 执行测试验证 - 输出到日志文件
exec_passed=0
exec_failed=0

echo "=== 执行测试验证开始 ===" >> test_logs_ssa/ssa_execution_test.log

process_dir() {
    local dir=$1
    
    for ll_file in "$dir"/*_ssa.ll; do
        # 跳过特殊文件
        if [[ "$file" != *_ssa.ll ]]; then
        continue
        fi
        
        # 获取基本文件名（不带扩展名）
        base_name=$(basename "$ll_file" _ssa.ll)
        
        # 查找对应的.out文件
        out_file="$dir/$base_name.out"
        
        # 在日志文件中记录测试信息
        echo "测试文件: $ll_file" >> test_logs_ssa/ssa_execution_test.log
        echo "期望输出文件: $out_file" >> test_logs_ssa/ssa_execution_test.log
        
        # 检查.out文件是否存在
        if [ ! -f "$out_file" ]; then
            echo "警告: 找不到 $out_file, 跳过测试 $ll_file" | tee -a test_logs_ssa/ssa_execution_test.log
            continue
        fi
        
        # 执行LLVM IR文件并捕获返回值
        echo "执行命令: lli-17 $ll_file" >> test_logs_ssa/ssa_execution_test.log
        lli-17 "$ll_file" >> test_logs_ssa/ssa_execution_test.log 2>&1
        actual_exit_code=$?
        
        # 读取期望的退出代码
        expected_exit_code=$(cat "$out_file")
        
        # 在日志文件中记录结果
        echo "实际退出代码: $actual_exit_code" >> test_logs_ssa/ssa_execution_test.log
        #echo "期望退出代码: $expected_exit_code" >> test_logs_ssa/ssa_execution_test.log
        
        # 比较结果
        if [ "$actual_exit_code" -eq "$expected_exit_code" ]; then
            echo "测试通过" >> test_logs_ssa/ssa_execution_test.log
            ((exec_passed++))
        else
            echo "测试失败" >> test_logs_ssa/ssa_execution_test.log
            ((exec_failed++))
        fi
        
        # 添加分隔线
        echo "----------------------------------------" >> test_logs_ssa/ssa_execution_test.log
    done
}

# 处理两个目录
process_dir "tests/h_functional"
process_dir "tests/functional"
echo "=== 执行测试验证结束 ===" >> test_logs_ssa/ssa_execution_test.log

echo
echo "=== 测试结果 ==="
echo "语法分析测试:"
echo "  通过: $passed"
echo "  失败: $failed"

echo
echo "LLVM IR验证测试 (编译器生成):"
echo "  通过: $true"
echo "  失败: $false"
echo "  详细日志: test_logs_ssa/ssa_validation.log"

echo
echo "执行测试验证 (lli-17 返回值 vs .out文件):"
echo "  通过: $exec_passed"
echo "  失败: $exec_failed"
echo "  详细日志: test_logs_ssa/ssa_execution_test.log"

echo ""
echo "=== 建议的验证步骤 ==="
echo "1. 检查生成的SSA形式IR文件，确认φ函数插入正确"
echo "2. 对比优化前后的IR，验证常量传播和折叠效果"  
echo "3. 确认死代码消除移除了无用指令"
echo "4. 运行汇编代码验证功能正确性"

# 如果有bc命令，显示详细的优化统计
if command -v bc &> /dev/null; then
    echo ""
    echo "详细优化分析完成，数据已保存到 test_results/ssa/ 目录"
else
    echo ""
    echo "注意: 安装bc命令可获得更详细的优化统计"
fi

echo
echo "=== 测试完成 ==="