#ifndef MACHINE_IR_H
#define MACHINE_IR_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>

// RISC-V指令操作码
enum class RISCVOpcode {
    // 算术运算指令
    ADD, ADDI, SUB, MUL, DIV, REM,
    // 浮点运算指令  
    FADD_S, FSUB_S, FMUL_S, FDIV_S,
    // 逻辑运算指令
    AND, ANDI, OR, ORI, XOR, XORI,
    // 移位指令
    SLL, SLLI, SRL, SRLI, SRA, SRAI,
    // 比较指令
    SLT, SLTI, SLTU, SLTIU,
    // 浮点比较指令
    FEQ_S, FLT_S, FLE_S,
    // 内存访问指令
    LW, LB, LH, LBU, LHU, SW, SB, SH,
    FLW, FSW,
    // 分支指令
    BEQ, BNE, BLT, BGE, BLTU, BGEU,
    // 跳转指令
    JAL, JALR,
    // 系统指令
    ECALL, EBREAK,
    // 伪指令
    LI, LA, MV, NOP, RET,
    // 类型转换
    FCVT_S_W, FCVT_W_S,
    // 浮点移动
    FMV_S,
    // 其他
    LUI, AUIPC
};

// RISC-V寄存器编号
enum class RISCVReg {
    // 通用寄存器
    X0 = 0, X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15,
    X16, X17, X18, X19, X20, X21, X22, X23, X24, X25, X26, X27, X28, X29, X30, X31,
    
    // 浮点寄存器
    F0 = 32, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31,
    
    // 特殊寄存器标识
    INVALID = 255
};

// 机器操作数基类
class MachineOperand {
public:
    enum OperandType {
        REGISTER,
        IMMEDIATE,
        MEMORY,
        LABEL
    };

protected:
    OperandType type;

public:
    MachineOperand(OperandType t) : type(t) {}
    virtual ~MachineOperand() = default;
    
    OperandType getType() const { return type; }
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<MachineOperand> clone() const = 0;
};

// 寄存器操作数
class RegisterOperand : public MachineOperand {
private:
    RISCVReg reg;
    bool isFloat;
    bool isVirtualReg;  // 是否为虚拟寄存器
    int virtualRegNum;  // 虚拟寄存器编号

public:
    // 物理寄存器构造函数
    RegisterOperand(RISCVReg r, bool isF = false) 
        : MachineOperand(REGISTER), reg(r), isFloat(isF), 
          isVirtualReg(false), virtualRegNum(-1) {}
    
    // 虚拟寄存器构造函数
    RegisterOperand(int vReg, bool isF = false)
        : MachineOperand(REGISTER), reg(RISCVReg::INVALID), isFloat(isF),
          isVirtualReg(true), virtualRegNum(vReg) {}
    
    RISCVReg getReg() const { return reg; }
    bool isFloatReg() const { return isFloat; }
    bool isVirtual() const { return isVirtualReg; }
    int getVirtualReg() const { return virtualRegNum; }
    
    // 设置物理寄存器（用于寄存器分配后）
    void setPhysicalReg(RISCVReg r) { 
        reg = r; 
        isVirtualReg = false; 
    }
    
    std::string toString() const override;
    std::unique_ptr<MachineOperand> clone() const override {
        if (isVirtualReg) {
            return std::make_unique<RegisterOperand>(virtualRegNum, isFloat);
        } else {
            return std::make_unique<RegisterOperand>(reg, isFloat);
        }
    }
};

// 立即数操作数
class ImmediateOperand : public MachineOperand {
private:
    int64_t value;

public:
    ImmediateOperand(int64_t val) : MachineOperand(IMMEDIATE), value(val) {}
    
    int64_t getValue() const { return value; }
    
    std::string toString() const override {
        return std::to_string(value);
    }
    
    std::unique_ptr<MachineOperand> clone() const override {
        return std::make_unique<ImmediateOperand>(value);
    }
};

// 内存操作数
class MemoryOperand : public MachineOperand {
private:
    std::unique_ptr<RegisterOperand> base;
    int64_t offset;

public:
    MemoryOperand(std::unique_ptr<RegisterOperand> b, int64_t off = 0) 
        : MachineOperand(MEMORY), base(std::move(b)), offset(off) {}
    
    const RegisterOperand* getBase() const { return base.get(); }
    int64_t getOffset() const { return offset; }
    
    std::string toString() const override {
        if (offset == 0) {
            return "(" + base->toString() + ")";
        }
        return std::to_string(offset) + "(" + base->toString() + ")";
    }
    
    std::unique_ptr<MachineOperand> clone() const override {
        auto clonedBase = std::unique_ptr<RegisterOperand>(
            static_cast<RegisterOperand*>(base->clone().release()));
        return std::make_unique<MemoryOperand>(std::move(clonedBase), offset);
    }
};

// 标签操作数
class MachineLabelOperand : public MachineOperand {
private:
    std::string label;

public:
    MachineLabelOperand(const std::string& lbl) : MachineOperand(LABEL), label(lbl) {}
    
    const std::string& getLabel() const { return label; }
    
    std::string toString() const override { return label; }
    
    std::unique_ptr<MachineOperand> clone() const override {
        return std::make_unique<MachineLabelOperand>(label);
    }
};

// 机器指令类
class MachineInstruction {
private:
    RISCVOpcode opcode;
    std::vector<std::unique_ptr<MachineOperand>> operands;
    std::string comment;

public:
    MachineInstruction(RISCVOpcode op) : opcode(op) {}
    
    void addOperand(std::unique_ptr<MachineOperand> operand) {
        operands.push_back(std::move(operand));
    }
    
    void setComment(const std::string& c) { comment = c; }
    
    RISCVOpcode getOpcode() const { return opcode; }
    const std::vector<std::unique_ptr<MachineOperand>>& getOperands() const { return operands; }
    const std::string& getComment() const { return comment; }
    
    std::string toString() const;
};

// 机器基本块
class MachineBasicBlock {
private:
    int id;
    std::string label;
    std::vector<std::unique_ptr<MachineInstruction>> instructions;

public:
    MachineBasicBlock(int blockId, const std::string& lbl = "") : id(blockId), label(lbl) {
        if (label.empty()) {
            label = ".L" + std::to_string(blockId);
        }
    }
    
    void addInstruction(std::unique_ptr<MachineInstruction> inst) {
        instructions.push_back(std::move(inst));
    }
    
    const std::string& getLabel() const { return label; }
    int getId() const { return id; }
    const std::vector<std::unique_ptr<MachineInstruction>>& getInstructions() const { return instructions; }
    
    void print(std::ostream& os) const;
};

// 机器函数
class MachineFunction {
private:
    std::string name;
    std::vector<std::unique_ptr<MachineBasicBlock>> blocks;
    std::map<int, MachineBasicBlock*> blockMap; // LLVM block ID -> Machine block

public:
    MachineFunction(const std::string& funcName) : name(funcName) {}
    
    MachineBasicBlock* createBlock(int llvmBlockId, const std::string& label = "") {
        auto block = std::make_unique<MachineBasicBlock>(llvmBlockId, label);
        auto* ptr = block.get();
        blockMap[llvmBlockId] = ptr;
        blocks.push_back(std::move(block));
        return ptr;
    }
    
    MachineBasicBlock* getBlock(int llvmBlockId) {
        auto it = blockMap.find(llvmBlockId);
        return (it != blockMap.end()) ? it->second : nullptr;
    }
    
    const std::string& getName() const { return name; }
    const std::vector<std::unique_ptr<MachineBasicBlock>>& getBlocks() const { return blocks; }
    
    void print(std::ostream& os) const;
};

// 机器模块
class MachineModule {
private:
    std::vector<std::unique_ptr<MachineFunction>> functions;
    std::vector<std::string> globalData;

public:
    MachineFunction* createFunction(const std::string& name) {
        auto func = std::make_unique<MachineFunction>(name);
        auto* ptr = func.get();
        functions.push_back(std::move(func));
        return ptr;
    }
    
    void addGlobalData(const std::string& data) {
        globalData.push_back(data);
    }
    
    const std::vector<std::unique_ptr<MachineFunction>>& getFunctions() const { return functions; }
    const std::vector<std::string>& getGlobalData() const { return globalData; }
    
    void print(std::ostream& os) const;
};

#endif // MACHINE_IR_H 