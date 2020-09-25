
/*
   Calcular el numero de a–os que han de pasar para obtener un total acumulado
   del doble del capital inicial
*/

#include <iostream> 
using namespace std;  
   
int main(){    
   double interes, capital_inicial, capital_acumulado, cuantia_final_a_conseguir;
   int  anios_transcurridos;
   
   cout << "Introduzca capital inicial --> ";
   cin >> capital_inicial;
   cout << "\nIntroduzca interes (como un %) --> ";
   cin >> interes;   

   /*
	Algoritmo:

		Incializar el capital obtenido al capital inicial

		Recorrer a–os hasta llegar al capital objetivo
			Acumular el capital del a–o anterior con el interes aplicado
	*/

	/*
		Si ponemos:
			while (capital_acumulado < capital_inicial * 2)
		estamos evaluando la misma expresion capital_inicial * 2 cada vez que entremos al bucle.
		Como la expresion no varia, mejor guardamos el valor en una variable antes de entrar al bucle:
	*/

   capital_acumulado = capital_inicial; // no variar datos iniciales
   anios_transcurridos = 0;
   cuantia_final_a_conseguir = capital_inicial * 2; // no evaluar capital_inicial * 2 cada iteracion

   while (capital_acumulado < cuantia_final_a_conseguir){             
      capital_acumulado = capital_acumulado  +  capital_acumulado * interes / 100.0;
      anios_transcurridos++;
      cout << "\nDinero obtenido en el a–o numero " << anios_transcurridos
           << " = " << capital_acumulado;
   }
   
   cout << "\n\nPara doblar la cantidad inicial han de pasar " << anios_transcurridos << " a–os";
   cout << "\n\n";
}
