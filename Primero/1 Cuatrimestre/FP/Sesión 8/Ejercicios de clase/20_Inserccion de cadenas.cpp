/*	Programa que concatena dos cadenas
	de caracteres en una determinada 
	posición */
	
#include <iostream>

using namespace std;

int main(){
	int LONGITUD1 = 20;
	int LONGITUD2 = 20;
	int contador1 = -1;
	int contador2 = -1;
	char cadena1[LONGITUD1];
	char cadena2 [LONGITUD2];
	int posicion_de_concatenacion;
	
	cout << "Introduce una cadena de caracteres: ";
	cout << "\nIntroduce " << LONGITUD1 << " caracteres o 'º' para terminar ";
	for(int i = 0; i != LONGITUD1; i++){
		cin >> cadena1 [i];
		contador1++;
		
		if(cadena1 [i] == 'º')
			i = LONGITUD1 - 1;			
	}
	
	cout << "\nIntroduce otra cadena de caracteres: ";
	cout << "\nIntroduce " << LONGITUD2 << " caracteres o 'º' para terminar ";
	for(int i = 0; i != LONGITUD2; i++){
		cin >> cadena2 [i];
		contador2++;
		
		if(cadena2 [i] == 'º')
			i = LONGITUD2 - 1;			
	}
	
	do{
		cout << "\n¿En que posición quieres concatenar las cadenas? ";
		cout << "Recuerda que tu cadena tiene de longitud " << contador1 << " caracteres ";
		cin >> posicion_de_concatenacion;
	}while(posicion_de_concatenacion >= LONGITUD1);
	
	cout << "\n\nLa cadena concatenada sería: " << "\n\n";
	
	for(int j = 0; j != (contador1 + contador2) ; j++){
		if(j < posicion_de_concatenacion)
			cout << cadena1 [j];
			
		if(j >= posicion_de_concatenacion && j < (posicion_de_concatenacion + contador2))
			cout << cadena2 [j - posicion_de_concatenacion];
			
		if(j >= posicion_de_concatenacion && j >= (posicion_de_concatenacion + contador2))
			cout << cadena1 [j - contador2];
	}
	
	cout << "\n\n";
	system ("pause");
}
	
	
	

