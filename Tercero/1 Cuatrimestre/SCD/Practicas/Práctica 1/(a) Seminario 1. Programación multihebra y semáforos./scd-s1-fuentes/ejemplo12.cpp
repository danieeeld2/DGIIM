// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 12 (ejemplo12.cpp)
// Uso de un objeto mutex para escritura en el terminal en exclusión mutua
//
// Historial:
// Creado en Mayo de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <future>     // declaracion de {\bf std::thread}, {\bf std::async}, {\bf std::future}
#include <mutex>      // declaracion de std::mutex
using namespace std ; // permite acortar la notación (abc en lugar de std::abc)

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

const int num_hebras = 8 ; // número de hebras

mutex mtx ; // objeto mutex compartido

// función que ejecutan las hebras: (cada una recibe i == índice de la hebra)
void funcion_hebra_m( int i )
{
  int fac = factorial( i+1 );
  mtx.lock() ; // esperar a que el mutex quede libre, entonces adquirirlo
  // sección crítica (escribe en la salida estándar)
  cout << "hebra número " << i << ", factorial(" << i+1 << ") = " << fac << endl;
  mtx.unlock() ; // liberar el mutex, permitir a otras hebras ejecutar S.C
}
int main()
{
  // declarar el array de variables de tipo 'thread'
  thread hebras[num_hebras] ;
  // poner en marcha todas las hebras (cada una de ellas imprime el result.)
  for( int i = 0 ; i < num_hebras ; i++ )
    hebras[i] = thread( funcion_hebra_m, i ) ;
  // esperar a que terminen todas las hebras
  for( int i = 0 ; i < num_hebras ; i++ )
    hebras[i].join() ;
}
