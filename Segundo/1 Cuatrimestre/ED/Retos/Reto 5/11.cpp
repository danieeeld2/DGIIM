/**
 * @file 11.cpp
 * @author Daniel Alconchel Vázquez * 
 */

#include<iostream>
#include "bintree.h"

using namespace std;

/**
 * @brief Calcula el número de nodos de un árbol binario cuya etiqueta es 
 * exáctamente igual al valor k 
 * @param A bintree
 * @param k valor a comparar
 * @return int número de etiquetas
 */
int nodos_k(bintree<int> &A, int k);

int main(){
    bintree<int> A(1);
    A.insert_left(A.root(), 2);
    A.insert_right(A.root(), 3);
    A.insert_left(A.root().left(), 2);
    A.insert_right(A.root().right(), 2);

    for(auto b = A.begin_preorder(); b != A.end_preorder(); ++b)
        cout << *b << " ";
    cout << endl;
    cout << "El número 2 se repite " << nodos_k(A,2) << " veces" << endl;

    return 0;
}

int nodos_k(bintree<int> &A, int k){
    int contador = 0;
    for(auto b = A.begin_preorder(); b != A.end_preorder(); ++b)
        if(*b == k)
            contador++;
    return contador;
}