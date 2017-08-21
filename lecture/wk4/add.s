.data
x:
    .word 3
y:
    .word 4
endl:
    .asciiz "\n"

.text
.globl main
main:
    lw $t0, x
    lw $t1, y
    add $a0, $t0, $t1
    li $v0, 1
    syscall
    li $a0, 0x0a
    li $v0, 11
#    la $a0, endl
#    li $v0, 4
    syscall
    jr $ra
