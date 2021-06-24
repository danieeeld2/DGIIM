/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file Ruta.cpp
 */

#include "../include/Ruta.h"
#include <algorithm>

Ruta::Ruta() {
    paises = nullptr;
    nombre = " ";
    recorrido.clear();
    interes.clear();
}

Ruta::Ruta(Paises *paises) {
    this->paises = paises;
}

void Ruta::nuevoPunto(Punto punto) {
    if (recorrido.size() == 0)
        recorrido.push_back(punto);
    else {
        bool ya_esta = false;
        for (long unsigned int i = 0; i < recorrido.size(); i++)
            if (recorrido[i].operator==(punto))
                ya_esta = true;
        if (!ya_esta) {
            std::vector <Punto> aux;
            bool insertado = false;
            for (long unsigned int i = 0; i < recorrido.size(); i++) {
                if (!recorrido[i].operator<(punto)) {
                    if (!insertado) {
                        aux.push_back(punto);
                        insertado = true;
                    }
                }
                aux.push_back(recorrido[i]);
            }
            if(!insertado)
                aux.push_back(punto);
            recorrido.clear();
            recorrido = aux;
        }
    }
}

void Ruta::nuevoNombre(std::string nombre) {
    this->nombre= nombre;
}

void Ruta::nuevoInteres(Punto punto) {
    bool ya_esta = false;
    for(long unsigned int i = 0; i < interes.size(); i++)
        if(interes[i].operator==(punto))
            ya_esta = true;
    if(!ya_esta)
        interes.push_back(punto);
}

int Ruta::longitud() const {
    return this->recorrido.size();
}

int Ruta::cantidadInteres() const {
    return this->interes.size();
}

std::string Ruta::GetNombre() const {
    return this->nombre;
}

std::istream& operator>>(std::istream& is, Ruta& r){
    // Leemos comentario
    if (is.peek() == '#') {
        std::string a;
        getline(is, a);
    }

    std::string b;
    is >> b;
    r.nuevoNombre(b);
    int c;
    is >> c;
    for (int i = 0; i<c; i++){
        char basura;
        float lat, lon;
        is >> basura >> lat >> basura >> lon >> basura;
        r.nuevoPunto(Punto(lat, lon));
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Ruta& r){
    os << r.GetNombre() << " " << r.longitud() << " ";
    for (int i=0; i<r.longitud(); i++)
        os<< "(" << r.recorrido[i].GetLatitud() << "," << r.recorrido[i].GetLongitud() <<")" << " ";
    os << std::endl;
    return os;
}

