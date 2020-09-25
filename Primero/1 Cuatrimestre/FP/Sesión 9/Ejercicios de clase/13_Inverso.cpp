/*	Programa que implementa
	un módulo que  imprime los
	dígitos de un entero en orden
	inverso */
	
#include<iostream>

using namespace std;

void Inversa (int a){
	const int LONGITUD = 50;
	int contador;
	int vector [LONGITUD];
	int divisor;
	
	contador = 0;
	divisor = 1;
	
	while(a / divisor != 0){
		divisor = divisor * 10;
		vector[contador] = ((a % divisor) - (a % (divisor / 10))) / (divisor / 10);
		contador++;
	};
	
	for(int i = 0 ; i != contador; i++){
		cout << vector[i];
	};
};

int main(){
	int numero;
	
	cout << "Introduzca un entero: ";
	cin >> numero;
	
	cout << "\nEl inverso es: ";
	Inversa(numero);
	
	cout << "\n\n";
}
