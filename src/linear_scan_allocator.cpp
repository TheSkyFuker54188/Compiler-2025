#include "linear_scan_allocator.h"
#include <iostream>
#include <algorithm>
#include <cassert>

// SpillManager实现
int SpillManager::allocateSpillSlot(int virtualReg) {
    auto it = virtualRegToSpillSlot.find(virtualReg);
    if (it != virtualRegToSpillSlot.end()) {
        return it->second;
    }
    
    int slot = nextSpillSlot++;
    virtualRegToSpillSlot[virtualReg] = slot;
    return slot;
}

int SpillManager::getSpillSlot(int virtualReg) {
    auto it = virtualRegToSpillSlot.find(virtualReg);
    return (it != virtualRegToSpillSlot.end()) ? it->second : -1;
}

bool SpillManager::isSpilled(int virtualReg) {
    return virtualRegToSpillSlot.find(virtualReg) != virtualRegToSpillSlot.end();
}

// LinearScanAllocator实现
LinearScanAllocator::LinearScanAllocator() : currentPosition(0) {
    initializeRegisterPool();
}

void LinearScanAllocator::initializeRegisterPool() {
    // 可分配的整数寄存器（按优先级排序）
    // 优先使用临时寄存器，然后是保存寄存器
    availableIntRegs = {
        // 临时寄存器 t0-t6 (调用者保存，使用成本低)
        RISCVReg::X5, RISCVReg::X6, RISCVReg::X7,        // t0-t2
        RISCVReg::X28, RISCVReg::X29, RISCVReg::X30, RISCVReg::X31, // t3-t6
        
        // 保存寄存器 s0-s11 (被调用者保存，使用成本高)
        RISCVReg::X8, RISCVReg::X9,                      // s0-s1
        RISCVReg::X18, RISCVReg::X19, RISCVReg::X20, RISCVReg::X21, // s2-s5
        RISCVReg::X22, RISCVReg::X23, RISCVReg::X24, RISCVReg::X25, // s6-s9
        RISCVReg::X26, RISCVReg::X27                     // s10-s11
    };
    
    // 可分配的浮点寄存器
    availableFloatRegs = {
        // 临时浮点寄存器 ft0-ft11
        RISCVReg::F0, RISCVReg::F1, RISCVReg::F2, RISCVReg::F3,   // ft0-ft3
        RISCVReg::F4, RISCVReg::F5, RISCVReg::F6, RISCVReg::F7,   // ft4-ft7
        RISCVReg::F28, RISCVReg::F29, RISCVReg::F30, RISCVReg::F31, // ft8-ft11
        
        // 保存浮点寄存器 fs0-fs11
        RISCVReg::F8, RISCVReg::F9,                               // fs0-fs1
        RISCVReg::F18, RISCVReg::F19, RISCVReg::F20, RISCVReg::F21, // fs2-fs5
        RISCVReg::F22, RISCVReg::F23, RISCVReg::F24, RISCVReg::F25, // fs6-fs9
        RISCVReg::F26, RISCVReg::F27                              // fs10-fs11
    };
}

void LinearScanAllocator::computeLiveIntervals(const MachineFunction& func) {
    intervals.clear();
    virtualToIntervalIndex.clear();
    currentPosition = 0;
    
    std::unordered_map<int, int> lastUse; // 虚拟寄存器 -> 最后使用位置
    std::unordered_map<int, bool> isFloatReg; // 虚拟寄存器 -> 是否为浮点
    
    // 第一遍：收集所有虚拟寄存器的使用信息
    int position = 0;
    for (const auto& block : func.getBlocks()) {
        for (const auto& inst : block->getInstructions()) {
            // 分析指令的操作数
            for (const auto& operand : inst->getOperands()) {
                if (auto* regOp = dynamic_cast<const RegisterOperand*>(operand.get())) {
                    if (regOp->isVirtual()) {
                        int vReg = regOp->getVirtualReg();
                        lastUse[vReg] = position;
                        isFloatReg[vReg] = regOp->isFloatReg();
                        
                        // 如果这是第一次见到这个寄存器，创建活跃区间
                        if (virtualToIntervalIndex.find(vReg) == virtualToIntervalIndex.end()) {
                            intervals.emplace_back(vReg, position, position, regOp->isFloatReg());
                            virtualToIntervalIndex[vReg] = intervals.size() - 1;
                        }
                    }
                }
            }
            position++;
        }
    }
    
    // 第二遍：更新活跃区间的结束位置
    for (auto& pair : lastUse) {
        int vReg = pair.first;
        int endPos = pair.second;
        
        auto it = virtualToIntervalIndex.find(vReg);
        if (it != virtualToIntervalIndex.end()) {
            intervals[it->second].endPos = endPos;
        }
    }
    
    // 按开始位置排序
    std::sort(intervals.begin(), intervals.end());
    
    // 更新索引映射
    virtualToIntervalIndex.clear();
    for (size_t i = 0; i < intervals.size(); ++i) {
        virtualToIntervalIndex[intervals[i].virtualReg] = i;
    }
}

void LinearScanAllocator::allocateRegisters() {
    // 清空活跃区间列表
    while (!activeIntervals.empty()) {
        activeIntervals.pop();
    }
    
    virtualToPhysical.clear();
    virtualToSpillSlot.clear();
    spillManager.reset();
    
    // 为每个活跃区间分配寄存器
    for (auto& interval : intervals) {
        // 过期旧的区间
        expireOldIntervals(interval.startPos);
        
        // 尝试分配寄存器
        if (!tryAllocateRegister(interval)) {
            // 分配失败，需要溢出
            spillAtInterval(interval);
        }
        
        // 将当前区间加入活跃列表
        activeIntervals.push(&interval);
    }
}

void LinearScanAllocator::expireOldIntervals(int position) {
    // 移除所有在当前位置已经结束的区间
    while (!activeIntervals.empty() && activeIntervals.top()->endPos < position) {
        LiveInterval* expired = activeIntervals.top();
        activeIntervals.pop();
        
        // 释放物理寄存器
        if (expired->assignedReg != RISCVReg::INVALID) {
            if (expired->isFloat) {
                availableFloatRegs.push_back(expired->assignedReg);
            } else {
                availableIntRegs.push_back(expired->assignedReg);
            }
        }
    }
}

bool LinearScanAllocator::tryAllocateRegister(LiveInterval& interval) {
    auto& availableRegs = interval.isFloat ? availableFloatRegs : availableIntRegs;
    
    if (!availableRegs.empty()) {
        // 有可用寄存器，直接分配
        interval.assignedReg = availableRegs.back();
        availableRegs.pop_back();
        
        virtualToPhysical[interval.virtualReg] = interval.assignedReg;
        return true;
    }
    
    return false; // 没有可用寄存器
}

void LinearScanAllocator::spillAtInterval(LiveInterval& interval) {
    if (activeIntervals.empty()) {
        // 没有活跃区间，直接溢出当前区间
        interval.spillSlot = spillManager.allocateSpillSlot(interval.virtualReg);
        virtualToSpillSlot[interval.virtualReg] = interval.spillSlot;
        return;
    }
    
    // 找到结束最晚的区间作为溢出候选
    std::vector<LiveInterval*> candidates;
    auto tempQueue = activeIntervals;
    
    while (!tempQueue.empty()) {
        LiveInterval* active = tempQueue.top();
        tempQueue.pop();
        
        // 只考虑同类型的寄存器
        if (active->isFloat == interval.isFloat && active->assignedReg != RISCVReg::INVALID) {
            candidates.push_back(active);
        }
    }
    
    if (candidates.empty()) {
        // 没有合适的候选，溢出当前区间
        interval.spillSlot = spillManager.allocateSpillSlot(interval.virtualReg);
        virtualToSpillSlot[interval.virtualReg] = interval.spillSlot;
        return;
    }
    
    // 选择结束最晚的区间进行溢出
    LiveInterval* spillCandidate = selectSpillCandidate(candidates);
    
    if (spillCandidate->endPos > interval.endPos) {
        // 候选区间比当前区间活得更久，溢出候选区间
        interval.assignedReg = spillCandidate->assignedReg;
        virtualToPhysical[interval.virtualReg] = interval.assignedReg;
        
        // 溢出候选区间
        spillCandidate->assignedReg = RISCVReg::INVALID;
        spillCandidate->spillSlot = spillManager.allocateSpillSlot(spillCandidate->virtualReg);
        virtualToPhysical.erase(spillCandidate->virtualReg);
        virtualToSpillSlot[spillCandidate->virtualReg] = spillCandidate->spillSlot;
    } else {
        // 溢出当前区间
        interval.spillSlot = spillManager.allocateSpillSlot(interval.virtualReg);
        virtualToSpillSlot[interval.virtualReg] = interval.spillSlot;
    }
}

LiveInterval* LinearScanAllocator::selectSpillCandidate(const std::vector<LiveInterval*>& candidates) {
    // 简单策略：选择结束最晚的区间
    LiveInterval* latest = candidates[0];
    for (auto* candidate : candidates) {
        if (candidate->endPos > latest->endPos) {
            latest = candidate;
        }
    }
    return latest;
}

RISCVReg LinearScanAllocator::getPhysicalReg(int virtualReg) {
    auto it = virtualToPhysical.find(virtualReg);
    return (it != virtualToPhysical.end()) ? it->second : RISCVReg::INVALID;
}

int LinearScanAllocator::getSpillSlot(int virtualReg) {
    auto it = virtualToSpillSlot.find(virtualReg);
    return (it != virtualToSpillSlot.end()) ? it->second : -1;
}

bool LinearScanAllocator::isSpilled(int virtualReg) {
    return virtualToSpillSlot.find(virtualReg) != virtualToSpillSlot.end();
}

void LinearScanAllocator::reset() {
    intervals.clear();
    virtualToIntervalIndex.clear();
    virtualToPhysical.clear();
    virtualToSpillSlot.clear();
    
    while (!activeIntervals.empty()) {
        activeIntervals.pop();
    }
    
    spillManager.reset();
    initializeRegisterPool();
    currentPosition = 0;
}

void LinearScanAllocator::printIntervals() const {
    std::cout << "=== Live Intervals ===" << std::endl;
    for (const auto& interval : intervals) {
        std::cout << "v" << interval.virtualReg 
                  << ": [" << interval.startPos << ", " << interval.endPos << "]"
                  << " (" << (interval.isFloat ? "float" : "int") << ")";
        
        if (interval.assignedReg != RISCVReg::INVALID) {
            std::cout << " -> assigned";
        } else if (interval.spillSlot != -1) {
            std::cout << " -> spill slot " << interval.spillSlot;
        }
        std::cout << std::endl;
    }
}

void LinearScanAllocator::printAllocation() const {
    std::cout << "=== Register Allocation Results ===" << std::endl;
    
    std::cout << "Physical assignments:" << std::endl;
    for (const auto& pair : virtualToPhysical) {
        std::cout << "  v" << pair.first << " -> physical reg" << std::endl;
    }
    
    std::cout << "Spilled registers:" << std::endl;
    for (const auto& pair : virtualToSpillSlot) {
        std::cout << "  v" << pair.first << " -> spill slot " << pair.second << std::endl;
    }
}

// OptimizedRegisterAllocator实现
RISCVReg OptimizedRegisterAllocator::allocateIntReg(int llvmReg) {
    if (analysisComplete) {
        // 分析完成后，返回优化后的分配结果
        return getMachineReg(llvmReg);
    }
    
    // 分析阶段：临时分配虚拟寄存器标识符
    // 这里我们不分配真实的物理寄存器，而是创建虚拟寄存器标识
    if (llvmReg != -1) {
        // 为了兼容现有代码，我们需要返回一个寄存器标识
        // 实际的物理寄存器将在optimizeFunction中确定
        RISCVReg tempReg = static_cast<RISCVReg>(static_cast<int>(RISCVReg::X5) + (nextTempIntReg % 20));
        nextTempIntReg++;
        tempMapping[llvmReg] = tempReg;
        return tempReg;
    }
    
    // 匿名寄存器
    RISCVReg tempReg = static_cast<RISCVReg>(static_cast<int>(RISCVReg::X5) + (nextTempIntReg % 20));
    nextTempIntReg++;
    return tempReg;
}

RISCVReg OptimizedRegisterAllocator::allocateFloatReg(int llvmReg) {
    if (analysisComplete) {
        return getMachineReg(llvmReg);
    }
    
    if (llvmReg != -1) {
        RISCVReg tempReg = static_cast<RISCVReg>(static_cast<int>(RISCVReg::F0) + (nextTempFloatReg % 20));
        nextTempFloatReg++;
        tempMapping[llvmReg] = tempReg;
        return tempReg;
    }
    
    RISCVReg tempReg = static_cast<RISCVReg>(static_cast<int>(RISCVReg::F0) + (nextTempFloatReg % 20));
    nextTempFloatReg++;
    return tempReg;
}

void OptimizedRegisterAllocator::performOptimization(const MachineFunction& func) {
    // 执行活跃区间分析
    linearScan.computeLiveIntervals(func);
    
    // 执行寄存器分配
    linearScan.allocateRegisters();
    
    analysisComplete = true;
}

RISCVReg OptimizedRegisterAllocator::getMachineReg(int llvmReg) {
    if (!analysisComplete) {
        auto it = tempMapping.find(llvmReg);
        return (it != tempMapping.end()) ? it->second : RISCVReg::INVALID;
    }
    
    return linearScan.getPhysicalReg(llvmReg);
}

int OptimizedRegisterAllocator::getSpillSlot(int llvmReg) {
    return analysisComplete ? linearScan.getSpillSlot(llvmReg) : -1;
}

bool OptimizedRegisterAllocator::isSpilled(int llvmReg) {
    return analysisComplete ? linearScan.isSpilled(llvmReg) : false;
}

void OptimizedRegisterAllocator::bindRegister(int llvmReg, RISCVReg machineReg) {
    tempMapping[llvmReg] = machineReg;
}

RISCVReg OptimizedRegisterAllocator::getArgReg(int argIndex, bool isFloat) {
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
    return RISCVReg::INVALID;
}

RISCVReg OptimizedRegisterAllocator::getReturnReg(bool isFloat) {
    return isFloat ? RISCVReg::F10 : RISCVReg::X10; // fa0 或 a0
}

void OptimizedRegisterAllocator::reset() {
    linearScan.reset();
    analysisComplete = false;
    nextTempIntReg = 0;
    nextTempFloatReg = 0;
    tempMapping.clear();
}

void OptimizedRegisterAllocator::printOptimizationResults() const {
    if (analysisComplete) {
        linearScan.printIntervals();
        linearScan.printAllocation();
    } else {
        std::cout << "Optimization not yet performed." << std::endl;
    }
} 