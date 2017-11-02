.data
msg: .asciiz "helloqa"
num: .word 16

.text
.globl main

main:
    la      $t0, msg
    li      $t1, 0
loop:
    lb      $s0, ($t0)
    beq     $s0, $t1, end_loop
    
    move    $a0, $s0
    li      $v0, 11
    syscall
    
    addi    $t0, $t0, 1
    j       loop
end_loop:
    
    move    $a0, $s0
    li      $v0, 1
    syscall
    jr      $ra
