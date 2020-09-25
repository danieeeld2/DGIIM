/*	Programa que implementa el algoritmo de la multiplicación
	rusa de dos enteros n y m */
	
#include <iostream>

using namespace std;

int main(){
	int entero_n;
	int entero_m;
	int multiplicador;
	int multiplicando;
	int producto;
	
	cout << "Introduzca un número entero: ";
	cin >> entero_n;
	
	cout << "Introduzca un número entero: ";
	cin >> entero_m;
	
	multiplicador = entero_m;
	multiplicando = entero_n;
	producto = 0;
	
	do{		
		if (multiplicando % 2 != 0)
			producto = producto + multiplicador;
			
		multiplicando = multiplicando / 2;
		multiplicador = multiplicador * 2;
			
	}while(multiplicando != 0);
	
	cout << "\n\nEl producto de " << entero_n << " por " << entero_m << " es: " << producto;
	
	cout << "\n\n";
	
	system ("pause");
}
