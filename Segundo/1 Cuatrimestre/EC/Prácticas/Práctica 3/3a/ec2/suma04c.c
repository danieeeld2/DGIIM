#include <stdio.h>
#include <stdlib.h>

extern int lista[];
extern char formato[];
extern int longlista;
extern int resultado;

void suma()
{
	int res = 0;
	for (int i = 0; i < longlista; ++i)
		res += lista[i];
	resultado = res;
	
	printf(formato, resultado, resultado);
	exit(0);
}
