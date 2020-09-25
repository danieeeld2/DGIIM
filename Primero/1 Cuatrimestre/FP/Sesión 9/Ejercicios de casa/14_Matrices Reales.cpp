/*	Programa que suma los elementos
	de una fila o columna de una 
	matriz de dimensiones mxn */
	
#include<iostream>

using namespace std;

int main(){
	const int LONGITUD_M = 3;
	const int LONGITUD_N = 3;
	int matriz [LONGITUD_M][LONGITUD_N];
	int fila;
	int columna;
	int suma;
	
	cout << "Introduzca los datos de la matriz: ";
	
	for(int z = 0; z != LONGITUD_N; z++)
		for(int i = 0; i != LONGITUD_M; i++)
			cin >> matriz [i][z];
			
	cout << "\n\nElige la columna que quieres sumar: ";
	cin >> columna;
	
	suma = 0;
	
	for(int i = 0; i != LONGITUD_N; i++)
		suma = suma + matriz[columna][i];
		
	cout << "\nLa suma de los elementos de la columna " << columna << " es " << suma;
	
	cout << "\n\nElige la fila que quieres sumar: ";
	cin >> fila;
	
	suma = 0;
	
	for(int i = 0; i != LONGITUD_M; i++)
		suma = suma + matriz[i][fila];
		
	cout << "\nLa suma de los elementos de la fila " << fila << " es " << suma;
	
	cout << "\n\n";
	system ("pause");
}
