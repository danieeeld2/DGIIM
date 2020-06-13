//
// Created by daniel on 12/6/20.
//

#ifndef UNTITLED_INFOPARADA_H
#define UNTITLED_INFOPARADA_H

#include <iosfwd>
#include <iostream>

class InfoParada{
private:
    bool activa;
    int indice_parada;
public:
    //...Interfaz
    int GetIndice();
    bool EstaActiva();
    bool read(std::istream& is);
    void print(std::ostream& os);
};
#endif //UNTITLED_INFOPARADA_H
