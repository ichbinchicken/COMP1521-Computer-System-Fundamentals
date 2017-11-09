.data
node1: .word  1
       .word  node2
node2: .word  2
       .word  node3
node3: .word  3
       .word  0

msg: .asciiz "->"
.text
.globl main

main:
#prologue
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
#func body:
la      $t0, node1
move    $a0, $t0
jal     showNode

#epilogue:
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra
showNode:
#prologue
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
#func body:
move    $t1, $a0   #t1 = curr = &node1

for:
    beq     $t1, $0, end_for
    lw      $a0, ($t1)
    li      $v0, 1
    syscall
    la      $a0, msg
    li      $v0, 4
    syscall
    lw      $t1, 4($t1)
    j       for 
end_for:
#epilogue:
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra
