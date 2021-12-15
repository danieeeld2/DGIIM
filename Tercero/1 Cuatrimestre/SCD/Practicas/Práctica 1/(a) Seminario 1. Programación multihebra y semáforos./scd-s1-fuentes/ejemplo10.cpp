// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 10 (ejemplo10.cpp)
// Uso de un tipo atómico para incrementos concurrentes de un entero
//
// Historial:
// Creado en Mayo de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>      // incluye la funcionalidad para tipos atómicos
using namespace std ;
using namespace std::chrono ;

const long  num_iters  = 1000000l ;
int         contador_no_atom  ; // contador compartido (no atomico)
atomic<int> contador_atom ;     // contador compartido (atomico)
// (tmb. se puede usar 'atomic_int' en lugar de 'atomic<int>')

void funcion_hebra_no_atom(  )
{ for( long i = 0 ; i < num_iters ; i++ )
      contador_no_atom ++ ; // incremento no atómico de la variable
}
void funcion_hebra_atom(  )
{ for( long i = 0 ; i < num_iters ; i++ )
      contador_atom ++ ; // incremento atómico de la variable
}
int main()
{
  contador_atom = 0 ;
  time_point<steady_clock> inicio_atom  = steady_clock::now() ;
  thread hebra1_atom = thread( funcion_hebra_atom ),
         hebra2_atom = thread( funcion_hebra_atom );
  hebra1_atom.join();
  hebra2_atom.join();
  time_point<steady_clock> fin_atom  = steady_clock::now() ;

  time_point<steady_clock> inicio_no_atom  = steady_clock::now() ;
  contador_no_atom = 0 ;
  thread hebra1_no_atom = thread( funcion_hebra_no_atom ),
         hebra2_no_atom = thread( funcion_hebra_no_atom );
  hebra1_no_atom.join();
  hebra2_no_atom.join();
  time_point<steady_clock> fin_no_atom = steady_clock::now() ;

  duration<float,milli> tiempo_atom    = fin_atom  - inicio_atom ,
                      tiempo_no_atom = fin_no_atom - inicio_no_atom ;

  cout << "valor esperado       : " << 2*num_iters << endl
       << "resultado (atom.)    : " << contador_atom << endl
       << "resultado (no atom.) : " << contador_no_atom << endl
       << "tiempo atom.         : " << tiempo_atom.count() << " milisegundos." << endl
       << "tiempo no atom.      : " << tiempo_no_atom.count() << " millisegundos." << endl ;
}
