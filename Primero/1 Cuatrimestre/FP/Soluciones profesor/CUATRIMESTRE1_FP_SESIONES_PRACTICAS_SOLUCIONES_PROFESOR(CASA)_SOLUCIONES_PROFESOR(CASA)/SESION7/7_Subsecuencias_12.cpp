/* Implementar un programa que calcule el numero de secuencias ascendentes de un vector de
 enteros. Por ejemplo, el vector {2, 4, 1, 1, 7, 2, 1} tiene 4 secuencias que son
 {2, 4}, {1, 1, 7}, {2}, {1}. */

#include<iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de un vector */
    const int LONGITUD_MAXIMA = 10;
    int vector[LONGITUD_MAXIMA];
    
    int componentes_utiles;
    int numero_secuencias_ascendentes = 0;
    
    cout << "\nIntroducir numero componentes (maximo " << LONGITUD_MAXIMA << "): ";
    cin >> componentes_utiles;
	
	cout << "\nIntroduzca el vector: ";
	for(int i = 0 ; i < componentes_utiles ; i++)
		cin >> vector[i];
	
    if ( componentes_utiles > 0)
        numero_secuencias_ascendentes++;
    
    for (int i=1; i<componentes_utiles; i++)
        if ( vector[i] < vector[i-1] )
            numero_secuencias_ascendentes++;
        
	cout << "\nHay " << numero_secuencias_ascendentes << " subsecuencias\n";
}
