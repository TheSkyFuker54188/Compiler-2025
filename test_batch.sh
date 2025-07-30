#!/bin/bash

# 清理函数，处理中断信号
cleanup() {
    echo ""
    echo "测试被中断，正在清理..."
    # 杀死可能还在运行的编译器进程
    pkill -f "./compiler" 2>/dev/null
    echo "清理完成"
    exit 1
}

# 捕获中断信号
trap cleanup SIGINT SIGTERM

echo "=== SYS语言语法分析器批量测试 ==="
echo "超时设置: ${TIMEOUT_SECONDS:-30} 秒"
echo

passed=0
failed=0
timeout_count=0
TIMEOUT_SECONDS=30  # 设置超时时间为30秒

for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        if timeout $TIMEOUT_SECONDS ./compiler "$file" -S -o "${file%.sy}.s"; then
            echo "$file 通过"
            ((passed++))
        else
            exit_code=$?
            if [ $exit_code -eq 124 ]; then
                echo "$file 超时 (>${TIMEOUT_SECONDS}s)"
                ((timeout_count++))
            else
                echo "$file 失败"
            fi
            ((failed++))
        fi
    else
        echo "跳过 $file (文件不存在)"
        ((failed++))
    fi
done

for file in tests/h_functional/*.c; do
    if [ -f "$file" ]; then
        echo -n "编译标准 $file ... "
        if timeout $TIMEOUT_SECONDS riscv64-unknown-elf-gcc "$file" -S -o "${file%.c}_standard.s"; then
            echo "完成"
        else
            echo "失败/超时"
        fi
    else
        echo "跳过 $file (文件不存在)"
    fi
done

for file in tests/functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        if timeout $TIMEOUT_SECONDS ./compiler "$file" -S -o "${file%.sy}.s"; then
            echo "$file 通过"
            ((passed++))
        else
            exit_code=$?
            if [ $exit_code -eq 124 ]; then
                echo "$file 超时 (>${TIMEOUT_SECONDS}s)"
                ((timeout_count++))
            else
                echo "$file 失败"
            fi
            ((failed++))
        fi
    else
        echo "跳过 $file (文件不存在)"
        ((failed++))
    fi
done

for file in tests/functional/*.c; do
    if [ -f "$file" ]; then
        echo -n "编译标准 $file ... "
        if timeout $TIMEOUT_SECONDS riscv64-unknown-elf-gcc "$file" -S -o "${file%.c}_standard.s"; then
            echo "完成"
        else
            echo "失败/超时"
        fi
    else
        echo "跳过 $file (文件不存在)"
    fi
done

echo
echo "=== 测试结果 ==="
echo "通过: $passed"
echo "失败: $failed"
echo "超时: $timeout_count"
if [ $timeout_count -gt 0 ]; then
    echo "警告: 有 $timeout_count 个测试用例超时"
fi

echo
echo "=== 测试完成 ===" 