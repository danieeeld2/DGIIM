/*	Programa para calcular el valor que toma una función Gaussiana en un punto x.
	Implementa: La función Gaussiana.
	Necesitas: esperanza, desviación típica y el valor de x
					esp, des, x
	Calcula: El valor que toma la función en x
					img
*/

#include <iostream>	//	Inclusión de los recursos de E/S
#include <cmath>		//	Inclusión de los recursos matemáticos

using namespace std;

int main (){			//Programa principal
	double esp;			//Declaración de variables
	double des;			//La esperanza, la desviación, el punto y el valor que toma la función
	double punto;
	double img;
	const double PI = 3.1415927;	//Declaración de PI como constante
	
	cout << "Introduzca el valor de la media o esperanza: "  ;
	cin >> esp;
	
	cout << "Introduzca el valor de la desviación típica: "  ;
	cin >> des;
	
	cout << "Introduzca el valor del punto (El valor de x): " ;
	cin >> punto;
	
	img = ((1/(des*sqrt(2*PI)))*exp(-1/2*pow(((punto-esp)/des), 2)));
	
	cout << "\nLa función toma el valor: " << img << "\n\n" ;
	
	system ("pause") ;
}
