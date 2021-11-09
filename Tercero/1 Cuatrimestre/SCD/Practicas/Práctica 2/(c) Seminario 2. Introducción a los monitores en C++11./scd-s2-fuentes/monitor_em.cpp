// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: monitor_em.cpp
// Ejemplo de monitores en C++11 sin variables condición
// (solo con encapsulamiento y exclusión mutua)
//
//  -- MContador1 : sin e.m.
//  -- MContador2 : con e.m. mediante acceso directo a cerrojos
//  -- MContador3 : con e.m. mediante guardas de cerrojo
//
// Historial:
// Creado en Julio de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

// *****************************************************************************
// clase contador, sin exclusión mutua
// las variables  pueden entrar a la vez al recurso compartido provocando que el valor final no sea el esperado

class MContador1
{
   private:
   int cont ;

   public:
   MContador1( int valor_ini ) ;
   void incrementa();
   int leer_valor();
} ;
// -----------------------------------------------------------------------------

MContador1::MContador1( int valor_ini )
{
   cont = valor_ini ;
}
// -----------------------------------------------------------------------------

void MContador1::incrementa()
{
   cont ++ ;
}
// -----------------------------------------------------------------------------

int MContador1::leer_valor()
{
   return cont ;
}

// *****************************************************************************
// clase contador, con exclusión mutua mediante manipulación directa del cerrojo
// esta versión, aunque es correcta, tiene varios inconvenientes y es que 
// puede ocurrir que se produzca un assert dentro del cerrojo, por lo que nunca se ejecuta
// unlock y las hebras se quedan esperando indefinidamente y que los return se hacen
// fuera del unlock (si se hace dentro sales de la funcion antes de la sentencia unlock), por lo
// que te tienes que crear una variable local.

class MContador2
{
   private:
   std::mutex cerrojo_mon ;
   int cont ;

   public:
   MContador2( int valor_ini ) ;
   void incrementa();
   int leer_valor();
} ;
// -----------------------------------------------------------------------------

MContador2::MContador2( int valor_ini )
{
   cont = valor_ini ;
}
// -----------------------------------------------------------------------------

void MContador2::incrementa()
{
   cerrojo_mon.lock();
   cont ++ ;
   cerrojo_mon.unlock();
}
// -----------------------------------------------------------------------------

int MContador2::leer_valor()
{
   cerrojo_mon.lock();
   int resultado = cont ;
   cerrojo_mon.unlock();
   return resultado ;
}

// *****************************************************************************
// clase contador, con exclusión mutua mediante guardas
// Las guardias apuntan al cerrojo que referencian y llaman a unlock al salir del método,
// independientemente de como este finalice

class MContador3
{
   private:
   std::mutex cerrojo_mon ;
   int cont ;

   public:
   MContador3( int valor_ini ) ;
   void incrementa();
   int leer_valor();
} ;
// -----------------------------------------------------------------------------

MContador3::MContador3( int valor_ini )
{
   cont = valor_ini ;
}
// -----------------------------------------------------------------------------

void MContador3::incrementa()
{
   unique_lock<mutex> guarda( cerrojo_mon );
   cont ++ ;
}
// -----------------------------------------------------------------------------

int MContador3::leer_valor()
{
   unique_lock<mutex> guarda( cerrojo_mon );
   return cont ;
}

// *****************************************************************************

const int num_incrementos = 10000 ;

// *****************************************************************************

void funcion_hebra_M1( MContador1 * monitor )
{
   for( int i = 0 ; i < num_incrementos ; i++ )
      monitor->incrementa();
}


void test_1()
{
   MContador1 monitor(0) ;

   thread hebra1( funcion_hebra_M1, &monitor ),
          hebra2( funcion_hebra_M1, &monitor );

   hebra1.join();
   hebra2.join();

   cout  << "Monitor contador (sin exclusión mutua):" << endl
         << endl
         << "  valor esperado == " << 2*num_incrementos << endl
         << "  valor obtenido == " << monitor.leer_valor() << endl
         << endl;
}
// *****************************************************************************

void funcion_hebra_M2( MContador2 * monitor )
{
   for( int i = 0 ; i < num_incrementos ; i++ )
      monitor->incrementa();
}


void test_2()
{
   MContador2 monitor(0) ;

   thread hebra1( funcion_hebra_M2, &monitor ),
          hebra2( funcion_hebra_M2, &monitor );

   hebra1.join();
   hebra2.join();

   cout  << "Monitor contador (EM con acceso directo a cerrojos):" << endl
         << endl
         << "  valor esperado == " << 2*num_incrementos << endl
         << "  valor obtenido == " << monitor.leer_valor() << endl
         << endl ;
}
// *****************************************************************************

void funcion_hebra_M3( MContador3 * monitor )
{
   for( int i = 0 ; i < num_incrementos ; i++ )
      monitor->incrementa();
}

void test_3()
{
   MContador3 monitor(0) ;

   thread hebra1( funcion_hebra_M3, &monitor ),
          hebra2( funcion_hebra_M3, &monitor );

   hebra1.join();
   hebra2.join();

   cout  << "Monitor contador (EM con guardas de cerrojo):" << endl
         << endl
         << "  valor esperado == " << 2*num_incrementos << endl
         << "  valor obtenido == " << monitor.leer_valor() << endl
         << endl ;
}

// *****************************************************************************


int main()
{
   test_1();
   test_2();
   test_3();
}
