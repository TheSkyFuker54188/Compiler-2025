#!/bin/bash

echo "=== SYS语言语法分析器批量测试 ==="
echo

# 测试文件列表
TEST_FILES=(
    "tests/h_functional/00_comment2.sy"
    "tests/h_functional/01_multiple_returns.sy"
    "tests/h_functional/02_ret_in_block.sy"
    "tests/h_functional/03_branch.sy"
    "tests/h_functional/04_break_continue.sy"
    "tests/h_functional/05_param_name.sy"
    "tests/h_functional/06_func_name.sy"
    "tests/h_functional/07_arr_init_nd.sy"
    "tests/h_functional/08_global_arr_init.sy"
    "tests/h_functional/14_dp.sy"
    "tests/h_functional/20_sort.sy"
)

passed=0
failed=0
total=${#TEST_FILES[@]}

echo "测试总数: $total"
echo

for file in "${TEST_FILES[@]}"; do
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
echo "总计: $total"
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