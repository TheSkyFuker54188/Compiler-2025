#!/bin/bash

echo "=== SysY编译器端到端测试脚本 ==="
echo "环境: 假设在RISC-V虚拟机中运行"
echo

# 检查编译器是否存在
if [ ! -f "./compiler" ]; then
    echo "❌ 错误: 编译器 'compiler' 不在当前目录"
    echo "请先执行 'make' 命令编译项目"
    exit 1
fi

# 检查RISC-V GCC是否存在
if ! command -v riscv64-linux-gnu-gcc &> /dev/null; then
    echo "❌ 错误: 'riscv64-linux-gnu-gcc' 未找到"
    echo "请确保已安装RISC-V交叉编译工具链"
    exit 1
fi

passed=0
failed=0
skipped=0
total=0

# 创建一个临时目录存放中间文件，避免污染根目录
mkdir -p temp_test_files
cd temp_test_files

# 遍历所有测试用例
for sy_file in ../tests/{functional,h_functional}/*.sy; do
    if [ ! -f "$sy_file" ]; then
        continue
    fi

    ((total++))
    base_name=$(basename "$sy_file" .sy)
    echo -n "测试 $base_name ... "

    # 定义相关文件名
    s_file="${base_name}.s"
    exe_file="${base_name}"
    out_file="${sy_file%.sy}.out"

    # 1. 调用你的编译器: .sy -> .s
    if ! ../compiler "$sy_file" -S -o "$s_file"; then
        echo "失败 (编译器错误)"
        ((failed++))
        continue
    fi

    # 检查.out文件是否存在，不存在则跳过执行对比
    if [ ! -f "$out_file" ]; then
        echo "跳过 (无.out文件)"
        ((skipped++))
        rm -f "$s_file" # 清理汇编文件
        continue
    fi

    # 2. 使用RISC-V GCC编译: .s -> executable
    if ! riscv64-linux-gnu-gcc -static -o "$exe_file" "$s_file" >/dev/null 2>&1; then
        echo "失败 (GCC编译错误)"
        ((failed++))
        rm -f "$s_file"
        continue
    fi

    # 3. 执行并对比结果
    "./$exe_file"
    actual_code=$?
    expected_code=$(cat "$out_file" | tr -d '\n\r ')

    if [ "$actual_code" -eq "$expected_code" ]; then
        echo "通过 (退出码: $actual_code)"
        ((passed++))
    else
        echo "失败 (期望: $expected_code, 实际: $actual_code)"
        ((failed++))
    fi

    # 清理本次测试生成的文件
    rm -f "$s_file" "$exe_file"
done

# 返回根目录并清理临时文件夹
cd ..
rm -r temp_test_files

echo
echo "=== 测试总结 ==="
echo "总计: $total"
echo "✅ 通过: $passed"
echo "❌ 失败: $failed"
echo "⏭️ 跳过: $skipped"
echo