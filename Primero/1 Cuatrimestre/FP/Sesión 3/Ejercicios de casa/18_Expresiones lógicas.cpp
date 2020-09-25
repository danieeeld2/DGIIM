/*	Programa que devuelve el valor de determinadas expresiones
	lógicas. En caso de que sean incorrectas se deberá justificar
	el error
*/

#include <iostream>

using namespace std;

int main(){
	
	/*	Para este ejercicio vamos a utilizar datos de tipo lógico 
		o booleanos, los cuales están formado únicamente por dos valores
		posibles: true o false.
		
		Además, necesitaremos usar algunos operadores lógicos, como son:
		&&, que corresponde a Y
		||, que corresponde a O
		!, que corresponde a NO
		
		También necesitaremos operadores relacionales como:
		== que es igual
		!= que significa distinto
		<> menor o mayor
		<= => menor o igua, mayor o igual
	*/
	
	// Apartado A
	
	bool desigualdad1;
	
	desigualdad1 = 2 + 3 < 5 + 8 ;	// True
	
	cout << "El compilador devuelve : " << desigualdad1 << ", ya que la proposición es verdadera" ;
	
	// Apartado B
	
	bool desigualdad2;
	
	desigualdad2 = 2 < 3 < 4 ;	//True
	
	cout << "\nEl compilador devuelve : " << desigualdad2 << ", ya que la proposición es verdadera" ;
	
	//	Apartado C
	
	bool suma;
	
	suma = 7/3 + 4.0 ;	//	Esta proposición no representa ninguna expresión lógica
	
	// Apartado D
	/*
	bool expresion1;
	int x, y, z;
	
	cout << "Introducir valor de x: " ;
	cin >> x ;
	
	cout << "Introducir valor de y: " ;
	cin >> y ;
	
	cout << "Introducir valor de z: " ;
	cin >> z ;
	
	expresion1 = ( (x == 4&&y == 3) || (!(z) = 2 == !(1) = 2) ) ; //	No tiene ningun sentido
	
	if (expresion1)
		cout << "\nEl compilador devuelve : " << expresion1 << ", ya que la proposición es verdadera" ; 
	else
		cout << "\nEl compilador devuelve : " << expresion1 << ", ya que la proposición es falsa" ;
	*/
			
	//	Apartado E
	
	bool expresion2;
	int x2;
	
	cout << "\nIntroducir valor de x: " ;
	cin >> x2 ;
	
	expresion2 = ( x2 <= 4||x2 >= 4 ) ;	//	Esta proposición es siempre verdadera, para todo valor entero de x
	
	if (expresion2)
		cout << "\nEl compilador devuelve : " << expresion2 << ", ya que la proposición es verdadera" ; 
	else
		cout << "\nEl compilador devuelve : " << expresion2 << ", ya que la proposición es falsa" ;
		
	cout << "\nLa proposición anterior es siempre verdadera (es trivial)" ;
	
	//	Apartado F
	
	bool expresion3;
	int x3;
	
	cout << "\n\nIntroducir valor de x: " ;
	cin >> x3 ;
	
	expresion3 = ( x3 < 4&&x3 > 4 ) ;	//	Esta proposición es falsa siempre
	
	cout << "\nEsta proposición es falsa siempre, ya que no existe numero entero que se a su vez mayor y menor que 4. " ;
	cout << "El compilador, por tanto, siempre devuelve " << expresion3 ;
	
	//	Apartado G
	
	bool expresion4;
	int z;
	char a;
	
	cout << "\nIntroduzca valor de z: " ;
	cin >> z ;
	
	cout << "Introduzca caracter : " ;
	cin >> a ;
	
	expresion4 = ( z > 6 || a < z && a > a || z < 6 ); // Esta expresión es siempre verdadera para z distinto de 6
	
	if (expresion2)
		cout << "\nEl compilador devuelve : " << expresion4 << ", ya que la proposición es verdadera" ; 
	else
		cout << "\nEl compilador devuelve : " << expresion4 << ", ya que la proposición es falsa" ;
	
	
	system ("pause");
}
	
