/*	Programa para enviar códigos de 5 dígitos 
	encriptados a una sede bancaria. Los códigos 
	contienen la ID de un cliente moroso */
	
#include <iostream>

using namespace std;

int main(){
	int letra_a;
	int letra_e;
	int letra_i;
	int letra_o;
	int letra_u;
	char letra;
	int contador_hastag;
	
	letra_a = letra_e = letra_i = 0;
	letra_o = letra_u = contador_hastag = 0;
	
	cout << "Introduzca la secuencia codificada: " << "\n\n";
	
	/*	Usamos un primer bucle para pedir datos constantemente.
		Cuando se introduzca el primer '#' el programa empezará
		a contar cuantas veces se introduce cada vocal.
		Cuando introduzcamos el segundp '#' dejará de contar y
		seguirá pidiendo datos hasta introducir '@' */
	
	while(letra != '@'){
		cout << "";
		cin >> letra;
		
		if (letra == '#')
			contador_hastag++;
		
		if(contador_hastag == 1){
			switch(letra){
				
				case 'a':
					letra_a++;
				break;
				
				case 'e':
					letra_e++;
				break;
				
				case 'i':
					letra_i++;
				break;
				
				case 'o':
					letra_o++;
				break;
				
				case 'u':
					letra_u++;
				break;
			};
		}
	};
	
	cout << "\n\nLa secuencia descodificada es: ";
	cout << letra_a << letra_e << letra_i << letra_o << letra_u;
	
	cout << "\n\n";
	
	system ("pause");
}
