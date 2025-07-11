#include "../include/regalloc.h"
#include <algorithm>
#include <unordered_map>

namespace regalloc {

// ===================================================================
// 线性扫描分配器实现
// ===================================================================

LinearScanAllocator::LinearScanAllocator() : next_spill_slot_(0) {
    // 初始化可用寄存器
    available_int_regs_ = riscv::getSortedIntRegs();
    available_float_regs_ = riscv::getSortedFloatRegs();
}

void LinearScanAllocator::setLiveIntervals(const std::vector<LiveInterval>& intervals) {
    live_intervals_ = intervals;
}

void LinearScanAllocator::setInterferences(const std::vector<Interference>& conflicts) {
    interferences_ = conflicts;
}

void LinearScanAllocator::setAvailableRegisters(const std::vector<RISCVReg>& int_regs,
                                               const std::vector<RISCVReg>& float_regs) {
    available_int_regs_ = int_regs;
    available_float_regs_ = float_regs;
}

AllocationResult LinearScanAllocator::allocate() {
    // 重置状态
    allocation_.clear();
    spilled_regs_.clear();
    spill_slots_.clear();
    active_intervals_.clear();
    next_spill_slot_ = 0;
    
    // 初始化空闲寄存器集合
    free_int_regs_.clear();
    free_float_regs_.clear();
    for (auto reg : available_int_regs_) {
        free_int_regs_.insert(reg);
    }
    for (auto reg : available_float_regs_) {
        free_float_regs_.insert(reg);
    }
    
    // 执行分配算法
    prepareIntervals();
    scanIntervals();
    
    // 构建结果
    AllocationResult result;
    result.allocation = allocation_;
    result.spilled_regs = spilled_regs_;
    result.spill_slots = spill_slots_;
    result.total_spill_slots = next_spill_slot_;
    
    return result;
}

void LinearScanAllocator::prepareIntervals() {
    // 按开始位置排序活跃区间
    std::sort(live_intervals_.begin(), live_intervals_.end(),
              [](const LiveInterval& a, const LiveInterval& b) {
                  if (a.start != b.start) {
                      return a.start < b.start;
                  }
                  // 开始位置相同时，优先级高的在前
                  return a.priority > b.priority;
              });
}

void LinearScanAllocator::scanIntervals() {
    for (const auto& interval : live_intervals_) {
        // 释放已经结束的区间
        expireOldIntervals(interval.start);
        
        // 尝试为当前区间分配寄存器
        if (!tryAllocateRegister(interval)) {
            spillInterval(interval);
        }
    }
}

void LinearScanAllocator::expireOldIntervals(int current_start) {
    auto it = active_intervals_.begin();
    while (it != active_intervals_.end()) {
        if (it->interval.end < current_start) {
            // 释放寄存器
            freeRegister(it->assigned_reg);
            it = active_intervals_.erase(it);
        } else {
            ++it;
        }
    }
}

bool LinearScanAllocator::tryAllocateRegister(const LiveInterval& interval) {
    auto& free_regs = getFreeRegs(interval.type);
    
    if (!free_regs.empty()) {
        // 有空闲寄存器，直接分配
        RISCVReg selected_reg = selectBestRegister(interval.type);
        free_regs.erase(selected_reg);
        
        allocation_[interval.virtual_reg] = selected_reg;
        active_intervals_.emplace_back(interval, selected_reg);
        
        return true;
    }
    
    return false;
}

void LinearScanAllocator::spillInterval(const LiveInterval& interval) {
    // 查找溢出候选
    ActiveInterval* spill_candidate = findSpillCandidate(interval);
    
    if (spill_candidate && spill_candidate->interval.end > interval.end) {
        // 溢出候选的生命周期更长，溢出候选而不是当前区间
        RISCVReg freed_reg = spill_candidate->assigned_reg;
        int spilled_reg = spill_candidate->interval.virtual_reg;
        
        // 移除候选从活跃列表
        active_intervals_.erase(
            std::remove_if(active_intervals_.begin(), active_intervals_.end(),
                          [spilled_reg](const ActiveInterval& ai) {
                              return ai.interval.virtual_reg == spilled_reg;
                          }),
            active_intervals_.end());
        
        // 溢出候选
        allocation_.erase(spilled_reg);
        spilled_regs_.insert(spilled_reg);
        spill_slots_[spilled_reg] = next_spill_slot_++;
        
        // 将释放的寄存器分配给当前区间
        allocation_[interval.virtual_reg] = freed_reg;
        active_intervals_.emplace_back(interval, freed_reg);
    } else {
        // 溢出当前区间
        spilled_regs_.insert(interval.virtual_reg);
        spill_slots_[interval.virtual_reg] = next_spill_slot_++;
    }
}

std::set<RISCVReg>& LinearScanAllocator::getFreeRegs(RegType type) {
    return (type == RegType::INTEGER) ? free_int_regs_ : free_float_regs_;
}

RISCVReg LinearScanAllocator::selectBestRegister(RegType type) {
    auto& free_regs = getFreeRegs(type);
    
    // 优先选择临时寄存器（调用者保存）
    for (auto reg : free_regs) {
        if (!riscv::isCalleeSaved(reg)) {
            return reg;
        }
    }
    
    // 没有临时寄存器，选择保存寄存器
    return *free_regs.begin();
}

LinearScanAllocator::ActiveInterval* LinearScanAllocator::findSpillCandidate(
    const LiveInterval& interval) {
    
    ActiveInterval* candidate = nullptr;
    
    // 查找同类型的活跃区间中结束最晚的
    for (auto& active : active_intervals_) {
        if (active.interval.type == interval.type) {
            if (!candidate || active.interval.end > candidate->interval.end) {
                candidate = &active;
            }
        }
    }
    
    return candidate;
}

void LinearScanAllocator::freeRegister(RISCVReg reg) {
    if (riscv::isIntegerReg(reg)) {
        free_int_regs_.insert(reg);
    } else if (riscv::isFloatReg(reg)) {
        free_float_regs_.insert(reg);
    }
}

int LinearScanAllocator::getSpillCount() const {
    return spilled_regs_.size();
}

void LinearScanAllocator::printStatistics() const {
    // 可选的统计信息输出，用于调试
    // 在生产环境中可以移除或通过编译选项控制
}

// ===================================================================
// 工厂函数
// ===================================================================

std::unique_ptr<RegisterAllocator> createLinearScanAllocator() {
    return std::make_unique<LinearScanAllocator>();
}

// ===================================================================
// RISC-V工具函数实现
// ===================================================================

namespace riscv {

std::string getRegisterName(RISCVReg reg) {
    static const std::unordered_map<RISCVReg, std::string> reg_names = {
        // 整数寄存器
        {RISCVReg::ZERO, "zero"}, {RISCVReg::RA, "ra"}, {RISCVReg::SP, "sp"},
        {RISCVReg::GP, "gp"}, {RISCVReg::TP, "tp"},
        {RISCVReg::T0, "t0"}, {RISCVReg::T1, "t1"}, {RISCVReg::T2, "t2"},
        {RISCVReg::S0, "s0"}, {RISCVReg::S1, "s1"},
        {RISCVReg::A0, "a0"}, {RISCVReg::A1, "a1"}, {RISCVReg::A2, "a2"}, {RISCVReg::A3, "a3"},
        {RISCVReg::A4, "a4"}, {RISCVReg::A5, "a5"}, {RISCVReg::A6, "a6"}, {RISCVReg::A7, "a7"},
        {RISCVReg::S2, "s2"}, {RISCVReg::S3, "s3"}, {RISCVReg::S4, "s4"}, {RISCVReg::S5, "s5"},
        {RISCVReg::S6, "s6"}, {RISCVReg::S7, "s7"}, {RISCVReg::S8, "s8"}, {RISCVReg::S9, "s9"},
        {RISCVReg::S10, "s10"}, {RISCVReg::S11, "s11"},
        {RISCVReg::T3, "t3"}, {RISCVReg::T4, "t4"}, {RISCVReg::T5, "t5"}, {RISCVReg::T6, "t6"},

        // 浮点寄存器
        {RISCVReg::FT0, "ft0"}, {RISCVReg::FT1, "ft1"}, {RISCVReg::FT2, "ft2"}, {RISCVReg::FT3, "ft3"},
        {RISCVReg::FT4, "ft4"}, {RISCVReg::FT5, "ft5"}, {RISCVReg::FT6, "ft6"}, {RISCVReg::FT7, "ft7"},
        {RISCVReg::FS0, "fs0"}, {RISCVReg::FS1, "fs1"},
        {RISCVReg::FA0, "fa0"}, {RISCVReg::FA1, "fa1"}, {RISCVReg::FA2, "fa2"}, {RISCVReg::FA3, "fa3"},
        {RISCVReg::FA4, "fa4"}, {RISCVReg::FA5, "fa5"}, {RISCVReg::FA6, "fa6"}, {RISCVReg::FA7, "fa7"},
        {RISCVReg::FS2, "fs2"}, {RISCVReg::FS3, "fs3"}, {RISCVReg::FS4, "fs4"}, {RISCVReg::FS5, "fs5"},
        {RISCVReg::FS6, "fs6"}, {RISCVReg::FS7, "fs7"}, {RISCVReg::FS8, "fs8"}, {RISCVReg::FS9, "fs9"},
        {RISCVReg::FS10, "fs10"}, {RISCVReg::FS11, "fs11"},
        {RISCVReg::FT8, "ft8"}, {RISCVReg::FT9, "ft9"}, {RISCVReg::FT10, "ft10"}, {RISCVReg::FT11, "ft11"},

        // 特殊标记
        {RISCVReg::SPILLED, "SPILLED"}, {RISCVReg::INVALID, "INVALID"}
    };

    auto it = reg_names.find(reg);
    return (it != reg_names.end()) ? it->second : "unknown";
}

bool isIntegerReg(RISCVReg reg) {
    return static_cast<int>(reg) >= 0 && static_cast<int>(reg) <= 31;
}

bool isFloatReg(RISCVReg reg) {
    return static_cast<int>(reg) >= 32 && static_cast<int>(reg) <= 63;
}

bool isCallerSaved(RISCVReg reg) {
    // 临时寄存器和参数寄存器是调用者保存
    switch (reg) {
        // 临时寄存器
        case RISCVReg::T0: case RISCVReg::T1: case RISCVReg::T2:
        case RISCVReg::T3: case RISCVReg::T4: case RISCVReg::T5: case RISCVReg::T6:
        // 参数寄存器
        case RISCVReg::A0: case RISCVReg::A1: case RISCVReg::A2: case RISCVReg::A3:
        case RISCVReg::A4: case RISCVReg::A5: case RISCVReg::A6: case RISCVReg::A7:
        // 浮点临时寄存器
        case RISCVReg::FT0: case RISCVReg::FT1: case RISCVReg::FT2: case RISCVReg::FT3:
        case RISCVReg::FT4: case RISCVReg::FT5: case RISCVReg::FT6: case RISCVReg::FT7:
        case RISCVReg::FT8: case RISCVReg::FT9: case RISCVReg::FT10: case RISCVReg::FT11:
        // 浮点参数寄存器
        case RISCVReg::FA0: case RISCVReg::FA1: case RISCVReg::FA2: case RISCVReg::FA3:
        case RISCVReg::FA4: case RISCVReg::FA5: case RISCVReg::FA6: case RISCVReg::FA7:
            return true;
        default:
            return false;
    }
}

bool isCalleeSaved(RISCVReg reg) {
    // 保存寄存器是被调用者保存
    switch (reg) {
        case RISCVReg::S0: case RISCVReg::S1: case RISCVReg::S2: case RISCVReg::S3:
        case RISCVReg::S4: case RISCVReg::S5: case RISCVReg::S6: case RISCVReg::S7:
        case RISCVReg::S8: case RISCVReg::S9: case RISCVReg::S10: case RISCVReg::S11:
        case RISCVReg::FS0: case RISCVReg::FS1: case RISCVReg::FS2: case RISCVReg::FS3:
        case RISCVReg::FS4: case RISCVReg::FS5: case RISCVReg::FS6: case RISCVReg::FS7:
        case RISCVReg::FS8: case RISCVReg::FS9: case RISCVReg::FS10: case RISCVReg::FS11:
            return true;
        default:
            return false;
    }
}

bool isArgumentReg(RISCVReg reg) {
    switch (reg) {
        case RISCVReg::A0: case RISCVReg::A1: case RISCVReg::A2: case RISCVReg::A3:
        case RISCVReg::A4: case RISCVReg::A5: case RISCVReg::A6: case RISCVReg::A7:
        case RISCVReg::FA0: case RISCVReg::FA1: case RISCVReg::FA2: case RISCVReg::FA3:
        case RISCVReg::FA4: case RISCVReg::FA5: case RISCVReg::FA6: case RISCVReg::FA7:
            return true;
        default:
            return false;
    }
}

bool isReturnReg(RISCVReg reg) {
    return reg == RISCVReg::A0 || reg == RISCVReg::A1 ||
           reg == RISCVReg::FA0 || reg == RISCVReg::FA1;
}

std::vector<RISCVReg> getAvailableIntRegs() {
    return {
        // 临时寄存器优先（调用者保存，使用灵活）
        RISCVReg::T0, RISCVReg::T1, RISCVReg::T2,
        RISCVReg::T3, RISCVReg::T4, RISCVReg::T5, RISCVReg::T6,

        // 参数寄存器（可用于局部计算）
        RISCVReg::A0, RISCVReg::A1, RISCVReg::A2, RISCVReg::A3,
        RISCVReg::A4, RISCVReg::A5, RISCVReg::A6, RISCVReg::A7,

        // 保存寄存器（需要在函数调用前后保存/恢复）
        RISCVReg::S1, RISCVReg::S2, RISCVReg::S3, RISCVReg::S4,
        RISCVReg::S5, RISCVReg::S6, RISCVReg::S7, RISCVReg::S8,
        RISCVReg::S9, RISCVReg::S10, RISCVReg::S11
        // 注意：S0通常用作帧指针，暂不包含
    };
}

std::vector<RISCVReg> getAvailableFloatRegs() {
    return {
        // 临时寄存器优先
        RISCVReg::FT0, RISCVReg::FT1, RISCVReg::FT2, RISCVReg::FT3,
        RISCVReg::FT4, RISCVReg::FT5, RISCVReg::FT6, RISCVReg::FT7,
        RISCVReg::FT8, RISCVReg::FT9, RISCVReg::FT10, RISCVReg::FT11,

        // 参数寄存器
        RISCVReg::FA0, RISCVReg::FA1, RISCVReg::FA2, RISCVReg::FA3,
        RISCVReg::FA4, RISCVReg::FA5, RISCVReg::FA6, RISCVReg::FA7,

        // 保存寄存器
        RISCVReg::FS0, RISCVReg::FS1, RISCVReg::FS2, RISCVReg::FS3,
        RISCVReg::FS4, RISCVReg::FS5, RISCVReg::FS6, RISCVReg::FS7,
        RISCVReg::FS8, RISCVReg::FS9, RISCVReg::FS10, RISCVReg::FS11
    };
}

std::vector<RISCVReg> getSortedIntRegs() {
    // 按优先级排序：临时寄存器 > 参数寄存器 > 保存寄存器
    return getAvailableIntRegs();
}

std::vector<RISCVReg> getSortedFloatRegs() {
    // 按优先级排序：临时寄存器 > 参数寄存器 > 保存寄存器
    return getAvailableFloatRegs();
}

} // namespace riscv

} // namespace regalloc
