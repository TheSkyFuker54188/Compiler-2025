#!/bin/bash

echo "=== SYS语言语法分析器批量测试 ==="
echo

passed=0
failed=0

for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        # 添加30秒超时
        if timeout 30s ./compiler "$file" > /dev/null 2>&1; then
            echo "$file 通过"
            ((passed++))
        else
            echo "$file 失败"
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
        if ./compiler "$file"; then
            echo "$file 通过"
            ((passed++))
        else
            echo "$file 失败"
            ((failed++))
        fi
    else
        echo "跳过 $file (文件不存在)"
        ((failed++))
    fi
done

echo
echo "=== 测试结果 ==="
echo "通过: $passed"
echo "失败: $failed"

echo
echo "=== 测试完成 ===" 