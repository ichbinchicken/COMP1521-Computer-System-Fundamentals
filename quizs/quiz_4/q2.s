.data
.text
main:
   li   $t1, 0
   li   $t2, 1
   li   $t3, 10
loop:
   bgt  $t2, $t3, end_loop
   mul  $t1, $t1, $t2
   addi $t2, $t2, 1
   j    loop
end_loop:
   move  $a0, $t1
   li   $v0, 1
   syscall
   jr $ra
