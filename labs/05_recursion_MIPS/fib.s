# MIPS assembler to compute Fibonacci numbers

   .data
msg1:
   .asciiz "n = "
msg2:
   .asciiz "fib(n) = "
msg3:
   .asciiz "n must be > 0"

   .text
# int main(void)
# {
#    int n;
#    printf("n = ");
#    scanf("%d", &n);
#    if (n >= 1)
#       printf("fib(n) = %d\n", fib(n));
#    else {
#       printf("n must be > 0\n");
#       exit(1);
#    }
#    return 0;
# }

   .globl main
main:
   # prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   # function body
   la   $a0, msg1       # printf("n = ");
   li   $v0, 4
   syscall

   li   $v0, 5          # scanf("%d", &n);
   syscall
   move $a0, $v0

   # ... add code to check (n >= 1)
   # ... print an error message, if needed
   # ... and return a suitable value from main()
   li $t0, 1 
if_start:
   blt  $a0, $t0, else  # if n($a0) < 1, jump else
   li   $s0, 0          # clear s0 first
   li   $s1, 0          # clear s1 first
   jal  fib             # $s0 = fib(n);
   nop
   move $s2, $v0

   la   $a0, msg2       # printf((fib(n) = ");
   li   $v0, 4
   syscall

   move $a0, $s2        # printf("%d", $s2);
   li   $v0, 1
   syscall

   li   $a0, '\n'       # printf("\n");
   li   $v0, 11
   syscall
   j if_exit
else:
   la   $a0, msg3
   li   $v0, 4
   syscall
   li   $a0, '\n'
   li   $v0, 11
   syscall
if_exit:
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra


# int fib(int n)
# {
#    if (n < 1)
#       return 0;
#    else if (n == 1)
#       return 1;
#    else
#       return fib(n-1) + fib(n-2);
# }

fib:
   # prologue
   sw   $fp, -4($sp)
   sw   $ra, -8($sp)
   sw   $s0, -12($sp)
   sw   $s1, -16($sp)
   sw   $a0, -20($sp)
   la   $fp, -4($sp)
   addi $sp, $sp, -20
   # function body
   li   $t1, 1
if_start2:
   bge  $a0, $t1, elseif2
   li   $v0, 0
   j    if_exit2
elseif2:
   bne  $a0, $t1, else2
   li   $v0, 1
   j    if_exit2
else2:
  move  $s0, $a0
  addi  $a0, $a0, -1
  jal   fib
  move  $a0, $s0
  move  $s1, $v0
  addi  $a0, $a0, -2
  jal   fib 
  add   $v0, $v0, $s1
if_exit2: 
   # epilogue
   lw   $a0, -16($fp)
   lw   $s1, -12($fp)
   lw   $s0, -8($fp)
   lw   $ra, -4($fp)
   la   $sp, 4($fp)
   lw   $fp, ($fp) 
   jr   $ra
