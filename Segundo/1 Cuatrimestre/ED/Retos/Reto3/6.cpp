/**
 * @author Daniel Alconchel Vázquez
 * @file Función 6
 **/

#include <iostream>
#include <list>
#include <vector>

using namespace std;

/**
 * @brief Funcion que dice si L es una combinación de las listas de VL
 * @param VL vector de listas
 * @param L lista
 * @return true en caso afirmativo @else false
 **/
bool iscomb(vector<list<int>> VL, list<int> L);

/**
 * @brief Funcion que mira si Lpref es prefijo de L
 * @param Lpref posible prefijo
 * @param L lista
 * @return true en caso afirmativo @else en aso contrario
 **/
bool ispref(list<int> Lpref, list<int> L);

int main(){
    vector<list<int>> VL;
    list<int> L, aux;
    int elem = 0;
    bool retorno;

    cout << "Introduce el vector de listas " << endl;
    while(elem != -1){
        cin >> elem;
        if(elem != -1 && elem != -2)
            aux.push_back(elem);
        if(elem == -2){
            VL.push_back(aux);
            aux.clear();
        }
    }
    elem = 0;
    cout << "Introduce los elementos de la lista " <<endl;
    while(elem != -1){
        cin >> elem;
        if(elem != -1)
            L.push_back(elem);
    }

    retorno = iscomb(VL, L);

    if(retorno)
        cout << "True " << endl;
    else 
        cout << "False" << endl;

    return 0;
};

bool iscomb(vector<list<int>> VL, list<int> L){
    list<int> aux;
    int longitudVL = 0;
    static bool retorno;

    /** Comenzamos mirando si la suma de las longitudes de 
     * VL[j] es igual a la de L
     **/
    for(int i=0; i<VL.size(); i++){
        aux = VL[i];
        longitudVL = longitudVL +aux.size();
    }

    if(longitudVL != L.size())
        return false;

    // Caso base de la recursividad
    if(VL.size() == 1){
        if(VL[0] == L)
            retorno = true;
        else 
            retorno = false;
    }

    for(int i=0; i<VL.size(); i++){
        if(ispref(VL[i], L)){
            for(int j=0; j<VL[i].size(); j++)
                L.pop_front();
            VL.erase(VL.begin()+i);
            iscomb(VL, L);
        }
    }

    return retorno;
}

bool ispref(list<int> Lpref, list<int> L){
    while(!Lpref.empty()){
        if(Lpref.front() != L.front())
            return false;
        else{
            L.pop_front();
            Lpref.pop_front();
        }
    }

    return true;
}