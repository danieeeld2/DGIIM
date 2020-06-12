//
// Created by daniel on 11/6/20.
//

#include "Vuelo.h"

Vuelo::Vuelo() {
    idVuelo = -1;
    //  Llama al resto de constructores por defecto
}

void Vuelo::copy(const Vuelo &orig) {
    idVuelo = orig.idVuelo;
    rutaOptima = orig.rutaOptima;
    rutaReal = orig.rutaReal;
}

Vuelo &Vuelo::operator=(const Vuelo &orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

Vuelo::Vuelo(const Vuelo &orig) {
    Vuelo();
    copy(orig);
}

Vuelo::Vuelo(int i, Trayectoria opt) {
    idVuelo = i;
    rutaOptima = opt;
    rutaReal=Trayectoria();
}

Vuelo &Vuelo::operator+=(const Punto3D &p) {
     if(this->rutaReal.GetNum() == 0){
         add(rutaOptima.GetPos(0));
     }
     add(p);
     return *this;
}

void Vuelo::add(const Punto3D &p) {
    Vuelo aux;
    aux.copy(*this);
    this->rutaReal.deallocate();
    this->rutaReal.allocate(aux.rutaReal.GetNum()+1);
    for(int i = 0; i < aux.rutaReal.GetNum(); i++)
        rutaReal.Set(i,aux.rutaReal.GetPos(i));
    rutaReal.Set(aux.rutaReal.GetNum(),p);
}

void Vuelo::print(std::ostream &os) {
    os << idVuelo << std::endl;
    os << rutaOptima.GetNum() << std::endl;
    for(int i = 0; i < rutaOptima.GetNum(); i++){
        rutaOptima.GetPos(i).operator<<(os) << std::endl;
    }
    os << rutaReal.GetNum() << std::endl;
    for(int i = 0; i < rutaReal.GetNum(); i++){
        rutaReal.GetPos(i).operator<<(os) << std::endl;
    }
}

std::ostream &Vuelo::operator<<(std::ostream& os) {
    print(os);
    return os;
}

Vuelo::Vuelo(std::string ifilename) {
    std::ifstream ifile;
    std::string cadena;
    Vuelo aux;
    ifile.open(ifilename);
    if(ifile.fail()) {
        std::cerr << "Error de Apertura del fichero";
        std::exit(1);
    }
    ifile >> cadena;
    if(cadena == "FICHEROVUELO")
        aux.read(ifile);
    else {
        std::cerr << "Falta palabra mágica";
        std::exit(1);
    }
    ifile.close();
    *this = aux;
}

double Vuelo::CalcularLongitudOptima() {
    double a;
    for(int i = 0; i < rutaOptima.GetNum()-1; i++){
         a = a + rutaOptima.CalcularLongitud(i);
    } 
    return a;
}

double Vuelo::CalcularLongitudReal() {
    double a;
    for(int i = 0; i < rutaReal.GetNum()-1; i++){
        a = a + rutaReal.CalcularLongitud(i);
    }
    return a;
}

bool Vuelo::read(std::istream& is) {
    Trayectoria A,B;
    int id;
    if(is.fail())
        return false;
    is >> id;
    if(!is.eof())
        return false;
    idVuelo = id;
    A.read(is);
    if(!is.eof())
        return false;
    rutaOptima = A;
    B.read(is);
    if(!is.eof())
        return false;
    rutaReal = B;
    return true;
}

std::istream &Vuelo::operator>>(std::istream &is) {
    read(is);
    return is;
}

double Vuelo::calcularDistanciaMediaTrayectorias() {
     double a=1;
     double minimo = 0;
     int pos;
     for(int i = 0; i < rutaReal.GetNum(); i++){
         for(int j = 0; j < rutaOptima.GetNum(); j++){
             if(minimo > rutaReal.CalcularLongitud2pt(rutaOptima.GetPos(j),i)){
                 minimo =  rutaReal.CalcularLongitud2pt(rutaOptima.GetPos(j),i);
                 pos = j;
             }
         }
         a = rutaReal.CalcularLongitud2pt(rutaOptima.GetPos(pos),i)*a;
     }
    return a;
}

bool Vuelo::operator<(Vuelo &vuelo) {
     bool mayor = false;
     if(calcularDistanciaMediaTrayectorias() < vuelo.calcularDistanciaMediaTrayectorias())
         mayor = true;
     return mayor;
}

int Vuelo::GetID() {
    return idVuelo;
}
