/*	Programa que indica las toneladas de horatliza
	que exporta un país y dice que país es el que más 
	toneladas exporta */

#include <iostream>

using namespace std;

int main(){
	char pais;
	char hortaliza;
	int toneladas;
	int total_exportado_Espania;
	int total_exportado_Francia;
	int total_exportado_Alemania;
	
	total_exportado_Espania = total_exportado_Francia = total_exportado_Alemania = 0;
	
	while ( pais != '@' ){
		cout << "Introduzca inicial del país: ";
		cin >> pais;
		
		cout << "Introduzca inicial de la hortaliza: ";
		cin >> hortaliza;
		
		cout << "Introduzca cantidad: ";
		cin >> toneladas;
		
		cout << pais << "" "" << hortaliza << "" "" << toneladas << "\n\n";
		
		if (pais == 'E')
			total_exportado_Espania = total_exportado_Espania + toneladas;
		if (pais == 'F')
			total_exportado_Francia = total_exportado_Francia + toneladas;
		if (pais == 'A')
			total_exportado_Alemania = total_exportado_Alemania + toneladas;
			
		if (total_exportado_Espania > total_exportado_Francia)
			cout << "El máximo exportador es España con " << total_exportado_Espania << " toneladas" << "\n\n";
		else
			if (total_exportado_Alemania > total_exportado_Francia)
				cout << "El máximo exportador es Alemania con " << total_exportado_Alemania << " toneladas" <<"\n\n";
			else
				cout << "El máximo exportador es Francia con " << total_exportado_Francia << " toneladas" << "\n\n";
	};
	
	cout << "\n\n";
	
	system ("pause");
}
