.data
matrix: .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15

.text
.globl main

main:

li      $t0, 0                     # row
li      $s0, 4                     # total row
li      $s3, 16                    # 16 bytes of a row
li      $s4, 0                     # sum

for:
    bge     $t0, $s0, end_for
    mul     $t3, $s3, $t0          # $t3 = offset
    la      $t4, matrix($t3)       # $t4 = start address of each row
    addi    $t0, $t0, 1
    mul     $t5, $s3, $t0
    la      $t6, matrix($t5)       # $t6 = end address of one row
    
    inner_for:                     # second loop
        bge     $t4, $t6, end_inner_for
        lw      $s5, ($t4)
        add     $s4, $s5, $s4
        addi    $t4, $t4, 4
        j       inner_for
    end_inner_for:                 #end_second_loop
        j       for 


end_for:
    jr      $ra
