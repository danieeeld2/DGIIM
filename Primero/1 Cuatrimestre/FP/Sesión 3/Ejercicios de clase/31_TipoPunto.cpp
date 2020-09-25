/*	Programa que pide el nombre de dos ciudades y sus respectivas 
	coordenadas y, a continuación, crea una nueva ciudad
	cuyo nombre es la concatenación de los dos anteriores
	y sus coordenadas la multiplicación de las dos anteriores
*/

#include <iostream>
#include <cstring>

using namespace std;

struct TipoPunto{
	double abcisa;
	double ordenada;
};

struct TipoCiudad{
	TipoPunto situacion;
	string nombre; 
};

int main(){
	TipoCiudad ciudad1;
	TipoCiudad ciudad2;
	TipoCiudad ciudad3;
	
	
	cout << " Introduzca nombre de la primera ciudad: " ,
	cin >> ciudad1.nombre ;
	cout << "\nIntroduzca nombre de la segunda ciudad: " ;
	cin >> ciudad2.nombre ;
	
	cout << "\nIntroducir abcisa de la primera ciudad: " ;
	cin >> ciudad1.situacion.abcisa ;
	cout << "\nIntroduza ordenada primera ciudad: " ;
	cin >> ciudad1.situacion.ordenada ;
	
	cout << "\nIntroducir abcisa segunda ciudad: " ;
	cin >> ciudad2.situacion.abcisa ;
	cout << "\nIntroducir abcisa segunda ciudad: " ;
	cin >> ciudad2.situacion.ordenada ;
	
	ciudad3.nombre = ciudad1.nombre+ciudad2.nombre ;
	ciudad3.situacion.abcisa = ciudad1.situacion.abcisa*ciudad2.situacion.abcisa ;
	ciudad3.situacion.ordenada = ciudad1.situacion.ordenada*ciudad2.situacion.ordenada ;
	
	cout << "\nEl nombre de la ciudad es: " << ciudad3.nombre ;
	cout << "\nLa abcisa de la nueva ciudad es: " << ciudad3.situacion.abcisa ;
	cout << "\nLa ordenada de la nueva ciudad es: " << ciudad3.situacion.ordenada << "\n\n" ;
	
	system ("pause");	
}
