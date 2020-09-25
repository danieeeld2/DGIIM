/*	Programa que dice si un entero es desgarrable o no.
	Un numero entero se dice que es desgarrable 
	si al dividirlo en dos partes izda y dcha,
	el cuadrado de la suma de ambas partes es igual a n. */
	
#include <iostream>

using namespace std;

int main(){
	int entero;
	int derecha;
	int izquierda;
	int divisor;
	bool desgarrable;
	
	cout << "Introducir un entero: ";
	cin >> entero;
	
	divisor = 1;
	
	derecha = 0;
	izquierda = entero;
	
	do{
		derecha = entero % divisor;
		izquierda = entero / divisor;
		divisor = divisor * 10;
		desgarrable = ((izquierda + derecha)*(izquierda + derecha)) == entero;
	}while (!desgarrable && izquierda != 0);
	
	if (desgarrable)
		cout << "\n\nEl entero " << entero << " es desgarrable ";
	else
		cout << "\n\nEl entero " << entero << " no es desgarrable ";
		
	cout << "\n\n";
	
	system ("pause");
}
