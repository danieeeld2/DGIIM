/*	Programa que lee tres valores enteros y dice
	si alguno divide al otro */
	
#include <iostream>

using namespace std;
	
int main(){
	int valor1;
	int valor2;
	
	//	Primero se pide resolver el ejercicio mezclando cómputos, entradas y salidas
	
	/*
		
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
		
	*/
		
	/*	Ahora lo hacemos con una solución más adecuada, indicando quien divide a quien
		 y teniendo en cuenta que no se puede dividir entre 0 */
		
	bool division1_2;
	bool division2_1;
	
	cout << "\nIntroduzca el valor entero 1: ";
	cin >> valor1;
	
	cout << "\nIntroduzca valor entero 2: ";
	cin >> valor2;
	
	division1_2 = (valor1 % valor2 == 0);
	division2_1 = (valor2 % valor1 == 0);
	
			
	if ( valor1 == 0 || valor2 == 0 ){
		if ( valor1 == 0 && valor2 == 0  )
			cout << "\n\nLos dos valores son 0. Se trata de una indeterminación ";
		
		if (  valor1 == 0 && valor2 != 0 ){
			cout << "<\n\nSi " << valor1 << " se encuentra en el numerador la división es 0. ";
			cout << "Si está en el denominador no se puede dividir ";
		}
		
		if (  valor1 != 0 && valor2 == 0 ){
			cout << "<\n\nSi " << valor2 << " se encuentra en el numerador la división es 0. ";
			cout << "Si está en el denominador no se puede dividir ";
		}
	}
	else{
		if (division1_2)
			cout<< "\n\n" << valor1 << " divide a " << valor2 << " de forma entera";
			
		if (division2_1)
			cout<< "\n\n" << valor2 << " divide a " << valor1 << " de forma entera";
		}
			
		
	cout << "\n\n";
		
	system ("pause");
}
	
	
	
	
