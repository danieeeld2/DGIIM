#include <iostream>

using namespace std;

/**
 *@brief Funcion que, a partir de un vector de enteros, extrae los numeros que son
 *       pares y los que son impares.
 *@param vector_entrada vector de enteros con los datos iniciales
 *@param utiles_entrada longitud de vector_entrada
 *@param vector_pares vector de enteros de salida con los pares de vector_entrada
 *@param utiles_pares longitud de vector_pares
 *@param vector_impares vector de enteros de salida con los impares de vector_entrada
 *@param utiles_impares longitud de vector_impares
 *
 *@post rellena vector_pares y vector_impares con los pares e impares de vector_entrada,
        respectivamente. Cambia utiles_pares y utiles_impares a su longitud.
 */
void ParesImpares (const int vector_entrada[], int utiles_entrada,
                   int vector_pares[], int & utiles_pares,
                   int vector_impares[], int & utiles_impares);

// Funciones de lectura y escritura
void LeerVector (int vector[], int &componentes_utiles);
void MostrarVector (const int vector[], int componentes_utiles);

int main(){
    const int MAXIMA_LONGITUD = 100;
    int vector_entrada[MAXIMA_LONGITUD];
	int vector_pares[MAXIMA_LONGITUD];
	int vector_impares[MAXIMA_LONGITUD];
    int utiles_entrada;
	int utiles_pares = 0;
	int utiles_impares = 0;
	
	LeerVector(vector_entrada, utiles_entrada);
	ParesImpares(vector_entrada, utiles_entrada, vector_pares, utiles_pares, vector_impares, utiles_impares);
    MostrarVector (vector_pares, utiles_pares);
    MostrarVector (vector_impares, utiles_impares);
}

void ParesImpares (const int vector_entrada[], int utiles_entrada,
                   int vector_pares[], int & utiles_pares,
                   int vector_impares[], int & utiles_impares){
    
    for (int i=0; i<utiles_entrada; i++)
        if ( vector_entrada[i] % 2 == 0 ){
            vector_pares[utiles_pares] = vector_entrada[i];
            utiles_pares++;
        }
        else{
            vector_impares[utiles_impares] = vector_entrada[i];
            utiles_impares++;
        }
}

void LeerVector ( int vector[], int & componentes_utiles){
	cout << "Introduce longitud: ";
    cin >> componentes_utiles;
    while ( componentes_utiles <= 0)
        cin >> componentes_utiles;
    
	cout << "Introduce vector:\n";
	for (int i = 0; i < componentes_utiles; i++)
		cin >> vector[i];
}

void MostrarVector (const int vector[], int componentes_utiles){
	for (int i = 0; i < componentes_utiles; i++)
		cout << vector[i] << " ";
    cout << "\n";
}
