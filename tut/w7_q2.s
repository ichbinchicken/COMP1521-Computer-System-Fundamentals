.data
nitems: .word 0
head:   .word 0
tail:   .word 0
items:  .space 32

.text
.globl main

main:
# prologue:
addi        $sp, $sp, -4
sw          $fp, ($sp)
la          $fp, ($sp)
addi        $sp, $sp, -4
sw          $ra, ($sp)
# func body:
li          $a0, 1
jal         enqueue
li          $a0, 2
jal         enqueue
li          $a0, 3
jal         enquene

# epilogue:
lw          $ra, ($sp)
addi        $sp, $sp, 4
lw          $fp, ($sp)
addi        $sp, $sp, 4
