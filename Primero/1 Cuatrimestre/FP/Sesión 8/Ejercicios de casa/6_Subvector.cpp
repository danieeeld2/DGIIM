/*	Programa que indica cuantas veces
	está contenido un subvector en otro
	vector y la posición en la que empieza
	la correspondencia */
	
#include <iostream>

using namespace std;

int main(){
	const int LONGITUD = 10;
	int vector[LONGITUD];
	const int LONGITUD2 = 3;
	int subvector[LONGITUD2];
	int posicion2;
	int contador;
	int repeticiones;
	
	posicion2 = 0;
	contador = 0;
	repeticiones = 0;
	
	cout << "Introduce las componentes del vector: ";
	
	for(int i = 0; i != LONGITUD; i++)
		cin >> vector[i];
		
	cout << "\nIntroduce las componentes del subvector: ";
		
	for(int j = 0; j != LONGITUD2; j++)
		cin >> vector[j];
		
	for(int z = 0; z != LONGITUD; z++){
		
		if(subvector[posicion2] == vector[z]){
			contador++;
			posicion2++;
		}
		else{
			contador = 0;
			posicion2 = 0;
		}
		
		if(contador == LONGITUD2){
			contador = 0;
			posicion2 = 0;
			repeticiones++;
		}
	};
	
	cout << "\n\nEl subvector está contenido en el vector " << repeticiones << " veces ";
	
	cout << "\n\n";
	system ("pause");
}
