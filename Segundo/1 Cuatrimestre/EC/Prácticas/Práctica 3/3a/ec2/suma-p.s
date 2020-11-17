# suma.s del Guión anterior
# 0.- ensamblar, linkar y depurar con
#	as  -g   suma.s -o suma.o
#	ld       suma.o -o suma
#	gdb -tui suma

.section .data
lista:		.int 0,1,2,3,4,5,6,7,8,9
longlista:	.int (.-lista)/4
resultado:	.int 0
formato:	.string "%i = 0x%08x\n"

.section .text
_start:	.global _start

	mov     $lista, %rdi
	mov  longlista, %esi
	call suma
#	mov  %eax, resultado	# res = suma(&lista,longlista);

	mov $formato,%rdi
	mov %eax,%esi
	mov %eax,%edx
	xor %eax,%eax
	call printf # printf("%i = 0x%08x\n", resultado, resultado)

	mov   $60, %rax
	xor %edi,%edi
	syscall			# _exit(resultado);

#############################
# int suma(int *lista, int n)
# eax             rdi    esi
#############################
suma:
	xor %eax,%eax
	xor %edx,%edx
bucle:
	add  (%rdi,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rsi
	jne    bucle
	ret
