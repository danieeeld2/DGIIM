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
	mov  $0, %rdx		# Hacemos 0 rdx
	mov  $0, %rsi		# Hacemos 0 esi
	mov  $0, %r8d		# Hacemos 0 r8d
	mov  $0, %r9d		# Hacemos 0 r9d
.Lbucle:
	mov  (%rdi,%rsi,4), %rdx	# Copiamos el valor en rdx. Esta solución usa directamente un registro de 64 bits
	add   %rdx, %rax		# Acumulamos la suma en rax
	inc   %rsi			# Incrementa el valor de rsi en 1
	cmp   %rsi,%rcx			# Compara el valor de los dos registros
	jne   .Lbucle			# Se salta si rsi==rcx (fin del bucle)
	cltd				# Convertimos rax-->edx:eax

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
