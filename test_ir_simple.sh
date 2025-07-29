#!/bin/bash

echo "=== 简化版 IR 测试脚本 ==="
echo

# 创建输出目录
mkdir -p test_logs

# 初始化日志文件
> test_logs/ir_validation.log
> test_logs/execution_test.log

# 测试一个指定的文件
test_single_file() {
    local sy_file=$1
    local base_name=$(basename "$sy_file" .sy)
    local dir=$(dirname "$sy_file")
    
    echo "=== 测试文件: $sy_file ==="
    
    # 1. 语法分析测试
    echo "1. 语法分析测试..."
    if ./compiler --ast "$sy_file"; then
        echo "✓ 语法分析通过"
    else
        echo "✗ 语法分析失败"
        return 1
    fi
    
    # 2. LLVM IR验证测试
    local ll_file="$dir/$base_name.ll"
    if [ -f "$ll_file" ]; then
        echo "2. LLVM IR验证测试..."
        if opt -p=verify "$ll_file" -S > /dev/null 2>&1; then
            echo "✓ LLVM IR验证通过"
        else
            echo "✗ LLVM IR验证失败"
            echo "详细错误信息:"
            opt -p=verify "$ll_file" -S 2>&1 | head -10
            return 1
        fi
    else
        echo "⚠ 没有找到对应的 .ll 文件: $ll_file"
    fi
    
    # 3. 执行测试验证
    local out_file="$dir/$base_name.out"
    if [ -f "$out_file" ] && [ -f "$ll_file" ]; then
        echo "3. 执行测试验证..."
        lli-17 "$ll_file" > /dev/null 2>&1
        local actual_exit_code=$?
        local expected_exit_code=$(cat "$out_file")
        
        if [ "$actual_exit_code" -eq "$expected_exit_code" ]; then
            echo "✓ 执行测试通过 (退出代码: $actual_exit_code)"
        else
            echo "✗ 执行测试失败"
            echo "  期望退出代码: $expected_exit_code"
            echo "  实际退出代码: $actual_exit_code"
            return 1
        fi
    else
        if [ ! -f "$out_file" ]; then
            echo "⚠ 没有找到对应的 .out 文件: $out_file"
        fi
    fi
    
    echo "✓ 文件 $sy_file 所有测试通过"
    echo
    return 0
}

# 测试指定数量的文件
test_batch() {
    local dir=$1
    local limit=${2:-5}  # 默认测试5个文件
    local count=0
    local passed=0
    local failed=0
    
    echo "测试目录: $dir (限制: $limit 个文件)"
    echo
    
    for file in "$dir"/*.sy; do
        if [ -f "$file" ] && [ $count -lt $limit ]; then
            if test_single_file "$file"; then
                ((passed++))
            else
                ((failed++))
            fi
            ((count++))
        fi
    done
    
    echo "=== 批量测试结果 ==="
    echo "测试目录: $dir"
    echo "测试文件数: $count"
    echo "通过: $passed"
    echo "失败: $failed"
    echo
}

# 主函数
main() {
    if [ $# -eq 0 ]; then
        echo "用法:"
        echo "  $0 single <文件路径>           # 测试单个文件"
        echo "  $0 batch <目录> [数量]        # 测试指定目录的文件(默认5个)"
        echo "  $0 h_functional [数量]        # 测试 h_functional 目录"
        echo "  $0 functional [数量]          # 测试 functional 目录"
        echo
        echo "示例:"
        echo "  $0 single tests/functional/00_main.sy"
        echo "  $0 batch tests/functional 3"
        echo "  $0 h_functional 2"
        echo "  $0 functional 5"
        exit 1
    fi
    
    case $1 in
        "single")
            if [ $# -lt 2 ]; then
                echo "错误: 请指定要测试的文件"
                exit 1
            fi
            test_single_file "$2"
            ;;
        "batch")
            if [ $# -lt 2 ]; then
                echo "错误: 请指定要测试的目录"
                exit 1
            fi
            test_batch "$2" "$3"
            ;;
        "h_functional")
            test_batch "tests/h_functional" "$2"
            ;;
        "functional")
            test_batch "tests/functional" "$2"
            ;;
        *)
            echo "错误: 未知命令 '$1'"
            exit 1
            ;;
    esac
}

main "$@"
