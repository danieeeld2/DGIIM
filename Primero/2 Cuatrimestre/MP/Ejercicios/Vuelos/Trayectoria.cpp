//
// Created by daniel on 11/6/20.
//

#include "Trayectoria.h"

Trayectoria::Trayectoria() {
    puntos = nullptr;
    numeroPuntos = 0;
}

Trayectoria::~Trayectoria() {
    deallocate();
}

void Trayectoria::deallocate() {
    if(puntos != nullptr)
        delete [] puntos;
    numeroPuntos = 0;
    puntos = nullptr;
}

void Trayectoria::allocate(int a) {
    deallocate();
    puntos = new Punto3D[a];
    numeroPuntos = a;
}

void Trayectoria::copy(const Trayectoria &orig) {
    deallocate();
    allocate(orig.numeroPuntos);
    numeroPuntos = orig.numeroPuntos;
    for(int i = 0; i < numeroPuntos; i++)
        puntos[i] = orig.puntos[i];
}

Trayectoria &Trayectoria::operator=(const Trayectoria &orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

Trayectoria::Trayectoria(Punto3D *p, int n) {
    numeroPuntos = n;
    for(int i = 0; i < n; i++){
        puntos[i] = p[i];
    }
}

int Trayectoria::GetNum() {
    return numeroPuntos;
}

void Trayectoria::Set(int a, Punto3D p) {
    puntos[a] = p;
}

Punto3D Trayectoria::GetPos(int a) {
    return puntos[a];
}

double Trayectoria::CalcularLongitud(int pos) {
    double a;
    double x,y,z;
    assert(pos>=0 && pos < numeroPuntos);
    x = puntos[pos].GetX()-puntos[pos+1].GetX();
    y = puntos[pos].GetY()-puntos[pos+1].GetY();
    z = puntos[pos].GetZ()-puntos[pos+1].GetZ();
    a = sqrt(x*x+y*y+z*z);
    return a;
}

bool Trayectoria::read(std::istream &is) {
    int n;
    Punto3D a;
    if(is.fail())
        return false;
    is >> n;
    if(is.eof())
        return false;
    numeroPuntos = n;
    allocate(n);
    for(int i = 0; i < n; i++){
        a.operator>>(is);
        if(!is.eof())
            return false;
        puntos[i] = a;
    }
    return true;
}

std::istream &Trayectoria::operator>>(std::istream &is) {
    read(is);
    return is;
}

double Trayectoria::CalcularLongitud2pt(Punto3D p, int pos) {
    Punto3D a;
    a = GetPos(pos);
    double x = a.GetX()-p.GetX();
    double y = a.GetY()-p.GetY();
    double z = a.GetZ()-p.GetZ();
    double b = sqrt(x*x+y*y+z*z);
    return b;
}




