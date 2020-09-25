/*	Programa para intercambiar
	dos componentes de un vector y
	comprueba si es correcto
*/

#include <iostream>

using namespace std;

int main(){
	int vector1 [4];
	int vector2 [4];
	int intercambiador;
	int respuesta1;
	int respuesta2;
	int contador;
	
	cout << "Introduce las componentes del vector: ";
	
	contador = 0;
	
	for (int i = 0; i!=4; i++)
		cin >> vector1 [i];
		
	for (int j = 0; j!=4; j++){
		vector2 [j] = vector1 [contador];
		contador++;
	};
		
	cout << "\n¿Que componentes desea cambiar? ";
	
	do{
		cout << "\nPrimera componente (0-3): ";
		cin >> respuesta1;
	}while (respuesta1 > 3);
	
	intercambiador = vector2 [respuesta1];
	
	do{
		cout << "\nSegunda componente (0-3): ";
		cin >> respuesta2;
	}while (respuesta2 > 3);
	
	vector2 [respuesta1] = vector2 [respuesta2];
	vector2 [respuesta2] = intercambiador;
	
	cout << "\nVector original: " << "\n";
	
	for (int x = 0; x!=4; x++)
		cout << vector1 [x];
		
	cout << "\nEl nuevo vector es: " << "\n";
	
	for (int y = 0; y!=4; y++)
		cout << vector2 [y];
		
	cout << "\n\n";
	system ("pause");
}
