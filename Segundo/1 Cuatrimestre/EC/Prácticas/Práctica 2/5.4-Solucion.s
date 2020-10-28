.section .data
lista:		.int	0, 1, 2, 3, 4, 5, 6, 7, 8, 9
longlista:	.int   (.-lista)/4
resultado:	.quad   0
  formato: 	.asciz	"suma = %lld = 0x%16llx\n"
  formato2:	.string "media = %i = 0x%08x\n"
  formato3:     .string "resto = %i = 0x%08x\n"

.section .text
_start: .global _start

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call trabajar2
	call imprim_media
	call trabajar3
	call imprim_resto
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rdi	# Contiene la lista
	mov  longlista, %esi	# Contiene la longitud de la lista
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	mov  %edx, resultado+4	# Para que se copien en la parte superior, que es la que nos interesa. +4 significa que se salta 4 bytes
	ret

trabajar2:
	mov 	$lista, %rdi
	mov  longlista, %esi
	call media
	ret

trabajar3:
	mov     $lista, %rdi
        mov  longlista, %esi
        call resto
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

######################################################
# int media(int *lista, int n)
#   eax    rdi       esi
#####################################################

media:
	push %rsi	# Para que no se modifique su valor
	call suma	# Llamamos a suma, la cual devuelve edx:eax
	pop  %rsi	# Deshacemos push
	idiv %esi	# (edx:eax)/esi --> eax

	ret

######################################################
# int media(int *lista, int n)
#   edx    rdi       esi
#####################################################

resto:
        push %rsi       # Para que no se modifique su valor
        call suma       # Llamamos a suma, la cual devuelve edx:eax
        pop  %rsi       # Deshacemos push
        idiv %esi       # (edx:eax)%esi --> edx
	mov  %edx, %eax

        ret


##################################################################################

imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);
	ret

imprim_media:
	mov  $formato2, %rdi
	mov       %eax, %esi
	mov	  %eax, %edx
	xor	  %eax, %eax
	call printf
	ret

imprim_resto:
        mov  $formato3, %rdi
        mov       %eax, %esi
        mov       %eax, %edx
        xor       %eax, %eax
        call printf
        ret


acabar_C:			# requiere libC
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
