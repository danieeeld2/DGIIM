//
// Created by daniel on 12/6/20.
//

#include "RedMetro.h"

int RedMetro::GetNumLineas() {
    return num_lineas;
}

int RedMetro::GetNumeroTotalParadas() {
    int a;
    for(int i = 0; i < num_lineas; i++){
        a = lineas[i].GetNumParadas()+a;
    }
    return a;
}

const Linea RedMetro::operator[](int i) const {
    return lineas[i];
}

RedMetro::RedMetro() {
    num_lineas = 0;
    lineas = nullptr;
}

RedMetro::~RedMetro() {
    deallocate();
}

void RedMetro::deallocate() {
    if(lineas != nullptr)
        delete [] lineas;
    lineas = nullptr;
    num_lineas = 0;
}

bool RedMetro::EstaVacia() {
    bool estavacia = false;
    if(num_lineas == 0)
        estavacia = true;
    return estavacia;
}

void RedMetro::copy(const RedMetro &orig) {
    deallocate();
    allocate(orig.num_lineas);
    for(int i = 0; i < num_lineas; i++)
        lineas[i] = orig.lineas[i];
}

RedMetro &RedMetro::operator=(const RedMetro &orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

void RedMetro::allocate(int a) {
    deallocate();
    if(a > 0){
        num_lineas = a;
        lineas = new Linea[a];
    }
}

RedMetro::RedMetro(const RedMetro &orig) {
    num_lineas = 0;
    lineas = nullptr;
    copy(orig);
}

RedMetro &RedMetro::operator+=(const RedMetro &orig) {
    RedMetro aux;
    aux.allocate(orig.num_lineas+num_lineas);
    for(int i = 0; i < num_lineas; i++){
        aux.lineas[i] = lineas[i];
    }
    for(int i = num_lineas; i < aux.num_lineas; i++){
        aux.lineas[i] = lineas[i];
    }
    *this = aux;
    aux.deallocate();
    return *this;
}

bool RedMetro::read(std::istream &is) {
    RedMetro aux;
    is >> aux.num_lineas;
    if(is.fail())
        return false;
    aux.lineas->operator>>(is);
    if(is.fail())
        return false;
    *this = aux;
    aux.deallocate();
    return true;
}

std::istream &RedMetro::operator>>(std::istream &is) {
    read(is);
    return is;
}

void RedMetro::print(std::ostream &os) {
    os << num_lineas << std::endl;
    for(int i = 0; i < num_lineas; i++){
        os << lineas[i].GetNumParadas() << std::endl;
        for(int j = 0; j < lineas[i].GetNumParadas(); j++){
            lineas[i].operator[](j).print(os);
            os << std::endl;
        }
    }
}

std::ostream &RedMetro::operator<<(std::ostream &os) {
    print(os);
    return os;
}

RedMetro::RedMetro(std::string ifilename) {
    std::string cadena;
    std::ifstream ifile;

    ifile.open(ifilename);
    if(ifile.fail()){
        std::cerr << "Error de apertura de fichero";
        exit(1);
    }
    ifile >> cadena;
    if(cadena == "METRO"){
        this->read(ifile);
    }else{
        std::cerr << "Error, falta palabra mágica";
        exit(1);
    }
}

bool RedMetro::operator==(const RedMetro &red) {
    int contador1 = 0;
    int contador2 = 0;

    if(red.num_lineas != num_lineas)
        return false;
    for(int i = 0; i < num_lineas; i++){
        if(lineas->operator[](i).EstaActiva())
            contador1++;
    }
    for(int j = 0; j < red.num_lineas; j++){
        if(red.lineas->operator[](j).EstaActiva())
            contador2++;
    }

    if(contador1==contador2)
        return true;
    else
        return false;
}

bool RedMetro::operator!=(const RedMetro &red) {
    if(this->operator==(red))
        return false;
    else
        return true;
}

bool RedMetro::operator>(const RedMetro &red) {
    int contador1 = 0;
    int contador2 = 0;
    double porcentaje1, porcentaje2;

    for(int i = 0; i < num_lineas; i++){
        if(lineas->operator[](i).EstaActiva())
            contador1++;
    }
    for(int j = 0; j < red.num_lineas; j++){
        if(red.lineas->operator[](j).EstaActiva())
            contador2++;
    }

    //Ponderamos
    porcentaje1 = num_lineas*0.3+contador1*0.7;
    porcentaje2 = red.num_lineas*0.3+contador2*0.7;

    if(porcentaje1 > porcentaje2)
        return true;
    else
        return false;
}

Linea RedMetro::MejorConectada() {
    //fALTA
}

bool RedMetro::EstaTotalmenteOperativa(int nl) {
    for(int i = 0; i < lineas[nl].GetNumParadas(); i++){
        if(lineas[nl].operator[](i).EstaActiva() == false)
            return false;
    }
    return true;
}

