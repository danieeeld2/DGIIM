/*	Programa que lee valores enteros desde el teclado
	hasta que se introduzca 0  e indica cual es el mínimo */
	
#include <iostream>

using namespace std;

int main(){
	int dato;
	int minimo;
	const int TERMINADOR = 0;
	
	//	Para la primera vez
	
	cout << "Introduzca un entero: ";
	cin >> dato;
	
	minimo = dato;
	
	cout << "El mínimo es: " << minimo;
	
	while ( dato!= TERMINADOR ){
		cout << "\n\nIntroduzca un nuevo entero: ";
		cin >> dato;
		
		if ( dato < minimo ){
			minimo = dato;
			cout << "El nuevo mínimo es: " << minimo;
		}
		
		if ( dato == TERMINADOR )
			cout << "Has introducido 0, el programa finalizará ";
	};
	
	cout << "\n\n";
	
	system ("pause");
}
