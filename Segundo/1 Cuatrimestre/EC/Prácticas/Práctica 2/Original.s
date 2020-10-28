.section .data
lista:		.int 1,2,10,  1,2,0b10,  1,2,0x10
longlista:	.int   (.-lista)/4
resultado:	.int   0
  formato: 	.asciz	"suma = %u = 0x%x hex\n"

# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B

.section .text
_start: .global _start
# main: .global  main

	call trabajar	# subrutina de usuario
#	call imprim_C	# printf()  de libC
	call acabar_L	# exit()   del kernel Linux
#	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	ret

suma:
	push     %rdx
	mov  $0, %eax
	mov  $0, %rdx
bucle:
	add  (%rbx,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rcx
	jne    bucle

	pop   %rdx
	ret

#imprim_C:			# requiere libC
#	mov   $formato, %rdi
#	mov   resultado,%esi
#	mov   resultado,%edx
#	mov          $0,%eax	# varargin sin xmm
#	call  printf		# == printf(formato, res, res);
#	ret

acabar_L:
	mov        $60, %rax
	mov  resultado, %edi
	syscall			# == _exit(resultado)
	ret

#acabar_C:			# requiere libC
#	mov  resultado, %edi
#	call _exit		# ==  exit(resultado)
#	ret
