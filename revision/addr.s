.data
val:
    .word 4, 5, 7
.text

.globl main

main:

la      $s0, 0
lw      $a0, val+4($s0)

li      $v0, 1
syscall
jr      $ra
