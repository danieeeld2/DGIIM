/*	Programa que calcula el número
	de seuencias ascendentes de un vector */
	
#include <iostream>

using namespace std;

int main(){
	const int LONGITUD = 20;
	int vector [LONGITUD];
	int comparador;
	int contador;
	
	cout << "Introduce las componentes del vector: " << "\n";
	
	for(int i = 0; i!=LONGITUD; i++)
		cin >> vector [i];
		
	cout << "\n\n";
		
	contador = 0;
	
	for(int z = 0; z!=LONGITUD; z++){
		
		if (z == 0){
			comparador = vector [z];
			cout << vector [z] << " ";
		}
		
		if (z != 0){		
			if (comparador < vector[z]){
				comparador = vector [z];
				cout << vector [z] << " ";
			}
		
			if (comparador > vector [z]){
				contador++;
				cout << "\n\n";
				cout << vector [z] << " ";
				comparador = vector [z];
			}
		}
	};
	
	contador++;
	
	cout << "\n\nEn total hay " << contador << " secuencias acendentes ";
	
	cout << "\n\n";
	system ("pause");
}
