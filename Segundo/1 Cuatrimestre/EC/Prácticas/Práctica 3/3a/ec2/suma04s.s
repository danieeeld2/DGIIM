.section .data
lista:		.int 0,1,2,3,4,5,6,7,8,9
longlista:	.int (.-lista)/4
formato:	.string "%i = 0x%08x\n"
resultado:	.int 0

.section .text
	.global _start
	.global formato
	.global lista
	.global longlista
	.global resultado

_start:

	jmp suma
