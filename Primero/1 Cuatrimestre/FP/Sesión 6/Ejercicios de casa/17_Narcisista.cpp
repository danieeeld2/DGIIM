/*	Programa para determinar si un número
	entero es narcisista o no.
	Consideramos que un número es narcisista 
	cuando se puede obtener como la suma de las potencias
	n-ésimas de sus dígitos */
	
#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int entero;
	int suma_potencia_nesima;
	int digito;
	int contador;
	int exponente;
	bool narcisista;
	bool reseteo;
			
	cout << "Introducir un número entero: ";
	cin >> entero;
	
	suma_potencia_nesima = 0;
	contador = 10;
	exponente = 1;
	
	do{
		digito = ((entero % contador)-(entero % (contador / 10))) / ( contador / 10);
		suma_potencia_nesima = suma_potencia_nesima + pow ((digito*1.0), exponente);
		
		narcisista = entero==suma_potencia_nesima;
		reseteo = entero / contador == 0;
		
		if (reseteo){
			exponente++;
			contador = 1;
			suma_potencia_nesima = 0;
		}					
		
		contador = contador * 10;
		
	}while (!narcisista && exponente < 20);
	
	if (narcisista)
		cout << "\nEl número " << entero << " es narcisista";
	else
		cout << "\nEl número " << entero << " no es narcisista";
		
	cout << "\n\n";
	
	system ("pause");
}
