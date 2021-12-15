// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 8 (ejemplo8.cpp)
// Medicion de la duración de la ejecución de unas instrucciones.
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <chrono>  // incluye now, time\_point, duration

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

using namespace std ;
using namespace std::chrono;

int main()
{
  // leer instante de inicio de las instrucciones
  time_point<steady_clock> instante_inicio = steady_clock::now() ;

  // aquí se ejecutan las instrucciones cuya duración se quiere medir
  long fact = factorial( 20 ); // p.ej: calcular el factorial de 50

  // leer instante final de las instrucciones
  time_point<steady_clock> instante_final = steady_clock::now() ;
  // restar ambos instantes y obtener una duración (en microsegundos en float)
  duration<float,micro> duracion_micros = instante_final - instante_inicio ;
  // imprimir los tiempos usando el método {\bf count}
  cout << "La actividad ha tardado : "
       << duracion_micros.count() << " microsegundos." << endl ;
}
