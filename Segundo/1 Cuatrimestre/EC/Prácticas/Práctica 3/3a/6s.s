################################
# int suma(int *begin, int *end)
# eax             rdi       rsi
################################

.text
	.globl suma

suma:
	xor %eax, %eax
0:	cmp %rdi, %rsi
	je 1f
	add (%rdi),%eax
	add $4,%rdi
	jmp 0b
1:	ret

