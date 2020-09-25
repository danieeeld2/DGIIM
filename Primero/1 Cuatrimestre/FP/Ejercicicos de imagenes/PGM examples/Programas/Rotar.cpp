/*
Programa que rota imagenes 90º a la derecha.
*/

#include <iostream>

using namespace std;
const int MAX_FILAS = 650;
const int MAX_COLUMNAS = 650;

typedef short int color;

void LeerPGM(string &cadena_magica, int &filas, int &columnas, int &M, color pixel[][MAX_COLUMNAS]);
void Rotar(int M, color pixel[][MAX_COLUMNAS], color salida[][MAX_COLUMNAS], int &filas, int &columnas);
void EscribirPGM(string cadena_magica, int filas, int columnas, int M, color salida[][MAX_COLUMNAS]);

int main(){
	
	color pixel[MAX_FILAS][MAX_COLUMNAS];
	color salida[MAX_FILAS][MAX_COLUMNAS];
	string cadena_magica;
	int filas = 0, columnas = 0;
	int M = 0;
	
	LeerPGM(cadena_magica, filas, columnas, M, pixel);
	Rotar(M, pixel, salida, filas, columnas);
	EscribirPGM(cadena_magica, filas, columnas, M, salida);
	
	system("pause");
}

void LeerPGM(string &cadena_magica, int &filas, int &columnas, int &M, color pixel[][MAX_COLUMNAS]){
	cin >> cadena_magica;
	cin >> columnas;
	cin >> filas;
	cin >> M;
	
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			cin >> pixel[i][j];
		}
	}
}

void Rotar(int M, color pixel[][MAX_COLUMNAS], color salida[][MAX_COLUMNAS], int &filas, int &columnas){
	int aux = 0;
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			salida[j][filas -1 - i] = pixel[i][j];
		}
	}
	aux = filas;
	filas = columnas;
	columnas = aux;
}

void EscribirPGM(string cadena_magica, int filas, int columnas, int M, color salida[][MAX_COLUMNAS]){
	cout << cadena_magica << "\n";
	cout << columnas << " " << filas << "\n";
	cout << M << "\n";
	
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			cout << salida[i][j] << " ";
		}
		cout << "\n";
	}
}
