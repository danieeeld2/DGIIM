// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de escenas (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaración de la clase 'Escena' y derivadas (una por cada práctica)
// **
// **  + Escena: clase con una colección de objetos para visualizar, las fuentes de luz
// **    y una cámara. En cada momento se visualiza uno de los objetos (se conmuta con 'o')
// **    Las clases derivadas incluyen cada una un constructor específico que crea el objeto,
// **    son estas:
// **
// **       + Escena1 : práctica 1
// **       + Escena2 : práctica 2
// **       + Escena3 : práctica 3
// **       + Escena4 : práctica 4
// **       + Escena5 : práctica 5
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

#ifndef ESCENA_H
#define ESCENA_H


#include <vector>
#include "aplicacion-ig.h"
// #include "objeto3d.h"
// #include "camara.h"


// *************************************************************************
// Clase Escena
// -----------------
// Clase para objetos visualizables de tipo escena: incluye objetos, cámaras,
// un material inicial, una colección de fuentes de luz, etc...


class Escena
{
   public:

   // crea una escena con una cámara orbital simple, materiales y luces por defecto.
   Escena() ;

   // visualiza el objeto actual de la escena
   void visualizarGL(  ) ;

   // visualiza el objeto actual de la escena, pero en modo selección 
   void visualizarGL_Seleccion(  );

   // pasa la cámara actual a la siguiente
   void siguienteCamara() ;

   // devuelve un puntero a la cámara actual
   CamaraInteractiva * camaraActual() ;

   // pasa el objeto actual al siguiente
   void siguienteObjeto() ;

   // devuelve puntero al objeto actual
   Objeto3D * objetoActual();

   // devuelve un puntero a la colección de fuentes actual
   ColFuentesLuz * colFuentes();

   // visualiza las normales del objeto actual de la escena
   void visualizarNormales();
  

   protected:
   // vector de objetos (alternativos: se visualiza uno de ellos nada más)
   std::vector<Objeto3D *> objetos ;

   // vector de cámaras (se usa una en cada momento)
   std::vector<CamaraInteractiva *> camaras ;

   // material por defecto que se activa antes de dibujar (con iluminación activada)
   Material * material_ini = nullptr ;

   // colección de fuentes de luz que se usarán para dibujar, (con iluminación activada)
   ColFuentesLuz * col_fuentes = nullptr ;

   // índice de la cámara activa (en el vector 'camaras')
   unsigned ind_camara_actual = 0 ;

   // índice del objeto activo (en el vector 'objetos')
   unsigned ind_objeto_actual = 0 ;

} ;


// -------------------------------------------------------------------------
// clase derivada de 'Escena', define un constructor que permite añadir
// al array de objetos de la escena los objetos que se indican en la práctica 1

class Escena1 : public Escena
{
   public:
      Escena1() ;
} ;


// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2, 3, 4 y 5.
// Añadir la declaración de las clases Escena2, Escena3, etc ..... para definir
// los objetos que se indican en los guiones de las prácticas 2,3,4 y 5.




#endif // ESCENA_H
