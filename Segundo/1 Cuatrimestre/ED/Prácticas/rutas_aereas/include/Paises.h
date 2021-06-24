/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file paises.h
 * @brief implementa el TDA Paises
 */

#ifndef PAISES_H
#define PAISES_H

#include "Pais.h"
#include <map>

/**
 * @brief TDA Paises, representa todos los paises que se pueden encontrar en una
 * ruta aerea
 * @note usar junto a rutas aereas para determinar los paises de estas
 */
class Paises {
private:
  std::map<Punto, Pais> paises;

public:
  /**
   * @brief constructor por defecto
   */
  Paises() = default;

  /**
   * @brief sobrecarga del operador [] para obtener un pais mediante su
   * localizacion
   * @param localizacion localizacion del pais a buscar
   * @return el pais con la ubicacion asociada
   * @warning exepcion en caso de no tener la localizacion
   */
  Pais operator[](Punto localizacion) const;

  /**
   * @brief agrega un nuevo pais al objeto
   * @param pais pais a ser agregado
   * @note la clave del pais sera la localizacion de este
   */
  void Insertar(Pais pais);

  // Clases iteradoras
  class iterator {
  private:
    std::map<Punto, Pais>::iterator p;

  public:
    iterator() {}
    iterator &operator++() {
      ++p;
      return *this;
    }

    iterator &operator--() {
      --p;
      return *this;
    }
    bool operator==(const iterator &it) { return it.p == p; }
    bool operator!=(const iterator &it) { return it.p != p; }
    const Pais &operator*() const { return (*p).second; }
    friend class Paises;
    friend class const_iterator;
  };
  class const_iterator {
  private:
    std::map<Punto, Pais>::const_iterator p;

  public:
    const_iterator() {}
    const_iterator(const iterator &it) { p = it.p; }
    const_iterator &operator=(const iterator &it) {
      p = it.p;
      return *this;
    }
    const_iterator &operator++() {
      ++p;
      return *this;
    }

    const_iterator &operator--() {
      --p;
      return *this;
    }
    bool operator==(const const_iterator &it) { return it.p == p; }
    bool operator!=(const const_iterator &it) { return it.p != p; }
    Pais operator*() const { return (*p).second; }
    friend class Paises;
  };

  // Funciones sobre iteradores
  iterator begin() {
    iterator it;
    it.p = paises.begin();
    return it;
  }

  const_iterator begin() const {
    const_iterator it;
    it.p = paises.begin();
    return it;
  }
  iterator end() {
    iterator it;
    it.p = paises.end();
    return it;
  }
  const_iterator end() const {
    const_iterator it;
    it.p = paises.end();
    return it;
  }
  iterator find(const Pais &p) {
    iterator it;
    std::map<Punto, Pais>::iterator i;
    for (i = paises.begin(); i != paises.end() && !((*i).second == p); ++i)
      ;
    it.p = i;
    return it;
  }
  iterator find(const Punto &p) {
    iterator it;
    std::map<Punto, Pais>::iterator i;
    for (i = paises.begin(); i != paises.end() && !((*i).first == p); ++i)
      ;
    it.p = i;
    return it;
  }

/**
 * @brief sobrecarga del operador >>
 * @param is flujo de entrada
 * @param R objeto al que introducir datos
 * @note seguir formato de paises.txt, defiere del de las rutas aereas
 */
  friend std::ostream &operator<<(std::ostream &os, const Paises &R);

/**
 * @brief sobrecarga del operador <<
 * @param os flujo de salida
 * @param R objeto del que sacar datos
 * @note seguir formato de paises.txt, defiere del de las rutas aereas
 */
  friend std::istream &operator>>(std::istream &is, Paises &R);
};

#endif