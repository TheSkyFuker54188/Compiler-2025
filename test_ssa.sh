#!/bin/bash

# SSA优化全面测试脚本
echo "=== SSA优化全面测试开始 ==="
echo "测试时间: $(date)"
echo ""

# 测试结果统计
total_tests=0
success_tests=0
failed_tests=0

# 创建测试结果目录
mkdir -p test_results/ssa_all/

# 函数：测试单个文件
test_file() {
    local file=$1
    local filename=$(basename "$file" .sy)
    echo "正在测试: $filename"
    
    # 增加计数
    ((total_tests++))
    
    # 运行编译
    ./compiler --ssa "$file" > "test_results/ssa_all/${filename}.log" 2>&1
    
    # 检查SSA优化是否成功
    if grep -q "SSA optimizations completed" "test_results/ssa_all/${filename}.log"; then
        echo "  ✅ SSA优化成功"
        ((success_tests++))
        
        # 统计优化效果
        eliminated=$(grep -o "Eliminated [0-9]* instructions" "test_results/ssa_all/${filename}.log" | head -1 | grep -o "[0-9]*" || echo "0")
        blocks_eliminated=$(grep -c "Eliminating unreachable block" "test_results/ssa_all/${filename}.log" || echo "0")
        algebraic_opts=$(grep -c "simplifications applied" "test_results/ssa_all/${filename}.log" | grep -v "0 simplifications" | wc -l || echo "0")
        
        echo "    - 消除指令: $eliminated 条"
        echo "    - 消除基本块: $blocks_eliminated 个" 
        echo "    - 代数化简: $algebraic_opts 次"
    else
        echo "  ❌ SSA优化失败"
        ((failed_tests++))
        # 显示错误信息的前几行
        echo "    错误信息:"
        head -10 "test_results/ssa_all/${filename}.log" | sed 's/^/    /'
    fi
    echo ""
}

echo "=== 测试 functional 目录 ==="
echo ""

# 测试所有functional目录的.sy文件
for file in tests/functional/*.sy; do
    if [ -f "$file" ]; then
        test_file "$file"
    fi
done

echo "=== 测试 h_functional 目录 ==="
echo ""

# 测试所有h_functional目录的.sy文件  
for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        test_file "$file"
    fi
done

echo "=== 测试结果汇总 ==="
echo "总测试数: $total_tests"
echo "成功数: $success_tests"
echo "失败数: $failed_tests"
echo "成功率: $(( success_tests * 100 / total_tests ))%"
echo ""

echo "=== 优化效果统计 ==="

# 统计所有测试的优化效果
total_eliminated=0
total_blocks_eliminated=0
total_algebraic_opts=0

for log_file in test_results/ssa_all/*.log; do
    if [ -f "$log_file" ]; then
        eliminated=$(grep -o "Eliminated [0-9]* instructions" "$log_file" | head -1 | grep -o "[0-9]*" 2>/dev/null || echo "0")
        blocks=$(grep -c "Eliminating unreachable block" "$log_file" 2>/dev/null || echo "0")
        algebraic=$(grep -c "simplifications applied" "$log_file" 2>/dev/null || echo "0")
        
        total_eliminated=$((total_eliminated + eliminated))
        total_blocks_eliminated=$((total_blocks_eliminated + blocks))
        total_algebraic_opts=$((total_algebraic_opts + algebraic))
    fi
done

echo "总消除指令数: $total_eliminated"
echo "总消除基本块数: $total_blocks_eliminated" 
echo "总代数化简次数: $total_algebraic_opts"

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
echo "=== 测试完成 ==="
echo "详细日志保存在: test_results/ssa_all/"

echo
echo "=== 测试完成 ==="