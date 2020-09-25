/*	Programa en el que incluimos dos variables, edad e ingresos.
	Si la persona es jubilada y cobra menos de 300 euros se le
	aumentará su salario en un 5%
*/

//	Suponemos que las personas se jubilan cuando son mayores de 65

#include <iostream>
#include <cstring>

using namespace std;

struct PERSONA{
	string NOMBRE;
	int edad;
	double ingresos;
};

int main (){
	
	PERSONA persona;
	
	cout << "Introducir nombre de la persona: " ;
	cin >> persona.NOMBRE ;
	
	cout << "\nIntroducir edad de la persona: " ;
	cin >> persona.edad ;
	
	cout << "\nIntroducir ingresos de la persona: " ;
	cin >> persona.ingresos ;
	
	if ( persona.ingresos <= 300 && persona.edad > 65 ){
	
		persona.ingresos = persona.ingresos + ( persona.ingresos * 5.0/100 ) ;
		
		cout << "\nEl nuevo ingreso de " << persona.NOMBRE << " es " << persona.ingresos << "\n\n" ;
   }	
	else
		
		cout << "\nNo es aplicable la subida " << "\n\n" ;
		
	system ("pause");
}
		
	
	
