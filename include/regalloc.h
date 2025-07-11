#pragma once

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>

namespace regalloc {

// ===================================================================
// 核心数据结构
// ===================================================================

enum class RegType {
    INTEGER,
    FLOAT
};

// 虚拟寄存器信息
struct VirtualRegister {
    int id;                    // 虚拟寄存器编号
    RegType type;             // 寄存器类型
    int priority;             // 优先级（使用频率等）
    
    VirtualRegister(int id, RegType type, int priority = 0)
        : id(id), type(type), priority(priority) {}
};

// 活跃区间
struct LiveInterval {
    int virtual_reg;          // 虚拟寄存器编号
    int start;               // 开始位置
    int end;                 // 结束位置
    RegType type;            // 寄存器类型
    int priority;            // 优先级
    
    // 默认构造函数
    LiveInterval() : virtual_reg(-1), start(0), end(0), type(RegType::INTEGER), priority(0) {}
    
    LiveInterval(int vr, int s, int e, RegType t, int p = 0)
        : virtual_reg(vr), start(s), end(e), type(t), priority(p) {}
    
    bool overlaps(const LiveInterval& other) const {
        return !(end < other.start || other.end < start);
    }
};

// 寄存器冲突关系
struct Interference {
    int reg1, reg2;
    
    Interference(int r1, int r2) : reg1(r1), reg2(r2) {}
};

// RISC-V物理寄存器定义
enum class RISCVReg {
    // 整数寄存器 (x0-x31)
    ZERO = 0,   // x0: 硬编码为0
    RA = 1,     // x1: 返回地址
    SP = 2,     // x2: 栈指针
    GP = 3,     // x3: 全局指针
    TP = 4,     // x4: 线程指针
    
    // 临时寄存器 (调用者保存)
    T0 = 5, T1 = 6, T2 = 7,
    T3 = 28, T4 = 29, T5 = 30, T6 = 31,
    
    // 保存寄存器 (被调用者保存)
    S0 = 8, S1 = 9,  // S0也是帧指针
    S2 = 18, S3 = 19, S4 = 20, S5 = 21,
    S6 = 22, S7 = 23, S8 = 24, S9 = 25,
    S10 = 26, S11 = 27,
    
    // 参数/返回值寄存器
    A0 = 10, A1 = 11, A2 = 12, A3 = 13,
    A4 = 14, A5 = 15, A6 = 16, A7 = 17,
    
    // 浮点寄存器 (f0-f31, 从32开始编号避免冲突)
    FT0 = 32, FT1 = 33, FT2 = 34, FT3 = 35,
    FT4 = 36, FT5 = 37, FT6 = 38, FT7 = 39,
    FS0 = 40, FS1 = 41,
    FA0 = 42, FA1 = 43, FA2 = 44, FA3 = 45,
    FA4 = 46, FA5 = 47, FA6 = 48, FA7 = 49,
    FS2 = 50, FS3 = 51, FS4 = 52, FS5 = 53,
    FS6 = 54, FS7 = 55, FS8 = 56, FS9 = 57,
    FS10 = 58, FS11 = 59,
    FT8 = 60, FT9 = 61, FT10 = 62, FT11 = 63,
    
    // 特殊标记
    SPILLED = 100,  // 溢出到内存
    INVALID = 101   // 无效寄存器
};

// 分配结果
struct AllocationResult {
    std::map<int, RISCVReg> allocation;     // 虚拟寄存器 -> 物理寄存器
    std::set<int> spilled_regs;             // 溢出的虚拟寄存器
    std::map<int, int> spill_slots;         // 溢出寄存器 -> 栈槽位
    int total_spill_slots;                  // 总溢出槽位数
    
    AllocationResult() : total_spill_slots(0) {}
};

// ===================================================================
// 寄存器分配器接口
// ===================================================================

class RegisterAllocator {
public:
    virtual ~RegisterAllocator() = default;
    
    // 设置输入数据
    virtual void setLiveIntervals(const std::vector<LiveInterval>& intervals) = 0;
    virtual void setInterferences(const std::vector<Interference>& conflicts) = 0;
    virtual void setAvailableRegisters(const std::vector<RISCVReg>& int_regs,
                                     const std::vector<RISCVReg>& float_regs) = 0;
    
    // 执行分配
    virtual AllocationResult allocate() = 0;
    
    // 获取统计信息
    virtual int getSpillCount() const = 0;
    virtual void printStatistics() const = 0;
};

// ===================================================================
// 线性扫描分配器
// ===================================================================

class LinearScanAllocator : public RegisterAllocator {
private:
    // 输入数据
    std::vector<LiveInterval> live_intervals_;
    std::vector<Interference> interferences_;
    std::vector<RISCVReg> available_int_regs_;
    std::vector<RISCVReg> available_float_regs_;
    
    // 分配状态
    std::map<int, RISCVReg> allocation_;
    std::set<int> spilled_regs_;
    std::map<int, int> spill_slots_;
    int next_spill_slot_;
    
    // 活跃区间管理
    struct ActiveInterval {
        LiveInterval interval;
        RISCVReg assigned_reg;
        
        ActiveInterval(const LiveInterval& iv, RISCVReg reg)
            : interval(iv), assigned_reg(reg) {}
    };
    
    std::vector<ActiveInterval> active_intervals_;
    std::set<RISCVReg> free_int_regs_;
    std::set<RISCVReg> free_float_regs_;

public:
    LinearScanAllocator();
    ~LinearScanAllocator() override = default;
    
    // RegisterAllocator接口实现
    void setLiveIntervals(const std::vector<LiveInterval>& intervals) override;
    void setInterferences(const std::vector<Interference>& conflicts) override;
    void setAvailableRegisters(const std::vector<RISCVReg>& int_regs,
                             const std::vector<RISCVReg>& float_regs) override;
    
    AllocationResult allocate() override;
    int getSpillCount() const override;
    void printStatistics() const override;

private:
    // 核心算法步骤
    void prepareIntervals();
    void scanIntervals();
    void expireOldIntervals(int current_start);
    bool tryAllocateRegister(const LiveInterval& interval);
    void spillInterval(const LiveInterval& interval);
    
    // 辅助函数
    std::set<RISCVReg>& getFreeRegs(RegType type);
    RISCVReg selectBestRegister(RegType type);
    ActiveInterval* findSpillCandidate(const LiveInterval& interval);
    void freeRegister(RISCVReg reg);
};

// ===================================================================
// 工厂函数和工具函数
// ===================================================================

// 创建线性扫描分配器
std::unique_ptr<RegisterAllocator> createLinearScanAllocator();

// RISC-V寄存器工具函数
namespace riscv {
    // 获取寄存器名称
    std::string getRegisterName(RISCVReg reg);
    
    // 判断寄存器属性
    bool isIntegerReg(RISCVReg reg);
    bool isFloatReg(RISCVReg reg);
    bool isCallerSaved(RISCVReg reg);
    bool isCalleeSaved(RISCVReg reg);
    bool isArgumentReg(RISCVReg reg);
    bool isReturnReg(RISCVReg reg);
    
    // 获取可用寄存器列表
    std::vector<RISCVReg> getAvailableIntRegs();
    std::vector<RISCVReg> getAvailableFloatRegs();
    
    // 按优先级排序寄存器（临时寄存器优先）
    std::vector<RISCVReg> getSortedIntRegs();
    std::vector<RISCVReg> getSortedFloatRegs();
}

} // namespace regalloc
