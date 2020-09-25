/*	Programa para blanquear
	una imagen */
	
#include<iostream>

using namespace std;

typedef short int color;

int main(){
	const int MAX_FILAS = 650;
	const int MAX_COLUMNAS = 650;
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
		for(int j = 0; j < filas; j++)
			salida[j][i] = (valor_maximo - matriz_pixels[j][i]);
			
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
			
	system("pause");			
}
