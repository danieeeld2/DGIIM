/**
 * @author Mario García Márquez y Daniel Alconchel Vázquez
 * @file imagen.h
 */

#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>
#include <istream>
#include <ostream>

#include "../imagenES/imagenES.h"

typedef unsigned char byte;

/**
 * @brief TDA IMAGEN
 * Representa una imagen PPM o PGM e implementa operaciones sobre la misma
 */
class Imagen {
 private:
  // Tipo de la imagen
  TipoImagen tipo;
  // Matriz, se almacena de forma lineal, PPM triple de longitud que PGM por
  // RGB
  byte *imagen;
  // Altura y longitud de la foto
  int alt, longt;

  // Funciones auxiliares para la implementacion
  void allocate(int alt, int longt, TipoImagen tipo);
  void deallocate();
  void copiar(const Imagen &orig);

 public:
  /**
   * @brief constructor base
   */
  Imagen();

  /**
   * @brief constructor copia
   * @param orig imagen a ser copiada
   */
  Imagen(const Imagen &orig);

  /**
   * @brief constructor con nombre
   * @param nombre nombre de la imagen a abrir
   * @note en caso de imagen no soportada o archivo no valido actuará igual
   * que el constructor base
   */
  Imagen(const char *nombre);

  /**
   * @brief destructor de la clase
   */
  ~Imagen();

  /**
   * @brief devuelve el tipo de la imagen
   * @return tipo de la imagen
   * @note en caso de estar inicializado a 0 devolverá imagen desconocida
   */
  TipoImagen tipoImagen() const;

  /**
   * @brief devuelve la altura de la foto(o filas)
   * @return un entero con el valor de la altura de la foto
   */
  int altura() const;

  /**
   * @brief devuelve el ancho de la foto(o columnas)
   * @return un entero con el valor del ancho de la foto
   */
  int ancho() const;

  /**
   * @brief asigna @param valor en la posicion @param fila @param columna
   * @precond fila, columna y valor deben de estar en un rango válido, si no
   * se lanzará un error de -1
   */
  void asignarPixel(int fila, int columna, byte valor);

  /**
   * @brief consulta el valor de la imagen en la posicion @param fila @param
   * columna
   * @precond fila y columna deben de estar en un rango valido, si no se lanza
   * un error de valor -1
   * @return el valor del pixel
   * @postcond el valor devuelto estará entre 0 y 255
   * @note en caso de que la imagen sea a color devolverá el valor en escala
   * de grises
   */
  byte valor(int fila, int columna) const;

  /**
    * @brief aumenta el contraste de la imagen, a todos los puntos que no pasen
   @param umbral se le asignará 255 y a los demás @param oscuridad
   */
  void binarizacion(byte umbral, byte oscuridad = 0);

  /**
   * @brief umbraliza la imagen, esto es que si un pixel esta entra entre
   * @param t1 y @param t2 estos mantienen su valor, en otro caso su valor se
   * convierte en 255
   */
  void umbralizar(byte t1, byte t2);

  /**
   * @brief umbraliza la imagen determinando el umbral de manera automática
   * @see Imagen::umbralizar
   */
  void umbralizacionAutomatica();

  /**
   * @brief devuelve una imagen con zoom aplicado en los puntos marcados
   * @precond los puntos deben de estar dentro de la imagen
   * @param x1 @param y1 coordenadas de la esquina superior izquierda
   * @param x2 @param y2 coordenadas de la esquina inferior derecha
   * @return una nueva imagen a la que se ha aplicado el zoom y se ha suavizado
   */
  Imagen zoom(int x1, int y1, int x2, int y2) const;

  /**
   * @brief genera una nueva imagen siendo una reduccion de la actual
   * @param nf numero de filas del icono resultante
   * @param nc numero de columnas del icono resultante
   * @return imagen con las dimensiones especificadas
   */
  Imagen icono(int nf, int nc) const;

  /**
   * @brief devuelve una imagen con contraste corregido
   * @return imagen con contraste mejorado
   */
  Imagen corregirContraste() const;

  /**
   * @brief calcula un morphing entre la imagen actual y orig
   * @pre ambas imagenes deben tener las mismas dimensiones
   * @param orig Imagen a la que se llega en el morphing
   * @param step numero de fotogramas, maximo 256
   * @post escribe un video con una transformacion morphing
   */
  void morphing(const Imagen &orig, int step);

  /**
   * @brief sobrecarga del operador de asignación
   */
  void operator=(const Imagen &orig);

  /**
   * @brief imprime la imagen a un archivo
   * @param nombre nombre del archivo al que escribir
   */
  void EscribirImagen(const char *nombre) const;

  /**
   * @brief lee una imagen desde el archivo especificado
   * @param nombre nombre del archivo
   */
  void LeerImagen(const char *nombre);
};

#endif
