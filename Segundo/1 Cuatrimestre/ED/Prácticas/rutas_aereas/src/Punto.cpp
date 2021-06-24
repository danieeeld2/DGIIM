/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file Punto.cpp
 */

#include "../include/Punto.h"

Punto::Punto() {
    latitud = 0;
    longitud = 0;
}

Punto::Punto(float latitud, float longitud) {
    this->longitud = longitud;
    this->latitud = latitud;
}

float Punto::GetLatitud() const {{
        return this->latitud;
}}

float Punto::GetLongitud() const {
    return this->longitud;
}

void Punto::setLatitud(float latitud) {
    this->latitud = latitud;
}

void Punto::setLongitud(float longitud) {
    this->longitud = longitud;
}