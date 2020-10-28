# Resumen Prácticas Estructura de Datos

###### Daniel Alconchel Vázquez

------

### <u>Introducción</u>

#### Paso de parámetros :

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/EC/Prácticas/Fotos/1.png)

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



### <u>Práctica 1</u>

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/EC/Prácticas/Fotos/2.png)

#### 

#### Ejercicio 1: gcc

Crear los ficheros sum.c y msum.c y reproducir con ellos la siguiente sesión de comandos de Linux.

Comenzamos creando los archivos:

```c
// Archivo sum.c:
long plus(long, long);

void sumstore(long x, long y, long *dest){
    long t = plus(x,y);
    *dest = t;
}

// Archivo msum.c:
void sumstore(long x, long y, long *dest);

int main(){
    long d;
    sumstore(2,3,&d);
    return d;
}

long plus(long a, long b){
    long s = a+b;
    return s;
}
```

Y, realizamos ahora la siguiente rutina de comandos:

```bash
$ gcc sum.c msum.c -o sum	# Compilamos todo
$ ./sum; echo $?	# Muestra cod.ret. 5 = 2+3
5
$ file sum	# Es shared object
sum: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=68cef05bd4e7e12c9510b3140d97e9286d00c6f1, for GNU/Linux 3.2.0, not stripped

$ gcc -no-pie sum.c msum.c -o sum	# No optimiza
$ ./sum: echo $?
5
$ file sum	# Es executable
sum: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=136cd42181ed20d0b0b8b5588b13eb1e73f2c5e1, for GNU/Linux 3.2.0, not stripped

$ FNSP=-fno-stack-protector	# Ahorrarse teclear switches tan largos
$ FNAUT=-fno-asynchronous-unwind-tables

$ gcc -Og -S sum.c $FNAUT
$ cat sum.s
.file	"sum.c"
	.text
	.globl	sumstore
	.type	sumstore, @function
sumstore:
	endbr64
	pushq	%rbx
	movq	%rdx, %rbx
	call	plus@PLT
	movq	%rax, (%rbx)
	popq	%rbx
	ret
	.size	sumstore, .-sumstore
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

$ gcc -Og -S msum.c $FNAUT $FNSP
$ cat msum.s
	.file	"msum.c"
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	subq	$24, %rsp
	leaq	8(%rsp), %rdx
	movl	$3, %esi
	movl	$2, %edi
	call	sumstore@PLT
	movl	8(%rsp), %eax
	addq	$24, %rsp
	ret
	.size	main, .-main
	.globl	plus
	.type	plus, @function
plus:
	endbr64
	leaq	(%rdi,%rsi), %rax
	ret
	.size	plus, .-plus
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

$ gcc -c sum.s msum.c # Crea sum.o, msum.o desde ASM/C
$ ls; file *.o
msum.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
sum.o:  ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped

$ gcc -no-pie sum.o msum.o -o sum # Crea exe sum desde objetos
$ file sum; ./sum; echo $?
sum: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=14991395a604625a78927ff96796f90def509a25, for GNU/Linux 3.2.0, not stripped
5
```

#### Ejercicio 2: as y ld

Mismo resultado que el ejercicio anterior, pero usando estos comandos. Veámoslo:

```bash
$ rm sum *sum.[os]; ls	# Limpiamos los ficheros anteriores
$ gcc -Og -S sum.c msum.c $FNAUT $FNSP
$ ls *sum.?
msum.c  msum.s  sum.c  sum.s

$ as sum.s -o sum.o	# Ensamblar
$ as msum.s -o msum.o
$ ls *.o; file *.o
msum.o  sum.o
msum.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
sum.o:  ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped

$ ld sum.o msum.o
ld: aviso: no se puede encontrar el símbolo de entrada _start; se usa por defecto 0000000000401000

$ gcc -### sum.o msum.o	# Para ver como enlaza gcc
$ gcc -### -no-pie *.o

$ ld sum.o msum.o -o sum
$ file sum; ./sum; echo $?
sum: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, not stripped
Violación de segmento (`core' generado)
139
```



#### 2 Código ensamblador y código máquina

La versión ensamblador de los ficheros vistos anteriormente, es una representación legible de las instrucciones máquina en que se convierte el programa. Con tiene, también, directivas, como **.text** (iniciar sección de código) y **,size** (tamaño de un objeto).

El ensamblador emite código máquina conforme traduce, ocupando posiciones (bytes) de memoria. El símbolo "." es la posición por donde va el ensamblador, y cada etiqueta tome el valor de una dirección de memoria.

Los ficheros **.o** no son legibles, ya que contiene código máquina, pero sí se puede desensamblar:

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/EC/Prácticas/Fotos/3.png)

#### Ejercicio 3: objdump y nm

Reproducir la siguiente sesión en línea de comandos de Linux

```bash
$ objdump -d sum.o
sum.o:     formato del fichero elf64-x86-64


Desensamblado de la sección .text:

0000000000000000 <sumstore>:
   0:	f3 0f 1e fa          	endbr64 
   4:	53                   	push   %rbx
   5:	48 89 d3             	mov    %rdx,%rbx
   8:	e8 00 00 00 00       	callq  d <sumstore+0xd>
   d:	48 89 03             	mov    %rax,(%rbx)
  10:	5b                   	pop    %rbx
  11:	c3                   	retq   

$ objdump -t sum.o
sum.o:     formato del fichero elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 sum.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .note.gnu.property	0000000000000000 .note.gnu.property
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	0000000000000012 sumstore
0000000000000000         *UND*	0000000000000000 _GLOBAL_OFFSET_TABLE_
0000000000000000         *UND*	0000000000000000 plus

$ nm sum.o
U _GLOBAL_OFFSET_TABLE_
                 U plus
0000000000000000 T sumstore

$ objdump -S sum.o	# Falta -g
sum.o:     formato del fichero elf64-x86-64


Desensamblado de la sección .text:

0000000000000000 <sumstore>:
   0:	f3 0f 1e fa          	endbr64 
   4:	53                   	push   %rbx
   5:	48 89 d3             	mov    %rdx,%rbx
   8:	e8 00 00 00 00       	callq  d <sumstore+0xd>
   d:	48 89 03             	mov    %rax,(%rbx)
  10:	5b                   	pop    %rbx
  11:	c3                   	retq   

$ gcc -g -Og -c sum.c
$ objdump -S sum.o	# Ahora sí
sum.o:     formato del fichero elf64-x86-64


Desensamblado de la sección .text:

0000000000000000 <sumstore>:
long plus(long, long);

void sumstore(long x, long y, long *dest){
   0:	f3 0f 1e fa          	endbr64 
   4:	53                   	push   %rbx
   5:	48 89 d3             	mov    %rdx,%rbx
    long t = plus(x,y);
   8:	e8 00 00 00 00       	callq  d <sumstore+0xd>
    *dest = t;
   d:	48 89 03             	mov    %rax,(%rbx)
  10:	5b                   	pop    %rbx
  11:	c3                   	retq   

$ objdump -t sum.o	# Secciones -g
sum.o:     formato del fichero elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 sum.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_loc	0000000000000000 .debug_loc
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .note.gnu.property	0000000000000000 .note.gnu.property
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	0000000000000012 sumstore
0000000000000000         *UND*	0000000000000000 _GLOBAL_OFFSET_TABLE_
0000000000000000         *UND*	0000000000000000 plus

$ objdump -h sum.o	# Ver text=11B
sum.o:     formato del fichero elf64-x86-64

Secciones:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000012  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000052  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000052  2**0
                  ALLOC
  3 .debug_info   000000cc  0000000000000000  0000000000000000  00000052  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING, OCTETS
  4 .debug_abbrev 000000aa  0000000000000000  0000000000000000  0000011e  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  5 .debug_loc    000000f1  0000000000000000  0000000000000000  000001c8  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  6 .debug_aranges 00000030  0000000000000000  0000000000000000  000002b9  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING, OCTETS
  7 .debug_line   0000004f  0000000000000000  0000000000000000  000002e9  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING, OCTETS
  8 .debug_str    000000e5  0000000000000000  0000000000000000  00000338  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  9 .comment      0000002b  0000000000000000  0000000000000000  0000041d  2**0
                  CONTENTS, READONLY
 10 .note.GNU-stack 00000000  0000000000000000  0000000000000000  00000448  2**0
                  CONTENTS, READONLY
 11 .note.gnu.property 00000020  0000000000000000  0000000000000000  00000448  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 12 .eh_frame     00000038  0000000000000000  0000000000000000  00000468  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA

$ gcc -Og -c sum.c	# Quitar -g
$ objdump -S suma.o	# Ahora no
objdump: 'suma.o': No hay tal ficher
```



#### 3. Primer programa completo en ASM: llamada al sistema

Vamos a analizar el siguiente código:

```assembly
.section .data
saludo:		.ascii	"Hola a todos!\nHello, World!\n"
longsaludo:	.quad	.-saludo

.section .text
.global _start
_start:
	mov $1, %rax
	mov         $1, %rdi
	mov    $saludo, %rsi
	mov longsaludo, %rdx
	syscall

	mov $60, %rax
	mov  $0, %rdi
	syscall
```

En el código se pueden distinguir: instrucciones del procesador, directivas del ensamblador, etiquetas, expresiones y comentarios. Las instrucciones usadas en este caso han sido **SYSCALL** y **MOV**, para realizar las dos llamadas requeridas al sistema (*write* y *exit*).  Las **directivas** son comandos que entiende el ensamblador, y que se han usado para declarar secciones de datos y código.  Las **etiquetas** se han usado para nombrar 3 elementos (*saludo, longsaludo, _start*) y permiten referirse a ellos posteriormente. Por último,los comentarios se indican con **#** ó **/* */**, los valores inmediatos con **$** y los registros con **%**.

En la arquitectura x86-64, cada posición de memoria es un byte.

#### Ejercicio 4: gdb -tui

Ensamblar y enlazar el programa saludos.s, incluyendo información de depuración, y reproducir la siguiente sesión gdb.

```bash
$ as -g saludo.s -o saludo.o	# Ensamblar incluyendo información de depuración
$ ld saludo.o -o saludo	# Enlazar
$ gdb -tui saludo	# Sesión gdb en modo text-user-interface
list	# localizar línea "mov $1, %rdi"
break 9	# Colocar breakpoint en dicha línea
info break

run
disassemble
print $rip	# RIP=0x4000b7
print $rax	# Rax=1, RDI=0
info registers
stepi
p $rip	# EIP sigue avanzando (p=print)
p $rdi	# RDI=1
si	# si=stepi
p/x $rsi	# RSI=0x6000df > RIP
dias_start

x/32cb &saludo
x/32xb &saludo
x/s &saludo
p (char*) &saludo
p (long) longsaludo
x/1dg &longsaludo	# Examine para ver dirección de inicio y valor
x/1xg &longsaludo 	# comprobar ordenamiento little-endian
x/8xb &longsaludo    
si # Comprobar regs EAX,RDI,RSI,RDX = 1,1,0x6000df,28    
info reg 	# (write,stdout,&saludo,longsaludo)    
disas # $saludo=$0x6000df(inm), longs=0x6000fb(dir), %rdx=28(reg)    
si # Se escribe mensaje en pantalla (View->GDB Console) 
3x si / cont # eq.gr: Pulsar cont o clickar 3 stepi para exit(0)

clear 9 # otra ejecución: parar justo antes del final    
break 16 # localizar la 2a syscall y ponerle bkpt    
info break    
run    
set $rdi=1 # y cambiar código de retorno sobre la marcha    
stepi / cont    
cl 16 # otra ejecución: parar antes de imprimir    
br 12 # localizar la primera syscall y ponerle bkpt    
info br    
run    
print saludo # 'saludo' has unknown type; cast it to 
p (int) saludo # interpreta 4B "Hola" (4 códigos ASCII)   
p /x (int) saludo # como un entero 0x616c6f48, ver Apénd.1   
p /x(char) saludo # typecast a char 1B ‘H’    
p (char) saludo # hex 0x48, decimal 72    
p &saludo # dirección de memoria    
p (char*)&saludo # typecast a char* = string    
p (char*)&saludo+13 # saltarse 13 letras, localizar \n    
p*((char*)&saludo+13)  # cambiarlo por '-'    
set var *((char*)&saludo+13)='-'    
print (char*)&saludo # comprobar cambio en memoria    
cont # comprobar cambio en ejecución    
quit 
```



#### 4. Segundo programa ASM: Llamadas a funciones (libC, usuario)

Es conveniente dividir el código de un programa entre varias funciones, de manera que al ser estas más cortas y estar centradas en una tarea concreta, se facilita su legibilidad y comprensión, además de poder ser reutlizadas si hacen falta en otras partes del programa.

Conocer el fucionamiento de la pila (stack) es fundamental para comprender cómo se implementan a bajo nivel las funciones. La pila se utiliza (en llamadas a subrutinas) para guardar la dirección de retorno, oara almacenar las variables locales y para pasar argumentos. Las instrucciones PUSH y POP y las llamadas y retornos de subrutinas (CALL, RET, INT, IRET) utilizan de forma implícita la pila, que es la zoa de memoria adonde apunta el puntero de la pila RSP. La pila crece hacia direcciones inferiores de memoria, y RSP apunta al último elemento insertado (topede pila), de manera que PUSH primero decrementa RSP en el número de posiciones de memoria que ocupe el dato a insertar y luego escribe ese dato en las posiciones reservadas, a partir de donde apunta RSP ahora. Similarmente POP primero lee del tope de pila, guardando el valor en donde indique su argumento, y luego incrementa RSP. Por su parte, CALL guarda la dirección de retorno en la pila antes de saltar a la subrutina indicada como argumento y RET recupera de la pila la dirección de retorno.

```assembly
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
```



### <u>Práctica 2</u>

#### 5.1. Sumar N enteros sin signo de 32 bits sobre dos registros de 32 bits usando uno de ellos como acumulador de acarreos (N=16)

Empezamos tomando el **archivo necesario para trabajar** esta sección: https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.1-Original.s

En su forma actual **suma.s** ya permite un tamaño variable de la lista. A partir de ahora trabajaremos en un nuevo fichero llamado **media.s**

El primer paso es copiar el contenido de **suma.s** en **media.s**. A continuación, la primera modificación que podemos llevar a cabo es cambiar la expresión de la lista por una en la que aparezca el número 1 repetido 16 veces.

```assembly
.section .data

/*Cambiamos la lista original a una lista que repite 16 veces el 1*/

lista:      .int 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
longlista:  .int (.-lista)/4
```

Podemos comprobar que es correcto mediante la siguiente secuencia de comandos en terminal:

```bash
$ gcc media.s -o media -no-pie -nostartfiles	# Sin sección .start
$ ./media
$ echo $?
16
```

**¿Qué valor mínimo habría que repetir 16 veces para que se produzca acarreo**

Tenemos que el valor mínimo para que se produzca acarreo al sumar 16 veces es el **0x1000 0000**. Esto es facil de ver sumando mentalmente, pues en las primeras 15 sumas el resultado que tendríamos sería **0xf000 0000**, pero, si volvemos a sumar **0x1000 0000**, el resultado sería **0x0001 0000 0000**, que ya son más de 32 bits, y, entonces, truncaría en los 32 primeros bits, quedando de resultado el **0x0000 0000**.

Podemos comprobarlo facilmente, realizando el siguiente cambio en **media.s**:

```assembly
.section .data
lista:		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000, 
            .int 0x10000000, 0x10000000, 0x10000000, 0x10000000, 
            .int 0x10000000, 0x10000000, 0x10000000, 0x10000000, 
            .int 0x10000000, 0x10000000, 0x10000000, 0x10000000
longlista:	.int (.-lista)/4
```

```bash
$ gcc media.s -o media -no-pie -nostartfiles	# Sin sección .start
$ ./media
$ echo $?
0
```

**¿Se produce acarreo usando 0x0fff ffff?**

Modificamos nuevamente el archivo **media.s**:

```assembly
.section .data
lista:		.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
            .int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
            .int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
            .int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
longlista:	.int (.-lista)/4
```

```bash
$ gcc media.s -o media -no-pie -nostartfiles	# Sin sección .start
$ ./media
$ echo $?
240
```

Notemos que al pasar el calor **0x0fff ffff** a binario sería **0b1111111111111111111111111111**, que, si lo pasamos a decimal, sería **4294967280**, que es un valor totalmente distinto, y mucho más alto, al que devuelve. Para comprobar que está sucediendo, vamos a depurar con ***gdb***.

El primer paso es descomentar las funciones **imprim_C** y **acabar_C**, para que el compilador las tome como líneas de código. Una vez hecho eso:

```bash
$ gcc -g media.s -o media -no-pie -nostartfiles
$ gdb media
(gdb)break 41	# El inicio de la subrutina bucle
Punto de interrupción 1 at 0x7ffff7de5f20: file init-first.c, line 44.
(gdb)run
suma = 4294967280 = 0xfffffff0 hex
```

Como observamos, es el valor que esperábamos obtener. Veamos ahora que ocurría al sumar 16 veces el dato **0x1000 0000**.

```bash
$ ./media
suma = 0 = 0x0 hex
```

Seguimos viendo que se pierde el bit de acarreo, por lo que vamos a tratar de solucionarlo. Para ello, lo que haremos será almacenar el acarreo en otro registro, el cual, luego concatenaremos y cambiaremos el resultado a 64 bits. Para ello, es necesario usar la orden **JNC** para saber cuando hay que incrementar el acarreo:

```assembly
suma:
	xor %eax, %eax			#Pone el registro a 0
	xor %ecx, %ecx			#Pone el registro a 0
	xor %edx, %edx			#Pone el registro a 0
.Lbucle:
	cmp %rcx, %rsi		#Compara el valor de los dos registros
	je .Lfin	#Salta si la comparación anterior resulta en igualdad (rsi==rcx)
	add (%rdi,%rcx,4), %eax	#(%rdi,%rcx,4)=(%rdi,%rcx,4)+eax 
							#(%rdi,%rcx,4) es una posición del vector
	jnc .Lsin_acarreo		#Salta si no hay acarreo en la operación anterior
	inc %edx			#Aumenta el valor de edx en 1
.Lsin_acarreo:
	inc %rcx			#Aumenta el valor de rcx en 1
	jmp .Lbucle			#Salta
.Lfin:
	ret	
```

También, vamos a tener qie cambiar el tipo de resultado a **.quad**, para que la salida tenga de tamaño 8 bytes:

```assembly
.section .data
lista:		.int 0xffffffff, 0xffffffff
resultado: .quad 0
```

Ahora, para concatenar los registros **edx:eax**, tenemos que:

```assembly
mov %eax, resultado
mov %edx, resultadotrabajar:
	mov     $lista, %rdi
	mov  longlista, %esi
	call suma		
	mov  %eax, resultado
	mov  %edx, resultado+4		# Movemos offset
	ret
```

Finalmente, modificamos imprime_C para que nos muestre por pantalla un resultado de 64 bits:

```assembly
imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	xor   %eax, %eax	
	call  printf		# == printf(formato, res, res);
	ret
```

Para comprobar que funciona, simplemente:

```bash
$ gcc media.s -o media -no-pie -nostartfiles
$ ./media
suma = 8589934590 = 0x00000001fffffffe
```

**Para ver el programa completo ir a:** https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.1-Solucion.s

#### 5.2. Sumar N enteros si signo de 32 bits sobre dos registros de 32 bits mediante extesión de ceros (N=16)

Sabemos que un número E sin signo de N bits puede ser extendido a N+M bits sin más que añadirle M bits a cero como parte más significativa (a la izquierda). En nuestro caso, para este ejercicio, deseamos sumar al acumulador **edx:eax**, de 32+32 bits, un elemento de la lista, E, de 32 bits. Como E no tiene signo, podemos extenderlo a 64 bits imaginando 32 bits a la izquierda. Para sumar estos dos números en doble precisión (haciendo suma de 32 bits), comenzamos sumando la parte menos significativa, puesto que puede haber acarreo, y luego sumamos las partes significativas.

Simplemente, tenemos que realizar un simple cambio en la línea de código:

```assembly
suma:
	xor %eax, %eax			#Pone el registro a 0
	xor %ecx, %ecx			#Pone el registro a 0
	xor %edx, %edx			#Pone el registro a 0
.Lbucle:
	cmp %rcx, %rsi				#Compara el valor de los dos regustros
	je .Lfin					#Salta si la comparación anterior (rsi==rcx)
	add (%rdi,%rcx,4), %eax		#(%rdi,%rcx,4)=(%rdi,%rcx,4)+eax, 
								#donde (%rdi,%rcx,4) es una posición del vector
	adc $0, %edx				#edx=edx+0+cf
	inc %rcx					#Aumenta en 1 rl valor de rcx
	jmp .Lbucle					#Salta
.Lfin:
	ret	
```

La orden **adc** toma el valor del acarreo y lo suma al destino junto a otro valor que pasemos. De esra forma, conseguimos sumar el valor del acarreo en la parte significativa y el resto en la menos significativa. 

**Fichero completo:** https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.2-Solucion.s

**<u>Inciso:</u>**

Antes de probar si esto funciona, notemos que a lo largo de la sesión se nos pide probar como responde el programa dependiendo de la inicializaciń del dato lista. Para evitar estar perdiendo el tiempo  reescribiendo la inicialización, existen varios métodos para aligerar el cambio de inicialización, como:

- Dejar comentada una línea de cada ejemplo para poder copiar y pegarla rapidamente las veces que la necesitemos

- Dejar comentada la inicialización completa y descomentarla cuando sea necesario

- Usar las directivas **irpc** y **.macro**:

  ```assembly
  .section .data
  	.macro linea
  		#	.int 1,1,1,1
  		#	.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
  		...  ...
  	.endm
  lista: .irpc i,1234
  	    linea
  	    .endr
  	    
  # Basta con descomentar la línea que necesites
  ```

- La estructura aterior se puede ampliar con condicionales:

  ```assembly
  .section .data
  #ifndef TEST
  #define TEST 9
  #endif
  	.macro
  	#if TEST==1
  		.int 1,1,1,1
  	#elif TEST==2
  		.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
  	#else
  		.error "Definir un TEST dentro del rango aceptado"
  	#endif
  	.endm
  ```

  De esta forma se pueden crear test para comprobar el funcionamiento del programa:

  ```bash
  for i in $(seq 1 9); do 
  	rm unsigned
  	gcc -x assembler-with-cpp -D TEST=$i -no-pie -nostartfiles media.s -o media
  	printf "____TEST%02d____%35s\n" $i " " | tr " " "-"; ./media
  done
  ```

  Muy importante quitar comentarios con '#' y quitar la línea **#define TEST valor**.

Volviendo a nuestro programa, veamos que funciona:

```bash
$ gcc media.s -o media -no-pie -nostartfiles
$ ./media
suma = 8589934590 = 0x00000001fffffffe
```

Probémoslo para otra inicalización, por ejemplo la lista de 16 veces **0x0fff ffff**:

```bash
$ gcc media.s -o media -no-pie -nostartfiles
$ ./media
suma = 4294967280 = 0x00000000fffffff0
```

Probemos ahora a hacer una batería de test. Para ello usaremos la script vista anteriormente y la siguiente batería:

```assembly
.section .data
#ifndef TEST
#endif
	.macro linea
#if TEST==1
	.int 1, 1, 1, 1
#elif TEST==2
	.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
#elif TEST==3
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==4
	.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#elif TEST==5
	.int -1, -1, -1, -1
#elif TEST==6
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==7
	.int 300000000, 300000000, 300000000, 300000000
#elif TEST==8
	.int 5000000000, 5000000000, 5000000000, 5000000000
#else
	.error "Definir TEST valido"
#endif
	.endm
			
	lista:		.irpc i,1234
			linea
			.endr

	longlista:	.int (.-lista)/4
	resultado:	.quad   0
  	formato: 	
  			.ascii "resultado \t =   %18lu (uns)\n"
  			.ascii "\t\t = 0x%18lx (hex)\n"
  			.asciz "\t\t = 0x %08x %08x\n"
```

**Fichero completo:** https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.2-ConTest.s

**Script**: https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.2-test.sh

Al ejecutar el script obtenemos:

```bash
rm: no se puede borrar 'unsigned': No existe el archivo o el directorio
__TEST01__-----------------------------------
resultado 	 =                   16 (uns)
		 = 0x                10 (hex)
		 = 0x 00000010 00000000
__TEST02__-----------------------------------
resultado 	 =           4294967280 (uns)
		 = 0x          fffffff0 (hex)
		 = 0x 00000010 00000000
__TEST03__-----------------------------------
resultado 	 =           4294967296 (uns)
		 = 0x         100000000 (hex)
		 = 0x 00000010 00000000
__TEST04__-----------------------------------
resultado 	 =          68719476720 (uns)
		 = 0x         ffffffff0 (hex)
		 = 0x 00000010 00000000
__TEST05__-----------------------------------
resultado 	 =          68719476720 (uns)
		 = 0x         ffffffff0 (hex)
		 = 0x 00000010 00000000
__TEST06__-----------------------------------
resultado 	 =           3200000000 (uns)
		 = 0x          bebc2000 (hex)
		 = 0x 00000010 00000000
__TEST07__-----------------------------------
resultado 	 =           4800000000 (uns)
		 = 0x         11e1a3000 (hex)
		 = 0x 00000010 00000000
5.2-ConTest.s: Mensajes del ensamblador:
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
5.2-ConTest.s:28: Aviso: valora 0x12a05f200 truncado a 0x2a05f200
__TEST08__-----------------------------------
resultado 	 =          11280523264 (uns)
		 = 0x         2a05f2000 (hex)
		 = 0x 00000010 00000000
5.2-ConTest.s: Mensajes del ensamblador:
5.2-ConTest.s:28: Error: Definir TEST valido
5.2-ConTest.s:28: Error: Definir TEST valido
5.2-ConTest.s:28: Error: Definir TEST valido
5.2-ConTest.s:28: Error: Definir TEST valido
__TEST09__-----------------------------------
./test.sh: línea 6: ./unsigned: No existe el archivo o el directorio

```

Como vemos, el **test 9** simplemente sirve para eliminar, indirectamente el ejecutable. Por otro lado, fijate en que en el **test 8** hay varios warnings. Esto se debe a que habíamos colocado un valor que no cabía en 32 bits, por lo que lo trunca para así poder realizar sumas de números de 32 bits.

El **test 5**, pese a que no da error, es erróneo, ya que nuestro programa no trabaja con signos.

#### 5.3. Sumar N enteros con signo de 32 bits sobre dos registros de 32 bits (mediante extesión natural del signo) (N=16)

Partimos nuevamente del archivo original, sin modificar y trabajemos desde 0 para ir repasando.

**Archivo:** https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.1-Original.s

Comenzamos haciendo la siguiente serie de cambios:

```assembly
.section .data
	lista:          .int    -1, -1 
	resultado:		.quad	0	# Necesitamos 32+32 bits
	formato: 	.asciz	"suma = %lld = 0x%16llx\n"
# ------------------- #

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


```

 **Archivo final**: https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.3-Solucion.s

Al igual que el apartado anterior, podemos modificar la lista para hacer un test, que nos permita comprobar que el funcionamiento del programa es el correcto. Para ello, realizamos el siguiente cambio:

```assembly
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
    formato: 	.ascii "resultado \t =   %18ld (sgn)\n"
```

**Archivo modificado completo**: https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.3-ConTest.s

Para ponerlo en marcha, usaremos la siguiente script:

```bash
#!/bin/bash

for i in $(seq 1 19); do
	rm salida
	gcc -x assembler-with-cpp -D TEST=$i -no-pie -nostartfiles 5.3-ConTest.s -o salida
	printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./salida
done
```

**Script**: https://github.com/danieeeld2/DGIIM/blob/master/Segundo/1%20Cuatrimestre/EC/Pr%C3%A1cticas/Pr%C3%A1ctica%202/5.3-test.sh

Si lo ejecutamos, veremos claramente que el **TEST14** y el **TEST19** son erróneos. 

```bash
__TEST14__-----------------------------------
resultado 	 =         -20719476736 (sgn)
		 = 0x  fffffffb2d05e000 (hex)
		 = 0x 00000010 2d05e000
__TEST19__-----------------------------------
resultado 	 =         -32000000000 (sgn)
		 = 0x  fffffff88ca6c000 (hex)
		 = 0x 00000010 8ca6c000
5.3-ConTest.s: Mensajes del ensamblador:
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200
5.3-ConTest.s:50: Aviso: valora 0xffffffff4d2fa200 truncado a 0x4d2fa200

```

Por un lado, el 14 nos da un resultado negativo, cuando se trataba de una suma de positivos. Este error se debe a que se ha producido un desbordamiento, es decir, hemos superado el número más grande que podíamos representar. Por otro lado, en el 19, el número eleigo no cabe en un registro de 32 bits, por lo que el compilador lo trunca.

#### 5.4. Media y resto de N enteros con signo de 32 bits calculada usando registros de 32 bits (N=16)

