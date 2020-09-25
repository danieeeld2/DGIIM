/*	Programa para calcular cuantos años deben
	pasar para doblar un capital inicial, depositado en
	un banco, dado un determinado interes */
	
#include <iostream>

using namespace std;

int main(){
	double capital_inicial;
	double capital_final;
	double interes;
	double TERMINADOR;
	int contador_anios;
	
	cout << "Introduzca el capital inicial: ";
	cin >> capital_inicial;
	cout << "Introduzca el interes: ";
	cin >> interes;
	
	TERMINADOR = 2*capital_inicial;
	
	capital_final = capital_inicial;
	contador_anios = 0;
	
	while ( capital_final < TERMINADOR ){
		capital_final = capital_final + (capital_final * interes/100);
		
		contador_anios++;
	}
	
	cout << "\nPara duplicar " << capital_inicial << " con " << interes << "% de intereses ";
	cout << "se requieren " << contador_anios << " años ";
	
	cout << "\n\n";
	
	system ("pause");
}
		
	
