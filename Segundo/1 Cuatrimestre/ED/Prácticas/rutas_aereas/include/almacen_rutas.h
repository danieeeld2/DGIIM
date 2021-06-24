/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file alamacen_rutas.h
 * @brief descripcion de la clase Alamacen_Rutas
 */

#ifndef ALMACEN_RUTAS_H
#define ALMACEN_RUTAS_H

#include "Ruta.h"

/**
 * @brief TDA Almacen_rutas, almacena rutas
 */
class Almacen_Rutas {
private:
  std::map<std::string, Ruta> datos;

public:
  /**
   * @brief devuelve la ruta con el nombre dado
   * @param nombre nombre de la ruta
   * @return una Ruta
   * @warning si la ruta no existe se lanzara una excepcion
   */
  Ruta GetRuta(const std::string &nombre) const { return datos.at(nombre); }

  /**
   * @brief sobrecarga del operador >>
   * @param is flujo de entrada
   * @param AR objeto al que introducir datos
   */
  friend std::ostream &operator<<(std::ostream &os, const Almacen_Rutas &AR);

  /**
   * @brief sobrecarga del operador <<
   * @param os flujo de salida
   * @param AR objeto del que sacar datos
   */
  friend std::istream &operator>>(std::istream &is, Almacen_Rutas &AR);
};

#endif