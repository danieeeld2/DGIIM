/*	Programa que transforma las letras minúsculas en mayúsculas
	y las mayúsculas en minúsculas. En caso de que el caracter
	introducido no sea alfabético lo almacenará en una
	variable a parte
*/

#include <iostream>

using namespace std;

int main(){
	char letra_original;
	char letra_convertida;
	bool es_minuscula;
	bool es_mayuscula;
	const int distancia = 'a'-'A';
		
	cout << "Introducir un carácter: " ;
	cin >> letra_original;
	
	es_mayuscula = ( letra_original >= 'A' ) && ( letra_original <= 'Z' ) ;
	es_minuscula = ( letra_original >= 'a' ) && ( letra_original <= 'z' ) ;
	
	if ( es_mayuscula )	
		letra_convertida = letra_original + distancia ;
		
	else{
		if ( es_minuscula )
			letra_convertida = letra_original - distancia ;
		else
			letra_convertida = letra_original ;
	}
	
	cout << "\n\nLa letra original es: " << letra_original ;
	cout << "\n\nLa letra convertida es: " << letra_convertida << "\n\n" ;
		
	system ("pause");
}
			
		
	
	
