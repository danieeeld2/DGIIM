.data
	begin:     .int 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	end:
	resultado: .int 0
	formato:   .string "suma = %d = 0x%08x\n"

.text
	.globl begin, end, formato, resultado, _start

_start:
	jmp suma
