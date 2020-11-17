#include<stdlib.h>	// Para exit()
#include<stdio.h>	// para printf()

int lista[]={1,2,10, 1,2,0b10, 1,2,0x10};
int longlista=sizeof(lista)/sizeof(int);
int resultado = 0;

int suma(int *array, int len){
	int res = 0;
	/* Las declaraciones e inicializaciones de variables, así como
	   el manejo del bucle y retorno del valor, lo hace mejor el compilador, luego,
	   dejamos esa parte esrita en C
	*/
	for(int i=0; i<len; ++i){
		/* La parte más interesante para hacer en ensamblador es la propia suma aritmética.
		   Como, en principio, no sabemos que registros usa el compilador, lo mejor es
		   escribir la versión extendida de asm y coordinarnos con el compilador.

		   Recordemos que:
		   Extendida: asm("<sentencia asm>" : <salidas> : <entradas> : <sobrescritos>)
		   Salidas: [<nombre ASM >] "=<restricción>" (<nombre C >)
		   Entradas: [<nombre ASM >] "<restricción>" (<expresión C >)
		   Sobrescritos: "<reg>" | "cc" | "memory"

		*/

		asm("add (%[a], %[i], 4), %[r]"
			:[r] "+r" (res)
			:[a] "r"  (array), [i] "r" ((long)i)	// Necesitamos que todo sea 64 bits
			// Los sobreescritos no hace falta, porque en el propio código asm no se sobrescriben
			);
	}
	return res;
}

int main(){
	resultado=suma(lista,longlista);
	printf("resultado = %d = %0x hex\n", resultado, resultado);
	exit(0);
}

/* 	Aclaración:
	Si no pasáramos nombres opcionales (etiquetas) a las restricciones, a cada una
	se le asigna un número, por ejemplo a [r] "+r" (res) se le asigna %0
*/