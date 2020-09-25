/*
Programa que blanquea imagenes.
*/

#include <iostream>

using namespace std;
const int MAX_FILAS = 650;
const int MAX_COLUMNAS = 650;

typedef short int color;

void LeerPGM(string &cadena_magica, int &filas, int &columnas, int &M, color pixel[][MAX_COLUMNAS]);
void Contrastar(int M, color pixel[][MAX_COLUMNAS], color salida[][MAX_COLUMNAS], int filas, int columnas);
void EscribirPGM(string cadena_magica, int filas, int columnas, int M, color salida[][MAX_COLUMNAS]);

int main(){
	
	color pixel[MAX_FILAS][MAX_COLUMNAS];
	color salida[MAX_FILAS][MAX_COLUMNAS];
	string cadena_magica;
	int filas = 0, columnas = 0;
	int M = 0;
	
	LeerPGM(cadena_magica, filas, columnas, M, pixel);
	Contrastar(M, pixel, salida, filas, columnas);
	EscribirPGM(cadena_magica, filas, columnas, M, salida);
	
	system("pause");
}

void LeerPGM(string &cadena_magica, int &filas, int &columnas, int &M, color pixel[][MAX_COLUMNAS]){
	cin >> cadena_magica;
	cin >> filas;
	cin >> columnas;
	cin >> M;
	
	for(int i = 0; i < columnas; i++){
		for(int j = 0; j < filas; j++){
			cin >> pixel[j][i];
		}
	}
}

void Contrastar(int M, color pixel[][MAX_COLUMNAS], color salida[][MAX_COLUMNAS], int filas, int columnas){
	for(int i = 0; i < columnas; i++){
		for(int j = 0; j < filas; j++){
			if(pixel[j][i] < 125)
				salida[j][i] = 0;
			else
				salida[j][i] = M;
		}
	}
}

void EscribirPGM(string cadena_magica, int filas, int columnas, int M, color salida[][MAX_COLUMNAS]){
	cout << cadena_magica << "\n";
	cout << filas << " " << columnas << "\n";
	cout << M << "\n";
	
	for(int i = 0; i < columnas; i++){
		for(int j = 0; j < filas; j++){
			cout << salida[j][i] << " ";
		}
		cout << "\n";
	}
}
