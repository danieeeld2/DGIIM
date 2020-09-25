/*	Programa que dice si un cuadrado
	es mágico.
	Se considera cuadrado mágico a una
	matriz cuadrada donde la suma de los 
	elementos de las columnas, de las filas
	y de la diagonal es constante */

#include<iostream>

using namespace std;

const int MAXIMO = 10;
	
bool Es_Magico(int matriz[][], int numero_filas){
	bool es_magico;
	int suma1;
	int suma_fila_columnas_diagonal;
	
	es_magico = true;
	suma_fila_columnas_diagonal = 0;
	suma1 = 0;
	
	for(int i = 0; i != numero_filas; i++)
		suma_fila_columnas_diagonal = suma_fila_columnas_diagonal + matriz[0][i];
	
	for(int i = 1; i != numero_filas && es_magico; i++){	
		for(int j = 0; j != numero_filas; j++)
			suma1 = suma1 + matriz[i][j];
			
		if(suma1 == suma_fila_columnas_diagonal){
			es_magico = true;
			suma1 = 0;
		}
		else
			es_magico = false;
	};
	
	suma1 = 0;
	
	for(int j = 0; j != numero_filas && es_magico; j++){	
		for(int i = 0; i != numero_filas; i++)
			suma1 = suma1 + matriz[i][j];
			
		if(suma1 == suma_fila_columnas_diagonal){
			es_magico = true;
			suma1 = 0;
		}
		else
			es_magico = false;
	};
	
	suma1 = 0;
	
	for(int i = 0; i != numero_filas && es_magico; i++)
		suma1 = suma1 + matriz[i][i];
		
	if(suma1 != suma_fila_columnas_diagonal)
		es_magico = false;
		
	return es_magico;
};

//////////////////////////////////////////////////////////////////

int main(){
	int matriz[MAXIMO][MAXIMO];
	int orden_matriz;
	bool es_magico;
	
	cout << "\nIntroduzca el orden de la matriz: ";
	cin >> orden_matriz;
	
	cout << "\nIntroduce los elementos de la matriz: ";
	for(int i = 0; i != orden_matriz; i++)
		for(int j = 0; j != orden_matriz; j++)
			cin >> matriz[i][j];
			
	es_magico = Es_Magico(matriz, orden_matriz);
	
	if(es_magico)
		cout << "\n\nEs magico ";
	else
		cout << "\n\nNo ";
		
	cout << "\n\n";
	system("pause");
}
		
	
			
		
	
