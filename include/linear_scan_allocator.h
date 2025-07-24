#ifndef LINEAR_SCAN_ALLOCATOR_H
#define LINEAR_SCAN_ALLOCATOR_H

#include "machine_ir.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>

// 活跃区间
struct LiveInterval {
    int virtualReg;     // LLVM虚拟寄存器号
    int startPos;       // 开始位置（指令索引）
    int endPos;         // 结束位置（指令索引）
    bool isFloat;       // 是否为浮点寄存器
    RISCVReg assignedReg; // 分配的物理寄存器
    int spillSlot;      // 溢出栈槽位（-1表示未溢出）
    
    LiveInterval() : virtualReg(-1), startPos(-1), endPos(-1), 
                    isFloat(false), assignedReg(RISCVReg::INVALID), spillSlot(-1) {}
    
    LiveInterval(int vReg, int start, int end, bool isF) 
        : virtualReg(vReg), startPos(start), endPos(end), isFloat(isF),
          assignedReg(RISCVReg::INVALID), spillSlot(-1) {}
    
    // 按开始位置排序
    bool operator<(const LiveInterval& other) const {
        return startPos < other.startPos;
    }
    
    // 检查是否与另一个区间冲突
    bool conflictsWith(const LiveInterval& other) const {
        return !(endPos < other.startPos || other.endPos < startPos);
    }
    
    // 检查在某个位置是否还活跃
    bool isActiveAt(int pos) const {
        return startPos <= pos && pos <= endPos;
    }
};

// 溢出管理器
class SpillManager {
private:
    int nextSpillSlot;
    std::unordered_map<int, int> virtualRegToSpillSlot;
    
public:
    SpillManager() : nextSpillSlot(0) {}
    
    int allocateSpillSlot(int virtualReg);
    int getSpillSlot(int virtualReg);
    bool isSpilled(int virtualReg);
    void reset() { 
        nextSpillSlot = 0; 
        virtualRegToSpillSlot.clear(); 
    }
};

// 线性扫描寄存器分配器
class LinearScanAllocator {
private:
    // 可用的物理寄存器池
    std::vector<RISCVReg> availableIntRegs;
    std::vector<RISCVReg> availableFloatRegs;
    
    // 当前活跃的区间列表（按结束位置排序）
    struct IntervalEndComparator {
        bool operator()(const LiveInterval* a, const LiveInterval* b) const {
            return a->endPos > b->endPos; // 最小堆：最早结束的在前
        }
    };
    
    std::priority_queue<LiveInterval*, std::vector<LiveInterval*>, IntervalEndComparator> activeIntervals;
    
    // 已处理的区间
    std::vector<LiveInterval> intervals;
    std::unordered_map<int, int> virtualToIntervalIndex;
    
    // 溢出管理
    SpillManager spillManager;
    
    // 寄存器映射
    std::unordered_map<int, RISCVReg> virtualToPhysical;
    std::unordered_map<int, int> virtualToSpillSlot;
    
    // 指令位置计数器
    int currentPosition;
    
private:
    void initializeRegisterPool();
    void expireOldIntervals(int position);
    bool tryAllocateRegister(LiveInterval& interval);
    void spillAtInterval(LiveInterval& interval);
    LiveInterval* selectSpillCandidate(const std::vector<LiveInterval*>& candidates);
    
public:
    LinearScanAllocator();
    
    // 活跃性分析
    void analyzeFunction(const MachineFunction& func);
    void computeLiveIntervals(const MachineFunction& func);
    
    // 寄存器分配
    void allocateRegisters();
    
    // 查询接口
    RISCVReg getPhysicalReg(int virtualReg);
    int getSpillSlot(int virtualReg);
    bool isSpilled(int virtualReg);
    
    // 重置状态
    void reset();
    
    // 调试接口
    void printIntervals() const;
    void printAllocation() const;
    
    // 获取活跃区间（用于测试）
    const std::vector<LiveInterval>& getLiveIntervals() const { return intervals; }
};

// 寄存器分配器接口（替换原有的简单分配器）
class OptimizedRegisterAllocator {
private:
    LinearScanAllocator linearScan;
    bool analysisComplete;
    
    // 临时分配（分析阶段使用）
    int nextTempIntReg;
    int nextTempFloatReg;
    std::unordered_map<int, RISCVReg> tempMapping;
    
public:
    OptimizedRegisterAllocator() : analysisComplete(false), nextTempIntReg(0), nextTempFloatReg(0) {}
    
    // 分析阶段：临时分配寄存器用于指令生成
    RISCVReg allocateIntReg(int llvmReg = -1);
    RISCVReg allocateFloatReg(int llvmReg = -1);
    
    // 优化阶段：执行线性扫描分配
    void performOptimization(const MachineFunction& func);
    
    // 查询优化后的分配结果
    RISCVReg getMachineReg(int llvmReg);
    int getSpillSlot(int llvmReg);
    bool isSpilled(int llvmReg);
    
    // 兼容性接口
    void bindRegister(int llvmReg, RISCVReg machineReg);
    RISCVReg getArgReg(int argIndex, bool isFloat);
    RISCVReg getReturnReg(bool isFloat);
    
    // 重置
    void reset();
    
    // 调试
    void printOptimizationResults() const;
};

#endif // LINEAR_SCAN_ALLOCATOR_H 