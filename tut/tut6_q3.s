.text

lw  $s0, x
lw  $s1, y

main:
    
first:
 # if fail j or
   beqz $s0, or
   li   $t0, 100
   div  $t0, $t0, $t0
   bgt  $t0, 5, dos1
or:
   bge  $s1, $s0, else # if y >= x j else

dos1:
   # do s1 stuff
   j end

else:
   # do s2 stuff
end:
   jr   $ra
