#!/bin/bash

echo "=== SYS语言语法分析器批量测试 ==="
echo

passed=0
failed=0

for file in tests/h_functional/*.sy; do
    if [ -f "$file" ]; then
        echo -n "测试 $file ... "
        if ./sys-compiler "$file"; then
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
        if ./sys-compiler "$file"; then
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

echo
echo "=== 测试结果 ==="
echo "通过: $passed"
echo "失败: $failed"

if [ $failed -eq 0 ]; then
    echo "✅ 所有测试都通过了！"
    success_rate=100
else
    success_rate=$((passed * 100 / total))
    echo "❌ 成功率: ${success_rate}%"
fi

echo
echo "=== 测试完成 ===" 