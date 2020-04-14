/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 14 de abril de 2020, 16:22
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
int main() {
    int v[10] ={1,3,4,2,3,4,8,9,2,1};
    int *ptr;   //  Apunta a la poición 0;
    int maximo;
    int minimo;
    bool primeravez = true;
    
    ptr = v;    //  Aounta a la posición 0 de v
    
    for(int i=0; i!=9; i++ ){
        if(primeravez){
            primeravez = false;
            maximo = *ptr;
            minimo = *ptr;
        }
        
        *(ptr++);
        
        if(*ptr > maximo)
            maximo = *ptr;
        if(*ptr < minimo)
            minimo = *ptr;
    }
    
    cout << endl << "Maximo: " << maximo << endl << "Minimo: " << minimo;
    
    return 0;
}

