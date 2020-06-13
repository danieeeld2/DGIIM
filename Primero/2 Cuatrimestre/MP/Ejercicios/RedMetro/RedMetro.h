//
// Created by daniel on 12/6/20.
//

#ifndef UNTITLED_REDMETRO_H
#define UNTITLED_REDMETRO_H

#include <iosfwd>
#include <fstream>
#include "Linea.h"

class RedMetro{
private:
    int num_lineas;
    Linea* lineas;
    void deallocate();
    void copy(const RedMetro& orig);
    void allocate(int a);
    bool read(std::istream& is);
    void print(std::ostream& os);
public:
    //...Interfaz
    RedMetro();
    ~RedMetro();
    RedMetro(const RedMetro& orig);
    RedMetro(std::string ifilename);
    int GetNumLineas();
    int GetNumeroTotalParadas();
    const Linea operator[](int i) const;
    bool EstaVacia();
    RedMetro& operator=(const RedMetro& orig);
    RedMetro& operator+=(const RedMetro& orig);
    std::istream & operator>>(std::istream& is);
    std::ostream & operator<<(std::ostream& os);
    bool operator==(const RedMetro& red);
    bool operator!=(const RedMetro& red);
    bool operator>(const RedMetro& red);
    Linea MejorConectada();
    bool EstaTotalmenteOperativa(int nl);
};
#endif //UNTITLED_REDMETRO_H
