// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 7 (ejemplo7.cpp)
// Creación de hebras idénticas con distintos parámetros.
// (usando async y un vector de futuros)
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <future>     // declaracion de {\bf std::thread}, {\bf std::async}, {\bf std::future}
using namespace std ; // permite acortar la notación (abc en lugar de std::abc)

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

const int num_hebras = 8 ; // número de hebras

int main()
{
  // declarar el array de variables de tipo 'future'
  future<long> futuros[num_hebras] ;

  // poner en marcha todas las hebras y obtener los futuros
  for( int i = 0 ; i < num_hebras ; i++ )
    futuros[i] = async( launch::async, factorial, i+1 ) ;

  // esperar a que acabe cada hebra e imprimir el resultado
  for( int i = 0 ; i < num_hebras ; i++ )
     cout << "factorial(" << i+1 << ") = " << futuros[i].get() << endl ;
}
