	.file	"daxpy.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L27
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	%rsp, %rdi
	movq	%rax, %r12
	cltq
	leaq	15(,%rax,4), %rax
	movq	%rax, %rcx
	movq	%rax, %rdx
	andq	$-4096, %rcx
	andq	$-16, %rdx
	subq	%rcx, %rdi
	movq	%rdi, %rcx
	cmpq	%rcx, %rsp
	je	.L4
.L28:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L28
.L4:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L29
.L5:
	movq	%rax, %rdx
	movq	%rsp, %rcx
	andq	$-4096, %rax
	movq	%rsp, %r15
	subq	%rax, %rcx
	andq	$-16, %rdx
	movq	%rcx, %rax
.L6:
	cmpq	%rax, %rsp
	je	.L7
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L6
.L29:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L5
.L7:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L30
.L8:
	leaq	3(%rsp), %rbx
	movq	%rbx, %r13
	andq	$-4, %rbx
	shrq	$2, %r13
	testl	%r12d, %r12d
	jle	.L9
	leal	-1(%r12), %r14d
	movl	$1, %eax
	movq	%r14, %r12
	addq	$2, %r14
	.p2align 4,,10
	.p2align 3
.L10:
	movl	%eax, (%r15,%rax,4)
	movl	%eax, (%rbx,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L10
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L12:
	imull	$47, (%r15,%rax,4), %edx
	addl	%edx, (%rbx,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L12
.L13:
	xorl	%edi, %edi
	leaq	-80(%rbp), %rsi
	movslq	%r12d, %r12
	call	clock_gettime@PLT
	movq	-72(%rbp), %rax
	pxor	%xmm0, %xmm0
	subq	-88(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	-80(%rbp), %rax
	subq	-96(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC1(%rip), %xmm0
	movl	(%rbx,%r12,4), %ecx
	movl	0(,%r13,4), %edx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L31
	leaq	-40(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L9:
	.cfi_restore_state
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	subl	$1, %r12d
	call	clock_gettime@PLT
	jmp	.L13
.L30:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L8
.L27:
	movq	stderr(%rip), %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	orl	$-1, %edi
	call	exit@PLT
.L31:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
