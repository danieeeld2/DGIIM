
/*	
Programa que lee un entero de tres digitos y los muestra individualmente,
separandolos por tres espacios.

Entradas: un entero
Salidas:  Los digitos del entero leido.
*/
/*********************************************************************/


#include <iostream>
using namespace std;

int main()
{
   int numero_3dig;	// Dato de entrada: un entero de tres digitos
   int numero_2dig; 
   int digito_centenas, digito_decenas, digito_unidades;

   // Entrada

   cout << "Introduce un entero de tres digitos: ";
   cin >> numero_3dig; 

   // Calculos

   digito_centenas = numero_3dig / 100;
   numero_2dig     = numero_3dig % 100;    // Las dos cifras menos significativas
   digito_decenas  = numero_2dig / 10;
   digito_unidades = numero_2dig % 10;

   // Salida

   cout << digito_centenas << "   " << digito_decenas << "   "  << digito_unidades << "\n";
}
