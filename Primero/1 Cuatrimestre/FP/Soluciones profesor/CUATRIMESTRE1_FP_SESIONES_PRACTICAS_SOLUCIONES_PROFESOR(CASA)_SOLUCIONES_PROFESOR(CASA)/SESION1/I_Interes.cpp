/*
   Programa que calcula el dinero que se obtiene al realizar una
   inversion a plazo fijo (en un a–o).
   Entradas: capital a invertir (capital) e interes a aplicar (interes).
   Salidas:  dinero total (capital + ganancia obtenida) calculado por:
				total = capital + (capital * interes/100)
*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main(){
	double interes;		// Entrada: interes a aplicar
	double capital;		// Entrada: capital solicitado
	double total;			// Salida: cantidad ganada en un año

	cout << "Introduzca capital inicial --> ";
	cin >> capital;
	cout << "\nIntroduzca interes --> ";
	cin >> interes;

    // Observad que la misma variable capital se puede usar en varios sitios de la expresion:

	total = capital + capital * interes/100;

	cout << "\nCapital + Ganancia obtenida = " << total;
	cout << "\n\n";

   /*
      'Hubiese sido mejor "ahorrarnos' la variable total?
      
         capital = capital + capital * interes/100;
         cout << "\nCapital + Ganancia obtenida = " << capital;
         
      El programa tambien funcionaria correctamente, pero Ày si quisieramos imprimir
      tambien el capital inicial? No lo podriamos hacer porque modificamos el valor
      original del capital en la asignacion capital = capital + capital * interes/100;

      Principio de Programacion:
         No debemos modificar los valores de los datos "importantes" de nuestro programa
         ya que es muy posible que los necesitemos en distintos sitios del programa.

      Por lo tanto, nunca debemos pensar que es bueno utilizar cuantas menos variables mejor.
      Al reves, en numerosas ocasiones, introducir variables aumenta la legibilidad del codigo.
   */
}

