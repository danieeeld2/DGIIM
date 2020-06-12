//
// Created by daniel on 11/6/20.
//

#include "Punto3D.h"

Punto3D::Punto3D() {
    x = 0;
    y = 0;
    z = 0;
}

std::ostream &Punto3D::operator<<(std::ostream &os) {
    os << x << " " << y << " " << z;
    return os;
}

int Punto3D::GetX() {
    return x;
}

int Punto3D::GetY() {
    return y;
}

int Punto3D::GetZ() {
    return z;
}

std::istream &Punto3D::operator>>(std::istream &is) {
    is >> x >> y >> z;
    return is;
}


