/**
 * @author Daniel Alconchel Vázquez
 * @file Función 8
 **/

#include <iostream>
#include <list>

using namespace std;

/**
 * @brief Función que dice si existe un rango de valores continuos, [p,q), tal que
 * la suma de los elementos del rango sea 0
 * @param L lista de enteros
 * @param L2 una de las posibles soluciones
 * @return true en caso de que exista dicho rango @else devuelve false
 **/
bool nullsum(list<int> &L, list<int> &L2);

int main(){
	list<int> L;
	list<int> L2;
	string aux;
	bool encontrado;

	cout << "Introduce los elementos de la lista" << endl;
	do{
		cin >> aux;
		if(aux != "@")
			L.push_back(stoi(aux));
	}while(aux != "@");

	encontrado = nullsum(L, L2);

	if(encontrado){
		cout << "Se ha encontrado un rango de la lista cuya suma es 0" << endl;
		while(L2.size() != 0){
			cout << L2.front() << " ";
			L2.pop_front();
		}
		cout << endl;
	}
	else{
		cout << "No se ha encontrado un rango de la lista cuya suma sea 0" << endl;
	}

	return 0;
}

bool nullsum(list<int> &L, list<int> &L2){
    int suma = 0;
    bool encontrado = false;
    list<int> aux;
    int cont = 0;
   	
   	while((L.size() != 0) && (!encontrado)){
   		suma = L.front();
                if(L.front() == 0){
                    L2.push_back(0);
                    return true;
                }
                aux = L;
   		aux.pop_front();

   		while((aux.size() != 0) && (!encontrado)){
   			suma = suma + aux.front();;
   			aux.pop_front();
   			if(suma == 0)
   				encontrado = true;
   			cont++;
   		}

   		if(encontrado){
   			for(int i=0; i<(cont+1); i++){
   				L2.push_back(L.front());
   				L.pop_front();
   			}
   		}
   		else{
   			cont = 0;
   			L.pop_front();
		}
   	}

   	return encontrado;
    
}