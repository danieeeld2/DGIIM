/*	Programa que indica si un año es bisiesto o no.
	La regla dice que un año es bisiesto si es múltiplo
	de 4, pero no de 100. Los múltipos de 400 si son 
	bisiestos.
*/

#include <iostream>

using namespace std;

int main(){
	int year ;
	bool bisiesto;
	
	cout << "Introduzcaun año: " ;
	cin >> year ;
	
	bisiesto = ( year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		
	if ( bisiesto )
		cout << "\n\nEl año " << year << " es bisiesto. " << "\n\n" ;
	else
		cout << "\n\nEl año " << year << " no es bisiesto. " << "\n\n" ;
		
	system ("pause") ;
}
