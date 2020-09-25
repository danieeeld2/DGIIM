/* Dos numeros a y b se dice que son amigos si la suma de los divisores de a (salvo el mismo)
 coincide con b y viceversa. Implementa una funcion que determine si dos numeros naturales
 son amigos. Diseña un programa que tenga como entrada dos numeros naturales y que muestre
 en la pantalla todas las parejas de numeros amigos que existan en dicho intervalo. */

#include <iostream>

using namespace std;

/* Funcion amigos
 * @brief Determina si dos enteros son amigos
 * @pre Los numeros deben ser positivos
 * @param entero1 y entero2 son los enteros a considerar
 * @return true si son amigos, false si no
 */
bool amigos (int entero1, int entero2);

int main(){
    int primer_entero, segundo_entero;
    
    // Se debe comprobar que se introducen correctamente...
    cout << "\nIntroduce enteros (el primero menor que el segundo): ";
    cin >> primer_entero >> segundo_entero;
    
    for (int candidato1 = primer_entero; candidato1 <= segundo_entero; candidato1++)
        for (int candidato2 = candidato1; candidato2 <= segundo_entero; candidato2++)
            if ( amigos(candidato1,candidato2) )
                cout << "(" << candidato1 << ", " << candidato2 << ")" << " ";
}

bool amigos (int entero1, int entero2){
    int suma1 = 0, suma2 = 0;
    int divisor_maximo1 = entero1 / 2;
    int divisor_maximo2 = entero2 / 2;
    bool amigos;
    
    /* Algoritmo
     Calcular la suma de los divisores propios del primer entero
     Calcular la suma de los divisores propios del segundo entero
     Devolver true si las suma de los divisores de uno coincide con el otro, y viceversa.
     */
    for (int i=1; i <= divisor_maximo1; i++)
        if ( entero1 % i == 0 )
            suma1 = suma1 + i;
    
    for (int i=1; i <= divisor_maximo2; i++)
        if ( entero2 % i == 0 )
            suma2 = suma2 + i;
    
    amigos = (suma2 == entero1) && (suma1 == entero2);

    return amigos;
}

