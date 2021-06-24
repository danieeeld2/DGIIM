/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @brief Descripcion del TDA pais
 * @file pais.h
 */

#ifndef PAIS_H
#define PAIS_H

#include "Punto.h"
#include <string>

/**
 * @brief TDA Pais, representa a un pais de una ruta aerea
 */
class Pais {
private:
  Punto localizacion;
  std::string nombre;
  std::string bandera;

public:
  /**
   * @brief constructor por defecto
   */
  Pais() = default;

  /**
   * @brief constructor de la clase pais
   * @param localizacion localizacion del pais
   * @param nombre nombre del pais
   * @param bandera nombre del archivo ppm de la bandera
   */
  Pais(Punto localizacion, std::string nombre, std::string bandera);

  /**
   * @brief getter de la localizacion del pais
   * @return la localizacion del pais
   */
  Punto Localizacion() const;

  /**
   * @brief getter del nombre del pais
   * @return el nombre del pais
   */
  std::string GetPais() const;

  /**
   * @brief establece la localizacion del pais
   * @param localizacion la nueva localizacion del pais
   */
  void setLocalizacion(Punto localizacion);

  /**
   * @brief establece el nombre del pais
   * @param nombre nuevo nombre del pais
   */
  void setNombre(std::string nombre);

  /**
   * @brief estable la bandera del pais
   * @param bandera nombre de la bandera del pais
   */
  void setBandera(std::string bandera);

  /**
   * @brief getter de la bandera
   */
  std::string GetBandera() const;

  /**
   * @brief operador de comparacion
   */
  bool operator==(const Pais &orig) const {
    return this->bandera == orig.bandera &&
           this->localizacion == orig.localizacion;
  }

  /**
   * @brief sobrecarga del operador >>
   * @param is flujo de entrada
   * @param p pais al que introducir datos
   * @note seguir formato de paises.txt (distinto para puntos)
   */
  friend std::istream &operator>>(std::istream &is, Pais &p);

  /**
   * @brief sobrecarga del operator <<
   * @param os flujo de salida
   * @param p pais que sacar por pantalla
   */
  friend std::ostream &operator<<(std::ostream &os, const Pais &P);
};

#endif