/* Leed desde teclado dos variables util_filas y util_columnas y leed los datos de una
 matriz de enteros de tamano util_filas x util_columnas. Sobre dicha matriz, se
 pide lo siguiente:
 (a) Calcular la traspuesta de la matriz, almacenando el resultado en otra matriz.
 (b) La posicion de aquel elemento que sea el mayor de entre los minimos de cada fila. Por
 ejemplo, dada la matriz M (3 4),
 9 7 4 5
 2 18 2 12
 7 9 1 5
 el maximo entre 4, 2 y 1 (los minimos de cada fila) es 4 y se encuentra en la posicion (0,
 2).
 (c) Ver si existe un valor MaxiMin, es decir, que sea a la vez, maximo de su fila y minimo
 de su columna.
 (d) Leer los datos de otra matriz y multiplicar ambas matrices (las dimensiones de la segunda
 matriz han de ser compatibles con las de la primera para poder hacer la multiplicacion)
*/

#include <iostream>

using namespace std;

int main(){
    /* Establecemos tamano maximo */
    const int TAMANO_MAXIMO = 10;
    int matriz1[TAMANO_MAXIMO][TAMANO_MAXIMO];
    int matriz2[TAMANO_MAXIMO][TAMANO_MAXIMO];
    int matriz_traspuesta[TAMANO_MAXIMO][TAMANO_MAXIMO];
    int vector_minimos_fila[TAMANO_MAXIMO];
    int producto[TAMANO_MAXIMO][TAMANO_MAXIMO]={0};
    
    int filas_utiles1, filas_utiles2, columnas_utiles1, columnas_utiles2;
    int filas_utiles_traspuesta, columnas_utiles_traspuesta;
    int minimo_fila = 0;
    
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
    
    /* Ejercicio a */
    
    filas_utiles_traspuesta = columnas_utiles1;
    columnas_utiles_traspuesta = filas_utiles1;
    
    for (int i=0; i<filas_utiles_traspuesta; i++)
        for (int j=0; j<columnas_utiles_traspuesta; j++)
            matriz_traspuesta[i][j] = matriz1[j][i];
    
    for (int i=0; i<filas_utiles_traspuesta; i++){
        for (int j=0; j<columnas_utiles_traspuesta; j++)
            cout << matriz_traspuesta[i][j] << " ";
        cout << "\n";
    }
    
    /* Ejercicio b */
    
    for (int i=0; i<filas_utiles1; i++){
        minimo_fila = 0;
        for (int j=0; j<columnas_utiles1; j++)
            if ( matriz1[i][j] < matriz1[i][minimo_fila] )
                minimo_fila = j;
        vector_minimos_fila[i] = minimo_fila;
    }
    
    int maximo_minimos = 0;
    
    for (int i=1; i<filas_utiles1; i++)
        if ( matriz1[i][vector_minimos_fila[i]] > matriz1[maximo_minimos][vector_minimos_fila[maximo_minimos]] )
            maximo_minimos = i;
    
    cout << "\El maximo de los minimos (fila) en la posicion " << maximo_minimos << " " << vector_minimos_fila[maximo_minimos] << "\n";
            
        
    /* Ejercicio c */
    
    // Igual al anterior
	


    /* Ejercicio d */
    
    int filas_utiles_producto = filas_utiles1;
    int columnas_utiles_producto = columnas_utiles2;
    
    if ( columnas_utiles1 == filas_utiles2 )
        for (int i=0; i<filas_utiles_producto; i++)
            for (int j=0; j<columnas_utiles_producto; j++)
                for (int k=0; k<columnas_utiles1; k++)
                    producto[i][j] = producto[i][j] + matriz1[i][k] * matriz2[k][j];
                
    for ( int i=0; i<filas_utiles_producto; i++){
        for (int j=0; j<columnas_utiles_producto; j++)
            cout << producto[i][j] << " ";
        cout << "\n";
    }
        
}
