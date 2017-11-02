  .data
x: .space 4
   .text
   .globl main
main:
   li  $a0, 32768
   li  $v0, 1
   syscall
   sw  $a0, x
   lh  $a0, x
   li  $v0, 1
   syscall
   jr  $ra
