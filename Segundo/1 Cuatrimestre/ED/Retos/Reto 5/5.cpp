/**
 * @author Daniel Alconchel Vázquez
 * @file Ejercicio 5
 */

#include "bintree.h"
#include <iostream>

using namespace std;

/**
 * @brief Devuelve cuántos nodos de T tienen exactamente un solo hijo
 * 
 * @param T bintree
 * @return El número de nodos con un solo hijo
 */
int onechild(bintree<int> &T);

int main(){
    bintree<int> T(1);
    T.insert_right(T.root(),2);
    T.insert_left(T.root().right(), 3);
    T.insert_right(T.root().right(), 4);
    bintree<int> T2(1);
    T2.insert_left(T2.root(), 2);
    T2.insert_right(T2.root().left(), 3);
    bintree<int> T3(1);
    T3.insert_left(T3.root(), 2);
    T3.insert_right(T3.root(), 3);
    T3.insert_left(T3.root().left(), 4);
    T3.insert_right(T3.root().left(), 5);
    bintree<int> T4(1);
    T4.insert_left(T4.root(), 2);
    T4.insert_right(T4.root(), 3);
    T4.insert_left(T4.root().left(), 4);
    T4.insert_right(T4.root().left(), 5);
    T4.insert_left(T4.root().right(),6);

    for(auto b = T.begin_preorder(); b != T.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;
    cout << "El número de nodos con un solo hijo es: " << onechild(T) << endl;

    for(auto b = T2.begin_preorder(); b != T2.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;
    cout << "El número de nodos con un solo hijo es: " << onechild(T2) << endl;

    for(auto b = T3.begin_preorder(); b != T3.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;
    cout << "El número de nodos con un solo hijo es: " << onechild(T3) << endl;

    for(auto b = T4.begin_preorder(); b != T4.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;
    cout << "El número de nodos con un solo hijo es: " << onechild(T4) << endl;

    return 0;
}

int onechild(bintree<int> &T){
    static int contador=0;
    if(T.root().left().null() && !(T.root().right().null())){
        contador++;
    }else if (!(T.root().left().null()) && T.root().right().null()){
        contador++;
    }else{
        bintree<int> aux1, aux2;
        T.prune_left(T.root(),aux1);
        T.prune_right(T.root(),aux2);
        if(T.size() <= 1)
            return 0;
        
        contador = onechild(aux1) + onechild(aux2);
    }

    return contador;
}