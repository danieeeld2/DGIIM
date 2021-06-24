/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file almacen_rutas.cpp
 */

#include "../include/almacen_rutas.h"

std::ostream &operator<<(std::ostream &os, const Almacen_Rutas &AR) {
    for(auto ruta: AR.datos) {
        os << ruta.second;
    }

    return os;
}

std::istream &operator>>(std::istream &is, Almacen_Rutas &AR){
    while(!is.eof()) {
        Ruta ruta;
        is >> ruta;
        if(is)
            AR.datos[ruta.GetNombre()] = ruta;
    }

    return is;
}