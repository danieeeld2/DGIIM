/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Skyline.h
 * Author: daniel
 *
 * Created on 14 de junio de 2020, 19:47
 */

#ifndef SKYLINE_H
#define SKYLINE_H

#include <ostream>


class SkyLine{
    double *abcisas;    //  abcisas[i] > abcissas[i-1]
    double *alturas;    //  alturas[i] >=0 && alturas[n-1] == 0
    int n;  //  tamaño de los vectores anteriores;
private:
    void deallocate();
    void allocate(int a);
    void copy(const SkyLine& orig);
    bool AbcisaEncontrada(double abcisas);
    int PosAbcisa(double abcisas);
public:
    SkyLine();
    SkyLine(double a, double b, double c);
    SkyLine(const SkyLine& orig);
    ~SkyLine();
    void redimensionar (int a);
    SkyLine& operator=(const SkyLine& orig);
    double Altura(double abcisas);
    SkyLine& operator+(const SkyLine& orig);
    bool read(std::istream& is);
    void print(std::ostream& os);
    friend std::ostream& operator<<(std::ostream& os, SkyLine& p);
    friend std::istream& operator>>(std::istream& is, SkyLine& p);
    void Cargar(std::string ifilename);
    void Salvar(std::string ifilename);
    void add(double a, double b, double c);
    inline double GetNumeroPuntos() const{return n;};
    
};

std::ostream& operator<<(std::ostream& os, SkyLine& p);
std::istream& operator>>(std::istream& is, SkyLine& p);

#endif /* SKYLINE_H */
