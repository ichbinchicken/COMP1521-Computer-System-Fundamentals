.data
x: .space   8
y: .space   4

.text
.globl main

main:
li      $v0, 5
syscall

move    $s0, $v0
move    $s1, $s0

addi    $s0, $s0, 2000
addi    $s1, $s1, 3000   

mult    $s0, $s1
mfhi    $t0
mflo    $t1

sw      $t0, x
sw      $t1, x+4

jr      $ra
