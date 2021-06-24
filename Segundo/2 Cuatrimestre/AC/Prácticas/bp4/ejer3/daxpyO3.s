	.file	"daxpy.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Falta num\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
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
	jle	.L43
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	%rsp, %rdi
	movq	%rax, %r15
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
.L44:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L44
.L4:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L45
.L5:
	leaq	3(%rsp), %r14
	movq	%rax, %rdx
	movq	%rsp, %rdi
	andq	$-4096, %rax
	movq	%r14, %rcx
	subq	%rax, %rdi
	andq	$-4, %r14
	andq	$-16, %rdx
	shrq	$2, %rcx
	movq	%rdi, %rax
.L6:
	cmpq	%rax, %rsp
	je	.L7
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L6
.L45:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L5
.L7:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L46
.L8:
	leaq	3(%rsp), %rbx
	movq	%rbx, %r13
	andq	$-4, %rbx
	shrq	$2, %r13
	testl	%r15d, %r15d
	jle	.L9
	leal	-1(%r15), %r12d
	cmpl	$2, %r12d
	jbe	.L10
	movl	%r15d, %edx
	movdqa	.LC0(%rip), %xmm0
	movl	$4, %eax
	movdqa	.LC2(%rip), %xmm2
	shrl	$2, %edx
	salq	$4, %rdx
	addq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L11:
	movdqa	%xmm0, %xmm1
	paddd	%xmm2, %xmm0
	movups	%xmm1, (%r14,%rax)
	movups	%xmm1, (%rbx,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L11
	movl	%r15d, %eax
	andl	$-4, %eax
	leal	1(%rax), %edx
	cmpl	%eax, %r15d
	je	.L12
	movslq	%edx, %rcx
	addl	$2, %eax
	movl	%edx, (%r14,%rcx,4)
	movl	%edx, (%rbx,%rcx,4)
	cmpl	%eax, %r15d
	jl	.L12
.L20:
	movslq	%eax, %rdx
	movl	%eax, (%r14,%rdx,4)
	movl	%eax, (%rbx,%rdx,4)
	addl	$1, %eax
	cmpl	%eax, %r15d
	jl	.L14
	movslq	%eax, %rdx
	movl	%eax, (%r14,%rdx,4)
	movl	%eax, (%rbx,%rdx,4)
.L14:
	xorl	%edi, %edi
	leaq	-96(%rbp), %rsi
	call	clock_gettime@PLT
	cmpl	$2, %r12d
	jbe	.L26
.L22:
	movl	%r15d, %edx
	movl	$4, %eax
	shrl	$2, %edx
	salq	$4, %rdx
	addq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L16:
	movdqu	(%r14,%rax), %xmm1
	movdqu	(%rbx,%rax), %xmm3
	movdqa	%xmm1, %xmm0
	pslld	$1, %xmm0
	paddd	%xmm1, %xmm0
	pslld	$4, %xmm0
	psubd	%xmm1, %xmm0
	paddd	%xmm3, %xmm0
	movups	%xmm0, (%rbx,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L16
	movl	%r15d, %edx
	andl	$-4, %edx
	leal	1(%rdx), %eax
	cmpl	%r15d, %edx
	je	.L19
.L18:
	movslq	%eax, %rdx
	imull	$47, (%r14,%rdx,4), %ecx
	addl	%ecx, (%rbx,%rdx,4)
	leal	1(%rax), %edx
	cmpl	%r15d, %edx
	jg	.L19
	movslq	%edx, %rdx
	addl	$2, %eax
	imull	$47, (%r14,%rdx,4), %ecx
	addl	%ecx, (%rbx,%rdx,4)
	cmpl	%eax, %r15d
	jl	.L19
	cltq
	imull	$47, (%r14,%rax,4), %edx
	addl	%edx, (%rbx,%rax,4)
.L19:
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
	divsd	.LC3(%rip), %xmm0
	movl	(%rbx,%r12,4), %ecx
	movl	0(,%r13,4), %edx
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L47
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
.L12:
	.cfi_restore_state
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	jmp	.L22
.L9:
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	leal	-1(%r15), %r12d
	call	clock_gettime@PLT
	jmp	.L19
.L10:
	movl	$1, 4(,%rcx,4)
	movl	$2, %eax
	movl	$1, 4(,%r13,4)
	cmpl	$1, %r15d
	jne	.L20
	leaq	-96(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movl	$1, %eax
	jmp	.L18
.L26:
	movl	$1, %eax
	jmp	.L18
.L46:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L8
.L43:
	movq	stderr(%rip), %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	call	fwrite@PLT
	orl	$-1, %edi
	call	exit@PLT
.L47:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1
	.long	2
	.long	3
	.long	4
	.align 16
.LC2:
	.long	4
	.long	4
	.long	4
	.long	4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
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
