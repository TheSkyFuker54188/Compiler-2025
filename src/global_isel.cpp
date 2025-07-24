#include "global_isel.h"
#include <cassert>
#include <algorithm>

// RegisterAllocator实现
RISCVReg RegisterAllocator::allocateIntReg(int llvmReg) {
    // 简单的寄存器分配策略：使用临时寄存器t0-t6和s0-s11
    static RISCVReg tempRegs[] = {
        RISCVReg::X5, RISCVReg::X6, RISCVReg::X7,  // t0-t2
        RISCVReg::X28, RISCVReg::X29, RISCVReg::X30, RISCVReg::X31, // t3-t6
        RISCVReg::X8, RISCVReg::X9,   // s0-s1
        RISCVReg::X18, RISCVReg::X19, RISCVReg::X20, RISCVReg::X21, // s2-s5
        RISCVReg::X22, RISCVReg::X23, RISCVReg::X24, RISCVReg::X25, // s6-s9
        RISCVReg::X26, RISCVReg::X27  // s10-s11
    };
    
    RISCVReg allocatedReg = tempRegs[nextIntReg % (sizeof(tempRegs) / sizeof(tempRegs[0]))];
    nextIntReg++;
    
    if (llvmReg != -1) {
        llvmToMachineReg[llvmReg] = allocatedReg;
    }
    
    usedIntRegs.insert(allocatedReg);
    return allocatedReg;
}

RISCVReg RegisterAllocator::allocateFloatReg(int llvmReg) {
    // 浮点寄存器分配：使用ft0-ft11和fs0-fs11
    static RISCVReg floatRegs[] = {
        RISCVReg::F0, RISCVReg::F1, RISCVReg::F2, RISCVReg::F3,   // ft0-ft3
        RISCVReg::F4, RISCVReg::F5, RISCVReg::F6, RISCVReg::F7,   // ft4-ft7
        RISCVReg::F28, RISCVReg::F29, RISCVReg::F30, RISCVReg::F31, // ft8-ft11
        RISCVReg::F8, RISCVReg::F9,   // fs0-fs1
        RISCVReg::F18, RISCVReg::F19, RISCVReg::F20, RISCVReg::F21, // fs2-fs5
        RISCVReg::F22, RISCVReg::F23, RISCVReg::F24, RISCVReg::F25, // fs6-fs9
        RISCVReg::F26, RISCVReg::F27  // fs10-fs11
    };
    
    RISCVReg allocatedReg = floatRegs[nextFloatReg % (sizeof(floatRegs) / sizeof(floatRegs[0]))];
    nextFloatReg++;
    
    if (llvmReg != -1) {
        llvmToMachineReg[llvmReg] = allocatedReg;
    }
    
    usedFloatRegs.insert(allocatedReg);
    return allocatedReg;
}

RISCVReg RegisterAllocator::getMachineReg(int llvmReg) {
    auto it = llvmToMachineReg.find(llvmReg);
    if (it != llvmToMachineReg.end()) {
        return it->second;
    }
    return RISCVReg::INVALID;
}

void RegisterAllocator::bindRegister(int llvmReg, RISCVReg machineReg) {
    llvmToMachineReg[llvmReg] = machineReg;
}

RISCVReg RegisterAllocator::getArgReg(int argIndex, bool isFloat) {
    if (isFloat) {
        // fa0-fa7 用于浮点参数
        if (argIndex < 8) {
            return static_cast<RISCVReg>(static_cast<int>(RISCVReg::F10) + argIndex);
        }
    } else {
        // a0-a7 用于整数参数
        if (argIndex < 8) {
            return static_cast<RISCVReg>(static_cast<int>(RISCVReg::X10) + argIndex);
        }
    }
    return RISCVReg::INVALID; // 超过8个参数需要使用栈传递
}

RISCVReg RegisterAllocator::getReturnReg(bool isFloat) {
    return isFloat ? RISCVReg::F10 : RISCVReg::X10; // fa0 或 a0
}

// GlobalISel实现
MachineModule& GlobalISel::selectInstructions() {
    // 处理全局变量和字符串常量
    for (auto& globalInst : llvmIR.global_def) {
        if (auto* globalVar = dynamic_cast<GlobalVarDefineInstruction*>(globalInst)) {
            selectGlobalVarDefineInstruction(globalVar);
        } else if (auto* globalStr = dynamic_cast<GlobalStringConstInstruction*>(globalInst)) {
            selectGlobalStringConstInstruction(globalStr);
        }
    }
    
    // 处理函数
    for (auto& funcBlockPair : llvmIR.function_block_map) {
        FuncDefInstruction funcDef = funcBlockPair.first;
        auto& blockMap = funcBlockPair.second;
        
        // 创建机器函数
        currentFunc = machineModule.createFunction(funcDef->Func_name);
        
        // 重置寄存器分配器和栈管理
        regAlloc = RegisterAllocator();
        currentStackOffset = 0;
        totalStackSize = 0;
        allocaOffsets.clear();
        
        // 处理函数参数
        for (size_t i = 0; i < funcDef->formals.size(); ++i) {
            LLVMType paramType = funcDef->formals[i];
            Operand paramReg = funcDef->formals_reg[i];
            
            bool isFloat = (paramType == FLOAT32);
            RISCVReg argReg = regAlloc.getArgReg(i, isFloat);
            
            if (auto* regOp = dynamic_cast<RegOperand*>(paramReg)) {
                regAlloc.bindRegister(regOp->GetRegNo(), argReg);
            }
        }
        
        // 按顺序处理基本块
        MachineBasicBlock* entryBlock = nullptr;
        for (auto& blockPair : blockMap) {
            int blockId = blockPair.first;
            LLVMBlock llvmBlock = blockPair.second;
            
            MachineBasicBlock* machineBlock = currentFunc->createBlock(blockId);
            
            // 记录入口块
            if (entryBlock == nullptr) {
                entryBlock = machineBlock;
            }
            
            // 转换块中的指令
            for (auto& inst : llvmBlock->Instruction_list) {
                selectInstruction(inst, machineBlock);
            }
        }
        
        // 为函数添加序言和尾声
        if (entryBlock && currentStackOffset > 0) {
            // 确保栈大小16字节对齐
            int alignedStackSize = ((currentStackOffset + 15) / 16) * 16;
            totalStackSize = alignedStackSize; // 保存总栈大小供尾声使用
            currentStackOffset = alignedStackSize; // 设置对齐后的大小
            generateFunctionPrologue(entryBlock);
        }
    }
    
    return machineModule;
}

void GlobalISel::selectInstruction(Instruction inst, MachineBasicBlock* block) {
    switch (inst->GetOpcode()) {
        case LOAD:
            selectLoadInstruction(dynamic_cast<LoadInstruction*>(inst), block);
            break;
        case STORE:
            selectStoreInstruction(dynamic_cast<StoreInstruction*>(inst), block);
            break;
        case ADD:
        case SUB:
        case MUL_OP:
        case DIV_OP:
        case FADD:
        case FSUB:
        case FMUL:
        case FDIV:
            selectArithmeticInstruction(dynamic_cast<ArithmeticInstruction*>(inst), block);
            break;
        case ICMP:
            selectIcmpInstruction(dynamic_cast<IcmpInstruction*>(inst), block);
            break;
        case FCMP:
            selectFcmpInstruction(dynamic_cast<FcmpInstruction*>(inst), block);
            break;
        case BR_COND:
            selectBrCondInstruction(dynamic_cast<BrCondInstruction*>(inst), block);
            break;
        case BR_UNCOND:
            selectBrUncondInstruction(dynamic_cast<BrUncondInstruction*>(inst), block);
            break;
        case RET:
            selectRetInstruction(dynamic_cast<RetInstruction*>(inst), block);
            break;
        case CALL:
            selectCallInstruction(dynamic_cast<CallInstruction*>(inst), block);
            break;
        case ALLOCA:
            selectAllocaInstruction(dynamic_cast<AllocaInstruction*>(inst), block);
            break;
        case GETELEMENTPTR:
            selectGetElementptrInstruction(dynamic_cast<GetElementptrInstruction*>(inst), block);
            break;
        default:
            // 其他指令暂时跳过或添加注释
            auto machineInst = std::make_unique<MachineInstruction>(RISCVOpcode::NOP);
            machineInst->setComment("Unsupported LLVM instruction");
            block->addInstruction(std::move(machineInst));
            break;
    }
}

void GlobalISel::selectLoadInstruction(LoadInstruction* inst, MachineBasicBlock* block) {
    auto dstOperand = convertOperand(inst->GetResult(), inst->GetType() == FLOAT32);
    
    RISCVOpcode loadOp = mapLoadOpcode(inst->GetType());
    
    // 检查是否从栈上加载
    std::unique_ptr<MachineOperand> srcOperand;
    if (auto* ptrReg = dynamic_cast<RegOperand*>(inst->GetPointer())) {
        int ptrRegNo = ptrReg->GetRegNo();
        auto it = allocaOffsets.find(ptrRegNo);
        if (it != allocaOffsets.end()) {
            // 从栈上加载：lw dst, offset(sp)
            srcOperand = createStackOperand(it->second);
        } else {
            // 从普通地址加载
            srcOperand = convertOperand(inst->GetPointer());
        }
    } else {
        srcOperand = convertOperand(inst->GetPointer());
    }
    
    auto machineInst = std::make_unique<MachineInstruction>(loadOp);
    machineInst->addOperand(std::move(dstOperand));
    machineInst->addOperand(std::move(srcOperand));
    
    block->addInstruction(std::move(machineInst));
}

void GlobalISel::selectStoreInstruction(StoreInstruction* inst, MachineBasicBlock* block) {
    RISCVOpcode storeOp = mapStoreOpcode(inst->GetType());
    bool isFloat = (inst->GetType() == FLOAT32);
    
    // 处理源操作数 - store指令不能使用立即数作为源
    std::unique_ptr<MachineOperand> valueOperand;
    if (inst->GetValue()->GetOperandType() == BasicOperand::IMMI32 && !isFloat) {
        // 整数立即数：先加载到寄存器
        auto* immOp = static_cast<ImmI32Operand*>(inst->GetValue());
        int immVal = immOp->GetIntImmVal();
        RISCVReg tempReg = regAlloc.allocateIntReg();
        loadImmediate(block, immVal, tempReg);
        valueOperand = std::make_unique<RegisterOperand>(tempReg);
    } else {
        // 普通操作数（应该是寄存器）
        valueOperand = convertOperand(inst->GetValue(), isFloat);
    }
    
    // 检查是否存储到栈上
    std::unique_ptr<MachineOperand> ptrOperand;
    if (auto* ptrReg = dynamic_cast<RegOperand*>(inst->GetPointer())) {
        int ptrRegNo = ptrReg->GetRegNo();
        auto it = allocaOffsets.find(ptrRegNo);
        if (it != allocaOffsets.end()) {
            // 存储到栈上：sw src, offset(sp)
            ptrOperand = createStackOperand(it->second);
        } else {
            // 存储到普通地址
            ptrOperand = convertOperand(inst->GetPointer());
        }
    } else {
        ptrOperand = convertOperand(inst->GetPointer());
    }
    
    auto machineInst = std::make_unique<MachineInstruction>(storeOp);
    machineInst->addOperand(std::move(valueOperand));
    machineInst->addOperand(std::move(ptrOperand));
    
    block->addInstruction(std::move(machineInst));
}

void GlobalISel::selectArithmeticInstruction(ArithmeticInstruction* inst, MachineBasicBlock* block) {
    bool isFloat = (inst->GetType() == FLOAT32);
    auto dstOperand = convertOperand(inst->GetResult(), isFloat);
    auto op1 = convertOperand(inst->GetOp1(), isFloat);
    
    RISCVOpcode arithmeticOp = mapArithmeticOpcode(static_cast<LLVMIROpcode>(inst->GetOpcode()), inst->GetType());
    
    // 处理第二个操作数
    std::unique_ptr<MachineOperand> op2;
    if (inst->GetOp2()->GetOperandType() == BasicOperand::IMMI32 && !isFloat) {
        auto* immOp = static_cast<ImmI32Operand*>(inst->GetOp2());
        int64_t immVal = immOp->GetIntImmVal();
        
        // 检查是否可以使用立即数指令
        if (isValidImm12(immVal)) {
            switch (arithmeticOp) {
                case RISCVOpcode::ADD:
                    arithmeticOp = RISCVOpcode::ADDI;
                    op2 = std::make_unique<ImmediateOperand>(immVal);
                    break;
                case RISCVOpcode::AND:
                    arithmeticOp = RISCVOpcode::ANDI;
                    op2 = std::make_unique<ImmediateOperand>(immVal);
                    break;
                case RISCVOpcode::OR:
                    arithmeticOp = RISCVOpcode::ORI;
                    op2 = std::make_unique<ImmediateOperand>(immVal);
                    break;
                case RISCVOpcode::XOR:
                    arithmeticOp = RISCVOpcode::XORI;
                    op2 = std::make_unique<ImmediateOperand>(immVal);
                    break;
                default:
                    // 对于不能使用立即数的指令，将立即数加载到寄存器
                    RISCVReg tempReg = regAlloc.allocateIntReg();
                    loadImmediate(block, immVal, tempReg);
                    op2 = std::make_unique<RegisterOperand>(tempReg);
                    break;
            }
        } else {
            // 大立即数，加载到寄存器
            RISCVReg tempReg = regAlloc.allocateIntReg();
            loadImmediate(block, immVal, tempReg);
            op2 = std::make_unique<RegisterOperand>(tempReg);
        }
    } else {
        // 非立即数或浮点数
        op2 = convertOperand(inst->GetOp2(), isFloat);
    }
    
    auto machineInst = std::make_unique<MachineInstruction>(arithmeticOp);
    machineInst->addOperand(std::move(dstOperand));
    machineInst->addOperand(std::move(op1));
    machineInst->addOperand(std::move(op2));
    
    block->addInstruction(std::move(machineInst));
}

void GlobalISel::selectRetInstruction(RetInstruction* inst, MachineBasicBlock* block) {
    if (inst->GetRetVal() != nullptr) {
        // 有返回值的情况
        bool isFloat = (inst->GetType() == FLOAT32);
        auto retValueOperand = convertOperand(inst->GetRetVal(), isFloat);
        RISCVReg retReg = regAlloc.getReturnReg(isFloat);
        
        // 将返回值移动到返回寄存器
        if (isFloat) {
            // 浮点数移动：fmv.s fa0, src
            auto moveInst = std::make_unique<MachineInstruction>(RISCVOpcode::FMV_S);
            moveInst->addOperand(std::make_unique<RegisterOperand>(retReg, true));
            moveInst->addOperand(std::move(retValueOperand));
            moveInst->setComment("Move float return value");
            block->addInstruction(std::move(moveInst));
        } else {
            // 整数移动：mv a0, src
            auto moveInst = std::make_unique<MachineInstruction>(RISCVOpcode::MV);
            moveInst->addOperand(std::make_unique<RegisterOperand>(retReg, false));
            moveInst->addOperand(std::move(retValueOperand));
            block->addInstruction(std::move(moveInst));
        }
    }
    
    // 生成函数尾声（恢复栈指针）
    // 重新计算当前函数的栈大小（以防被其他函数覆盖）
    int functionStackSize = ((currentStackOffset + 15) / 16) * 16;
    if (functionStackSize > 0) {
        auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto spReg2 = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto stackImm = std::make_unique<ImmediateOperand>(functionStackSize);
        
        auto stackRestoreInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
        stackRestoreInst->addOperand(std::move(spReg));
        stackRestoreInst->addOperand(std::move(spReg2));
        stackRestoreInst->addOperand(std::move(stackImm));
        stackRestoreInst->setComment("Function epilogue: restore stack");
        
        block->addInstruction(std::move(stackRestoreInst));
    }
    
    // 生成返回指令
    auto retInst = std::make_unique<MachineInstruction>(RISCVOpcode::RET);
    block->addInstruction(std::move(retInst));
}

// 辅助函数实现
std::unique_ptr<MachineOperand> GlobalISel::convertOperand(Operand operand, bool isFloat) {
    switch (operand->GetOperandType()) {
        case BasicOperand::REG: {
            auto* regOp = static_cast<RegOperand*>(operand);
            int llvmRegNo = regOp->GetRegNo();
            
            RISCVReg machineReg = regAlloc.getMachineReg(llvmRegNo);
            if (machineReg == RISCVReg::INVALID) {
                // 分配新寄存器
                machineReg = isFloat ? regAlloc.allocateFloatReg(llvmRegNo) 
                                    : regAlloc.allocateIntReg(llvmRegNo);
            }
            
            // 检查寄存器类型是否匹配
            bool regIsFloat = (static_cast<int>(machineReg) >= 32);
            return std::make_unique<RegisterOperand>(machineReg, regIsFloat);
        }
        
        case BasicOperand::IMMI32: {
            auto* immOp = static_cast<ImmI32Operand*>(operand);
            return std::make_unique<ImmediateOperand>(immOp->GetIntImmVal());
        }
        
        case BasicOperand::IMMF32: {
            auto* immOp = static_cast<ImmF32Operand*>(operand);
            // 浮点立即数需要特殊处理，可能需要加载到寄存器
            // 这里简化处理，直接转换为整数表示
            union { float f; int32_t i; } converter;
            converter.f = immOp->GetFloatVal();
            return std::make_unique<ImmediateOperand>(converter.i);
        }
        
        case BasicOperand::GLOBAL: {
            auto* globalOp = static_cast<GlobalOperand*>(operand);
            return std::make_unique<MachineLabelOperand>(getGlobalLabel(globalOp->GetName()));
        }
        
        case BasicOperand::LABEL: {
            auto* labelOp = static_cast<LabelOperand*>(operand);
            return std::make_unique<MachineLabelOperand>(getLabelName(labelOp->GetLabelNo()));
        }
        
        default:
            return std::make_unique<ImmediateOperand>(0); // 默认值
    }
}

RISCVOpcode GlobalISel::mapArithmeticOpcode(LLVMIROpcode llvmOp, LLVMType type) {
    if (type == FLOAT32) {
        switch (llvmOp) {
            case FADD: return RISCVOpcode::FADD_S;
            case FSUB: return RISCVOpcode::FSUB_S;
            case FMUL: return RISCVOpcode::FMUL_S;
            case FDIV: return RISCVOpcode::FDIV_S;
            default: return RISCVOpcode::ADD; // 默认
        }
    } else {
        switch (llvmOp) {
            case ADD: return RISCVOpcode::ADD;
            case SUB: return RISCVOpcode::SUB;
            case MUL_OP: return RISCVOpcode::MUL;
            case DIV_OP: return RISCVOpcode::DIV;
            default: return RISCVOpcode::ADD; // 默认
        }
    }
}

RISCVOpcode GlobalISel::mapLoadOpcode(LLVMType type) {
    switch (type) {
        case I32: return RISCVOpcode::LW;
        case I8: return RISCVOpcode::LB;
        case FLOAT32: return RISCVOpcode::FLW;
        default: return RISCVOpcode::LW;
    }
}

RISCVOpcode GlobalISel::mapStoreOpcode(LLVMType type) {
    switch (type) {
        case I32: return RISCVOpcode::SW;
        case I8: return RISCVOpcode::SB;
        case FLOAT32: return RISCVOpcode::FSW;
        default: return RISCVOpcode::SW;
    }
}

std::string GlobalISel::getLabelName(int llvmLabel) {
    return ".L" + std::to_string(llvmLabel);
}

std::string GlobalISel::getFunctionLabel(const std::string& funcName) {
    return funcName;
}

std::string GlobalISel::getGlobalLabel(const std::string& globalName) {
    return globalName;
}

void GlobalISel::loadImmediate(MachineBasicBlock* block, int64_t value, RISCVReg dstReg) {
    if (isValidImm12(value)) {
        // 小立即数：addi dst, x0, imm
        auto addiInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
        addiInst->addOperand(std::make_unique<RegisterOperand>(dstReg));
        addiInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X0)); // zero
        addiInst->addOperand(std::make_unique<ImmediateOperand>(value));
        block->addInstruction(std::move(addiInst));
    } else {
        // 大立即数：lui + addi
        int32_t high = (value + 0x800) >> 12; // 考虑符号扩展
        int32_t low = value & 0xfff;
        
        // lui dst, high
        auto luiInst = std::make_unique<MachineInstruction>(RISCVOpcode::LUI);
        luiInst->addOperand(std::make_unique<RegisterOperand>(dstReg));
        luiInst->addOperand(std::make_unique<ImmediateOperand>(high));
        block->addInstruction(std::move(luiInst));
        
        // addi dst, dst, low (如果低12位不为0)
        if (low != 0) {
            auto addiInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
            addiInst->addOperand(std::make_unique<RegisterOperand>(dstReg));
            addiInst->addOperand(std::make_unique<RegisterOperand>(dstReg));
            addiInst->addOperand(std::make_unique<ImmediateOperand>(low));
            block->addInstruction(std::move(addiInst));
        }
    }
}

void GlobalISel::selectGlobalVarDefineInstruction(GlobalVarDefineInstruction* inst) {
    std::string globalData;
    globalData += ".globl " + inst->GetName() + "\n";
    globalData += inst->GetName() + ":";
    
    // 根据类型和初始值生成数据
    if (inst->GetType() == I32) {
        globalData += "\n\t.word\t";
        if (!inst->GetAttr().IntInitVals.empty()) {
            globalData += std::to_string(inst->GetAttr().IntInitVals[0]);
        } else {
            globalData += "0";
        }
    } else if (inst->GetType() == FLOAT32) {
        globalData += "\n\t.word\t";
        if (!inst->GetAttr().FloatInitVals.empty()) {
            union { float f; uint32_t i; } converter;
            converter.f = inst->GetAttr().FloatInitVals[0];
            globalData += "0x" + std::to_string(converter.i);
        } else {
            globalData += "0";
        }
    }
    
    machineModule.addGlobalData(globalData);
}

void GlobalISel::selectGlobalStringConstInstruction(GlobalStringConstInstruction* inst) {
    std::string globalData;
    globalData += inst->GetName() + ":";
    globalData += "\n\t.string\t\"" + inst->GetValue() + "\"";
    
    machineModule.addGlobalData(globalData);
}

// 其他待实现的函数可以添加默认实现
void GlobalISel::selectIcmpInstruction(IcmpInstruction* inst, MachineBasicBlock* block) {
    auto dstOperand = convertOperand(inst->GetResult());
    auto op1 = convertOperand(inst->GetOp1());
    auto op2 = convertOperand(inst->GetOp2());
    
    IcmpCond cond = inst->GetCond();
    
    // 根据比较条件选择适当的RISC-V指令
    switch (cond) {
        case eq: {
            // x == y: 使用xor + sltiu来实现
            // xor tmp, x, y; sltiu dst, tmp, 1
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // xor tmp, op1, op2
            auto xorInst = std::make_unique<MachineInstruction>(RISCVOpcode::XOR);
            xorInst->addOperand(std::move(tempRegOp));
            xorInst->addOperand(std::move(op1));
            xorInst->addOperand(std::move(op2));
            block->addInstruction(std::move(xorInst));
            
            // sltiu dst, tmp, 1
            auto sltiuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTIU);
            sltiuInst->addOperand(std::move(dstOperand));
            sltiuInst->addOperand(std::move(tempRegOp2));
            sltiuInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(sltiuInst));
            break;
        }
        
        case ne: {
            // x != y: 使用xor + sltu来实现
            // xor tmp, x, y; sltu dst, zero, tmp
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // xor tmp, op1, op2
            auto xorInst = std::make_unique<MachineInstruction>(RISCVOpcode::XOR);
            xorInst->addOperand(std::move(tempRegOp));
            xorInst->addOperand(std::move(op1));
            xorInst->addOperand(std::move(op2));
            block->addInstruction(std::move(xorInst));
            
            // sltu dst, zero, tmp
            auto sltuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTU);
            sltuInst->addOperand(std::move(dstOperand));
            sltuInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X0)); // zero
            sltuInst->addOperand(std::move(tempRegOp2));
            block->addInstruction(std::move(sltuInst));
            break;
        }
        
        case slt: {
            // x < y (signed): 直接使用slt
            auto sltInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLT);
            sltInst->addOperand(std::move(dstOperand));
            sltInst->addOperand(std::move(op1));
            sltInst->addOperand(std::move(op2));
            block->addInstruction(std::move(sltInst));
            break;
        }
        
        case sle: {
            // x <= y: 实现为 !(y < x)，即 slt tmp, y, x; xori dst, tmp, 1
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // slt tmp, op2, op1 (注意操作数顺序)
            auto sltInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLT);
            sltInst->addOperand(std::move(tempRegOp));
            sltInst->addOperand(std::move(op2));
            sltInst->addOperand(std::move(op1));
            block->addInstruction(std::move(sltInst));
            
            // xori dst, tmp, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::move(tempRegOp2));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        case sgt: {
            // x > y: 实现为 y < x，即 slt dst, y, x
            auto sltInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLT);
            sltInst->addOperand(std::move(dstOperand));
            sltInst->addOperand(std::move(op2)); // 注意操作数顺序
            sltInst->addOperand(std::move(op1));
            block->addInstruction(std::move(sltInst));
            break;
        }
        
        case sge: {
            // x >= y: 实现为 !(x < y)，即 slt tmp, x, y; xori dst, tmp, 1
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // slt tmp, op1, op2
            auto sltInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLT);
            sltInst->addOperand(std::move(tempRegOp));
            sltInst->addOperand(std::move(op1));
            sltInst->addOperand(std::move(op2));
            block->addInstruction(std::move(sltInst));
            
            // xori dst, tmp, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::move(tempRegOp2));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        case ult: {
            // x < y (unsigned): 使用sltu
            auto sltuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTU);
            sltuInst->addOperand(std::move(dstOperand));
            sltuInst->addOperand(std::move(op1));
            sltuInst->addOperand(std::move(op2));
            block->addInstruction(std::move(sltuInst));
            break;
        }
        
        case ule: {
            // x <= y (unsigned): 实现为 !(y < x)
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // sltu tmp, op2, op1
            auto sltuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTU);
            sltuInst->addOperand(std::move(tempRegOp));
            sltuInst->addOperand(std::move(op2));
            sltuInst->addOperand(std::move(op1));
            block->addInstruction(std::move(sltuInst));
            
            // xori dst, tmp, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::move(tempRegOp2));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        case ugt: {
            // x > y (unsigned): 实现为 y < x
            auto sltuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTU);
            sltuInst->addOperand(std::move(dstOperand));
            sltuInst->addOperand(std::move(op2));
            sltuInst->addOperand(std::move(op1));
            block->addInstruction(std::move(sltuInst));
            break;
        }
        
        case uge: {
            // x >= y (unsigned): 实现为 !(x < y)
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // sltu tmp, op1, op2
            auto sltuInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLTU);
            sltuInst->addOperand(std::move(tempRegOp));
            sltuInst->addOperand(std::move(op1));
            sltuInst->addOperand(std::move(op2));
            block->addInstruction(std::move(sltuInst));
            
            // xori dst, tmp, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::move(tempRegOp2));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        default: {
            // 默认情况：使用slt
            auto machineInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLT);
            machineInst->addOperand(std::move(dstOperand));
            machineInst->addOperand(std::move(op1));
            machineInst->addOperand(std::move(op2));
            machineInst->setComment("Unknown ICMP condition");
            block->addInstruction(std::move(machineInst));
            break;
        }
    }
}

void GlobalISel::selectFcmpInstruction(FcmpInstruction* inst, MachineBasicBlock* block) {
    auto dstOperand = convertOperand(inst->GetResult());
    auto op1 = convertOperand(inst->GetOp1(), true); // 浮点操作数
    auto op2 = convertOperand(inst->GetOp2(), true); // 浮点操作数
    
    FcmpCond cond = inst->GetCond();
    
    // 根据浮点比较条件选择适当的RISC-V指令
    switch (cond) {
        case OEQ: {
            // x == y (ordered equal): 使用feq.s
            auto feqInst = std::make_unique<MachineInstruction>(RISCVOpcode::FEQ_S);
            feqInst->addOperand(std::move(dstOperand));
            feqInst->addOperand(std::move(op1));
            feqInst->addOperand(std::move(op2));
            block->addInstruction(std::move(feqInst));
            break;
        }
        
        case ONE: {
            // x != y (ordered not equal): 实现为 !feq.s
            RISCVReg tempReg = regAlloc.allocateIntReg();
            auto tempRegOp = std::make_unique<RegisterOperand>(tempReg);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg);
            
            // feq.s tmp, op1, op2
            auto feqInst = std::make_unique<MachineInstruction>(RISCVOpcode::FEQ_S);
            feqInst->addOperand(std::move(tempRegOp));
            feqInst->addOperand(std::move(op1));
            feqInst->addOperand(std::move(op2));
            block->addInstruction(std::move(feqInst));
            
            // xori dst, tmp, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::move(tempRegOp2));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        case OLT: {
            // x < y (ordered less than): 使用flt.s
            auto fltInst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            fltInst->addOperand(std::move(dstOperand));
            fltInst->addOperand(std::move(op1));
            fltInst->addOperand(std::move(op2));
            block->addInstruction(std::move(fltInst));
            break;
        }
        
        case OLE: {
            // x <= y (ordered less than or equal): 使用fle.s
            auto fleInst = std::make_unique<MachineInstruction>(RISCVOpcode::FLE_S);
            fleInst->addOperand(std::move(dstOperand));
            fleInst->addOperand(std::move(op1));
            fleInst->addOperand(std::move(op2));
            block->addInstruction(std::move(fleInst));
            break;
        }
        
        case OGT: {
            // x > y (ordered greater than): 实现为 y < x，即 flt.s dst, y, x
            auto fltInst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            fltInst->addOperand(std::move(dstOperand));
            fltInst->addOperand(std::move(op2)); // 注意操作数顺序
            fltInst->addOperand(std::move(op1));
            block->addInstruction(std::move(fltInst));
            break;
        }
        
        case OGE: {
            // x >= y (ordered greater than or equal): 实现为 y <= x，即 fle.s dst, y, x
            auto fleInst = std::make_unique<MachineInstruction>(RISCVOpcode::FLE_S);
            fleInst->addOperand(std::move(dstOperand));
            fleInst->addOperand(std::move(op2)); // 注意操作数顺序
            fleInst->addOperand(std::move(op1));
            block->addInstruction(std::move(fleInst));
            break;
        }
        
        case UEQ: {
            // x == y (unordered or equal): 实现为 !(x < y || y < x)
            RISCVReg tempReg1 = regAlloc.allocateIntReg();
            RISCVReg tempReg2 = regAlloc.allocateIntReg();
            
            auto tempRegOp1 = std::make_unique<RegisterOperand>(tempReg1);
            auto tempRegOp1_2 = std::make_unique<RegisterOperand>(tempReg1);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg2);
            auto tempRegOp2_2 = std::make_unique<RegisterOperand>(tempReg2);
            
            // flt.s tmp1, op1, op2
            auto flt1Inst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            flt1Inst->addOperand(std::move(tempRegOp1));
            flt1Inst->addOperand(convertOperand(inst->GetOp1(), true));
            flt1Inst->addOperand(convertOperand(inst->GetOp2(), true));
            block->addInstruction(std::move(flt1Inst));
            
            // flt.s tmp2, op2, op1
            auto flt2Inst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            flt2Inst->addOperand(std::move(tempRegOp2));
            flt2Inst->addOperand(std::move(op2));
            flt2Inst->addOperand(std::move(op1));
            block->addInstruction(std::move(flt2Inst));
            
            // or tmp1, tmp1, tmp2
            auto orInst = std::make_unique<MachineInstruction>(RISCVOpcode::OR);
            orInst->addOperand(std::move(tempRegOp1_2));
            orInst->addOperand(std::move(tempRegOp1_2));
            orInst->addOperand(std::move(tempRegOp2_2));
            block->addInstruction(std::move(orInst));
            
            // xori dst, tmp1, 1
            auto xoriInst = std::make_unique<MachineInstruction>(RISCVOpcode::XORI);
            xoriInst->addOperand(std::move(dstOperand));
            xoriInst->addOperand(std::make_unique<RegisterOperand>(tempReg1));
            xoriInst->addOperand(std::make_unique<ImmediateOperand>(1));
            block->addInstruction(std::move(xoriInst));
            break;
        }
        
        case UNE: {
            // x != y (unordered or not equal): 实现为 x < y || y < x
            RISCVReg tempReg1 = regAlloc.allocateIntReg();
            RISCVReg tempReg2 = regAlloc.allocateIntReg();
            
            auto tempRegOp1 = std::make_unique<RegisterOperand>(tempReg1);
            auto tempRegOp1_2 = std::make_unique<RegisterOperand>(tempReg1);
            auto tempRegOp2 = std::make_unique<RegisterOperand>(tempReg2);
            auto tempRegOp2_2 = std::make_unique<RegisterOperand>(tempReg2);
            
            // flt.s tmp1, op1, op2
            auto flt1Inst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            flt1Inst->addOperand(std::move(tempRegOp1));
            flt1Inst->addOperand(convertOperand(inst->GetOp1(), true));
            flt1Inst->addOperand(convertOperand(inst->GetOp2(), true));
            block->addInstruction(std::move(flt1Inst));
            
            // flt.s tmp2, op2, op1
            auto flt2Inst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            flt2Inst->addOperand(std::move(tempRegOp2));
            flt2Inst->addOperand(std::move(op2));
            flt2Inst->addOperand(std::move(op1));
            block->addInstruction(std::move(flt2Inst));
            
            // or dst, tmp1, tmp2
            auto orInst = std::make_unique<MachineInstruction>(RISCVOpcode::OR);
            orInst->addOperand(std::move(dstOperand));
            orInst->addOperand(std::move(tempRegOp1_2));
            orInst->addOperand(std::move(tempRegOp2_2));
            block->addInstruction(std::move(orInst));
            break;
        }
        
        default: {
            // 默认情况：使用flt.s
            auto machineInst = std::make_unique<MachineInstruction>(RISCVOpcode::FLT_S);
            machineInst->addOperand(std::move(dstOperand));
            machineInst->addOperand(std::move(op1));
            machineInst->addOperand(std::move(op2));
            machineInst->setComment("Unknown FCMP condition");
            block->addInstruction(std::move(machineInst));
            break;
        }
    }
}

void GlobalISel::selectBrCondInstruction(BrCondInstruction* inst, MachineBasicBlock* block) {
    auto condOperand = convertOperand(inst->GetCond());
    auto trueLabelOperand = convertOperand(inst->GetTrueLabel());
    auto falseLabelOperand = convertOperand(inst->GetFalseLabel());
    
    // RISC-V条件分支策略：
    // 如果条件为真(非零)，跳转到真标签
    // 否则跳转到假标签
    
    // bne cond, zero, trueLabel  (如果cond != 0，跳转到trueLabel)
    auto bneInst = std::make_unique<MachineInstruction>(RISCVOpcode::BNE);
    bneInst->addOperand(std::move(condOperand));
    bneInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X0)); // zero register
    bneInst->addOperand(std::move(trueLabelOperand));
    block->addInstruction(std::move(bneInst));
    
    // jal zero, falseLabel  (无条件跳转到falseLabel)
    auto jalInst = std::make_unique<MachineInstruction>(RISCVOpcode::JAL);
    jalInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X0)); // zero register (不保存返回地址)
    jalInst->addOperand(std::move(falseLabelOperand));
    block->addInstruction(std::move(jalInst));
}

void GlobalISel::selectBrUncondInstruction(BrUncondInstruction* inst, MachineBasicBlock* block) {
    auto labelOperand = convertOperand(inst->GetLabel());
    
    // 使用 jal zero, label 实现无条件跳转
    auto jalInst = std::make_unique<MachineInstruction>(RISCVOpcode::JAL);
    jalInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X0)); // zero register (不保存返回地址)
    jalInst->addOperand(std::move(labelOperand));
    jalInst->setComment("Unconditional branch");
    
    block->addInstruction(std::move(jalInst));
}

void GlobalISel::selectCallInstruction(CallInstruction* inst, MachineBasicBlock* block) {
    // 简化实现：生成函数调用指令
    auto machineInst = std::make_unique<MachineInstruction>(RISCVOpcode::JAL);
    machineInst->addOperand(std::make_unique<RegisterOperand>(RISCVReg::X1)); // ra register
    machineInst->addOperand(std::make_unique<MachineLabelOperand>(inst->GetFuncName()));
    
    block->addInstruction(std::move(machineInst));
}

void GlobalISel::selectAllocaInstruction(AllocaInstruction* inst, MachineBasicBlock* block) {
    // 计算需要分配的空间大小
    int elementSize = 4; // 默认4字节，可以根据类型调整
    if (inst->GetType() == I32 || inst->GetType() == FLOAT32) {
        elementSize = 4;
    } else if (inst->GetType() == I64 || inst->GetType() == DOUBLE) {
        elementSize = 8;
    } else if (inst->GetType() == I8) {
        elementSize = 1;
    }
    
    int totalSize = elementSize;
    
    // 处理数组情况
    const std::vector<int>& dims = inst->GetDims();
    if (!dims.empty()) {
        for (int dim : dims) {
            totalSize *= dim;
        }
    }
    
    // 确保对齐到4字节边界
    if (totalSize % 4 != 0) {
        totalSize = ((totalSize + 3) / 4) * 4;
    }
    
    // 分配栈空间
    int stackOffset = allocateStackSpace(totalSize);
    
    // 将alloca的结果寄存器与栈偏移量关联
    if (auto* regOp = dynamic_cast<RegOperand*>(inst->GetResult())) {
        allocaOffsets[regOp->GetRegNo()] = stackOffset;
    }
    
    // 生成地址计算指令：addi dst_reg, sp, offset
    auto dstOperand = convertOperand(inst->GetResult());
    auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
    auto offsetImm = std::make_unique<ImmediateOperand>(stackOffset);
    
    auto addiInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
    addiInst->addOperand(std::move(dstOperand));
    addiInst->addOperand(std::move(spReg));
    addiInst->addOperand(std::move(offsetImm));
    
    // 添加详细的注释
    std::string comment = "Stack allocation: " + std::to_string(totalSize) + " bytes";
    if (!dims.empty()) {
        comment += " (array";
        for (size_t i = 0; i < dims.size(); ++i) {
            comment += (i == 0) ? "[" : "x";
            comment += std::to_string(dims[i]);
        }
        comment += "])";
    }
    addiInst->setComment(comment);
    
    block->addInstruction(std::move(addiInst));
}

void GlobalISel::selectGetElementptrInstruction(GetElementptrInstruction* inst, MachineBasicBlock* block) {
    auto dstOperand = convertOperand(inst->GetResult());
    auto baseOperand = convertOperand(inst->GetPtrVal());
    
    // 获取基本信息
    LLVMType elementType = inst->GetType();
    const std::vector<int>& dims = inst->GetDims();
    const std::vector<Operand>& indexes = inst->GetIndexes();
    
    // 计算元素大小
    int elementSize = 4; // 默认4字节 (i32, float)
    if (elementType == I8) elementSize = 1;
    else if (elementType == I64 || elementType == DOUBLE) elementSize = 8;
    
    if (indexes.empty()) {
        // 没有索引，直接复制基址
        auto moveInst = std::make_unique<MachineInstruction>(RISCVOpcode::MV);
        moveInst->addOperand(std::move(dstOperand));
        moveInst->addOperand(std::move(baseOperand));
        moveInst->setComment("Copy base address");
        block->addInstruction(std::move(moveInst));
        return;
    }
    
    // 开始地址计算
    RISCVReg currentAddrReg;
    
    // 首先处理基址
    if (auto* ptrReg = dynamic_cast<RegOperand*>(inst->GetPtrVal())) {
        int ptrRegNo = ptrReg->GetRegNo();
        auto it = allocaOffsets.find(ptrRegNo);
        if (it != allocaOffsets.end()) {
            // 栈上的数组：计算基址 = sp + offset
            currentAddrReg = regAlloc.allocateIntReg();
            auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
            auto offsetImm = std::make_unique<ImmediateOperand>(it->second);
            
            auto addiInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
            addiInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
            addiInst->addOperand(std::move(spReg));
            addiInst->addOperand(std::move(offsetImm));
            addiInst->setComment("Calculate array base address");
            block->addInstruction(std::move(addiInst));
        } else {
            // 普通指针，直接使用
            currentAddrReg = regAlloc.getMachineReg(ptrRegNo);
            if (currentAddrReg == RISCVReg::INVALID) {
                currentAddrReg = regAlloc.allocateIntReg(ptrRegNo);
            }
        }
    } else {
        // 其他情况，分配新寄存器
        currentAddrReg = regAlloc.allocateIntReg();
        auto moveInst = std::make_unique<MachineInstruction>(RISCVOpcode::MV);
        moveInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
        moveInst->addOperand(std::move(baseOperand));
        block->addInstruction(std::move(moveInst));
    }
    
         // 处理索引计算 - 简化版本，专注于正确的地址计算
     for (size_t i = 0; i < indexes.size(); ++i) {
         // 第一个索引通常是0（数组类型本身），跳过
         if (i == 0) {
             if (auto* immOp = dynamic_cast<ImmI32Operand*>(indexes[i])) {
                 if (immOp->GetIntImmVal() == 0) {
                     continue;
                 }
             }
         }
         
         // 计算当前维度的步长
         int stride = elementSize;
         
         // 对于多维数组，计算步长
         if (!dims.empty() && i > 0) {
             size_t dimIndex = i - 1; // 减去跳过的第一个索引
             if (dimIndex < dims.size()) {
                 // 计算从当前维度到最后维度的总大小
                 stride = elementSize;
                 for (size_t j = dimIndex + 1; j < dims.size(); ++j) {
                     stride *= dims[j];
                 }
             }
         }
         
         // 处理索引值
         if (auto* immOp = dynamic_cast<ImmI32Operand*>(indexes[i])) {
             int indexVal = immOp->GetIntImmVal();
             if (indexVal != 0) {
                 int offset = indexVal * stride;
                 
                 // 如果偏移量在12位立即数范围内，使用addi
                 if (isValidImm12(offset)) {
                     auto newAddrReg = regAlloc.allocateIntReg();
                     auto addiInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
                     addiInst->addOperand(std::make_unique<RegisterOperand>(newAddrReg));
                     addiInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
                     addiInst->addOperand(std::make_unique<ImmediateOperand>(offset));
                     addiInst->setComment("Add array index offset: " + std::to_string(indexVal) + " * " + std::to_string(stride));
                     block->addInstruction(std::move(addiInst));
                     currentAddrReg = newAddrReg;
                 } else {
                     // 大偏移量，先加载到寄存器再相加
                     RISCVReg offsetReg = regAlloc.allocateIntReg();
                     loadImmediate(block, offset, offsetReg);
                     
                     auto newAddrReg = regAlloc.allocateIntReg();
                     auto addInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADD);
                     addInst->addOperand(std::make_unique<RegisterOperand>(newAddrReg));
                     addInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
                     addInst->addOperand(std::make_unique<RegisterOperand>(offsetReg));
                     addInst->setComment("Add large array offset");
                     block->addInstruction(std::move(addInst));
                     currentAddrReg = newAddrReg;
                 }
             }
         } else {
             // 动态索引（变量索引）
             RISCVReg indexReg;
             if (auto* regOp = dynamic_cast<RegOperand*>(indexes[i])) {
                 indexReg = regAlloc.getMachineReg(regOp->GetRegNo());
                 if (indexReg == RISCVReg::INVALID) {
                     indexReg = regAlloc.allocateIntReg(regOp->GetRegNo());
                 }
             } else {
                 indexReg = regAlloc.allocateIntReg();
                 // 这种情况应该不会发生，但为了安全起见
                 loadImmediate(block, 0, indexReg);
             }
             
             // 计算 index * stride
             RISCVReg offsetReg = regAlloc.allocateIntReg();
             if (stride == 1) {
                 // 步长为1，直接使用索引
                 auto moveInst = std::make_unique<MachineInstruction>(RISCVOpcode::MV);
                 moveInst->addOperand(std::make_unique<RegisterOperand>(offsetReg));
                 moveInst->addOperand(std::make_unique<RegisterOperand>(indexReg));
                 block->addInstruction(std::move(moveInst));
             } else if (stride == 4) {
                 // 常见情况：int数组，左移2位
                 auto slliInst = std::make_unique<MachineInstruction>(RISCVOpcode::SLLI);
                 slliInst->addOperand(std::make_unique<RegisterOperand>(offsetReg));
                 slliInst->addOperand(std::make_unique<RegisterOperand>(indexReg));
                 slliInst->addOperand(std::make_unique<ImmediateOperand>(2));
                 slliInst->setComment("Multiply index by 4 (sizeof(int))");
                 block->addInstruction(std::move(slliInst));
             } else {
                 // 一般情况：index * stride
                 RISCVReg strideReg = regAlloc.allocateIntReg();
                 loadImmediate(block, stride, strideReg);
                 
                 auto mulInst = std::make_unique<MachineInstruction>(RISCVOpcode::MUL);
                 mulInst->addOperand(std::make_unique<RegisterOperand>(offsetReg));
                 mulInst->addOperand(std::make_unique<RegisterOperand>(indexReg));
                 mulInst->addOperand(std::make_unique<RegisterOperand>(strideReg));
                 mulInst->setComment("Calculate dynamic index offset");
                 block->addInstruction(std::move(mulInst));
             }
             
             // 将偏移量加到当前地址
             RISCVReg newAddrReg = regAlloc.allocateIntReg();
             auto addInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADD);
             addInst->addOperand(std::make_unique<RegisterOperand>(newAddrReg));
             addInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
             addInst->addOperand(std::make_unique<RegisterOperand>(offsetReg));
             addInst->setComment("Add dynamic offset to address");
             block->addInstruction(std::move(addInst));
             currentAddrReg = newAddrReg;
         }
     }
    
    // 将最终地址赋给结果寄存器
    auto finalMoveInst = std::make_unique<MachineInstruction>(RISCVOpcode::MV);
    finalMoveInst->addOperand(std::move(dstOperand));
    finalMoveInst->addOperand(std::make_unique<RegisterOperand>(currentAddrReg));
    finalMoveInst->setComment("Final array element address");
    block->addInstruction(std::move(finalMoveInst));
}

// 栈管理函数实现
void GlobalISel::generateFunctionPrologue(MachineBasicBlock* entryBlock) {
    // 为函数序言创建指令列表
    std::vector<std::unique_ptr<MachineInstruction>> prologueInsts;
    
    // 分配栈空间：addi sp, sp, -stackSize
    if (currentStackOffset > 0) {
        auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto spReg2 = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto stackImm = std::make_unique<ImmediateOperand>(-currentStackOffset);
        
        auto stackAllocInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
        stackAllocInst->addOperand(std::move(spReg));
        stackAllocInst->addOperand(std::move(spReg2));
        stackAllocInst->addOperand(std::move(stackImm));
        stackAllocInst->setComment("Function prologue: allocate stack");
        
        prologueInsts.push_back(std::move(stackAllocInst));
    }
    
            // 将序言指令插入到函数开头
        auto& instructions = const_cast<std::vector<std::unique_ptr<MachineInstruction>>&>(
            entryBlock->getInstructions());
        instructions.insert(instructions.begin(), 
                           std::make_move_iterator(prologueInsts.begin()),
                           std::make_move_iterator(prologueInsts.end()));
}

void GlobalISel::generateFunctionEpilogue(MachineBasicBlock* exitBlock) {
    // 函数尾声：恢复栈指针
    if (currentStackOffset > 0) {
        auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto spReg2 = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
        auto stackImm = std::make_unique<ImmediateOperand>(currentStackOffset);
        
        auto stackRestoreInst = std::make_unique<MachineInstruction>(RISCVOpcode::ADDI);
        stackRestoreInst->addOperand(std::move(spReg));
        stackRestoreInst->addOperand(std::move(spReg2));
        stackRestoreInst->addOperand(std::move(stackImm));
        stackRestoreInst->setComment("Function epilogue: restore stack");
        
        // 在return指令之前插入
        auto& instructions = const_cast<std::vector<std::unique_ptr<MachineInstruction>>&>(
            exitBlock->getInstructions());
        if (!instructions.empty() && 
            instructions.back()->getOpcode() == RISCVOpcode::RET) {
            instructions.insert(instructions.end() - 1, std::move(stackRestoreInst));
        } else {
            instructions.push_back(std::move(stackRestoreInst));
        }
    }
}

int GlobalISel::allocateStackSpace(int size) {
    currentStackOffset += size;
    // 确保8字节对齐
    if (currentStackOffset % 8 != 0) {
        currentStackOffset = ((currentStackOffset + 7) / 8) * 8;
    }
    return -currentStackOffset; // 返回负偏移量（栈向下增长）
}

std::unique_ptr<MemoryOperand> GlobalISel::createStackOperand(int offset) {
    auto spReg = std::make_unique<RegisterOperand>(RISCVReg::X2); // sp
    return std::make_unique<MemoryOperand>(std::move(spReg), offset);
} 