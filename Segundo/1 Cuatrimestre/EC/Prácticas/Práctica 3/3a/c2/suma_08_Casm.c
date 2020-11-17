// 8.- gcc -Og -g suma_08_Casm.c -o suma_08_Casm

#include <stdio.h>  // para printf()
#include <stdlib.h> // para exit()

int lista[] = {1, 2, 10, 1, 2, 0b10, 1, 2, 0x10};
int longlista = sizeof(lista) / sizeof(int);
int resultado = 0;

int suma(int *array, int len)
{
	int res = 0;
	for (int i = 0; i < len; ++i)
		// res += array[i]; // traducir sólo esta línea a ASM
		asm("add (%2,%1,4),%0"
		    :"+r" (res)     // output-input
		    :"r" ((long)i), // input
		     "r"   (array)
		    // : "cc"           // clobber
		);
	return res;
}

int main()
{
	resultado = suma(lista, longlista);
	printf("resultado = %d = 0x%x\n", resultado,resultado);
}

