/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Ejercicio 1

#include <iostream>

struct Celda{
    double dato;
    Celda* sig;
};

int main(){
    Celda* lista;
    double valor;
    
    lista = nullptr;
    std::cin >> valor;
    Celda* aux = new Celda;
    
    //  Creación de lista
    while(valor != 0.0){
        Celda* aux = new Celda;
        aux->dato = valor;
        aux->sig = lista;
        lista = aux;
        std::cin >> valor;
    };
    
    //  Mostrar elementos
    aux = lista;
    while(aux!=0){
        std::cout << aux->dato << " ";
        aux = aux->sig;
    }
    std:: cout << std:: endl;
    
    //  Destrucción de la lista
    while(lista != 0){
        Celda*aux = lista;
        lista = aux->sig;
        delete aux;
    }
    
    return 0;
}