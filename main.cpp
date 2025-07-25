#include "include/ast.h"
#include "include/astprinter.h"
#include "include/block.h"
#include "include/code_emitter.h"
#include "include/globalisel.h"
#include "include/riscv_mir.h"
#include "include/semantic.h"
#include "include/ssa.h"
#include "parser/parser.tab.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

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
                 bool generate_ir = true, bool generate_asm = false,
                 bool optimize = false, const std::string &output_file = "") {
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
  LLVMIR ir;
  if (generate_ir && semantic_success) {
    if (verbose) {
      std::cout << "阶段3: 中间代码生成..." << std::endl;
    }

    IRgenerator irgen;
    root->accept(irgen);
    ir = irgen.getLLVMIR();

    // 输出原始IR到文件
    std::string ir_filename =
        filename.substr(0, filename.find_last_of('.')) + ".ll";
    std::ofstream ir_file(ir_filename);
    if (ir_file.is_open()) {
      ir.printIR(ir_file);
      ir_file.close();
      if (verbose) {
        std::cout << "中间代码已生成到 " << ir_filename << std::endl;
      }
    } else {
      std::cerr << "无法创建IR文件 " << ir_filename << std::endl;
      return false;
    }
  }

  // 第五阶段：SSA变换和优化
  LLVMIR optimized_ir = ir;
  if (semantic_success && !ir.function_block_map.empty() && optimize) {
    if (verbose) {
      std::cout << "阶段4: SSA变换和优化..." << std::endl;
    }

    // SSA变换
    SSATransformer ssa_transformer;
    LLVMIR ssa_ir = ssa_transformer.transform(ir);

    if (verbose) {
      std::cout << "SSA变换完成" << std::endl;
    }

    // 输出SSA形式的IR到文件（可选）
    std::string ssa_ir_filename =
        filename.substr(0, filename.find_last_of('.')) + "_ssa.ll";
    std::ofstream ssa_ir_file(ssa_ir_filename);
    if (ssa_ir_file.is_open()) {
      ssa_ir.printIR(ssa_ir_file);
      ssa_ir_file.close();
      if (verbose) {
        std::cout << "SSA中间代码已生成到 " << ssa_ir_filename << std::endl;
      }
    }

    // SSA优化
    SSAOptimizer ssa_optimizer;
    LLVMIR optimized_ssa_ir = ssa_optimizer.optimize(ssa_ir);

    if (verbose) {
      std::cout << "SSA优化完成" << std::endl;
    }

    // SSA销毁
    SSADestroyer ssa_destroyer;
    optimized_ir = ssa_destroyer.destroySSA(optimized_ssa_ir);

    if (verbose) {
      std::cout << "SSA销毁完成，准备后端代码生成" << std::endl;
    }

    // 输出优化后的IR到文件
    std::string opt_ir_filename =
        filename.substr(0, filename.find_last_of('.')) + "_opt.ll";
    std::ofstream opt_ir_file(opt_ir_filename);
    if (opt_ir_file.is_open()) {
      optimized_ir.printIR(opt_ir_file);
      opt_ir_file.close();
      if (verbose) {
        std::cout << "优化后的中间代码已生成到 " << opt_ir_filename
                  << std::endl;
      }
    }
  }

  // 第五阶段：汇编代码生成
  if (generate_asm && semantic_success && generate_ir) {
    if (verbose) {
      std::cout << "阶段4: 汇编代码生成..." << std::endl;
    }

    try {
      MachineModule mir_module;
      MachineModule asm_module; // 用于汇编生成的模块
      RISCVGlobalISel global_isel;

      // 第一步：运行到InstructionSelect阶段，用于生成MIR文件
      bool isel_success = global_isel.runGlobalISelToInstructionSelect(
          optimized_ir, mir_module);

      if (isel_success) {
        // 输出生成的MIR到文件（InstructionSelect阶段的状态）
        // std::string mir_filename =
        //     filename.substr(0, filename.find_last_of('.')) + ".mir";
        // std::ofstream mir_file(mir_filename);
        // if (mir_file.is_open()) {
        //   mir_module.printMIR(mir_file);  // 使用MIR专用格式
        //   mir_file.close();
        //   if (verbose) {
        //     std::cout << "机器中间代码已生成到 " << mir_filename <<
        //     std::endl;
        //   }
        // } else {
        //   std::cerr << "无法创建MIR文件 " << mir_filename << std::endl;
        // }

        // 第二步：运行完整流程用于生成汇编文件
        bool full_success = global_isel.runGlobalISel(ir, asm_module);

        if (full_success) {
          if (verbose) {
            std::cout << "GlobalISel指令选择成功!" << std::endl;
          }

          // 输出生成的RISC-V汇编代码到文件（使用代码发射器）
          std::string asm_filename =
              output_file.empty()
                  ? filename.substr(0, filename.find_last_of('.')) + ".s"
                  : output_file;
          std::ofstream asm_file(asm_filename);
          if (asm_file.is_open()) {
            RISCVCodeEmitter emitter(asm_file); // 使用专门的代码发射器
            emitter.emitModule(asm_module);
            asm_file.close();
            if (verbose) {
              std::cout << "RISC-V汇编代码已生成到 " << asm_filename
                        << std::endl;
            }
          } else {
            std::cerr << "无法创建汇编文件 " << asm_filename << std::endl;
          }
        } else {
          std::cerr << "GlobalISel完整流程执行失败!" << std::endl;
          return false;
        }
      } else {
        std::cerr << "GlobalISel指令选择失败!" << std::endl;
        return false;
      }
    } catch (const std::exception &e) {
      std::cerr << "GlobalISel执行出错: " << e.what() << std::endl;
      return false;
    }
  }

  return semantic_success;
}

/**
 * 显示使用帮助
 */
void showUsage(const char *program_name) {
  std::cout << "SYS Language Compiler" << std::endl;
  std::cout << "Usage: " << program_name << " [options] <file.sy>" << std::endl;
  std::cout << "\nOptions:" << std::endl;
  std::cout << "  -h, --help       显示帮助信息" << std::endl;
  std::cout << "  -q, --quiet      静默模式（只显示错误）" << std::endl;
  std::cout << "  -S               生成汇编代码" << std::endl;
  std::cout << "  -o <file>        指定输出文件名" << std::endl;
  std::cout << "  --ast            打印AST结构" << std::endl;
  std::cout << "  --no-semantic    跳过语义分析" << std::endl;
  std::cout << "  --O1             优化" << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    showUsage(argv[0]);
    return 1;
  }

  bool quiet_mode = true;
  bool enable_semantic = true;
  bool print_ast = false;
  bool generate_ir = true;
  bool generate_asm = true;
  bool optimize = true; // 默认启用优化
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
                             generate_ir, generate_asm, optimize, output_file);

  return success ? 0 : 1;
}