.section .data
#ifndef TEST
#endif
	.macro linea
#if TEST==1
	.int -1 ,-1 ,-1, -1
#elif TEST==2
	.int 0x04000000, 0x04000000, 0x04000000, 0x04000000
#elif TEST==3
	.int 0x08000000, 0x08000000, 0x08000000, 0x08000000
#elif TEST==4
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==5
	.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
#elif TEST==6
	.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
#elif TEST==7
	.int 0xF0000000, 0xF0000000, 0xF0000000, 0xF0000000
#elif TEST==8
	.int 0xF8000000, 0xF8000000, 0xF8000000, 0xF8000000
#elif TEST==9
	.int 0xF7FFFFFF. 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF
#elif TEST==10
	.int 100000000, 100000000, 100000000, 100000000
#elif TEST==11
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==12
	.int 300000000, 300000000, 300000000, 300000000
#elif TEST==13
	.int 2000000000, 2000000000, 2000000000, 2000000000
#elif TEST==14
	.int 3000000000, 3000000000, 3000000000, 3000000000
#elif TEST==15
	.int -100000000, -100000000, -100000000, -100000000
#elif TEST==16
	.int -200000000, -200000000, -200000000, -200000000
#elif TEST==17
	.int -300000000, -200000000, -200000000, -200000000
#elif TEST==18
	.int -2000000000, -2000000000, -2000000000, -2000000000
#elif TEST==19
	.int -3000000000, -3000000000, -3000000000, -3000000000
#else
	.error "Definir TEST valido"
#endif
	.endm
			
	lista:		.irpc i,1234
			linea
			.endr
longlista:	.int   (.-lista)/4
resultado:	.quad   0
  formato: 	.asciz	"suma = %lld = 0x%16llx\n"

.section .text
_start: .global _start

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rdi	# Contiene la lista
	mov  longlista, %rcx	# Contiene la longitud de la lista
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	mov  %edx, resultado+4	# Para que se copien en la parte superior, que es la que nos interesa. +4 significa que se salta 4 bytes
	ret

#####################################################
# long long suma(int *lista, int n)
#    edx:eax	       rdi   esi
####################################################

suma:
	mov  $0, %eax		# Hacemos 0 eax
	mov  $0, %edx		# Hacemos 0 edx
	mov  $0, %rsi		# Hacemos 0 esi
	mov  $0, %r8d		# Hacemos 0 r8d
	mov  $0, %r9d		# Hacemos 0 r9d
.Lbucle:
	mov  (%rdi,%rsi,4), %eax	# Copiamos el valor del vector en eax
	mov   %eax, %edx		# Copiamos eax en edx
	sar   $31, %edx			# Desplazamiento aritmético a la derecha. Nos quedamos con el bit de signo
	add   %eax, %r8d		# Almacenamos la suma de la parte baja en r8d
	adc   %edx, %r9d		# Almacenamos la suma de la parte alta, más el acarreo, si existe, en r9d
	inc   %rsi			# Incrementa el valor de rsi en 1
	cmp   %rsi,%rcx			# Compara el valor de los dos registros
	jne   .Lbucle			# Se salta si rsi==rcx (fin del bucle)
	mov   %r8d, %eax		# La parte baja del resultado la dejamos en eax
	mov   %r9d, %edx		# La parte alta del resultado la dejamos en edx

	ret

##################################################################################

imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);
	ret

acabar_C:			# requiere libC
	mov  resultado, %rdi
	call _exit		# ==  exit(resultado)
	ret
