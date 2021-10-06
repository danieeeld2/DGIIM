// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 4 (ejemplo4.cpp)
// Obtención de resultados mediante parámetros de salida (referencias)
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <future>     // declaracion de {\bf std::thread}, {\bf std::async}, {\bf std::future}
using namespace std ; // permite acortar la notación (abc en lugar de std::abc)

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

// función que ejecutan las hebras
void funcion_hebra( int n, long & resultado) { resultado= factorial(n); }

int main()
{
 long resultado1, resultado2 ; // variables (locales) con los resultados

 // iniciar las hebras (los parámetros por referencia se ponen con 'ref')
 thread hebra1( funcion_hebra, 5,  ref(resultado1) ), // calcula fact.(5) en result.1
        hebra2( funcion_hebra, 10, ref(resultado2) ); // calcula fact.(10) en result.2

 // esperar a que terminen las hebras, y escriban en resultado1 y resultado2
 hebra1.join() ; hebra2.join() ;

 // imprimir los resultads:
 cout << "factorial(5)  == " << resultado1 << endl
      << "factorial(10) == " << resultado2 << endl ;
}
