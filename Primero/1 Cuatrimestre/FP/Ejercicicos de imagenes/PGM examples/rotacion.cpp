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
	int posicion1, posicion2;
	color matriz_pixels[MAX_FILAS][MAX_COLUMNAS];
	color salida[MAX_COLUMNAS][MAX_FILAS];
	
	cin >> cadena_magica;
	cin >> filas;
	cin >> columnas;
	cin >> valor_maximo;
	
	for(int i = 0; i < columnas; i++)
		for(int j = 0; j < filas; j++)
			cin >> matriz_pixels[j][i];
			
	posicion1 = 0;
	posicion2 = 0;
			
	for(int j = filas; j!=0; j--){
		for(int i = 0; i!= columnas; i++){
			salida[posicion1][posicion2] = matriz_pixels[j][i];
			posicion1++;
		};
		posicion1 = 0;
		posicion2++;
	};
				
			
	cout << cadena_magica;
	cout << "\n";
	cout << filas << " " << columnas;
	cout << "\n";
	cout << valor_maximo;
	cout << "\n";
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++)
			cout << salida[j][i] << " ";
		
		cout << "\n";
	};
			
	system("pause");			
}
