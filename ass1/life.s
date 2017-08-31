# board.s ... Game of Life on a 10x10 grid

   .data

N: .word 10  # gives board dimensions

board:
   .byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0

newBoard: .space 100
# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by Ziming Zheng z5052592, 31 August 2017

.data
main_addr_save: .space 4
maxiters:       .space 4
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
   sw   $v0, maxiters # store value into 'maxiters'
   
   lw   $t0, maxiters
   li   $t1, 1  # int n = 1
   li   $t2, 0  # int i = 0
   li   $t3, 0  # int j = 0
end_main:
   lw   $ra, main_addr_save
   jr   $ra


# The other functions go here
