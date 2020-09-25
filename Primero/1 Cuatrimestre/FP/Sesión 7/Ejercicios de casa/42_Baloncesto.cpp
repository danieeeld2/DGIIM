/*	Programa que registra el acta
	de un partido de baloncesto e indica
	que equipo ha ganado */
	
#include <iostream>

using namespace std;

int main(){
	int puntos;
	int dorsal;
	int suma1;
	int suma2;
	int suma3;
	int suma4;
	int suma5;
	int suma6;
	int suma_equipo1;
	int suma_equipo2;
	
	cout << "Introduzca la secuencia de número: ";
	cout << "(Finaliza al introducir ´-1') ";
	
	suma1 = suma2 = suma3 = suma4 = suma5 = suma6 = 0;
	dorsal = 0;

	while(dorsal != -1){
		cin >> dorsal;		
		cin >> puntos;
		
		switch(dorsal){
			case 1:
				suma1 = suma1 + puntos;
			break;
			
			case 2:
				suma2 = suma2 + puntos;
			break;
			
			case 3:
				suma3 = suma3 + puntos;
			break;
			
			case 4:
				suma4 = suma4 + puntos;
			break;
			
			case 5:
				suma5 = suma5 + puntos;
			break;
			
			case 6:
				suma6 = suma6 + puntos;
			break;
		}
		
	};
	
	suma_equipo1 = suma1 + suma2 + suma3;
	suma_equipo2 = suma4 + suma5 + suma6;
	
	if(suma_equipo1 > suma_equipo2)
		cout << "\n\nGana equipo 1 ";
	else{
		if (suma_equipo1 == suma_equipo2)
			cout << "\n\nEmpate ";
		else
			cout << "\n\nGana equipo 2 ";
		}
		
	cout << "\n\n";
	system ("pause");
	}
		
		
