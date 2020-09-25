/*	Programa que determina si dos valores enteros, los cuales,
	se introducen desde el teclado, se dividen o no de forma
	entera
*/

#include <iostream>

using namespace std;

int main(){
	int valor1;
	int valor2;
	bool division;
	
	cout << "\nIntroduzca el valor entero 1: " ;
	cin >> valor1 ;
	
	cout << "\nIntroduzca valor entero 2: " ;
	cin >> valor2;
	
	division = ( valor1 % valor2 == 0 || valor2 % valor1 == 0 ) ;	// o valor 1/2 es 0 o valor 2/1 es 0
	
	if ( division )
		cout << "\nUno divide al otro de forma entera " << "\n\n" ;	// Si división es true
	else
		cout << "\nNo se dividen de forma entera " << "\n\n" ;		//	Si división es false
		
	system ("pause");
}
	
