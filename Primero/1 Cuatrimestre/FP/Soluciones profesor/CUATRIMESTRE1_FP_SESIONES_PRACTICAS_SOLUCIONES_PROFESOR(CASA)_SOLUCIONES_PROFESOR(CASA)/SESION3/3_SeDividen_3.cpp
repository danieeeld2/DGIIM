
/*
   Ver si dos enteros se dividen
*/

#include <iostream>
using namespace std;

int main(){
   int a, b;               // Nunca usaremos nombres de variables tan cortos como a, b
                        // Este ejercicio es una excepcion ya que los datos son genericos
   bool se_dividen;

	// Entrada de datos

   cout << "\nIntroduzca primer valor ";      
   cin >> a;                           
   cout << "\nIntroduzca segundo valor ";      
   cin >> b;                          

   // Computos
   
    
   se_dividen = (a % b == 0 || b % a == 0);

	// Salida de Resultados 

   if (se_dividen)
      cout << "\nUno divide al otro";
   else
      cout << "\nNinguno divide al otro";

   cout << "\n\n";
}
