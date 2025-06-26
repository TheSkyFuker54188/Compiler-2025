#include "instruction.h"
#include <iomanip>
#include <iostream>
#include <sstream>

std::ostream &operator<<(std::ostream &s, LLVMDataType type) {
  switch (type) {
  case I32:
    s << "i32";
    break;
  case Float32:
    s << "float";
    break;
  case Pointer:
    s << "ptr";
    break;
  case Void:
    s << "void";
    break;
  case I8:
    s << "i8";
    break;
  case I1:
    s << "i1";
    break;
  case I64:
    s << "i64";
    break;
  case Double:
    s << "double";
    break;
  }
  return s;
}
std::ostream &operator<<(std::ostream &s, LLVMInstructionType type) {
  switch (type) {
  case Load:
    s << "load";
    break;
  case Store:
    s << "store";
    break;
  case Add:
    s << "add";
    break;
  case Sub:
    s << "sub";
    break;
  case IntegerCompare:
    s << "icmp";
    break;
  case Phi:
    s << "phi";
    break;
  case Allocate:
    s << "alloca";
    break;
  case Multiply:
    s << "mul";
    break;
  case Divide:
    s << "sdiv";
    break;
  case ConditionalBranch:
    s << "br";
    break;
  case UnconditionalBranch:
    s << "br";
    break;
  case FloatAdd:
    s << "fadd";
    break;
  case FloatSub:
    s << "fsub";
    break;
  case FloatMultiply:
    s << "fmul";
    break;
  case FloatDivide:
    s << "fdiv";
    break;
  case FloatCompare:
    s << "fcmp";
    break;
  case Modulo:
    s << "srem";
    break;
  case BitXor:
    s << "xor";
    break;
  case BitAnd:
    s << "and";
    break;
  case ShiftLeft:
    s << "shl";
    break;
  }
  return s;
}
std::ostream &operator<<(std::ostream &s, IntegerCompareCondition type) {
  switch (type) {
  case Equal:
    s << "eq";
    break;
  case NotEqual:
    s << "ne";
    break;
  case UnsignedGreaterThan:
    s << "ugt";
    break;
  case UnsignedGreaterOrEqual:
    s << "uge";
    break;
  case UnsignedLessThan:
    s << "ult";
    break;
  case UnsignedLessOrEqual:
    s << "ule";
    break;
  case SignedGreaterThan:
    s << "sgt";
    break;
  case SignedGreaterOrEqual:
    s << "sge";
    break;
  case SignedLessThan:
    s << "slt";
    break;
  case SignedLessOrEqual:
    s << "sle";
    break;
  }
  return s;
}
std::ostream &operator<<(std::ostream &s, FloatCompareCondition type) {
  switch (type) {
  case False:
    s << "false";
    break;
  case OrderedEqual:
    s << "oeq";
    break;
  case OrderedGreaterThan:
    s << "ogt";
    break;
  case OrderedGreaterOrEqual:
    s << "oge";
    break;
  case OrderedLessThan:
    s << "olt";
    break;
  case OrderedLessOrEqual:
    s << "ole";
    break;
  case OrderedNotEqual:
    s << "one";
    break;
  case Ordered:
    s << "ord";
    break;
  case UnorderedEqual:
    s << "ueq";
    break;
  case UnorderedGreaterThan:
    s << "ugt";
    break;
  case UnorderedGreaterOrEqual:
    s << "uge";
    break;
  case UnorderedLessThan:
    s << "ult";
    break;
  case UnorderedLessOrEqual:
    s << "ule";
    break;
  case UnorderedNotEqual:
    s << "une";
    break;
  case Unordered:
    s << "uno";
    break;
  case True:
    s << "true";
    break;
  }
  return s;
}

// 将操作数转换为字符串表示
std::string OperandToString(const Operand &op) {
  switch (op.type) {
    // @register operand;%r+register No
  case REG:
    return "%r" + std::to_string(op.reg_num);
    // @integer32 immediate
  case IMMI32:
    return std::to_string(op.immi32);
    // @float32 immediate
  case IMMF32: {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = op.immf32;
    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << u.i;
    return ss.str();
  }
  // @global identifier @+name
  case GLOBAL:
    return "@" + op.global_name;
    // @label %L+label No
  case LABEL:
    return "%L" + std::to_string(op.label_num);
    // @integer64 immediate
  case IMMI64:
    return std::to_string(op.immi64);
  default:
    return "<unknown>";
  }
}

void global_array(std::ostream &s, LLVMDataType type, const Instruction &v,
                  int dimDph, int beginPos, int endPos) {
  if (dimDph == 0) {
    int allzero = 1;
    if (v.type == 1) {
      for (auto x : v.IntInitVals) {
        if (x != 0) {
          allzero = 0;
          break;
        }
      }
    } else {
      for (auto x : v.FloatInitVals) {
        if (x != 0) {
          allzero = 0;
          break;
        }
      }
    }
    if (allzero) {
      for (int dim : v.dims) {
        s << "[" << dim << "x ";
      }
      s << type << std::string(v.dims.size(), ']') << " "
        << "zeroinitializer";
      return;
    }
  }
  if (beginPos == endPos) {
    if (type == I32) {
      s << type << " " << v.IntInitVals[beginPos];
    } else if (type == Float32) {
      float rawFloat = v.FloatInitVals[beginPos];
      unsigned long long rawFloatByte = *((int *)&rawFloat);
      unsigned long long signBit = rawFloatByte >> 31;
      unsigned long long expBits = (rawFloatByte >> 23) & ((1 << 8) - 1);
      unsigned long long part1 = rawFloatByte & ((1 << 23) - 1);

      unsigned long long out_signBit = signBit << 63;
      unsigned long long out_sigBits = part1 << 29;
      unsigned long long expBits_highestBit = (expBits & (1 << 7)) << 3;
      unsigned long long expBits_lowerBit = (expBits & (1 << 7) - 1);
      unsigned long long expBits_lowerBit_highestBit =
          expBits_lowerBit & (1 << 6);
      unsigned long long expBits_lowerBit_ext =
          (expBits_lowerBit_highestBit) | (expBits_lowerBit_highestBit << 1) |
          (expBits_lowerBit_highestBit << 2) |
          (expBits_lowerBit_highestBit << 3);
      unsigned long long expBits_full =
          expBits_highestBit | expBits_lowerBit | expBits_lowerBit_ext;
      unsigned long long out_expBits = expBits_full << 52;
      unsigned long long out_rawFloatByte =
          out_signBit | out_expBits | out_sigBits;
      s << type << " "
        << "0x" << std::hex << out_rawFloatByte;
      s << std::dec;
    }
    return;
  }
  for (int i = dimDph; i < v.dims.size(); i++) {
    s << "[" << v.dims[i] << " x ";
  }
  s << type << std::string(v.dims.size() - dimDph, ']') << " ";
  s << "[";
  int step = 1;
  for (int i = dimDph + 1; i < v.dims.size(); i++) {
    step *= v.dims[i];
  }
  for (int i = 0; i < v.dims[dimDph]; i++) {
    global_array(s, type, v, dimDph + 1, beginPos + i * step,
                 beginPos + (i + 1) * step - 1);
    if (i != v.dims[dimDph] - 1)
      s << ","; // Not the last element
  }
  s << "]";
}

void PrintIR(std::ostream &s, const Instruction &ins) {
  switch (ins.type) {
    // load
    // Syntax: <result>=load <ty>, ptr <pointer>
  case Load: {
    // operands[0]: 结果寄存器, operands[1]: 源指针
    s << OperandToString(ins.operands[0]) << " = load " << ins.result_type
      << ", ptr " << OperandToString(ins.operands[1]) << "\n";
    break;
  }
    // store
    // Syntax: store <ty> <value>, ptr<pointer>
  case Store: {
    // operands[0]: 存储的值, operands[1]: 目标指针
    s << "store " << ins.result_type << " " << OperandToString(ins.operands[0])
      << ", ptr " << OperandToString(ins.operands[1]) << "\n";
    break;
  }
  //<result>=add <ty> <op1>,<op2>
  case Add: {
    // operands[0]: 结果寄存器, operands[1]: 操作数1, operands[2]: 操作数2
    s << OperandToString(ins.operands[0]) << " = add " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
  //<result>=sub <ty> <op1>,<op2>
  case Sub: {
    s << OperandToString(ins.operands[0]) << " = sub " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
  //<result>=mul <ty> <op1>,<op2>
  case Multiply: {
    s << OperandToString(ins.operands[0]) << " = mul " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
  //<result>=div <ty> <op1>,<op2>
  case Divide: {
    s << OperandToString(ins.operands[0]) << " = div " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
  case AddModulo: {
    s << OperandToString(ins.operands[0])
      << " = call i32 @___llvm_ll_add_mod(i32 "
      << OperandToString(ins.operands[1]) << ",i32 "
      << OperandToString(ins.operands[2]) << ",i32 "
      << OperandToString(ins.operands[3]) << ")\n";
    break;
  }
  case UnsignedMinI32: {
    s << OperandToString(ins.operands[0])
      << " = call i32 @___llvm_ll_unsigned_min_i32(i32 "
      << OperandToString(ins.operands[1]) << ",i32 "
      << OperandToString(ins.operands[2]) << ")\n";
    break;
  }
  case UnsignedMaxI32: {
    s << OperandToString(ins.operands[0])
      << " = call i32 @___llvm_ll_unsigned_max_i32(i32 "
      << OperandToString(ins.operands[1]) << ",i32 "
      << OperandToString(ins.operands[2]) << ")\n";
    break;
  }
  case SignedMinI32: {
    s << OperandToString(ins.operands[0])
      << " = call i32 @___llvm_ll_signed_min_i32(i32 "
      << OperandToString(ins.operands[1]) << ",i32 "
      << OperandToString(ins.operands[2]) << ")\n";
    break;
  }
  case SignedMaxI32: {
    s << OperandToString(ins.operands[0])
      << " = call i32 @___llvm_ll_signed_max_i32(i32 "
      << OperandToString(ins.operands[1]) << ",i32 "
      << OperandToString(ins.operands[2]) << ")\n";
    break;
  }
  case FloatMinF32: {
    s << OperandToString(ins.operands[0])
      << " = call float @___llvm_ll_float_min_f32(float "
      << OperandToString(ins.operands[1]) << ",float "
      << OperandToString(ins.operands[2]) << ")\n";
    break;
  }
  case FloatMaxF32: {
    s << OperandToString(ins.operands[0])
      << " = call float @___llvm_ll_float_max_f32(float "
      << OperandToString(ins.operands[1]) << ",float "
      << OperandToString(ins.operands[2]) << ")\n";
  }
  //<result>=icmp <cond> <ty> <op1>,<op2>
  case IntegerCompare: {
    s << OperandToString(ins.operands[0]) << " = icmp "
      << ins.int_compare_condition << " " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
  //<result>=fcmp <ty> <op1>,<op2>
  case FloatCompare: {
    s << OperandToString(ins.operands[0]) << " = fcmp "
      << ins.float_compare_condition << " " << ins.result_type << " "
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
    // Conditional branch
    // Syntax:
    // br i1 <cond>, label <iftrue>, label <iffalse>
  case ConditionalBranch: {
    // operands[0]: 条件, operands[1]: true标签, operands[2]: false标签
    s << "br i1 " << OperandToString(ins.operands[0]) << ", label "
      << OperandToString(ins.operands[1]) << ", label "
      << OperandToString(ins.operands[2]) << "\n";
    break;
  }
    // Unconditional branch
    // Syntax:
    // br label <dest>
  case UnconditionalBranch: {
    // operands[0]: 目标标签
    s << "br label " << OperandToString(ins.operands[0]) << "\n";
    break;
  }
    // phi syntax:
    //<result>=phi <ty> [val1,label1],[val2,label2],……
  case Phi: {
    s << OperandToString(ins.operands[0]) << " = phi " << ins.result_type
      << " ";
    for (auto it = ins.phi_list.begin(); it != ins.phi_list.end(); ++it) {
      s << "[" << OperandToString(it->second) << ","
        << OperandToString(it->first) << "]";
      auto jt = it;
      if ((++jt) != ins.phi_list.end())
        s << ",";
    }
    s << '\n';
    break;
  }
    // alloca
    // usage 1: <result>=alloca <type>
    // usage 2: %3 = alloca [20 x [20 x i32]]
  case Allocate: {
    s << OperandToString(ins.operands[0]) << " = alloca ";
    if (ins.dims.empty())
      s << OperandToString(ins.operands[1]) << "\n"; // 单个变量
    else {
      for (std::vector<int>::const_iterator it = ins.dims.begin();
           it != ins.dims.end(); ++it)
        s << "[" << *it << " x "; // 高维数组
      s << OperandToString(ins.operands[1]) << std::string(ins.dims.size(), ']')
        << "\n";
    }
    break;
  }
    // Function Definition Syntax:
    // define void @DFS(i32 %0,i32 %1){
    //   Function Body
    // }
  case FunctionDefine: {
    s << "define " << ins.function_return_type << " @" << ins.function_name
      << "(";
    for (size_t i = 0; i < ins.args.size(); ++i) {
      s << ins.args[i].first << " " << OperandToString(ins.args[i].second);
      if (i < ins.args.size() - 1)
        s << ", ";
    }
    s << ") {\n";
    break;
  }
  // declare void @FunctionName(i32,f32)
  case FunctionDeclare: {
    s << "declare " << ins.function_return_type << " @" << ins.function_name
      << "(";
    for (size_t i = 0; i < ins.args.size(); ++i) {
      s << ins.args[i].first;
      if (i < ins.args.size() - 1) {
        s << ", ";
      }
    }
    s << ")\n";
    break;
  }

  /*
Global Id Define Instruction Syntax
Example 1:
    @p = global [105 x i32] zeroinitializer
Example 2:
    @.str = constant [4 x i8] c"%d \00", align 1
Example 3:
    @p = global [105 x [104 x i32]] [[104 x i32] [], [104 x i32]
zeroinitializer, ...]
*/
  case GlobalVariable: {
    if (ins.dims.empty()) {
      if (ins.init_val != nullptr)
        s << "@" << ins.str_name << " = global " << ins.result_type << " "
          << ins.init_val << "\n";
      else
        s << "@" << ins.str_name << " = global " << ins.result_type << " "
          << "zeroinitializer\n";
      break;
    }
    s << "@" << ins.str_name << " = global ";
    // print type
    // print init_val
    int step = 1;
    for (int i = 0; i < ins.dims.size(); i++) {
      step *= ins.dims[i];
    }
    global_array(s, ins.result_type, ins, 0, 0, step - 1);
    s << "\n";
    break;
  }
    /*
    Call Instruction Syntax
    Example 1:
        %12 = call i32 (ptr, ...)@printf(ptr @.str,i32 %11)
    Example 2:
        call void @DFS(i32 0,i32 %4)
    */
  case Call: {
    if (ins.result_type != Void) {
      s << OperandToString(ins.operands[0]) << " = call " << ins.result_type
        << " @" << ins.function_name << "(";
    } else {
      s << "call " << ins.result_type << " @" << ins.function_name << "(";
    }
    for (size_t i = 0; i < ins.args.size(); ++i) {
      s << ins.args[i].first << " " << OperandToString(ins.args[i].second);
      if (i < ins.args.size() - 1) {
        s << ", ";
      }
    }
    s << ")\n";
    break;
  }
  /*
Ret Instruction Syntax
Example 1:
    ret i32 0
Example 2:
    ret void
Example 3:
    ret i32 %r7
*/
  case Return: {
    s << "ret " << ins.return_type;
    if (ins.return_type != Void) {
      s << " " << OperandToString(ins.operands[0]) << "\n";
    } else {
      s << "\n";
    }
    break;
  }

  case Select: {
    // Syntax: <result> = select <cond>, <iftrue>, <iffalse>
    s << OperandToString(ins.operands[0]) << " = select i1"
      << OperandToString(ins.operands[1]) << ", "
      << OperandToString(ins.operands[2]) << ", "
      << OperandToString(ins.operands[3]) << "\n";
    break;
  }
  /*
Syntax:
<result> = getelementptr <ty>, ptr <ptrval>{, [inrange] <ty> <idx>}*
<result> = getelementptr inbounds <ty>, ptr <ptrval>{, [inrange] <ty> <idx>}*
<result> = getelementptr <ty>, <N x ptr> <ptrval>, [inrange] <vector index type>
<idx>
*/
  case GetElementPointer: {
    s << OperandToString(ins.operands[0]) << " = getelementptr ";
    if (ins.dims.empty())
      s << ins.type;
    else {
      for (int dim : ins.dims) {
        s << "[" << dim << " x ";
      }
      s << ins.type;
      s << std::string(ins.dims.size(), ']');
    }

    // print ptrval
    s << ", ptr " << OperandToString(ins.operands[1]);
    // print indexes
    for (size_t i = 2; i < ins.operand_count; ++i) {
      s << ", i32 " << OperandToString(ins.operands[i]);
    }
    s << "\n";
  }
  case FloatToSignedInt: {
    s << OperandToString(ins.operands[0]) << " = fptosi float"
      << OperandToString(ins.operands[1]) << " to " << ins.result_type
      << "i32 \n";
    break;
  }
  case SignedIntToFloat: {
    s << OperandToString(ins.operands[0]) << " = sitofp "
      << "i32 " << OperandToString(ins.operands[1]) << " to float\n";
    break;
  }
  case FloatExt: {
    s << OperandToString(ins.operands[0]) << " = fpext float"
      << OperandToString(ins.operands[1]) << " to double"
      << "\n";
    break;
  }
  case ZeroExtend: {
    s << OperandToString(ins.operands[0]) << " = zext " << ins.result_type
      << " " << OperandToString(ins.operands[1]) << " to " << ins.result_type
      << "\n";
    break;
  }
  case BitCast: {
    s << OperandToString(ins.operands[0]) << " = bitcast " << ins.result_type
      << " " << OperandToString(ins.operands[1]) << " to " << ins.result_type
      << "\n";
    break;
  }
  case GlobalString: {
    int str_len = ins.str_val.size() + 1;
    for (char c : ins.str_val) {
      if (c == '\\')
        str_len--;
    }
    s << "@" << ins.str_name << " = private unnamed_addr constant [" << str_len
      << " x i8] c\"";
    for (int i = 0; i < ins.str_val.size(); i++) {
      char c = ins.str_val[i];
      if (c == '\\') {
        i++;
        c = ins.str_val[i];
        if (c == 'n')
          s << "\\0A";
        else if (c == 't')
          s << "\\09";
        else if (c == '\"')
          s << "\\22";
        else if (c == 'r')
          s << "\\0D";
        else if (c == 'b')
          s << "\\08";
        else if (c == 'f')
          s << "\\0C";
        else if (c == 'v')
          s << "\\0B";
        else if (c == 'a')
          s << "\\07";
        else if (c == '?')
          s << "\?";
        else if (c == '0')
          s << "\\00";
        else if (c == '\'')
          s << "\'";
        else if (c == '\\')
          s << "\\\\";
        else
          s << c;
      } else
        s << c;
    }
    s << "\\00"
      << "\"\n";
    break;
  }
  default:
    s << "; Unknown instruction type\n";
    break;
  }
}
