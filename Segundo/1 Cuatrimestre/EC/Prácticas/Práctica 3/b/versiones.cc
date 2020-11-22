#include <x86intrin.h> // __rdtscp

#include <array>       // array
#include <bitset>      // bitset
#include <chrono>      // now
#include <iomanip>     // setw
#include <iostream>    // cout endl
#include <mutex>       // once_flag
#include <numeric>     // iota


/*------------------------ Version 1 ---------------------------*/

unsigned popcount01(unsigned elem){
	unsigned count = 0;
	for(unsigned i = 0; i<sizeof(elem) * 8; ++i){
		unsigned mask = 1 << i;
		if((elem & mask) != 0)	// Con estructura condicional
			++count;
	}
	return count;
}

/*------------------------ Version 2 ---------------------------*/

unsigned popcount02(unsigned elem){
	unsigned count = 0;
	for(unsigned i = 0; i<sizeof(elem) * 8; ++i){
		unsigned mask = 1 << i;
		count += (elem & mask) != 0;	// Quitando la estructura condicional
	}
	return count;
}


/* 	Al pasar estas dos primeras versiones a lenguaje máquina, para lo que hemos
	usado la página https://godbolt.org , obtenemos que para ambos casos, el
	compilador traduce el código a las mismas sentencias máquina, luego, 
	no habrá, prácticamente, diferencia de rendimiento.

	popcount01(unsigned int):
	      xorl %ecx, %ecx
  		  xorl %eax, %eax
 		  movl $1, %esi
	.L3:
		  movl %esi, %edx
		  sall %cl, %edx
		  andl %edi, %edx
		  cmpl $1, %edx
		  sbbl $-1, %eax
		  incl %ecx
		  cmpl $32, %ecx
		  jne .L3
		  ret
*/

/*------------------------ Version 3 ---------------------------*/

unsigned popcount03(unsigned elem){
	unsigned count = 0;
	unsigned mask = 1;	// Máscara constante, no la desplazamos
	for(unsigned i = 0; i<sizeof(elem) * 8; ++i){
		if((elem & mask) != 0)
			++count;
		elem >>= 1;	// Desplazamos un bit a la derecha

	}
	return count;
}

/*	Esta versión comienza a mejorar un poco. Al pasar el código
	a lenguaje máquina, obervamos que este es más corto que en los 
	casos anteriores:

	popcount03(unsigned int):
	  movl $32, %edx
	  xorl %eax, %eax
	.L3:
	  movl %edi, %ecx
	  andl $1, %ecx
	  cmpl $1, %ecx
	  sbbl $-1, %eax
	  shrl %edi
	  decl %edx
	  jne .L3
	  ret
*/

/*------------------------ Version 4 ---------------------------*/

unsigned popcount04(unsigned elem){
	unsigned count = 0; 
	while(elem){	// Como vamos desplazando el elemento, seguimos mientras no sea 0
		count += elem & 1;	// La máscara es siempre 1, no hace falta declarar una variable
							// Ahora no hace falta comparar porque elem siempre es 1 (sino no entra en el bucle)
		elem >>= 1;
	}
	return count;
}

/*	Como podemos obervar a continuación. El código ensamblador resultante es mucho
	más corto, por lo que es posible que se ejecute más rápido:

	popcount04(unsigned int):
	  xorl %eax, %eax
	.L3:
	  testl %edi, %edi
	  je .L1
	  movl %edi, %edx
	  shrl %edi
	  andl $1, %edx
	  addl %edx, %eax
	  jmp .L3
	.L1:
	  ret
*/

/*------------------------ Version 5 ---------------------------*/

unsigned popcount05(unsigned elem){
	unsigned count = 0; 
	while(elem){	 
		// count += elem & 1;	 
		// elem >>= 1;

		/*	Como al hacer shr el bit desplazado acaba en el
			acarreo, lo podemos sumar directamente y ahorrarnos
			ĺa mácara
		*/

		asm("shr $1, %0  \n\t"	// Desplazamiento de un bit a la derecha
			"adc $0, %1  \n\t"	// Sumamos el bit
			: "+r" (elem), "+r" (count)		// De entrada y salida
			);
	}
	return count;
}

/*	Como vemos esta versión es mucho mas corta
	que las anteriores, luego, en principio, tendrá un 
	mejor rendimiento:

	popcount05(unsigned int):
  		xorl %eax, %eax
	.L3:
	  testl %edi, %edi
	  je .L1
	  shr $1, %edi 
	  adc $0, %eax 

	  jmp .L3
	.L1:
	  ret

*/

/*------------------------ Version 6 ---------------------------*/

unsigned popcount06(unsigned elem){
	unsigned count = 0; 
		/*	Ahora, intentamos quitarnos la instrucción testl. Para ello, aprovechamos 
			que la instrucción shr también afecta a la bandera Z (Zero flag), el
			cual se pone a true si el resultado de la suma es 0 y false en 
			caso contrario
		*/

	asm("0: shr $1, %0  \n\t"	// Etiqueta 0
		"	jz if 		\n\t"	// Salta si es 0
		"	adc $0, %1  \n\t"	
		"	jmp 0b		\n\t"	// Vuelve a la etiqueta 0 
		"1:	adc $0, %1	\n\t"	// Salida del bucle y añadimos la última iteración
		: "+r" (elem), "+r" (count)		// De entrada y salida
		);
	return count;
}

/*	Aquí el resultado en ensamblador:

	popcount05(unsigned int):
	  xorl %eax, %eax
	  0: shr $1, %edi 
	  jz if 
	  adc $0, %eax 
	  jmp 0b 
	  1: adc $0, %eax 

	  ret
*/

/*------------------------ Version 7 ---------------------------*/

unsigned popcount07(unsigned elem){
	unsigned count = 0;
}

