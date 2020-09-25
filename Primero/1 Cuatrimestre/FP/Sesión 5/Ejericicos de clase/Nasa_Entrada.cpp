/*	Continuando con el primer ejercicio de la Nasa,
	ahora creamos un programa que lea una secuencia desde 
	un fichero e indique el producto de los
	número primos */
	
#include <iostream>

using namespace std;

int main(){
	int secuencia_codificada;
	int contador_de_1;
	int contador_de_0;
	
	contador_de_1 = 0;
	contador_de_0 = 0;
	
	while(contador_de_0 != 5){
		cin >> secuencia_codificada;
		
		if (secuencia_codificada == 1){
			if (contador_de_0 > 0 ){
				contador_de_1 = 0;
				contador_de_0 = 0;
			}
			
			contador_de_1++;
		}
		
		if (secuencia_codificada == 0){
			if (contador_de_0 == 0)
				cout << contador_de_1 << "" << "";
				
			contador_de_0++;
		}
	};
	
	system ("pause");
}
