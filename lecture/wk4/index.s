.data
var:
    .word 3, 5
endl:
    .asciiz "\n"

.text
.globl main
main:
    la $s0, var
    lw $a0, 4($s0)   
#move $a0, $s0
    li $v0, 1   # print 5
    syscall
    la $a0, endl
    li $v0, 4
    syscall

    li $s1, 0x10010000   #*
#    la $s1, 0x10010000  #* this also works
    lw $a0, ($s1)        #$
#    lw $a0, var         #$ this also works
    li $v0, 1
    syscall     # print 3

    li $s2, 0x10010008   #@
    move $a0, $s2        #@
#    la $a0, endl        #@ the above 2 lines are the same as this line
    li $v0, 4
    syscall


    la $a0, var
    li $v0, 1
    syscall     # print address of 3
    la $a0, endl
    li $v0, 4
    syscall

    la $a0, 4($s0)
    li $v0, 1
    syscall     # print address of 5
    la $a0, endl
    li $v0, 4
    syscall
    jr $ra

  #4($s0)
