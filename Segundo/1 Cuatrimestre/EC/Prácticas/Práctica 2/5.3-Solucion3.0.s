.section .data
lista:		.int	-1, -1 
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
	mov  longlista, %esi	# Contiene la longitud de la lista
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	mov  %edx, resultado+4	# Para que se copien en la parte superior, que es la que nos interesa. +4 significa que se salta 4 bytes
	ret

#####################################################
# long long suma(int *lista, int n)
#    edx:eax	       rdi   esi
####################################################

suma:
	xor %ecx, %ecx
	xor %eax, %eax
.Lbucle:
	movslq  (%rdi,%rcx,4), %rdx	# 64 bits
	add	       	 %rdx, %rax	# Suma ambas partes
	inc		 %rcx		# Aumenta rcx en uno
	cmp		 %rcx, %rsi	# Compara ambos valores
	jne		    .Lbucle	# Se salta si la comparación anterior resulta en igualdad
	mov		 %rax, %rdx
	shr		  $32, %rdx	# Desplazamiento lógico a la derecha de 32 bits

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
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
