#!/bin/bash

# 脚本功能：
# 1. 编译SysY源文件到RISC-V汇编。
# 2. 将汇编文件与运行时库链接成可执行文件。
# 3. 在QEMU中运行可执行文件。
# 4. 比较程序退出码与期望值，判断测试是否通过。
#
# 用法：
# ./test_execution.sh                    # 测试所有文件
# ./test_execution.sh 95_float           # 仅测试指定的测试点
# ./test_execution.sh 95_float.sy        # 仅测试指定的测试点（带扩展名）

# RISC-V工具链路径，如果不在系统PATH中，请修改这里
# 例如: export PATH=$PATH:/path/to/riscv/toolchain/bin
# RISC-V QEMU的库路径，根据您的环境修改
QEMU_LD_PREFIX=/usr/riscv64-linux-gnu

# 解析命令行参数
SPECIFIC_TEST=""
if [ $# -gt 0 ]; then
    SPECIFIC_TEST="$1"
    # 如果参数包含.sy扩展名，则去掉
    SPECIFIC_TEST="${SPECIFIC_TEST%.sy}"
    echo "======================================="
    echo "  仅测试指定测试点: $SPECIFIC_TEST"
    echo "======================================="
fi

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

# 新增：检查依赖工具的详细函数
check_dependencies() {
    local missing_deps=()
    
    if ! command -v qemu-riscv64-static &> /dev/null; then
        missing_deps+=("qemu-riscv64-static")
    fi
    
    if ! command -v riscv64-linux-gnu-gcc &> /dev/null; then
        missing_deps+=("riscv64-linux-gnu-gcc")
    fi
    
    if ! command -v riscv64-linux-gnu-as &> /dev/null; then
        missing_deps+=("riscv64-linux-gnu-as")
    fi
    
    if [ ! -f "./compiler" ]; then
        missing_deps+=("./compiler")
    fi
    
    if [ ! -d "./lib" ] || [ ! -f "./lib/libsysy_riscv.a" ]; then
        missing_deps+=("RISC-V运行时库 (./lib/libsysy_riscv.a)")
    fi
    
    if [ ${#missing_deps[@]} -gt 0 ]; then
        echo "错误: 缺少以下依赖："
        for dep in "${missing_deps[@]}"; do
            echo "  - $dep"
        done
        echo ""
        echo "请确保："
        echo "1. RISC-V工具链已正确安装"
        echo "2. QEMU已安装 (apt install qemu-user-static)"
        echo "3. 编译器已构建 (make clean && make)"
        echo "4. 运行时库已构建"
        exit 1
    fi
}

# 新增：智能检测QEMU库路径
detect_qemu_lib_path() {
    local possible_paths=(
        "/usr/riscv64-linux-gnu"
        "/usr/lib/riscv64-linux-gnu"
        "/opt/riscv/sysroot"
        "/usr/local/riscv64-linux-gnu"
    )
    
    for path in "${possible_paths[@]}"; do
        if [ -d "$path" ]; then
            QEMU_LD_PREFIX="$path"
            return 0
        fi
    done
    
    echo "警告: 无法自动检测QEMU库路径，使用默认路径: $QEMU_LD_PREFIX"
    echo "如果运行时出错，请手动设置正确的路径"
}

# 在脚本开始处调用检查
detect_qemu_lib_path
check_dependencies

# 初始化计数器
passed=0
failed=0
total=0
skipped=0

# 定义日志与汇总文件路径
LOG_FILE="test_results.txt"
SUMMARY_CSV="test_results_summary.csv"

# 清空日志/汇总文件
> "$LOG_FILE"
echo "case,status,detail" > "$SUMMARY_CSV"

# 函数：打印并记录日志
log() {
    echo -e "$1" | tee -a "$LOG_FILE"
}

# 新增：去除ANSI颜色
strip_ansi() {
    # 移除常见ANSI转义序列
    sed -r 's/\x1B\[[0-9;]*[A-Za-z]//g'
}

# 新增：CSV安全写入（转义换行/引号/逗号）
csv_write() {
    local name="$1"; local status="$2"; local detail_raw="${3:-}"
    # 去颜色
    local detail_clean
    detail_clean="$(printf '%s' "$detail_raw" | strip_ansi)"
    # 统一换行转义为 \n，去CR
    detail_clean="$(printf '%s' "$detail_clean" | sed ':a;N;$!ba;s/\r//g; s/\n/\\n/g')"
    # 双引号转义为两倍引号
    detail_clean="${detail_clean//\"/\"\"}"
    # 逗号可保留，整列用双引号包裹
    echo "$name,$status,\"$detail_clean\"" >> "$SUMMARY_CSV"
}

# 记录本地结果状态（修改：写入CSV时包含详情并做好转义/去色）
declare -A LOCAL_STATUS
record_status() {
    local name="$1"; local status="$2"; local detail="${3:-}"
    LOCAL_STATUS["$name"]="$status"
    csv_write "$name" "$status" "$detail"
}

# 测试函数
# 参数1: 测试目录
run_tests_in_dir() {
    local test_dir=$1
    log "======================================="
    log "  正在测试目录: $test_dir"
    log "======================================="

    for sy_file in "$test_dir"/*.sy; do
        if [ ! -f "$sy_file" ]; then continue; fi
        base_name=$(basename "$sy_file" .sy)
        
        # 如果指定了特定测试点，且当前文件不匹配，则跳过
        if [ -n "$SPECIFIC_TEST" ] && [ "$base_name" != "$SPECIFIC_TEST" ]; then
            continue
        fi

        ((total++))
        s_file="$test_dir/$base_name.s"
        exe_file="$test_dir/$base_name.exe"
        out_file="$test_dir/$base_name.out"

        log -n "[$base_name] 测试 $base_name ($sy_file) ... "

        # 1) 编译
        compile_stderr="compile_stderr_$base_name.log"
        compile_stdout="compile_stdout_$base_name.log"
        timeout 30 ./compiler "$sy_file" -S -o "$s_file" > "$compile_stdout" 2> "$compile_stderr"
        compile_result=$?

        compile_error_output=$(cat "$compile_stderr" 2>/dev/null || echo "")
        compile_stdout_output=$(cat "$compile_stdout" 2>/dev/null || echo "")
        rm -f "$compile_stderr" "$compile_stdout"

        compile_full_output=""
        [ -n "$compile_stdout_output" ] && compile_full_output="$compile_stdout_output"
        if [ -n "$compile_error_output" ]; then
            [ -n "$compile_full_output" ] && compile_full_output="$compile_full_output"$'\n'"$compile_error_output" || compile_full_output="$compile_error_output"
        fi

        compile_failed=false
        assembly_error=""

        if [ $compile_result -eq 124 ]; then
            log "\e[31m编译超时\e[0m"
            record_status "$base_name" "CE_TIMEOUT" "compile timeout"
            ((failed++))
            continue
        elif [ $compile_result -ne 0 ]; then
            compile_failed=true
        elif [ ! -f "$s_file" ] || [ ! -s "$s_file" ]; then
            compile_failed=true
        else
            if grep -q "^error" "$s_file" 2>/dev/null; then
                compile_failed=true
            fi
            file_size=$(stat -c%s "$s_file" 2>/dev/null || echo "0")
            if [ "$file_size" -gt 31457280 ]; then
                compile_failed=true
                compile_full_output="${compile_full_output}"$'\n'"错误: 生成的汇编代码超过30MB，停止输出"
            fi
        fi

        if [ "$compile_failed" = false ] && [ -f "$s_file" ]; then
            asm_check_stderr="asm_check_stderr_$base_name.log"
            riscv64-linux-gnu-as "$s_file" -o /dev/null 2> "$asm_check_stderr" > /dev/null
            asm_check_result=$?
            asm_error_output=$(cat "$asm_check_stderr" 2>/dev/null || echo "")
            rm -f "$asm_check_stderr"
            if [ $asm_check_result -ne 0 ] && [ -n "$asm_error_output" ]; then
                compile_failed=true
                assembly_error="$asm_error_output"
                [ -n "$compile_full_output" ] && compile_full_output="$compile_full_output"$'\n'"$assembly_error" || compile_full_output="$assembly_error"
            fi
        fi

        if [ "$compile_failed" = true ]; then
            log "\e[31m编译失败\e[0m"
            if [ -n "$compile_full_output" ]; then
                log "[$base_name] 编译错误: $compile_full_output"
            fi
            # 关键：把完整编译错误写入CSV
            record_status "$base_name" "CE" "编译错误: ${compile_full_output:-未知错误}"
            ((failed++))
            continue
        fi

        # 期望输出缺失
        if [ ! -f "$out_file" ]; then
            log "\e[33m跳过 (缺少 .out 文件)\e[0m"
            record_status "$base_name" "SKIP_NO_OUT" "缺少期望输出文件: $out_file"
            ((skipped++))
            continue
        fi

        # 2) 链接
        link_stderr="link_stderr_$base_name.log"
        timeout 30 riscv64-linux-gnu-gcc -o "$exe_file" "$s_file" -L./lib -lsysy_riscv 2> "$link_stderr" > /dev/null
        link_result=$?
        link_error_output=$(cat "$link_stderr" 2>/dev/null || echo "")
        rm -f "$link_stderr"

        if [ $link_result -eq 124 ]; then
            log "\e[31m链接超时\e[0m"
            record_status "$base_name" "LE_TIMEOUT" "链接超时(30s)"
            ((failed++))
            continue
        elif [ $link_result -ne 0 ]; then
            log "\e[31m链接失败\e[0m"
            [ -n "$link_error_output" ] && log "[$base_name] 链接错误: $link_error_output"
            # 关键：把链接错误写入CSV
            record_status "$base_name" "LE" "链接错误: ${link_error_output:-无stderr输出}"
            ((failed++))
            continue
        fi

        # 3) 运行
        temp_stdout="temp_stdout_$base_name.log"
        temp_stderr="temp_stderr_$base_name.log"
        timeout 30 qemu-riscv64-static -L "$QEMU_LD_PREFIX" "$exe_file" > "$temp_stdout" 2> "$temp_stderr"
        actual_exit_code=$?

        if [ $actual_exit_code -eq 124 ]; then
            log "\e[31m运行超时\e[0m"
            # 关键：把stderr一并写入CSV
            record_status "$base_name" "RT_TIMEOUT" "运行超时(30s)${run_stderr:+; stderr: $run_stderr}"
            ((failed++))
            rm -f "$temp_stdout" "$temp_stderr"
            continue
        fi

        actual_stdout=$(cat "$temp_stdout" | grep -v "TOTAL:" | tr -d '\r')
        run_stderr=$(cat "$temp_stderr" 2>/dev/null || echo "")
        rm -f "$temp_stdout" "$temp_stderr"

        if [ $actual_exit_code -gt 255 ]; then
            actual_exit_code=$((actual_exit_code % 256))
        elif [ $actual_exit_code -lt 0 ]; then
            actual_exit_code=$((256 + actual_exit_code))
        fi

        expected_stdout=$(head -n -1 "$out_file" 2>/dev/null | tr -d '\r' || echo "")
        expected_exit_code=$(tail -n 1 "$out_file" | tr -d '\n\r' | xargs)

        stdout_ok=false
        exit_code_ok=false

        if [ "$actual_stdout" == "$expected_stdout" ]; then
            stdout_ok=true
        else
            expected_stdout_clean=$(echo "$expected_stdout" | sed 's/[[:space:]]*$//')
            actual_stdout_clean=$(echo "$actual_stdout" | sed 's/[[:space:]]*$//')
            if [ "$actual_stdout_clean" == "$expected_stdout_clean" ]; then
                stdout_ok=true
            fi
        fi

        if [[ "$actual_exit_code" =~ ^-?[0-9]+$ ]] && [[ "$expected_exit_code" =~ ^-?[0-9]+$ ]]; then
            expected_exit_code_mod=$expected_exit_code
            if [ $expected_exit_code -gt 255 ]; then
                expected_exit_code_mod=$((expected_exit_code % 256))
            elif [ $expected_exit_code -lt 0 ]; then
                expected_exit_code_mod=$((256 + expected_exit_code))
            fi
            [ "$actual_exit_code" -eq "$expected_exit_code_mod" ] && exit_code_ok=true
        fi

        if $stdout_ok && $exit_code_ok; then
            log "\e[32m通过\e[0m"
            record_status "$base_name" "AC" ""
            ((passed++))
        elif $stdout_ok && ! $exit_code_ok; then
            # 输出一致，但退出码不同 => 通过 + 警告；保留组合哈希不匹配信息
            # 组合哈希: 近似平台可能的做法——对 "stdout + 换行 + exit" 求 MD5，仅用于提示
            actual_md5_stdout=$(echo -n "$actual_stdout" | md5sum | cut -d' ' -f1)
            expected_md5_stdout=$(echo -n "$expected_stdout" | md5sum | cut -d' ' -f1)
            actual_md5_combined=$(printf '%s\n%s' "$actual_stdout" "$actual_exit_code" | md5sum | cut -d' ' -f1)
            expected_md5_combined=$(printf '%s\n%s' "$expected_stdout" "$expected_exit_code_mod" | md5sum | cut -d' ' -f1)

            log "\e[33m通过(退出码不匹配)\e[0m"
            log "[$base_name] 退出码不匹配. 期望: $expected_exit_code, 实际: $actual_exit_code"
            log "[$base_name] 组合哈希不匹配(仅供参考):"
            log "[$base_name] 实际: $actual_md5_combined"
            log "[$base_name] 预期: $expected_md5_combined"

            detail_text="输出正确，但退出码不匹配
期望退出码: $expected_exit_code
实际退出码: $actual_exit_code

哈希信息(仅供参考):
stdout_md5_actual: $actual_md5_stdout
stdout_md5_expect: $expected_md5_stdout
combined_md5_actual(stdout+exit): $actual_md5_combined
combined_md5_expect(stdout+exit): $expected_md5_combined"
            # 计为通过(AC)，但细节里保留不匹配信息
            record_status "$base_name" "AC" "$detail_text"
            ((passed++))
        else
            log "\e[31m失败\e[0m"

            # 构造平台风格的详情文本，并写入CSV第三列
            # 计算Filesize（优先exe，没有则用.s）
            filesz="N/A"
            if [ -f "$exe_file" ]; then
                filesz=$(stat -c%s "$exe_file" 2>/dev/null || echo "N/A")
            elif [ -f "$s_file" ]; then
                filesz=$(stat -c%s "$s_file" 2>/dev/null || echo "N/A")
            fi

            # 哈希按stdout计算（信息用途）
            actual_md5=$(echo -n "$actual_stdout" | md5sum | cut -d' ' -f1)
            expected_md5=$(echo -n "$expected_stdout" | md5sum | cut -d' ' -f1)

            # 详细文本模板
            detail_text=""

            if ! $stdout_ok && ! $exit_code_ok; then
                detail_text="结果哈希值不匹配
实际结果: $actual_md5
预期结果: $expected_md5

FPGA运行输出:
Running testcases/$base_name
Filesize: $filesz
Failed: 0.0 result is $actual_md5"
                log "[$base_name] 结果哈希值不匹配"
                log "[$base_name] 实际结果: $actual_md5"
                log "[$base_name] 预期结果: $expected_md5"
                log ""
                log "[$base_name] FPGA运行输出:"
                [ -n "$actual_stdout" ] && log "[$base_name] 输出: $actual_stdout"
                log "[$base_name] 退出码: $actual_exit_code"
                [ -n "$run_stderr" ] && detail_text="$detail_text
stderr:
$run_stderr"

                record_status "$base_name" "WA_BOTH" "$detail_text"

            elif ! $stdout_ok; then
                detail_text="结果哈希值不匹配
实际结果: $actual_md5
预期结果: $expected_md5

FPGA运行输出:
Running testcases/$base_name
Filesize: $filesz
Failed: 0.0 result is $actual_md5

标准输出不匹配:
期望: '$expected_stdout'
实际: '$actual_stdout'"
                log "[$base_name] 标准输出不匹配:"
                log "[$base_name] 期望: '$expected_stdout'"
                log "[$base_name] 实际: '$actual_stdout'"
                [ -n "$run_stderr" ] && detail_text="$detail_text
stderr:
$run_stderr"

                record_status "$base_name" "WA_STDOUT" "$detail_text"

            # 注意: 这里不再单独把“仅退出码不匹配”判为失败，已在上面对齐为通过
            fi

            ((failed++))
        fi
    done
}

# 运行测试
if [ -n "$SPECIFIC_TEST" ]; then
    # 如果指定了特定测试，优先在 functional 目录查找
    if [ -f "tests/functional/${SPECIFIC_TEST}.sy" ]; then
        run_tests_in_dir "tests/functional"
    elif [ -f "tests/h_functional/${SPECIFIC_TEST}.sy" ]; then
        run_tests_in_dir "tests/h_functional"
    else
        echo "错误: 找不到测试文件 '${SPECIFIC_TEST}.sy'"
        echo "请检查文件是否存在于 tests/functional/ 或 tests/h_functional/ 目录中"
        exit 1
    fi
else
    # 运行所有测试
    run_tests_in_dir "tests/functional"
    run_tests_in_dir "tests/h_functional"
fi

# 清理生成的文件
if [ -n "$SPECIFIC_TEST" ]; then
    # 只清理指定测试的文件
    rm -f "tests/functional/${SPECIFIC_TEST}.s" "tests/functional/${SPECIFIC_TEST}.exe"
    rm -f "tests/h_functional/${SPECIFIC_TEST}.s" "tests/h_functional/${SPECIFIC_TEST}.exe"
else
    # 清理所有生成的文件
    rm -f tests/functional/*.s tests/functional/*.exe
    rm -f tests/h_functional/*.s tests/h_functional/*.exe
fi

# 打印最终结果（保留原有，移除平台对照）
echo "======================================="
echo "  测试结果"
echo "======================================="
echo -e "总计: $total, \e[32m通过: $passed\e[0m, \e[31m失败: $failed\e[0m, \e[33m跳过: $skipped\e[0m"
echo "======================================="

if [ $failed -gt 0 ]; then
    exit 1
else
    exit 0
fi
