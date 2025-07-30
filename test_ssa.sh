#!/bin/bash

echo "=== SSA优化批量测试 ==="
echo

# 创建输出目录
mkdir -p test_logs_ssa

# 初始化日志文件
> test_logs_ssa/ssa_validation.log
> test_logs_ssa/ssa_execution_test.log
> test_logs_ssa/ssa_optimization_details.log
> test_logs_ssa/test_summary.log

# 记录测试开始时间
echo "SSA优化测试开始时间: $(date)" | tee test_logs_ssa/test_summary.log

passed=0
failed=0

echo "=== 编译和SSA优化测试 ===" | tee -a test_logs_ssa/test_summary.log

for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        echo "=== 测试文件: $file ===" >> test_logs_ssa/ssa_optimization_details.log
        if ./compiler --ast --O1 "$file" >> test_logs_ssa/ssa_optimization_details.log 2>&1; then
            echo "通过"
            echo "测试 $file: 通过" >> test_logs_ssa/test_summary.log
            ((passed++))
        else
            echo "失败"
            echo "测试 $file: 失败" >> test_logs_ssa/test_summary.log
            ((failed++))
        fi
        echo "----------------------------------------" >> test_logs_ssa/ssa_optimization_details.log
    else
        echo "跳过 $file (文件不存在)"
        echo "跳过 $file (文件不存在)" >> test_logs_ssa/test_summary.log
        ((failed++))
    fi
done

for file in tests/functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        echo "=== 测试文件: $file ===" >> test_logs_ssa/ssa_optimization_details.log
        if ./compiler --ast --O1 "$file" >> test_logs_ssa/ssa_optimization_details.log 2>&1; then
            echo "通过"
            echo "测试 $file: 通过" >> test_logs_ssa/test_summary.log
            ((passed++))
        else
            echo "失败"
            echo "测试 $file: 失败" >> test_logs_ssa/test_summary.log
            ((failed++))
        fi
        echo "----------------------------------------" >> test_logs_ssa/ssa_optimization_details.log
    else
        echo "跳过 $file (文件不存在)"
        echo "跳过 $file (文件不存在)" >> test_logs_ssa/test_summary.log
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

echo
echo "=== 测试完成 ==="
echo "测试结束时间: $(date)"
echo

# 将总结信息写入日志
echo "=== 最终测试结果 ===" >> test_logs_ssa/test_summary.log
echo "语法分析测试: 通过 $passed, 失败 $failed" >> test_logs_ssa/test_summary.log
echo "LLVM IR验证测试: 通过 $true, 失败 $false" >> test_logs_ssa/test_summary.log
echo "执行测试验证: 通过 $exec_passed, 失败 $exec_failed" >> test_logs_ssa/test_summary.log
echo "测试结束时间: $(date)" >> test_logs_ssa/test_summary.log

echo "=== 详细日志文件 ==="
echo "  - SSA优化详细输出: test_logs_ssa/ssa_optimization_details.log"
echo "  - LLVM IR验证日志: test_logs_ssa/ssa_validation.log" 
echo "  - 执行测试日志: test_logs_ssa/ssa_execution_test.log"
echo "  - 测试结果摘要: test_logs_ssa/test_summary.log"