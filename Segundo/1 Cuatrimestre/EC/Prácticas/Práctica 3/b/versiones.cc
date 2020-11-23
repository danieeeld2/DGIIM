#include <x86intrin.h> // __rdtscp

#include <array>       // array
#include <bitset>      // bitset
#include <chrono>      // now
#include <iomanip>     // setw
#include <iostream>    // cout endl
#include <mutex>       // once_flag
#include <numeric>     // iota

//------------------------------------------------------------------------------

const unsigned GAP = 12;            // gap between columns
const unsigned REP = 1000;          // how many times we repeat the experiment

//------------------------------------------------------------------------------

std::array<unsigned, 1 << 16> list; // 64K * 4B = 256KB

/*------------------------ Version 0 ---------------------------*/

// El máximo rendimiento teórico es simplemente retornar

unsigned popcount00(unsigned elem){
	return elem;
}

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
		"	jz 1f 		\n\t"	// Salta si es 0
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
	  jz 1f 
	  adc $0, %eax 
	  jmp 0b 
	  1: adc $0, %eax 

	  ret
*/

/*------------------------ Version 7 ---------------------------*/

unsigned popcount07(unsigned elem){
	int count = 0;
    for (unsigned i = 0; i < 8; ++i)
    {
        count += elem & 0x01010101;
        elem >>= 1;
    }
    count += (count >> 16);
    count += (count >>  8);
    return count & 0xff;
}

/*	Este código se basa en aplicar sucesivamente
	la máscara 0x0101.., para ir aumulando los bits de cada byte 
	en una nueva variable coount y sumar en árbol los 2 bytes.

	En 8 bits puede haber como máximo 8 bits A1 --> log(8)/log(2) = 3 bits
	0x01 --> 0000 0001 
	Como se hace en grupos de 8
	0x01 01 01 01 --> 0000 0001 0000 0001 ...

	 aa bb cc dd
	+00 00 aa bb
	-------------
	 aa bb xx yy
	+00 aa bb xx
	-------------
	 aa gg hh zz

	El resultado final, y que nos interesa, es zz, por eso aplicamos
	la máscara 0xff al final, para quitarnos la basura restante.

	El código ensamblador resultante es:

	popcount07(unsigned int):
	  movl $8, %eax
	  xorl %edx, %edx
	.L2:
	  movl %edi, %ecx
	  shrl %edi
	  andl $16843009, %ecx
	  addl %ecx, %edx
	  decl %eax
	  jne .L2
	  movl %edx, %eax
	  sarl $16, %eax
	  addl %eax, %edx
	  movl %edx, %eax
	  sarl $8, %eax
	  addl %edx, %eax
	  movzbl %al, %eax
	ret
*/


/*------------------------ Version 8 ---------------------------*/

unsigned popcount08(unsigned elem)
{
    elem = (elem & 0x55555555) + 
            ((elem >> 1) & 0x55555555);
    elem = (elem & 0x33333333) + 
            ((elem >> 2) & 0x33333333);
    elem = (elem & 0x0f0f0f0f) + 
            ((elem >> 4) & 0x0f0f0f0f);
    elem = (elem & 0x00ff00ff) + 
            ((elem >> 8) & 0x00ff00ff);
    elem = (elem & 0x0000ffff) + 
            ((elem >> 16) & 0x0000ffff);
    return elem;
}

/*	La idea reside en yo tengo elemento (32 bits). Comienzo
	sumando los bits de dos en dos y coloco la suma en la posición de esos
	dos bits. Como tengo que tomar de dos en dos bits, la máscara sera
	0101 0101 0101..., que, en hezadecimal es 0x555...

	A continuación tegno que sumar el resultado de esa suma de dos bits con el 
	resultado de las dos siguientes, es decir, sumamos de 4 en 4, por lo que la máscara 
	esta vez será 0011 0011 ..., que, en hexadecimal es 0x333...
	Además esta vez no me desplazo un bit, sino que me tengo que esplazar dos bits

	Así sucesivamente

	El código ensamblador resultante es-.

	popcount08(unsigned int):
	  movl %edi, %edx
	  shrl %edi
	  andl $1431655765, %edx
	  andl $1431655765, %edi
	  leal (%rdx,%rdi), %eax
	  movl %eax, %edx
	  shrl $2, %eax
	  andl $858993459, %edx
	  andl $858993459, %eax
	  addl %edx, %eax
	  movl %eax, %edx
	  shrl $4, %eax
	  andl $252645135, %edx
	  andl $252645135, %eax
	  addl %edx, %eax
	  movl %eax, %edx
	  shrl $8, %eax
	  andl $16711935, %edx
	  andl $16711935, %eax
	  addl %edx, %eax
	  movzwl %ax, %edx
	  shrl $16, %eax
	  addl %edx, %eax
    ret
*/


/*------------------------ Version 9 ---------------------------*/

unsigned popcount09(unsigned elem)
{
	unsigned count;
	asm("popcnt %1, %0 \n\t"
		 :"=r" (count)
		 : "r" (elem));
	return count;
}

/*	Esta versión se basa en usar directamente la orden popcnt.
	El código ensamblador resultante es tan sencillo como:

	popcount09(unsigned int):
  		popcnt %edi, %eax 

    ret
*/

/*------------------------ Version 10 ---------------------------*/

unsigned popcount10(unsigned elem)
{
	return __builtin_popcount(elem);
}

/*	Esta versión se basa en la misma que la anterior, pero facilitamos
	la escritura utilizando una función creada por alguna persona, que vio que esto
	se utilizaba con frecuencia y decidió simplificarlo al máximo
*/

/*------------------------ Version 11 ---------------------------*/

// En la última versión de C++20 incluyeron una versión:
#include <bit>
unsigned popcount11(unsigned elem)
{
	return std::popcount(elem);
}
	
	
/*------------------------ Version 11 ---------------------------*/

// Usando la stl
#include<bitset>
unsigned popcount12(unsigned elem)
{
	std::bitset<sizeof(elem)*8>bits(elem);
	return bits.count();
}

// A partir de aquí son las versiones multimedias. Simplemente leer guión. Ya están implementadas



//------------------------------------------------------------------------------

template <class _F> void test (_F& __f, const char* msg)
{
	using namespace std::chrono;
	
	static std::once_flag flag;
	static unsigned long long cycle_overhead;
	static duration<high_resolution_clock::rep, std::nano> time_overhead;
	unsigned id; // needed by __rdtscp()
	
	std::call_once(flag, [&]
	{
		cycle_overhead = std::numeric_limits<unsigned long long>::max();
		for (unsigned i = 0; i < REP * REP; ++i)
		{
			unsigned long long t1 = __rdtscp(&id);
			unsigned long long t2 = __rdtscp(&id);
			if (t1 < t2)
				cycle_overhead = std::min(cycle_overhead, t2 - t1);
		}
		
		time_overhead = duration<high_resolution_clock::rep, std::nano>::max();
		for (unsigned i = 0; i < REP * REP; ++i)
		{
			auto t1 = high_resolution_clock::now();
			auto t2 = high_resolution_clock::now();
			if (t1 < t2)
				time_overhead = std::min(time_overhead, t2 - t1);
		}
	});
	
	unsigned long long t1 = __rdtscp(&id);
	for (unsigned i = 0; i < REP; ++i)
		__f(list[0]);
	unsigned long long t2 = __rdtscp(&id);
	unsigned long long cycles = (t2 - t1) / REP;
	if (cycles > cycle_overhead) cycles -= cycle_overhead;
	
	unsigned result;
	auto time = duration<high_resolution_clock::rep, std::nano>::max();
	for (unsigned i = 0; i < REP; ++i)
	{
		result = 0;
		auto t1 = high_resolution_clock::now();
		std::for_each(list.begin(), list.end(), [&](unsigned x){ result += __f(x); });
		auto t2 = high_resolution_clock::now();
		time = std::min(time, t2 - t1);
	}
	if (time > time_overhead) time -= time_overhead;
	
	std::cout << '"' << std::setw(GAP * 2 - 2) << msg << '"' 
	          << std::setw(GAP) << result
	          << std::setw(GAP) << cycles
	          << std::setw(GAP) << std::fixed << std::setprecision(2)
	          << duration_cast<nanoseconds>(time).count() / static_cast<double>(list.size())
	          << std::setw(GAP) << duration_cast<nanoseconds>(time).count() / 1000.0
	          << std::endl;
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	std::iota(list.begin(), list.end(), 0);

	

	std::cout << "#" << std::setw(GAP * 2 - 1) << argv[0]
	          << std::setw(GAP) << "value"
	          << std::setw(GAP) << "cycles"
	          << std::setw(GAP) << "timex1(ns)"
	          << std::setw(GAP) << "timexn(us)"
	          << std::endl;

	test(popcount00, "popcount00");
	test(popcount01, "popcount01");
	test(popcount02, "popcount02");
	test(popcount03, "popcount03");
	test(popcount04, "popcount04");
	test(popcount05, "popcount05");
	test(popcount06, "popcount06");
	test(popcount07, "popcount07");
	test(popcount08, "popcount08");
	test(popcount09, "popcount09");
	test(popcount10, "popcount10");
	test(popcount11, "popcount11");
	test(popcount12, "popcount12");
}
