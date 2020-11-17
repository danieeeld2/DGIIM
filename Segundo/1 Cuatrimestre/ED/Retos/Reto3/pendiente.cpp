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

}

bool nullsum(list<int> &L, list<int> &L2){
    int suma = 0;
    list<int> aux;

    aux = L;
    L.sort();
    if(L.front() > 0)
        return false;

    for(int i=0; i<aux.size(); ++i){
        if(aux.front() == 0){
            return true;
            L2.push_back(0);
        }
        aux.pop_front();
    }

    L = aux;

    
}