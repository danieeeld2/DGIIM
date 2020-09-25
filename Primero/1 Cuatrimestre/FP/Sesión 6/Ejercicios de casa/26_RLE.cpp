/*	Programa que codifica una secuencia de
	datos formados por valores identicos consecutivos
	como una secuencia de pareja de números */
	
#include <iostream>

using namespace std;

int main(){
	int entero;
	int contador;
	int comprobador;
	
	cout << "Introduzca la secuencia: " << "\n\n";
	
	cout << "";
	cin >> entero;
	
	contador = 1;
	comprobador = entero;
	 
	while (entero > -1){
		cout << "";
		cin >> entero;
					
		if (entero == comprobador)
			contador++;
		else{
			cout << "\n\t" << comprobador << "" << contador << "\n";
			contador = 1;
			comprobador = entero;
		}
	}
	
	cout << "\n\n";
	system ("pause");
}
