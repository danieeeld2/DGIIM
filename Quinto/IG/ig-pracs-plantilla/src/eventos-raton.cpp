// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de eventos de ratón
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las funciones gestoras de eventos (FGEs) producidos 
// ** por el ratón:
// **
// **     + FGE_Scroll - movimiento de la rueda del ratón
// **     + FGE_PulsarLevantarBotonRaton - botones del ratón
// **     + FGE_MovimientoRaton - movimiento del ratón (con un botón pulsado, si no se ignora)
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


#include "ig-aux.h"  
#include "camara.h"
#include "seleccion.h"
#include "animacion.h"
#include "eventos-teclado.h"

// evita la necesidad de escribir std::
using namespace std ;

// variables de estado para gestionar eventos de arrastrar ratón
static unsigned x_ant_mabd ;  // coord. X anterior del ratón en modo arrastrar con botón derecho pulsado
static unsigned y_ant_mabd ;  // coord. Y anterior del ratón en modo arrastrar con botón derecho pulsado


// --------------------------------------------------------------------
// función gestora del evento de hacer scroll
// (se registra con 'glfwSetScrollCallback'

void FGE_Scroll( GLFWwindow* window, double xoffset, double yoffset  )
{
   assert( apl != nullptr );

   if ( fabs( yoffset) < 0.05 ) // si hay poco movimiento vertical, ignorar el evento
      return ;

   constexpr float cam_d_z_incre_scroll = 1.0 ;
   const     float direccion            = 0.0 < yoffset ? +1.0 : -1.0 ;

   CamaraInteractiva * camara = apl->escenas[apl->ind_escena_act]->camaraActual() ; 
   assert( camara!= nullptr );

   camara->moverZ( direccion*cam_d_z_incre_scroll ) ;
   apl->revisualizar_escena = true ;
}

// --------------------------------------------------------------------
// función gestora del evento de pulsar/levantar tecla del ratón
// (se registra con 'glfwSetMouseButtonCallback'

void FGE_PulsarLevantarBotonRaton( GLFWwindow* window, int button, int action, int mods )
{
   assert( apl != nullptr );

   // solo estamos interesados en eventos de pulsar algún botón (no levantar)
   if ( action != GLFW_PRESS )
      return ;

   // leer la posición del puntero de ratón en x,y (enteros)
   double x_f,y_f ;
   glfwGetCursorPos( window, &x_f, &y_f );
   const int x = int(x_f), y = int(y_f);

   //cout << "click, tam ventana == " << apl->ventana_tam_x << " x " << apl->ventana_tam_y << endl ;
   //cout << "click, cursor pos  == " << x << ", " << y <<  endl ;

   if ( button == GLFW_MOUSE_BUTTON_LEFT )
   {
      // pulsar botón izquierdo: selección
      if ( apl->seleccion( x*apl->mouse_pos_factor, (apl->ventana_tam_y - y*apl->mouse_pos_factor) ) )
         apl->revisualizar_escena = true ;
   }
   else if ( button == GLFW_MOUSE_BUTTON_RIGHT )
   {
      // pulsar botón derecho: inicio de modo arrastrar con botón derecho pulsado:
      x_ant_mabd = x ; // registrar posición de inicio en X
      y_ant_mabd = y ; // registrar posición de inicio en Y
      apl->revisualizar_escena = true ;
   }
}

// --------------------------------------------------------------------
// función gestora del evento de ratón movido a una nueva posición
// (se registra con 'glfwSetCursorPosCallback'

void FGE_MovimientoRaton( GLFWwindow* window, double xpos, double ypos )
{
   assert( apl != nullptr );

   // Ignorar evento si no está pulsado el botón derecho
   if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_RIGHT ) != GLFW_PRESS )
      return ;

   // Estamos en modo arrastrar con el botón derecho pulsado:
   // Actualizar la cámara actual.

   constexpr float delta = 1.0; // incremento de ángulos con el ratón (por pixel)

   // calcular el desplazamiento en pixels en X y en Y respecto de la última posición
   const int
      x  = int( xpos ),
      y  = int( ypos ),
      dx = x - x_ant_mabd ,
      dy = y - y_ant_mabd ;

   // usar desplazamientos para desplazar/rotar la cámara actual en X y en Y
   CamaraInteractiva * camara = apl->escenas[apl->ind_escena_act]->camaraActual() ; assert( camara!= nullptr );
   camara->desplRotarXY( -dx*delta, dy*delta );

   // registrar (x,y) como la última posición del ratón
   x_ant_mabd = x ;
   y_ant_mabd = y ;

   // forzar que la escena se vuelva a visualizar
   apl->revisualizar_escena = true ;

}