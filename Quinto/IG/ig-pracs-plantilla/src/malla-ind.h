// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaración de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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

#ifndef IG_MALLAIND_HPP
#define IG_MALLAIND_HPP

#include <vector>       // usar std::vector
#include <ig-aux.h>
#include <vaos-vbos.h>

#include "objeto3d.h"   // declaración de 'Objeto3D'


// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaInd : public Objeto3D
{
   
   protected:
      // COMPLETAR: incluir aquí las variables y métodos privados que sean
      // necesarios para una malla indexada (y que no aparezcan ya declarados en esta plantilla)
      // ......

      std::vector<glm::vec3>  vertices ;
      std::vector<glm::uvec3> triangulos ;

      std::vector<glm::vec3> col_ver ;   // colores de los vértices
      std::vector<glm::vec3> nor_ver ;   // normales de vértices
      std::vector<glm::vec3> nor_tri ;   // normales de triángulos
      std::vector<glm::vec2> cc_tt_ver ; // coordenadas de textura de los vértices
      
      // descriptor del VAO con los vértices, triángulos y atributos de esta malla indexada
      // (se crea bajo demanda en 'visualizarGL')
      DescrVAO * dvao = nullptr  ;

      // VAO con los segmentos de las normales (vis. con GL_LINES)
      // ( se crea bajo demanda en 'visualizarNormales')
      DescrVAO * dvao_normales = nullptr ;

      std::vector<glm::vec3> segmentos_normales ; // guarda los segmentos de normales
      

      // normales de triángulos y vértices
      void calcularNormales();

      // calculo de las normales de triángulos (solo si no están creadas ya)
      void calcularNormalesTriangulos() ;



   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
      MallaInd() ;

      // crea una malla vacía con un nombre concreto:
      MallaInd( const std::string & nombreIni );

      // Visualizar el objeto con OpenGL
      // usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      virtual void visualizarGL(  ) ;

      // Visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
      // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
      virtual void visualizarGeomGL(  ) ;

      // Visualizar las normales del objeto, si no tiene tabla de normales imprime advertencia y no hace nada.
      virtual void visualizarNormalesGL() ;

      // visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
      // basados en los identificadores de los objetos
      virtual void visualizarModoSeleccionGL() ;

      // métodos para acceder a las tablas de una malla (acceso de lectura)
      const std::vector<glm::vec3> & refVertices()   const { return vertices ;  } 
      const std::vector<glm::uvec3> & refTriangulos() const { return triangulos ; }
      


     
} ;
// ---------------------------------------------------------------------
// Clase para mallas obtenidas de un archivo 'ply'
// es un tipo de malla indexada que define un nuevo constructor
// que recibe el nombre del archivo ply como parámetro

class MallaPLY : public MallaInd
{
   public:
      MallaPLY( const std::string & nombre_arch ) ;
} ;


// ---------------------------------------------------------------------

class Cubo : public MallaInd
{
   public:
      Cubo();
};

// ---------------------------------------------------------------------


#endif
