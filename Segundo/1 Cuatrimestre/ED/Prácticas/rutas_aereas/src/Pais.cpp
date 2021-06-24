/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file Pais.cpp
 */

#include "../include/Pais.h"

using namespace std;

Pais::Pais(Punto localizacion, std::string nombre, std::string bandera){
  this->localizacion = localizacion;
  this->nombre = nombre;
  this->bandera = bandera;
};

Punto Pais::Localizacion() const { return this->localizacion; }

string Pais::GetPais() const { return nombre; }

string Pais::GetBandera() const { return bandera; }

void Pais::setLocalizacion(Punto localizacion) {
  this->localizacion = localizacion;
}

void Pais::setNombre(string nombre) { this->nombre = nombre; }

void Pais::setBandera(string bandera) { this->bandera = bandera; }

istream &operator>>(istream &is, Pais &P) {
  double lat, lng;

  is >> lat >> lng >> P.nombre >> P.bandera;

  P.localizacion = Punto(lat, lng);
  return is;
}

ostream &operator<<(ostream &os, const Pais &P) {
  os << P.Localizacion() << " " << P.GetPais() << " " << P.GetBandera();
  return os;
}