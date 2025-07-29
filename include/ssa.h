#pragma once

#include "block.h"
#include "llvm_instruction.h"
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// SSA变换相关的数据结构

/**
 * SSA变换器 - 将非SSA的LLVM IR转换为SSA形式
 */
class SSATransformer {
public:
  /**
   * 将LLVM IR转换为SSA形式
   * @param ir 输入的LLVM IR
   * @return 转换后的SSA形式IR
   */
  LLVMIR transform(const LLVMIR &ir);

private:
  // 支配边界计算
  struct DominanceInfo {
    std::unordered_map<int, std::unordered_set<int>> dominators;   // 支配关系
    std::unordered_map<int, std::unordered_set<int>> dom_frontier; // 支配边界
    std::unordered_map<int, int> idom;                             // 直接支配者
  };

  // 控制流图
  struct ControlFlowGraph {
    std::unordered_map<int, std::vector<int>> predecessors; // 前驱
    std::unordered_map<int, std::vector<int>> successors;   // 后继
  };

  // 变量重命名信息
  struct RenameInfo {
    std::unordered_map<std::string, std::vector<int>> var_stack; // 变量版本栈
    std::unordered_map<std::string, int> var_counter; // 变量版本计数器
  };

  /**
   * 构建控制流图
   */
  ControlFlowGraph
  buildControlFlowGraph(const std::map<int, LLVMBlock> &blocks);

  /**
   * 基于控制流图计算支配信息
   */
  DominanceInfo
  computeDominanceInfoFromCFG(const std::map<int, LLVMBlock> &blocks,
                              const ControlFlowGraph &cfg);

  /**
   * 快速支配算法 - 适用于大型控制流图
   */
  DominanceInfo computeFastDominanceInfo(const std::map<int, LLVMBlock> &blocks,
                                         const ControlFlowGraph &cfg);

  /**
   * 计算控制流图的支配信息
   */
  DominanceInfo computeDominanceInfo(const std::map<int, LLVMBlock> &blocks);

  /**
   * 插入φ函数
   */
  void insertPhiFunctions(std::map<int, LLVMBlock> &blocks,
                          const DominanceInfo &dom_info);

  /**
   * 变量重命名
   */
  void renameVariables(std::map<int, LLVMBlock> &blocks,
                       const DominanceInfo &dom_info);

  /**
   * 收集函数中定义的所有变量
   */
  std::unordered_set<std::string>
  collectDefinedVariables(const std::map<int, LLVMBlock> &blocks);

  /**
   * 计算直接支配者
   */
  void computeImmediateDominators(DominanceInfo &info,
                                  const std::map<int, LLVMBlock> &blocks);

  /**
   * 计算支配边界
   */
  void computeDominanceFrontier(DominanceInfo &info,
                                const std::map<int, LLVMBlock> &blocks,
                                const ControlFlowGraph &cfg);

  /**
   * 找到两个块的公共支配者（快速算法辅助函数）
   */
  int findCommonDominator(int b1, int b2,
                          const std::unordered_map<int, int> &idom);

  /**
   * 简化的支配边界计算（快速算法辅助函数）
   */
  void
  computeSimplifiedDominanceFrontier(DominanceInfo &info,
                                     const std::map<int, LLVMBlock> &blocks,
                                     const ControlFlowGraph &cfg);

  /**
   * 获取基本块的前驱
   */
  std::vector<int> getPredecessors(int block_id,
                                   const std::map<int, LLVMBlock> &blocks);

  /**
   * 获取基本块的后继
   */
  std::vector<int> getSuccessors(int block_id,
                                 const std::map<int, LLVMBlock> &blocks);

  /**
   * 递归重命名变量 - DFS遍历支配树
   */
  void renameVariablesRecursive(int block_id,
                                const std::map<int, LLVMBlock> &blocks,
                                const DominanceInfo &dom_info,
                                RenameInfo &rename_info);

  /**
   * 生成新的变量名（加版本号）
   */
  std::string getNewVariableName(const std::string &var_name,
                                 RenameInfo &rename_info);

  /**
   * 获取变量的当前版本
   */
  std::string getCurrentVariableVersion(const std::string &var_name,
                                        const RenameInfo &rename_info);

  /**
   * 更新φ函数的参数
   */
  void updatePhiArguments(std::map<int, LLVMBlock> &blocks,
                          const ControlFlowGraph &cfg,
                          const RenameInfo &rename_info);
};

/**
 * 常量值表示
 */
struct ConstantValue {
  enum Type { INT, FLOAT, UNDEF } type;
  union {
    int int_val;
    float float_val;
  };

  ConstantValue() : type(UNDEF) {}
  ConstantValue(int val) : type(INT), int_val(val) {}
  ConstantValue(float val) : type(FLOAT), float_val(val) {}

  bool isConstant() const { return type != UNDEF; }
  bool isInt() const { return type == INT; }
  bool isFloat() const { return type == FLOAT; }
};

/**
 * SSA优化器 - 在SSA形式上进行各种优化
 */
class SSAOptimizer {
public:
  /**
   * 对SSA形式的IR进行优化
   */
  LLVMIR optimize(const LLVMIR &ssa_ir);

private:
  // 常量传播相关
  std::unordered_map<int, ConstantValue> constants_map;
  std::unordered_set<Instruction> useful_instructions;

  /**
   * 死代码消除
   */
  void eliminateDeadCode(LLVMIR &ir);

  /**
   * 常量传播
   */
  void constantPropagation(LLVMIR &ir);

  /**
   * 常量折叠
   */
  void constantFolding(LLVMIR &ir);

  /**
   * 复制传播
   */
  void copyPropagation(LLVMIR &ir);

  /**
   * 公共子表达式消除
   */
  void commonSubexpressionElimination(LLVMIR &ir);

  /**
   * 代数化简
   */
  void algebraicSimplification(LLVMIR &ir);

  /**
   * φ函数简化
   */
  void simplifyPhiFunctions(LLVMIR &ir);

  /**
   * 无用代码消除
   */
  void eliminateUnreachableCode(LLVMIR &ir);

  // 辅助函数
  bool isCriticalInstruction(const Instruction &inst);
  size_t countInstructions(const LLVMIR &ir);
  std::vector<Operand> getInstructionOperands(const Instruction &inst);
  bool isRegisterOperand(const Operand operand);
  Instruction findDefiningInstruction(const Operand operand,
                                      const std::map<int, LLVMBlock> &blocks);
  bool canPropagateConstants(const Instruction &inst);
  void propagateConstantsInInstruction(Instruction &inst);
  void updateConstantMapping(const Instruction &inst);
  bool canFoldConstants(const Instruction &inst);
  void foldConstantsInInstruction(Instruction &inst);
  bool isCopyInstruction(const Instruction &inst);
  bool extractCopyRegisters(const Instruction &inst, int &dest_reg,
                            int &src_reg);
  bool replaceCopyUsages(Instruction &inst,
                         const std::unordered_map<int, int> &copies);
  std::string generateExpressionString(const Instruction &inst);
  void replaceWithExistingResult(Instruction &inst, int existing_reg);
  int getInstructionResultRegister(const Instruction &inst);

  // 新增的具体实现函数
  int getRegisterFromOperand(const Operand operand);
  ConstantValue getConstantFromOperand(const Operand operand);
  void replaceOperandWithConstant(Operand &operand,
                                  const ConstantValue &constant);
  ConstantValue evaluateArithmeticOp(LLVMIROpcode op, const ConstantValue &left,
                                     const ConstantValue &right);
  ConstantValue evaluateComparisonOp(LLVMIROpcode op, const ConstantValue &left,
                                     const ConstantValue &right);
  bool isArithmeticInstruction(const Instruction &inst);
  bool isComparisonInstruction(const Instruction &inst);
  void markInstructionAsUseful(const Instruction &inst);
  void markOperandDefAsUseful(const Operand operand,
                              const std::map<int, LLVMBlock> &blocks);

  // 新增的辅助函数声明
  void addUsersToWorkList(int reg_num, const std::map<int, LLVMBlock> &blocks,
                          std::queue<std::pair<int, size_t>> &work_list);
  bool isPhiCopyCandidate(const Instruction &inst);
  int getPhiSingleSource(const Instruction &inst);
  void removeTrivialCopies(std::map<int, LLVMBlock> &blocks,
                           const std::unordered_map<int, int> &copy_map);
  bool hasOtherUsers(int reg_num, const std::map<int, LLVMBlock> &blocks,
                     const Instruction &excluding_inst);
  void markControlDependencies(const Instruction &phi_inst,
                               const std::map<int, LLVMBlock> &blocks,
                               std::queue<Instruction> &work_list);
  ConstantValue computeArithmeticResult(const Instruction &inst);
  ConstantValue computeComparisonResult(const Instruction &inst);
  ConstantValue computePhiResult(const Instruction &inst);
  void replaceInstructionWithConstant(Instruction &inst,
                                      const ConstantValue &constant);
  void replaceOperandRegister(Operand &operand, int new_reg);

  // 新增的通用指令处理函数
  std::vector<Operand> getGenericInstructionOperands(const Instruction &inst);
  int getGenericInstructionResultRegister(const Instruction &inst);

  // 新增的增强优化函数
  bool simplifyArithmeticInstruction(Instruction &inst);
  bool simplifyBitwiseInstruction(Instruction &inst);
  bool isRedundantPhiFunction(const Instruction &inst);
  void replaceRegisterUsages(std::map<int, LLVMBlock> &blocks, int old_reg,
                             int new_reg);
  bool tryConstantPropagation(Instruction &inst);
  void replaceInstructionWithOperand(Instruction &inst, const Operand &operand);
  void convertMultiplyByTwoToAdd(Instruction &inst, const Operand &operand);
  bool isSameRegisterOperand(const Operand &op1, const Operand &op2);

  // 代数化简辅助函数
  bool isZero(const ConstantValue &const_val);
  bool isOne(const ConstantValue &const_val);
  bool isTwo(const ConstantValue &const_val);
  bool isAllOnes(const ConstantValue &const_val);

  // 不可达代码消除辅助函数
  int getUnconditionalBranchTarget(const Instruction &inst);
  std::pair<int, int> getConditionalBranchTargets(const Instruction &inst);

  // 公共子表达式消除辅助函数
  bool canPerformCSE(const Instruction &inst);
};

/**
 * SSA销毁器 - 将SSA形式转换回普通形式以便后端处理
 */
class SSADestroyer {
public:
  /**
   * 将SSA形式转换回非SSA形式
   * 主要是消除φ函数，插入必要的复制指令
   */
  LLVMIR destroySSA(const LLVMIR &ssa_ir);

private:
  // φ函数信息结构体
  struct PhiInfo {
    int block_id;
    Instruction instruction;
    std::string result_var;
    std::vector<std::pair<std::string, int>> phi_args; // (变量名, 来源块ID)
  };

  /**
   * 消除φ函数
   */
  void eliminatePhiFunctions(std::map<int, LLVMBlock> &blocks);

  /**
   * 在前驱块中插入复制指令
   */
  void insertCopiesInPredecessors(
      int phi_block, const std::string &phi_var,
      const std::vector<std::pair<std::string, int>> &phi_args,
      std::map<int, LLVMBlock> &blocks);

  /**
   * 解析φ函数指令
   */
  void parsePhiFunction(const Instruction &phi_inst, PhiInfo &phi_info);

  /**
   * 创建复制指令
   */
  Instruction createCopyInstruction(const std::string &dest_var,
                                    const std::string &source_var);

  /**
   * 在终止指令之前插入复制指令
   */
  void insertCopyBeforeTerminator(LLVMBlock block, Instruction copy_inst);

  /**
   * 检查指令是否为终止指令
   */
  bool isTerminatorInstruction(const Instruction &inst);

  /**
   * 获取基本块的前驱块
   */
  std::vector<int> getPredecessorBlocks(int block_id,
                                        const std::map<int, LLVMBlock> &blocks);

  /**
   * 获取跳转指令的目标块
   */
  int getJumpTarget(const Instruction &inst);

  /**
   * 验证SSA销毁的正确性
   */
  void validateSSADestruction(const LLVMIR &original_ssa,
                              const LLVMIR &destroyed_ir);
};
