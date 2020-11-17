// 7.- gcc -Og -g suma_07_Casm.c -o suma_07_Casm

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()

int lista[] = {1, 2, 10, 1, 2, 0b10, 1, 2, 0x10};
int longlista = sizeof(lista) / sizeof(int);
int resultado = 0;

int suma(int *array, int len)
{
//	int res=0;
//	for (int i = 0; i < len; ++i)
//	    res += array[i];
//	return res;

	asm("        mov  $0, %eax	\n" // EAX – gcc salva-invocante
	    "        mov  $0, %rdx	\n" // RDX – gcc salva-invocante
	    "bucle:                          \n"
	    "        add (%rdi,%rdx,4), %eax \n"
	    "        inc %rdx                \n"
	    "        cmp %rdx,%rsi           \n"
	    "        jne bucle               \n"
	// La sintaxis extendida incluiría:
	//   :             // output
	//   :             // input
	//   : "cc",       // clobber
	//     "eax","rdx" // en este caso, la hemos comentado
	);                 // y nos ahorramos muchos %% arriba
}

int main()
{
	resultado = suma(lista, longlista);
	printf("resultado = %d = 0x%x\n", resultado,resultado);
}

