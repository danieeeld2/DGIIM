//
// Created by daniel on 11/6/20.
//

#ifndef UNTITLED_VUELO_H
#define UNTITLED_VUELO_H
#include "Punto3D.h"
#include "Trayectoria.h"
#include <iostream>
#include <string>
#include <fstream>


class Vuelo {
private:
    int idVuelo;
    Trayectoria rutaOptima;
    Trayectoria rutaReal;
    void copy(const Vuelo& orig);
    void add(const Punto3D& p);
    bool read(std::istream& is);
public:
    Vuelo();
    Vuelo(const Vuelo& orig);
    Vuelo(std::string ifilename);
    Vuelo(int i, Trayectoria opt);
    Vuelo& operator=(const Vuelo& orig);
    Vuelo& operator+=(const Punto3D& p);
    std::ostream& operator<<(std::ostream& os);
    double CalcularLongitudOptima();
    double CalcularLongitudReal();
    std::istream& operator>>(std::istream& is);
    double calcularDistanciaMediaTrayectorias();
    bool operator<(Vuelo& vuelo);
    int GetID();
    void print(std::ostream& os);
};


#endif //UNTITLED_VUELO_H
