// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 1 (ejemplo1.cpp)
// Puesta en marcha de dos hebras, con finalización errónea.
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

  // finalización errónea: se destruyen los objetos hebra y acaba
  // la hebra principal, posiblemente antes de que acaben las hebras en ejecución
}
