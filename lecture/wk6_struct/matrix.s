        .data
row0:   .space 16
row1:   .space 16
row2:   .space 16
row3:   .space 16
matrix: .word row0, row1, row2, row3

        .text
        .globl main
main:  
addi	$sp, $sp, -4			
sw      $fp, ($sp)
move 	$fp, $sp
addi    $sp, $sp, -4
sw	$ra, ($sp)

li      $s0, 0
li      $t0, 4                         # $t0: matrix boundary 
li      $t1, 4
loop1:
        bge     $s0, $t0, end_loop1
        move    $t2, $s0
        mul     $t2, $t2, 4
        lw      $s3, matrix($t2)    # $s3: rowN

        li      $s1, 0                         # $s1: row loop start
        loop2:
                bge     $s1, $t1, end_loop2
                move    $t3, $s1
                mul     $t3, $t3, 4
                li      $t4, 1
                move    $t5, $s3
                add     $t5, $t5, $t3
                sw      $t4, ($t5)
                lw      $a0, ($t5)
                li      $v0, 1
                syscall
                addi    $s1, $s1, 1
                j       loop2
        end_loop2:

        li      $a0, '\n'
        li      $v0, 11
        syscall
        addi    $s0, $s0, 1
        j       loop1
end_loop1:

lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr	$ra					# jump to $ra

