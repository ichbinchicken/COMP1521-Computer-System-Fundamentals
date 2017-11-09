# know if the first bit of half word is 1
# it will expand 1s at the front because
# the half word will be treated as signed number
.data
x: .word 0x00010101
y: .word 0x00008000
z: .word 0x0000002A
eol: .asciiz "\n"
.text
.globl main
main:

move $s3, $ra

la $t0, x
move $a0, $t0
jal print

lw  $t0, x
move $a0, $t0
jal print

lh $t0, x
move $a0, $t0
jal print

lh $t0, y
move $a0, $t0
jal print

lhu $t0, y
move $a0, $t0
jal print

lbu $t0, y
move $a0, $t0
jal print
move $ra, $s3
jr  $ra

print:
      move $s1, $a0
      move $s2, $ra
      li   $v0, 1
      syscall
      la   $a0, eol
      li   $v0, 4
      syscall
      move $a0, $s1
      move $ra, $s2
      jr   $ra


