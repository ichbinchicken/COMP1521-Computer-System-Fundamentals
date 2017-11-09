# MIPS assembler to compute Fibonacci numbers

   .data
msg1:
   .asciiz "n = "
msg2:
   .asciiz "fib(n) = "
msg3:
   .asciiz "n must be > 0"
n:
   .space 4

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
# prologue:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
# func body:
la      $a0, msg1
li      $v0, 4
syscall                     # print("n = ")
li      $v0, 5
syscall
move    $s0, $v0            # $s0 = n (int n)
li      $t0, 1              # $t0 = 1
if_main:
    blt     $s0, $t0, else_main
    move    $a0, $s0
    jal     fib             # call fib function
    move    $s1, $v0
    la      $a0, msg2
    li      $v0, 4
    syscall
    move    $a0, $s1
    li      $v0, 1
    syscall
    li      $a0, '\n'
    li      $v0, 11
    syscall     
    j       end_if_main
else_main:
    la      $a0, msg3       # print("n > 0")
    li      $v0, 4
    syscall
    li      $a0, '\n'
    li      $v0, 11
    syscall
end_if_main:
# epilogue:
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra





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
# prologue:
addi    $sp, $sp, -4
sw      $fp, ($sp)
la      $fp, ($sp)
addi    $sp, $sp, -4
sw      $ra, ($sp)
addi    $sp, $sp, -4
sw      $s2, ($sp)
addi    $sp, $sp, -4
sw      $s3, ($sp)
# func body:
move    $s2, $a0        # s2 = (int) n
li      $t1, 1
if: 
    bge     $s2, $t1, else_if
    li      $v0, 0
    j       end_if
else_if:
    bne     $s2, $t1, else
    li      $v0, 1
    j       end_if
else:
    move    $a0, $s2
    addi    $a0, $a0, -1
    jal     fib
    move    $s3, $v0
    move    $a0, $s2
    addi    $a0, $a0, -2
    jal     fib
    add     $v0, $v0, $s3
     
end_if:
# epilogue:
lw      $s3, ($sp)
addi    $sp, $sp, 4
lw      $s2, ($sp)
addi    $sp, $sp, 4
lw      $ra, ($sp)
addi    $sp, $sp, 4
lw      $fp, ($sp)
addi    $sp, $sp, 4
jr      $ra
