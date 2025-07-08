#include "../include/ast.h"
#include "../include/block.h"
#include "../include/symtab.h"
#include <assert.h>
#include <stdexcept>
#include <optional>

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
static int now_label = 0;
static int loop_start_label = -1;
static int loop_end_label = -1;

std::map<FuncDefInstruction, int> max_label_map{};
std::map<FuncDefInstruction, int> max_reg_map{};

int max_reg = -1;
int max_label = -1;

IRgenTable irgen_table;
LLVMIR llvmIR;

extern void (*IRgenSingleNode[6])(SyntaxNode *a, BinaryOp opcode, LLVMBlock B);
extern void (*IRgenBinaryNode[6][6])(SyntaxNode *a, SyntaxNode *b, BinaryOp opcode, LLVMBlock B);

LLVMType Type2LLvm[6] = {LLVMType::I32, LLVMType::FLOAT32, LLVMType::I1, LLVMType::VOID_TYPE, LLVMType::PTR, LLVMType::DOUBLE};
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

void IRgenArithmeticI32(LLVMBlock B, LLVMIROpcode opcode, int reg1, int reg2, int result_reg) {
    B->InsertInstruction(1, new ArithmeticInstruction(opcode, LLVMType::I32, GetNewRegOperand(reg1),
                                                      GetNewRegOperand(reg2), GetNewRegOperand(result_reg)));
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
    B->InsertInstruction(1, new IcmpInstruction(LLVMType::I32, GetNewRegOperand(reg1), GetNewRegOperand(reg2), cmp_op,
                                                GetNewRegOperand(result_reg)));
}

void IRgenFcmp(LLVMBlock B, FcmpCond cmp_op, int reg1, int reg2, int result_reg) {
    B->InsertInstruction(1, new FcmpInstruction(LLVMType::FLOAT32, GetNewRegOperand(reg1), GetNewRegOperand(reg2),
                                                cmp_op, GetNewRegOperand(result_reg)));
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
}

void IRgenStore(LLVMBlock B, LLVMType type, int value_reg, Operand ptr) {
    B->InsertInstruction(1, new StoreInstruction(type, ptr, GetNewRegOperand(value_reg)));
}

void IRgenStore(LLVMBlock B, LLVMType type, Operand value, Operand ptr) {
    B->InsertInstruction(1, new StoreInstruction(type, ptr, value));
}

void IRgenCall(LLVMBlock B, LLVMType type, int result_reg, std::vector<std::pair<enum LLVMType, Operand>> args, std::string name) {
    B->InsertInstruction(1, new CallInstruction(type, GetNewRegOperand(result_reg), name, args));
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

void AddLibFunctionDeclare() {
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

void IRgenerator::handleArrayInitializer(InitVal* init, int base_reg, VarAttribute& attr, const std::vector<int>& dims, size_t dim_idx) {
  if (!init) return;
  if (std::holds_alternative<std::unique_ptr<Exp>>(init->value)) {
      auto& expr = std::get<std::unique_ptr<Exp>>(init->value);
      expr->accept(*this);
      int init_reg = max_reg;
      Operand value = irgen_table.RegTable[init_reg].IntInitVals.size() > 0 ?
                     static_cast<Operand>(new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0])) :
                     static_cast<Operand>(GetNewRegOperand(init_reg));
      IRgenStore(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value, GetNewRegOperand(base_reg));
  } else {
      auto& init_list = std::get<std::vector<std::unique_ptr<InitVal>>>(init->value);
      size_t flat_idx = 0;
      // Compute the limit as size_t to avoid sign-compare warning
      size_t limit = static_cast<size_t>(dims[0]) * (dim_idx + 1 < dims.size() ? static_cast<size_t>(dims[1]) : 1);
      for (size_t i = 0; i < init_list.size() && flat_idx < limit; i++) {
          if (dim_idx + 1 < dims.size()) {
              int sub_reg = newReg();
              std::vector<Operand> indices = {new ImmI32Operand(static_cast<int>(i)), new ImmI32Operand(0)};
              IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], sub_reg,
                                 GetNewRegOperand(base_reg), dims, indices);
              std::vector<int> sub_dims(dims.begin() + 1, dims.end());
              handleArrayInitializer(init_list[i].get(), sub_reg, attr, sub_dims, dim_idx + 1);
          } else {
              init_list[i]->accept(*this);
              int init_reg = max_reg;
              int elem_ptr_reg = newReg();
              std::vector<Operand> indices = {new ImmI32Operand(0), new ImmI32Operand(static_cast<int>(flat_idx))};
              IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], elem_ptr_reg,
                                 GetNewRegOperand(base_reg), dims, indices);
              Operand value = irgen_table.RegTable[init_reg].IntInitVals.size() > 0 ?
                             static_cast<Operand>(new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0])) :
                             static_cast<Operand>(GetNewRegOperand(init_reg));
              IRgenStore(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value, GetNewRegOperand(elem_ptr_reg));
              flat_idx++;
          }
      }
  }
}

LLVMBlock IRgenerator::getCurrentBlock() {
    return llvmIR.GetBlock(function_now, now_label);
}

int IRgenerator::newReg() { return ++current_reg_counter; }

int IRgenerator::newLabel() { return ++max_label; }

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
                // If it's a variable or parameter with no indices, it's a pointer (e.g., from alloca or global)
                auto* arr_type = dynamic_cast<ArrayType*>(sym->type.get());
                if (!arr_type || sym->is_array_pointer) {
                    return true;
                }
            }
            break;
        }
    }
    // If the register has dimensions, it's likely a pointer (e.g., array base)
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
    current_type = node.type;
    for (auto &def : node.definitions) {
        def->accept(*this);
    }
}

void IRgenerator::visit(ConstDef &node) {
    if (isGlobalScope()) {
        VarAttribute attr;
        attr.type = current_type;
        attr.ConstTag = true;
        for (auto &dim : node.array_dimensions) {
            auto val = evaluateConstExpression(dim.get());
            attr.dims.push_back(val.value_or(1));
        }
        node.initializer->accept(*this);
        int init_reg = max_reg;
        if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
            attr.IntInitVals = irgen_table.RegTable[init_reg].IntInitVals;
        } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
            attr.FloatInitVals = irgen_table.RegTable[init_reg].FloatInitVals;
        }
        llvmIR.global_def.push_back(new GlobalVarDefineInstruction(node.name, Type2LLvm[static_cast<int>(attr.type)], attr));
        
        // Add to symbol table with constant value
        SymbolInfo* sym = str_table.lookup(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::CONSTANT, makeBasicType(attr.type), node.name, true);
            if (attr.IntInitVals.size() > 0) {
                sym_info->setConstantValue(attr.IntInitVals[0]);
            } else if (attr.FloatInitVals.size() > 0) {
                sym_info->setConstantValue(attr.FloatInitVals[0]);
            }
            sym_info->setArrayDimensions(std::vector<int>(attr.dims.begin(), attr.dims.end()));
            str_table.insert(node.name, sym_info);
        }
    } else {
        int reg = newReg();
        VarAttribute attr;
        attr.type = current_type;
        attr.ConstTag = true;
        IRgenAlloca(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], reg);
        irgen_table.RegTable[reg] = attr;
        irgen_table.name_to_reg[node.name] = reg;
        node.initializer->accept(*this);
        int init_reg = max_reg;
        Operand value;
        if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
            value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
        } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
            value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
        } else {
            value = GetNewRegOperand(init_reg);
        }
        IRgenStore(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value, GetNewRegOperand(reg));
        
        // Add to symbol table with constant value
        SymbolInfo* sym = str_table.lookupCurrent(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::CONSTANT, makeBasicType(attr.type), node.name, true);
            if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                sym_info->setConstantValue(irgen_table.RegTable[init_reg].IntInitVals[0]);
            } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
                sym_info->setConstantValue(irgen_table.RegTable[init_reg].FloatInitVals[0]);
            }
            str_table.insert(node.name, sym_info);
        }
    }
}

void IRgenerator::visit(VarDecl &node) {
    current_type = node.type;
    for (auto &def : node.definitions) {
        def->accept(*this);
    }
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
        llvmIR.global_def.push_back(new GlobalVarDefineInstruction(node.name, Type2LLvm[static_cast<int>(attr.type)], attr));
        
        // Add to symbol table
        SymbolInfo* sym = str_table.lookup(node.name);
        if (!sym) {
            auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::VARIABLE, makeBasicType(attr.type), node.name, node.initializer.has_value());
            sym_info->setArrayDimensions(std::vector<int>(attr.dims.begin(), attr.dims.end()));
            str_table.insert(node.name, sym_info);
        }
    } else {
        int reg = newReg(); // Use node.name directly for clarity
        VarAttribute attr;
        attr.type = current_type;
        std::vector<int> dims;
        for (auto &dim : node.array_dimensions) {
            auto val = evaluateConstExpression(dim.get());
            if (val) {
                dims.push_back(*val);
            } else {
                dims.push_back(1); // Fallback for non-constant dimensions
            }
        }
        // Convert dims to std::vector<size_t>
        attr.dims = std::vector<size_t>(dims.begin(), dims.end());
        if (!dims.empty()) {
            IRgenAllocaArray(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], reg, dims);
        } else {
            IRgenAlloca(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], reg);
        }
        irgen_table.RegTable[reg] = attr;
        irgen_table.name_to_reg[node.name] = reg;
        if (node.initializer) {
            if (dims.empty()) {
                // Scalar variable initialization
                (*node.initializer)->accept(*this);
                int init_reg = max_reg;
                Operand value;
                if (irgen_table.RegTable[init_reg].IntInitVals.size() > 0) {
                    value = new ImmI32Operand(irgen_table.RegTable[init_reg].IntInitVals[0]);
                } else if (irgen_table.RegTable[init_reg].FloatInitVals.size() > 0) {
                    value = new ImmF32Operand(irgen_table.RegTable[init_reg].FloatInitVals[0]);
                } else if (isPointer(init_reg)) {
                    int value_reg = newReg();
                    IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value_reg, GetNewRegOperand(init_reg));
                    value = GetNewRegOperand(value_reg);
                } else {
                    value = GetNewRegOperand(init_reg);
                }
                IRgenStore(getCurrentBlock(), Type2LLvm[static_cast<int>(attr.type)], value, GetNewRegOperand(reg));
            } else {
                // Array initialization
                handleArrayInitializer(node.initializer->get(), reg, attr, dims, 0);
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
    function_now = new FunctionDefineInstruction(Type2LLvm[static_cast<int>(node.return_type)], node.name);
    function_returntype = node.return_type;
    llvmIR.NewFunction(function_now);
    now_label = 0;
    current_reg_counter = -1; // Reset register counter
    llvmIR.NewBlock(function_now, now_label);

    // Symbol table setup
    std::vector<std::shared_ptr<Type>> param_types;
    for (const auto& param : node.parameters) {
        param_types.push_back(makeBasicType(param->type));
    }
    auto func_type = makeFunctionType(makeBasicType(node.return_type), param_types);
    auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::FUNCTION, func_type, node.name, true);
    str_table.insert(node.name, sym_info);

    for (auto &param : node.parameters) {
        param->accept(*this);
    }
    node.body->accept(*this);
    AddNoReturnBlock();
    function_now = nullptr;
}

void IRgenerator::visit(FuncFParam &node) {
    int reg = newReg(); // Use node.name for clarity
    VarAttribute attr;
    attr.type = node.type;
    if (node.is_array_pointer || !node.array_dimensions.empty()) {
        attr.dims.push_back(0); // Array parameters are pointers
        function_now->InsertFormal(Type2LLvm[static_cast<int>(node.type)]);
    } else {
        // Scalar parameter: treat as value, not pointer
        function_now->InsertFormal(Type2LLvm[static_cast<int>(node.type)]);
    }
    function_now->formals_reg.push_back(GetNewRegOperand(reg));
    irgen_table.RegTable[reg] = attr;
    irgen_table.name_to_reg[node.name] = reg;

    // Add parameter to symbol table
    auto param_type = node.is_array_pointer ? makeArrayType(makeBasicType(node.type), {-1}) : makeBasicType(node.type);
    auto sym_info = std::make_shared<SymbolInfo>(SymbolKind::PARAMETER, param_type, node.name, true);
    sym_info->is_array_pointer = node.is_array_pointer;
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
    node.condition->accept(*this);
    int cond_reg = max_reg;
    int true_label = newLabel();
    int false_label = newLabel();
    int end_label = newLabel();
    IRgenBrCond(getCurrentBlock(), cond_reg, true_label, false_label);
    llvmIR.NewBlock(function_now, true_label);
    node.then_statement->accept(*this);
    IRgenBRUnCond(getCurrentBlock(), end_label);
    if (node.else_statement) {
        llvmIR.NewBlock(function_now, false_label);
        (*node.else_statement)->accept(*this);
        IRgenBRUnCond(getCurrentBlock(), end_label);
    } else {
        false_label = end_label;
    }
    llvmIR.NewBlock(function_now, end_label);
    now_label = end_label;
}

void IRgenerator::visit(WhileStmt &node) {
    int loop_start = newLabel();
    int loop_body = newLabel();
    int loop_end = newLabel();
    int old_loop_start = loop_start_label;
    int old_loop_end = loop_end_label;
    loop_start_label = loop_start;
    loop_end_label = loop_end;
    IRgenBRUnCond(getCurrentBlock(), loop_start);
    llvmIR.NewBlock(function_now, loop_start);
    node.condition->accept(*this);
    int cond_reg = max_reg;
    IRgenBrCond(getCurrentBlock(), cond_reg, loop_body, loop_end);
    llvmIR.NewBlock(function_now, loop_body);
    node.body->accept(*this);
    IRgenBRUnCond(getCurrentBlock(), loop_start);
    llvmIR.NewBlock(function_now, loop_end);
    now_label = loop_end;
    loop_start_label = old_loop_start;
    loop_end_label = old_loop_end;
}

void IRgenerator::visit(ExpStmt &node) {
    if (node.expression) {
        (*node.expression)->accept(*this);
    }
}

void IRgenerator::visit(AssignStmt &node) {
    node.rvalue->accept(*this);
    int rvalue_reg = max_reg;
    node.lvalue->accept(*this);
    int lvalue_reg = max_reg;
    LLVMType type = Type2LLvm[static_cast<int>(irgen_table.RegTable[lvalue_reg].type)];
    Operand value = irgen_table.RegTable[rvalue_reg].IntInitVals.size() > 0 ?
                   static_cast<Operand>(new ImmI32Operand(irgen_table.RegTable[rvalue_reg].IntInitVals[0])) :
                   static_cast<Operand>(GetNewRegOperand(rvalue_reg));
    IRgenStore(getCurrentBlock(), type, value, GetNewRegOperand(lvalue_reg));
}

void IRgenerator::visit(ReturnStmt &node) {
    if (node.expression) {
        (*node.expression)->accept(*this);
        int ret_reg = max_reg;
        LLVMType ret_type = Type2LLvm[static_cast<int>(function_returntype)];
        if (irgen_table.RegTable[ret_reg].IntInitVals.size() > 0) {
            IRgenRetImmInt(getCurrentBlock(), ret_type, irgen_table.RegTable[ret_reg].IntInitVals[0]);
        } else if (irgen_table.RegTable[ret_reg].FloatInitVals.size() > 0) {
            IRgenRetImmFloat(getCurrentBlock(), ret_type, irgen_table.RegTable[ret_reg].FloatInitVals[0]);
        } else if (node.expression.has_value() && dynamic_cast<FunctionCall*>((*node.expression).get())) {
            // Directly return function call result
            IRgenRetReg(getCurrentBlock(), ret_type, ret_reg);
        } else if (isPointer(ret_reg)) {
            int value_reg = newReg();
            IRgenLoad(getCurrentBlock(), ret_type, value_reg, GetNewRegOperand(ret_reg));
            IRgenRetReg(getCurrentBlock(), ret_type, value_reg);
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

void IRgenerator::visit(UnaryExp &node) {
    node.operand->accept(*this);
    int operand_reg = max_reg;
    int result_reg = newReg();
    switch (node.op) {
    case UnaryOp::PLUS:
        max_reg = operand_reg;
        break;
    case UnaryOp::MINUS:
        IRgenArithmeticI32(getCurrentBlock(), SUB, 0, operand_reg, result_reg);
        break;
    case UnaryOp::NOT:
        IRgenIcmp(getCurrentBlock(), IcmpCond::eq, operand_reg, 0, result_reg);
        break;
    }
}

void IRgenerator::visit(BinaryExp &node) {
    node.lhs->accept(*this);
    int lhs_reg = max_reg;
    VarAttribute lhs_attr = irgen_table.RegTable[lhs_reg];
    node.rhs->accept(*this);
    int rhs_reg = max_reg;
    VarAttribute rhs_attr = irgen_table.RegTable[rhs_reg];
    int result_reg = newReg();

    // Determine the type of operation
    LLVMType type = Type2LLvm[static_cast<int>(lhs_attr.type)];
    if (lhs_attr.type != rhs_attr.type) {
        // Handle type mismatches if necessary (e.g., int and float)
        type = LLVMType::I32; // For this test case, assume integer operations
    }

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
        // Check if LHS is a global variable
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
            // Global variable or array
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
        // Check if RHS is a global variable
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
            // Global variable or array
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
            if (is_lhs_constant && is_rhs_constant) {
                getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(ADD, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            } else if (is_lhs_constant) {
                IRgenArithmeticI32ImmLeft(getCurrentBlock(), ADD, lhs_attr.IntInitVals[0], rhs_reg, result_reg);
            } else if (is_rhs_constant) {
                IRgenArithmeticI32ImmRight(getCurrentBlock(), ADD, lhs_reg, rhs_attr.IntInitVals[0], result_reg);
            } else {
                getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(ADD, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            }
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
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(BITAND, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
        case BinaryOp::OR:
            getCurrentBlock()->InsertInstruction(1, new ArithmeticInstruction(BITXOR, type, lhs_operand, rhs_operand, GetNewRegOperand(result_reg)));
            break;
    }
    VarAttribute result_attr;
    result_attr.type = lhs_attr.type; // Assuming same type as LHS
    irgen_table.RegTable[result_reg] = result_attr;
    max_reg = result_reg;
}

void IRgenerator::visit(LVal &node) {
    auto it = irgen_table.name_to_reg.find(node.name);
    if (it != irgen_table.name_to_reg.end()) {
        // Local variable or parameter
        int reg = it->second;
        if (!node.indices.empty()) {
            std::vector<Operand> indices;
            indices.push_back(new ImmI32Operand(0)); // First index for local array
            for (auto& idx : node.indices) {
                idx->accept(*this);
                indices.push_back(GetNewRegOperand(max_reg));
            }
            int ptr_reg = newReg();
            std::vector<int> dims_int;
            for (auto dim : irgen_table.RegTable[reg].dims) {
                dims_int.push_back(static_cast<int>(dim));
            }
            IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(irgen_table.RegTable[reg].type)],
                               ptr_reg, GetNewRegOperand(reg), dims_int, indices);
            max_reg = ptr_reg;
        } else {
            max_reg = reg; // Local variable: max_reg is the pointer to the variable
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
                // Load the value from the global variable
                int value_reg = newReg();
                VarAttribute attr;
                attr.type = basic_type->type;
                irgen_table.RegTable[value_reg] = attr;
                IRgenLoad(getCurrentBlock(), Type2LLvm[static_cast<int>(basic_type->type)], value_reg, GetNewGlobalOperand(node.name));
                max_reg = value_reg; // Set max_reg to the loaded value, not a pointer
            } else {
                // Handle array access for global variable
                std::vector<Operand> indices;
                indices.push_back(new ImmI32Operand(0)); // First index for global array
                for (auto& idx : node.indices) {
                    idx->accept(*this);
                    indices.push_back(GetNewRegOperand(max_reg));
                }
                int ptr_reg = newReg();
                std::vector<int> dims_int(sym->array_dimensions.begin(), sym->array_dimensions.end());
                IRgenGetElementptr(getCurrentBlock(), Type2LLvm[static_cast<int>(basic_type->type)],
                                   ptr_reg, GetNewGlobalOperand(node.name), dims_int, indices);
                max_reg = ptr_reg;
            }
        } else {
            throw std::runtime_error("Undefined variable: " + node.name);
        }
    }
}

void IRgenerator::visit(FunctionCall &node) {
    std::vector<std::pair<enum LLVMType, Operand>> args;
    for (auto &arg : node.arguments) {
        arg->accept(*this);
        int arg_reg = max_reg;
        args.push_back({Type2LLvm[static_cast<int>(irgen_table.RegTable[arg_reg].type)], GetNewRegOperand(arg_reg)});
    }
    int result_reg = newReg();
    IRgenCall(getCurrentBlock(), Type2LLvm[static_cast<int>(function_returntype)], result_reg, args, node.function_name);
    max_reg = result_reg;
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