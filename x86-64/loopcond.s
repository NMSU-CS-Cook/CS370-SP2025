	.file	"loopcond.c"
	.text
	.comm	globalx,4,4
	.comm	globali,4,4
	.section	.rodata
.LC0:
	.string	"globali=%d\n"
.LC1:
	.string	"*"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)

# this is the BITWISE AND example
	movl	-8(%rbp), %eax
	andl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)

# this is the LOGICAL AND example
	movl	globalx(%rip), %eax
	cmpl	$100, %eax
	jle	.L2
	movl	globalx(%rip), %eax
	cmpl	$199, %eax
	jg	.L2
	movl	$9, globali(%rip)
	jmp	.L3
.L2:
	movl	$7, globali(%rip)
.L3:

# this is the printf() after the if-else block
	movl	globali(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

# this is the while loop, with the loop
# condition on the bottom
	jmp	.L4
.L5:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	globali(%rip), %eax
	subl	$1, %eax
	movl	%eax, globali(%rip)
.L4:
	movl	globali(%rip), %eax
	cmpl	$1, %eax
	jg	.L5

# code after the loop continues here
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	sum, .-sum
	.section	.rodata
.LC2:
	.string	"globalx = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$42, globalx(%rip)
	movl	globalx(%rip), %eax
	movl	$11, %edx
	movl	%eax, %esi
	movl	$7, %edi
	call	sum
	movl	%eax, globalx(%rip)
	movl	globalx(%rip), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
