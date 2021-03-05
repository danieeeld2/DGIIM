/**
   @file Ordenaci�n por inserci�n
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por inserci�n  */

/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static 
void insercion(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(int T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}



int main(int argc, char * argv[])
{
  int n;
  /* cout << "Introduce n�mero de elementos del vector: ";
  cin >> n;
 */
  n=atoi(argv[1]);
  int * T = new int[n];
  assert(T);

  srandom(time(0));

  for (int i = 0; i < n; i++)
    {
      T[i] = random();
    };

  clock_t t_antes = clock();
  insercion(T, n);
  clock_t t_despues = clock();
  cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

  delete [] T;

  return 0;
};
