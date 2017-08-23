.data
x:
    .word 0x12345678

.text
.globl main
main:
    lh $t0, x
    jr $ra
