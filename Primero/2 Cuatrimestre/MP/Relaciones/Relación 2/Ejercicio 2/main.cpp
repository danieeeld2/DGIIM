/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 14 de abril de 2020, 15:45
 */

/* Ejercicio 2 Relación 2*/

#include <cstdlib>
#include <iostream>

using namespace std;

void ElevarCuadrado(int *ptrentero);
void PoneraCero(int * ptrentero);

//  Main de prueba

int main(){
    int a = 5;
    int *ptr =&a;
    
    cout << endl << "El valor del puntero es: " << *ptr << " y apunta a la dirección: " << &ptr;
    ElevarCuadrado(ptr);
    cout << endl << "Ahora su valor es: " << *ptr << " y apunta a: " << &ptr;
    PoneraCero(ptr);
    cout << endl << "Ahora su valor es; " << *ptr << " y apunta a: " << &ptr;
    
    return 0;    
}

void ElevarCuadrado(int* ptrentero){
    int a = *ptrentero;
    a = a*a;
    *ptrentero = a;
}

void PoneraCero(int* ptrentero){
    *ptrentero = 0;
}