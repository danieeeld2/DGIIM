#include <stdio.h>
#include <stdlib.h>

extern int begin, end, resultado;
extern char formato[];

void suma()
{
	int *p = &begin, r = 0;
	while (p != &end)
		r += *p++;
	resultado = r;
	
	printf(formato, resultado, resultado);
	
	exit(0);
}
