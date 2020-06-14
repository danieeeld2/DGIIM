/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Frecuencias.h
 * Author: daniel
 *
 * Created on 14 de junio de 2020, 17:35
 */

#ifndef FRECUENCIAS_H
#define FRECUENCIAS_H

#include<iostream>

struct Pareja{
    int dato;
    int nveces;
};
class Frecuencias{
    Pareja *parejas;    //  "npares" datos tipo "Pareja" ordenados por "dato". 0 si no hay parejas
    int npares;
private:
    void deallocate();
    void copy(const Frecuencias& orig);
    void allocate(int n);
    bool DatoEncontrado(int a);
    int PosicionDato(int a);
    void Redimensionar(int a);
public:
    Frecuencias();
    Frecuencias(const Frecuencias& orig);
    ~Frecuencias();
    Frecuencias& operator=(const Frecuencias& orig);
    void add(int a);
    Frecuencias& operator+=(Pareja a);
    friend std::ostream& operator<<(std::ostream& os, const Frecuencias& orig);
    bool read(std::istream& is);
    int Repeticiones(int a);
};

std::ostream& operator<<(std::ostream& os, const Frecuencias& orig);

#endif /* FRECUENCIAS_H */
