/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file punto.h
 * @brief descripcion de TDA punto que se usara para indicar la posicion de los
 * paises en el mapa
 */

#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>
#include <utility>

/**
 * @brief TDA Punto, representa un punto en coordenadas geograficas
 */
class Punto {
private:
  float latitud;
  float longitud;

public:
  /**
   * @brief contructor por defecto de la clase punto
   */
  Punto();

  /**
   * @brief contructor con parametros de la clase punto
   * @param latitud latitud del punto (entre 90 y -90)
   * @param longitud longitud del punto (entre -180 y 180)
   * @note en la longitud -180 y 180 representan el mismo valor
   */
  Punto(float latitud, float longitud);

  /**
   * @brief getter de la latitud
   * @return la latitud del punto
   */
  float GetLatitud() const;

  /**
   * @brief getter de la longitud
   * @return la longitud del punto
   */
  float GetLongitud() const;

  /**
   * @brief setter de la latitud
   * @param latitud nueva latitud del punto
   */
  void setLatitud(float latitud);

  /**
   * @brief setter de la longitud
   * @param longitud nuevo longitud del punto
   */
  void setLongitud(float longitud);

    /**
     * @brief operador de comparacion
     */
    bool operator==(const Punto &orig) const {
        return this->latitud == orig.latitud && this->longitud == orig.longitud;
    }

    bool operator<(const Punto &orig) const {
        return this->latitud < orig.latitud;
    }

    /**
     * @brief sobrecarga del operador >>
     * @param is flujo de entrada
     * @param p punto al que introducir datos
     * @note seguir formato de ruta aereaas
     */
    friend std::istream &operator>>(std::istream &is, Punto &p) {
        float a,b;
        is >> a;
        p.setLatitud(a);
        is >> b;
        p.setLongitud(b);
        return is;
    };

    /**
    * @brief sobrecarga del operador <<
    * @param os flujo de salida
    * @param p punto al que introducir datos
    * @note seguir formato de paises.txt, difiere del formato de las rutas aereas
    */
    friend std::ostream &operator<<(std::ostream &os, const Punto &p) {
        os << p.GetLatitud() << " " << p.GetLongitud();
        return os;
    };
};

#endif