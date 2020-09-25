/*
Contraste, versión de Sergio usando la base de Danipollas.
*/
	
#include<iostream>

using namespace std;

typedef short int color;
const int MAX_FILAS = 650;
const int MAX_COLUMNAS = 650;

void ImprimirImagen(string cadena_magica, int filas, int columnas, int valor_maximo, color salida[][MAX_FILAS]);

int main(){
	string cadena_magica;
	int filas;
	int columnas;
	int valor_maximo;
	color matriz_pixels[MAX_FILAS][MAX_COLUMNAS];
	color salida[MAX_FILAS][MAX_COLUMNAS];
	
	cin >> cadena_magica;
	cin >> filas;
	cin >> columnas;
	cin >> valor_maximo;
	
	for(int i = 0; i < columnas; i++)
		for(int j = 0; j < filas; j++)
			cin >> matriz_pixels[j][i];

			
	for(int i = 0; i < columnas; i++)
		for(int j = 0; j < filas; j++){
			if(matriz_pixels[j][i] < 125)
				salida[j][i] = 0;
			else
				salida[j][i] = 255;
		};
			
	 ImprimirImagen(cadena_magica, filas, columnas, valor_maximo, salida);
			
	system("pause");			
}

void ImprimirImagen(string cadena_magica, int filas, int columnas, int valor_maximo, color salida[][MAX_FILAS]){
	cout << cadena_magica;
	cout << "\n";
	cout << filas << " " << columnas;
	cout << "\n";
	cout << valor_maximo;
	cout << "\n";
	for(int i = 0; i < columnas; i++){
		for(int j = 0; j < filas; j++)
			cout << salida[j][i] << " ";
		
		cout << "\n";
	};
}

