/*	Ampliación del programa 
	anterior */
	
#include <iostream>

using namespace std;

int main(){
	const int LONGITUD = 10;
	char vector1 [LONGITUD];
	char vector2 [LONGITUD];
	int posicion_lectura;
	int posicion_escritura;
	bool condicion_escritura;
	
	cout << "Introduce las componentes del vector: ";
	
	for(int i = 0; i!=LONGITUD; i++)
		cin >> vector1 [i];
		
	posicion_lectura = posicion_escritura = 0;
	condicion_escritura = (vector1 [posicion_lectura] < 'A') && (vector1 [posicion_lectura] > 'Z');
	
	while(posicion_lectura != LONGITUD){
		if(condicion_escritura){
			vector2 [posicion_escritura] = vector1 [posicion_lectura];

			posicion_escritura++;
		}
		
		posicion_lectura++;
	};
	
	cout << "\n\nEl vector sin mayúsculas es: " << "\n\n";
	
	for(int j= 0; j!=posicion_escritura; j++)
		cout << vector2 [j];
		
	cout << "\n\n";
	system ("pause");
}
