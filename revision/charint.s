.data
x: .byte 'a'
msg: .asciiz "same\n"
.text
.globl main
main:
    lb      $t0, x
    li      $t1, 97
if:
    bne     $t0, $t1, end_if
    la      $a0, msg
    li      $v0, 4
    syscall
end_if:
    jr      $ra    
