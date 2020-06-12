//
// Created by daniel on 11/6/20.
//

#ifndef UNTITLED_PUNTO3D_H
#define UNTITLED_PUNTO3D_H
#include <iostream>


class Punto3D {
private:
    double x,y,z;
public:
    Punto3D();
    Punto3D& operator+=(const Punto3D& orig);
    std::ostream& operator<<(std::ostream& os);
    int GetX();
    int GetY();
    int GetZ();
    std::istream& operator>>(std::istream& is);
};


#endif //UNTITLED_PUNTO3D_H
