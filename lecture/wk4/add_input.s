.data
x:
    .space 4
y:
    .space 4
str1:
    .asciiz "First num: "
str2:
    .asciiz "Second num: "
endl:
    .asciiz "\n"

.text
main:
    la $a0, str1
    li $v0, 4   # printf
    syscall
    li $v0, 5   # scanf
    sw $v0, x

    la $a0, str2
    li $v0, 4
    syscall
    li $v0, 5   # scanf
    sw $v0, y
    


