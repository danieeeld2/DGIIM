// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 2 (ejemplo2.cpp)
// Puesta en marcha de dos hebras, con finalización correcta.
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------


#include <iostream>
#include <thread>     // declaraciones del tipo {\bf std::thread}
using namespace std ; // permite acortar la notación

void funcion_hebra_1(  ) // función que va a ejecutar la hebra primera
{ for( unsigned long i = 0 ; i < 5000 ; i++ )
     cout << "hebra 1, i == " << i << endl << flush ;
}
void funcion_hebra_2(  )  // función que va a ejecutar la hebra segunda
{  for( unsigned long i = 0 ; i < 5000 ; i++ )
      cout << "                hebra 2, i == " << i << endl << flush ;
}
int main()
{
  thread hebra1( funcion_hebra_1 ), // crear {\bf hebra1} ejecutando {\bf funcion\_hebra\_1}
         hebra2( funcion_hebra_2 ); // crear {\bf hebra2} ejecutando {\bf funcion\_hebra\_2}


  hebra1.join(); // la hebra principal espera a que {\bf hebra1} termine
  hebra2.join(); // la hebra principal espera a que {\bf hebra2} termine
}
