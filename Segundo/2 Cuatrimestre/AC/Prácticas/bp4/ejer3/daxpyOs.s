	.file	"daxpy.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Falta num\n"
.LC2:
	.string	"Tiempo(seg): %f\ny[0]=%d, y[N-1]=%d \n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	decl	%edi
	jg	.L2
	movq	stderr(%rip), %rsi
	leaq	.LC0(%rip), %rdi
	call	fputs@PLT
	orl	$-1, %edi
	call	exit@PLT
.L2:
	movq	8(%rsi), %rdi
	call	atoi@PLT
	movq	%rsp, %rdi
	movl	%eax, %ebx
	cltq
	leaq	15(,%rax,4), %rax
	movq	%rax, %rcx
	movq	%rax, %rdx
	andq	$-4096, %rcx
	andq	$-16, %rdx
	subq	%rcx, %rdi
	movq	%rdi, %rcx
.L3:
	cmpq	%rcx, %rsp
	je	.L4
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L3
.L4:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	je	.L5
	orq	$0, -8(%rsp,%rdx)
.L5:
	movq	%rax, %rdx
	movq	%rsp, %rcx
	andq	$-4096, %rax
	movq	%rsp, %r14
	subq	%rax, %rcx
	andq	$-16, %rdx
	movq	%rcx, %rax
.L6:
	cmpq	%rax, %rsp
	je	.L7
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L6
.L7:
	movq	%rdx, %rax
	andl	$4095, %eax
	subq	%rax, %rsp
	testq	%rax, %rax
	je	.L8
	orq	$0, -8(%rsp,%rax)
.L8:
	leaq	3(%rsp), %r13
	movl	$1, %eax
	movq	%r13, %r12
	andq	$-4, %r13
	shrq	$2, %r12
.L9:
	cmpl	%eax, %ebx
	jl	.L22
	movl	%eax, (%r14,%rax,4)
	movl	%eax, 0(%r13,%rax,4)
	incq	%rax
	jmp	.L9
.L22:
	leaq	-72(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	xorl	%eax, %eax
.L11:
	incq	%rax
	cmpl	%eax, %ebx
	jl	.L23
	imull	$47, (%r14,%rax,4), %edx
	addl	%edx, 0(%r13,%rax,4)
	jmp	.L11
.L23:
	xorl	%edi, %edi
	leaq	-56(%rbp), %rsi
	decl	%ebx
	call	clock_gettime@PLT
	movq	-48(%rbp), %rax
	subq	-64(%rbp), %rax
	movslq	%ebx, %rbx
	cvtsi2sdq	%rax, %xmm0
	movq	-56(%rbp), %rax
	subq	-72(%rbp), %rax
	divsd	.LC1(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	movl	0(%r13,%rbx,4), %ecx
	movb	$1, %al
	movl	0(,%r12,4), %edx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	movq	-40(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leaq	-32(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
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
