# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by Ziming Zheng z5052592, 31 August 2017

.data
msg1:           .asciiz "# Iterations: "
msg2:           .asciiz "=== After iteration "
msg3:           .asciiz " ===\n"
.align 2
main_addr_save: .space 4
.text
.globl main

# int main (void)
# save registers'allocation in main function:
# $s0: maxiter
# $s1: first addr of board
# $s2: last addr of board
# $s3: n
# $s4: starting addr of each row(board)
# $s5: addr of board
# $s6: N for N*N
# $s7: nn
main:
   sw   $ra, main_addr_save
   la   $a0, msg1 # printf("# Iterations: ")
   li   $v0, 4
   syscall
   li   $v0, 5 # scanf("%d", &maxiters)
   syscall
   
   move $s0, $v0      # $s0: maxiter
   la   $s1, board    # $s1: the first addr of board
   lw   $s2, N
   move $s6, $s2      # $s6: the num of rows/columns
   mul  $s2, $s2, $s2  
   add  $s2, $s1, $s2 # $s2: last addr of board + 1
   li   $s3, 1        # int n = 1

iters_loop:                       # for (int n=1;n<=maxiters;n++)
   bgt  $s3, $s0, iters_done    
   la   $s4, board                # for (int i=0;i<N;i++)
   rows_loop:
        bge $s4, $s2, rows_done       
        move  $s5, $s4            # for (int j=0;j<N;j++)
        add $s4, $s4, $s6
        columns_loop:                   
            bge  $s5, $s4, columns_done
            move $a0, $s4
            sub  $a0, $a0, $s6
            sub  $a0, $a0, $s1
            div  $a0, $a0, $s6      # $a0 = i
            move $a1, $s5
            move $t6, $s4
            sub  $t6, $t6, $s6
            sub  $a1, $a1, $t6      # $a1 = j
            jal  neighbours         # int nn = neighbours(i,j)
            move $s7, $v0           # nn = $s7
            outter_if:
                lb    $t2, ($s5)    # $t2 = board[i][j]
                li    $t0, 1        # $t0 = 1
                bne   $t2, $t0, outter_elif
                inner_if:
                      li    $t3, 2   # $t3 = 2
                      bge   $s7, $t3, inner_elif
                      li    $t4, 0
                      sub   $t5, $s5, $s1          # offset of first addr of board
                      sb    $t4, newBoard($t5)     # newboard[i][j] = 0
                      j     inner_if_exit    
                inner_elif:
                      li    $t3, 2
                      bne   $s7, $t3, inner_elif2
                      j     inner_action     
                inner_elif2:
                      li    $t1, 3
                      bne   $s7, $t1, inner_else
                inner_action:
                      li    $t4, 1
                      sub   $t5, $s5, $s1
                      sb    $t4, newBoard($t5)
                      j     inner_if_exit
                inner_else:
                      li    $t4, 0
                      sub   $t5, $s5, $s1
                      sb    $t4, newBoard($t5)
                inner_if_exit:
                      j     outter_if_exit
            outter_elif:
                      li    $t3, 3
                      bne   $s7, $t3, outter_else
                      li    $t4, 1
                      sub   $t5, $s5, $s1          # offset of first addr of board
                      sb    $t4, newBoard($t5)     # newboard[i][j] = 0
                      j     outter_if_exit
            outter_else:
                      li    $t4, 0
                      sub   $t5, $s5, $s1          # offset of first addr of board
                      sb    $t4, newBoard($t5)     # newboard[i][j] = 0
            outter_if_exit:        
            addi $s5, $s5, 1
            j   columns_loop
        columns_done:
        j   rows_loop
   rows_done:
   la   $a0, msg2 # printf("=== After iteration ")
   li   $v0, 4
   syscall
   move $a0, $s3 # printf(%d)
   li   $v0, 1
   syscall
   la   $a0, msg3 # printf(" ===")
   li   $v0, 4
   syscall
   jal  copyBackAndShow
   addi $s3, $s3, 1
   j    iters_loop

iters_done:  
   lw   $ra, main_addr_save
   jr   $ra

# int neighbours(int i, int j)
# $a0 = i
# $a1 = j
# $s6 = N
# return $v0
neighbours:
# prologue:
   sw   $fp, -4($sp)
   sw   $ra, -8($sp)
   sw   $s0, -12($sp)  # $s0 = x
   sw   $s1, -16($sp)  # $s1 = y
   la   $fp, -4($sp)
   addi $sp, $sp, -16

#function body
   li   $v0, 0         # int nn = 0
   li   $s0, -1        # int x = -1
   li   $t7, 1         # 1 in for loop
   add  $t2, $s6, -1    # $t2 = N-1
loop_x:
   bgt  $s0, $t7, loop_x_exit
   li   $s1, -1        # int y = -1
   loop_y:
        bgt  $s1, $t7, loop_y_exit
        add $t3, $a1, $s1  # $t3 = j+y
        add $t0, $a0, $s0   # $t0 = i+x
        if1:
            bge $t0, $0, if1_1
            j   if1_action
        if1_1:
            ble $t0, $t2, if2
            j   if1_action
        if1_action:
            j   continue
        if2:
            bge $t3, $0, if2_1
            j   if2_action
        if2_1:
            ble $t3, $t2, if3
            j   if2_action
        if2_action:
            j   continue     
        if3:
            bnez $s0, if4
            bnez $s1, if4
            j   continue
        if4:
            mul  $t0, $t0, $s6
            add  $t3, $t3, $t0  # update $t3 to the total offset of board
            lb   $t4, board($t3)
            bne  $t4, $t7, continue
            addi $v0, $v0, 1       
    continue:
        addi $s1, $s1, 1
        j    loop_y
   loop_y_exit:
   addi $s0, $s0, 1
   j    loop_x

loop_x_exit:
#epilogue
  lw    $s1, -12($fp)
  lw    $s0, -8($fp)
  lw    $ra, -4($fp)
  la    $sp, 4($fp)
  lw    $fp, ($fp)
  jr    $ra           # return nn

#void copyBackAndShow()
copyBackAndShow:
#prologue:
    sw   $fp, -4($sp)
    sw   $ra, -8($sp)
    sw   $s0, -12($sp)  # $s0 = x
    sw   $s1, -16($sp)  # $s1 = y
    la   $fp, -4($sp)
    addi $sp, $sp, -16
#function body: 
    la   $s0, board     # starting addr of board
    la   $s1, newBoard  # starting addr of newBoard
    la   $t0, board($s6)
    addi $t0, $t0, -1  # $t0 is the last of each row
loop:
    bge  $s0, $s2, loop_exit
    lb   $t1, ($s1)
    sb   $t1, ($s0)  # board[i][j] = newboard[i][j]
    if:
         bnez $t1, else
         li   $a0, '.'
         li   $v0, 11
         syscall
         j    endif
    else:
         li   $a0, '#'
         li   $v0, 11
         syscall
    endif: 
    blt  $s0, $t0, inc
    li   $a0, '\n'
    li   $v0, 11
    syscall
    add  $t0, $t0, $s6
inc:
    addi $s0, $s0, 1
    addi $s1, $s1, 1
    j    loop
loop_exit:
#epilogue:
    lw    $s1, -12($fp)
    lw    $s0, -8($fp)
    lw    $ra, -4($fp)
    la    $sp, 4($fp)
    lw    $fp, ($fp)
    jr    $ra           






















   
