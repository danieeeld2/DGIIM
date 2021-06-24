/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file Paises.cpp
 */

#include "../include/Paises.h"
using namespace std;

Pais Paises::operator[](Punto localizacion) const {
  return paises.at(localizacion);
}

void Paises::Insertar(Pais pais) { paises[pais.Localizacion()] = pais; }

istream &operator>>(istream &is, Paises &R) {
  Paises rlocal;
  // leemos el comentario
  if (is.peek() == '#') {
    string a;
    getline(is, a);
  }

  Pais P;
  while (is >> P) {
    rlocal.Insertar(P);
  }
  R = rlocal;
  return is;
}
ostream &operator<<(ostream &os, const Paises &R) {

  Paises::const_iterator it;
  for (it = R.begin(); it != R.end(); ++it) {
    os <<  (*it) << endl;
  }
  return os;
}