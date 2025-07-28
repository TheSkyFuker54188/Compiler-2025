  .file "test_ssa_if.s"
  .option nopic
  .attribute stack_align, 16
  .data
  .text
  .globl ifElseIf
  .type ifElseIf, @function
ifElseIf:
.L1:
  addi  sp,sp,-32
  sd  s0,24(sp)
  sd  ra,16(sp)
  addi  s0,sp,32
  li  %r2,5
  li  %r36,5
  sw  %r36,-24(s0)
  li  %r4,10
  li  %r37,10
  sw  %r37,-20(s0)
  lw  %r5,-24(s0)
  li  %r6,6
  lw  %r8,-20(s0)
  li  %r9,11
.L2:
  lw  %r12,-24(s0)
  mv  a0,a0
  ld  s0,24(sp)
  ld  ra,16(sp)
  addi  sp,sp,32
  jr  ra
.L3:
  lw  %r13,-20(s0)
  li  %r14,10
  lw  %r16,-24(s0)
  li  %r17,1
.L4:
  li  %r20,25
  li  %r38,25
  sw  %r38,-24(s0)
.L5:
  lw  %r21,-20(s0)
  li  %r22,10
  lw  %r24,-24(s0)
  li  %r25,5
  li  %r26,-5
.L6:
  lw  %r29,-24(s0)
  li  %r30,15
  addi  %r31,%r29,15
  sw  %r31,-24(s0)
.L7:
  lw  %r32,-24(s0)
  li  %r39,0
  sub  %r34,%r39,%r32
  sw  %r34,-24(s0)
.L8:
.L9:
.L10:
  lw  %r35,-24(s0)
  mv  a0,a0
  ld  s0,24(sp)
  ld  ra,16(sp)
  addi  sp,sp,32
  jr  ra
.L11:
  li  a0,0
  ld  s0,24(sp)
  ld  ra,16(sp)
  addi  sp,sp,32
  jr  ra
  .size ifElseIf, .-ifElseIf

  .globl main
  .type main, @function
main:
.L1:
  addi  sp,sp,-16
  sd  s0,8(sp)
  sd  ra,0(sp)
  addi  s0,sp,16
    call  ifElseIf
    call  putint
  li  %r3,0
  li  a0,0
  ld  s0,8(sp)
  ld  ra,0(sp)
  addi  sp,sp,16
  jr  ra
  .size main, .-main

