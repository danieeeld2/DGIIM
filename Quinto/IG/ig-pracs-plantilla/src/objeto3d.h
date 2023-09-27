// *********************************************************************
// **
// ** Objetos que se pueden visualizar (declaración)
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** Declaración de la clase 'Objeto3D' (objetos que se pueden 
// ** visualizar). Son en esencia objetos de clases derivadas que 
// ** definen un método llamado 'visualizarGL'
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

#ifndef IG_OBJETO3D_HPP
#define IG_OBJETO3D_HPP

#include <string>          // usar std::string
#include <vector>
#include <glm/glm.hpp>

//#include <tup_mat.h>
//using namespace tup_mat ;

// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class Objeto3D
{

   public:
      // pone el identificador a '0', siempre
      Objeto3D() ;

      // visualizar el objeto con OpenGL, usando la configuración especificada la aplicación
      //
      virtual void visualizarGL(  ) = 0 ;

      // visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
      // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
      //
      virtual void visualizarGeomGL(  ) = 0 ;

      // Visualizar las normales del objeto, si se puede hacer, en otro caso no hace nada.
      //
      virtual void visualizarNormalesGL () = 0 ;

      // Visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
      // basados en los identificadores de los objetos
      //
      virtual void visualizarModoSeleccionGL() = 0 ;

      // Ejecutar código después de producirse un click sobre este objeto.
      // Se debe redefinir para comportamientos específicos en clases derivadas de 'Objeto3D'.
      // Si no se redefine, la versión por defecto da estos pasos:
      //   (1) escribe el nombre del objeto,
      //   (2) apunta la cámara actual de la escena actual al centro del objeto, 
      //   (3) devuelve true.
      //
      // @param centro_wc (vec3) -- centro del objeto en coordenadas del mundo
      // @return (bool) --  'true' si el estado del objeto ha cambiado y hay que revisualizar, false en otro caso.
      //
      virtual bool cuandoClick( const glm::vec3 & centro_wc) ;

      // devuelve el nombre del objeto
      std::string leerNombre() const ;

      // Le asigna un nuevo nombre al objeto.
      // @param nuevoIdent (string) -- nuevo nombre del objeto 
      //
      void ponerNombre( const std::string & nuevoNombre );

      // Devuelve el identificador actual del objeto
      // @return (int) -- identificador actual
      //
      int leerIdentificador() ;

      // Le asigna un nuevo identificador al objeto
      // @param nuevoIdent (int) -- nuevo identificador del objeto 
      //
      void ponerIdentificador( int nuevoIdent );

      // Consultar si el objeto tiene color o no lo tiene. 
      // Por defecto, los objetos no tienen asignado un color definido.
      // @return (bool) 'true' si el objeto tiene asignado un color, 'false' en otro caso
      // 
      bool tieneColor();

      // Devuelve el color actual del objeto (si tieneColor() == true )
      // @return (glm::vec3) - color actual del objeto
      //
      glm::vec3 leerColor();

      // Le asigna un color al objeto 
      // (a partir de esta llamada, 'tieneColor()' devuelve true).
      // @param nuevo_color (vec3) -- nuevo color del objeto 
      //
      void ponerColor( const glm::vec3 & nuevo_color );

    
      // ----------------------------------------------------------------------
      // métodos virtuales, relativos a los parámetros del objeto

      // Devuelve el número de parámetros de este objeto
      // (por defecto no hay ningún parámetro: devuelve 0)
      // (virtual: redefinir en clases derivadas)
      //
      // @return (unsigned) -- número de parámetros del objeto.
      //
      virtual unsigned leerNumParametros() const ;

      // Actualiza el valor de un parámetro a un instante de tiempo
      // (por defecto produce un error: número de parámetro fuera de rango, esto se debe
      // a que por defecto un objeto 3D declara tener 0 parámetros, y esta función no se
      // debe llamar, a no ser que se declaren tener más parámetros).
      // (virtual: redefinir en clases derivadas)
      //
      //  @param iParam (unsigned) -- índice del parámetro (entre 0 y numParametros()-1 )
      //  @param t_sec  (float)    -- tiempo en segundos desde el estado inicial
      //
      virtual void actualizarEstadoParametro( const unsigned iParam, const float t_sec );

      // ---------------------------------------------------------------------------------
      // métodos no virtuales, relativos a los parámetros, ya implementados en 'Objeto3D'

      // Cambia el parámetro activo actualmente,
      // si d == +1 pasa al siguiente (o del último al primero),
      // si d == -1 pasa al anterior (o del primero al último).
      // Si hay 0 parámetros, no hace nada.
      //
      // @param d (int) -- determina si se pasa al siguiente (+1) o al anterior (-1)
      //
      void modificarIndiceParametroActivo( const int d );

      // Incrementa o decrementa el valor de uno de los parámetros del objeto.
      // (por defecto, para un objeto con 0 parámetros produce un error: número de parámetro fuera de rango)
      //
      //  @param iParam (unsigned) -- índice del parámetro (entre 0 y numParametros()-1 )
      //  @param delta  (int)      --  número de unidades de incremento o decremento (típicamente +1 o -1)
      //
      void modificarParametro( const unsigned iParam, const int delta );

      // Incrementa o decrementa el valor del parámetro activo del objeto.
      // (por defecto, para objetos con 0 parámetros produce un error).
      //
      //  @param delta  (int)      --  número de unidades de incremento o decremento (típicamente +1 o -1)
      //
      void modificarParametro( const int delta );

      // actualiza el estado del objeto tras transcurrir un intervalo de tiempo
      // (recorre todos los parámetros y los actualiza uno a uno, para ello
      // llama a actualizarEstadoParametro)
      //
      // @param dtSec (float) -- es el tiempo en segundos transcurrido desde el inicio de las
      //         animaciones o desde la última llamada a este método
      //
      void actualizarEstado( const float dtSec );

      // ----------------------------------------------------------------------
      // métodos relativos al punto central del objeto (para selección).

      // pone los valores de los parámetros a cero (estado inicial)
      // (por defecto no hace nada)
      void resetParametros();

      // poner el centro del objeto:
      void ponerCentroOC( const glm::vec3 & nuevoCentro );

      // leer el centro del objeto
      glm::vec3 leerCentroOC();

      // (re)calcular centro del objeto, si es necesario
      virtual void calcularCentroOC() ;


      // ----------------------------------------------------------------------
      // método para buscar un objeto (o subobjeto) con un identificador y devolver
      // un puntero al objeto y el punto central
      //
      // resultado:
      //    true si se ha encontrado, false si no.
      //
      // parámetros de entrada:
      //    ident_busc: identificador a buscar
      //    modelview:  matriz de modelado del padre del objeto (pasa coords.loc. a WC)
      //                (en el nodo raíz de un grafo de escena es la matriz identidad)
      //
      // parámetros de salida
      //    objeto: si encontrado y no es nullptr: apunta al puntero al objeto
      //    centro_wc: punto central del nodo en coords. de mundo (si encontrado)

      virtual bool buscarObjeto( const int ident_busc,
         const glm::mat4 & mmodelado, Objeto3D ** objeto, glm::vec3 & centro_wc )  ;

      // ----------------------------------------------------------------------
      // destructor
      virtual ~Objeto3D();

    

      

   private: //-----

      // la primera vez que se llama, inicializa los valores base de los
      // parámetros (a cero), las siguientes comprueba que tpSec tiene tantas
      // entradas como parámetros.
      void initTP();

      // valores actuales de 'tiempo' de cada parámetro (en segundos)
      // (inicialmente está vacío, así todos los objetos tienen 0 parámetros por defecto)
      std::vector<float> tiempo_par_sec ;

      // índice del parámetro activo (solo sirve si 'leerNumParametros() > 0')
      int ind_par_act = 0 ;

      // nombre asignado al objeto
      std::string nombre_obj = "no asignado";

      // punto central o representativo del objeto, en coordenadas de objeto
      glm::vec3 centro_oc = { 0.0, 0.0, 0.0 };

      // identificador de este objeto
      //  0 : no seleccionable
      // -1 : mismo identificador que el padre en la jerarquía
      // >0 : tiene este identificador (es seleccionable)
      int identificador = -1 ;

      // 'true' el objeto tiene asignado un color
      // 'false' el objeto no tiene asignado un color
      bool tiene_color = false ;

      // si 'tiene_color' es 'true', color actual del objeto
      glm::vec3 color_objeto = { 1.0, 1.0, 1.0 } ;

} ;



#endif
