.section .data
	lista:		.int 0xffffffff, 0xffffffff
	longlista:	.int (.-lista)/4
	resultado:	.quad   0
  	formato: 	.string "suma = %llu = 0x%016llx\n"
  	
#################################################################################
# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B
#################################################################################

.section .text
_start: .global _start

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rdi
	mov  longlista, %esi
	call suma		
	mov  %eax, resultado
	mov  %edx, resultado+4		# Movemos offset
	ret
	
##################################################
# long long suma(int *lista, int n)
#   edx:eax             rdi    esi
##################################################

suma:
	xor %eax, %eax			#Pone el registro a 0
	xor %ecx, %ecx			#Pone el registro a 0
	xor %edx, %edx			#Pone el registro a 0
.Lbucle:
	cmp %rcx, %rsi			#Compara el valor de los dos registros
	je .Lfin			#Salta si la comparación anterior resulta en igualdad (rsi==rcx)
	add (%rdi,%rcx,4), %eax	#(%rdi,%rcx,4)=(%rdi,%rcx,4)+eax, donde (%rdi,%rcx,4) es una posición del vector
	jnc .Lsin_acarreo		#Salta si no hay acarreo en la operación anterior
	inc %edx			#Aumenta el valor de edx en 1
.Lsin_acarreo:
	inc %rcx			#Aumenta el valor de rcx en 1
	jmp .Lbucle			#Salta
.Lfin:
	ret			

###########################################################################################3

imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	xor   %eax, %eax	
	call  printf		# == printf(formato, res, res);
	ret


acabar_C:			# requiere libC
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
