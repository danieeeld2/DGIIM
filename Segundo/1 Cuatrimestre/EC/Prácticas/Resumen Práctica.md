# Resumen Prácticas Estructura de Datos

###### Daniel Alconchel Vázquez

------

### <u>Introducción</u>

#### Paso de parámetros :

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/EC/Prácticas/1.png)

#### Comandos para programas en C:

```bash
Compilar:	gcc nombre.c -o nombre
Ejecutar: ./nombre
Tipo de archivo: file ./nombre
¿Qué he hecho?: nm ./nombre
Desensamblar: objdump -d nombre # | less para versión reducida
Llamadas al sistema: strace ./nombre
LLamadas a bibliotecas: ltrace ./nombre
Bibliotecas que usa: ldd ./nombre
Examinar biblioteca: objdump -d nombre
```



#### Programa básico ensamblador :

Un programa ensamblador está formada por dos partes, la parte donde se declaran los datos y la parte donde se ejecutan las instrucciones:

```assembly
.data
.text
	.global _start
```

Veamos un ejemplo de un programa:

```assembly
.data
msg:	.string "hola mundo\n"
tam:	.quad .-msg

.text
		.global _start

write:	mov    $1 ,    %rax   # write
		mov    $1 ,    %rdi   # stdout
		mov    $msg ,  %rsi   # texto
		mov    tam ,   %rdx   # tamaño
		syscall             # llamada a write
		ret
		
exit:   mov    $60 ,   %rax   # exit
		xor    %rdi ,  %rdi   # 0
		syscall             # llamada a exit
		ret
		
_start: call   write         # llamada a función
		call   exit			 # llamada a función
```



Para poder ejecutar el código anterior, hay que compilarlo. Para ello:

```bash
# Opción A: ensamblar + enlazar
$ as nombre.s -o nombre.o
$ ld nombre.o -o nombre

# Opción B: Compilar directamente
$ gcc nombre.s - nombre

# Opción C: makefile
SHELL = bash
.ONESHELL:

ASM = $(wildcard *.s)
ATT = $(EXE:=.att)
SRC = $(wildcard *.cc)
EXE = $(basename  $(ASM) $(SRC))

ASFLAGS = -g -no-pie -nostartfiles
CFLAGS = -g -no-pie -Os -Wall
CXXFLAGS = $(CFLAGS)

all: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) core.* *~

test: $(EXE)
	@for i in {,un}signed{32,64}; do
		echo "#############################################################"
		echo "$$i"
		echo "#############################################################"
		./$$i
	done

%.att: %
	objdump -Cd $< > $@

.PHONY: all clean test
```



Para ver código de C o C++ en ensamblador usar: https://godbolt.org/z/9bT7sb



