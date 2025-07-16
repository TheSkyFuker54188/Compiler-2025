#pragma once

#include "block.h"
#include "instruction.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace riscv {

// ===================================================================
// RISC-V寄存器定义
// ===================================================================

enum class RISCVRegister {
    // 整数寄存器
    ZERO = 0,   // x0: 硬编码为0
    RA = 1,     // x1: 返回地址  
    SP = 2,     // x2: 栈指针
    GP = 3,     // x3: 全局指针
    TP = 4,     // x4: 线程指针
    
    // 临时寄存器
    T0 = 5, T1 = 6, T2 = 7,
    T3 = 28, T4 = 29, T5 = 30, T6 = 31,
    
    // 保存寄存器
    S0 = 8, S1 = 9,  // S0也是帧指针
    S2 = 18, S3 = 19, S4 = 20, S5 = 21,
    S6 = 22, S7 = 23, S8 = 24, S9 = 25,
    S10 = 26, S11 = 27,
    
    // 参数/返回值寄存器
    A0 = 10, A1 = 11, A2 = 12, A3 = 13,
    A4 = 14, A5 = 15, A6 = 16, A7 = 17,
    
    // 浮点寄存器
    FT0 = 32, FT1 = 33, FT2 = 34, FT3 = 35,
    FT4 = 36, FT5 = 37, FT6 = 38, FT7 = 39,
    FS0 = 40, FS1 = 41,
    FA0 = 42, FA1 = 43, FA2 = 44, FA3 = 45,
    FA4 = 46, FA5 = 47, FA6 = 48, FA7 = 49,
    FS2 = 50, FS3 = 51, FS4 = 52, FS5 = 53,
    FS6 = 54, FS7 = 55, FS8 = 56, FS9 = 57,
    FS10 = 58, FS11 = 59,
    FT8 = 60, FT9 = 61, FT10 = 62, FT11 = 63,
    
    // 虚拟寄存器标记
    VIRTUAL_BASE = 1000
};

// ===================================================================
// RISC-V指令表示
// ===================================================================

struct RISCVInstruction {
    std::string mnemonic;
    std::vector<std::string> operands;
    std::string comment;
    
    RISCVInstruction(const std::string& mn) : mnemonic(mn) {}
    RISCVInstruction(const std::string& mn, const std::vector<std::string>& ops) 
        : mnemonic(mn), operands(ops) {}
    
    std::string toString() const {
        std::string result = "    " + mnemonic;
        if (!operands.empty()) {
            result += " ";
            for (size_t i = 0; i < operands.size(); ++i) {
                if (i > 0) result += ", ";
                result += operands[i];
            }
        }
        if (!comment.empty()) {
            result += "  # " + comment;
        }
        return result;
    }
};

// ===================================================================
// RISC-V函数和基本块
// ===================================================================

struct RISCVBasicBlock {
    std::string label;
    std::vector<RISCVInstruction> instructions;
    
    RISCVBasicBlock(const std::string& lbl) : label(lbl) {}
    
    void addInstruction(const RISCVInstruction& inst) {
        instructions.push_back(inst);
    }
    
    void emit(std::ostream& os) const {
        if (!label.empty()) {
            os << label << ":\n";
        }
        for (const auto& inst : instructions) {
            os << inst.toString() << "\n";
        }
    }
};

struct RISCVFunction {
    std::string name;
    std::vector<std::unique_ptr<RISCVBasicBlock>> blocks;
    int stack_size = 0;
    
    RISCVFunction(const std::string& n) : name(n) {}
    
    RISCVBasicBlock* createBlock(const std::string& label) {
        auto block = std::make_unique<RISCVBasicBlock>(label);
        RISCVBasicBlock* ptr = block.get();
        blocks.push_back(std::move(block));
        return ptr;
    }
    
    void emit(std::ostream& os) const {
        os << ".globl " << name << "\n";
        os << ".type " << name << ", @function\n";
        os << name << ":\n";
        
        for (const auto& block : blocks) {
            block->emit(os);
        }
        
        os << ".size " << name << ", .-" << name << "\n\n";
    }
};

// ===================================================================
// 虚拟寄存器管理
// ===================================================================

class VirtualRegisterManager {
private:
    int next_virtual_reg_ = 0;
    std::map<int, std::string> virtual_reg_names_;
    
public:
    int allocateVirtualReg() {
        int reg_id = next_virtual_reg_++;
        virtual_reg_names_[reg_id] = "%v" + std::to_string(reg_id);
        return reg_id;
    }
    
    std::string getVirtualRegName(int reg_id) const {
        auto it = virtual_reg_names_.find(reg_id);
        return (it != virtual_reg_names_.end()) ? it->second : "%v" + std::to_string(reg_id);
    }
    
    void reset() {
        next_virtual_reg_ = 0;
        virtual_reg_names_.clear();
    }
};

// ===================================================================
// 指令选择器主类
// ===================================================================

class InstructionSelector {
private:
    // 输出管理
    std::ostream& output_;
    
    // 当前处理状态
    RISCVFunction* current_function_ = nullptr;
    RISCVBasicBlock* current_block_ = nullptr;
    
    // 寄存器管理
    VirtualRegisterManager vreg_manager_;
    std::map<int, int> llvm_to_virtual_;  // LLVM寄存器 -> 虚拟寄存器
    
    // 全局数据
    std::vector<std::string> global_data_;
    
    // 辅助方法
    std::string getRegisterName(RISCVRegister reg) const;
    std::string getVirtualRegName(int llvm_reg);
    std::string getOperandString(Operand op);
    std::string getLabelName(int label_id);
    
    // 指令翻译方法
    void translateLoad(const LoadInstruction& inst);
    void translateStore(const StoreInstruction& inst);
    void translateArithmetic(const ArithmeticInstruction& inst);
    void translateIcmp(const IcmpInstruction& inst);
    void translateFcmp(const FcmpInstruction& inst);
    void translateBranch(const BrCondInstruction& inst);
    void translateBranch(const BrUncondInstruction& inst);
    void translateReturn(const RetInstruction& inst);
    void translateCall(const CallInstruction& inst);
    void translateAlloca(const AllocaInstruction& inst);
    void translateGetelementptr(const GetElementptrInstruction& inst);
    void translateGlobalVar(const GlobalVarDefineInstruction& inst);
    void translateGlobalString(const GlobalStringConstInstruction& inst);
    void translateConvert(const BasicInstruction& inst);
    
    // 函数处理
    void processFunction(FuncDefInstruction func_def, 
                        const std::map<int, LLVMBlock>& blocks);
    void processFunctionProlog(const std::string& func_name);
    void processFunctionEpilog();
    
    // 基本块处理
    void processBasicBlock(LLVMBlock block, int block_id);
    
public:
    InstructionSelector(std::ostream& output) : output_(output) {}
    
    // 主入口点
    void selectInstructions(const LLVMIR& ir);
    
    // 辅助方法
    void emitHeader();
    void emitGlobalData();
    void emitLibraryDeclarations();
};

// ===================================================================
// 工具函数
// ===================================================================

std::string riscvRegisterName(RISCVRegister reg);
bool isIntegerType(LLVMType type);
bool isFloatType(LLVMType type);
std::string getTypeSize(LLVMType type);

} // namespace riscv
