/*	Programa que imprime las cifras
	de un entero arbitrario; separadas por
	espacios en blanco */
	
#include <iostream>

using namespace std;

int main(){
	int entero;
	int divisor;
	int cifra;
	int contador;
	
	cout << "Introduzca un entero: ";
	cin >> entero;
	cout << "\n\n";
	
	divisor = 1;
	contador = 0;
	
	while(entero / divisor != 0){
		contador++;
		divisor = divisor * 10;
	};
	
	while (entero / divisor != entero){
		divisor = divisor / 10;
		cifra = (entero / divisor) - (entero / (divisor * 10)*10);
		
		cout << " " << cifra << " ";
	};
	
	cout << "\n\n";
	system ("pause");
}

