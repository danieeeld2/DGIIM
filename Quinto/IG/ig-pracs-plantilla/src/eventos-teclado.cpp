// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de eventos de teclado
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de la función gestora del evento de teclado 
// ** (función 'FGE_PulsarLevantarTecla')
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


#include "ig-aux.h"  // include cabeceras de opengl / glut / glut / glew
#include "camara.h"
#include "seleccion.h"
#include "animacion.h"
#include "materiales-luces.h"
#include "eventos-teclado.h"


// evita la necesidad de escribir std::
using namespace std ;


// ---------------------------------------------------------------------
// F.G. del evento de pulsar o levantar una tecla

void FGE_PulsarLevantarTecla( GLFWwindow* window, int key, int scancode, int action, int mods )
{
   assert( apl != nullptr );
   using namespace std ;

   if ( action == GLFW_PRESS ) // solo estamos interesados en el evento de levantar una tecla
      return ;                 // (ignoramos el evento generado al pulsar)

   bool redib = true ; // true sii al final de esta función es necesario redibujar

   // recuperar y comprobar camara y objeto actual
   Escena *            escena = apl->escenas[apl->ind_escena_act] ; assert( escena != nullptr);
   CamaraInteractiva * camara = escena->camaraActual();             assert( camara != nullptr );
   Objeto3D *          objeto = escena->objetoActual();             assert( objeto != nullptr );

   // si está pulsada la tecla 'L', actualizar la colección de fuentes de luz y terminar
   if ( glfwGetKey( window, GLFW_KEY_L) == GLFW_PRESS )
   {
      // COMPLETAR: Práctica 4: procesar la tecla 'key' para actualizar la colección de fuentes
      // de luz actual (usar método 'colFuentes' de la escena activa para obtener un puntero), llamar a
      // 'ProcesaTeclaFuenteLuz', si devuelve 'true', forzar revisualizar escena (asignar 'revisualizar_escena')
      // .....

      return ; // finalizar la f.g.e, ya que si está la tecla L pulsada no se mira ninguna otra tecla.
   }

   // si está pulsada la tecla 'A', la tecla se procesa en 'animacion.cpp'
   // actúa sobre el objeto que se está visualizando
   
   if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
   {
      // COMPLETAR: Práctica 3: procesar pulsación de una tecla de animación
      //
      // procesar la tecla en la variable 'key' para actualizar el estado de animación
      // del objeto actual ('objeto'), se debe usar 'ProcesarTeclaAnimacion': si devuelve
      // 'true', forzar revisualizar escena (asignando valor a 'revisualizar_escena')
      

      return ; // finalizar la f.g.e, ya que si está la tecla A pulsada no se mira ninguna otra tecla.
   }

   constexpr float
      cam_d_incre_tecla   = 1.0,     // incremento de 'cam_d' por teclado (debe ser >= 1.0)
      cam_ab_incre_tecla  = 3.0;     // incremento de ángulos por teclado

   switch ( key )
   {
      // teclas de camara :

      case GLFW_KEY_LEFT:
         camara->desplRotarXY( +cam_ab_incre_tecla, 0.0 );
         break;

      case GLFW_KEY_RIGHT:
         camara->desplRotarXY( -cam_ab_incre_tecla, 0.0 );
         break;

      case GLFW_KEY_UP:
         camara->desplRotarXY( 0.0, +cam_ab_incre_tecla  );
         break;

      case GLFW_KEY_DOWN:
         camara->desplRotarXY( 0.0, -cam_ab_incre_tecla );
         break;

      case GLFW_KEY_KP_SUBTRACT :  // tecla '-' en el teclado numérico
         camara->moverZ( +cam_d_incre_tecla );
         break;

      case GLFW_KEY_KP_ADD :        // tecla '+' en el teclado numérico ¿?
         camara->moverZ( -cam_d_incre_tecla );
         break;

      case GLFW_KEY_C :
         camara->siguienteModo();
         break ;

      case GLFW_KEY_V :
         escena->siguienteCamara() ;
         break ;

      // teclas para cambiar de escena y de objeto dentro de la escena

      case GLFW_KEY_O :
         escena->siguienteObjeto() ;
         break ;

      case GLFW_KEY_P :
         assert( apl->ind_escena_act < apl->escenas.size());
         apl->ind_escena_act = (apl->ind_escena_act+1) % apl->escenas.size();
         cout << "Escena actual cambiada a: " << (apl->ind_escena_act+1) << endl << flush ;
         break ;


      // tecla para terminar
      case GLFW_KEY_ESCAPE:
      case GLFW_KEY_Q:
         apl->terminar_programa = true ;
         break ;

      // teclas variadas:

      case GLFW_KEY_E:
         apl->dibujar_ejes = ! apl->dibujar_ejes ;
         cout << "Dibujar ejes: " << (apl->dibujar_ejes? "activado." : "desactivado.") << endl << flush ;
         break ;

      case GLFW_KEY_N :
         apl->visualizar_normales = ! apl->visualizar_normales ;
         cout << "Visualizar normales: " << (apl->visualizar_normales ? "activado." : "desactivado.") << endl << flush ;
         break ;

      case GLFW_KEY_M :
         apl->modo_visu = ModosVisu( (int(apl->modo_visu)+1) % int(ModosVisu::num_modos) );
         cout << "Modo de visualización cambiado a: '" << nombreModoVisu[int(apl->modo_visu)] << "'" << endl << flush ;
         break ;

      case GLFW_KEY_W :
         apl->dibujar_aristas = ! apl->dibujar_aristas ;
         cout << "Dibujar aristas: " << (apl->dibujar_aristas? "activado" : "desactivado" ) << endl ;
         break ;

      case GLFW_KEY_I :
         apl->iluminacion = ! apl->iluminacion ;
         cout << "Iluminación : " << (apl->iluminacion ? "activada" : "desactivada") << endl << flush ;
         break ;

      case GLFW_KEY_F :
          apl->usar_normales_tri = ! apl->usar_normales_tri ;
          cout << "La iluminación usa " << (apl->usar_normales_tri ? "la normal del triángulo" : "las normales de vértices (interpoladas)") << endl << flush ;
          break ;

      case GLFW_KEY_G :
         apl->suavizar_aristas = ! apl->suavizar_aristas ;
         cout << "suavizar_aristas : " << (apl->suavizar_aristas ? "activado" : "desactivado") << endl << flush ;
         break ;





      // COMPLETAR: práctica 5: conmutar 'apl->visualizar_fbo' con la tecla 'Y'
      //
      // Añadir un caso nuevo: si se ha pulsado la tecla 'Y' (GLFW_KEY_Y), conmutar 
      // el valor de 'apl->visualizar_fbo, e informar sobre si la visualización del 
      // FBO ha quedado activada o desactivada
      //


      case GLFW_KEY_T :
         apl->imprimir_tiempos = ! apl->imprimir_tiempos ;
         cout << "imprimir tiempos : " << (apl->imprimir_tiempos ? "activado" : "desactivado") << endl << flush ;
         break ;

      default:
         redib = false ; // para otras teclas, no es necesario redibujar
         break ;
   }
   // si se ha cambiado algo, forzar evento de redibujado
   if ( redib )
      apl->revisualizar_escena = true ;
}
