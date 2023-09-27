// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Declaración de la clase 'AplicacionIG'
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** La clase 'AplicacionIG' contine
// **     
// **     + ventana GLFW
// **     + vector de escenas e índice de la escena actual
// **     + variables de estado para gestionar el bucle de eventos (revisualizar_escena, terminar_programa)
// **     + variables de estado del ratón para gestionar eventos de mover con botón pulsado (arrastrar).
// **     + diversas variables de estado que determinan como se visualizan los objetos, las animaciones, etc ....
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


#ifndef APLICACION_IG_H
#define APLICACION_IG_H

#include <vector>
#include "ig-aux.h"

// declaraciones adelantadas de clases (para poder declarar punteros antes de "ver" la estructura de la clase)
class Escena ;
class Cauce ;
class ColFuentesLuz ;
class ContextoVis ;
class CamaraInteractiva ;
class Material ;
class Objeto3D ;
class AplicacionIG ;
class Framebuffer ;
class PilaMateriales ;


// ---------------------------------------------------------------------
// tipo de datos enumerado para los modos de visualización:
enum class ModosVisu
{
   relleno,
   lineas,
   puntos,
   num_modos
} ;

const std::string nombreModoVisu[ int(ModosVisu::num_modos)+1 ] =
{
   "relleno",
   "líneas",
   "puntos",
   "*** NUM. MODOS. VIS. ***"
} ;


// puntero al objeto de la clase 'AplicacionIG' con variables y parámetros globales
extern AplicacionIG * apl ;

// --------------------------------------------------------------------
// Clase AplicacionIG 
// variables de configuración variadas, cauce, etc....

class AplicacionIG
{
   public:
   // Constructor:
   // crea el cauce, la pila de materiales, el vector de escenas
   AplicacionIG(); 

   // Inicializa GLFW, crea la ventana, registra funciones gestoras de eventos.
   // (se llama desde el constructor)
   void inicializarGLFW() ;

   // Gestiona un evento de cambio de tamaño de la ventana
   //
   // @param nuevo_ancho_fb (int) - nuevo ancho de la ventana
   // @param nuevo_alto_fb (int) - nuevo alto de la ventana
   //
   void cambioTamano( int nuevo_ancho_fb, int nuevo_alto_fb );

   // Ejecuta el bucle principal  de gestion de eventos GLFW, hasta que se cierra ventana o
   // bien 'terminar_programa' se pone a 'true' en algún gestor de eventos.
   void buclePrincipalGLFW( );

   // Visualiza la escena en la ventana GLFW, se llama durante el bucle de 
   // de gestión de eventos, en cada iteración, si hay que refrescar los contenidos de la ventana
   void visualizarFrame();

   // Función principal de selección, se llama al hacer click con el botón izquierdo
   // usa la posición donde se ha hecho click en coordenadas del dispositivo del FBO (enteras).
   // Si en ese pixel hay un objeto con identificador >0, ejecuta 'cuandoClick' del objeto.
   // y pone la camara actual de la escena actual mirando hacia el centro del objeto.
   //
   // @param x (int) -- posición en X del click (coords. de dispoitivo)
   // @param y (int) -- posición en Y del click (coords. de dispositivo)
   // @return (bool) true si se ha seleccionado algún objeto, false si no
   //
   bool seleccion( int x, int y );

   // puntero a la ventana GLFW que está usando la aplicación
   GLFWwindow * ventana_glfw = nullptr;  

   // puntero al cauce activo actualmente
   Cauce * cauce = nullptr ; 

   // punero al framebuffer usado para selección
   Framebuffer * fbo = nullptr ; 

   // puntero a la pila de materiales actual (incluye material actual)
   PilaMateriales * pila_materiales = nullptr ;

   // vector con punteros a las escenas que gestiona la aplicación
   std::vector<Escena *> escenas;                   
   
   // índice de la escena actual en el vector de escenas
   unsigned ind_escena_act = 0;      

   // factor de conversión para displays "retina" en macOS
   unsigned mouse_pos_factor = 1 ;      

   // versión de OpenGL (major y minor) - actualizado en 'InformeOpenGL'
   unsigned opengl_ver_major = 0;       
   unsigned opengl_ver_minor = 0 ;      

   // variables de estado para gestionar el bucle principal de eventos.
   // se modifican en las funciones gestoras de eventos y se tienen en cuenta 
   // en el bucle principal de eventos.

   bool revisualizar_escena = true;    // true indica que hay que redibujar la escena
   bool terminar_programa   = false;   // true indica que hay que cerrar la aplicación
   bool imprimir_tiempos    = false;   // 'true' imprimir tiempo por frame, 'false', no imprimir

   // modo de visualización actual
   ModosVisu modo_visu = ModosVisu::relleno ;

   // Tipo de normales para Phong shading:
   // true  --> usar normales de triángulos 
   // false -->  usar normales de vértices interpoladas (tradicional)
   bool usar_normales_tri = false ;

   // true -> dibujando en modo selección con FBO invisible (puede ser el back-buffer)
   bool modo_seleccion = false ;

   // indica si durante la visualización se usa iluminación y materiales (true), 
   // o simplemente se usa un color plano (false)
   bool iluminacion = true ;

   // Indica si queremos dibujar aristas al visualizar sólido (true) o no
   bool dibujar_aristas = false ;

   // Indica si queremos visualizar normales al visualizar los objetos (true) o no.
   bool visualizar_normales = false ;

   // true cuando se está en proceso de visualizar normales durante una llamada a 'Escena::visualizarNormales'
   //bool visualizando_normales = false ;

   // 'true' para dibujar ejes, 'false' -> no dibujar ejes
   bool dibujar_ejes = true ;

   // 'true' -> visualizar FBO de seleccion, 'false' -> no visualizarlo
   bool visualizar_fbo = false ;

   // numero de columnas (tam_x) y filas (tam_y) del viewport actual
   int ventana_tam_x = -1,
       ventana_tam_y = -1 ;
   
   // suavizar aristas (y puntos) si/no (no funciona en todos los drivers)
   bool suavizar_aristas = false ;
   



};


#endif // APLICACION_IG_H
