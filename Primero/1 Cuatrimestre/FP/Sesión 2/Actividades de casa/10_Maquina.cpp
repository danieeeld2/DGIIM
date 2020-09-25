/*	Programa que simula el funcionamiento de una máquina de refrescos,
	de tal forma que el usuario introduzca por teclado el precio
	del producto y el dinero que se introduce en la máquina
	(Se considera que el usuario introduce una cantidad igual o
	superior al precio del producto) y por pantalla salga el
	número de monedas de 1 euro, 50, 20, 10 y 5 ctmos que la 
	maquina debe devolver como cambio
*/

//	Se considera que el usuario introduce los datos en céntimos

#include <iostream>

using namespace std;

int main(){
	int precio;
	int dinero_introducido;
	int euro;
	int _50cent; 
	int auxiliar1;
	int _20cent; 
	int auxiliar2;
	int _10cent; 
	int auxiliar3;
	int _5cent; 
	int auxiliar4;
	
	cout << "Introduzca precio del producto: " ;
	cin >> precio ;
	
	cout << "Introduzca el dinero introducido en la máquina: " ;
	cin >> dinero_introducido ;
	
	euro = (dinero_introducido-precio)/100 ;			//	1 euro = 100 cent
	auxiliar1 = (dinero_introducido-precio)%100 ;
	_50cent = auxiliar1/50 ;								
	auxiliar2 = auxiliar1%50 ;
	_20cent = auxiliar2/20 ;
	auxiliar3 = auxiliar2%20 ;
	_10cent = auxiliar3/10 ;
	auxiliar4 = auxiliar3%10 ;
	_5cent = auxiliar4/5 ;
	
	/*	Utilizamos el concepto de que, para variables enteras,
		el operador / se queda con el cociente de la división de enteros
		y el operador % con el rest */
	
	cout << "Monedas de euro: " << euro << "\n" ;
	cout << "Monedas de 50 céntimos: " << _50cent << "\n" ;
	cout << "Monedas de 20 céntimos: " << _20cent << "\n" ;
	cout << "Monedas de 10 céntimos: " << _10cent << "\n" ;
	cout << "Monedas de 5 céntimos: " << _5cent << "\n" ;
	
	system ("pause");
}
