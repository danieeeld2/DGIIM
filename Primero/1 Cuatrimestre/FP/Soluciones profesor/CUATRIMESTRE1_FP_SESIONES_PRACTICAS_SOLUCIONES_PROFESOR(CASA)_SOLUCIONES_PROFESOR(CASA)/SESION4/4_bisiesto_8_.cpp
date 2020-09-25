/*
Cread un programa que acepte el numero de un a–o e indique si es bisiesto o no.
Un a–o es bisiesto si es multiplo de cuatro, pero no de cien. Excepcion a la regla
anterior son los multiplos de cuatrocientos que siempre son bisiestos. Son bisiestos:
1600,1996, 2000, 2004. No son bisiestos: 1700, 1800, 1900, 1998, 2002.
*/

#include <iostream>
using namespace std;

int main(){
    bool es_bisiesto;
    unsigned int anio;

	cout << "Introduzca un a–o ";
	cin >> anio;

    // almacenamos en una variable la condicion
	es_bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);

	if (es_bisiesto)
		cout << "\nEl a–o es bisiesto";
	else
		cout << "\nEl a–o no es bisiesto";

    cout << "\n\n";
}
