.data
person:
        .word 5000035
        .asciiz "John"
        .space  10
        .ascii "Shepherd"
        .space  6
        .space  2
        .word   99

.text
.globl main

main:
#prologue:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)

#function body:
la      $a0, person
jal     showPerson



#epilogue:
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra
showPerson:
#prologue:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
#func body:
move    $s0, $a0
#print student id
lw      $a0, ($s0)
li      $v0, 1
syscall
li      $a0, ','
li      $v0, 11
syscall
#print first name
la      $a0, 19($s0)
li      $v0, 4
syscall
li      $a0, ','
li      $v0, 11
syscall
#print last name
la      $a0, 4($s0)
li      $v0, 4
syscall
li      $a0, ','
li      $v0, 11
syscall
#print wam:
lw      $a0, 36($s0)
li      $v0, 1
syscall
li      $a0, ','
li      $v0, 11
syscall
#epilogue:
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra
