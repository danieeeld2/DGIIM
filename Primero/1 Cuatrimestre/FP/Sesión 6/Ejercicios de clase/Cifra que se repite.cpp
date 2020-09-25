/*	Programa que dice cuantas veces aparece una
	cifra ,k, en un intervalo cerrado */
	
#include <iostream>

using namespace std;

int main(){
	int origen;
	int final;
	int entero_repetido;
	int valor_analizando;
	int contador;
	int divisor;
	int comprobador;
	
	cout << "Introduzca un entero: ";
	cin >> origen;
	cout << "\nIntroduzca un entero: ";
	cin >> final;
	cout << "\nIntroduzca cifra a analizar: ";
	cin >> entero_repetido;
	
	contador = 0;
	divisor = 1;
	valor_analizando = origen;
	
	while(valor_analizando <= final){
		while(valor_analizando / divisor != 0){
			divisor = divisor * 10;
			comprobador = ((valor_analizando % divisor) - (valor_analizando % (divisor/10))) / (divisor / 10);
			
			if(entero_repetido == comprobador)
				contador++;
		};
		
		valor_analizando++;
		divisor = 1;
	};
	
	cout << "\n\nSe repite: " << contador << " veces";
	
	cout << "\n\n";
	system ("pause");
}
		
