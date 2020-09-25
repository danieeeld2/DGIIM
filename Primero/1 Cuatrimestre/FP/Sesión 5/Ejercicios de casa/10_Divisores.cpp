/*	Programa que lee un entero e indica todos los divisores 
	del mismo */
	
#include <iostream>

using namespace std;

int main(){
	int entero;
	int divisor;
	
	cout << "Introduzca un entero: ";
	cin >> entero;
	
	if ( entero > 0 ){
		divisor = 1;
			
		do{
			if ( entero % divisor == 0 )
				cout << "\n" << divisor << " es divisor de " << entero;
		
			divisor++;
		}while ( divisor < entero );
	}
	
	if ( entero < 0){
		divisor = -1;
		
		do{
			if ( entero % divisor == 0 )
				cout << "\n" << divisor << " es divisor de " << entero;
			
			divisor = divisor - 1;
		}while ( entero < divisor );
	}
	
	cout << "\n\n";
	
	system ("pause");
}
