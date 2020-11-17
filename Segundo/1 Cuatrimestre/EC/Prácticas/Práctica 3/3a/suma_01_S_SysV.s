# suma.s del Guión anterior
# 1.- cambiando a convención SystemV
#	as  -g   suma_01_S_SysV.s -o suma_01_S_SysV.o
#	ld       suma_01_S_SysV.o -o suma_01_S_SysV
#	gdb -tui suma_01_S_SysV

.section .data
lista:		.int 1,2,10,  1,2,0b10,  1,2,0x10
longlista:	.int (.-lista)/4
resultado:	.int 0

.section .text

_start:	.global _start

	mov     $lista, %rdi
	mov  longlista, %esi
	call suma
	mov  %eax, resultado	# res = suma(&lista,longlista);

	mov   $60, %rax
	mov    $0, %edi
	syscall			# _exit(resultado);

suma:
	mov  $0, %eax		# acumulador
	mov  $0, %rdx		# índice
bucle:
	add  (%rdi,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rsi
	jne    bucle

	ret
