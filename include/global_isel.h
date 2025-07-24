#ifndef GLOBAL_ISEL_H
#define GLOBAL_ISEL_H

#include "instruction.h"
#include "block.h"
#include "machine_ir.h"
#include <unordered_map>
#include <stack>

// 寄存器分配器简单实现
class RegisterAllocator {
private:
    int nextIntReg;
    int nextFloatReg;
    std::unordered_map<int, RISCVReg> llvmToMachineReg; // LLVM虚拟寄存器 -> 物理寄存器
    std::set<RISCVReg> usedIntRegs;
    std::set<RISCVReg> usedFloatRegs;
    
    // RISC-V调用约定：
    // a0-a7 (x10-x17): 参数传递/返回值
    // t0-t6 (x5-x7, x28-x31): 临时寄存器
    // s0-s11 (x8-x9, x18-x27): 保存寄存器
    // fa0-fa7 (f10-f17): 浮点参数/返回值
    // ft0-ft11 (f0-f7, f28-f31): 浮点临时寄存器
    
public:
    RegisterAllocator() : nextIntReg(5), nextFloatReg(0) {} // 从t0开始分配
    
    RISCVReg allocateIntReg(int llvmReg = -1);
    RISCVReg allocateFloatReg(int llvmReg = -1);
    RISCVReg getMachineReg(int llvmReg);
    void bindRegister(int llvmReg, RISCVReg machineReg);
    
    // 获取函数参数寄存器
    RISCVReg getArgReg(int argIndex, bool isFloat);
    RISCVReg getReturnReg(bool isFloat);
};

// GlobalISel指令选择器
class GlobalISel {
private:
    LLVMIR& llvmIR;
    MachineModule machineModule;
    RegisterAllocator regAlloc;
    MachineFunction* currentFunc;
    std::unordered_map<int, std::string> labelMap; // LLVM label -> Machine label
    
    // 栈管理
    int currentStackOffset;
    int totalStackSize; // 总栈大小（用于尾声恢复）
    std::unordered_map<int, int> allocaOffsets; // LLVM寄存器 -> 栈偏移量
    
    // 当前上下文
    std::stack<MachineBasicBlock*> blockStack;
    
public:
    GlobalISel(LLVMIR& ir) : llvmIR(ir), currentFunc(nullptr) {}
    
    // 主要转换函数
    MachineModule& selectInstructions();
    
private:
    // 指令选择函数
    void selectInstruction(Instruction inst, MachineBasicBlock* block);
    void selectLoadInstruction(LoadInstruction* inst, MachineBasicBlock* block);
    void selectStoreInstruction(StoreInstruction* inst, MachineBasicBlock* block);
    void selectArithmeticInstruction(ArithmeticInstruction* inst, MachineBasicBlock* block);
    void selectIcmpInstruction(IcmpInstruction* inst, MachineBasicBlock* block);
    void selectFcmpInstruction(FcmpInstruction* inst, MachineBasicBlock* block);
    void selectBrCondInstruction(BrCondInstruction* inst, MachineBasicBlock* block);
    void selectBrUncondInstruction(BrUncondInstruction* inst, MachineBasicBlock* block);
    void selectRetInstruction(RetInstruction* inst, MachineBasicBlock* block);
    void selectCallInstruction(CallInstruction* inst, MachineBasicBlock* block);
    void selectAllocaInstruction(AllocaInstruction* inst, MachineBasicBlock* block);
    void selectGetElementptrInstruction(GetElementptrInstruction* inst, MachineBasicBlock* block);
    void selectGlobalVarDefineInstruction(GlobalVarDefineInstruction* inst);
    void selectGlobalStringConstInstruction(GlobalStringConstInstruction* inst);
    
    // 辅助函数
    std::unique_ptr<MachineOperand> convertOperand(Operand operand, bool isFloat = false);
    RISCVOpcode mapArithmeticOpcode(LLVMIROpcode llvmOp, LLVMType type);
    RISCVOpcode mapIcmpOpcode(IcmpCond cond);
    RISCVOpcode mapFcmpOpcode(FcmpCond cond);
    RISCVOpcode mapBranchOpcode(IcmpCond cond);
    RISCVOpcode mapBranchOpcodeFcmp(FcmpCond cond);
    RISCVOpcode mapLoadOpcode(LLVMType type);
    RISCVOpcode mapStoreOpcode(LLVMType type);
    
    // 类型转换
    void insertTypeConversion(MachineBasicBlock* block, int srcReg, LLVMType srcType, 
                             int dstReg, LLVMType dstType);
    
    // 立即数处理
    void loadImmediate(MachineBasicBlock* block, int64_t value, RISCVReg dstReg);
    bool isValidImm12(int64_t value) { return value >= -2048 && value <= 2047; }
    
    // 栈管理
    void generateFunctionPrologue(MachineBasicBlock* entryBlock);
    void generateFunctionEpilogue(MachineBasicBlock* exitBlock);
    int allocateStackSpace(int size);
    std::unique_ptr<MemoryOperand> createStackOperand(int offset);
    
    // 标签管理
    std::string getLabelName(int llvmLabel);
    std::string getFunctionLabel(const std::string& funcName);
    std::string getGlobalLabel(const std::string& globalName);
};

// RISC-V汇编代码生成器
class RISCVAsmPrinter {
private:
    MachineModule& module;
    std::ostream& output;
    
public:
    RISCVAsmPrinter(MachineModule& mod, std::ostream& os) : module(mod), output(os) {}
    
    void printAssembly();
    
private:
    void printGlobalData();
    void printFunction(const MachineFunction& func);
    void printBasicBlock(const MachineBasicBlock& block);
    void printInstruction(const MachineInstruction& inst);
    
    std::string opcodeToString(RISCVOpcode opcode);
    std::string regToString(RISCVReg reg);
};

#endif // GLOBAL_ISEL_H 