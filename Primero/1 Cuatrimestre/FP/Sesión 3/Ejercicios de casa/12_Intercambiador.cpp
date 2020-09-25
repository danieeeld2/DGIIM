/*	Programa para intercambiar el valor de tres variables x, y, z,
	de tal forma que el valor de x pase a y, el de y a z y el de z a x
	Se pide utilizar el menor número de variables auxiliares posibles
*/

#include <iostream> 

using namespace std; 

int main(){
	int x, y, z;
	int copia;
	
	x = 10 ;
	y = 20 ;
	z = 30 ;
	 
	cout << " \nOriginalmente los valores de x, y, z eran 10, 20 y 30, pero el programa los ha intercambiado: " ;
	
	copia = y ;
	y = x ;
	x = z ;
	z = copia ;
	
	cout << "\nAhora x vale: " << x ;
	cout << "\nAhora y vale: " << y ;
	cout << "\nAhora z vale: " << z << "\n\n" ;
	
	// Observamos que los valores de las variables se han intercambiado y 
	// solo hemos necesitado una variable auxiliar
	
	system ("pause");
}
