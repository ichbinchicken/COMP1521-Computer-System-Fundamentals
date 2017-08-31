# This code is to check if qtspim is using little endian.
.data
    x: .word 0x10000011
    y: .asciiz "\n"
.text
main:
    la $t0, x
    lb $a0, ($t0)
    li $v0, 1
    syscall
    la $a0, y
    li $v0, 4
    syscall
    jr $ra
