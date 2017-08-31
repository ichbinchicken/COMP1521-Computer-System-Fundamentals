.data
    main_addr_save: .word 4
    msg: .asciiz "n!= "
    .align 2
.text
.globl main
main:
    sw $ra, main_addr_save
    li $v0, 5 # scanf(, &n)
    syscall
    li $s0, 1 #clear $s0
    move $a0, $v0
    jal recurFac # $t0 = recurFac(n) 
    move $t0, $v0 # because we need to print "n!=" first
    la $a0, msg
    li $v0, 4
    syscall # printf("n!=")
    move $a0, $t0
    li $v0, 1
    syscall #prinf(,n)
    li $a0, '\n'
    li $v0, 11
    syscall #printf('\n')
    lw $ra, main_addr_save
    jr $ra

recurFac:

#prologue
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    sw $s0, -12($sp)
    sw $a0, -16($sp)
    la $fp, -4($sp)
    addi $sp, $sp, -16
    
    li $t1, 1
if_start:
    bne $a0, $t1, else
    li $v0, 1
    j if_end
else:
    move $s0, $a0
    addi $a0, $a0, -1
    jal recurFac
    mul $v0, $s0, $v0

if_end:
#epilogue
    lw $a0, -12($fp)
    lw $s0, -8($fp)
    lw $ra, -4($fp)
    la $sp, 4($fp)
    lw $fp, ($fp)
    jr $ra
