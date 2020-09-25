/*	Programa para determinar si dos números son amigos.
	(Se consideran amigos cuando la suma de los divisores
	del primero es igual al segundo y viceversa */
	
#include <iostream>

using namespace std;

int main(){
	int entero1;
	int entero2;
	int suma1;
	int suma2;
	int factorizacion1;
	int factorizacion2;
	int divisor1;
	int divisor2;
	bool amigos;
	
	cout << "Introduce un entero: ";
	cin >> entero1;
	
	cout << "Introduce otro entero: ";
	cin >> entero2;
	
	suma1 = suma2 = 0;
	divisor1 = divisor2 = 1;
	factorizacion1 = entero1;
	factorizacion2 = entero2;
	
	/*	Usamos dos bucles para realizar la suma
		de los divisores de cada entero.
		A continuación se evalua si son 
		"amigos"*/
	
	while (entero1 != divisor1){
		factorizacion1 = entero1 % divisor1;
		
		if (factorizacion1 == 0)
			suma1 = suma1 + divisor1;
			
		divisor1++;
		};

	while (entero2 != divisor2){
		factorizacion2 = entero2 % divisor2;
		
		if (factorizacion2 == 0)
			suma2 = suma2 + divisor2;
			
		divisor2++;
		};
		
		amigos = (entero2 == suma1) && (entero1 == suma2);
		
		if (amigos)
			cout << "\n\n" << entero1 << " y " << entero2 << " son amigos ";
		else
			cout << "\n\n" << entero1 << " y " << entero2 << " no son amigos ";
			
		cout << "\n\n";
		
		system ("pause");
	}
