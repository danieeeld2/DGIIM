/* Implementar un programa que modifique un vector de caracteres eliminando la mayusculas.
 Por ejemplo, si el vector es {’S’,’o’,’Y’,’y’,’O’}, este debe quedarse con {’o’,’y’}.
 Utiliza dos bucles anidados. */

#include<iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de un vector */
    const int LONGITUD_MAXIMA = 10;
    char vector[LONGITUD_MAXIMA];
	
	int componentes_utiles;
	
	cout << "Introducir numero de componentes del vector: ";
    cin >> componentes_utiles;
	
	cout << "Introducir vector: ";
	for (int i = 0 ; i < componentes_utiles ; i++)
		cin >> vector[i];
        // Para espacios en blanco vector[i] = cin.get();
	
    /* Algoritmo:
     Mientras la componente "posicion" no supere al numero de componentes utiles
        Si es una mayuscula,
            desplaza todas las componentes a partir de "posicion" una posicion menos
            decrementa componentes_utiles
     */
    
    int posicion = 0;
    while (posicion <= componentes_utiles ){
        if (vector[posicion] >= 'A' && vector[posicion] <= 'Z' ){
            for (int j = posicion; j < componentes_utiles-1; j++)
                vector[j] = vector[j + 1];
            componentes_utiles--;
        }
        else
            posicion++;
    }

    cout << "\nEl vector queda: ";
	for (int i = 0; i < componentes_utiles; i++)
		cout << vector[i] << " ";
    cout << "\n";
}
