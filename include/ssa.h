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

  // ====== 公开数据结构声明 ======
  struct DominanceInfo {
    std::unordered_map<int, std::unordered_set<int>> dominators;
    std::unordered_map<int, std::unordered_set<int>> dom_frontier;
    std::unordered_map<int, int> idom;
  };

  struct ControlFlowGraph {
    std::unordered_map<int, std::vector<int>> predecessors;
    std::unordered_map<int, std::vector<int>> successors;
  };

  struct RenameInfo {
    std::unordered_map<std::string, std::vector<int>> var_stack;
    std::unordered_map<std::string, int> var_counter;
  };

  // 如果需要，补充如下辅助函数声明（如你的实现文件用到了）：
  DominanceInfo computeFastDominanceInfo(const std::map<int, LLVMBlock> &blocks,
                                         const ControlFlowGraph &cfg);
  void updatePhiArguments(std::map<int, LLVMBlock> &blocks,
                          const ControlFlowGraph &cfg,
                          const RenameInfo &rename_info);
  int findCommonDominator(int a, int b,
                          const std::unordered_map<int, int> &idom);
  void
  computeSimplifiedDominanceFrontier(DominanceInfo &info,
                                     const std::map<int, LLVMBlock> &blocks,
                                     const ControlFlowGraph &cfg);

private:
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
  // ============================================================================
  // 公共数据结构定义
  // ============================================================================

  // 循环信息结构体
  struct LoopInfo {
    int header_block;             // 循环头块
    int latch_block;              // 循环尾块(回边源)
    std::vector<int> body_blocks; // 循环体块
    std::vector<int> exit_blocks; // 循环出口块
    int induction_var;            // 归纳变量寄存器
    ConstantValue initial_value;  // 初始值
    ConstantValue step_value;     // 步长
    ConstantValue limit_value;    // 循环界限
    int trip_count;               // 迭代次数(-1表示未知)
    bool is_simple_loop;          // 是否为简单循环

    // 添加缺失的成员变量
    int instruction_count;   // 循环体指令数量
    int header;              // 循环头块（别名）
    int latch;               // 循环尾块（别名）
    int preheader;           // 循环前置块
    std::vector<int> blocks; // 循环体块（别名）
  };

  // 函数信息结构体
  struct FunctionInfo {
    std::string name;                // 函数名
    std::vector<int> parameter_regs; // 参数寄存器
    int return_reg;                  // 返回值寄存器(-1表示void)
    std::map<int, LLVMBlock> blocks; // 函数体基本块
    int instruction_count;           // 指令数量
    int call_count;                  // 被调用次数
    bool is_recursive;               // 是否递归
    bool is_inline_candidate;        // 是否为内联候选
  };

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

  // 除法优化
  bool isPowerOfTwo(int n);
  int log2_upper(int x);
  std::tuple<long long, int, int> choose_multiplier(int d, int prec);
  void optimizeDivision(LLVMIR &ir);

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

  void replaceWithIdentity(Instruction &inst, const Operand &source);
  void replaceWithConstant(Instruction &inst, const ConstantValue &constant);
  bool operandEquals(const Operand &op1, const Operand &op2);

  bool isPureFunctionalInstruction(const Instruction &inst);
  void replaceInstructionWithCopy(Instruction &inst, int existing_reg);

  RegOperand *GetNewRegOperand(int reg_num);

  void replaceWithShift(Instruction &inst, const Operand &operand,
                        int shift_amount, LLVMIROpcode opcode);
  void replaceWithBitwise(Instruction &inst, const Operand &operand, int mask,
                          LLVMIROpcode opcode);

  bool isLoopInvariant(
      const Instruction &inst, const LoopInfo &loop,
      const std::map<int, LLVMBlock> &blocks,
      const std::unordered_set<Instruction> &invariant_instructions);
  bool isInstructionInLoop(const Instruction &inst, const LoopInfo &loop,
                           const std::map<int, LLVMBlock> &blocks);
  void moveInstructionsToPreheader(
      const std::unordered_set<Instruction> &instructions, int preheader_block,
      std::map<int, LLVMBlock> &blocks);

  bool constantEquals(const ConstantValue &a, const ConstantValue &b);

  std::string generateCanonicalExpression(const Instruction &inst);
  bool isCommutativeOperation(int opcode);
  std::string getOperandString(const Operand &operand);

  // ============================================================================
  // 高级优化算法声明
  // ============================================================================

  /**
   * 强度削减
   */
  void strengthReduction(LLVMIR &ir);

  /**
   * 循环不变量外提
   */
  void loopInvariantCodeMotion(LLVMIR &ir);

  /**
   * 条件常量传播
   */
  void conditionalConstantPropagation(LLVMIR &ir);

  /**
   * 全局值编号
   */
  void globalValueNumbering(LLVMIR &ir);

  /**
   * 循环展开
   */
  void loopUnrolling(LLVMIR &ir);

  /**
   * 函数内联
   */
  void functionInlining(LLVMIR &ir);

  void algebraicSimplification(LLVMIR &ir);
  void simplifyPhiFunctions(LLVMIR &ir);
  void eliminateUnreachableCode(LLVMIR &ir);

  int log2_floor(int x);

  // 循环分析和识别
  std::vector<LoopInfo> detectLoops(const std::map<int, LLVMBlock> &blocks);
  bool isBackEdge(int from_block, int to_block,
                  const std::map<int, LLVMBlock> &blocks);
  LoopInfo analyzeLoop(int header_block, int latch_block,
                       const std::map<int, LLVMBlock> &blocks);
  bool findInductionVariable(const LoopInfo &loop,
                             const std::map<int, LLVMBlock> &blocks,
                             LoopInfo &updated_loop);
  int computeTripCount(const LoopInfo &loop,
                       const std::map<int, LLVMBlock> &blocks);
  bool isSimpleLoop(const LoopInfo &loop,
                    const std::map<int, LLVMBlock> &blocks);

  // 循环展开实现
  bool canUnrollLoop(const LoopInfo &loop,
                     const std::map<int, LLVMBlock> &blocks);
  void performLoopUnrolling(LoopInfo &loop, std::map<int, LLVMBlock> &blocks,
                            int unroll_factor);
  void duplicateLoopBody(const LoopInfo &loop, std::map<int, LLVMBlock> &blocks,
                         int iteration);
  void updateInductionVariable(const LoopInfo &loop,
                               std::map<int, LLVMBlock> &blocks, int iteration);
  void adjustBranchTargets(const LoopInfo &loop,
                           std::map<int, LLVMBlock> &blocks, int iteration);

  // 函数分析和内联
  std::map<std::string, FunctionInfo> analyzeFunctions(const LLVMIR &ir);
  std::vector<Instruction>
  findFunctionCalls(const std::map<int, LLVMBlock> &blocks);
  bool canInlineFunction(const FunctionInfo &func,
                         const Instruction &call_inst);
  void performFunctionInlining(Instruction &call_inst, const FunctionInfo &func,
                               std::map<int, LLVMBlock> &blocks);
  void substituteParameters(const FunctionInfo &func,
                            const Instruction &call_inst,
                            std::map<int, LLVMBlock> &inlined_blocks);
  void renameInlinedRegisters(std::map<int, LLVMBlock> &inlined_blocks,
                              int base_reg);
  void insertInlinedBlocks(const Instruction &call_inst,
                           const std::map<int, LLVMBlock> &inlined_blocks,
                           std::map<int, LLVMBlock> &target_blocks);

  // 控制流分析辅助函数
  std::vector<int> getPredecessors(int block_id,
                                   const std::map<int, LLVMBlock> &blocks);
  std::vector<int> getSuccessors(int block_id,
                                 const std::map<int, LLVMBlock> &blocks);
  std::vector<int> getBranchTargets(const Instruction &inst);
  bool dominates(int dominator, int dominated,
                 const std::map<int, LLVMBlock> &blocks);
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