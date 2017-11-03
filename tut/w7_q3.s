.data
nrows: .word 6
ncols: .word 12
flag:  .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
       .byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
       .byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'

.text
.globl main
main:
lw      $s0, nrows          # s0 = nrows
lw      $s1, ncols          # s1 = ncols
li      $t0, 0              # t0 = row index
li      $t1, 0              # t1 = col index
for:
    bge      $t0, $s0, end_for
    mul      $t2, $s1, $t0      
    la       $t3, flag($t2)    # start of this row addr
    addi     $t0, $t0, 1
    mul      $t4, $s1, $t0       
    la       $t5, flag($t4)    # next row addr
    inner_for:
        bge     $t3, $t5, end_inner_for
        lb      $a0, ($t3)
        li      $v0, 11
        syscall
        addi    $t3, $t3, 1
        j       inner_for
    end_inner_for:
    li       $a0, '\n'  # print "\n"
    li       $v0, 11
    syscall
    j        for
end_for:
   jr       $ra 
