// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 3 (ejemplo3.cpp)
// Obtención de resultados mediante variables globales
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <future>     // declaracion de {\bf std::thread}, {\bf std::async}, {\bf std::future}
using namespace std ; // permite acortar la notación (abc en lugar de std::abc)

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

// variables globales donde se escriben los resultados
long resultado1, resultado2 ;

// funciones que ejecutan las hebras
void funcion_hebra_1( int n ) { resultado1 = factorial( n ) ; }
void funcion_hebra_2( int n ) { resultado2 = factorial( n ) ; }

int main()
{
  // iniciar las hebras
  thread hebra1( funcion_hebra_1, 5  ), // calcula factorial(5) en resultado1
         hebra2( funcion_hebra_2, 10 ); // calcula factorial(10) en resultado2

  // esperar a que terminen las hebras,
  hebra1.join() ; hebra2.join() ;

  // imprimir los resultads:
  cout << "factorial(5)  == " << resultado1 << endl
       << "factorial(10) == " << resultado2 << endl ;
}
