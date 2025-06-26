#include "./include/yacc/parser.hpp"
#include <fstream>
#include <iostream>
#include <memory>

// 这个全局变量连接到输入文件流，parser会读取这个文件
extern FILE *yyin;

/*
 * 前端解析器的主入口函数
 *
 * 这个程序只需要一个参数：SysY源文件的路径
 * 它会解析文件，构建抽象语法树(AST)，然后输出确认信息
 * 构建好的AST存储在全局单例中，后续的后端处理可以直接获取
 *
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 成功返回0，失败返回1
 */
int main(int argc, char **argv)
{
  // --- 参数检查 ---
  if (argc != 2)
  {
    std::cerr << "用法: " << argv[0] << " <输入文件.sy>" << std::endl;
    return 1;
  }

  // --- 文件处理 ---
  yyin = fopen(argv[1], "r");
  if (!yyin)
  {
    perror(argv[1]); // 打印系统错误信息
    return 1;
  }

  // --- 开始解析 ---
  // yy::parser对象会调用词法分析器并构建AST
  yy::parser parser_instance;
  bool success = (parser_instance.parse() == 0);
  fclose(yyin);

  if (!success)
  {
    std::cerr << "解析失败了！" << std::endl;
    return 1;
  }

  std::cout << "前端解析成功完成！AST已经构建完毕。" << std::endl;

  // TODO: 实现AST遍历和可视化功能
  // 下一步可以考虑添加一个方法来打印AST结构，比如：
  // ast_root->print_tree();

  // TODO: 与后端对接的接口
  // 后端需要拿到AST根节点开始进行中间代码(IR)生成
  // 使用方式大概是这样：
  // IRGenerator ir_generator;
  // ir_generator.process(ast_root);
  // auto module = ir_generator.get_ir_module();

  return 0;
}