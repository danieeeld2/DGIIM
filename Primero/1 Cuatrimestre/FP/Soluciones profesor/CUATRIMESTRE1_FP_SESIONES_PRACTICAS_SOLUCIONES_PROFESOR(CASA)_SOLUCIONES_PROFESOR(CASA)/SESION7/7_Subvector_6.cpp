/* Dados dos vectores de enteros, construid un programa que devuelva las veces que el segundo
aparece en el primero. Por ejemplo, para los vectores (1,4,2,3,4,1,2,4,5) y (1,4,2), el programa
devolveria el valor 2. Amplia el programa para que tambien devuelva la posicion donde empiezan
las coincidencias. */

#include <iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de un vector */
	const int LONGITUD_MAXIMA = 10;
    int vector1[LONGITUD_MAXIMA], vector2[LONGITUD_MAXIMA];
    
    int componentes_utiles1, componentes_utiles2;
    int repeticiones = 0;
    /* para almacenar donde comienzan las repeticiones
     la variable repteticiones hace de marcador
     de la longitud util de posiciones */
    int comienzos[LONGITUD_MAXIMA];
	
	bool es_repeticion = false;
	
	cout << "\nIntroducir componentes de los vectores: ";
	cin >> componentes_utiles1 >> componentes_utiles2;
	
	cout << "Introducir primer vector: ";
	for (int i = 0 ; i < componentes_utiles1 ; i++)
		cin >> vector1[i];
	
    cout << "Introducir segundo vector: ";
    for (int i = 0 ; i < componentes_utiles2 ; i++)
		cin >> vector2[i];
	
    /* Algoritmo:
     Mientras la componente i no sea mayor que la diferencia de longitudes
        si el vector2 tiene una copia en vector1 a partir de la componente i
            aumenta repeticiones
            inserta i en el vector comienzos*/
    
    int final = componentes_utiles1 - componentes_utiles2;
    
    for ( int posicion = 0; posicion < final; posicion++ ){
        es_repeticion = true;
            
        for ( int j = 0; j < componentes_utiles2 && es_repeticion; j++)
            if ( vector1[posicion+j] != vector2[j] )
                es_repeticion = false;
            
        if (es_repeticion){
            comienzos[repeticiones] = posicion;
            repeticiones++;
        }
    }
        
    if (repeticiones > 0){
        cout << "\nSe dan " << repeticiones << " repeticiones en las posiciones ";
        for (int i = 0; i<repeticiones; i++)
            cout << comienzos[i] << " ";
        cout << "\n";
    }
    else
        cout << "\nNo hay repeticiones\n";
}
