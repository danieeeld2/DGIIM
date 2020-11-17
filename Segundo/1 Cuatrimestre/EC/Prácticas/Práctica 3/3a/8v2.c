#include <stdio.h>

int lista[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int N = sizeof(lista) / sizeof(int);

int suma(int *begin, int *end)
{
	int r = 0;
	while (begin != end)
	{
		asm("add (%1),%0" : "+r" (r), "+r" (begin) : "r" (end));
		begin++;
	}
	return r;
}

int main()
{
	int resultado = suma(lista, lista + N);
	printf("suma = %i = 0x%08x\n", resultado, resultado);
}
