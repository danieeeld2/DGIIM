# suma.s del Guión anterior
# 1.- cambiando a convención SystemV
# 2.- añadiendo printf() y cambiando syscall por exit()
# 3.- extrayendo suma a módulo C para linkar
# 4.- dejando sólo los datos, que el resto lo haga suma() en módulo C
#	gcc -Og -g -c suma_04_SC_c.c
#	as      -g    suma_04_SC_s.s -o suma_04_SC_s.o
#	ld            suma_04_SC_c.o    suma_04_SC_s.o -o suma_04_SC \
#		-lc   -dynamic-linker /lib64/ld-linux-x86-64.so.2


.section .data
lista:		.int 1,2,10,  1,2,0b10,  1,2,0x10
longlista:	.int (.-lista)/4
resultado:	.int 0
formato:	.string	"resultado = %d = 0x%x hex\n"

.global lista, longlista, resultado, formato

.section .text
_start:  .global _start
	jmp suma


