	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	leaq	L_.str(%rip), %rdi
	leaq	-48(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -8(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -48(%rbp)
	movl	$1, -44(%rbp)
	movl	$3, -40(%rbp)
	movq	%rax, %rcx
	addq	$4, %rcx
	movq	%rax, %rdx
	addq	$8, %rdx
	movq	%rax, %rsi
	movq	%rdx, -64(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdx
	movq	-64(%rbp), %rcx         ## 8-byte Reload
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	jne	LBB0_2
## BB#1:
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%p, %p, %p\n"


.subsections_via_symbols
