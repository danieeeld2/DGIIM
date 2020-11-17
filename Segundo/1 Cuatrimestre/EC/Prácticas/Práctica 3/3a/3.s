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
