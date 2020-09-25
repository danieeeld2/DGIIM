/*	Programa para realizar una 
	permutación como función biyectiva
	de 1,...,n en 1,...,n */
	
#include<iostream>

using namespace std;

struct Permutacion{
	const int LONGITUDN = 10;
	int vector_enteros [LONGITUDN];
	int longitud_utilizada;
};

int main(){
	Permutacion Datos;
	Permutacion Entrada;
	bool permutacion_valida;
	int contador;
	
	do{
		cout << "Introduzca el número de enteros (MÁXIMO " << LONGITUDN << ") :"
		cin >> Datos.longitud_utilizada;
	}while(Datos.longitud_utilizada > LONGITUDN)

	cout << "\nSu dominio sería: " << "\n";
	
	for(int i = 0; i != longitud_utilizada; i++){
		Datos.vector_enteros [i] =  i;
		cout << Datos.vector_enteros[i] << " ";
	}
	
	cout << "\n\nRealice una permutación : ";	
	
	for(int z = 0; z != longitud_utilizada; z++)
		cin >> Entrada.vector_enteros[z];
		
	contador = 0;
	
	for(int j = 0; j != longitud_utilizada; j++){
		for(int x = 0; x != longitud_utilizada; x++){
			if(Datos.vector_enteros[j] == Entrada.vector_enteros[z]
				contador++;
		}
	}
	
	permutacion_valida = contador == Entrada.longitud_utilizada;
	
	if(permutacion_valida)
		cout << "\n\nLa permutación es válida ";
	else
		cout << "\n\nLa permutación no es válida ";
		
	cout << "\n\n";
	system ("pause");
}
