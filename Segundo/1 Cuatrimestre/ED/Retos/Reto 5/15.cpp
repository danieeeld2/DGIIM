/**
 * @file 15.cpp
 * @author Daniel Alconchel Vázquez
 */

#include <iostream>
#include "bintree.h"

using namespace std;

/**
 * @brief Comprueba si la jerarquía de B está incluida en A
 * @param A bintree
 * @param B bintree
 * @return true en caso afirmativo @else false en caso negativo
 */
bool incluido(bintree<int> &A, bintree<int> &B);
bool cnodes(bintree<int>::node n1, bintree<int>::node n2);


int main(){
    bintree<int> B1(2);
    B1.insert_left(B1.root(), 3);
    B1.insert_right(B1.root(), 4);
    bintree<int> B2(1);
    B2.insert_left(B2.root(), 2);
    B2.insert_left(B2.root().left(), 3);
    B2.insert_right(B2.root().left(), 7);
    bintree<int> B3(1);
    B3.insert_left(B3.root(), 2);
    B3.insert_right(B3.root(), 5);
    B3.insert_left(B3.root().left(), 3);
    B3.insert_right(B3.root().left(), 7);
    bintree<int> B4(9);
    B4.insert_right(B4.root(), 7);
    B4.insert_right(B4.root().right(), 6);
    bintree<int> aux1 = B2;
    bintree<int> aux2 = B3;

    if(incluido(B2, B1))
        cout << "B1 incluido en B2" << endl;
    else 
        cout << "B1 NO está incluido en B2" << endl;
    
    if(incluido(aux2, aux2))
        cout << "B2 incluido en B3" << endl;
    else 
        cout << "B2 NO está incluido en B3" << endl;
    
    if(incluido(B4, B3))
        cout << "B3 incluido en B4" << endl;
    else 
        cout << "B3 NO está incluido en B4" << endl;

    return 0;
}

bool incluido(bintree<int> &A, bintree<int> &B){
    if(B.size() > A.size())
        return false;
    
    bool estado1 = B.root().null();
    bool estado2 = !estado1 && B.root().left().null() && B.root().right().null();
    bool estado3 = !estado1 && !(B.root().left().null()) && B.root().right().null();
    bool estado4 = !estado1 && B.root().left().null() && !(B.root().right().null());
    bool estado5 = !estado1 && !(B.root().left().null()) && !(B.root().right().null());

    if(cnodes(A.root(),B.root()))
        return true;
    else{
        if(estado1 && !(A.root().null()))
            return false;
        bintree<int> aux1,aux2;
        A.prune_left(A.root(),aux1);
        A.prune_right(A.root(),aux2);
        if(estado3){
            if(cnodes(aux1.root(), B.root()))
                return true;
        }
        if(estado4){
            if(cnodes(aux2.root(), B.root()))
                return true;
        }
        if(estado5){
            if(cnodes(aux1.root(), B.root()) || cnodes(aux2.root(), B.root()))
                return true;
        }
    }
    return false; 
}

bool cnodes(bintree<int>::node n1, bintree<int>::node n2){
    bool estado1 = n2.null();
    bool estado2 = !estado1 && n2.left().null() && n2.right().null();
    bool estado3 = !estado1 && !(n2.left().null()) && n2.right().null();
    bool estado4 = !estado1 && n2.left().null() && !(n2.right().null());
    bool estado5 = !estado1 && !(n2.left().null()) && !(n2.right().null());

    if(n1.null() && n2.null())
        return true;
    if(n1.null() || n2.null())
        return false;
    if(estado5){
        if(!cnodes(n1.left(),n2.left()))
            return false;
        if(!cnodes(n1.right(),n1.right()))
            return false;
    }
    if(estado2){
        if(!n1.null())
            return true;
        else 
            return false;
    }
    if(estado3){
        if(!cnodes(n1.left(),n2.left()))
            return false;
    }
    if(estado4){
        if(!cnodes(n1.right(),n1.right()))
            return false;
    }
    return true;
}

