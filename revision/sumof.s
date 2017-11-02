.data
array: .word 5, 4, 7, 6, 8, 9, 1, 2, 3, 0
msg: .asciiz "\n"
.text
.globl main

main:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)

li      $a0, 0
li      $a1, 9
jal     sumof

move    $a0, $v0
li      $v0, 1
syscall

la      $a0, msg
li      $v0, 4
syscall

lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr       $ra

sumof:
# prologue:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
addi    $sp, $sp, -4
sw      $s0, ($sp)

move    $t0, $a0  # lo
move    $t1, $a1  # hi

if:
    ble     $t0, $t1, else
    li      $v0, 0
    j       end_if
else:
    li      $t2, 4
    mult    $t2, $t0
    mflo    $t3
    lw      $s0, array($t3)
    move    $a0, $t0
    addi    $a0, $a0, 1
    move    $a1, $t1
    jal     sumof
    add     $v0, $v0, $s0
end_if:
# epilogue
lw      $s0, ($sp)
addi    $sp, $sp, 4
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4

jr      $ra












