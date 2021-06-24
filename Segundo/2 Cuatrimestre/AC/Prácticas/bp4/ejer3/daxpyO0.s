	.file	"daxpy.c"
	.text
	.section	.rodata
.LC0:
	.string	"Falta num\n"
	.align 8
.LC2:
	.string	"Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
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
	subq	$168, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -164(%rbp)
	movq	%rsi, -176(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	%rsp, %rax
	movq	%rax, %rbx
	cmpl	$1, -164(%rbp)
	jg	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	movl	$-1, %edi
	call	exit@PLT
.L2:
	movq	-176(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -148(%rbp)
	movl	$47, -140(%rbp)
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -136(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -192(%rbp)
	movq	$0, -184(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -208(%rbp)
	movq	$0, -200(%rbp)
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	movq	%rax, %rdx
	andq	$-4096, %rdx
	movq	%rsp, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rdx
.L3:
	cmpq	%rdx, %rsp
	je	.L4
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L3
.L4:
	movq	%rax, %rdx
	andl	$4095, %edx
	subq	%rdx, %rsp
	movq	%rax, %rdx
	andl	$4095, %edx
	testq	%rdx, %rdx
	je	.L5
	andl	$4095, %eax
	subq	$8, %rax
	addq	%rsp, %rax
	orq	$0, (%rax)
.L5:
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -128(%rbp)
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -120(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	movq	%rax, %rdx
	andq	$-4096, %rdx
	movq	%rsp, %rdi
	subq	%rdx, %rdi
	movq	%rdi, %rdx
.L6:
	cmpq	%rdx, %rsp
	je	.L7
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L6
.L7:
	movq	%rax, %rdx
	andl	$4095, %edx
	subq	%rdx, %rsp
	movq	%rax, %rdx
	andl	$4095, %edx
	testq	%rdx, %rdx
	je	.L8
	andl	$4095, %eax
	subq	$8, %rax
	addq	%rsp, %rax
	orq	$0, (%rax)
.L8:
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -112(%rbp)
	movl	$1, -144(%rbp)
	jmp	.L9
.L10:
	movq	-128(%rbp), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	movl	-144(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	movq	-112(%rbp), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	movl	-144(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -144(%rbp)
.L9:
	movl	-144(%rbp), %eax
	cmpl	-148(%rbp), %eax
	jle	.L10
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	movl	$1, -144(%rbp)
	jmp	.L11
.L12:
	movq	-128(%rbp), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	imull	-140(%rbp), %eax
	movl	%eax, %ecx
	movq	-112(%rbp), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	addl	%eax, %ecx
	movq	-112(%rbp), %rax
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -144(%rbp)
.L11:
	movl	-144(%rbp), %eax
	cmpl	-148(%rbp), %eax
	jle	.L12
	leaq	-80(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	movq	-80(%rbp), %rdx
	movq	-96(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	movq	-72(%rbp), %rdx
	movq	-88(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC1(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -104(%rbp)
	movl	-148(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-112(%rbp), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %edx
	movq	-112(%rbp), %rax
	movl	(%rax), %ecx
	movq	-104(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %xmm0
	leaq	.LC2(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movq	%rbx, %rsp
	movl	$0, %eax
	movq	-56(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L14
	call	__stack_chk_fail@PLT
.L14:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
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
