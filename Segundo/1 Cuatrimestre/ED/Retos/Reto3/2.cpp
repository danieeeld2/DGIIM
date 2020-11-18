/**
 * @author Daniel Alconchel Vázquez
 * @file Función 2
 **/

#include <iostream>
#include <list>

using namespace std;

/**
 * @brief Función que calcula si los elementos de la lista L están
 * contenidos en una y sólo una de las listas de LL
 * @param LL lista de listas de enteros
 * @param L lista de enteros
 * @return true en caso afirmativo @else false
 **/
bool contenido(list<list<int>> LL, list<int> L);

int main(){
    list<list<int>> LL;
    list<int> L;
    list<int> aux;
    string elem;
    bool retorno;

    cout << "Introduce la lista de listas: " << endl;
    cout << "Itroduce & para indicar fin de una lista e introduce @ para indicar fin de la lista de listas" << endl;
    do{
        cin >> elem;
        if(elem != "@" && elem != "&")
            aux.push_back(stoi(elem));
        if(elem == "&"){
            LL.push_back(aux);
            aux.clear();
        }
    }while(elem != "@");
    
    cout << "Introduce la sublista: " << endl;
    cout << "Introduce @ para fin de la lista" << endl;    
    do{
        cin >> elem;
        if(elem != "@")
            L.push_back(stoi(elem));
    }while(elem != "@");
    
    retorno = contenido(LL, L);

    if(retorno)
        cout << "true" << endl;
    else 
        cout << "false" << endl;

    return 0;
};

bool contenido(list<list<int>> LL, list<int> L){
    list<list<int>> aux;
    list<int> aux1, aux2;
    int contador = 0;
    
    aux1=L;
    aux=LL;
    
    while(!aux1.empty()){
        int elem = aux1.front();
        
        for(int i=0; i<LL.size(); i++){
            aux2 = aux.front();
            
            for(int j=0; aux2.size(); j++){
                int elem2 = aux2.front();
                if(elem2 == elem)
                    contador++;
                aux2.pop_front();
            }
            if(contador>1)
                return false;
            aux.pop_front();
        }
        
        if(contador == 0)
            return false;
        contador = 0;
        aux = LL;
        aux1.pop_front();
    }
    
    return true;    
}