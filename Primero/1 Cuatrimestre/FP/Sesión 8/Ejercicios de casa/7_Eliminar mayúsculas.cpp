/*	Programa que elimina las mayúsculas
	de un vector de caractéres */
	
#include <iostream>

using namespace std;

int main(){
	char vector1 [5];
	char vector2 [5];
	bool condicion_de_copia;
	
	cout << "Introduce las componentes del vector: ";
	
	for(int i = 0; i!=5; i++)
		cin >> vector1 [i];
		
	for(int j = 0; j!=5; j++){
		condicion_de_copia = vector1 [j] >= 'A' && vector1 [j] <= 'Z';
		
		if(!condicion_de_copia)
			vector2 [j] = vector1 [j];
	};
	
	cout << "\nEl vector original es: " << "\n\n";
	
	for(int z = 0; z!=5; z++)
		cout << vector1 [z];
		
	cout << "\nEl vector sin mayúsculas: " << "\n\n";
	
	for(int y = 0; y!=5; y++)
		cout << vector2 [y];
		
	cout << "\n\n";
	system ("pause");
}
