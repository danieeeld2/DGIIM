/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Skyline.cpp
 * Author: daniel
 * 
 * Created on 14 de junio de 2020, 19:47
 */

#include <fstream>
#include <iostream>

#include "Skyline.h"

//  Ehercicio 1

void SkyLine::deallocate() {
    if (abcisas != nullptr)
        delete[] abcisas;
    if (alturas != nullptr)
        delete[] alturas;
    abcisas = nullptr;
    alturas = nullptr;
    n = 0;
}

SkyLine::SkyLine() {
    abcisas = nullptr;
    alturas = nullptr;
    n = 0;
}

SkyLine::~SkyLine() {
    deallocate();
}

void SkyLine::allocate(int a) {
    deallocate();
    if (a > 0) {
        n = a;
        alturas = new double[n];
        abcisas = new double[n];
    }
}

void SkyLine::copy(const SkyLine& orig) {
    allocate(orig.n);
    for(int i = 0; i < n; i++){
        abcisas[i] = orig.abcisas[i];
        alturas[i] = orig.alturas[i];
    }
}


void SkyLine::redimensionar(int a) {
    SkyLine aux;
    aux.copy(*this);
    allocate(n+a);
    for(int i = 0; i < aux.n; i++){
        abcisas[i] = aux.abcisas[i];
        alturas[i] = aux.alturas[i];
    }
}

SkyLine::SkyLine(double a, double b, double c) {
    allocate(2);
    abcisas[0] = a;
    abcisas[1] = b;
    alturas[0] = c;
    alturas[1] = c;
}

SkyLine::SkyLine(const SkyLine& orig) {
    copy(orig);
}

SkyLine& SkyLine::operator=(const SkyLine& orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

//  Ejercicio 2

bool SkyLine::AbcisaEncontrada(double abcisas) {
    for(int i = 0; i < n; i++){
        if( abcisas[i] == abcisas)
            return true;
    }
    return false;
}

int SkyLine::PosAbcisa(double abcisas) {
    for(int i = 0; i < n; i++){
        if(abcisas[i] == abcisas)
            return i;
    }
    return -1;  //  No esta la abcisa
}

double SkyLine::Altura(double abcisas) {
    if(AbcisaEncontrada(abcisas))
        return alturas[PosAbcisa(abcisas)];
    else
        return 0;
}

//  Ejercicio 3

SkyLine& SkyLine::operator+(const SkyLine& orig) {
    //  Pendiente
}

void SkyLine::print(std::ostream& os) {
    os << n << std::endl;
    for(int i = 0; i < n; i++){
        os << abcisas[i] << "," << alturas[i] << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, SkyLine& p) {
    p.print(os);
    return os;
}

bool SkyLine::read(std::istream& is) {
    is >> n;
    if(!is)
        return false;
    allocate(n);
    for(int i = 0; i < n; i++){
        is >> abcisas[i];
        is >> alturas[i];
        if(!is)
            return false;
    }
    return true;
}

std::istream& operator>>(std::istream& is, SkyLine& p) {
    p.read(is);
    return is;
}

//  Ejercicio 5

void SkyLine::Cargar(std::string ifilename) {
    std::ifstream ifile;
    ifile.open(ifilename);
    if(ifile.fail()){
        std::cerr << "Error de apertura del fichero";
        exit(1);
    }
    ifile >> *this;
    ifile.close();
}

void SkyLine::Salvar(std::string ifilename) {
    std::ofstream ifile;
    ifile.open(ifilename);
    if(ifile.fail()){
        std::cerr << "Error en la apertura del fichero";
        exit(1);
    }
    ifile << *this;
    ifile.close();
}

void SkyLine::add(double a, double b, double c) {
    redimensionar(n+2);
    abcisas[n-2] = a;
    abcisas[n-1] = b;
    alturas[n-2] = c;
    alturas[n-1] = c;
}
