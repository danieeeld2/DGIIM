// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de animaciones (implementaciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementaciones de las funciones:
// **    + ActualizarEstado: actualiza el estado de un objeto 3D
// **    + AnimacionesActivadas: indica si las animaciones están activadas o no
// **    + ProcesarTeclaAnimacion: procesa una tecla pulsada a la vez que 'A'
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

#include "animacion.h" 

using namespace std::chrono ;
//using namespace tup_mat ;

// tipo de datos para duraciones en segundos
typedef duration<float,std::ratio<1,1>> DuracionSeg ;

// instante de inicio de animaciones o instante de la última actualización
time_point<steady_clock> ultima_actu ;

// valor que indica si las animaciones están activadas o no lo están
// (si lo están, se llama periodicamente a 'ActualizarEstado' para el objeto actual)

static bool animaciones_activadas = false ; 

// --------------------------------------------------------------------------

bool AnimacionesActivadas()
{
   return animaciones_activadas ;
}

// --------------------------------------------------------------------------

bool ActualizarEstado( Objeto3D & objeto )
{
   using namespace std ;
   //cout << __FUNCTION__ << ", actualizando estado de objeto == " << objeto.leerNombre() << ", num pars == " << objeto.leerNumParametros() << endl ;
   // si el objeto no tiene parámetros, no hay nada que hacer (no se puede animar)
   if ( objeto.leerNumParametros() == 0 )
      return false ;

   // calcular el instante actual y el tiempo transcurrido desde el anterior
   const time_point<steady_clock> ahora = steady_clock::now();
   const float tiempo_seg = DuracionSeg(ahora - ultima_actu).count();

   // fijar instante actual como instante de última actualización
   ultima_actu = ahora ;

   // actualizar el estado del objeto
   objeto.actualizarEstado( tiempo_seg );
   return true ; //
}

//----------------------------------------------------------------------
// modificar estado de las animaciones en respuesta a una tecla
// devuelve 'true' si se ha cambiado algo, false si no.

bool ProcesarTeclaAnimacion( Objeto3D * objeto, int glfw_key )
{
   using namespace std ;
   assert( objeto != nullptr );
   bool redisp = true ;

   switch( glfw_key )
   {
      //case GLFW_KEY_PAGE_UP :
      case GLFW_KEY_RIGHT_BRACKET : // tecla '+' en el teclado normal (NO en la plantilla)
      case GLFW_KEY_KP_ADD :    // tecla '+' en el teclado numérico ¿?
         if ( ! animaciones_activadas )
         {  animaciones_activadas = true ;
            ultima_actu = steady_clock::now(); // registrar instante de última actualización
            cout << "Animaciones activadas." << endl ;
         }
         else
         {  cout << "Las animaciones ya estaban activadas." << endl ;
            redisp = false ;
         }
         break ;

      //case GLFW_KEY_PAGE_DOWN :
      case GLFW_KEY_SLASH :        // tecla con '-' y '_' en el teclado normal (NO en la plantilla)
      case GLFW_KEY_KP_SUBTRACT :  // tecla '-' en el teclado numérico
         if ( animaciones_activadas )
         {  animaciones_activadas = false ;
            cout << "Animaciones desactivadas." << endl ;
         }
         else
         {  cout << "Las animaciones ya estaban desactivadas." << endl ;
            redisp = false ;
         }
         break ;

      case GLFW_KEY_LEFT :
         objeto->modificarIndiceParametroActivo( -1 );
         break ;

      case GLFW_KEY_RIGHT :
         objeto->modificarIndiceParametroActivo( +1 );
         break ;

      case GLFW_KEY_DOWN :
         if ( ! animaciones_activadas )
            objeto->modificarParametro( -1 );
         else
         {  cout << "No se puede modificar un parámetro con las animaciones activadas." << endl ;
            redisp = false ;
         }
         break ;

      case GLFW_KEY_UP :
         if ( ! animaciones_activadas )
            objeto->modificarParametro( +1 );
         else
         {  cout << "No se puede modificar un parámetro con las animaciones activadas." << endl ;
            redisp = false ;
         }
         break ;

      default :
         redisp = false ;
         break ;
   }
   return redisp ;
}
