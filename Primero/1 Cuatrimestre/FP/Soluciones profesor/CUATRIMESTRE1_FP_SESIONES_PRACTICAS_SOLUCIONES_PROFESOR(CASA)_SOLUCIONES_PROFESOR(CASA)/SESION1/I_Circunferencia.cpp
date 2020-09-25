/*
   Programa que pide el radio y calcula e imprime
   en pantalla el area correspondiente y la longitud de la circunferencia.
   Entradas: El radio de la circunferencia
   Salidas:  El area del círculo calculada mediante:
				      area = PI * radio * radio
             La longitud de la circunferencia calculada mediante:
				      longitud = 2 * PI * radio
*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main(){
   /*
      Si en vez de usar el dato PI hubiesemos utilizado el literal 3.1416
      
         area = 3.1416 * radio * radio;
	      longitud = 2 * 3.1416  * radio;
	      
      el codigo fuente es "propenso a errores" ya que la actualización del programa
      puede ser problematica. Para cambiar 3.1416 por un valor mas preciso como 3.1415927
      debemos marcar con el raton el texto y reemplazar 16 por 15927
      ÀY si en el texto marcado hubiese alguna aparicion de 16 que no correspondiese a Pi?
      Lo resolvemos usando el dato PI y actualizamos su valor modificando unicamente
      la linea en la que se define dicho dato.

      Principio de Programacion:
         Las actualizaciones futuras de nuestro codigo deben afectar al menor numero
         posible de instrucciones.

      Por otra parte, seria deseable que el compilador diese un error
        si el programador incluyese una sentencia para modificar el valor de PI.
        Esto se consigue con el cualificador const:
        
        const double PI = 3.1415927
   */

	const double PI = 3.1415927;

	double radio;				// Dato de entrada
	double area, longitud;	// Datos de salida

	cout << "Introduzca el valor del radio: ";
	cin >> radio;

	area = PI * radio * radio;
	longitud = 2 * PI  * radio;

	cout << "\n\nEl area del circulo vale " << area;
	cout << "\n\nLa longitud de la circunferencia vale " << longitud;
	cout << "\n\n";
}
