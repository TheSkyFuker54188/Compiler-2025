#include "include/ast.h"
#include "include/astprinter.h"
#include "include/block.h"
#include "include/semantic.h"
#include "parser/parser.tab.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
// #include "include/instruction.h"

// 外部变量声明
extern std::unique_ptr<CompUnit> root;
extern int yyparse();
extern FILE *yyin;
extern int line_number;

// 全局变量定义
int line_number = 1;
int col_number = 1;
int cur_col_number = 1;

/**
 * 编译单个SYS语言文件：词法分析、语法分析、语义分析
 */
bool compileFile(const std::string &filename, bool verbose = true,
                 bool enable_semantic = true, bool print_ast = false,
                 bool generate_ir = true) {
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
    std::cout << "=== 编译 " << filename << " ===" << std::endl;
  }

  // 第一阶段：执行语法分析
  if (verbose) {
    std::cout << "阶段1: 词法和语法分析..." << std::endl;
  }

  int result = yyparse();
  fclose(yyin);

  if (result != 0) {
    std::cerr << "语法分析失败!" << std::endl;
    return false;
  }

  if (!root) {
    std::cerr << "没有生成AST!" << std::endl;
    return false;
  }

  if (verbose) {
    std::cout << "语法分析成功!" << std::endl;
  }

  // 第二阶段：语义分析
  bool semantic_success = true;
  if (enable_semantic) {
    if (verbose) {
      std::cout << "阶段2: 语义分析..." << std::endl;
    }

    SemanticAnalyzer analyzer;
    semantic_success = analyzer.analyze(*root);

    if (semantic_success) {
      if (verbose) {
        std::cout << "语义分析成功!" << std::endl;
      }
    } else {
      std::cerr << "语义分析失败!" << std::endl;
      analyzer.printErrors();
    }
  }

  // 第三阶段：打印AST（可选）
  if (print_ast) {
    std::string AST = filename.substr(0, filename.find_last_of('.')) + ".ast";
    std::ofstream ast_file(AST);
    ASTPrinter printer(ast_file);
    printer.setShowTypes(true);
    printer.setShowLocations(false);
    root->accept(printer);
  }

  // 第四阶段：生成中间代码
  if (generate_ir && semantic_success) {
    if (verbose) {
      std::cout << "阶段3: 中间代码生成..." << std::endl;
    }

    IRgenerator irgen;
    root->accept(irgen);

    // 输出生成的IR到文件
    std::string ir_filename =
        filename.substr(0, filename.find_last_of('.')) + ".ll";
    std::ofstream ir_file(ir_filename);
    if (ir_file.is_open()) {
      irgen.getLLVMIR().printIR(ir_file);
      ir_file.close();
      if (verbose) {
        std::cout << "中间代码已生成到 " << ir_filename << std::endl;
      }
    } else {
      std::cerr << "无法创建IR文件 " << ir_filename << std::endl;
      return false;
    }
  }

  return semantic_success;
}

/**
 * 显示使用帮助
 */
void showUsage(const char *program_name) {
  std::cout << "SYS Language Compiler - 语义分析器" << std::endl;
  std::cout << "Usage: " << program_name << " [options] <file.sy>" << std::endl;
  std::cout << "\nOptions:" << std::endl;
  std::cout << "  -h, --help       显示帮助信息" << std::endl;
  std::cout << "  -q, --quiet      静默模式（只显示错误）" << std::endl;
  std::cout << "  --ast            打印AST结构" << std::endl;
  std::cout << "  --no-semantic    跳过语义分析" << std::endl;
  std::cout << "\nExample:" << std::endl;
  std::cout << "  " << program_name << " program.sy           # 完整编译"
            << std::endl;
  std::cout << "  " << program_name << " --ast test.sy        # 编译并显示AST"
            << std::endl;
  std::cout << "  " << program_name << " --no-semantic test.sy # 只进行语法分析"
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    showUsage(argv[0]);
    return 1;
  }

  bool quiet_mode = false;
  bool enable_semantic = true;
  bool print_ast = false;
  bool generate_ir = true;
  std::string filename;

  // 解析命令行参数
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      showUsage(argv[0]);
      return 0;
    } else if (arg == "-q" || arg == "--quiet") {
      quiet_mode = true;
    } else if (arg == "--ast") {
      print_ast = true;
    } else if (arg == "--no-semantic") {
      enable_semantic = false;
    } else if (arg[0] == '-') {
      std::cerr << "未知选项: " << arg << std::endl;
      showUsage(argv[0]);
      return 1;
    } else {
      if (filename.empty()) {
        filename = arg;
      } else {
        std::cerr << "不支持多个输入文件" << std::endl;
        return 1;
      }
    }
  }

  if (filename.empty()) {
    std::cerr << "没有指定输入文件" << std::endl;
    showUsage(argv[0]);
    return 1;
  }

  // 编译文件
  bool success = compileFile(filename, !quiet_mode, enable_semantic, print_ast,
                             generate_ir);

  return success ? 0 : 1;
}