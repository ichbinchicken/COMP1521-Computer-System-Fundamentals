.data
    array: .word 5, 4, 7, 6, 8, 9, 1, 2, 3, 0 # As this array is global, can I use it straightaway instead of loading into $a0?
    lineFeed: .asciiz "\n"
    .align 2
    main_addr_save: .space 4
.text
#.globl main
main:
    sw $ra, main_addr_save
    li $s0, 0  
    li $a0, 0
    li $a1, 36 #9*4
    jal sumOf
    move $a0, $v0
    li $v0, 1
    syscall
    la $a0, lineFeed
    li $v0, 4
    syscall
    lw $ra, main_addr_save
    jr $ra

# int sumOf()
sumOf:

#prologue
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    sw $s0, -12($sp)
    la $fp, -4($sp) 
    add $sp, $sp, -12

if:
    ble $a0, $a1,else
    li  $v0, 0
    j   endif
else:
    lw  $s0,array($a0)
    addi $a0, $a0, 4
    jal sumOf
    add $v0, $s0, $v0  
endif:

#epilogue
    lw $s0, -8($fp)
    lw $ra, -4($fp)
    la $sp, 4($fp)
    lw $fp, ($fp)  # lw $fp, -4($sp)
    jr $ra
    
