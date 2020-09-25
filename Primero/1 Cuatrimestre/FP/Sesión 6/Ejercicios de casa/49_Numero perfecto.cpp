/*	Programa que indica si un entero es
	un número perfecto.
	Se considera número perfecto a aquel que se puede
	expresar como suma de sus divisores positivos,
	menos él mismo */
	
#include <iostream>

using namespace std;

int main(){
	int tope;
	int numero;
	int divisor;
	int suma;
	int maximo_perfecto;
	bool es_perfecto;
	
	
	cout << "Introduzca un número tope: ";
	cin >> tope;
	
	divisor = 1;
	suma = 0;
	numero = 1;
	maximo_perfecto = 1;
	
	while(numero != tope){
		
		while(divisor != numero){
			if ( numero % divisor == 0)
				suma = suma + divisor;
			
			divisor++;
		};
	
		es_perfecto = numero == suma;
	
		if (es_perfecto && (numero > maximo_perfecto))
			maximo_perfecto = numero;
			
		numero++;
		divisor = 1;
		suma = 0;
	};
	
	cout << "\nEl mayor número perfecto hasta " << tope << " es " << maximo_perfecto;
	
	cout << "\n\n";
	
	system ("pause");
}
