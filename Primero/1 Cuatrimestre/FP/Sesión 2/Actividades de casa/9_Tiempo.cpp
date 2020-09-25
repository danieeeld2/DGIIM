/*	Programa que implementa un algoritmo que lea horas, minutos y 
	segundos dentro de su rango correspondiente.
	
	Para este ejercicio usaremos los operadores /, el cual
	se queda con el cociente, y %, el cual se queda con el resto,
	de una diviión de enteros
*/

#include <iostream>

using namespace std;

int main(){
	int horas, minutos, segundos;
	int horas_aux1, minutos_aux1, segundos_aux1;
	int minutos_totales, horas_totales, dias_totales;
	
	cout << "Introduzca los segundos: " ;
	cin >> segundos ;
	
	cout << "Introduzca los minutos: " ;
	cin >> minutos ;
	
	cout << "Introduzca las horas: " ;
	cin >> horas ;
	
	minutos_totales = ( segundos/60 ) + minutos ;
	horas_totales = ( minutos/60 ) + horas ;
	dias_totales = ( horas/24 ) ;
	
	segundos_aux1 = segundos % 60 ;
	minutos_aux1 = minutos_totales % 60 ;
	horas_aux1 = horas_totales % 24 ;
	
	/*	Volvemos a usar el cocepto de que dado las variables
		enteras x,y x/y almacena el cociente, mientras que
		x%y se queda con el resto */
		
	/*	Observar como existe la posibilidad de que las variables
		auxiliares se sustituyan por las enteras si el valor
		es exacto */	
	
	cout << "Días: " << dias_totales;
	cout << "  Horas: " << horas_aux1 ;
	cout << "  Minutos: " << minutos_aux1 ;
	cout << "  Segundos: " << segundos_aux1 ;
	
	system ("pause");
}
