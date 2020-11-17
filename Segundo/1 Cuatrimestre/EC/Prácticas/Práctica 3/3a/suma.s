# suma.s del Guión anterior
# 0.- ensamblar, linkar y depurar con
#	as  -g   suma.s -o suma.o
#	ld       suma.o -o suma
#	gdb -tui suma

.section .data
lista:		.int 1,2,10,  1,2,0b10,  1,2,0x10
longlista:	.int (.-lista)/4
resultado:	.int 0

.section .text
_start:	.global _start

	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma
	mov  %eax, resultado	# res = suma(&lista,longlista);

	mov   $60, %rax
	mov    $0, %edi
	syscall			# _exit(resultado);

suma:
	push     %rdx		# preservar %rdx (se usa como índice)
	mov  $0, %eax		# acumulador
	mov  $0, %rdx		# índice
bucle:
	add  (%rbx,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rcx
	jne    bucle

	pop   %rdx		# recuperar %rdx antiguo
	ret
