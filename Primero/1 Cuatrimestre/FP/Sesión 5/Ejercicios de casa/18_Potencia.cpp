/*	Programa para calcular la potencia
	x^n y funcion factorial n! */
	
#include <iostream>

using namespace std;

int main(){
	double base;
	int entero;
	int entero_factorial;
	int contador;
	double potencia;
	int factorial;
	
	cout << "Introduzca la base de la potencia: ";
	cin >> base;
	cout << "Introduzca el exponente: ";
	cin >> entero;
	
	potencia = base;
	
	//	Vamos primero con la potencia
	
	for (contador = 1; contador != entero; contador++)
		potencia = potencia * base;
		
	cout << "\nLa potencia " << base << " elevado a " << entero << " es: " << potencia;
	
	//	Vamos ahora con el factorial
	
	cout << "\n\nIntroduzca un entero: ";
	cin >> entero_factorial;
	
	factorial = entero_factorial;
	
	if ( entero_factorial == 0 )
		cout << "\n\nEl factorial de 0 es 1 ";
	else{	
		for (contador = 1; contador != entero_factorial; contador++)
			factorial = factorial * (entero_factorial - contador);
			
		cout << "\nEl factorial de " <<  entero_factorial << " es " << factorial;
	};
	
	cout << "\n\n";
	
	system ("pause");
}
	
		
