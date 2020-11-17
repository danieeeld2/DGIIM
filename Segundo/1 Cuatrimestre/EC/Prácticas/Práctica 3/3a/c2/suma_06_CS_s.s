# suma.s del Guión anterior
# 1.- cambiando a convención SystemV
# 2.- añadiendo printf() y cambiando syscall por exit()
# 3.- extrayendo suma a módulo C para linkar
# 4.- dejando sólo los datos, que el resto lo haga suma() en módulo C
# 5.- entero en C
# 6.- volviendo a sacar la suma a ensamblador
#	gcc -Og -g    suma_06_CS_c.c    suma_06_CS_s.s -o suma_06_CS
#
#	gcc -Og -g -c suma_06_CS_c.c
#	as      -g    suma_06_CS_s.s -o suma_06_CS_s.o
#	gcc           suma_06_CS_c.o    suma_06_CS_s.o -o suma_06_CS
#
#	ld            suma_06_CS_c.o    suma_06_CS_s.o -o suma_06_CS \
#					/usr/lib/x86*/crt?.o -lc     \
#					-dynamic-linker /lib64/ld-linux*

.section .text
suma:	.global suma
	mov  $0, %eax		# acumulador
	mov  $0, %rdx		# índice
bucle:
	add  (%rdi,%rdx,4), %eax
	inc   %rdx
	cmp   %rdx,%rsi
	jne    bucle

	ret
