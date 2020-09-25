/*	Programa que lea un carácter que el usuario introduzca en
	mayúscula y lo transforma a minúscula.
	No se pueden usar las funciones toupper ni tolower de la
	biblioteca cctype. Ha de realizarse con la equivalencia entre
	enteros y caracteres. 
*/

#include <iostream>

using namespace std;

int main(){
	
	/*	Teniendo en cuenta que en la tabla ASCII hay el mismo número
		de letras en mayúscuas y en minúscula y que están colocadas
		en el mismo orden, basta con sabe cuántos caracteres separan
		a A ( primera letra mayúscula ) y a ( primera letra minúscula )
		
		El orden de 'A' es 65 y el de 'a' 97, por tanto la separación
		es de 32. Esta proporción se cumple de B-b, de C-c ...
		
		Sabiendo esto ya podemos realizar nuestro programa 
	*/
	
	char minuscula, mayuscula;
	
	cout << " Introduzca una letra en mayúscula: " ;
	cin >> mayuscula ;
	
	minuscula = mayuscula + 32 ;
	
	cout << "\nEl carácter en mayúscula es: " << mayuscula ;
	cout << "\nEl carácter en minúscula es: " << minuscula << "\n\n" ;
	
	system ("pause");
}	
