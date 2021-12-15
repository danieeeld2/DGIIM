// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 5 (ejemplo5.cpp)
// Obtención de resultados mediante 'return' y la llamada a 'async'
//
// Historial:
// Creado en Abril de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <future>     // declaracion de {\bf std::thread}, {\bf std::async}, {\bf std::future}
using namespace std ; // permite acortar la notación (abc en lugar de std::abc)

// declaración de la función {\bf factorial} (parámetro {\bf int}, resultado {\bf long})
long factorial( int n ) { return n > 0 ? n*factorial(n-1) : 1 ; }

int main()
{
  // iniciar las hebras y obtener los objetos {\bf future} (conteniendo un {\bf long})
  // (el valor {\bf launch:async} indica que se debe usar una hebra concurrente
  // para evaluar la función):
  future<long> futuro1 = async( launch::async, factorial, 5  ),
               futuro2 = async( launch::async, factorial, 10 );

  // esperar a que terminen las hebras, obtener resultado e imprimirlos
  cout << "factorial(5)  == " << futuro1.get() << endl
       << "factorial(10) == " << futuro2.get() << endl ;
}
