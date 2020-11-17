.data
	begin:   .int 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	end:
	formato: .string "suma = %d = 0x%08x\n"

.text
_start:	.globl _start

	mov $begin,%rdi
	mov $end,%rsi
	call suma

	mov $formato,%rdi
	mov %eax,%esi
	mov %eax,%edx
	xor %eax,%eax
	call printf

	xor %rdi,%rdi
	call exit

################################
# int suma(int *begin, int *end)
# eax             rdi       rsi
################################
suma:
	xor %eax,%eax
0:	cmp %rdi,%rsi
	je 1f
	add (%rdi),%eax
	add $4,%rdi
	jmp 0b
1:	ret
