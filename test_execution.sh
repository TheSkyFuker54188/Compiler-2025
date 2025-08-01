#!/bin/bash

# 脚本功能：
# 1. 编译SysY源文件到RISC-V汇编。
# 2. 将汇编文件与运行时库链接成可执行文件。
# 3. 在QEMU中运行可执行文件。
# 4. 比较程序退出码与期望值，判断测试是否通过。

# RISC-V工具链路径，如果不在系统PATH中，请修改这里
# 例如: export PATH=$PATH:/path/to/riscv/toolchain/bin
# RISC-V QEMU的库路径，根据您的环境修改
QEMU_LD_PREFIX=/usr/riscv64-linux-gnu

# 清理函数
cleanup() {
    echo -e "\n测试被中断，正在清理..."
    pkill -f "./compiler" 2>/dev/null
    pkill -f "qemu-riscv64-static" 2>/dev/null
    rm -f tests/functional/*.o tests/functional/*.exe
    rm -f tests/h_functional/*.o tests/h_functional/*.exe
    echo "清理完成"
    exit 1
}
trap cleanup SIGINT SIGTERM

# 检查qemu-riscv64是否存在
if ! command -v qemu-riscv64-static &> /dev/null; then
    echo "错误: 'qemu-riscv64-static' 未找到。"
    echo "请确保QEMU已安装并且在您的PATH中。"
    exit 1
fi

# 检查riscv64-linux-gnu-gcc是否存在
if ! command -v riscv64-linux-gnu-gcc &> /dev/null; then
    echo "错误: 'riscv64-linux-gnu-gcc' 未找到。"
    echo "请确保RISC-V GCC工具链已安装并且在您的PATH中。"
    exit 1
fi

# 初始化计数器
passed=0
failed=0
total=0

# 测试函数
# 参数1: 测试目录
run_tests_in_dir() {
    local test_dir=$1
    echo "======================================="
    echo "  正在测试目录: $test_dir"
    echo "======================================="

    for sy_file in "$test_dir"/*.sy; do
        if [ ! -f "$sy_file" ]; then continue; fi

        ((total++))
        base_name=$(basename "$sy_file" .sy)
        s_file="$test_dir/$base_name.s"
        exe_file="$test_dir/$base_name.exe"
        out_file="$test_dir/$base_name.out"

        echo -n "测试 $base_name ... "

        # 1. 编译 .sy -> .s (3分钟超时)
        timeout 180 ./compiler "$sy_file" -S -o "$s_file" > /dev/null 2>&1
        compile_result=$?
        if [ $compile_result -eq 124 ]; then
            echo -e "\e[31m编译超时\e[0m"
            ((failed++))
            continue
        elif [ $compile_result -ne 0 ]; then
            echo -e "\e[31m编译失败\e[0m"
            ((failed++))
            continue
        fi

        # 检查期望输出文件是否存在
        if [ ! -f "$out_file" ]; then
            echo -e "\e[33m跳过 (缺少 .out 文件)\e[0m"
            continue
        fi

        # 2. 链接 .s -> .exe (3分钟超时)
        timeout 180 riscv64-linux-gnu-gcc -o "$exe_file" "$s_file" -L./lib -lsysy_riscv
        link_result=$?
        if [ $link_result -eq 124 ]; then
            echo -e "\e[31m链接超时\e[0m"
            ((failed++))
            continue
        elif [ $link_result -ne 0 ]; then
            echo -e "\e[31m链接失败\e[0m"
            ((failed++))
            continue
        fi

        # 3. 运行 .exe，捕获标准输出和退出码 (3分钟超时)
        temp_stdout="temp_stdout_$base_name.log"
        timeout 180 qemu-riscv64-static -L "$QEMU_LD_PREFIX" "$exe_file" > "$temp_stdout"
        actual_exit_code=$?
        if [ $actual_exit_code -eq 124 ]; then
            echo -e "\e[31m运行超时\e[0m"
            ((failed++))
            rm -f "$temp_stdout"
            continue
        fi
        actual_stdout=$(cat "$temp_stdout")
        rm -f "$temp_stdout"

        # 4. 读取期望的标准输出和退出码
        # 约定：.out文件最后一行是退出码，其余是标准输出
        expected_stdout=$(head -n -1 "$out_file" 2>/dev/null | tr -d '\r' || echo "")
        expected_exit_code=$(tail -n 1 "$out_file" | tr -d '\n\r' | xargs)
        
        # 处理实际输出，去除可能的回车符
        actual_stdout=$(echo "$actual_stdout" | tr -d '\r')

        # 5. 比较结果
        stdout_ok=false
        exit_code_ok=false

        # 比较标准输出（去除尾部换行符进行比较）
        expected_stdout_clean=$(echo "$expected_stdout" | sed 's/[[:space:]]*$//')
        actual_stdout_clean=$(echo "$actual_stdout" | sed 's/[[:space:]]*$//')
        if [ "$actual_stdout_clean" == "$expected_stdout_clean" ]; then
            stdout_ok=true
        fi

        # 比较退出码
        if [[ "$actual_exit_code" =~ ^-?[0-9]+$ ]] && [[ "$expected_exit_code" =~ ^-?[0-9]+$ ]] && [ "$actual_exit_code" -eq "$expected_exit_code" ]; then
            exit_code_ok=true
        fi

        # 判断测试是否通过
        if $stdout_ok && $exit_code_ok; then
            echo -e "\e[32m通过\e[0m"
            ((passed++))
        else
            echo -e "\e[31m失败\e[0m"
            if ! $stdout_ok; then
                echo "  - 标准输出不匹配. 期望: '$expected_stdout_clean', 实际: '$actual_stdout_clean'"
                echo "    期望原始: '$expected_stdout'"
                echo "    实际原始: '$actual_stdout'"
            fi
            if ! $exit_code_ok; then
                echo "  - 退出码不匹配. 期望: $expected_exit_code, 实际: $actual_exit_code"
            fi
            ((failed++))
        fi
    done
}

# 运行测试
run_tests_in_dir "tests/functional"
run_tests_in_dir "tests/h_functional"

# 清理生成的文件
rm -f tests/functional/*.s tests/functional/*.exe
rm -f tests/h_functional/*.s tests/h_functional/*.exe

# 打印最终结果
echo "======================================="
echo "  测试结果"
echo "======================================="
echo -e "总计: $total, \e[32m通过: $passed\e[0m, \e[31m失败: $failed\e[0m"
echo "======================================="

if [ $failed -gt 0 ]; then
    exit 1
else
    exit 0
fi
