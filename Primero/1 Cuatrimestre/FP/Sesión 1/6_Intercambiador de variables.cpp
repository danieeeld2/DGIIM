/*	Programa para intercambiar los contenidos de dos variables enteras
	Necesita: Introducir edad de Juan y edad de Pedro
				edad_Pedro y edad_Juan
	Calcula:	Intercambia los contenidos de las variables
*/

#include <iostream>

using namespace std;

int main (){				//Programa principal
	int edad_Pedro;		//Declaración de variables
	int edad_Juan;
	int auxiliar;			//Declaración de variable auxiliar
	
	cout << "Introducir edad de Pedro: " ;
	cin >> edad_Pedro ;
	
	cout << "Introducir edad de Juan: " ;
	cin >> edad_Juan ;
		
	auxiliar = edad_Pedro ;
	edad_Pedro = edad_Juan;
	edad_Juan = auxiliar;
	
	cout << "Ahora la edad de Pedro es: " << edad_Pedro ;
	cout << "   Ahora la edad de Juan es: " << edad_Juan;
	
	system ("pause");
}
