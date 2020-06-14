/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Frecuencias.cpp
 * Author: daniel
 * 
 * Created on 14 de junio de 2020, 17:35
 */

#include "Frecuencias.h"

//  Ejercicio 1

Frecuencias::Frecuencias() {
    npares = 0;
    parejas = nullptr;
}

Frecuencias::~Frecuencias() {
    deallocate();
}

void Frecuencias::deallocate() {
    if(parejas != nullptr){
        delete[] parejas;
    }
    parejas = nullptr;
    npares = 0;
}

void Frecuencias::allocate(int n) {
    deallocate();
    if(n > 0){
        npares = n;
        parejas = new Pareja[n];
    }
}


void Frecuencias::copy(const Frecuencias& orig) {
    allocate(orig.npares);
    for(int i = 0; i < npares; i++){
        parejas[i].dato = orig.parejas[i].dato;
        parejas[i].nveces = orig.parejas[i].nveces;
    }
}

Frecuencias::Frecuencias(const Frecuencias& orig) {
    npares = 0;
    parejas = nullptr;
    copy(orig);
}

Frecuencias& Frecuencias::operator=(const Frecuencias& orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

//  Ejercicio 2

bool Frecuencias::DatoEncontrado(int a) {
    for(int i = 0; i < npares; i++){
        if(parejas[i].dato == a)
            return true;
    }
    return false;
}

int Frecuencias::PosicionDato(int a) {
    for(int i = 0; i < npares; i++){
        if(parejas[i].dato == a)
            return i;
    }
    return -1;   //  El dato no está
}

void Frecuencias::Redimensionar(int a) {
    Frecuencias aux(*this); //  Usamos el constructor de copia
    allocate(a);
    copy(aux);  //  Ahora tenemos una posición más reservada    
}


void Frecuencias::add(int a) {
    if(DatoEncontrado(a)){
        parejas[PosicionDato(a)].nveces++;
    }else{
        Redimensionar(npares+1);
        parejas[npares-1].dato = a;
        parejas[npares-1].nveces = 1;
    }
}

//  Ejercicio 4

Frecuencias& Frecuencias::operator+=(Pareja a) {
    add(a.dato);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Frecuencias& orig) {
    os << "Número de Parejas: " << orig.npares << std::endl;
    for(int i = 0; i < orig.npares; i++){
        os << orig.parejas[i].dato << " " << orig.parejas[i].nveces << std::endl;
    }
    return os;
}

bool Frecuencias::read(std::istream& is) {
    is >> npares;
    if(!is){
        return false;
    }
    for(int i = 0; i < npares; i++){
        is >> parejas[i].dato;
        is >> parejas[i].nveces;
        if(!is)
            return false;
    }
    
    return true;
}

//  Ejercicio 6

int Frecuencias::Repeticiones(int a) {
    if(!DatoEncontrado(a)){
        return 0;
    }else{
        return parejas[PosicionDato(a)].nveces;
    }
}
