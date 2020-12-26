/**
 * @file 6.cpp
 * @author Daniel Alconchel Vázquez 
 */

#include <iostream>
#include "bintree.h"

using namespace std;

/**
 * @brief Comprueba si un árbol es recurrente.
 * Se considera que un árbol es recurrente si es completo y la suma de 
 * los hijos de un nodo interior es el valor del propio nodo
 * 
 * @param T bintree
 * @return true en caso afirmativo @else devuelve false
 */
bool is_recurrent_tree(bintree<int> &T);
/**
 * @brief Comprueba si un árbol es completo
 * 
 * @param T bintree
 * @return true en caso afirmativo @else devuelve false
 */
bool is_complete(bintree<int> &T);
/**
 * @brief Comprueba si la suma de los valores de los hijos es
 * igual a la del nodo
 * 
 * @param T bintree
 * @return true en caso afirmativo @else devuelve false
 */
bool int_sum(bintree<int> &T);

int main(){
    bintree<int> T1(12);
    T1.insert_left(T1.root(), 5);
    T1.insert_right(T1.root(), 7);
    T1.insert_left(T1.root().right(), 3);
    T1.insert_right(T1.root().right(), 4);
    bintree<int> T2(8);
    T2.insert_left(T2.root(), 7);
    T2.insert_right(T2.root(), 2);
    T2.insert_left(T2.root().left(), 4);
    T2.insert_right(T2.root().left(), 3);
    bintree<int> T3(12);
    T3.insert_left(T3.root(), 9);
    T3.insert_right(T3.root(), 3);
    T3.insert_left(T3.root().left(), 4);
    T3.insert_right(T3.root().left(), 5);
    T3.insert_left(T3.root().right(), 8);
    T3.insert_right(T3.root().right(), 7);

    if(is_recurrent_tree(T1)){
        cout << "El árbol T1 es recurrente" << endl;
    }else{
        cout << "El árbol T1 NO es recurrente" << endl;
    }
    if(is_recurrent_tree(T2)){
        cout << "El árbol T2 es recurrente" << endl;
    }else{
        cout << "El árbol T2 NO es recurrente" << endl;
    }
    if(is_recurrent_tree(T3)){
        cout << "El árbol T3 es recurrente" << endl;
    }else{
        cout << "El árbol T3 NO es recurrente" << endl;
    }

    return 0;
}

bool is_recurrent_tree(bintree<int> &T){
    if(int_sum(T) && is_complete(T))
        return true;
    else 
        return false;
}

bool is_complete(bintree<int> &T){
    if(T.root().null() || T.empty())
        return true;
    if(T.root().right().null() && T.root().left().null())
        return true;
    else{
        if(T.root().left().null() && !(T.root().right().null()))
            return false;
        else{
            bintree<int> aux1, aux2;
            T.prune_left(T.root(), aux1);
            T.prune_right(T.root(), aux2);
            return is_complete(aux1) && is_complete(aux2);
        }
    }
}

bool int_sum(bintree<int> &T){
    if(T.root().null() || T.empty())
        return true;
    if(T.root().right().null() && T.root().left().null())
        return true;
    else {
        if(!(T.root().right().null()) && T.root().left().null()){
            if(*(T.root()) == *(T.root().right()))
                return true;
            else
                return false;
        }
        if(T.root().right().null() && !(T.root().left().null())){
            if(*(T.root()) == *(T.root().left()))
                return true;
            else 
                return false;
        }
        if(*(T.root()) == *(T.root().right()) + *(T.root().left())){
            bintree<int> aux1,aux2;
            T.prune_left(T.root(),aux1);
            T.prune_right(T.root(),aux2);
            return int_sum(aux1)&&int_sum(aux2);
        }else
        return false;
    }
}