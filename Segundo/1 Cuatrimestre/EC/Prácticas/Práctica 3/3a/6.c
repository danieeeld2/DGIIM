#include <stdio.h>

int lista[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int N = sizeof(lista) / sizeof(int);

extern int suma(int *begin, int *end);

int main()
{
	int resultado = suma(lista, lista + N);
	printf("suma = %i = 0x%08x\n", resultado, resultado);
}
