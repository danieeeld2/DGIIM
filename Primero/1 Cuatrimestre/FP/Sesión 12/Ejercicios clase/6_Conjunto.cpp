#include<iostream>

using namespace std;

const int MAX = 10;

int SubCadena(int vector[], int suma, int longitud){
	int suma_subcadena;
	int posicion;
	
	for(int i = 0; i != longitud && suma_subcadena != suma; i++){
		suma_subcadena = 0;
		
		for(int j = i; j != longitud && suma_subcadena != suma; j++){
			suma_subcadena = suma_subcadena + vector[j];
		}
		
		posicion = i;
	}
	
	if(suma_subcadena != suma)
		posicion = -1;
		
	return posicion;
}

int main(){
	int vector[MAX] = {4, 1, 3, 9, 2};
	int suma = 12;
	int longitud = 5;
	int posicion;
	
	posicion = SubCadena(vector, suma, longitud);
	
	cout << "\n\n" << posicion << "\n\n";
}
	
