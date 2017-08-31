# COMP1521 Lab 04 ... Simple MIPS assembler
# #include <stdio.h>
# #include <stdlib.h>
#  
# int fac(int);
#  
# int main(void)
# {
#    int n;
#    printf("n: ");
#    scanf("%d", &n);
#    printf("n! = %d\n", fac(n));
#    return 0;
# }
#  
# int fac(int k)
# {
#    int i, f = 1;
#    for (i = 1; i <= k; i++) f = f * i;
#    return f;
# }

### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
   sw   $ra, main_ret_save
   la   $a0, msg1
   li   $v0, 4  #printf("n: ")
   syscall  
   li   $v0, 5  #scanf("%d", &n) 
   syscall
   move   $a0, $v0
   jal  fac     #fac(n)  
   la   $a0, msg2
   li   $v0, 4  #printf("n!= ")
   syscall
   move   $a0, $s0  # use the value of fac(n)
   li   $v0, 1
   syscall
   # maybe we don't need another '\n' because when we enter the new value, it had one.
   la   $a0, eol
   li   $v0, 4 #printf("\n")
   syscall
   lw   $ra, main_ret_save
   jr   $ra           # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4

   .text

fac:
   sw   $ra, fac_ret_save
   li   $t0, 1  #counter
   li   $t1, 1  #factor starter

loop:
   blt  $a0, $t0, exit
   mul  $t1, $t1, $t0
   add  $t0, $t0, 1 
   j    loop   

exit:
   move   $s0, $t1
   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)

