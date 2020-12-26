/**
 * @file 3.cpp
 * @author Daniel Alconchel Vázquez 
 */

#include "bintree.h"
#include <iostream>

using namespace std;

/**
 * @brief Comprueba si un árbol binario es inferior a otro
 * @param ab1 bintree
 * @param ab2 bintree
 * 
 * @return true si el primero es menor que el segundo @else devuelve false
 * @warning Para que sean comparables deben tener la misma ramificación
 */
bool es_inferior(bintree<int> &ab1, bintree<int> &ab2);

int main(){
    bintree<int> T1(1);
    T1.insert_right(T1.root(),2);
    T1.insert_left(T1.root().right(), 3);
    T1.insert_right(T1.root().right(), 4);

    bintree<int> T2(2);
    T2.insert_right(T2.root(),3);
    T2.insert_left(T2.root().right(), 4);
    T2.insert_right(T2.root().right(), 5);

    cout << "Bintree 1: ";
    for(auto b = T1.begin_preorder(); b != T1.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;
    cout << "Bintree 2: ";
    for(auto b = T2.begin_preorder(); b != T2.end_preorder(); ++b){
        cout << *b << " ";
    }
    cout << endl;

    if(es_inferior(T1, T2))
        cout << "T1 es inferior a T2 " << endl;
    else 
        cout << "T1 NO es inferior a T2 " << endl;

    return 0;
}

bool es_inferior(bintree<int> &ab1, bintree<int> &ab2){
    auto it2 = ab2.begin_preorder();
    for(auto it1 = ab1.begin_preorder(); it1 != ab1.end_preorder(); ++it1){
        if(*it2 < *it1)
            return false;
        ++it2;
    }

    return true;
}