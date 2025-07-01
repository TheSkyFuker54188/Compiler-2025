#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "include/ast.h"
#include "include/astprinter.h"
#include "parser/parser.tab.h"

// 外部变量声明
extern std::unique_ptr<CompUnit> root;
extern int yyparse();
extern FILE* yyin;
extern int line_number;

// 全局变量定义
int line_number = 1;
int col_number = 1;
int cur_col_number = 1;

/**
 * 解析单个SYS语言文件并打印AST
 */
bool parseAndPrintAST(const std::string& filename, bool verbose = true) {
    // 重置全局变量
    line_number = 1;
    col_number = 1;
    root.reset();
    
    // 打开文件
    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    if (verbose) {
        std::cout << "=== Parsing " << filename << " ===" << std::endl;
    }
    
    // 执行语法分析
    int result = yyparse();
    fclose(yyin);
    
    if (result != 0) {
        std::cerr << "Parse failed!" << std::endl;
        return false;
    }
    
    if (!root) {
        std::cerr << "No AST generated!" << std::endl;
        return false;
    }
    
    if (verbose) {
        std::cout << "Parse successful!" << std::endl;
        std::cout << "\n=== AST Structure ===" << std::endl;
    }
    
    // 创建AST打印器并打印AST
    ASTPrinter printer;
    printer.setShowTypes(true);
    printer.setShowLocations(false);
    root->accept(printer);
    
    return true;
}

/**
 * 显示使用帮助
 */
void showUsage(const char* program_name) {
    std::cout << "SYS Language Compiler - AST Parser" << std::endl;
    std::cout << "Usage: " << program_name << " [options] <file.sy>" << std::endl;
    std::cout << "\nOptions:" << std::endl;
    std::cout << "  -h, --help     Show this help message" << std::endl;
    std::cout << "  -q, --quiet    Quiet mode (only show AST)" << std::endl;
    std::cout << "  -v, --version  Show version information" << std::endl;
    std::cout << "\nExample:" << std::endl;
    std::cout << "  " << program_name << " program.sy" << std::endl;
    std::cout << "  " << program_name << " -q test.sy" << std::endl;
}

/**
 * 显示版本信息
 */
void showVersion() {
    std::cout << "SYS Language Compiler v1.0" << std::endl;
    std::cout << "AST Parser and Printer" << std::endl;
    std::cout << "Built with modern C++17" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showUsage(argv[0]);
        return 1;
    }
    
    bool quiet_mode = false;
    std::string filename;
    
    // 解析命令行参数
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            showUsage(argv[0]);
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            showVersion();
            return 0;
        } else if (arg == "-q" || arg == "--quiet") {
            quiet_mode = true;
        } else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << std::endl;
            showUsage(argv[0]);
            return 1;
        } else {
            if (filename.empty()) {
                filename = arg;
            } else {
                std::cerr << "Multiple input files not supported" << std::endl;
                return 1;
            }
        }
    }
    
    if (filename.empty()) {
        std::cerr << "No input file specified" << std::endl;
        showUsage(argv[0]);
        return 1;
    }
    
    // 解析并打印AST
    bool success = parseAndPrintAST(filename, !quiet_mode);
    
    return success ? 0 : 1;
} 