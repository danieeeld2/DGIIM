// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: barrera1_sc.cpp
// Ejemplo de un monitor 'Barrera' simple, con semántica SC
//
// Historial:
// Creado en Julio de 2017
// -----------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

// *****************************************************************************
// clase para monitor Barrera, version 1 (simple) semántica SC

class MBarreraSC
{
   private:
   int                cont,             // contador de hebras en cita
                      num_hebras ;      // número total de hebras
   mutex              cerrojo_monitor ; // cerrojo del monitor
   condition_variable cola ;            // cola de hebras esperando en cita

   public:
   MBarreraSC( const int num_hebras ) ; // constructor
   void cita( int num_hebra );                  // método de cita
} ;
// -----------------------------------------------------------------------------

MBarreraSC::MBarreraSC( int p_num_hebras )
{
   num_hebras = p_num_hebras ;
   cont       = 0 ;
}
// -----------------------------------------------------------------------------

void MBarreraSC::cita( int num_hebra )
{
   unique_lock<mutex> guarda( cerrojo_monitor ); // ganar E.M.
   cont ++ ;
   const int orden = cont ;
   cout << "Llega hebra " << num_hebra << " (" << orden << ")." << endl ;
   if ( cont < num_hebras )
      cola.wait( guarda );
   else
   {
      for( int i = 0 ; i < num_hebras-1 ; i++ )
         cola.notify_one() ;
      cont = 0 ;
   }
   cout << "              Sale hebra " << num_hebra << " (" << orden << ")." << endl ;
}
// -----------------------------------------------------------------------------

void funcion_hebra( MBarreraSC * monitor, int num_hebra )
{
   while( true )
   {  const int ms = aleatorio<5,100>();
      this_thread::sleep_for( chrono::milliseconds(ms) );
      monitor->cita( num_hebra );
   }
}
// *****************************************************************************

int main()
{
   // declarar el número total de hebras
   const int num_hebras = 6 ;

   // crear monitor
   MBarreraSC monitor( num_hebras );

   // crear y lanzar hebras
   thread hebra[num_hebras];
   for( unsigned i = 0 ; i < num_hebras ; i++ )
      hebra[i] = thread( funcion_hebra, &monitor, i );

   // esperar a que terminen las hebras (no pasa nunca)
   for( unsigned i = 0 ; i < num_hebras ; i++ )
      hebra[i].join();
}
