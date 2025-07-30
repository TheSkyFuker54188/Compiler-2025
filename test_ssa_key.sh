#!/bin/bash

echo "=== SSA优化全文件测试 ==="
echo

# 创建输出目录
mkdir -p test_results/ssa_all_tests

# 初始化日志文件
> test_results/ssa_all_tests/test_summary.log
> test_results/ssa_all_tests/optimization_details.log
> test_results/ssa_all_tests/ssa_statistics.log

echo "SSA优化全文件测试开始时间: $(date)" | tee test_results/ssa_all_tests/test_summary.log

passed=0
failed=0
ssa_success=0
ssa_failed=0

echo "=== 全文件SSA优化测试 ===" | tee -a test_results/ssa_all_tests/test_summary.log

# 测试所有h_functional文件
for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        echo "=== 优化测试: $file ===" >> test_results/ssa_all_tests/optimization_details.log
        
        # 运行编译器并捕获SSA优化输出
        ./compiler --ast --O1 "$file" >> test_results/ssa_all_tests/optimization_details.log 2>&1
        compile_result=$?
        
        # 检查是否有SSA优化输出
        if grep -q "Starting SSA optimizations" test_results/ssa_all_tests/optimization_details.log; then
            if grep -q "SSA optimizations completed" test_results/ssa_all_tests/optimization_details.log; then
                echo "SSA优化成功"
                echo "测试 $file: SSA优化成功" >> test_results/ssa_all_tests/test_summary.log
                ((ssa_success++))
                
                # 提取优化统计
                grep -E "(Eliminated.*instructions|Removed.*instructions)" test_results/ssa_all_tests/optimization_details.log | tail -10 >> test_results/ssa_all_tests/ssa_statistics.log
                echo "--- $file ---" >> test_results/ssa_all_tests/ssa_statistics.log
            else
                echo "SSA优化失败"
                echo "测试 $file: SSA优化失败" >> test_results/ssa_all_tests/test_summary.log
                ((ssa_failed++))
            fi
        else
            echo "SSA未启动"
            echo "测试 $file: SSA未启动" >> test_results/ssa_all_tests/test_summary.log
            ((ssa_failed++))
        fi
        
        if [ $compile_result -eq 0 ]; then
            ((passed++))
        else
            ((failed++))
        fi
        
        echo "----------------------------------------" >> test_results/ssa_all_tests/optimization_details.log
    fi
done

# 测试所有functional文件
for file in tests/functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        echo "=== 优化测试: $file ===" >> test_results/ssa_all_tests/optimization_details.log
        
        # 运行编译器并捕获SSA优化输出
        ./compiler --ast --O1 "$file" >> test_results/ssa_all_tests/optimization_details.log 2>&1
        compile_result=$?
        
        # 检查是否有SSA优化输出
        if grep -q "Starting SSA optimizations" test_results/ssa_all_tests/optimization_details.log; then
            if grep -q "SSA optimizations completed" test_results/ssa_all_tests/optimization_details.log; then
                echo "SSA优化成功"
                echo "测试 $file: SSA优化成功" >> test_results/ssa_all_tests/test_summary.log
                ((ssa_success++))
                
                # 提取优化统计
                grep -E "(Eliminated.*instructions|Removed.*instructions)" test_results/ssa_all_tests/optimization_details.log | tail -10 >> test_results/ssa_all_tests/ssa_statistics.log
                echo "--- $file ---" >> test_results/ssa_all_tests/ssa_statistics.log
            else
                echo "SSA优化失败"
                echo "测试 $file: SSA优化失败" >> test_results/ssa_all_tests/test_summary.log
                ((ssa_failed++))
            fi
        else
            echo "SSA未启动"
            echo "测试 $file: SSA未启动" >> test_results/ssa_all_tests/test_summary.log
            ((ssa_failed++))
        fi
        
        if [ $compile_result -eq 0 ]; then
            ((passed++))
        else
            ((failed++))
        fi
        
        echo "----------------------------------------" >> test_results/ssa_all_tests/optimization_details.log
    fi
done

echo "=== 测试结果 ===" | tee -a test_results/ssa_all_tests/test_summary.log
echo "总文件数: $((ssa_success + ssa_failed))" | tee -a test_results/ssa_all_tests/test_summary.log
echo "SSA优化成功: $ssa_success" | tee -a test_results/ssa_all_tests/test_summary.log
echo "SSA优化失败: $ssa_failed" | tee -a test_results/ssa_all_tests/test_summary.log
echo "完整编译成功: $passed" | tee -a test_results/ssa_all_tests/test_summary.log
echo "完整编译失败: $failed" | tee -a test_results/ssa_all_tests/test_summary.log
echo "测试结束时间: $(date)" | tee -a test_results/ssa_all_tests/test_summary.log

echo
echo "=== 详细报告位置 ==="
echo "  - 测试摘要: test_results/ssa_all_tests/test_summary.log"
echo "  - SSA优化详情: test_results/ssa_all_tests/optimization_details.log"
echo "  - 优化统计: test_results/ssa_all_tests/ssa_statistics.log"
echo
echo "查看SSA优化效果："
echo "  grep 'SSA优化成功' test_results/ssa_all_tests/test_summary.log | wc -l"
echo "  grep 'Eliminated.*instructions' test_results/ssa_all_tests/ssa_statistics.log"
echo "  tail -20 test_results/ssa_all_tests/ssa_statistics.log"
