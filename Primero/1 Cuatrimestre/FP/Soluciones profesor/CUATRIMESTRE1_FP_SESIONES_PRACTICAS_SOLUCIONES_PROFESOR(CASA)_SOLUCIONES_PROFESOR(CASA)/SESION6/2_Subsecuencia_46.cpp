
/*
Escribir un programa que lea una secuencia de numeros enteros en el rango de 0
a 100 terminada en un numero mayor que 100 o menor que 0 y encuentre la subsecuencia
de numeros ordenada, de menor a mayor, de mayor longitud. El programa
nos debe decir la posicion donde comienza la subsecuencia y su longitud. Por ejemplo,
ante la entrada siguiente:
23 25 7 40 45 45 73 73 71 4 9 101
el programa nos debe indicar que la mayor subsecuencia empieza en la posicion 3 (en
el 7) y tiene longitud 6 (termina en la segunda aparicion del 73)

*/

#include <iostream>
#include <string>

using namespace std;


int main (){
    
    int numero, actual, anterior, total_numeros;
    int posicion, longitud, maxima_longitud, maxima_posicion;
    const string mensaje = "\nIntroduce un entero en [0,100]:\n";
    
    // Lectura adelantada
    cout << mensaje;
    cin >> numero;
    
    anterior = -1;
    actual = numero;
    posicion = 1;
    longitud = 0;
    total_numeros = 0;
    maxima_longitud = 0;
    maxima_posicion = 0;
    
    
    /*
     Algoritmo:
     Mientras la entrada este en [0,100]
        incrementar el total de nœmeros insertados
        si el numero insertado coincide con el anterior
            incrementar la longitud de la secuencia actual
        si no
            comparar la secuencia que finaliza con la maxima, y actualizar datos si es mayor
            devolver longitud de la secuencia actual a 1
     */
    while ( numero > -1 && numero < 101 ){
        total_numeros++;
        
        if ( actual >= anterior )
            longitud++;
        else{
            if ( longitud > maxima_longitud ){
                maxima_longitud = longitud;
                maxima_posicion = posicion;
            }
            longitud = 1;
            posicion = total_numeros;
        }
        
        cout << mensaje;
        cin >> numero;
        anterior = actual;
        actual = numero;
    }
    cout << "\nLa subsecuencia mas larga empieza en la posicion " << maxima_posicion;
    cout << " y tiene longitud  " << maxima_longitud << "\n";
}
