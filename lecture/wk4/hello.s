
.data
msg:
    .asciiz "Hello, MIPS!\n"
msg2:
    .asciiz "aaaaaaaaaaaaaaaaaaa\n"
msg3:
    .asciiz "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"


.text
.globl main
main:
    la $a0, msg
    la $a1, msg2
    la $a2, msg3
    li $v0, 4
    syscall
    jr $ra
