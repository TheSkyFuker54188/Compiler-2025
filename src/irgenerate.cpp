#include "../include/ast.h"
#include "../include/block.h"
#include "../include/symtab.h"
#include <assert.h>
#include <stdexcept>
#include <optional>
#include <math.h>

std::ostream &operator<<(std::ostream &s, LLVMType type) {
  switch (type) {
  case I32: s << "i32"; break;
  case FLOAT32: s << "float"; break;
  case PTR: s << "ptr"; break;
  case VOID_TYPE: s << "void"; break;
  case I8: s << "i8"; break;
  case I1: s << "i1"; break;
  case I64: s << "i64"; break;
  case DOUBLE: s << "double"; break;
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, LLVMIROpcode type) {
    switch (type) {
    case LOAD: s << "load"; break;
    case STORE: s << "store"; break;
    case ADD: s << "add"; break;
    case SUB: s << "sub"; break;
    case ICMP: s << "icmp"; break;
    case PHI: s << "phi"; break;
    case ALLOCA: s << "alloca"; break;
    case MUL_OP: s << "mul"; break;
    case DIV_OP: s << "sdiv"; break;
    case BR_COND: s << "br"; break;
    case BR_UNCOND: s << "br"; break;
    case FADD: s << "fadd"; break;
    case FSUB: s << "fsub"; break;
    case FMUL: s << "fmul"; break;
    case FDIV: s << "fdiv"; break;
    case FCMP: s << "fcmp"; break;
    case MOD_OP: s << "srem"; break;
    case BITXOR: s << "xor"; break;
    case BITAND: s << "and"; break;
    case BITOR: s << "or"; break;
    case SHL: s << "shl"; break;
    }
    return s;
  }

std::ostream &operator<<(std::ostream &s, IcmpCond type) {
  switch (type) {
  case eq: s << "eq"; break;
  case ne: s << "ne"; break;
  case ugt: s << "ugt"; break;
  case uge: s << "uge"; break;
  case ult: s << "ult"; break;
  case ule: s << "ule"; break;
  case sgt: s << "sgt"; break;
  case sge: s << "sge"; break;
  case slt: s << "slt"; break;
  case sle: s << "sle"; break;
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, FcmpCond type) {
  switch (type) {
  case FALSE: s << "false"; break;
  case OEQ: s << "oeq"; break;
  case OGT: s << "ogt"; break;
  case OGE: s << "oge"; break;
  case OLT: s << "olt"; break;
  case OLE: s << "ole"; break;
  case ONE: s << "one"; break;
  case ORD: s << "ord"; break;
  case UEQ: s << "ueq"; break;
  case UGT: s << "ugt"; break;
  case UGE: s << "uge"; break;
  case ULT: s << "ult"; break;
  case ULE: s << "ule"; break;
  case UNE: s << "une"; break;
  case UNO: s << "uno"; break;
  case TRUE: s << "true"; break;
  }
  return s;
}

class IRgenTable {
public:
  Operand current_strptr = nullptr;
  std::map<int, VarAttribute> RegTable;
  std::map<int, int> FormalArrayTable;
  std::map<std::string, int> name_to_reg;
  IRgenTable() {}
};

SymbolTable str_table;
static FuncDefInstruction function_now;
static BaseType function_returntype = BaseType::VOID;
//static int now_label = 0;
static int loop_start_label = -1;
static int loop_end_label = -1;
static std::map<int, LLVMType> RegLLVMTypeMap;

std::map<FuncDefInstruction, int> max_label_map{};
std::map<FuncDefInstruction, int> max_reg_map{};

int max_reg = -1;
//int max_label = -1;

IRgenTable irgen_table;
LLVMIR llvmIR;

// extern void (*IRgenSingleNode[6])(SyntaxNode *a, BinaryOp opcode, LLVMBlock B);
// extern void (*IRgenBinaryNode[6][6])(SyntaxNode *a, SyntaxNode *b, BinaryOp opcode, LLVMBlock B);

//LLVMType Type2LLvm[6] = {LLVMType::I32, LLVMType::FLOAT32, LLVMType::I1, LLVMType::VOID_TYPE, LLVMType::PTR, LLVMType::DOUBLE};
std::map<BaseType, LLVMType> Type2LLvm = {
    {BaseType::INT, LLVMType::I32},
    {BaseType::FLOAT, LLVMType::FLOAT32},
    {BaseType::VOID, LLVMType::VOID_TYPE},
    {BaseType::STRING, LLVMType::PTR}
};
RegOperand *GetNewRegOperand(int RegNo);

static std::unordered_map<int, RegOperand *> RegOperandMap;
static std::map<int, LabelOperand *> LabelOperandMap;
static std::map<std::string, GlobalOperand *> GlobalOperandMap;

RegOperand *GetNewRegOperand(int RegNo) {
    auto it = RegOperandMap.find(RegNo);
    if (it == RegOperandMap.end()) {
        auto R = new RegOperand(RegNo);
        RegOperandMap[RegNo] = R;
        return R;
    } else {
        return it->second;
    }
}

LabelOperand *GetNewLabelOperand(int LabelNo) {
    auto it = LabelOperandMap.find(LabelNo);
    if (it == LabelOperandMap.end()) {
        auto L = new LabelOperand(LabelNo);
        LabelOperandMap[LabelNo] = L;
        return L;
    } else {
        return it->second;
    }
}

GlobalOperand *GetNewGlobalOperand(std::string name) {
    auto it = GlobalOperandMap.find(name);
    if (it == GlobalOperandMap.end()) {
        auto G = new GlobalOperand(name);
        GlobalOperandMap[name] = G;
        return G;
    } else {
        return it->second;
    }
}

long long Float_to_Byte(float f) {
    float rawFloat = f;
    unsigned long long rawFloatByte = *((int *)&rawFloat);
    unsigned long long signBit = rawFloatByte >> 31;
    unsigned long long expBits = (rawFloatByte >> 23) & ((1 << 8) - 1);
    unsigned long long part1 = rawFloatByte & ((1 << 23) - 1);
  
    unsigned long long out_signBit = signBit << 63;
    unsigned long long out_sigBits = part1 << 29;
    unsigned long long expBits_highestBit = (expBits & (1 << 7)) << 3;
    unsigned long long expBits_lowerBit = (expBits & (1 << 7) - 1);
    unsigned long long expBits_lowerBit_highestBit = expBits_lowerBit & (1 << 6);
    unsigned long long expBits_lowerBit_ext = (expBits_lowerBit_highestBit) | (expBits_lowerBit_highestBit << 1) |
                                              (expBits_lowerBit_highestBit << 2) | (expBits_lowerBit_highestBit << 3);
    unsigned long long expBits_full = expBits_highestBit | expBits_lowerBit | expBits_lowerBit_ext;
    unsigned long long out_expBits = expBits_full << 52;
    unsigned long long out_rawFloatByte = out_signBit | out_expBits | out_sigBits;
    /*
        Example: Float Value 114.514
  
        llvm Double:
            0                               ---1 bit    (sign bit)
            1000 0000 101                   ---11 bits  (exp bits)
            1100 1010 0000 1110 0101 011    ---23 bits  (part 1)
            00000000000000000000000000000   ---29 bits  (part 2 All zero)
  
        IEEE Float:
            0                               ---1 bit    (sign bit)
            1    0000 101                   ---8 bits   (exp bits)
            1100 1010 0000 1110 0101 011    ---23 bits  (part 1)
  
    */
  
    return out_rawFloatByte;
  }

void recursive_print(std::ostream &s, LLVMType type, VarAttribute &v, size_t dimDph, size_t beginPos, size_t endPos) {
    if (dimDph == 0) {
        int allzero = 1;
        if (v.type == BaseType::INT) {
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
            for (size_t dim : v.dims) {
                s << "[" << dim << "x ";
            }
            s << type << std::string(v.dims.size(), ']') << " zeroinitializer";
            return;
        }
    }
    if (beginPos == endPos) {
        if (type == I32) {
            s << type << " " << v.IntInitVals[beginPos];
        } else if (type == FLOAT32) {
            float rawFloat = v.FloatInitVals[beginPos];
            unsigned long long rawFloatByte;
            std::memcpy(&rawFloatByte, &rawFloat, sizeof(float));
            unsigned long long signBit = rawFloatByte >> 31;
            unsigned long long expBits = (rawFloatByte >> 23) & ((1 << 8) - 1);
            unsigned long long part1 = rawFloatByte & ((1 << 23) - 1);
            unsigned long long out_signBit = signBit << 63;
            unsigned long long out_sigBits = part1 << 29;
            unsigned long long expBits_highestBit = (expBits & (1 << 7)) << 3;
            unsigned long long expBits_lowerBit = (expBits & ((1 << 7) - 1));
            unsigned long long expBits_lowerBit_highestBit = expBits_lowerBit & (1 << 6);
            unsigned long long expBits_lowerBit_ext = (expBits_lowerBit_highestBit) | (expBits_lowerBit_highestBit << 1) |
                                                     (expBits_lowerBit_highestBit << 2) | (expBits_lowerBit_highestBit << 3);
            unsigned long long expBits_full = expBits_highestBit | expBits_lowerBit | expBits_lowerBit_ext;
            unsigned long long out_expBits = expBits_full << 52;
            unsigned long long out_rawFloatByte = out_signBit | out_expBits | out_sigBits;
            s << type << " 0x" << std::hex << out_rawFloatByte;
            s << std::dec;
        }
        return;
    }
    for (size_t i = dimDph; i < v.dims.size(); i++) {
        s << "[" << v.dims[i] << " x ";
    }
    s << type << std::string(v.dims.size() - dimDph, ']') << " [";
    size_t step = 1;
    for (size_t i = dimDph + 1; i < v.dims.size(); i++) {
        step *= v.dims[i];
    }
    for (size_t i = 0; i < v.dims[dimDph]; i++) {
        recursive_print(s, type, v, dimDph + 1, beginPos + i * step, beginPos + (i + 1) * step - 1);
        if (i != v.dims[dimDph] - 1) s << ",";
    }
    s << "]";
}

void IRgenArithmeticI32ImmRight(LLVMBlock B, LLVMIROpcode opcode, int reg1, int val2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::I32, GetNewRegOperand(reg1),
                                                      new ImmI32Operand(val2), GetNewRegOperand(result_reg)));
}

void IRgenArithmeticI32(LLVMBlock B, LLVMIROpcode opcode,
    int reg1, int reg2, int result_reg) {
B->InsertInstruction(1, new ArithmeticInstruction(opcode,
                                  LLVMType::I32,
                                  GetNewRegOperand(reg1),
                                  GetNewRegOperand(reg2),
                                  GetNewRegOperand(result_reg)));
RegLLVMTypeMap[result_reg] = LLVMType::I32;
}

void IRgenArithmeticF32(LLVMBlock B, LLVMIROpcode opcode, int reg1, int reg2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::FLOAT32, GetNewRegOperand(reg1),
                                                      GetNewRegOperand(reg2), GetNewRegOperand(result_reg)));
}

void IRgenArithmeticI32ImmLeft(LLVMBlock B, LLVMIROpcode opcode, int val1, int reg2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::I32, new ImmI32Operand(val1),
                                                      GetNewRegOperand(reg2), GetNewRegOperand(result_reg)));
}

void IRgenArithmeticF32ImmLeft(LLVMBlock B, LLVMIROpcode opcode, float val1, int reg2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::FLOAT32, new ImmF32Operand(val1),
                                                      GetNewRegOperand(reg2), GetNewRegOperand(result_reg)));
}

void IRgenArithmeticI32ImmAll(LLVMBlock B, LLVMIROpcode opcode, int val1, int val2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::I32, new ImmI32Operand(val1),
                                                      new ImmI32Operand(val2), GetNewRegOperand(result_reg)));
}

void IRgenArithmeticF32ImmAll(LLVMBlock B, LLVMIROpcode opcode, float val1, float val2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::FLOAT32, new ImmF32Operand(val1),
                                                      new ImmF32Operand(val2), GetNewRegOperand(result_reg)));
}

void IRgenIcmp(LLVMBlock B, IcmpCond cmp_op, int reg1, int reg2, int result_reg) {
    B->InsertInstruction(1, new IcmpInstruction(LLVMType::I32,
                                                GetNewRegOperand(reg1),
                                                new ImmI32Operand(reg2),
                                                cmp_op,
                                                GetNewRegOperand(result_reg)));
    // 结果是 i1
    RegLLVMTypeMap[result_reg] = LLVMType::I1;
}

void IRgenFcmp(LLVMBlock B, FcmpCond cmp_op, int reg1, int reg2, int result_reg) {
    B->InsertInstruction(1, new FcmpInstruction(LLVMType::FLOAT32,
                                                GetNewRegOperand(reg1),
                                                GetNewRegOperand(reg2),
                                                cmp_op,
                                                GetNewRegOperand(result_reg)));
    // 结果也是 i1
    RegLLVMTypeMap[result_reg] = LLVMType::I1;
}

void IRgenIcmpImmRight(LLVMBlock B, IcmpCond cmp_op, int reg1, int val2, int result_reg) {
    B->InsertInstruction(1, new IcmpInstruction(LLVMType::I32, GetNewRegOperand(reg1), new ImmI32Operand(val2), cmp_op,
                                                GetNewRegOperand(result_reg)));
}

void IRgenFcmpImmRight(LLVMBlock B, FcmpCond cmp_op, int reg1, float val2, int result_reg) {
    B->InsertInstruction(1, new FcmpInstruction(LLVMType::FLOAT32, GetNewRegOperand(reg1), new ImmF32Operand(val2),
                                                cmp_op, GetNewRegOperand(result_reg)));
}

void IRgenFptosi(LLVMBlock B, int src, int dst) {
    B->InsertInstruction(1, new FptosiInstruction(GetNewRegOperand(dst), GetNewRegOperand(src)));
}

void IRgenFpext(LLVMBlock B, int src, int dst) {
    B->InsertInstruction(1, new FpextInstruction(GetNewRegOperand(dst), GetNewRegOperand(src)));
}

void IRgenSitofp(LLVMBlock B, int src, int dst) {
    B->InsertInstruction(1, new SitofpInstruction(GetNewRegOperand(dst), GetNewRegOperand(src)));
}

void IRgenZextI1toI32(LLVMBlock B, int src, int dst) {
    B->InsertInstruction(1, new ZextInstruction(LLVMType::I32, GetNewRegOperand(dst), LLVMType::I1, GetNewRegOperand(src)));
}

void IRgenGetElementptr(LLVMBlock B, LLVMType type, int result_reg, Operand ptr, std::vector<int> dims, std::vector<Operand> indexs) {
    B->InsertInstruction(1, new GetElementptrInstruction(type, GetNewRegOperand(result_reg), ptr, dims, indexs));
}

void IRgenLoad(LLVMBlock B, LLVMType type, int result_reg, Operand ptr) {
    B->InsertInstruction(1, new LoadInstruction(type, ptr, GetNewRegOperand(result_reg)));
    RegLLVMTypeMap[result_reg] = type;
}

void IRgenStore(LLVMBlock B, LLVMType type, int value_reg, Operand ptr) {
    B->InsertInstruction(1, new StoreInstruction(type, ptr, GetNewRegOperand(value_reg)));
}

void IRgenStore(LLVMBlock B, LLVMType type, Operand value, Operand ptr) {
    B->InsertInstruction(1, new StoreInstruction(type, ptr, value));
}

void IRgenCall(LLVMBlock B, LLVMType type, int result_reg,
    std::vector<std::pair<LLVMType, Operand>> args,
    std::string name) {
B->InsertInstruction(1, new CallInstruction(type,
                                     GetNewRegOperand(result_reg),
                                     name,
                                     args));
if (result_reg >= 0)
RegLLVMTypeMap[result_reg] = type;
}

void IRgenCallVoid(LLVMBlock B, LLVMType type, std::vector<std::pair<enum LLVMType, Operand>> args, std::string name) {
    B->InsertInstruction(1, new CallInstruction(type, GetNewRegOperand(-1), name, args));
}

void IRgenCallNoArgs(LLVMBlock B, LLVMType type, int result_reg, std::string name) {
    B->InsertInstruction(1, new CallInstruction(type, GetNewRegOperand(result_reg), name));
}

void IRgenCallVoidNoArgs(LLVMBlock B, LLVMType type, std::string name) {
    B->InsertInstruction(1, new CallInstruction(type, GetNewRegOperand(-1), name));
}

void IRgenRetReg(LLVMBlock B, LLVMType type, int reg) {
    B->InsertInstruction(1, new RetInstruction(type, GetNewRegOperand(reg)));
}

void IRgenRetImmInt(LLVMBlock B, LLVMType type, int val) {
    B->InsertInstruction(1, new RetInstruction(type, new ImmI32Operand(val)));
}

void IRgenRetImmFloat(LLVMBlock B, LLVMType type, float val) {
    B->InsertInstruction(1, new RetInstruction(type, new ImmF32Operand(val)));
}

void IRgenRetVoid(LLVMBlock B) {
    B->InsertInstruction(1, new RetInstruction(LLVMType::VOID_TYPE, nullptr));
}

void IRgenBRUnCond(LLVMBlock B, int dst_label) {
    B->InsertInstruction(1, new BrUncondInstruction(GetNewLabelOperand(dst_label)));
}

void IRgenBrCond(LLVMBlock B, int cond_reg, int true_label, int false_label) {
    B->InsertInstruction(1, new BrCondInstruction(GetNewRegOperand(cond_reg), GetNewLabelOperand(true_label),
                                                  GetNewLabelOperand(false_label)));
}

void IRgenAlloca(LLVMBlock B, LLVMType type, int reg) {
    B->InsertInstruction(0, new AllocaInstruction(type, GetNewRegOperand(reg)));
}

void IRgenAllocaArray(LLVMBlock B, LLVMType type, int reg, std::vector<int> dims) {
    B->InsertInstruction(0, new AllocaInstruction(type, dims, GetNewRegOperand(reg)));
}

void BasicBlock::InsertInstruction(int pos, Instruction Ins) {
    assert(pos == 0 || pos == 1);
    if (pos == 0) {
        Instruction_list.push_front(Ins);
    } else if (pos == 1) {
        Instruction_list.push_back(Ins);
    }
}

bool IsBr(Instruction ins) {
    int opcode = ins->GetOpcode();
    return opcode == BR_COND || opcode == BR_UNCOND;
}

bool IsRet(Instruction ins) {
    int opcode = ins->GetOpcode();
    return opcode == RET;
}

void AddNoReturnBlock() {
    for (auto block : llvmIR.function_block_map[function_now]) {
        LLVMBlock B = block.second;
        if (B->Instruction_list.empty() || (!IsRet(B->Instruction_list.back()) && !IsBr(B->Instruction_list.back()))) {
            if (function_returntype == BaseType::VOID) {
                IRgenRetVoid(B);
            } else if (function_returntype == BaseType::INT) {
                IRgenRetImmInt(B, LLVMType::I32, 0);
            } else if (function_returntype == BaseType::FLOAT) {
                IRgenRetImmFloat(B, LLVMType::FLOAT32, 0);
            }
        }
    }
}

void IRgenerator ::AddLibFunctionDeclare() {
    FunctionDeclareInstruction *getint = new FunctionDeclareInstruction(I32, "getint");
    llvmIR.function_declare.push_back(getint);

    FunctionDeclareInstruction *getchar = new FunctionDeclareInstruction(I32, "getch");
    llvmIR.function_declare.push_back(getchar);

    FunctionDeclareInstruction *getfloat = new FunctionDeclareInstruction(FLOAT32, "getfloat");
    llvmIR.function_declare.push_back(getfloat);

    FunctionDeclareInstruction *getarray = new FunctionDeclareInstruction(I32, "getarray");
    getarray->InsertFormal(PTR);
    llvmIR.function_declare.push_back(getarray);

    FunctionDeclareInstruction *getfloatarray = new FunctionDeclareInstruction(I32, "getfarray");
    getfloatarray->InsertFormal(PTR);
    llvmIR.function_declare.push_back(getfloatarray);

    FunctionDeclareInstruction *putint = new FunctionDeclareInstruction(VOID_TYPE, "putint");
    putint->InsertFormal(I32);
    llvmIR.function_declare.push_back(putint);

    FunctionDeclareInstruction *putch = new FunctionDeclareInstruction(VOID_TYPE, "putch");
    putch->InsertFormal(I32);
    llvmIR.function_declare.push_back(putch);

    FunctionDeclareInstruction *putfloat = new FunctionDeclareInstruction(VOID_TYPE, "putfloat");
    putfloat->InsertFormal(FLOAT32);
    llvmIR.function_declare.push_back(putfloat);

    FunctionDeclareInstruction *putarray = new FunctionDeclareInstruction(VOID_TYPE, "putarray");
    putarray->InsertFormal(I32);
    putarray->InsertFormal(PTR);
    llvmIR.function_declare.push_back(putarray);

    FunctionDeclareInstruction *putfarray = new FunctionDeclareInstruction(VOID_TYPE, "putfarray");
    putfarray->InsertFormal(I32);
    putfarray->InsertFormal(PTR);
    llvmIR.function_declare.push_back(putfarray);

    FunctionDeclareInstruction *putf = new FunctionDeclareInstruction(VOID_TYPE, "putf");
    putf->InsertFormal(PTR);
    llvmIR.function_declare.push_back(putf);

    FunctionDeclareInstruction *starttime = new FunctionDeclareInstruction(VOID_TYPE, "_sysy_starttime");
    starttime->InsertFormal(I32);
    llvmIR.function_declare.push_back(starttime);

    FunctionDeclareInstruction *stoptime = new FunctionDeclareInstruction(VOID_TYPE, "_sysy_stoptime");
    stoptime->InsertFormal(I32);
    llvmIR.function_declare.push_back(stoptime);

    FunctionDeclareInstruction *llvm_memset = new FunctionDeclareInstruction(VOID_TYPE, "llvm.memset.p0.i32");
    llvm_memset->InsertFormal(PTR);
    llvm_memset->InsertFormal(I8);
    llvm_memset->InsertFormal(I32);
    llvm_memset->InsertFormal(I1);
    llvmIR.function_declare.push_back(llvm_memset);

    FunctionDeclareInstruction *llvm_ll_add_mod = new FunctionDeclareInstruction(VOID_TYPE, "___llvm_ll_add_mod");
    llvm_ll_add_mod->InsertFormal(I32);
    llvm_ll_add_mod->InsertFormal(I32);
    llvm_ll_add_mod->InsertFormal(I32);
    llvmIR.function_declare.push_back(llvm_ll_add_mod);

    FunctionDeclareInstruction *llvm_umax = new FunctionDeclareInstruction(I32, "llvm.umax.i32");
    llvm_umax->InsertFormal(I32);
    llvm_umax->InsertFormal(I32);
    llvmIR.function_declare.push_back(llvm_umax);

    FunctionDeclareInstruction *llvm_umin = new FunctionDeclareInstruction(I32, "llvm.umin.i32");
    llvm_umin->InsertFormal(I32);
    llvm_umin->InsertFormal(I32);
    llvmIR.function_declare.push_back(llvm_umin);

    FunctionDeclareInstruction *llvm_smax = new FunctionDeclareInstruction(I32, "llvm.smax.i32");
    llvm_smax->InsertFormal(I32);
    llvm_smax->InsertFormal(I32);
    llvmIR.function_declare.push_back(llvm_smax);

    FunctionDeclareInstruction *llvm_smin = new FunctionDeclareInstruction(I32, "llvm.smin.i32");
    llvm_smin->InsertFormal(I32);
    llvm_smin->InsertFormal(I32);
    llvmIR.function_declare.push_back(llvm_smin);

    FunctionDeclareInstruction *llvm_fmin = new FunctionDeclareInstruction(FLOAT32, "___llvm_fmin_f32");
    llvm_fmin->InsertFormal(FLOAT32);
    llvm_fmin->InsertFormal(FLOAT32);
    llvmIR.function_declare.push_back(llvm_fmin);

    FunctionDeclareInstruction *llvm_fmax = new FunctionDeclareInstruction(FLOAT32, "___llvm_fmax_f32");
    llvm_fmax->InsertFormal(FLOAT32);
    llvm_fmax->InsertFormal(FLOAT32);
    llvmIR.function_declare.push_back(llvm_fmax);
}

// 辅助函数：递归展平初始化列表
// void flattenInitList(InitVal* init, std::vector<Exp*>& result) {
//     if (!init) return;
    
//     if (std::holds_alternative<std::unique_ptr<Exp>>(init->value)) {
//         auto& expr = std::get<std::unique_ptr<Exp>>(init->value);
//         result.push_back(expr.get());
//     } else {
//         auto& list = std::get<std::vector<std::unique_ptr<InitVal>>>(init->value);
//         for (auto& item : list) {
//             flattenInitList(item.get(), result);
//         }
//     }
// }

// void IRgenerator::handleArrayInitializer(InitVal* init, int base_reg, VarAttribute& attr, const std::vector<int>& dims) {
//     if (!init) return;

//     // 展平初始化列表
//     std::vector<Exp*> exprs;
//     flattenInitList(init, exprs);

//     // 计算数组总容量
//     size_t total_capacity = 1;
//     for (int d : dims) {
//         total_capacity *= d;
//     }

//     // 按行优先顺序初始化数组元素
//     for (size_t flat_idx = 0; flat_idx < exprs.size() && flat_idx < total_capacity; flat_idx++) {
//         // 计算多维索引
//         std::vector<int> indices(dims.size(), 0);
//         size_t temp = flat_idx;
//         for (int j = dims.size() - 1; j >= 0; j--) {
//             indices[j] = temp % dims[j];
//             temp /= dims[j];
//         }

//         // 构建GEP索引
//         std::vector<Operand> gep_indices;
//         gep_indices.push_back(new ImmI32Operand(0)); // 数组基址
//         for (int idx_val : indices) {
//             gep_indices.push_back(new ImmI32Operand(idx_val));
//         }

//         // 生成GEP指令
//         int ptr_reg = newReg();
//         IRgenGetElementptr(getCurrentBlock(), Type2LLvm[attr.type], ptr_reg, 
//                           GetNewRegOperand(base_reg), dims, gep_indices);

//         // 计算初始化值
//         require_address = false;
//         exprs[flat_idx]->accept(*this);
//         int init_reg = max_reg;
//         Operand value;

//         if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
//             value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
//         } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
//             value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
//         } else if (isPointer(init_reg)) {
//             int value_reg = newReg();
//             IRgenLoad(getCurrentBlock(), Type2LLvm[attr.type], value_reg, GetNewRegOperand(init_reg));
//             value = GetNewRegOperand(value_reg);
//         } else {
//             value = GetNewRegOperand(init_reg);
//         }

//         // 存储初始化值
//         IRgenStore(getCurrentBlock(), Type2LLvm[attr.type], value, GetNewRegOperand(ptr_reg));
//     }
// }

void IRgenerator::handleArrayInitializer(InitVal* init, int base_reg, VarAttribute& attr, const std::vector<int>& dims, size_t dim_idx) {
    if (!init) return;

    LLVMBlock B = getCurrentBlock();
    //LLVMType type = Type2LLvm[static_cast<int>(attr.type)];
    LLVMType type = Type2LLvm[attr.type];

    if (std::holds_alternative<std::unique_ptr<Exp>>(init->value)) {
        auto& expr = std::get<std::unique_ptr<Exp>>(init->value);
        require_address = false; // Ensure expression yields a value
        expr->accept(*this);
        int init_reg = max_reg;
        Operand value;

        if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
            value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
        } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
            value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
        } else if (isPointer(init_reg)) {
            // Load the value from the pointer
            int value_reg = newReg();
            IRgenLoad(B, type, value_reg, GetNewRegOperand(init_reg));
            value = GetNewRegOperand(value_reg);
        } else {
            value = GetNewRegOperand(init_reg);
        }

        std::vector<Operand> indices;
        indices.push_back(new ImmI32Operand(0));
        for (size_t i = 0; i < dim_idx; ++i) {
            indices.push_back(new ImmI32Operand(0));
        }
        indices.push_back(new ImmI32Operand(0));
        int ptr_reg = newReg();
        IRgenGetElementptr(B, type, ptr_reg, GetNewRegOperand(base_reg), dims, indices);
        IRgenStore(B, type, value, GetNewRegOperand(ptr_reg));
    } else {
        auto& init_list = std::get<std::vector<std::unique_ptr<InitVal>>>(init->value);
        size_t flat_idx = 0;

        for (size_t i = 0; i < init_list.size() && i < static_cast<size_t>(dims[dim_idx]); ++i) {
            std::vector<Operand> indices;
            indices.push_back(new ImmI32Operand(0));
            for (size_t j = 0; j < dim_idx; ++j) {
                indices.push_back(new ImmI32Operand(0));
            }
            indices.push_back(new ImmI32Operand(static_cast<int>(i)));

            if (dim_idx + 1 < dims.size()) {
                // Nested array
                int sub_reg = newReg();
                IRgenGetElementptr(B, type, sub_reg, GetNewRegOperand(base_reg), dims, indices);
                std::vector<int> sub_dims(dims.begin() + dim_idx + 1, dims.end());
                handleArrayInitializer(init_list[i].get(), sub_reg, attr, sub_dims, 0);
            } else {
                // Leaf element
                require_address = false; // Ensure initializer yields a value
                init_list[i]->accept(*this);
                int init_reg = max_reg;
                Operand value;
                if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                    value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
                } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
                    value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
                } else if (isPointer(init_reg)) {
                    // Load the value from the pointer
                    int value_reg = newReg();
                    IRgenLoad(B, type, value_reg, GetNewRegOperand(init_reg));
                    value = GetNewRegOperand(value_reg);
                } else {
                    value = GetNewRegOperand(init_reg);
                }
                int elem_ptr_reg = newReg();
                IRgenGetElementptr(B, type, elem_ptr_reg, GetNewRegOperand(base_reg), dims, indices);
                IRgenStore(B, type, value, GetNewRegOperand(elem_ptr_reg));
                flat_idx++;
            }
        }
    }
}

LLVMBlock IRgenerator::getCurrentBlock() {
    return llvmIR.GetBlock(function_now, now_label);
}

int IRgenerator::newReg() { return (++current_reg_counter); }

int IRgenerator::newLabel() { return (++max_label); }

bool IRgenerator::isGlobalScope() { return function_now == nullptr; }

// New helper function to evaluate constant expressions
std::optional<int> IRgenerator::evaluateConstExpression(Exp* expr) {
    if (auto* num = dynamic_cast<Number*>(expr)) {
        if (std::holds_alternative<int>(num->value)) {
            return std::get<int>(num->value);
        }
    } else if (auto* unary = dynamic_cast<UnaryExp*>(expr)) {
        auto operand_val = evaluateConstExpression(unary->operand.get());
        if (operand_val) {
            switch (unary->op) {
                case UnaryOp::PLUS: return *operand_val;
                case UnaryOp::MINUS: return -*operand_val;
                case UnaryOp::NOT: return !*operand_val;
            }
        }
    } else if (auto* binary = dynamic_cast<BinaryExp*>(expr)) {
        auto lhs_val = evaluateConstExpression(binary->lhs.get());
        auto rhs_val = evaluateConstExpression(binary->rhs.get());
        if (lhs_val && rhs_val) {
            switch (binary->op) {
                case BinaryOp::ADD: return *lhs_val + *rhs_val;
                case BinaryOp::SUB: return *lhs_val - *rhs_val;
                case BinaryOp::MUL: return *lhs_val * *rhs_val;
                case BinaryOp::DIV: 
                    if (*rhs_val != 0) return *lhs_val / *rhs_val;
                    break;
                case BinaryOp::MOD: 
                    if (*rhs_val != 0) return *lhs_val % *rhs_val;
                    break;
                default: break;
            }
        }
    } else if (auto* lval = dynamic_cast<LVal*>(expr)) {
        SymbolInfo* sym = str_table.lookup(lval->name);
        if (sym && sym->kind == SymbolKind::CONSTANT && lval->indices.empty()) {
            if (auto val = sym->getConstantValue<int>()) {
                return *val;
            }
        }
    }
    return std::nullopt;
}

// 浮点常量表达式求值
std::optional<float> IRgenerator::evaluateConstExpressionFloat(Exp *expr)
{
    if (auto *num = dynamic_cast<Number *>(expr))
    {
        if (std::holds_alternative<float>(num->value))
        {
            return std::get<float>(num->value);
        }
        else if (std::holds_alternative<int>(num->value))
        {
            // 整数到浮点数转换
            return static_cast<float>(std::get<int>(num->value));
        }
    }
    else if (auto *unary = dynamic_cast<UnaryExp *>(expr))
    {
        auto operand_val = evaluateConstExpressionFloat(unary->operand.get());
        if (operand_val)
        {
            switch (unary->op)
            {
            case UnaryOp::PLUS:
                return *operand_val;
            case UnaryOp::MINUS:
                return -*operand_val;
            case UnaryOp::NOT:
                return static_cast<float>(!static_cast<bool>(*operand_val));
            }
        }
    }
    else if (auto *binary = dynamic_cast<BinaryExp *>(expr))
    {
        auto lhs_val = evaluateConstExpressionFloat(binary->lhs.get());
        auto rhs_val = evaluateConstExpressionFloat(binary->rhs.get());
        if (lhs_val && rhs_val)
        {
            switch (binary->op)
            {
            case BinaryOp::ADD:
                return *lhs_val + *rhs_val;
            case BinaryOp::SUB:
                return *lhs_val - *rhs_val;
            case BinaryOp::MUL:
                return *lhs_val * *rhs_val;
            case BinaryOp::DIV:
                if (*rhs_val != 0.0f)
                    return *lhs_val / *rhs_val;
                break;
            case BinaryOp::MOD:
                if (*rhs_val != 0.0f)
                    return fmodf(*lhs_val, *rhs_val);
                break;
            default:
                break;
            }
        }
    }
    else if (auto *lval = dynamic_cast<LVal *>(expr))
    {
        SymbolInfo *sym = str_table.lookup(lval->name);
        if (sym && sym->kind == SymbolKind::CONSTANT && lval->indices.empty())
        {
            if (auto val = sym->getConstantValue<float>())
            {
                return *val;
            }
            else if (auto val = sym->getConstantValue<int>())
            {
                // 整数常量转换为浮点数
                return static_cast<float>(*val);
            }
        }
    }
    return std::nullopt;
}


// New helper function to infer expression type
std::shared_ptr<Type> IRgenerator::inferExpressionType(Exp* expression) {
    if (auto* lval = dynamic_cast<LVal*>(expression)) {
        SymbolInfo* sym = str_table.lookup(lval->name);
        if (sym) {
            if (lval->indices.empty()) {
                return sym->type;
            } else {
                auto* arr_type = dynamic_cast<ArrayType*>(sym->type.get());
                if (arr_type && arr_type->dimensions.size() > lval->indices.size()) {
                    std::vector<int> remaining_dims(arr_type->dimensions.begin() + lval->indices.size(), arr_type->dimensions.end());
                    return makeArrayType(arr_type->element_type, remaining_dims);
                } else if (arr_type && arr_type->dimensions.size() == lval->indices.size()) {
                    return arr_type->element_type;
                }
            }
        }
    } else if (auto* num = dynamic_cast<Number*>(expression)) {
        if (std::holds_alternative<int>(num->value)) {
            return makeBasicType(BaseType::INT);
        } else {
            return makeBasicType(BaseType::FLOAT);
        }
    } else if (auto* unary = dynamic_cast<UnaryExp*>(expression)) {
        return inferExpressionType(unary->operand.get());
    } else if (auto* binary = dynamic_cast<BinaryExp*>(expression)) {
        auto lhs_type = inferExpressionType(binary->lhs.get());
        auto rhs_type = inferExpressionType(binary->rhs.get());
        if (lhs_type && rhs_type) {
            if (dynamic_cast<BasicType*>(lhs_type.get()) && dynamic_cast<BasicType*>(rhs_type.get())) {
                return lhs_type; // Simplified: assumes compatible types
            }
        }
    } else if (auto* call = dynamic_cast<FunctionCall*>(expression)) {
        SymbolInfo* sym = str_table.lookup(call->function_name);
        if (sym && sym->kind == SymbolKind::FUNCTION) {
            auto* func_type = dynamic_cast<FunctionType*>(sym->type.get());
            if (func_type) return func_type->return_type;
        }
    }
    return nullptr;
}

// New helper function to check if a register is a pointer
bool IRgenerator::isPointer(int reg) {
    auto it = irgen_table.RegTable.find(reg);
    if (it == irgen_table.RegTable.end()) return false;

    // Check if the register is associated with a variable in the symbol table
    for (const auto& [name, reg_id] : irgen_table.name_to_reg) {
        if (reg_id == reg) {
            SymbolInfo* sym = str_table.lookup(name);
            if (sym && (sym->kind == SymbolKind::VARIABLE || sym->kind == SymbolKind::PARAMETER)) {
                // If it's a variable or parameter with no indices, check if it's an array or explicitly a pointer
                auto* arr_type = dynamic_cast<ArrayType*>(sym->type.get());
                if (arr_type || sym->is_array_pointer || sym->kind == SymbolKind::VARIABLE) {
                    return true;
                }
            }
            break;
        }
    }
    // If the register has dimensions, it's a pointer (e.g., array base)
    return !it->second.dims.empty();
}


void IRgenerator::visit(CompUnit &node) {
    AddLibFunctionDeclare();
    for (auto &item : node.items) {
        if (auto decl = std::get_if<std::unique_ptr<Decl>>(&item)) {
            (*decl)->accept(*this);
        } else if (auto funcDef = std::get_if<std::unique_ptr<FuncDef>>(&item)) {
            (*funcDef)->accept(*this);
        }
    }
}

void IRgenerator::visit(ConstDecl &node) {
    BaseType prev_type = current_type;
    current_type = node.type;
    for (auto &def : node.definitions) {
        def->accept(*this);
    }
    current_type = prev_type;
}


// 辅助函数：递归展平常量初始化列表
void IRgenerator::flattenConstInit(ConstInitVal* init, std::vector<std::variant<int, float>>& result, BaseType type) {
    if (!init) return;
    
    if (std::holds_alternative<std::unique_ptr<Exp>>(init->value)) {
        auto& expr = std::get<std::unique_ptr<Exp>>(init->value);
        auto int_val = evaluateConstExpression(expr.get());  // 移除类名前缀
        auto float_val = evaluateConstExpressionFloat(expr.get());  // 移除类名前缀
        
        if (int_val && type == BaseType::INT) {
            result.push_back(*int_val);
        } else if (float_val && type == BaseType::FLOAT) {
            result.push_back(*float_val);
        } else {
            // 默认值
            result.push_back(type == BaseType::INT ? 0 : 0.0f);
        }
    } else {
        auto& list = std::get<std::vector<std::unique_ptr<ConstInitVal>>>(init->value);
        for (auto& item : list) {
            flattenConstInit(item.get(), result, type);
        }
    }
}

void IRgenerator::visit(ConstDef &node) {
    if (isGlobalScope()) {
        VarAttribute attr;
        attr.type = current_type;
        attr.ConstTag = true;
        
        // 处理数组维度
        for (auto &dim : node.array_dimensions) {
            auto val = evaluateConstExpression(dim.get());
            attr.dims.push_back(val.value_or(1));
        }

        // 处理初始化器
        if (auto *const_init = dynamic_cast<ConstInitVal *>(node.initializer.get())) {
            if (!attr.dims.empty()) {
                // 多维数组初始化
                std::vector<std::variant<int, float>> flat_values;
                flattenConstInit(const_init, flat_values, current_type);
                
                // 计算总元素数量
                size_t total_elements = 1;
                for (auto d : attr.dims) total_elements *= d;
                
                // 填充初始化值
                for (size_t i = 0; i < total_elements; i++) {
                    if (i < flat_values.size()) {
                        if (auto* ival = std::get_if<int>(&flat_values[i])) {
                            attr.IntInitVals.push_back(*ival);
                        } else if (auto* fval = std::get_if<float>(&flat_values[i])) {
                            attr.FloatInitVals.push_back(*fval);
                        }
                    } else {
                        // 填充默认值
                        if (current_type == BaseType::INT) {
                            attr.IntInitVals.push_back(0);
                        } else {
                            attr.FloatInitVals.push_back(0.0f);
                        }
                    }
                }
            } else {
                // 标量初始化
                if (std::holds_alternative<std::unique_ptr<Exp>>(const_init->value)) {
                    auto &expr = std::get<std::unique_ptr<Exp>>(const_init->value);
                    if (current_type == BaseType::INT) {
                        auto int_val = evaluateConstExpression(expr.get());
                        if (int_val)
                        {
                            attr.IntInitVals.push_back(*int_val);
                        }
                        else
                        {
                            std::cerr << "Error: Cannot evaluate constant expression for " << node.name << std::endl;
                            attr.IntInitVals.push_back(0);
                        }
                    } else if (current_type == BaseType::FLOAT) {
                        auto float_val = evaluateConstExpressionFloat(expr.get());
                        if (float_val)
                    {
                        attr.FloatInitVals.push_back(*float_val);
                    }
                    else
                    {
                        std::cerr << "Error: Cannot evaluate constant expression for " << node.name << std::endl;
                        attr.FloatInitVals.push_back(0.0f);
                    }
                    }
                }
            }
        }
        
        llvmIR.global_def.push_back(new GlobalVarDefineInstruction(node.name, Type2LLvm[attr.type], attr));

        // 添加到符号表
        SymbolInfo *sym = str_table.lookup(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::CONSTANT, 
                                                         makeBasicType(attr.type), 
                                                         node.name, 
                                                         true);
            
            // 设置常量值
            if (attr.IntInitVals.size() > 0) {
                sym_info->setConstantValue(attr.IntInitVals[0]);
            } else if (attr.FloatInitVals.size() > 0) {
                sym_info->setConstantValue(attr.FloatInitVals[0]);
            }
            
            // 设置数组维度
            sym_info->setArrayDimensions(std::vector<int>(attr.dims.begin(), attr.dims.end()));
            str_table.insert(node.name, sym_info);
        }
    } else {
        // 局部常量初始化
        int reg = newReg();
        VarAttribute attr;
        attr.type = current_type;
        attr.ConstTag = true;
        
        // 分配内存
        if (!node.array_dimensions.empty()) {
            std::vector<int> dims;
            for (auto &dim : node.array_dimensions) {
                auto val = evaluateConstExpression(dim.get());
                dims.push_back(val.value_or(1));
            }
            IRgenAllocaArray(getCurrentBlock(), Type2LLvm[attr.type], reg, dims);
            attr.dims = std::vector<size_t>(dims.begin(), dims.end());
        } else {
            IRgenAlloca(getCurrentBlock(), Type2LLvm[attr.type], reg);
        }
        
        irgen_table.RegTable[reg] = attr;
        irgen_table.name_to_reg[node.name] = reg;
        
        // 处理初始化
        if (node.initializer) {
            require_address = false;
            node.initializer->accept(*this);
            int init_reg = max_reg;
            
            if (attr.dims.empty()) {
                // 标量初始化
                Operand value;
                if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                    value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
                } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
                    value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
                } else {
                    value = GetNewRegOperand(init_reg);
                }
                IRgenStore(getCurrentBlock(), Type2LLvm[attr.type], value, GetNewRegOperand(reg));
            } else {
                // 数组初始化
                handleArrayInitializer(dynamic_cast<InitVal*>(node.initializer.get()), 
                                      reg, 
                                      attr, 
                                      std::vector<int>(attr.dims.begin(), attr.dims.end()), 
                                      0);
            }
        }
        
        // 添加到符号表
        SymbolInfo *sym = str_table.lookupCurrent(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::CONSTANT, 
                                                         makeBasicType(attr.type), 
                                                         node.name, 
                                                         true);
            
            // 设置常量值
            if (irgen_table.RegTable[reg].IntInitVals.size() > 0) {
                sym_info->setConstantValue(irgen_table.RegTable[reg].IntInitVals[0]);
            } else if (irgen_table.RegTable[reg].FloatInitVals.size() > 0) {
                sym_info->setConstantValue(irgen_table.RegTable[reg].FloatInitVals[0]);
            }
            
            // 设置数组维度
            std::vector<int> dims_int(attr.dims.begin(), attr.dims.end());
            sym_info->setArrayDimensions(dims_int);
            
            str_table.insert(node.name, sym_info);
        }
    }
}


void IRgenerator::visit(VarDecl &node) {
    BaseType prev_type = current_type;
    current_type = node.type;
    for (auto &def : node.definitions) {
        def->accept(*this);
    }
    current_type = prev_type;
}

void IRgenerator::visit(VarDef &node) {
    if (isGlobalScope()) {
        VarAttribute attr;
        attr.type = current_type;
        for (auto &dim : node.array_dimensions) {
            auto val = evaluateConstExpression(dim.get());
            attr.dims.push_back(val.value_or(1));
        }
        if (node.initializer) {
            (*node.initializer)->accept(*this);
            int init_reg = max_reg;
            if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                attr.IntInitVals = irgen_table.RegTable[init_reg].IntInitVals;
            } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
                attr.FloatInitVals = irgen_table.RegTable[init_reg].FloatInitVals;
            }
        }
        //llvmIR.global_def.push_back(new GlobalVarDefineInstruction(node.name, Type2LLvm[static_cast<int>(attr.type)], attr));
        llvmIR.global_def.push_back(new GlobalVarDefineInstruction(node.name, Type2LLvm[attr.type], attr));

        // Add to symbol table
        SymbolInfo* sym = str_table.lookup(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::VARIABLE, makeBasicType(attr.type), node.name, node.initializer.has_value());
            sym_info->setArrayDimensions(std::vector<int>(attr.dims.begin(), attr.dims.end()));
            str_table.insert(node.name, sym_info);
        }
    } else {
        int reg = newReg();
        VarAttribute attr;
        attr.type = current_type;
        attr.ConstTag = false; // 明确标记为非常量
        std::vector<int> dims;
        for (auto &dim : node.array_dimensions) {
            auto val = evaluateConstExpression(dim.get());
            if (val)
            {
                dims.push_back(*val);
            }
            else
            {
                dims.push_back(1); // 非常量维度的回退值
            }
        }
        attr.dims = std::vector<size_t>(dims.begin(), dims.end());
        if (!dims.empty()) {
            //IRgenAllocaArray(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], reg, dims);
            IRgenAllocaArray(getCurrentBlock(), Type2LLvm[attr.type], reg, dims);
        } else {
            //IRgenAlloca(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], reg);
            IRgenAlloca(getCurrentBlock(), Type2LLvm[attr.type], reg);
        }
        irgen_table.RegTable[reg] = attr;
        irgen_table.name_to_reg[node.name] = reg;
        if (node.initializer) {
            if (dims.empty()) {
                // Scalar variable initialization
                require_address = false;
                (*node.initializer)->accept(*this);
                int init_reg = max_reg;
                VarAttribute init_attr = irgen_table.RegTable[init_reg];
                Operand value;
                if (init_attr.IntInitVals.size() > 0) {
                    value = new ImmI32Operand(init_attr.IntInitVals[0]);
                } else if (init_attr.FloatInitVals.size() > 0) {
                    value = new ImmF32Operand(init_attr.FloatInitVals[0]);
                } else if (isPointer(init_reg)) {
                    int value_reg = newReg();
                    //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value_reg, GetNewRegOperand(init_reg));
                    IRgenLoad(getCurrentBlock(), Type2LLvm.at(attr.type), value_reg, GetNewRegOperand(init_reg));
                    value = GetNewRegOperand(value_reg);
                } else {
                    value = GetNewRegOperand(init_reg);
                }
                IRgenStore(getCurrentBlock(), Type2LLvm.at(attr.type), value, GetNewRegOperand(reg));
                //IRgenStore(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value, GetNewRegOperand(reg));
            } else {
                // Array initialization
               handleArrayInitializer(node.initializer->get(), reg, attr, dims, 0);
               //handleArrayInitializer(node.initializer->get(), reg, attr, dims);
            }
        }
        
        // Add to symbol table
        SymbolInfo* sym = str_table.lookupCurrent(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::VARIABLE, makeBasicType(attr.type), node.name, node.initializer.has_value());
            sym_info->setArrayDimensions(dims);
            str_table.insert(node.name, sym_info);
        }
    }
}


void IRgenerator::visit(FuncDef &node) {
    //function_now = new FunctionDefineInstruction(Type2LLvm[static_cast<int>(node.return_type)], node.name);
    function_now = new FunctionDefineInstruction(Type2LLvm.at(node.return_type), node.name);
    function_returntype = node.return_type;
    llvmIR.NewFunction(function_now);
    now_label = 0;
    current_reg_counter = -1; // Reset register counter
    max_label = 0;  // 重置标签计数器
    llvmIR.NewBlock(function_now, now_label);

    // Symbol table setup
    std::vector<std::shared_ptr<Type>> param_types;
    for (const auto& param : node.parameters) {
        param_types.push_back(makeBasicType(param->type));
    }
    auto func_type = makeFunctionType(makeBasicType(node.return_type), param_types);
    auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::FUNCTION, func_type, node.name, true);
    str_table.insert(node.name, sym_info);
    
    // 第一步：处理参数声明
    for (auto &param : node.parameters) {
        param->accept(*this);
    }
    // 第二步：在入口块为标量参数分配空间并存储初始值
    for (auto &param : node.parameters) {
        std::string param_name = param->name;
        auto it = irgen_table.name_to_reg.find(param_name);
        if (it == irgen_table.name_to_reg.end()) continue;
        
        int param_reg = it->second;
        VarAttribute &attr = irgen_table.RegTable[param_reg];
        
         // 判断是否为数组参数
         bool is_array_param = !attr.dims.empty() || param->is_array_pointer;
        
        if (is_array_param) {
            // 数组参数 - 分配指针空间
            int alloca_reg = newReg();
            IRgenAlloca(getCurrentBlock(), PTR, alloca_reg);
            
            // 存储指针参数
            IRgenStore(getCurrentBlock(), PTR, GetNewRegOperand(param_reg), 
                      GetNewRegOperand(alloca_reg));
            
            // 更新符号表映射
            irgen_table.name_to_reg[param_name] = alloca_reg;
            
            // 更新寄存器属性
            irgen_table.RegTable[alloca_reg] = attr;

        } else {
            // 标量参数 - 原有逻辑不变
            int alloca_reg = newReg();
            LLVMType param_type = Type2LLvm.at(attr.type);
            IRgenAlloca(getCurrentBlock(), param_type, alloca_reg);
            IRgenStore(getCurrentBlock(), param_type, GetNewRegOperand(param_reg), 
                      GetNewRegOperand(alloca_reg));
            irgen_table.name_to_reg[param_name] = alloca_reg;
            irgen_table.RegTable[alloca_reg] = attr;
        }
    }
    // 处理函数体
    if(node.body){
    node.body->accept(*this);
    }
    AddNoReturnBlock();
    function_now = nullptr;
}


// void IRgenerator::visit(FuncFParam &node) {
//     int reg = newReg();
//     VarAttribute attr;
//     attr.type = node.type;
//     if (node.is_array_pointer || !node.array_dimensions.empty()) {
//         // Array parameter
//         attr.dims.push_back(0); // Mark as pointer
//         function_now->InsertFormal(PTR);
//     } else {
//         // Scalar parameter
//         //function_now->InsertFormal(Type2LLvm[static_cast<int>(node.type)]);
//         function_now->InsertFormal(Type2LLvm.at(node.type));
//     }
//     //function_now->formals_reg.push_back(GetNewRegOperand(reg));
//     irgen_table.RegTable[reg] = attr;
//     irgen_table.name_to_reg[node.name] = reg;

//     // Add parameter to symbol table
//     auto param_type = node.is_array_pointer || !node.array_dimensions.empty() ?
//                       makeArrayType(makeBasicType(node.type), {-1}) :
//                       makeBasicType(node.type);
//     auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::PARAMETER, param_type, node.name, true);
//     sym_info->is_array_pointer = node.is_array_pointer || !node.array_dimensions.empty();
//     str_table.insert(node.name, sym_info);
// }

void IRgenerator::visit(FuncFParam &node) {
    int reg = newReg();
    VarAttribute attr;
    attr.type = node.type;
    
    // 修改点：正确设置数组参数类型
    if (node.is_array_pointer || !node.array_dimensions.empty()) {
        function_now->InsertFormal(PTR); // 数组参数作为指针传递
        attr.dims.push_back(0); // 标记为指针
    } else {
        function_now->InsertFormal(Type2LLvm.at(node.type));
    }
    
    irgen_table.RegTable[reg] = attr;
    irgen_table.name_to_reg[node.name] = reg;


    auto param_type = node.is_array_pointer || !node.array_dimensions.empty() ?
                      makeArrayType(makeBasicType(node.type), {-1}) :
                      makeBasicType(node.type);
    auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::PARAMETER, param_type, node.name, true);
    sym_info->is_array_pointer = node.is_array_pointer || !node.array_dimensions.empty();
    str_table.insert(node.name, sym_info);
}

void IRgenerator::visit(Block &node) {
    str_table.enterScope();
    for (auto &item : node.items) {
        if (auto stmt = std::get_if<std::unique_ptr<Stmt>>(&item)) {
            (*stmt)->accept(*this);
        } else if (auto decl = std::get_if<std::unique_ptr<Decl>>(&item)) {
            (*decl)->accept(*this);
        }
    }
    str_table.exitScope();
}

void IRgenerator::visit(IfStmt &node) {
    //max_label=now_label;
    //now_label = max_label;

    // int saved_now_label = now_label;
    // int saved_max_label = max_label;
    if(max_label==0){
        max_label=1;
    }
    // std::cout<<"now_label: " << now_label << std::endl;
    // std::cout<<"max_label: " << max_label << std::endl;
      // 创建标签：then块、else块和合并块
    //   int then_label = newLabel();
    //   std::cout<< "then_label: " << then_label << std::endl;
    //   int else_label = newLabel();
    //     std::cout<< "else_label: " << else_label << std::endl;
    //   int merge_label = newLabel();
    //   std::cout<< "merge_label: " << merge_label << std::endl;
    //max_label++;
    // 生成条件表达式
    node.condition->accept(*this);
    int cond_reg_if = max_reg;
    LLVMBlock B_if = getCurrentBlock();

    // 如果条件类型是i32（整数），转换为i1（布尔）
    if (RegLLVMTypeMap[cond_reg_if] == LLVMType::I32) {
        std::cout<< "Converting i32 condition to i1" << std::endl;
        int tmp_reg = newReg();
        IRgenIcmp(B_if, IcmpCond::ne, cond_reg_if, 0, tmp_reg);
        cond_reg_if = tmp_reg;
        RegLLVMTypeMap[cond_reg_if] = LLVMType::I1;
    }
    
    // // 创建标签：then块、else块和合并块
    // int then_label = newLabel();
    // int else_label = newLabel();
    // int merge_label = newLabel();

    // 条件跳转指令
    //IRgenBrCond(B, cond_reg, then_label, else_label);

    //IRgenBrCond(getCurrentBlock(), cond_reg, then_label, else_label);

    int then_label = newLabel();
    // 生成then块
    //llvmIR.NewBlock(function_now, now_label);
    llvmIR.NewBlock(function_now, then_label);
    now_label = then_label;
    node.then_statement->accept(*this);
    LLVMBlock B_then = getCurrentBlock();
    // 如果then块没有终止指令，跳转到合并块
    // if (B->Instruction_list.empty() || 
    //     (!IsBr(B->Instruction_list.back()) && !IsRet(B->Instruction_list.back()))) {
    //     IRgenBRUnCond(B, merge_label);
    // }


    int else_label = newLabel();
    // 生成else块
    //llvmIR.NewBlock(function_now, now_label);
    llvmIR.NewBlock(function_now, else_label);
    now_label = else_label;
    if (node.else_statement) {
        node.else_statement->get()->accept(*this);
      }
    LLVMBlock B_else = getCurrentBlock();
    // 如果else块没有终止指令，跳转到合并块
    // if (B->Instruction_list.empty() || 
    //     (!IsBr(B->Instruction_list.back()) && !IsRet(B->Instruction_list.back()))) {
    //     IRgenBRUnCond(B, merge_label);
    // }
    
    int merge_label = newLabel();
    // 生成合并块
    llvmIR.NewBlock(function_now, merge_label);
    now_label = merge_label;
        // 恢复外层状态
    // now_label = saved_now_label;
    // max_label = saved_max_label;
    IRgenBrCond(B_if, cond_reg_if, then_label, else_label);
       // 如果then块没有终止指令，跳转到合并块
    if (B_then->Instruction_list.empty() || 
        (!IsBr(B_then->Instruction_list.back()) && !IsRet(B_then->Instruction_list.back()))) {
        IRgenBRUnCond(B_then, merge_label);
    }
        // 如果else块没有终止指令，跳转到合并块
    if (B_else->Instruction_list.empty() || 
        (!IsBr(B_else->Instruction_list.back()) && !IsRet(B_else->Instruction_list.back()))) {
        IRgenBRUnCond(B_else, merge_label);
    }
}

void IRgenerator::visit(WhileStmt &node) {
    // if(max_label==0){
    //     max_label=1;
    // }
    // int loop_header = newLabel();
    // int loop_body = newLabel();
    // int loop_end = newLabel();
    // int old_loop_start = loop_start_label;
    // int old_loop_end = loop_end_label;
    // loop_start_label = loop_header;
    // loop_end_label = loop_end;
    
    LLVMBlock B_before = getCurrentBlock();
    // 入口跳转到条件检查
    // if (B_before->Instruction_list.empty() ||
    //     (!IsBr(B_before->Instruction_list.back()) && !IsRet(B_before->Instruction_list.back()))) {
    //     IRgenBRUnCond(B_before, loop_header);
    // }

    int loop_header = newLabel();
    // 循环头：条件判断
    llvmIR.NewBlock(function_now, loop_header);
    LLVMBlock B_header = getCurrentBlock();
    now_label = loop_header;
    node.condition->accept(*this);
    int cond_reg_header = max_reg;
    if (RegLLVMTypeMap[cond_reg_header] == LLVMType::I32) {
        int tmp = newReg();
        IRgenIcmp(B_header, IcmpCond::ne, cond_reg_header, 0, tmp);
        cond_reg_header = tmp;
    }
    // IRgenBrCond(B_header, cond_reg_header, loop_body, loop_end);

    int loop_body = newLabel();
    // 循环体
    llvmIR.NewBlock(function_now, loop_body);
    LLVMBlock B_body = getCurrentBlock();
    now_label = loop_body;
    node.body->accept(*this);
    // 如果循环体末尾未结束，则跳回头部
    // if (B_body->Instruction_list.empty() ||
    //     (!IsBr(B_body->Instruction_list.back()) && !IsRet(B_body->Instruction_list.back()))) {
    //     IRgenBRUnCond(B_body, loop_header);
    // }
    
    int loop_end = newLabel();
    // 循环退出块
    llvmIR.NewBlock(function_now, loop_end);
    LLVMBlock B_end = getCurrentBlock();
    now_label = loop_end;

    // 入口跳转到条件检查
    if (B_before->Instruction_list.empty() ||
        (!IsBr(B_before->Instruction_list.back()) && !IsRet(B_before->Instruction_list.back()))) {
        IRgenBRUnCond(B_before, loop_header);
    }

    IRgenBrCond(B_body, cond_reg_header, loop_body, loop_end);
        // 如果循环体末尾未结束，则跳回头部
    if (B_body->Instruction_list.empty() ||
        (!IsBr(B_body->Instruction_list.back()) && !IsRet(B_body->Instruction_list.back()))) {
        std::cout<<"1"<<std::endl;
        //IRgenBRUnCond(B_body, loop_header);
    }
    IRgenBRUnCond(B_end, loop_header);
    std::cout<<"2"<<std::endl;

    // loop_start_label = old_loop_start;
    // loop_end_label = old_loop_end;
}
void IRgenerator::visit(ExpStmt &node) {
    if (node.expression) {
        (*node.expression)->accept(*this);
    }
}

// void IRgenerator::visit(AssignStmt &node) {
//     require_address = true;
//     node.lvalue->accept(*this);
//     int lvalue_reg = max_reg;
//     VarAttribute lvalue_attr = irgen_table.RegTable[lvalue_reg];
    
//     // 获取左值的基本类型
//     LLVMType type;
//     SymbolInfo* sym = str_table.lookup(node.lvalue->name);
//     if (sym) {
//         if (auto* basic_type = dynamic_cast<BasicType*>(sym->type.get())) {
//             type = Type2LLvm.at(basic_type->type);
//         } else {
//             // 默认为i32类型
//             type = LLVMType::I32;
//         }
//     } else {
//         type = Type2LLvm.at(lvalue_attr.type);
//     }

//     require_address = false;
//     node.rvalue->accept(*this);
//     int rvalue_reg = max_reg;
//     VarAttribute rvalue_attr = irgen_table.RegTable[rvalue_reg];

//     Operand value;
//     if (rvalue_attr.IntInitVals.size() > 0) {
//         value = new ImmI32Operand(rvalue_attr.IntInitVals[0]);
//     } else if (rvalue_attr.FloatInitVals.size() > 0) {
//         value = new ImmF32Operand(rvalue_attr.FloatInitVals[0]);
//     } else if (isPointer(rvalue_reg)) {
//         int value_reg = newReg();
//         IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(rvalue_reg));
//         value = GetNewRegOperand(value_reg);
//     } else {
//         value = GetNewRegOperand(rvalue_reg);
//     }

//     // 直接使用左值寄存器作为指针（不再重新计算地址）
//     IRgenStore(getCurrentBlock(), type, value, GetNewRegOperand(lvalue_reg));
// }

void IRgenerator::visit(AssignStmt &node) {
    require_address = true;
    node.lvalue->accept(*this);
    int lvalue_reg = max_reg;
    VarAttribute lvalue_attr = irgen_table.RegTable[lvalue_reg];
    
    // 获取左值的基本类型
    LLVMType type;
    SymbolInfo* sym = str_table.lookup(node.lvalue->name);
    if (sym) {
        if (auto* basic_type = dynamic_cast<BasicType*>(sym->type.get())) {
            type = Type2LLvm.at(basic_type->type);
        } else {
            type = LLVMType::I32; // 默认类型
        }
    } else {
        type = Type2LLvm.at(lvalue_attr.type);
    }

    require_address = false;
    node.rvalue->accept(*this);
    int rvalue_reg = max_reg;
    VarAttribute rvalue_attr = irgen_table.RegTable[rvalue_reg];

    Operand value;
    if (rvalue_attr.IntInitVals.size() > 0) {
        value = new ImmI32Operand(rvalue_attr.IntInitVals[0]);
    } else if (rvalue_attr.FloatInitVals.size() > 0) {
        value = new ImmF32Operand(rvalue_attr.FloatInitVals[0]);
    } else if (isPointer(rvalue_reg)) {
        int value_reg = newReg();
        IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(rvalue_reg));
        value = GetNewRegOperand(value_reg);
    } else {
        value = GetNewRegOperand(rvalue_reg);
    }

    // +++ 新增：类型检查与转换 +++
    int final_value_reg = -1;
    if (lvalue_attr.type == BaseType::INT && rvalue_attr.type == BaseType::FLOAT) {
        // 浮点转整数
        final_value_reg = newReg();
        IRgenFptosi(getCurrentBlock(), rvalue_reg, final_value_reg);
        value = GetNewRegOperand(final_value_reg);
    } else if (lvalue_attr.type == BaseType::FLOAT && rvalue_attr.type == BaseType::INT) {
        // 整数转浮点
        final_value_reg = newReg();
        IRgenSitofp(getCurrentBlock(), rvalue_reg, final_value_reg);
        value = GetNewRegOperand(final_value_reg);
    } else {
        // 类型相同，无需转换
        final_value_reg = rvalue_reg;
    }

    // 直接使用左值寄存器作为指针
    IRgenStore(getCurrentBlock(), type, value, GetNewRegOperand(lvalue_reg));
}



void IRgenerator::visit(ReturnStmt &node) {
    if (node.expression) {
        require_address = false;
        (*node.expression)->accept(*this);
        int ret_reg = max_reg;
        LLVMType ret_type = Type2LLvm.at(function_returntype);
        VarAttribute ret_attr = irgen_table.RegTable[ret_reg];

        if (ret_attr.IntInitVals.size() > 0) {
            IRgenRetImmInt(getCurrentBlock(), ret_type, ret_attr.IntInitVals[0]);
        } else if (ret_attr.FloatInitVals.size() > 0) {
            IRgenRetImmFloat(getCurrentBlock(), ret_type, ret_attr.FloatInitVals[0]);
        } else if (node.expression.has_value() && dynamic_cast<FunctionCall*>((*node.expression).get())) {
            IRgenRetReg(getCurrentBlock(), ret_type, ret_reg);
        } else if (isPointer(ret_reg)) {
            int value_reg = newReg();
            IRgenLoad(getCurrentBlock(), ret_type, value_reg, GetNewRegOperand(ret_reg));
            IRgenRetReg(getCurrentBlock(), ret_type, value_reg);
        } else if (dynamic_cast<LVal*>((*node.expression).get())) {
            // 检查是否是全局常量数组元素
            LVal* lval = dynamic_cast<LVal*>((*node.expression).get());
            SymbolInfo* sym = str_table.lookup(lval->name);
            
            if (sym && sym->kind == SymbolKind::CONSTANT && !lval->indices.empty()) {
                // 全局常量数组元素 - 直接返回值
                IRgenRetReg(getCurrentBlock(), ret_type, ret_reg);
            } else {
                // 局部常量变量 - 需要加载值
                // int value_reg = newReg();
                // IRgenLoad(getCurrentBlock(), ret_type, value_reg, GetNewRegOperand(ret_reg));
                //IRgenRetReg(getCurrentBlock(), ret_type, value_reg);
                IRgenRetReg(getCurrentBlock(), ret_type, ret_reg);
            }
        } else {
            IRgenRetReg(getCurrentBlock(), ret_type, ret_reg);
        }
    } else {
        IRgenRetVoid(getCurrentBlock());
    }
}

void IRgenerator::visit(BreakStmt &) {
    if (loop_end_label != -1) {
        IRgenBRUnCond(getCurrentBlock(), loop_end_label);
    }
}

void IRgenerator::visit(ContinueStmt &) {
    if (loop_start_label != -1) {
        IRgenBRUnCond(getCurrentBlock(), loop_start_label);
    }
}

// void IRgenerator::visit(UnaryExp &node) {
//     node.operand->accept(*this);
//     int operand_reg = max_reg;
//     int result_reg = newReg();
//     VarAttribute operand_attr = irgen_table.RegTable[operand_reg];

//     // 处理嵌套的一元操作
//     int sign = 1;
//     UnaryOp effective_op = node.op;
//     Exp* current = &node;
//     while (auto* unary = dynamic_cast<UnaryExp*>(current)) {
//         if (unary->op == UnaryOp::PLUS) {
//             // 正号不改变符号
//         } else if (unary->op == UnaryOp::MINUS) {
//             sign *= -1;
//         } else if (unary->op == UnaryOp::NOT) {
//             effective_op = UnaryOp::NOT;
//             break;
//         }
//         current = unary->operand.get();
//     }

//     // 准备操作数
//     Operand operand;
//     LLVMType operand_type;
//     if (isPointer(operand_reg)) {
//         // 指针类型需要加载值
//         int value_reg = newReg();
//         operand_type = Type2LLvm.at(operand_attr.type);
//         IRgenLoad(getCurrentBlock(), operand_type, value_reg, GetNewRegOperand(operand_reg));
//         operand = GetNewRegOperand(value_reg);
//     } else if (operand_attr.IntInitVals.size() > 0) {
//         // 整数常量
//         operand = new ImmI32Operand(operand_attr.IntInitVals[0]);
//         operand_type = LLVMType::I32;
//     } else if (operand_attr.FloatInitVals.size() > 0) {
//         // 浮点数常量
//         operand = new ImmF32Operand(operand_attr.FloatInitVals[0]);
//         operand_type = LLVMType::FLOAT32;
//     } else {
//         // 直接使用寄存器
//         operand = GetNewRegOperand(operand_reg);
//         operand_type = Type2LLvm.at(operand_attr.type);
//     }

//     switch (effective_op) {
//     case UnaryOp::PLUS:
//     case UnaryOp::MINUS:
//         if (sign == -1) {
//             // 确保类型有效
//             if (operand_type == LLVMType::VOID_TYPE) {
//                 operand_type = LLVMType::I32;
//             }
            
//             // 创建零值操作数
//             Operand zero;
//             if (operand_type == LLVMType::FLOAT32) {
//                 zero = new ImmF32Operand(0.0f);
//             } else {
//                 zero = new ImmI32Operand(0);
//             }
            
//             // 生成减法指令
//             getCurrentBlock()->InsertInstruction(1, 
//                 new ArithmeticInstruction(SUB, operand_type, zero, operand, 
//                 GetNewRegOperand(result_reg)));
//         } else {
//             // 正号不需要操作，但需要确保操作数已加载
//             result_reg = operand_reg; // 直接使用操作数寄存器
//         }
//         break;
//     case UnaryOp::NOT:
//         if (operand_attr.IntInitVals.size() > 0) {
//             // 整数常量取反
//             int val = operand_attr.IntInitVals[0];
//             irgen_table.RegTable[result_reg].type = BaseType::INT;
//             irgen_table.RegTable[result_reg].IntInitVals.push_back(!val);
//         } else {
//             // 生成比较指令
//             // getCurrentBlock()->InsertInstruction(1, 
//             //     new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
//             //     IcmpCond::eq, GetNewRegOperand(result_reg)));

//             int cmp_reg = newReg();
//             getCurrentBlock()->InsertInstruction(1, 
//                 new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
//                 IcmpCond::eq, GetNewRegOperand(cmp_reg)));
            
//             // 将i1扩展为i32（0或1）
//             IRgenZextI1toI32(getCurrentBlock(), cmp_reg, result_reg);
//         }
//         break;
//     }
    
//     // 更新寄存器属性
//     if (effective_op == UnaryOp::PLUS && sign == 1) {
//         // 正号操作直接传递原寄存器属性
//         irgen_table.RegTable[result_reg] = operand_attr;
//     } else {
//         irgen_table.RegTable[result_reg].type = operand_attr.type;
//     }
    
//     max_reg = result_reg;
// }

// void IRgenerator::visit(UnaryExp &node) {
//     node.operand->accept(*this);
//     int operand_reg = max_reg;
//     int result_reg = newReg();
//     VarAttribute operand_attr = irgen_table.RegTable[operand_reg];

//     // 处理嵌套的一元操作
//     int sign = 1;
//     UnaryOp effective_op = node.op;
//     Exp* current = &node;
//     while (auto* unary = dynamic_cast<UnaryExp*>(current)) {
//         if (unary->op == UnaryOp::PLUS) {
//             // 正号不改变符号
//         } else if (unary->op == UnaryOp::MINUS) {
//             sign *= -1;
//         } else if (unary->op == UnaryOp::NOT) {
//             effective_op = UnaryOp::NOT;
//             break;
//         }
//         current = unary->operand.get();
//     }

//     // 准备操作数
//     Operand operand;
//     LLVMType operand_type;
//     if (isPointer(operand_reg)) {
//         // 指针类型需要加载值
//         int value_reg = newReg();
//         operand_type = Type2LLvm.at(operand_attr.type);
//         IRgenLoad(getCurrentBlock(), operand_type, value_reg, GetNewRegOperand(operand_reg));
//         operand = GetNewRegOperand(value_reg);
//     } else if (operand_attr.IntInitVals.size() > 0) {
//         // 整数常量
//         operand = new ImmI32Operand(operand_attr.IntInitVals[0]);
//         operand_type = LLVMType::I32;
//     } else if (operand_attr.FloatInitVals.size() > 0) {
//         // 浮点数常量
//         operand = new ImmF32Operand(operand_attr.FloatInitVals[0]);
//         operand_type = LLVMType::FLOAT32;
//     } else {
//         // 直接使用寄存器
//         operand = GetNewRegOperand(operand_reg);
//         operand_type = Type2LLvm.at(operand_attr.type);
//     }

//     switch (effective_op) {
//     case UnaryOp::PLUS:
//     case UnaryOp::MINUS:
//         if (sign == -1) {
//             // 确保类型有效
//             if (operand_type == LLVMType::VOID_TYPE) {
//                 operand_type = LLVMType::I32;
//             }
            
//             // 创建零值操作数
//             Operand zero;
//             if (operand_type == LLVMType::FLOAT32) {
//                 zero = new ImmF32Operand(0.0f);
//             } else {
//                 zero = new ImmI32Operand(0);
//             }
            
//             // 生成减法指令
//             getCurrentBlock()->InsertInstruction(1, 
//                 new ArithmeticInstruction(SUB, operand_type, zero, operand, 
//                 GetNewRegOperand(result_reg)));
//         } else {
//             // 正号不需要操作，但需要确保操作数已加载
//             result_reg = operand_reg; // 直接使用操作数寄存器
//         }
//         break;
//     case UnaryOp::NOT:
//         if (operand_attr.IntInitVals.size() > 0) {
//             // 整数常量取反
//             int val = operand_attr.IntInitVals[0];
//             irgen_table.RegTable[result_reg].type = BaseType::INT;
//             irgen_table.RegTable[result_reg].IntInitVals.push_back(!val);
//         } else {
//             // 生成比较指令
//             // getCurrentBlock()->InsertInstruction(1, 
//             //     new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
//             //     IcmpCond::eq, GetNewRegOperand(result_reg)));
//             //     // 更新寄存器类型为 i1
//             // RegLLVMTypeMap[result_reg] = LLVMType::I1;

//             // 生成比较指令（结果始终是i1）
//             int cmp_reg = newReg();
            
//             // 根据操作数类型选择合适的比较
//             if (operand_type == LLVMType::FLOAT32) {
//                 getCurrentBlock()->InsertInstruction(1, 
//                     new FcmpInstruction(operand_type, operand, new ImmF32Operand(0.0f),
//                     FcmpCond::OEQ, GetNewRegOperand(cmp_reg)));
//             } else {
//                 // 默认使用整数比较
//                 getCurrentBlock()->InsertInstruction(1, 
//                     new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
//                     IcmpCond::eq, GetNewRegOperand(cmp_reg)));
//             }
            
//             // 记录结果为i1类型
//             RegLLVMTypeMap[cmp_reg] = LLVMType::I1;
//             result_reg = cmp_reg;

//             // int cmp_reg = newReg();
//             // getCurrentBlock()->InsertInstruction(1, 
//             //     new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
//             //     IcmpCond::eq, GetNewRegOperand(cmp_reg)));
            
//             // // 将i1扩展为i32（0或1）
//             // IRgenZextI1toI32(getCurrentBlock(), cmp_reg, result_reg);
//         }
//         break;
//     }
    
//     // 更新寄存器属性
//     if (effective_op == UnaryOp::PLUS && sign == 1) {
//         // 正号操作直接传递原寄存器属性
//         irgen_table.RegTable[result_reg] = operand_attr;
//     } else {
//         irgen_table.RegTable[result_reg].type = operand_attr.type;
//     }
    
//     max_reg = result_reg;
// }

void IRgenerator::visit(UnaryExp &node) {
    node.operand->accept(*this);
    int operand_reg = max_reg;
    int result_reg = newReg();
    VarAttribute operand_attr = irgen_table.RegTable[operand_reg];

    // 处理嵌套的一元操作
    int sign = 1;
    UnaryOp effective_op = node.op;
    Exp* current = &node;
    while (auto* unary = dynamic_cast<UnaryExp*>(current)) {
        if (unary->op == UnaryOp::PLUS) {
            // 正号不改变符号
        } else if (unary->op == UnaryOp::MINUS) {
            sign *= -1;
        } else if (unary->op == UnaryOp::NOT) {
            effective_op = UnaryOp::NOT;
            break;
        }
        current = unary->operand.get();
    }

    // 准备操作数
    Operand operand;
    LLVMType operand_type;
    if (isPointer(operand_reg)) {
        // 指针类型需要加载值
        int value_reg = newReg();
        operand_type = Type2LLvm.at(operand_attr.type);
        IRgenLoad(getCurrentBlock(), operand_type, value_reg, GetNewRegOperand(operand_reg));
        operand = GetNewRegOperand(value_reg);
    } else if (operand_attr.IntInitVals.size() > 0) {
        // 整数常量
        operand = new ImmI32Operand(operand_attr.IntInitVals[0]);
        operand_type = LLVMType::I32;
    } else if (operand_attr.FloatInitVals.size() > 0) {
        // 浮点数常量
        operand = new ImmF32Operand(operand_attr.FloatInitVals[0]);
        operand_type = LLVMType::FLOAT32;
    } else {
        // 直接使用寄存器
        operand = GetNewRegOperand(operand_reg);
        operand_type = Type2LLvm.at(operand_attr.type);
    }

    switch (effective_op) {
    case UnaryOp::PLUS:
    case UnaryOp::MINUS:
        if (sign == -1) {
            // 确保类型有效
            if (operand_type == LLVMType::VOID_TYPE) {
                operand_type = LLVMType::I32;
            }
            
            // 创建零值操作数
            Operand zero;
            if (operand_type == LLVMType::FLOAT32) {
                zero = new ImmF32Operand(0.0f);
            } else {
                zero = new ImmI32Operand(0);
            }
            
            // 生成减法指令
            getCurrentBlock()->InsertInstruction(1, 
                new ArithmeticInstruction(SUB, operand_type, zero, operand, 
                GetNewRegOperand(result_reg)));
        } else {
            // 正号不需要操作，但需要确保操作数已加载
            result_reg = operand_reg; // 直接使用操作数寄存器
        }
        break;
        case UnaryOp::NOT:
        if (operand_attr.IntInitVals.size() > 0) {
            // 整数常量取反
            int val = operand_attr.IntInitVals[0];
            irgen_table.RegTable[result_reg].type = BaseType::INT;
            irgen_table.RegTable[result_reg].IntInitVals.push_back(!val);
        } else if (operand_attr.FloatInitVals.size() > 0) {
            // 浮点数常量取反
            float val = operand_attr.FloatInitVals[0];
            irgen_table.RegTable[result_reg].type = BaseType::INT;
            irgen_table.RegTable[result_reg].IntInitVals.push_back(val == 0.0f ? 1 : 0);
        } else {
            // 生成比较指令（结果始终是i1）
            int cmp_reg = newReg();
            if (operand_type == LLVMType::FLOAT32) {
                getCurrentBlock()->InsertInstruction(1, 
                    new FcmpInstruction(operand_type, operand, new ImmF32Operand(0.0f),
                    FcmpCond::OEQ, GetNewRegOperand(cmp_reg)));
            } else {
                // 默认使用整数比较
                getCurrentBlock()->InsertInstruction(1, 
                    new IcmpInstruction(LLVMType::I32, operand, new ImmI32Operand(0), 
                    IcmpCond::eq, GetNewRegOperand(cmp_reg)));
            }
            // 记录结果为i1类型
            RegLLVMTypeMap[cmp_reg] = LLVMType::I1;
            
            // +++ 新增：将i1结果转换为i32（0或1） +++
            // int zext_reg = newReg();
            // IRgenZextI1toI32(getCurrentBlock(), cmp_reg, zext_reg);
            // result_reg = zext_reg;
            result_reg = cmp_reg;
        }
        break;
    }
    
    // 更新寄存器属性
    if (effective_op == UnaryOp::PLUS && sign == 1) {
        // 正号操作直接传递原寄存器属性
        irgen_table.RegTable[result_reg] = operand_attr;
    } else {
        irgen_table.RegTable[result_reg].type = operand_attr.type;
    }
    
    max_reg = result_reg;
}


void IRgenerator::visit(BinaryExp &node) {
    node.lhs->accept(*this);
    int lhs_reg = max_reg;
    VarAttribute lhs_attr = irgen_table.RegTable[lhs_reg];
    node.rhs->accept(*this);
    int rhs_reg = max_reg;
    VarAttribute rhs_attr = irgen_table.RegTable[rhs_reg];
    int result_reg = newReg();

    BaseType result_base_type;
    if (lhs_attr.type != BaseType::VOID) {
        result_base_type = lhs_attr.type;
    } else if (rhs_attr.type != BaseType::VOID) {
        result_base_type = rhs_attr.type;
    } else {
        // 默认使用INT类型防止void,TODO
        result_base_type = BaseType::INT;
    }
    LLVMType type = Type2LLvm.at(result_base_type);

    // Determine the type of operation
    //LLVMType type = Type2LLvm.at(lhs_attr.type);
    
    //LLVMType type = Type2LLvm.at(rhs_attr.type);
    // LLVMType type = Type2LLvm[static_cast<int>(lhs_attr.type)];
    LLVMType result_type = (node.op == BinaryOp::AND || node.op == BinaryOp::OR) ? LLVMType::I1 : type;

    // Prepare operands
    Operand lhs_operand, rhs_operand;
    bool is_lhs_constant = !lhs_attr.IntInitVals.empty();
    bool is_rhs_constant = !rhs_attr.IntInitVals.empty();
    bool is_lhs_pointer = isPointer(lhs_reg);
    bool is_rhs_pointer = isPointer(rhs_reg);

    // Handle LHS
    if (is_lhs_constant) {
        lhs_operand = new ImmI32Operand(lhs_attr.IntInitVals[0]);
    } else if (is_lhs_pointer) {
        int value_reg = newReg();
        IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(lhs_reg));
        lhs_operand = GetNewRegOperand(value_reg);
    } else if (auto* lval = dynamic_cast<LVal*>(node.lhs.get())) {
        auto it = irgen_table.name_to_reg.find(lval->name);
        SymbolInfo* sym = str_table.lookup(lval->name);
        if (sym && sym->kind == SymbolKind::CONSTANT && lval->indices.empty()) {
            if (auto int_val = sym->getConstantValue<int>()) {
                lhs_operand = new ImmI32Operand(*int_val);
            } else if (auto float_val = sym->getConstantValue<float>()) {
                lhs_operand = new ImmF32Operand(*float_val);
            } else {
                int value_reg = newReg();
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewGlobalOperand(lval->name));
                lhs_operand = GetNewRegOperand(value_reg);
            }
        } else if (it == irgen_table.name_to_reg.end()) {
            int value_reg = newReg();
            if (!lval->indices.empty()) {
                std::vector<Operand> indices;
                indices.push_back(new ImmI32Operand(0));
                for (auto& idx : lval->indices) {
                    idx->accept(*this);
                    int idx_reg = max_reg;
                    if (irgen_table.RegTable[idx_reg].IntInitVals.size() > 0) {
                        indices.push_back(new ImmI32Operand(irgen_table.RegTable[idx_reg].IntInitVals[0]));
                    } else {
                        indices.push_back(GetNewRegOperand(idx_reg));
                    }
                }
                std::vector<int> dims_int(sym->array_dimensions.begin(), sym->array_dimensions.end());
                int ptr_reg = newReg();
                IRgenGetElementptr(getCurrentBlock(), type, ptr_reg, GetNewGlobalOperand(lval->name), dims_int, indices);
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(ptr_reg));
            } else {
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewGlobalOperand(lval->name));
            }
            lhs_operand = GetNewRegOperand(value_reg);
        } else {
            lhs_operand = GetNewRegOperand(lhs_reg);
        }
    } else {
        lhs_operand = GetNewRegOperand(lhs_reg);
    }

    // Handle RHS
    if (is_rhs_constant) {
        rhs_operand = new ImmI32Operand(rhs_attr.IntInitVals[0]);
    } else if (is_rhs_pointer) {
        int value_reg = newReg();
        IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(rhs_reg));
        rhs_operand = GetNewRegOperand(value_reg);
    } else if (auto* lval = dynamic_cast<LVal*>(node.rhs.get())) {
        auto it = irgen_table.name_to_reg.find(lval->name);
        SymbolInfo* sym = str_table.lookup(lval->name);
        if (sym && sym->kind == SymbolKind::CONSTANT && lval->indices.empty()) {
            if (auto int_val = sym->getConstantValue<int>()) {
                rhs_operand = new ImmI32Operand(*int_val);
            } else if (auto float_val = sym->getConstantValue<float>()) {
                rhs_operand = new ImmF32Operand(*float_val);
            } else {
                int value_reg = newReg();
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewGlobalOperand(lval->name));
                rhs_operand = GetNewRegOperand(value_reg);
            }
        } else if (it == irgen_table.name_to_reg.end()) {
            int value_reg = newReg();
            if (!lval->indices.empty()) {
                std::vector<Operand> indices;
                indices.push_back(new ImmI32Operand(0));
                for (auto& idx : lval->indices) {
                    idx->accept(*this);
                    int idx_reg = max_reg;
                    if (irgen_table.RegTable[idx_reg].IntInitVals.size() > 0) {
                        indices.push_back(new ImmI32Operand(irgen_table.RegTable[idx_reg].IntInitVals[0]));
                    } else {
                        indices.push_back(GetNewRegOperand(idx_reg));
                    }
                }
                std::vector<int> dims_int(sym->array_dimensions.begin(), sym->array_dimensions.end());
                int ptr_reg = newReg();
                IRgenGetElementptr(getCurrentBlock(), type, ptr_reg, GetNewGlobalOperand(lval->name), dims_int, indices);
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewRegOperand(ptr_reg));
            } else {
                IRgenLoad(getCurrentBlock(), type, value_reg, GetNewGlobalOperand(lval->name));
            }
            rhs_operand = GetNewRegOperand(value_reg);
        } else {
            rhs_operand = GetNewRegOperand(rhs_reg);
        }
    } else {
        rhs_operand = GetNewRegOperand(rhs_reg);
    }

    // Generate the appropriate instruction
    switch (node.op) {
        case BinaryOp::ADD:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(ADD, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::SUB:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(SUB, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::MUL:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(MUL_OP, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::DIV:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(DIV_OP, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::MOD:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(MOD_OP, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::GT:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::sgt, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::GTE:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::sge, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::LT:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::slt, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::LTE:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::sle, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::EQ:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::eq, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::NEQ:
            getCurrentBlock()->InsertInstruction(1, new IcmpInstruction(type, lhs_operand, rhs_operand, IcmpCond::ne, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::AND:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(BITAND, LLVMType::I1, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::OR:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(BITOR, LLVMType::I1, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
    }
    VarAttribute result_attr;
    result_attr.type = (node.op == BinaryOp::AND || node.op == BinaryOp::OR) ? BaseType::INT : lhs_attr.type;
    irgen_table.RegTable[result_reg] = result_attr;
    max_reg = result_reg;
}

void IRgenerator::visit(LVal &node) {
    auto it = irgen_table.name_to_reg.find(node.name);
    if (it != irgen_table.name_to_reg.end()) {
        // Local variable or parameter
        int reg = it->second;
        VarAttribute &attr = irgen_table.RegTable[reg];

        // +++ 新增: 处理局部常量 +++
        if (attr.ConstTag && node.indices.empty() && !require_address) {
            // 局部常量标量 - 直接使用存储的值
            if (attr.IntInitVals.size() > 0) {
                int value_reg = newReg();
                IRgenLoad(getCurrentBlock(), Type2LLvm.at(attr.type), value_reg, GetNewRegOperand(reg));
                max_reg = value_reg;
                return;
            }
        }

        if (!node.indices.empty()) {
            std::vector<Operand> indices;
            indices.push_back(new ImmI32Operand(0)); // First index for local array
            for (auto& idx : node.indices) {
                bool old_require = require_address;
                require_address = false; // 索引需要值，而不是地址
                idx->accept(*this);
                require_address = old_require;

                int idx_reg = max_reg;
                // 确保索引是值而不是指针
                if (isPointer(idx_reg)) {
                    int value_reg = newReg();
                    IRgenLoad(getCurrentBlock(), LLVMType::I32, value_reg, 
                              GetNewRegOperand(idx_reg));
                    indices.push_back(GetNewRegOperand(value_reg));
                } else if (irgen_table.RegTable[idx_reg].IntInitVals.size() > 0) {
                    indices.push_back(new ImmI32Operand(
                        irgen_table.RegTable[idx_reg].IntInitVals[0]));
                } else {
                    indices.push_back(GetNewRegOperand(idx_reg));
                }
            }
            int ptr_reg = newReg();
            std::vector<int> dims_int;
            for (auto dim : irgen_table.RegTable[reg].dims) {
                dims_int.push_back(static_cast<int>(dim));
            }
            // IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(irgen_table.RegTable[reg].type)],
            //                    ptr_reg, GetNewRegOperand(reg), dims_int, indices);
            IRgenGetElementptr(getCurrentBlock(), Type2LLvm.at(irgen_table.RegTable[reg].type), ptr_reg, GetNewRegOperand(reg), dims_int, indices);
            if (!require_address) {
                // Load the value if a value is required
                int value_reg = newReg();
                //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(irgen_table.RegTable[reg].type)], value_reg, GetNewRegOperand(ptr_reg));
                IRgenLoad(getCurrentBlock(), Type2LLvm.at(irgen_table.RegTable[reg].type), value_reg, GetNewRegOperand(ptr_reg));
                // +++ 设置新寄存器属性 +++
                VarAttribute new_attr;
                new_attr.type = attr.type;
                irgen_table.RegTable[value_reg] = new_attr;
                max_reg = value_reg;
            } else {
                max_reg = ptr_reg;
            }
        } else {
            // if (!require_address && !irgen_table.RegTable[reg].dims.empty()) {
            //     // Load the value for array base if value is required
            //     int value_reg = newReg();
            //     IRgenLoad(getCurrentBlock(), Type2LLvm.at(irgen_table.RegTable[reg].type), value_reg, GetNewRegOperand(reg));
            //     //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(irgen_table.RegTable[reg].type)], value_reg, GetNewRegOperand(reg));
            //     max_reg = value_reg;
            // } else {
            //     max_reg = reg; // Return the pointer
            // }
            if (require_address) {
                // 需要地址时直接返回指针
                max_reg = reg;
            } else {
                // 标量变量需要加载值
                if (irgen_table.RegTable[reg].dims.empty()) {
                    int value_reg = newReg();
                    IRgenLoad(getCurrentBlock(), 
                             Type2LLvm.at(irgen_table.RegTable[reg].type), 
                             value_reg, 
                             GetNewRegOperand(reg));
                             // +++ 设置新寄存器属性 +++
                VarAttribute new_attr;
                new_attr.type = attr.type;
                irgen_table.RegTable[value_reg] = new_attr;
                    max_reg = value_reg;
                    //max_reg = reg;
                } else {
                    // 数组直接返回基地址
                    //max_reg = reg;
                    int value_reg = newReg();
                    IRgenLoad(getCurrentBlock(), 
                             Type2LLvm.at(irgen_table.RegTable[reg].type), 
                             value_reg, 
                             GetNewRegOperand(reg));
                             // +++ 设置新寄存器属性 +++
                VarAttribute new_attr;
                new_attr.type = attr.type;
                irgen_table.RegTable[value_reg] = new_attr;
                    max_reg = value_reg;
                }
            }
        }
    } else {
        // Check if it's a global variable or constant
        SymbolInfo* sym = str_table.lookup(node.name);
        if (sym && (sym->kind == SymbolKind::VARIABLE || sym->kind == SymbolKind::CONSTANT)) {
            auto* basic_type = dynamic_cast<BasicType*>(sym->type.get());
            if (!basic_type) {
                throw std::runtime_error("Global variable " + node.name + " has invalid type");
            }
            if (sym->kind == SymbolKind::CONSTANT && node.indices.empty() && sym->constant_value.has_value()) {
                // Handle constant scalar value
                int value_reg = newReg();
                VarAttribute attr;
                attr.type = basic_type->type;
                irgen_table.RegTable[value_reg] = attr;
                if (auto int_val = sym->getConstantValue<int>()) {
                    irgen_table.RegTable[value_reg].IntInitVals.push_back(*int_val);
                } else if (auto float_val = sym->getConstantValue<float>()) {
                    irgen_table.RegTable[value_reg].FloatInitVals.push_back(*float_val);
                }
                max_reg = value_reg;
            } else if (node.indices.empty()) {
                if (require_address) {
                    // 获取全局变量地址
                    int ptr_reg = newReg();
                    std::vector<int> dims_int; // 标量，无维度
                    std::vector<Operand> indices;
                    indices.push_back(new ImmI32Operand(0));
                    IRgenGetElementptr(getCurrentBlock(), 
                                      Type2LLvm.at(basic_type->type), 
                                      ptr_reg, 
                                      GetNewGlobalOperand(node.name), 
                                      dims_int, 
                                      indices);
                    max_reg = ptr_reg;
                }else{
                // Load the value from the global variable
                int value_reg = newReg();
                VarAttribute attr;
                attr.type = basic_type->type;
                irgen_table.RegTable[value_reg] = attr;
                max_reg = value_reg;
                IRgenLoad(getCurrentBlock(), Type2LLvm.at(basic_type->type), value_reg, GetNewGlobalOperand(node.name));
                //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(basic_type->type)], value_reg, GetNewGlobalOperand(node.name));
                //max_reg = value_reg; // Set max_reg to the loaded value
                }
            } else {
                // Handle array access for global variable
                std::vector<Operand> indices;
                indices.push_back(new ImmI32Operand(0)); // First index for global array
                for (auto& idx : node.indices) {
                    idx->accept(*this);
                    int idx_reg = max_reg;
                    if (auto const_val = evaluateConstExpression(idx.get())) {
                        indices.push_back(new ImmI32Operand(*const_val));
                    } else {
                        indices.push_back(GetNewRegOperand(idx_reg));
                    }
                }
                int ptr_reg = newReg();
                std::vector<int> dims_int(sym->array_dimensions.begin(), sym->array_dimensions.end());
                // IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(basic_type->type)],
                //                    ptr_reg, GetNewGlobalOperand(node.name), dims_int, indices);
                IRgenGetElementptr(getCurrentBlock(), Type2LLvm.at(basic_type->type), ptr_reg, GetNewGlobalOperand(node.name), dims_int, indices);
                if (!require_address) {
                    // Load the value if a value is required
                    int value_reg = newReg();
                    IRgenLoad(getCurrentBlock(), Type2LLvm.at(basic_type->type), value_reg, GetNewRegOperand(ptr_reg));
                    //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(basic_type->type)], value_reg, GetNewRegOperand(ptr_reg));
                    // +++ 设置新寄存器属性 +++
                    VarAttribute new_attr;
                    new_attr.type = basic_type->type;
                    irgen_table.RegTable[value_reg] = new_attr;
                    max_reg = value_reg;
                } else {
                    max_reg = ptr_reg;
                }
            }
        } else {
            throw std::runtime_error("Undefined variable: " + node.name);
        }
    }
}



// void IRgenerator::visit(FunctionCall &node) {
//     std::vector<std::pair<enum LLVMType, Operand>> args;
//     for (auto &arg : node.arguments) {
//         require_address = false; // Arguments should be values
//         arg->accept(*this);
//         int arg_reg = max_reg;
//         VarAttribute arg_attr = irgen_table.RegTable[arg_reg];
//         Operand arg_operand;
//         if (arg_attr.IntInitVals.size() > 0) {
//             arg_operand = new ImmI32Operand(arg_attr.IntInitVals[0]);
//         } else if (arg_attr.FloatInitVals.size() > 0) {
//             arg_operand = new ImmF32Operand(arg_attr.FloatInitVals[0]);
//         } else if (isPointer(arg_reg)) {
//             int value_reg = newReg();
//             IRgenLoad(getCurrentBlock(), Type2LLvm.at(arg_attr.type), value_reg, GetNewRegOperand(arg_reg));
//             //IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(arg_attr.type)], value_reg, GetNewRegOperand(arg_reg));
//             arg_operand = GetNewRegOperand(value_reg);
//         } else {
//             arg_operand = GetNewRegOperand(arg_reg);
//         }
//         args.push_back(std::make_pair(Type2LLvm.at(arg_attr.type), arg_operand));
//         //args.push_back({Type2LLvm[static_cast<int>(arg_attr.type)], arg_operand});
//     }
//     int result_reg = newReg();
//     //IRgenCall(getCurrentBlock(), Type2LLvm[static_cast<int>(function_returntype)], result_reg, args, node.function_name);
//     IRgenCall(getCurrentBlock(), Type2LLvm.at(function_returntype), result_reg, args, node.function_name);
//     VarAttribute result_attr;
//     result_attr.type = function_returntype;
//     irgen_table.RegTable[result_reg] = result_attr;
//     max_reg = result_reg;
// }

void IRgenerator::visit(FunctionCall &node) {
    // 检查是否是库函数
    bool is_lib_func = (node.function_name == "getint" ||
                       node.function_name == "getch" ||
                       node.function_name == "getfloat" ||
                       node.function_name == "getarray" ||
                       node.function_name == "getfarray" ||
                       node.function_name == "putint" ||
                       node.function_name == "putch" ||
                       node.function_name == "putfloat" ||
                       node.function_name == "putarray" ||
                       node.function_name == "putfarray" ||
                       node.function_name == "putf" ||
                       node.function_name == "_sysy_starttime" ||
                       node.function_name == "_sysy_stoptime");

    // 获取函数返回类型
    BaseType return_type = BaseType::VOID;
    std::vector<BaseType> param_types;
    if (is_lib_func) {
        // 硬编码库函数的类型信息
        if (node.function_name == "getint" || node.function_name == "getch") {
            return_type = BaseType::INT;
        } else if (node.function_name == "getfloat") {
            return_type = BaseType::FLOAT;
        } else if (node.function_name == "getarray" || node.function_name == "getfarray") {
            return_type = BaseType::INT;
            param_types.push_back(BaseType::STRING); // ptr参数
        } else if (node.function_name == "putint" || node.function_name == "putch") {
            param_types.push_back(BaseType::INT);
        } else if (node.function_name == "putfloat") {
            param_types.push_back(BaseType::FLOAT);
        } else if (node.function_name == "putarray" || node.function_name == "putfarray") {
            param_types.push_back(BaseType::INT);
            param_types.push_back(BaseType::STRING); // ptr参数
        } else if (node.function_name == "putf") {
            param_types.push_back(BaseType::STRING); // ptr参数
        } else if (node.function_name == "_sysy_starttime" || node.function_name == "_sysy_stoptime") {
            param_types.push_back(BaseType::INT);
        }
    } else {
        // 普通函数：从符号表获取类型信息
        SymbolInfo* sym = str_table.lookup(node.function_name);
        if (sym && sym->kind == SymbolKind::FUNCTION) {
            FunctionType* func_type = dynamic_cast<FunctionType*>(sym->type.get());
            if (func_type) {
                return_type = dynamic_cast<BasicType*>(func_type->return_type.get())->type;
                for (auto& param : func_type->parameter_types) {
                    BasicType* basic_param = dynamic_cast<BasicType*>(param.get());
                    if (basic_param) {
                        param_types.push_back(basic_param->type);
                    }
                }
            }
        }
    }

    // 准备参数
    std::vector<std::pair<enum LLVMType, Operand>> args;
    for (size_t i = 0; i < node.arguments.size(); i++) {
        require_address = false;
        node.arguments[i]->accept(*this);
        int arg_reg = max_reg;
        VarAttribute arg_attr = irgen_table.RegTable[arg_reg];
        
        // 确定参数类型：优先使用函数声明的正式类型
        BaseType expected_type = (i < param_types.size()) ? param_types[i] : arg_attr.type;
        LLVMType llvm_type = Type2LLvm.at(expected_type);

        Operand arg_operand;
        if (arg_attr.IntInitVals.size() > 0) {
            arg_operand = new ImmI32Operand(arg_attr.IntInitVals[0]);
        } else if (arg_attr.FloatInitVals.size() > 0) {
            arg_operand = new ImmF32Operand(arg_attr.FloatInitVals[0]);
        } else if (isPointer(arg_reg)) {
            int value_reg = newReg();
            IRgenLoad(getCurrentBlock(), llvm_type, value_reg, GetNewRegOperand(arg_reg));
            arg_operand = GetNewRegOperand(value_reg);
        } else {
            arg_operand = GetNewRegOperand(arg_reg);
        }
        args.push_back(std::make_pair(llvm_type, arg_operand));
    }

    // 生成调用指令
    if (return_type == BaseType::VOID) {
        // void函数：无返回值
        IRgenCallVoid(getCurrentBlock(), Type2LLvm.at(return_type), args, node.function_name);
        max_reg = -1; // void调用没有结果寄存器
    } else {
        // 非void函数：有返回值
        int result_reg = newReg();
        IRgenCall(getCurrentBlock(), Type2LLvm.at(return_type), result_reg, args, node.function_name);
        VarAttribute result_attr;
        result_attr.type = return_type;
        irgen_table.RegTable[result_reg] = result_attr;
        max_reg = result_reg;
    }
}

void IRgenerator::visit(Number &node) {
    if (std::holds_alternative<int>(node.value)) {
        max_reg = newReg();
        irgen_table.RegTable[max_reg].type = BaseType::INT;
        irgen_table.RegTable[max_reg].IntInitVals.push_back(std::get<int>(node.value));
    } else {
        max_reg = newReg();
        irgen_table.RegTable[max_reg].type = BaseType::FLOAT;
        irgen_table.RegTable[max_reg].FloatInitVals.push_back(std::get<float>(node.value));
    }
}

void IRgenerator::visit(StringLiteral &node) {
    std::string str_name = "str_" + std::to_string(newLabel());
    llvmIR.global_def.push_back(new GlobalStringConstInstruction(node.value, str_name));
    int reg = newReg();
    IRgenLoad(getCurrentBlock(), PTR, reg, GetNewGlobalOperand(str_name));
    max_reg = reg;
}

void IRgenerator::visit(InitVal &node) {
    if (std::holds_alternative<std::unique_ptr<Exp>>(node.value)) {
        std::get<std::unique_ptr<Exp>>(node.value)->accept(*this);
    } else {
        auto& init_list = std::get<std::vector<std::unique_ptr<InitVal>>>(node.value);
        VarAttribute attr;
        attr.type = current_type;
        for (auto& init : init_list) {
            init->accept(*this);
            int init_reg = max_reg;
            if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                attr.IntInitVals.insert(attr.IntInitVals.end(),
                                        irgen_table.RegTable[init_reg].IntInitVals.begin(),
                                        irgen_table.RegTable[init_reg].IntInitVals.end());
            }
        }
        irgen_table.RegTable[max_reg] = attr;
    }
}

void IRgenerator::visit(ConstInitVal &node) {
    if (std::holds_alternative<std::unique_ptr<Exp>>(node.value)) {
        std::get<std::unique_ptr<Exp>>(node.value)->accept(*this);
    } else {
        auto& init_list = std::get<std::vector<std::unique_ptr<ConstInitVal>>>(node.value);
        VarAttribute attr;
        attr.type = current_type;
        for (auto& init : init_list) {
            init->accept(*this);
            int init_reg = max_reg;
            if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                attr.IntInitVals.insert(attr.IntInitVals.end(),
                                        irgen_table.RegTable[init_reg].IntInitVals.begin(),
                                        irgen_table.RegTable[init_reg].IntInitVals.end());
            }
        }
        irgen_table.RegTable[max_reg] = attr;
    }
}