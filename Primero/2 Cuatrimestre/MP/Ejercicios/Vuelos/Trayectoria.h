//
// Created by daniel on 11/6/20.
//

#ifndef UNTITLED_TRAYECTORIA_H
#define UNTITLED_TRAYECTORIA_H
#include "Punto3D.h"
#include <cmath>
#include <cassert>


class Trayectoria {
private:
    Punto3D *puntos;
    int numeroPuntos;
public:
    Trayectoria();
    ~Trayectoria();
    void deallocate();
    void allocate(int a);
    void copy(const Trayectoria& orig);
    Trayectoria(Punto3D*p, int n);
    Trayectoria& operator=(const Trayectoria& orig);
    int GetNum();
    Punto3D GetPos(int a);
    void Set(int a, Punto3D p);
    double CalcularLongitud(int pos);
    bool read(std::istream& is);
    std::istream& operator>>(std::istream & is);
    double CalcularLongitud2pt(Punto3D p,int pos);
};


#endif //UNTITLED_TRAYECTORIA_H
