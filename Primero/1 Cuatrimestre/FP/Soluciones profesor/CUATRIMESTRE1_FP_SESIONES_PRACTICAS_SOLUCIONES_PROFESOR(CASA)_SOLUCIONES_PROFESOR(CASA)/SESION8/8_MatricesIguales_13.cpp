/* Construir un programa para comprobar si dos matrices son iguales */

#include<iostream>

using namespace std;

int main(){
    /* Establecemos tamano maximo */
    const int TAMANO_MAXIMO = 10;
    int matriz1[TAMANO_MAXIMO][TAMANO_MAXIMO];
    int matriz2[TAMANO_MAXIMO][TAMANO_MAXIMO];
    
    int filas_utiles1, filas_utiles2, columnas_utiles1, columnas_utiles2;
    bool iguales = true;
    
    cout << "\nIntroduce numero filas y columnas de la primera matriz: ";
    cin >> filas_utiles1 >> columnas_utiles1;
    
    cout << "\nIntroduce numero filas y columnas de la segunda matriz: ";
    cin >> filas_utiles2 >> columnas_utiles2;
    
    cout << "\nIntroduce matriz 1: ";
    for (int i=0; i<filas_utiles1; i++)
        for (int j=0; j<columnas_utiles1; j++)
            cin >> matriz1[i][j];
    
    cout << "\nIntroduce matriz2: ";
    for (int i=0; i<filas_utiles2; i++)
        for (int j=0; j<columnas_utiles2; j++)
            cin >> matriz2[i][j];
    
	if ( filas_utiles1 != filas_utiles2 || columnas_utiles1 != columnas_utiles2 )
        iguales = false;
    else
        for (int i=0; i<filas_utiles1 && iguales; i++)
            for (int j=0; j<columnas_utiles1 && iguales; j++)
                if (matriz1[i][j] != matriz2[i][j] )
                    iguales = false;
    
	if(iguales)
		cout << "\nSon iguales";
	else
		cout << "\nSon distintas";
}
