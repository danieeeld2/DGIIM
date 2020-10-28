.section .data
lista:		.int	0, 1, 2, 3, 4, 5, 6, 7, 8, 9 
longlista:	.int   (.-lista)/4
resultado:	.quad   0
  formato: 	.asciz	"suma = %lld = 0x%16llx\n"
  formato2:	.string "media = %i = 0x%08x\n"
  formato3:	.string "resto = %i = 0x%08x\n"

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
	mov  longlista, %rcx	# Contiene la longitud de la lista
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	mov  %edx, resultado+4	# Para que se copien en la parte superior, que es la que nos interesa. +4 significa que se salta 4 bytes
	ret

trabajar2:
	mov	$lista, %rdi
	mov    $10,    %rcx	# Por alguna razón, se modifica el valor de longlista
	call media
	ret
	
trabajar3:
	mov	$lista, %rdi
	mov    $10,    %rcx	# Por alguna razón, se modifica el valor de longlista
	call resto
	mov    %edx, %eax
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
	mov  (%rdi,%rsi,4), %r8d	# Copiamos el valor del vector en r8d
	mov   %r8d, %r9d		# Copiamos r8d en r9d
	sar   $31, %r9d			# Desplazamiento aritmético a la derecha. Nos quedamos con el bit de signo
	add   %r8d, %eax		# Almacenamos la suma de la parte baja en eax
	adc   %r9d, %edx		# Almacenamos la suma de la parte alta, más el acarreo, si existe, en edx
	inc   %rsi			# Incrementa el valor de rsi en 1
	cmp   %rsi,%rcx			# Compara el valor de los dos registros
	jne   .Lbucle			# Se salta si rsi==rcx (fin del bucle)

	ret

media:
	call  suma
	idiv  %rsi

	ret
	
resto:
	call  suma
	idiv  %rsi
	mov   %edx, %eax

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
	mov	    $0, %rsi
	add	  %eax, %esi
	mov	    $0, %rdx
	add	  %eax, %edx
	mov	    $0, %eax
	call  printf
	ret
	
imprim_resto:
	mov  $formato3, %rdi
	mov	    $0, %rsi
	add	  %eax, %esi
	mov	    $0, %rdx
	add	  %eax, %edx
	mov	    $0, %eax
	call  printf
	ret


acabar_C:			# requiere libC
	mov  resultado, %rdi
	call _exit		# ==  exit(resultado)
	ret
