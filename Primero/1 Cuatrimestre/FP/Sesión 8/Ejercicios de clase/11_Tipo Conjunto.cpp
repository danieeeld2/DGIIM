/*	Programa para trabajar con
	conjuntos. Permite introducir
	elementos en un conjunto, calcular
	la unión y la intersección.
	Se asume que el usuario
	ha introducido previamente los
	datos iniciales */
	
//	TENGO QUE CORREGIR LOS DOS ÚLTIMOS
	
#include<iostream>

using namespace std;

struct TipoConjunto{
	int num_elem;
	int elementos[1000];
};

int main(){
	TipoConjunto ConjuntoA;
	TipoConjunto ConjuntoB;
	int elemento;
	bool pertenece;
	char opcion;
	char conjunto;
	int a_desplazar;
	int posicion;
	TipoConjunto ConjuntoUnion;
	int contador = 0;
	
	/*	Asumimos que el usuario ha introducido los siguientes
		datos iniciales */
		
	ConjuntoA.elementos [0] = 2;
	ConjuntoA.elementos [1] = 7;
	ConjuntoA.elementos [2] = 9;
	ConjuntoA.elementos [3] = 10;
	ConjuntoA.elementos [4] = 11;
	ConjuntoA.num_elem = 5;
	ConjuntoB.elementos [0] = 2;
	ConjuntoB.elementos [1] = 9;
	ConjuntoB.elementos [2] = 15;
	ConjuntoB.elementos [3] = 20;
	ConjuntoB.num_elem = 4;
	
	
	//	Determinar si un elemento pertenece al conjunto
	
	do{
		cout << "\nIntroduce un elemento para ver si pertenece a algún conjunto: ";
		cin >> elemento;
	
		pertenece = false;
	
		for(int i = 0; i != ConjuntoA.num_elem && !pertenece; i++)
			if(ConjuntoA.elementos[i] == elemento)
				pertenece = true;
	
		if(pertenece)
			cout << "\nEl elemento " << elemento << " pertenece al primer conjunto ";
		if(!pertenece)
			cout << "\nEl elemento " << elemento << " no pertenece al primer conjunto ";
		
		pertenece = false;
	
		for(int i = 0; i != ConjuntoB.num_elem && !pertenece; i++)
			if(ConjuntoB.elementos[i] == elemento)
				pertenece = true;
	
		if(pertenece)
			cout << "\nEl elemento " << elemento << " pertenece al segundo conjunto ";
		if(!pertenece)
			cout << "\nEl elemento " << elemento << " no pertenece al segundo conjunto ";
		
		cout << "\n\n¿Quieres analizar otro elemento (s/n)? ";
		cin >> opcion;
	}while(opcion == 's');
	
	//	Incorporar un nuevo elemento al conjunto
	
	cout << "\n\nIncorpore un nuevo elemento al conjunto ";
	
	do{
		cout << "\nElige el conjunto al que añadir el elemento (A/B): ";
		cin >> conjunto;
		
		switch (conjunto){
			case 'A':
				cout << "\nIntroduzca un elemento: ";
				cin >> ConjuntoA.elementos [ConjuntoA.num_elem];
				ConjuntoA.num_elem++;
				
				a_desplazar = ConjuntoA.elementos [ConjuntoA.num_elem - 1];
				for(int i = ConjuntoA.num_elem - 1; ConjuntoA.elementos [i] > a_desplazar; i--){
					ConjuntoA.elementos [i+1] = ConjuntoA.elementos[i];
					posicion = i;
				}
				ConjuntoA.elementos[posicion]	= a_desplazar;
				
				cout << "\nEl conjunto A ahora es: " << "\n\n";
				for(int z = 0; z != ConjuntoA.num_elem; z++)
					cout << ConjuntoA.elementos [z] << " ";
				
				break;
				
			case 'B':
				cout << "\nIntroduzca un elemento: ";
				cin >> ConjuntoB.elementos [ConjuntoB.num_elem];
				ConjuntoB.num_elem++;
				
				a_desplazar = ConjuntoB.elementos [ConjuntoB.num_elem - 1];
				for(int i = ConjuntoB.num_elem - 1; ConjuntoB.elementos [i] > a_desplazar; i--){
					ConjuntoB.elementos [i+1] = ConjuntoB.elementos[i];
					posicion = i;
				}
				ConjuntoB.elementos[posicion]	= a_desplazar;
				
				cout << "\nEl conjunto B ahora es: " << "\n\n";
				for(int z = 0; z != ConjuntoB.num_elem; z++)
					cout << ConjuntoB.elementos [z] << " " ;
				
				break;
		};
		
		cout << "\n\n¿Quieres introducir más elementos(s/n)? ";
		cin >> opcion;
	}while(opcion == 's');
	
	//	Calcular la unión de los dos conjuntos
	
	cout << "\n\nLa unión de los dos conjuntos será: ";
			
	// Calcular la interseccion
	
	cout << "\n\nLa intersección será : " << "\n";
	
	for(int i = 0; i != ConjuntoA.num_elem; i++){
		for(int z = 0; z != ConjuntoA.num_elem; z++){
			if(ConjuntoA.elementos[z] == ConjuntoB.elementos[contador]);
				cout << ConjuntoB.elementos[contador];
		}
		
		contador++;
	}	
	
	cout << "\n\n";
	system ("pause");
}
