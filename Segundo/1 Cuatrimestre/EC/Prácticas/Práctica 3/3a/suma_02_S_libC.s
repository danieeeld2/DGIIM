# suma.s del Guión anterior
# 1.- cambiando a convención SystemV
# 2.- añadiendo printf() y cambiando syscall por exit()
#	as  -g   suma_02_S_libC.s -o suma_02_S_libC.o
#	ld       suma_02_S_libC.o -o suma_02_S_libC \
#		  -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2

.section .data
lista:		.int 1,2,10,  1,2,0b10,  1,2,0x10
longlista:	.int (.-lista)/4
resultado:	.int 0
formato:	.string	"resultado = %d = 0x%x hex\n"
				# formato para printf() libC
.section .text
_start:	.global _start

	mov     $lista, %rdi
	mov  longlista, %esi
	call suma
	mov  %eax, resultado	# res = suma(&lista,longlista);

	mov   $formato, %rdi
	mov  resultado, %esi	# podría haber sido %eax
	mov  resultado, %edx
	mov         $0, %eax
	call printf		# printf(formato, resultado, resultado);

	mov         $0, %edi
	call exit		# exit(status);

suma:
	mov  $0, %eax		# acumulador
	mov  $0, %rdx		# índice
bucle:
	add  (%rdi,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rsi
	jne    bucle

	ret
