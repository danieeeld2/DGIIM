/* Realizar un programa que tenga como entrada una matriz de reales y produzca como salida
un vector con la suma de los elementos de cada fila. Realizar un programa que tenga como
entrada una matriz de reales y produzca como salida un vector con la suma de los elementos
de cada columna. */

#include<iostream>

using namespace std;

int main(){
    /* Establecemos tamano maximo */
    const int TAMANO_MAXIMO = 10;
    int matriz[TAMANO_MAXIMO][TAMANO_MAXIMO];
    int vector_suma_filas[TAMANO_MAXIMO];
    int vector_suma_columnas[TAMANO_MAXIMO];
    
    int filas_utiles, columnas_utiles, componentes_utiles_sumafilas, componentes_utiles_sumacolumnas;
    int suma = 0;
    
    cout << "\nIntroduce numero filas y columnas de la matriz: ";
    cin >> filas_utiles >> columnas_utiles;
    
    componentes_utiles_sumacolumnas = columnas_utiles;
    componentes_utiles_sumafilas = filas_utiles;
    
    cout << "\nIntroduce matriz: ";
    for (int i=0; i<filas_utiles; i++)
        for (int j=0; j<columnas_utiles; j++)
            cin >> matriz[i][j];
    
    for (int i=0; i<filas_utiles; i++){
        suma = 0;
        for (int j=0; j<columnas_utiles; j++)
            suma = suma + matriz[i][j];
        vector_suma_filas[i] = suma;
    }
    
    for (int i=0; i<columnas_utiles; i++){
        suma = 0;
        for (int j=0; j<filas_utiles; j++)
            suma = suma + matriz[j][i];
        vector_suma_columnas[i] = suma;
    }
    
	cout << "\nLa suma de las filas es: ";
	for (int i=0; i<componentes_utiles_sumafilas; i++)
		cout << vector_suma_filas[i] << " ";
	
	cout << "\nLa suma de las columnas es: ";
	for (int i=0; i<componentes_utiles_sumacolumnas; i++)
		cout << vector_suma_columnas[i] << " ";
    
    cout << "\n";
}
