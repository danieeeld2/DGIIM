//
// Created by daniel on 12/6/20.
//

#include "InfoParada.h"

int InfoParada::GetIndice() {
    return indice_parada;
}

bool InfoParada::EstaActiva() {
    return activa;
}

bool InfoParada::read(std::istream &is) {
    bool ac;
    int n;

    is >>  ac;
    if(is.fail())
        return false;
    is >> n;
    if(is.fail())
        return false;
    activa = ac;
    indice_parada = n;
    return true;
}

void InfoParada::print(std::ostream &os) {
    os << indice_parada << " ";
    if(activa)
        os << 'S';
    else
        os << 'N';
}

