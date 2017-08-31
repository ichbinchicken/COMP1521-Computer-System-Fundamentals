# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by Ziming Zheng z5052592, 31 August 2017

.data
main_addr_save: .space 4
msg1:           .asciiz "# Iterations: "

.text
.globl main

# int main (void)
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
   mul  $s2, $s2, $s2 # total size of board 
   add  $s2, $s1, $s2 # $s2: last addr of board
   li   $s3, 1        # int n = 1
iters_loop:
   bgt  $s3, $s0, iters_done    # for (int n=1;n<=maxiters;n++)
   la   $s4, board
   rows_loop:
        bge $s4, $s2, rows_done       # for (int i=0;i<N;i++)
        move  $s5, $s4
        addi $s4, $s4, 10 
        columns_loop:                   # for (int j=0;j<N;j++)
            bge $s5, $s4, columns_done
            addi $s5, $s5, 1
            j   columns_loop
        columns_done:
        j   rows_loop
   rows_done:
   addi $s3, $s3, 1
   j    iters_loop
iters_done:  
   lw   $ra, main_addr_save
   jr   $ra


# The other functions go here
