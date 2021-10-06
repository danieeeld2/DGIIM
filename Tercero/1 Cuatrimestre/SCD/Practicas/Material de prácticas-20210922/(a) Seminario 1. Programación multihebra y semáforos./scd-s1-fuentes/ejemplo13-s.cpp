// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 13 (ejemplo13-s.cpp)
// Solución con semáforos al problema del productor-consumidor
//
// Historial:
// Creado en Mayo de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> 
#include "scd.h" // incluye tipo 'Semaphore', entre otros

using namespace std ; // permite acortar la notación ('abc' en lugar de 'std::abc')
using namespace scd ; // permite usar 'Semaphore' en lugar de 'scd::Semaphore'

// constantes y variables globales (compartidas)
const int num_iter = 10000 ;   // numero de iteraciones
int       valor_compartido ;   // valor para escribir o leer
// semáforos
Semaphore puede_escribir = 1 , // 1 si no hay valor pendiente de leer
          puede_leer     = 0 ; // 1 si hay valor pendiente de leer
// contador usado para ir produciendo los enteros en secuencia
int contador = 0 ;

// -----------------------------------------------------------------------------
// funcion que produce un valor (produce los valores en secuencia)
int producir_valor()
{
  contador++ ;
  cout << "producido: " << contador << endl << flush ;
  return contador ;
}
// -----------------------------------------------------------------------------
// función que consume un valor (simplemente lo imprime)
void consumir_valor( int valor )
{
  cout << "                    consumido: " << valor << endl  ;
}

// -----------------------------------------------------------------------------
// función que ejecuta la hebra productora (escribe la variable)
// (escribe los valores desde 1 hasta 'num_iters', ambos incluidos)
void funcion_hebra_productora(  )
{
   for( unsigned long i = 0 ; i < num_iter ; i++ )
   {
      int valor_producido = producir_valor(); // generar valor
      sem_wait( puede_escribir ) ;
      valor_compartido = valor_producido ; // escribe el valor
      cout << "escrito: " << valor_producido << endl ;
      sem_signal( puede_leer ) ;
   }
}

// -----------------------------------------------------------------------------
// función que ejecuta la hebra consumidora (lee la variable)
// (lee los valores desde 1 hasta 'num_iters', ambos incluidos)
void funcion_hebra_consumidora(  )
{
   for( unsigned long i = 0 ; i < num_iter ; i++ )
   {
      sem_wait( puede_leer ) ;
      int valor_leido = valor_compartido ; // lee el valor generado
      cout << "                    leído: " << valor_leido << endl  ;
      sem_signal( puede_escribir ) ;
      consumir_valor( valor_leido );
   }
}
// -----------------------------------------------------------------------------
// hebra principal (pone las otras dos en marcha)
int main()
{
  // crear y poner en marcha las dos hebras
  thread hebra_productora( funcion_hebra_productora ),
         hebra_consumidora( funcion_hebra_consumidora );

  // esperar a que terminen todas las hebras
  hebra_productora.join();
  hebra_consumidora.join();
}
