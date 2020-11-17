/**
 * @author Daniel Alconchel Vázquez
 * @file Función 14
 **/

#include <iostream>
#include <stack>
#include <list>

using namespace std;

/**
 * @brief Función que toma un elemento n de la pila S y, si es 
 * positivo, saca n elementos de L y los remplaza por  su suma
 * @param L lista de enteros
 * @param S pila de enteros
 **/
void compacta(list<int> &L, stack<int> &S);

int main(){
    list<int> L;
    stack<int> S;
    string elem = "0";

    cout << "Introduce una lista de enteros: " << endl;
    while(elem != "@"){
        cin >> elem;
        if(elem != "@")
            L.push_back(stoi(elem));
    }
    cout << "Introduce una pila de enteros: " << endl;
    elem = "0";
    while(elem != "@"){
        cin >> elem;
        if(elem != "@")
            S.push(stoi(elem));
    }

    compacta(L,S);
    
    cout << "La lista resultante es: " << endl;
    while(!L.empty()){
        cout << L.front() << " ";
        L.pop_front();
    }
    cout << endl;
    cout << "La pila resultante es: " << endl;
    while(!S.empty()){
        cout << S.top() << " ";
        S.pop();
    }

    return 0;
}

void compacta(list<int> &L, stack<int> &S){
    list<int> aux;
    stack<int> aux1;
    int elem;
    int suma = 0;

    // Reordenamos la pila
    while(!S.empty()){
        aux1.push(S.top());
        S.pop();
    }

    while(!L.empty() && !aux1.empty()){
        elem = aux1.top();
        if(elem > 0){
            for(int i=0; (i<elem)&&(!L.empty()); i++){
                suma = suma + L.front();
                L.pop_front();
            }
            aux.push_back(suma);
            suma = 0;
        }
        aux1.pop();
    }

    while(!L.empty()){
        aux.push_back(L.front());
        L.pop_front();
    }

    L.clear();
    L = aux;
    S = aux1;
}