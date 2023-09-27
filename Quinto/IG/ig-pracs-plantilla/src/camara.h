// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de cámaras (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaraciones de las clases 'Viewport', 'Camara' y derivadas de 'Camara'
// **
// **   Camara: clase base
// **      + CamaraInteractiva: cámaras editables
// **          + CamaraOrbitalSimple: cámara orbital usada en las 
// **            prácticas (implementada al 100%)
// **          + Camara3Modos: cámara con tres modos de funcionamiento (práctica 5)
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#ifndef CAMARA_HPP
#define CAMARA_HPP

//#include "tup_mat.h"
#include "cauce.h"

// *********************************************************************
// clase: Viewport

class Viewport
{
  public:
  int       org_x, org_y, // origen en pixels (esquina inferior izquierda)
            ancho, alto ; // dimensiones en pixels (núm. columnas, núm. filas)
  float     ratio_yx ;    // == alto/ancho (relación de aspecto)
  glm::mat4  matrizVp ,    // matriz de viewport ( pasa: NDC ==> DC )
            matrizVpInv ; // matriz inversa ( pasa: DC ==> NDC )
  // constructor
  Viewport() ; // crea viewport de 512 x 512 con origen en (0,0)
  Viewport( int p_org_x, int p_org_y, int p_ancho, int p_alto );
} ;

// ******************************************************************
// clase base para cámaras

class Camara
{
   public: // ----------------------------

   // fija las matrices model-view y projection en el cauce
   void activar( Cauce & cauce )  ;

   // cambio el valor de 'ratio_vp' (alto/ancho del viewport)
   void fijarRatioViewport( const float nuevo_ratio ) ;

   // lee la descripción de la cámara (y probablemente su estado)
   virtual std::string descripcion() ;

   protected: // ------------------------------

   bool      matrices_actualizadas = false ;        // true si matrices actualizadas
   glm::mat4 matriz_vista = glm::mat4(1.0) , // matriz de vista
             matriz_proye  = glm::mat4(1) ; // matriz de proyección
   float     ratio_vp      = 1.0 ;         // alto del viewport dividido por el ancho del viewport

   // actualiza 'matriz_vista' y 'matriz_proye' a partir de los parámetros
   // específicos de cada tipo de cámara
   virtual void actualizarMatrices() ;
} ;

// ******************************************************************
// clase (abstracta) para cámaras interactivas (cámaras manipulables)

class CamaraInteractiva : public Camara
{
   public:
   // desplazar o rotar la cámara en horizontal 'da' unidades y en vertical 'db' unidades
   // (en horizontal y en vertical aquí se entiende relativo al marco de camara)
   virtual void desplRotarXY( const float da, const float db ) = 0 ;

   // acercar/alejar o desplazar la camara en el eje Z un total de 'dz' unidades
   // (el eje es el eje Z, relativo al marco de la camara, es decir, perpendicular al plano de visión)
   virtual void moverZ( const float dz ) = 0 ;

   // hacer que apunte hacía el punto de atención 'paten' y
   // cambiar de modo a modo examinar
   // por defecto imprime mensaje de advertencia de que la cámra no ofrece esta funcionalidad
   virtual void mirarHacia( const glm::vec3 & paten )  ;

   // cambiar el modo de la camara al siguiente modo o al primero
   // por defecto imprime mensaje de advertencia de que la cámra no ofrece esta funcionalidad
   virtual void siguienteModo()  ;

   virtual std::string descripcion() 
   {
      return "cámara interactiva" ;
   }
} ;

// ******************************************************************
// clase para una cámara orbital sencilla que siempre tiene el origen de
// coordenadas del mundo en el centro de la imagen (tiene un modo único)

class CamaraOrbitalSimple : public CamaraInteractiva
{
   public:

   // cambia la longitud usando 'da' y la latitud usando 'db'
   virtual void desplRotarXY( const float da, const float db )   ;

   // acercar/alejar 'dz' unidades al origen (sin 'atravesarlo' nunca)
   virtual void moverZ( const float dz )  ;

   // lee la descripción de la cámara (y probablemente su estado)
   virtual std::string descripcion() ;

   protected:
      // posición de la cámara en coordenadas esféricas relativas al origen de
      // coordenadas del mundo (y a sus ejes)
      float a = 0.0,   // ángulo horizontal (angulo del eje Z con el plano z==0 en cc.m.)
            b = 0.0,   // ángulo vértical (angulo del eje Z con el plano y==0 en cc.m.)
            d = 4.0 ;  // distancia entre origen de cámara y origen de cc. de mundo

   virtual void actualizarMatrices() ;
} ;

// tipo enumerado para los modos de las cámaras interactivas
enum class ModoCam { examinar, prim_pers_rot, prim_pers_despl } ;

// ******************************************************************
// cámara interactiva completa, que puede funcionar en tres modos, y
// que puede centrarse en un punto (pasa a modo examinar)
//
// Los modos son:
//
//   ** modo examinar (o modo orbital), relativo a un punto de atención
//   ** modo primera persona con rotaciones (típico de los videojuegos)
//   ** modo primera persona con desplazamientos  (horizontal o vertical)



class Camara3Modos : public CamaraInteractiva
{
   public:

   // crea una cámara perspectiva con valores por defecto
   Camara3Modos() ;

   // crea una cámara, inicialmente en modo examinar, con el punto
   // de atención en el origen, se especifica:
   // * perspectiva_ini : true si es una camara perspectiva, false si es ortográfica
   // * origen_ini      : punto de vista inicial (origen marco de cámara)
   // * punto_aten_ini  : punto de atención
   // * fovy_grad_ini   : si es perspectiva, la apertura de campo vertical, en grados

   Camara3Modos( const bool perspectiva_ini,
                 const glm::vec3 & origen_ini, const float ratio_vp_ini,
                 const glm::vec3 & punto_aten_ini, const float fovy_grad_ini = 70.0 ) ;

   // desplazar o rotar la cámara en horizontal 'dx' unidades y en vertical 'dy' unidades
   // (en horizontal y en vertical aquí se entiende relativo al marco de camara)
   virtual void desplRotarXY( const float da, const float db )  ;

   // acercar/alejar la cámara respecto al punto de atención
   // (el eje es el eje Z, relativo al marco de la camara, es decir, perpendicular al plano de visión)
   virtual void moverZ( const float dz )  ;

   // hacer que apunte hacía el punto de atención 'paten' y pasar a modo examinar
   virtual void mirarHacia( const glm::vec3 & nuevo_punto_aten )  ;

   // cambiar el modo de la camara al siguiente modo o al primero
   virtual void siguienteModo()  ;

   // devuelve el punto de atencion actual
   virtual glm::vec3 puntoAtencion() ;

   // lee la descripción de la cámara (y probablemente su estado)
   virtual std::string descripcion() ;

private:

      // modo actual de la cámara,
      // (0=examinar, 1=prim.persona con desplazamientos, 2=prim.persona con rotaciones)
      ModoCam modo_actual = ModoCam::examinar ;

      // true si la cámara es perspectiva, false en otro caso:
      bool perspectiva = true ;

      // apertura de campo vertical en grados
      float fovy_grad = 60.0 ;

      // distancia inicial entre el origen del marco y el punto de atención
      const float d_ini = 3.0 ;

      // punto de atención
      glm::vec3 punto_atencion = { 0.0, 0.0, 0.0 } ;

      // coordenadas polares del origen de coordenadas del mcv, respecto del punto de atención
      // las componentes 0 y 1 son los ángulos de longitud y latitud, ambos EN RADIANES, inicialmente 0
      // la componente 2 es la distancia al origen, inicialmente 'd_ini'
      glm::vec3 org_polares = { 0.0, 0.0, d_ini } ;

      // coordenadas cartesianas del origen de coordenadas del mcv, respecto del punto de atención
      glm::vec3 org_cartesianas = { 0.0, 0.0, d_ini };

      // ejes del marco de coordenadas de vista
      glm::vec3 eje[3] = {  { 1.0, 0.0, 0.0 }, // eje X
                            { 0.0, 1.0, 0.0 }, // eje Y
                            { 0.0, 0.0, 1.0 }  // eje Z
                         };

      virtual void actualizarMatrices() ;
      void actualizarEjesMCV() ;

} ;

#endif
