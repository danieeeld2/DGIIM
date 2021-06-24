/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file ruta.h
 * @brief descripcion de la clase ruta
 */

#ifndef RUTA_H
#define RUTA_H

#include "Paises.h"
#include <vector>

/**
 * @class Clase ruta para almacenar una ruta aerea
 */

class Ruta {
private:
  Paises *paises; // Puntero a nuestro almacen de paises, para poder determinar
                  // datos sobre ellos, no es memoria dinamica!!!
  std::string nombre;           // nombre de la ruta
  std::vector<Punto> recorrido; // Puntos por donde pasa la ruta, en orden
  std::vector<Punto> interes;   // Puntos de interes

public:
  /**
   * @brief constructor por defecto
   */
  Ruta();

  /**
   * @brief constructor con direccion almacen de paises
   * @param paises datos de los paises de las rutas
   */
  Ruta(Paises *paises);

  /**
   * @brief constructor copia
   */
  Ruta(const Ruta &orig) = default;

  /**
   * @brief destructor de la clase
   * @warning no borra paises
   */
  ~Ruta() = default;

  /**
   * @brief operador de asignacion
   */
  Ruta &operator=(const Ruta &orig) = default;

  /**
   * @brief agrega un nuevo punto a la ruta
   * @param punto Punto a agregar en la ruta
   * @pre punto debe de ser la localizacion valida de un pais
   */
  void nuevoPunto(Punto punto);

  /**
   * @brief permite cambiar el nombre de la ruta
   * @param nombre el nuevo nombre de la ruta
   */
  void nuevoNombre(std::string nombre);

  /**
   * @brief agrega un nuevo punto de interes a la ruta
   * @param punto El punto de interes
   */
  void nuevoInteres(Punto punto);

  /**
   * @brief devuelve la cantidad de puntos de la ruta
   * @return la cantidad de puntos de la ruta
   */
  int longitud() const;

  /**
   * @brief devuelve la cantidad de puntos de interes de la ruta
   * @return la cantidad de puntos de interes
   */
  int cantidadInteres() const;

  /**
   * @brief getter del numbre de la ruta
   * @return el nombre de la ruta
   */
  std::string GetNombre() const;

  // Clases iteradoras
  class const_iterator;
  class iterator {
  private:
    std::vector<Punto>::iterator p;

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
    const Punto &operator*() const { return *p; }
    friend class Ruta;
    friend class const_iterator;
  };
  class const_iterator {
  private:
    std::vector<Punto>::const_iterator p;

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
    const Punto &operator*() const { return *p; }
    friend class Ruta;
  };

  // Funciones sobre iteradores
  iterator begin() {
    iterator it;
    it.p = recorrido.begin();
    return it;
  }

  const_iterator begin() const {
    const_iterator it;
    it.p = recorrido.begin();
    return it;
  }
  iterator end() {
    iterator it;
    it.p = recorrido.end();
    return it;
  }
  const_iterator end() const {
    const_iterator it;
    it.p = recorrido.end();
    return it;
  }

  Pais determinar(const const_iterator& c) const {
      return (*paises)[*c];
  }

    /**
     * @brief sobrecarga del operador <<
     * @param os flujo de salida
     * @param r ruta que sacar
     * @note seguir formato de de rutas
     */
  friend std::ostream& operator<<(std::ostream& os, const Ruta& r);

};

/**
   * @brief sobrecarga del operador >>
   * @param is flujo de entrada
   * @param r ruta a la que introducir datos
   * @note seguir formato de rutas
   */
  std::istream& operator>>(std::istream& is, Ruta& r);


#endif