/*	Programa para convertir el valor de un 
	caracter numérico entero, en nuestro caso 7
	y se le asigne el valor numérico a una variable tipo 
	entera, la cual imprimirá por pantalla
*/

#include <iostream>
#include <cstdlib>

using namespace std; 

int main(){
	
	/*	Para este programa debemos tener en cuenta que al introducir "7"
		como un caracter, su valor numérico correspondiente en ASCII es
		55.
		
		Sabiendo esto; para almacenar el valor numérico 7 en una variable de tipo
		entera e imprimirla por pantalla bastaría con asignarle a dicha
		variable el valor "7" - 48.
		
		El código anterior sería claramente válido, pero podría llevar
		a confusión ya que si alguien lee explícitamente "7"-48 no estaría
		pensando en 7 como resultado.
		
		Para evitar esta confusión, lo mejor es buscar en la tabla ASCII un 
		caracter cuyo orden sea de 48 en ASCII y restarle dicho valor a "7",
		el cual se trata del 0,el cual es del orden de 48 en ASCII.
		
		De esta forma pordemos evitar posibles confusiones.
	*/
	
	char caracter;
	int entero;
	const char cero = '0'; 
	
	/*	Como el la tabla ASCII los número enteros 0 a 9 están ordenados, el 
		razonamiento anterior es válido para cualquiera de estos números
	*/
	
	cout << "\nIntroduca un carácter numérico: " ;	//	Supongamos que el usuario introduce un entero del 0-9
	cin >> caracter ;
	
	entero = caracter-cero ;
	
	cout << "\nEl entero correpondiente es: " << entero << "\n\n" ;
	
	system ("pause");
}
