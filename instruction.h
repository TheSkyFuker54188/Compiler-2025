#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <vector>

// LLVM IR中的指令类型枚举
enum LLVMInstructionType {
  Unknown = 0,              // 未定义指令
  Load = 1,                 // 加载指令
  Store = 2,                // 存储指令
  Add = 3,                  // 加法
  Sub = 4,                  // 减法
  IntegerCompare = 5,       // 整数比较
  Phi = 6,                  // Phi节点
  Allocate = 7,             // 分配内存
  Multiply = 8,             // 乘法
  Divide = 9,               // 除法
  ConditionalBranch = 10,   // 条件分支
  UnconditionalBranch = 11, // 无条件分支
  FloatAdd = 12,            // 浮点加法
  FloatSub = 13,            // 浮点减法
  FloatMultiply = 14,       // 浮点乘法
  FloatDivide = 15,         // 浮点除法
  FloatCompare = 16,        // 浮点比较
  Modulo = 17,              // 取模
  BitXor = 18,              // 按位异或
  Return = 19,              // 返回指令
  ZeroExtend = 20,          // 零扩展
  ShiftLeft = 21,           // 左移
  FloatToSignedInt = 24,    // 浮点转有符号整数
  GetElementPointer = 25,   // 获取元素指针
  Call = 26,                // 函数调用
  SignedIntToFloat = 27,    // 有符号整数转浮点
  GlobalVariable = 28,      // 全局变量定义
  GlobalString = 29,        // 全局字符串
  AddModulo = 30,           // 加法取模
  UnsignedMinI32 = 31,      // 无符号32位整数最小值
  UnsignedMaxI32 = 32,      // 无符号32位整数最大值
  SignedMinI32 = 33,        // 有符号32位整数最小值
  SignedMaxI32 = 34,        // 有符号32位整数最大值
  BitCast = 35,             // 位转换
  FloatMinF32 = 36,         // 32位浮点最小值
  FloatMaxF32 = 37,         // 32位浮点最大值
  BitAnd = 38,              // 按位与
  FloatExt = 39,            // 浮点提升
  Select = 40,              // 选择指令
  FunctionDefine = 41,      // 函数定义
  FunctionDeclare = 42,     // 函数声明
};

// 操作数的数据类型
enum LLVMDataType {
  I32 = 1,     // 32位整数
  Float32 = 2, // 32位浮点数
  Pointer = 3, // 指针
  Void = 4,    // 无返回值
  I8 = 5,      // 8位整数
  I1 = 6,      // 1位布尔值
  I64 = 7,     // 64位整数
  Double = 8   // 双精度浮点数
};

// 整数比较条件
enum IntegerCompareCondition {
  Equal = 1,                  // 等于
  NotEqual = 2,               // 不等于
  UnsignedGreaterThan = 3,    // 无符号大于
  UnsignedGreaterOrEqual = 4, // 无符号大于等于
  UnsignedLessThan = 5,       // 无符号小于
  UnsignedLessOrEqual = 6,    // 无符号小于等于
  SignedGreaterThan = 7,      // 有符号大于
  SignedGreaterOrEqual = 8,   // 有符号大于等于
  SignedLessThan = 9,         // 有符号小于
  SignedLessOrEqual = 10      // 有符号小于等于
};

// 浮点比较条件
enum FloatCompareCondition {
  False = 1,                    // 始终返回false
  OrderedEqual = 2,             // 有序相等
  OrderedGreaterThan = 3,       // 有序大于
  OrderedGreaterOrEqual = 4,    // 有序大于等于
  OrderedLessThan = 5,          // 有序小于
  OrderedLessOrEqual = 6,       // 有序小于等于
  OrderedNotEqual = 7,          // 有序不相等
  Ordered = 8,                  // 有序（无NaN）
  UnorderedEqual = 9,           // 无序相等
  UnorderedGreaterThan = 10,    // 无序大于
  UnorderedGreaterOrEqual = 11, // 无序大于等于
  UnorderedLessThan = 12,       // 无序小于
  UnorderedLessOrEqual = 13,    // 无序小于等于
  UnorderedNotEqual = 14,       // 无序不相等
  Unordered = 15,               // 无序（可能有NaN）
  True = 16                     // 始终返回true
};

enum OperandType {
  REG = 1,
  IMMI32 = 2,
  IMMF32 = 3,
  GLOBAL = 4,
  LABEL = 5,
  IMMI64 = 6
};

struct Operand {
  OperandType type;
  union {
    int reg_num;
    int immi32;
    float immf32;
    std::string global_name;
    int label_num;
    long long immi64;
  };
};

struct Instruction {
  int block_id;                                  // 所属基本块ID
  int id;                                        // 指令ID
  LLVMInstructionType type;                      // 指令类型
  Operand *operands;                             // 操作数列表
  int operand_count;                             // 操作数数量
  LLVMDataType result_type;                      // 结果类型
  LLVMDataType function_return_type;             // 函数返回类型
  std::string function_name;                     // 函数名
  LLVMDataType return_type;                      // 返回类型
  IntegerCompareCondition int_compare_condition; // 整数比较条件
  FloatCompareCondition float_compare_condition; // 浮点比较条件
  std::vector<std::pair<LLVMDataType, Operand>> args;
  std::vector<std::pair<Operand, Operand>> phi_list;
  std::vector<int> dims;
  std::string str_val;
  std::string str_name;
  Operand *init_val;
  std::vector<int> IntInitVals{}; // used for array
  std::vector<float> FloatInitVals{};
};

#endif