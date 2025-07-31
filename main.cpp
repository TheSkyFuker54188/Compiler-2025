#include "include/ast.h"
#include "include/astprinter.h"
#include "include/block.h"
#include "include/irtranslater.h"
#include "include/register_allocator.h"
#include "include/semantic.h"
#include "include/ssa.h"
#include "parser/parser.tab.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <string>

// 外部变量声明
extern std::unique_ptr<CompUnit> root;
extern int yyparse();
extern FILE *yyin;

// 全局变量定义
int line_number = 1;
int col_number = 1;
int cur_col_number = 1;

std::map<std::string, int> function_name_to_maxreg;

/**
 * 编译单个SYS语言文件：词法分析、语法分析、语义分析
 */
bool compileFile(const std::string &filename, bool verbose = true,
                 bool enable_semantic = true, bool print_ast = false,
                 bool generate_ir = true, bool generate_asm = false,
                 bool optimize = false, bool enable_ssa = false,
                 const std::string &output_file = "") {
  // 重置全局变量
  line_number = 1;
  col_number = 1;
  root.reset();

  // 声明一些主要变量
  IRgenerator ir_gen;
  LLVMIR ssa_ir;
  bool ssa_generated = false;

  // 打开文件
  yyin = fopen(filename.c_str(), "r");
  if (!yyin) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return false;
  }

  if (verbose)
    std::cout << "=== 编译 " << filename << " ===" << std::endl;
  if (verbose)
    std::cout << "1. 语法分析..." << std::endl;

  // 语法分析
  if (yyparse() != 0) {
    std::cerr << "语法分析失败" << std::endl;
    fclose(yyin);
    return false;
  }

  fclose(yyin);

  if (!root) {
    std::cerr << "解析后根节点为空" << std::endl;
    return false;
  }

  if (verbose)
    std::cout << "语法分析完成" << std::endl;

  // 打印AST
  if (print_ast) {
    if (verbose)
      std::cout << "2. 打印AST..." << std::endl;
    ASTPrinter printer;
    root->accept(printer);
  }

  // 语义分析
  if (enable_semantic) {
    if (verbose)
      std::cout << "3. 语义分析..." << std::endl;

    SemanticAnalyzer analyzer;
    try {
      root->accept(analyzer);
      if (verbose)
        std::cout << "语义分析完成" << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "语义分析失败: " << e.what() << std::endl;
      return false;
    }
  }

  // IR生成
  if (generate_ir) {
    if (verbose)
      std::cout << "4. IR生成..." << std::endl;

    // 生成IR
    root->accept(ir_gen);
    std::stringstream ir_stream;
    ir_gen.llvmIR.printIR(ir_stream);
    std::string ir = ir_stream.str();

    // 确定输出文件名
    std::string ir_filename;
    if (!output_file.empty()) {
      // 如果指定了输出文件，使用该文件名但改扩展名为.ll
      size_t dot_pos = output_file.find_last_of('.');
      if (dot_pos != std::string::npos) {
        ir_filename = output_file.substr(0, dot_pos) + ".ll";
      } else {
        ir_filename = output_file + ".ll";
      }
    } else {
      // 否则基于输入文件名生成
      size_t dot_pos = filename.find_last_of('.');
      if (dot_pos != std::string::npos) {
        ir_filename = filename.substr(0, dot_pos) + ".ll";
      } else {
        ir_filename = filename + ".ll";
      }
    }

    // SSA变换
    if (enable_ssa) {
      if (verbose)
        std::cout << "5. SSA变换..." << std::endl;

      // 在SSA变换前保存原始IR
      std::string original_ir_filename = ir_filename;

      // 为SSA变换后的文件生成新文件名
      size_t dot_pos = ir_filename.find_last_of('.');
      if (dot_pos != std::string::npos) {
        ir_filename = ir_filename.substr(0, dot_pos) + "_ssa.ll";
      } else {
        ir_filename = ir_filename + "_ssa";
      }

      try {
        SSATransformer ssa_transformer;
        ssa_ir = ssa_transformer.transform(ir_gen.llvmIR);
        ssa_generated = true;

        // SSA优化
        if (optimize) {
          if (verbose)
            std::cout << "6. SSA优化..." << std::endl;
          SSAOptimizer ssa_optimizer;
          ssa_ir = ssa_optimizer.optimize(ssa_ir);
        }

        // 输出SSA IR
        std::stringstream ssa_stream;
        ssa_ir.printIR(ssa_stream);
        std::string ssa_ir_str = ssa_stream.str();

        std::ofstream ssa_out(ir_filename);
        if (ssa_out.is_open()) {
          ssa_out << ssa_ir_str;
          ssa_out.close();
          if (verbose)
            std::cout << "SSA IR已输出到: " << ir_filename << std::endl;
        } else {
          std::cerr << "无法创建SSA IR输出文件: " << ir_filename << std::endl;
          return false;
        }

        // 也保存原始IR
        std::ofstream orig_out(original_ir_filename);
        if (orig_out.is_open()) {
          orig_out << ir;
          orig_out.close();
          if (verbose)
            std::cout << "原始IR已输出到: " << original_ir_filename
                      << std::endl;
        }

      } catch (const std::exception &e) {
        std::cerr << "SSA变换失败: " << e.what() << std::endl;
        return false;
      }
    } else {
      // 输出原始IR
      std::ofstream ir_out(ir_filename);
      if (ir_out.is_open()) {
        ir_out << ir;
        ir_out.close();
        if (verbose)
          std::cout << "IR已输出到: " << ir_filename << std::endl;
      } else {
        std::cerr << "无法创建IR输出文件: " << ir_filename << std::endl;
        return false;
      }
    }
  }

  // 汇编生成
  if (generate_asm) {
    if (verbose)
      std::cout << "7. IR到汇编翻译..." << std::endl;

    try {
      // 确定输出文件名
      std::string asm_filename;
      if (!output_file.empty()) {
        size_t dot_pos = output_file.find_last_of('.');
        if (dot_pos != std::string::npos) {
          asm_filename = output_file.substr(0, dot_pos) + ".s";
        } else {
          asm_filename = output_file + ".s";
        }
      } else {
        size_t dot_pos = filename.find_last_of('.');
        if (dot_pos != std::string::npos) {
          asm_filename = filename.substr(0, dot_pos) + ".s";
        } else {
          asm_filename = filename + ".s";
        }
      }

      // 使用已生成的IR进行汇编翻译
      LLVMIR ir_for_asm;
      if (enable_ssa && ssa_generated) {
        // 如果启用了SSA，需要先销毁SSA形式
        SSADestroyer ssa_destroyer;
        ir_for_asm = ssa_destroyer.destroySSA(ssa_ir);
      } else {
        ir_for_asm = ir_gen.llvmIR;
      }

      Translator translator(asm_filename);
      translator.translate(ir_for_asm);

      // 8. 寄存器分配
      if (verbose)
        std::cout << "8. 寄存器分配..." << std::endl;
      RegisterAllocationPass::applyToTranslator(translator);
      if (verbose)
        std::cout << "寄存器分配完成" << std::endl;

      std::ofstream asm_out(asm_filename);
      if (asm_out.is_open()) {
        translator.riscv.print(asm_out);
        asm_out.close();
        if (verbose)
          std::cout << "9. 汇编代码已输出到: " << asm_filename << std::endl;
      } else {
        std::cerr << "无法创建汇编输出文件: " << asm_filename << std::endl;
        return false;
      }
    } catch (const std::exception &e) {
      std::cerr << "汇编生成失败: " << e.what() << std::endl;
      return false;
    }
  }

  return true;
}

void showUsage(const char *program_name) {
  std::cout << "用法: " << program_name << " [选项] <输入文件>" << std::endl;
  std::cout << "选项:" << std::endl;
  std::cout << "  -h, --help       显示此帮助信息" << std::endl;
  std::cout << "  -q, --quiet      静默模式" << std::endl;
  std::cout << "  -S               生成汇编代码" << std::endl;
  std::cout << "  -o <文件>        指定输出文件" << std::endl;
  std::cout << "  --ast            打印抽象语法树" << std::endl;
  std::cout << "  --no-semantic    跳过语义分析" << std::endl;
  std::cout << "  --O1             优化" << std::endl;
  std::cout << "  --ssa            启用SSA变换" << std::endl;
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
  bool generate_asm = true;
  bool optimize = false;
  bool enable_ssa = false;
  std::string filename;
  std::string output_file;

  // 解析命令行参数
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      showUsage(argv[0]);
      return 0;
    } else if (arg == "-q" || arg == "--quiet") {
      quiet_mode = true;
    } else if (arg == "-S") {
      generate_asm = true;
    } else if (arg == "-o") {
      if (i + 1 < argc) {
        output_file = argv[++i];
      } else {
        std::cerr << "选项 -o 需要指定输出文件名" << std::endl;
        return 1;
      }
    } else if (arg == "--ast") {
      print_ast = true;
    } else if (arg == "--no-semantic") {
      enable_semantic = false;
    } else if (arg == "--O1") {
      optimize = true;
    } else if (arg == "--ssa") {
      enable_ssa = true;
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
  bool success =
      compileFile(filename, !quiet_mode, enable_semantic, print_ast,
                  generate_ir, generate_asm, optimize, enable_ssa, output_file);

  return success ? 0 : 1;
}
