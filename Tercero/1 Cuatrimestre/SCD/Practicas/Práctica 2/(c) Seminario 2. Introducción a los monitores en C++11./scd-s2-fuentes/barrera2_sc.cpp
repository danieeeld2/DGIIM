// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: barrera2_sc.cpp
// Ejemplo de un monitor 'Barrera' parcial, con semántica SC
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
// clase para monitor Barrera, version 2,  semántica SC

class MBarreraParSC
{
   private:
   int                cont,             // contador de hebras en cita
                      num_hebras_cita ;  // número total de hebras en cita
   mutex              cerrojo_monitor ; // cerrojo del monitor
   condition_variable cola ;            // cola de hebras esperando en cita

   public:
   MBarreraParSC( const int num_hebras ) ; // constructor
   void cita( int num_hebra );                  // método de cita
} ;
// -----------------------------------------------------------------------------

MBarreraParSC::MBarreraParSC( int p_num_hebras_cita )
{
   num_hebras_cita = p_num_hebras_cita ;
   cont            = 0 ;
}
// -----------------------------------------------------------------------------

void MBarreraParSC::cita( int num_hebra )
{
   unique_lock<mutex> guarda( cerrojo_monitor ); // ganar E.M.
   cont ++ ;
   const int orden = cont ;
   cout << "Llega hebra " <<setw(2) << num_hebra << " (" <<setw(2) << orden << ")." << endl ;
   if ( cont < num_hebras_cita )
      cola.wait( guarda );
   else
   {
      for( int i = 0 ; i < num_hebras_cita-1 ; i++ )
         cola.notify_one() ;
      cont = 0 ;
   }
   cout << "              Sale hebra " <<setw(2) << num_hebra << " (" <<setw(2) << orden << ")." << endl ;
}
// -----------------------------------------------------------------------------

void funcion_hebra( MBarreraParSC * monitor, int num_hebra )
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
   const int num_hebras = 100,
             num_hebras_cita = 5 ;

   // crear monitor
   MBarreraParSC monitor( num_hebras_cita );

   // crear y lanzar hebras
   thread hebra[num_hebras];
   for( unsigned i = 0 ; i < num_hebras ; i++ )
      hebra[i] = thread( funcion_hebra, &monitor, i );

   // esperar a que terminen las hebras (no pasa nunca)
   for( unsigned i = 0 ; i < num_hebras ; i++ )
      hebra[i].join();
}
