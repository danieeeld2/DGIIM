// *********************************************************************
// **
// ** Objetos que se pueden visualizar (implementación)
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** Implementación de la clase 'Objeto3D' (objetos que se pueden 
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

#include <iostream>

#include "objeto3d.h"
#include "aplicacion-ig.h"  
#include "seleccion.h"
#include "camara.h"

using namespace std ;

// -----------------------------------------------------------------------------

Objeto3D::Objeto3D()
{
}
// -----------------------------------------------------------------------------

std::string Objeto3D::leerNombre() const 
{
   return nombre_obj ;
}
// -----------------------------------------------------------------------------

void Objeto3D::ponerNombre( const std::string & nuevoNombre )
{
   nombre_obj = nuevoNombre ;
}
// -----------------------------------------------------------------------------

int Objeto3D::leerIdentificador()
{
   return identificador ;
}
// -----------------------------------------------------------------------------

void Objeto3D::ponerIdentificador( int nuevoIdent )
{
   identificador = nuevoIdent ;
}
// -----------------------------------------------------------------------------

bool Objeto3D::tieneColor()
{
   return tiene_color ;
}
// -----------------------------------------------------------------------------

glm::vec3 Objeto3D::leerColor()
{
   assert( tieneColor() );
   return color_objeto ;
}
// -----------------------------------------------------------------------------

void Objeto3D::ponerColor( const glm::vec3 & nuevo_color )
{
   tiene_color = true ;
   color_objeto = nuevo_color ;
}
// -----------------------------------------------------------------------------

void Objeto3D::ponerCentroOC( const glm::vec3 & nuevoCentro )
{
   centro_oc = nuevoCentro ;
}
// -----------------------------------------------------------------------------

bool Objeto3D::cuandoClick( const glm::vec3 & centro_wc ) 
{
   using namespace std ;
   assert( apl != nullptr );
   Escena * escena = apl->escenas[apl->ind_escena_act] ; assert( escena != nullptr );

   cout << "Ejecutando método 'cuandoClick' por defecto." << endl ;
   cout << "Click realizado sobre el objeto: '" << leerNombre() << "'" << endl ;

   // COMPLETAR: práctica 5: apuntar la cámara actual a este objeto 
   //
   // Recuperar la camara actual de la escena (puntero 'escena') con el método 'camaraActual', 
   // y hacer que apunte al punto central de este objeto (parámetro 'centro_wc'), usando 
   // el método 'mirarHacia' de esa cámara.
   // ...

   return true ;
}
// -----------------------------------------------------------------------------

glm::vec3 Objeto3D::leerCentroOC()
{
   return centro_oc ;
}
// -----------------------------------------------------------------------------

void Objeto3D::calcularCentroOC()
{
   // Por defecto no se hace nada: se asume que el centro está bien calculado
   // en el constructor. Se puede redefinir en clases derivadas, por ejemplo,
   // se redefine en los nodos de grafo de escena. 
   // (y se puede redefinir en las mallas indexadas)
}

// -----------------------------------------------------------------------------
// buscar un identificador (implementación por defecto para todos los Objeto3D)

bool Objeto3D::buscarObjeto
(
   const int          ident_busc,
   const glm::mat4 &  mmodelado,
   Objeto3D **        objeto,
   glm::vec3 &        centro_wc
)
{
   using namespace glm ;
   assert( 0 < ident_busc );

   if ( identificador == ident_busc )
   {
      centro_wc = mmodelado*vec4( leerCentroOC(), 1.0f ) ;
      if ( objeto != nullptr )
         *objeto = this ;
      return true ;
   }
   else
      return false ;
}

// -----------------------------------------------------------------------------
// Devuelve el número de parámetros de este objeto
// (por defecto no hay ningún parámetro: devuelve 0)
// (virtual: redefinir en las clases derivadas)

unsigned Objeto3D::leerNumParametros() const
{
   return 0 ;
}

// -----------------------------------------------------------------------------
// cambia el parámetro activo actualmente (variable 'ind_par_act')
// si d == +1 pasa al siguiente (o del último al primero)
// si d == -1 pasa al anterior (o del primero al último)
// (si hay 0 parámetros, no hace nada)

void Objeto3D::modificarIndiceParametroActivo( const int d )
{
   const int n = leerNumParametros() ;

   using namespace std ;

   if ( n == 0 )
   {  cout << "no es posible cambiar el parámetro activo, este objeto no tiene ningún parámetro definido." << endl ;
      return ;
   }
   assert( 0 <= ind_par_act );
   ind_par_act = ( ind_par_act + n + d ) % n ;
   cout << "parámetro actual del objeto cambiado a " << (ind_par_act+1) << " / " << n << endl ;
}

// -----------------------------------------------------------------------------
// Incrementa o decrementa el valor base de uno de los parámetros del objeto
//  iParam : índice del parámetro (entre 0 y numParametros()-1 )
//  delta  : número de unidades de incremento o decremento (típicamente +1 o -1)
// (por defecto produce un error: número de parámetro fuera de rango)

void Objeto3D::modificarParametro( const unsigned iParam, const int delta )
{
   assert( iParam < leerNumParametros() );
   initTP();
   tiempo_par_sec[iParam] += float(delta)/10.0 ; // cada unidad es equivalente a una décima de segundo
   actualizarEstadoParametro( iParam, tiempo_par_sec[iParam] );
}

// -----------------------------------------------------------------------------
// igual que el anterior, pero cambia el parámetro activo (iParam --> ind_par_act)
void Objeto3D::modificarParametro( const int delta )
{
   assert( 0 <= ind_par_act && ind_par_act < int(leerNumParametros()) );
   initTP();
   tiempo_par_sec[ind_par_act] += float(delta)/10.0 ; // cada unidad es equivalente a una décima de segundo
   actualizarEstadoParametro( ind_par_act, tiempo_par_sec[ind_par_act] );
}

// -----------------------------------------------------------------------------
// Actualiza el valor de un parámetro a un instante de tiempo
//  iParam : índice del parámetro (entre 0 y numParametros()-1 )
//  tSec   : tiempo en segundos desde el estado inicial
// (por defecto produce un error)
// (virtual: redefinir en las clases derivadas)

void Objeto3D::actualizarEstadoParametro( const unsigned iParam, const float tSec )
{
   cerr << "Se ha invocado el método: " << __PRETTY_FUNCTION__  << endl
        << "(este método se debe redefinir para clases de objetos que tengan algún parámetro)" << endl ;
   exit(1);
}

// -----------------------------------------------------------------------------
// Actualiza el estado del objeto tras transcurrir un intervalo de tiempo
// (recorre todos los parámetros y los actualiza uno a uno, para ello
// llama a actualizarEstadoParametro)
// dtSec : es el tiempo en segundos transcurrido desde el inicio de las
//         animaciones o la última llamada a este método

void Objeto3D::actualizarEstado( const float dtSec )
{
   initTP();
   for( unsigned i = 0 ; i < leerNumParametros() ; i++  )
   {
      tiempo_par_sec[i] += dtSec ;
      actualizarEstadoParametro( i, tiempo_par_sec[i] );
   }
}

// -----------------------------------------------------------------------------
// Pone los valores de los parámetros a cero (estado inicial)

void Objeto3D::resetParametros()
{
   initTP();
   for( unsigned i = 0 ; i < leerNumParametros() ; i++  )
   {
      tiempo_par_sec[i] = 0.0 ;
      actualizarEstadoParametro( i, tiempo_par_sec[i] );
   }
}

// -----------------------------------------------------------------------------
// la primera vez que se llama, inicializa los valores base de los
// parámetros (a cero), las siguientes comprueba que tiempo_par_sec tiene tantas
// entradas como parámetros.

void Objeto3D::initTP()
{
   if ( tiempo_par_sec.size() == 0  )
      for( unsigned i = 0 ; i < leerNumParametros() ; i++ )
         tiempo_par_sec.push_back( 0.0 );
   else
      assert( tiempo_par_sec.size() == leerNumParametros() );
}

// -----------------------------------------------------------------------------
// Destructor
Objeto3D::~Objeto3D()
{
   using namespace std ;
   cout << "destruyendo objeto3D de nombre: " << nombre_obj << endl << flush ;
}
// -----------------------------------------------------------------------------


