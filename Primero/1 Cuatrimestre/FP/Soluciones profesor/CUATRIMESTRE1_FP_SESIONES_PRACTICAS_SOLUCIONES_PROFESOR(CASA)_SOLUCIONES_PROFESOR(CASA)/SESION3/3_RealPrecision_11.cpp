
/*	
   Programa para practicar con los problemas de precision y desbordamiento.
*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	int		resultado_a, entero1, entero2;
	double	resultado_b, real1, real2;
	double	resultado_c;
    double resultado_d, resultaod_e, resultado_f;
	double	real, otro_real;


    cout.precision(20);

	// Apartado a

	entero1 = 123456789;
	entero2 = 123456780;
	resultado_a = entero1 * entero2;

	cout << "entero1 = "  << entero1 << endl;
	cout << "entero2 = "  << entero2 << endl;
	cout << "resultado_a = entero1 * entero2" << endl;
	cout << "\n\t(int) resultado_a = " << resultado_a << endl << endl;  // 1425960444

	// El resultado debia ser del orden de 10e18, imposible de almacenar en un int
	// por lo que el numero guardado es incorrecto, resultado de desbordamiento

    // Apartado b

    long grande;
    int chico1, chico2;
    chico1 = 123456789;
    chico2 = 123456780;
    grande = chico1 * chico2;
    
    cout << "chico1 = "  << chico1 << endl;
    cout << "chico2 = "  << chico2 << endl;
    cout << "grande = entero1 * entero2" << endl;
    cout << "\n\t(int) resultado_b = " << resultado_b << endl << endl;  // 1425960444
    
    // También es erroneo por un desbordamiento previo de chico1*chico2, luego se acumula
    // 1425960444 como double
    
	// Apartado c

	real1 = 123.1;
	real2 = 124.2;
	resultado_c = real1 * real2;

	cout << "real1 = " <<  real1 << endl;
	cout << "real2 = " <<  real2 << endl;
	cout << "resultado_c = real1 * real2" << endl;
	cout << "\n\t(double) resultado_c = " << resultado_c;  //  15289.02
    cout << "\n\t 15289.02 es : " << 15289.02;
	cout << "\n\n";

	// Correcto.
	// En cualquier caso, recordemos que toda parte real se ha de considerar siempre que se representa de forma aproximada.


	// Apartado d

	real1 = 123456789.1;
	real2 = 123456789.2;
	resultado_d = real1 * real2;

	cout << "real1 = " << real1 << endl;
	cout << "real2 = " << real2 << endl;
	cout << "resultado_d = real1 * real2" << endl;
	cout << "\n\t(double) resultado_d = " << resultado_d << endl << endl;  // 15241578787227558.0

	// Hay un claro problema de precision al tener el resultado mas de 16 digitos.
	// Deberia dar: 15241578787227557.72
		

	// Apartado e

	real = 2e34;
	otro_real = real + 1;
	otro_real = otro_real - real;

	cout << "real = " << real << endl;
	cout << "otro_real = real + 1" << endl;
	cout << "otro_real = otro_real - real" << endl;
	cout << "\n\t(double) otro_real = " << otro_real << endl << endl;  // 0.0

	/* 
	El resultado no es 1 como cabria esperar sino 0, debido al problema
	de la precision al trabajar en coma flotante.
	El numero 2e34 + 1 tiene mas de 16 digitos, por lo que su representacion no es exacta
	y se "pierden" digitos en su representacion. Asi que el resultado de 2e34 + 1 es 2e34.
   Por lo tanto, el resultado de la resta final es cero.
	*/

    // caso f
    
	real1 = 1e+300;
	real2 = 1e+200;
	resultado_f = real1 * real2;

	cout << "real1 = " << real1 << endl;
	cout << "real2 = " << real2 << endl;
	cout << "resultado = real1 * real2" << endl;
	cout << "\n\t(double) resultado_f = " << resultado_f << endl << endl;
	
	// Infinito. Los reales en coma flotante no se "desbordan" de la misma forma que los int. 
	// El resultado es infinito que es un valor especifico que se representa en coma flotante.

    
    // caso g
	float chico;
    double granded;

    granded = 2e+150;
    chico = granded;

	cout << "chico (float)  = " << chico << endl;
	cout << "granded (double) = " << grande << endl;
	cout << "chico = granded" << endl;
	cout << "\n\t(double) resultado = " << chico << endl << endl;  

	// Infinito. Los reales en coma flotante no se "desbordan" de la misma forma que los int. 
	// El resultado es infinito que es un valor especifico que se representa en coma flotante.
}

