/*	Programa que dado una cadena de
	caracteres; devuelva la subcadena
	comprendidas ente ñas posiciones 'x' e 'y'
	incluidas */
	
#include <iostream>
#include <cstring>

using namespace std;

int main(){
	const int LONGITUD_CADENA = 20;
	char cadena_principal[LONGITUD_CADENA];
	int posicion_inicio;
	int posicion_final;
	int contador = 0;
	
	cout << "Introduce una cadena de caracteres: ";
	cout << "(Para finalizar introduzca 'º' o introduzca " << LONGITUD_CADENA << " caracteres) ";
	cout << "\n";
	
	for(int i = 0; i != LONGITUD_CADENA; i++){
		cin >> cadena_principal [i];
		contador++;
		
		if (cadena_principal [i] == 'º')
			i = 19;
	}
		
	cout << "\n\nIntroduzca la posición en la que empieza la subcadena: ";
	cin >> posicion_inicio;
	cout << "\n\nIntroduzca la posición en la que termina la subcadena: ";
	cin >> posicion_final;
	
	cout << "\n\nLa subcadena sería: " << "\n" ;
	
	if (posicion_final > contador)
		cout << "\nCUIDADO: No has introducido tantos carácteres ";
	else{	
		for(int j = posicion_inicio; j != posicion_final + 1; j++)		
			cout << cadena_principal[j];
	}	
		
	cout << "\n\n";
	system ("pause");
}
