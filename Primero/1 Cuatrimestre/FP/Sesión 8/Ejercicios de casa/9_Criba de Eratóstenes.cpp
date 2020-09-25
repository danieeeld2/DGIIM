/*	Programa que calcula los números
	primos hasta un natural tope o
	cota superior */
	
#include <iostream>

using namespace std;

int main(){
	const int TOPE = 20;
	int vector_primos [TOPE];
	int  natural_variable;
	int contador;
	int primo_variable;
	bool primera_vez;
	int repeticiones;
	
	natural_variable = 3;
	contador = 0;
	primo_variable = 2;
	repeticiones = 0;
	vector_primos [0] = 2;
	primera_vez = true;
	
	while(primo_variable != TOPE){		
		if(primera_vez){
			for(int i = 1; natural_variable != TOPE; i++){
				if(natural_variable % primo_variable != 0){
					vector_primos [i] = natural_variable;
					contador++;
				}
					
				natural_variable++;
			};
			
			primera_vez = false;
		}
		
		primo_variable++;
		
		for(repeticiones = 0; repeticiones != contador; repeticiones++){
			if(vector_primos[repeticiones] % primo_variable == 0)
				vector_primos[repeticiones] = 0;
		};
		
		repeticiones = 0;
	};
	
	cout << "\nLos números primos hasta el " << TOPE << " son: " << "\n\n";
	
	for(int z = 0; z != contador; z++){
		if(vector_primos[z] != 0)
			cout << vector_primos[z] << " ";
	};
	
	cout << "\n\n";
	system ("pause");
}
