/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file main.cpp
 */

#include "../include/Cola_max.h"

using namespace std;

int main(){
	Cola_max<int> cola;
	int i;
	for(i=10; i>=0; i--){
		cola.Insertar(i);
	}
	while(!cola.vacio()){
		elemento<int> x = cola.Front();
		cout << x << endl;
		cola.Eliminar();
	}
	return 0;
}