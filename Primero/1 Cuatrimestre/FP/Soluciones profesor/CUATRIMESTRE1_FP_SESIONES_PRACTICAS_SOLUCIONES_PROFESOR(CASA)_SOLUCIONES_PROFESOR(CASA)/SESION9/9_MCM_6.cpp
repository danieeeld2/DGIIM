/* Escribir en C++ un modulo int MCM(int a, int b), que devuelva el Minimo Comun
 Multiplo de a y b.
 */

#include<iostream>

using namespace std;

/**
 *@brief Funcion que calcula el minimo comun multiplo de dos enteros
 *@param a primer entero
 *@param b segundo entero
 *@pre por simplicidad, los enteros deben ser positivos
 *@retval devuelve cero si no son positivos, el mcm si los dos son positivos
 */
int MCM(int a, int b);

int main(){
    int entero1, entero2, mcm;
    
    cout << "\nIntrodir enteros positivos: ";
    cin >> entero1 >> entero2;
    
    mcm = MCM(entero1, entero2);
    
    cout << "\nMCM: " << mcm << "\n";
}

int MCM(int entero1, int entero2){
    int mcm = 0;
    
    /* Algoritmo:
     recorre los enteros de forma creciente hasta encontrar un multiplo comun
     */
    if ( entero1>0 && entero2>0 ){
        mcm++;
        while( mcm % entero1 != 0 || mcm % entero2 != 0)
            mcm++;
    }
    
    return mcm;
}
