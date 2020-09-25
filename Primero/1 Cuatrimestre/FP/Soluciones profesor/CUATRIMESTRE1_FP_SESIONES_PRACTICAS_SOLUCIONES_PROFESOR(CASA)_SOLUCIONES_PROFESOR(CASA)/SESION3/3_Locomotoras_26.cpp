/*
 Calcular la distancia que recorren las locomotoras antes del choque
 */

#include <iostream>

using namespace std;

int main(){
	int distancia, velocidad1, velocidad2;
	double tiempo, distancia1, distancia2;
	
	cout << "\nIntroduca la distancia que separa a las dos locomotoras en m: " ;
	cin >> distancia ;
	cout << "\nIntroduzca la velocidad de la primera locomotora en m/s: " ;
	cin >> velocidad1 ;
	cout << "\nIntroduzca la velocidad de la segunda locomotora en m/s: " ;
	cin >> velocidad2 ;
	
	tiempo = (double) distancia / (velocidad1 + velocidad2) ;
    // casting a double para no hacer división entera
    // prodiamos considerar la velocidad y la distancia tambien double
    // y entonces no sería necesario

    distancia1 = tiempo * velocidad1 ;
	distancia2 = tiempo * velocidad2 ;
	
	cout << "\nLa distancia que recorre la primera locomotora: " << distancia1 << "m" ;
	cout << "\nLa distancia que recorre la segunda locomotora: " << distancia2 << "m\n" ;
}
