#include<iostream>
#include<vector>
#include<list>
#include "bintree.h"

using namespace std;

// Sirve para deshacer el arbol en parejas de nivel y nodo
vector<pair<int,bintree<int>::node>> niveles(bintree<int>::node n, int lev){          
    static vector<pair<int,bintree<int>::node>> retorno;
    pair<int,bintree<int>::node> aux;

    if(!n.null()){
        aux.first = lev;
        aux.second = n;
        retorno.push_back(aux);
        niveles(n.right(), lev+1);
        niveles(n.left(), lev+1);
    }

    return retorno;
}

vector<list<int>> caminos(bintree<int>::node n){    // Falta arreglar esta funcion
    static vector<list<int>> retorno;
    list<int> aux;
    
    aux.push_back(*n);
    if(n.right().null() && n.left().null())
        if(aux.size()>=1)
            retorno.push_back(aux);
    else{
        caminos(n.right());
        caminos(n.left());
    }

    return retorno;
}

vector<list<int>> secuenciascaminos(bintree<int> A, int level){
    vector<list<int>> aux3;
    vector<list<int>> retorno;
    // Deshacemos el arbol en parejas de nivel y nodo
    vector<pair<int,bintree<int>::node>> aux = niveles(A.root(), 0);
    for(int i=0; i<aux.size(); ++i){
        if(aux[i].first == level){
           aux3 = caminos(aux[i].second);  // Calculamos todos los caminos a las hojas dado un nodo
        } 
        for(int j=0; j<aux3.size(); ++j){
            list<int> aux2 = aux3[j];
            retorno.push_back(aux2);    
        }
    }

    return retorno;
}



int main(){
    bintree<int> A(1);
    A.insert_left(A.root(), 4);
    A.insert_right(A.root(), 7);
    A.insert_left(A.root().left(), 8);
    A.insert_right(A.root().left(), 9);
    A.insert_left(A.root().right(), 11);
    A.insert_right(A.root().right(), 10);
    A.insert_left(A.root().left().right(), 6);
    A.insert_right(A.root().right().left(), 14);
    
    vector<list<int>> aux = secuenciascaminos(A, 3);
    for(int i=0; i<aux.size(); ++i){
        for (auto it=aux[i].begin(); it!=aux[i].end(); ++it)
            cout << *it << ",";
        cout << endl;
    }

    return 0;
}