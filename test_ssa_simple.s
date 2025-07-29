  .file "test_ssa_simple.s"
  .option nopic
  .attribute stack_align, 16
  .data
  .globl a
  .type a, @object
a:
  .word 3
  .globl b
  .type b, @object
b:
  .word 5
  .text
  .globl main
  .type main, @function
main:
.L1:
  addi  sp,sp,-32
  sd  s0,24(sp)
  sd  ra,16(sp)
  addi  s0,sp,32
  li  %r2,5
  li  %r7,5
  sw  %r7,-20(s0)
  lw  %r3,-20(s0)
  la  %r8,b
  lw  %r4,0(%r8)
  la  %r9,b
  lw  %r6,0(%r9)
  add  %r5,%r3,%r4
  mv  a0,a0
  ld  s0,24(sp)
  ld  ra,16(sp)
  addi  sp,sp,32
  jr  ra
  .size main, .-main

