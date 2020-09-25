/*	Programa que obliga al usuario a introducir 
	una letra mayúscula, mediante una estructura de bucle,
	para, posteriormente, imprimir su correspondiente minúscula */
	
#include <iostream>

using namespace std;

int main(){
	char mayuscula;
	char minuscula;
	const int DISTANCIA = 'a'-'A';
	
	do{
		cout << "\n\nIntroducir una letra mayúscula: ";
		cin >> mayuscula;
	}while ( mayuscula > 'A' && 'Z' < mayuscula);
	
	minuscula = mayuscula + DISTANCIA;
	
	cout << "\nLa correspondiente minúscula es: " << minuscula;
	
	cout << "\n\n";
	
	system ("pause");
}
