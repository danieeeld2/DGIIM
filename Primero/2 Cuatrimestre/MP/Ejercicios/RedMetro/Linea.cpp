//
// Created by daniel on 12/6/20.
//

#include "Linea.h"

int Linea::GetNumParadas() {
    return num_paradas;
}

void Linea::copy(const Linea &orig) {
    allocate(orig.num_paradas);
    for(int i = 0; i < num_paradas; i++)
        paradas[i] = orig.paradas[i];
}

InfoParada Linea::operator[](int i) {
    return paradas[i];
}

void Linea::deallocate() {
    if(paradas != nullptr)
        delete [] paradas;
    paradas = nullptr;
    num_paradas = 0;
}

void Linea::allocate(int a) {
    deallocate();
    if(a > 0){
        num_paradas = a;
        paradas = new InfoParada[a];
    }
}

Linea &Linea::operator=(const Linea &orig) {
    if(this!= &orig)
        copy(orig);
    return *this;
}

Linea &Linea::operator+=(const Linea &orig) {
    Linea aux;
    aux.num_paradas = num_paradas+orig.num_paradas;
    aux.allocate(aux.num_paradas);
    for(int i = 0; i < num_paradas; i++){
        aux.paradas[i] = paradas[i];
    }
    for(int i = num_paradas; i < aux.num_paradas; i++){
        aux.paradas[i] = paradas[i];
    }
    *this = aux;
    aux.deallocate();
    return *this;
}

bool Linea::read(std::istream &is) {
    Linea B;
    is >> B.num_paradas;
    if(is.fail())
        return false;
    B.paradas->read(is);
    if(is.fail())
        return false;
    *this = B;
    B.deallocate();
    return true;
}

std::istream &Linea::operator>>(std::istream &is) {
    read(is);
    return is;
}

void Linea::print(std::ostream &os) {
    os << num_paradas << std::endl;
    for(int i = 0; i < num_paradas; i++){
        paradas[i].print(os);
    }
}
