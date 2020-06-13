//
// Created by daniel on 12/6/20.
//

#ifndef UNTITLED_LINEA_H
#define UNTITLED_LINEA_H

#include <iosfwd>
#include "InfoParada.h"

class Linea{
private:
    int num_paradas;
    InfoParada* paradas;
    void copy(const Linea& orig);
    void deallocate();
    void allocate(int a);
    bool read(std::istream& is);
public:
    //...Interfaz
    int GetNumParadas();
    InfoParada operator[](int i);
    Linea& operator=(const Linea& orig);
    Linea& operator+=(const  Linea& orig);
    std::istream & operator>>(std::istream& is);
    void print(std::ostream& os);
};

#endif //UNTITLED_LINEA_H
