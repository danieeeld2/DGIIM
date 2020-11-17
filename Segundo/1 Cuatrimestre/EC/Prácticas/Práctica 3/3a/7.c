#include <stdio.h>

int lista[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int N = sizeof(lista) / sizeof(int);

int suma(int *begin, int *end)
{
	asm("    xor %eax, %eax  \n"
	    "0:  cmp %rdi, %rsi  \n"
	    "    je 1f           \n"
	    "    add (%rdi),%eax \n"
	    "    add $4,%rdi     \n"
	    "    jmp 0b          \n"
	    "1:  ret             \n");
}

int main()
{
	int resultado = suma(lista, lista + N);
	printf("suma = %i = 0x%08x\n", resultado, resultado);
}
