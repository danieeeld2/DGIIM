/*	Módulo que divide un vector de 
	enteros en uno de números pares
	y otro de impares */
	
#include<iostream>

using namespace std;

void Entrada_Datos(int vector[], int &longitud);
void ParesImpares(const int vector[], int longitud, int pares[],
		int &longitud_pares, int impares[], int &longitud_impares);
void Salida(int vector[], int longitud);

///////////////////////////////////////////////////

int main(){
	const int Longitud_Maxima = 50;
	int longitud_util;
	int vector[Longitud_Maxima];
	int pares[Longitud_Maxima];
	int impares[Longitud_Maxima];
	int longitud_pares;
	int longitud_impares;
	
	Entrada_Datos(vector, longitud_util);
	ParesImpares(vector, longitud_util, pares, longitud_pares, impares, longitud_impares);
	
	cout << "\nLos pares son: " << "\n";
	Salida(pares, longitud_pares);
	
	cout << "\nLos impares son: " << "\n";
	Salida(impares, longitud_impares);
	
	cout << "\n\n";
	system("pause");
};

/////////////////////////////////////////////////////////////

/*	Funcion para introducir los detos del vector */

void Entrada_Datos(int vector[], int &longitud){
	cout << "\nIntroduce la longitud del vector: ";
	do{
		cin >> longitud;
	}while(longitud < 0);
	
	cout << "\nIntroduce las componentes del vector: ";
	for(int i = 0; i != longitud; i++)
		cin >> vector[i];
};

/////////////////////////////////////////////////////////////

/*	Función que separa los pares y los impares y los
	introduce en dos subvectores independientes*/

void ParesImpares(const int vector[], int longitud, int pares[],
		int &longitud_pares, int impares[], int &longitud_impares){
			
	longitud_pares = 0;
	longitud_impares = 0;
	
	for(int i = 0; i != longitud; i++){
		if(vector[i] % 2 == 0){
			pares[longitud_pares] = vector[i];
			longitud_pares++;
		}
		else{
			impares[longitud_impares] = vector[i];
			longitud_impares++;
		}
	}
};

/////////////////////////////////////////////////////////////////

/*	Función para no repetir código en la salida por pantallaç
	del vector */

void Salida(int vector[], int longitud){
	for(int i = 0; i != longitud; i++)
		cout << vector[i] << ", ";
};
	
