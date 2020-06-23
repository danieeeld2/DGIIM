/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 22 de junio de 2020, 9:04
 */

#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    int numeros[8];
    int maximo = 0;
    
    for(int i = 0; i < 8; i++){
        do{
            cout << endl << "Introduce un número positivo entre 15 y 250 ";
            cin >> numeros[i];
        }while(numeros[i] < 15 || numeros[i] > 250);
    }
    
    for(int i = 0; i < 8; i++){
        if(numeros[i] > maximo)
            maximo = numeros[i];
    }
    
    cout << endl << "El máximo es: ";
    
    cout << endl << "Los múltiplos de 5 son :";
    for(int i = 0; i < 8; i++){
        if(numeros[i]%5 == 0)
            cout << endl << numeros[i];
    }
    
    cout << endl;
    return 0;
}

/*
 * 
 */
