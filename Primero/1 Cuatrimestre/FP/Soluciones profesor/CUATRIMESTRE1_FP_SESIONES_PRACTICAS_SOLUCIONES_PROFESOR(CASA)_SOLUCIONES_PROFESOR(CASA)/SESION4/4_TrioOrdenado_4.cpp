/*

	Programa que lee tres enteros desde teclado y nos dice si estan
	ordenados (da igual si es de forma ascendente o descendente) o no.
	(la version 2 informa adicionalmente sobre el tipo de ordenacion)
	
	Entradas: tres numeros enteros
	Salidas: El mensaje "Estan ordenados" o "No estan ordenados"


*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	int numero1, numero2, numero3;

	// Entrada 	
	
	cout << "\nIntroduce tres enteros: ";
	cin >> numero1 >> numero2 >> numero3;

	// Calculos

	/* 	Version 1:
		Estructura condicional doble que no comprueba el 
		tipo de orden creciente/decreciente	

	bool estan_ordenados; 

	if ((numero1 > numero2) && (numero2 > numero3))
		estan_ordenados = true; 
	else 
		if ((numero1 < numero2) && (numero2 < numero3))
			estan_ordenados = true; 
	 	else 
			estan_ordenados = false; 	
	*/
	 	
	/* 	Version 2:
		Se guardan los estados en variable lógicas.
		Se inician todas a false por defecto
	*/
	
    
    // almacenamos las posibilidades en variables
	bool orden_creciente, orden_decreciente, estan_ordenados;
	orden_creciente = orden_decreciente = estan_ordenados = false; 

	orden_creciente = ((numero1 < numero2) && (numero2 < numero3));
	orden_decreciente = ((numero1 > numero2) && (numero2 > numero3));
	estan_ordenados = orden_creciente || orden_decreciente; 
	 		 	

	// Salida 
	
	if (estan_ordenados) {
		cout << "Estan ordenados.";
		if (orden_creciente) 
			cout << " Orden creciente.";
		else 
			cout << " Orden decreciente.";
	}	
	else 
		cout << "No estan ordenados.";

	cout << endl << endl;

}
