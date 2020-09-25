/*	Programa que dada una secuencia de enteros de 0
	a 100 calcula la subsecuencia ordenada de menor
	a mayor de mayor longitud */
	
#include <iostream>

using namespace std;

int main(){
	int entero;
	int contador;
	int maximo;
	int minimo;
	int posicion_minimo;
	int posicion_maximo;
	
	cout << "Introduzca los números de la secuencia: ";
	cin >> entero;
	
	maximo = minimo = entero;
	contador = posicion_maximo = posicion_minimo = 1;
	
	while(entero >= 0 && entero <= 100){
		cout << "";
		cin >> entero;
		
		contador++;
		
		if (entero < minimo){
			minimo = entero;
			posicion_minimo = contador;
		}
			
		if (entero > maximo){
			maximo = entero;
			posicion_maximo = contador;
		}
	};
	
	cout << "\nLa subsecuencia comienza con " << minimo << " que se encuentra en la posición " << posicion_minimo << "\n";
	cout << "\nLa subsecuencia acaba con " << maximo << " que se encuentra en la posición " << posicion_maximo << "\n";
	
	cout << "\n\n";
	
	system ("pause");
}
