
/*
Programa que lee desde teclado tres variables correspondientes a un numero de horas, minutos
y segundos, respectivamente, y calcula las horas, minutos
y segundos dentro de su rango correspondiente. En el caso de que nos salgan mas de 24 horas, daremos tambien los dias correspondientes (pero ya no pasamos a ver los meses, a–os, etc)
*/

#include <iostream>
using namespace std;

int main(){
    // <- No usad nombres como aux1, aux2, aux3 !!
   int segundos_enteros, minutos_enteros, horas_enteras, dias_enteros;
   int minutos_totales, horas_totales, dias_totales;
   int segundos, minutos, horas; // Entradas

   cout << "\nIntroduzca segundos --> ";
   cin >> segundos;
   cout << "\nIntroduzca minutos --> ";
   cin >> minutos;
   cout << "\nIntroduzca horas --> ";
   cin >> horas;

   /* 
   La siguiente solucion repite muchos computos.
   Repetir codigo tiene los siguientes problemas:
   1. Es ineficiente pues se pierde tiempo en evaluar expresiones repetidas
   2. Mucho peor: Es propenso a errores ya que hay que teclear varias veces
   una misma expresion y debe ser igual siempre
   3. Es dificil de modificar ya que cada cambio habra que hacerlo
   en cada una de las expresiones repetidas.
	*/

	/*
   segundos_enteros  = segundos % 60;
   minutos_enteros	= (segundos / 60 + minutos) % 60;
   horas_enteras = ((segundos / 60 + minutos) / 60 + horas ) % 24;
   dias_enteros	 = ((segundos / 60 + minutos) / 60 + horas ) / 24;
   */

    /*
     El siguiente codigo no repite computos. En cualquier caso, estamos modificando las variables originales segundos, minutos, horas y no es recomendable.
     */
    
    /*
     segundos_enteros  = segundos % 60;
     minutos = segundos / 60 + minutos;
     minutos_enteros = minutos % 60;
     horas = minutos / 60 + horas;
     horas_enteras = horas % 24;
     dias_totales = horas / 24;
     */
    
   /*
   El siguiente algoritmo no repite codigo.
	Hemos usado tres variables adicionales con los totales de los minutos, horas, etc. 
   */

   minutos_totales  = segundos / 60  +  minutos;
   horas_totales    = minutos_totales / 60  +  horas;
   dias_totales     = horas_totales / 24;  // + dias en su caso  

   segundos_enteros = segundos % 60;
   minutos_enteros  = minutos_totales % 60;
   horas_enteras    = horas_totales % 24;  		

   cout << "\nSegundos enteros: " << segundos_enteros;
   cout << "\nMinutos enteros:  " << minutos_enteros;
   cout << "\nHoras enteras:    " << horas_enteras;
   cout << "\nDías restantes:   " << dias_totales;

   /*
   ***********************************************************************************
   ***********************************************************************************
   Recomendaciones:

   - El uso de variables intermedias ayuda a realizar las operaciones intermedias, 
	  facilitando la comprension del codigo

   - No debemos modificar los valores de las variables importantes de nuestro programa,
	  ya que posiblemente se usen en varios sitios y querremos recuperar el valor original.

   ***********************************************************************************
   ***********************************************************************************
   */
}
