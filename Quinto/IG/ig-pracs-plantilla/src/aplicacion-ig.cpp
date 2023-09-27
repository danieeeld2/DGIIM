// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Implementación de la clase 'AplicacionIG' y puntero a la aplicación actual.
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de los métodos de la clase
// ** Puntero a la aplicación actual, inicialmente nulo (la instancia se crea en la func. 'main')
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

#include "aplicacion-ig.h"
#include "eventos-teclado.h"
#include "eventos-raton.h"
#include "escena.h"
#include "materiales-luces.h"
#include "animacion.h"

AplicacionIG * apl = nullptr ;

// ---------------------------------------------------------------------
// F.G. del evento de cambio de tamaño de la ventana (del framebuffer)

void FGE_CambioTamano( GLFWwindow* ventana_glfw, int nuevo_ancho_fb, int nuevo_alto_fb )
{
   assert( apl != nullptr );
   apl->cambioTamano( nuevo_ancho_fb, nuevo_alto_fb );
}

// -----------------------------------------
// constructor: inicializa la aplicación: 
//    + inicializa GLFW, crea la ventana, 
//    + inicializa GLEW, OpenGL,
//    + crea el cauce, la pila de materiales
//    + crea el vector de escenas                    

AplicacionIG::AplicacionIG()
{
   using namespace std ;
   
   // Inicializar GLFW y crear la ventana 
   inicializarGLFW();

   // Inicialización de GLEW (dejar esta llamada siempre: en macOS no hace nada)
   InicializaGLEW();  

   // escribe características de OpenGL en pantalla (ver 'ig-aux.cpp')
   InformeOpenGL() ; 

   // Crea el objeto Cauce (compila los 'shaders')
   cauce = new Cauce() ;
   assert( cauce != nullptr );

   // Crea la pila de materiales 
   pila_materiales = new PilaMateriales();
   assert( pila_materiales != nullptr );

   // crear los objetos y las escenas que forman, insertar escenas en 'escenas'
   escenas.push_back( new Escena1() );

   // COMPLETAR: práctica 2: añadir escena de la práctica 2
   //
   // hacer 'push_back' en el vector de escenas de una instancia de 'Escena2'
   // ......


   // COMPLETAR: práctica 3: añadir escena de la práctica 3
   //
   // hacer 'push_back' en el vector de escenas de una instancia de 'Escena3'
   // ......


   // COMPLETAR: práctica 4: añadir escena de la práctica 4
   //
   // hacer 'push_back' en el vector de escenas de una instancia de 'Escena4'
   // ......


   // COMPLETAR: práctica 5: añadir escena de la práctica 5
   //
   // hacer 'push_back' en el vector de escenas de una instancia de 'Escena5'
   // ......




   cout << "Objetos creados." << endl ;
}

// ---------------------------------------------------------------------
// gestiona un cambio de tamaño de la ventana de la aplicación

void AplicacionIG::cambioTamano(int nuevo_ancho_fb, int nuevo_alto_fb )
{
   // actualizar 'ventana_tam_x' y 'ventana_tam_y' (en la aplicación)
   ventana_tam_x = nuevo_ancho_fb ;
   ventana_tam_y = nuevo_alto_fb ;

   // forzar un nuevo evento de redibujado, para actualizar ventana
   revisualizar_escena = true ;
}


// ---------------------------------------------------------------------
// inicialización de GLFW: creación de la ventana, designar FGEs. Se llama desde el constructor.

void AplicacionIG::inicializarGLFW(  )
{
   using namespace std ;

   // Tendrán la posicion y tamaño de la ventana y el framebuffer
   int fbx, fby, wx, wy, px, py ; 

   // Inicializacion y configuracion de la librería GLFW:
   glfwSetErrorCallback( ErrorGLFW ); // fijar función llamada ante error (aborta, ver 'ig-aux.cpp')
   glfwInit() ;                       // inicializacion de GLFW

   // Especificar versión de OpenGL y parámetros de compatibilidad que se querrán
   // (pedimos una version 'compatible' con OpenGL 3.3 'core', creo que eso incluye versiones posteriores)
   
   glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); 
   glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 ); 
   glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE ); 
   glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
   
   // Crear y posicionar la ventana,
   TamPosVentanaGLFW( wx, wy, px, py ); // calcula pos. y tam., usando tam. escritorio (ver 'ig-aux.cpp')
   
   ventana_glfw = glfwCreateWindow( wx, wy, "Practicas IG GIM (23-24)", nullptr, nullptr ); // crea ventana
   assert( ventana_glfw != nullptr );

   glfwSetWindowPos( ventana_glfw, px, py ); // posiciona la ventana


   // Establecer el 'rendering context' de la ventana como el 'context' actual
   glfwMakeContextCurrent( ventana_glfw );

   // Leer el tamaño real actual de la ventana (ventana_tam_x/_y)
   // * Los eventos de ratón del gestor de ventanas usan el tamaño de la ventana.
   // * OpenGL usa el tamaño del framebuffer 
   // En algunos casos ambos tamaños pueden ser distintos, así que a veces es necesario 
   // usar un factor de conversión para las coordenadas de los eventos de ratón.

   glfwGetWindowSize( ventana_glfw, &wx, &wy );
   glfwGetFramebufferSize( ventana_glfw, &fbx, &fby );
   ventana_tam_x    = fbx > 0 ? fbx : wx ;
   ventana_tam_y    = fby > 0 ? fby : wy ;
   mouse_pos_factor = fbx>0 ? fbx/wx : 1 ;  // en displays macos retina, esto es 2
   cout << "Factor de posición del mouse == " << mouse_pos_factor << endl ;

   // define la imagen que se usará para el icono de la ventana glfw
   // (únicamente en Windows y Linux, en macOs no hace nada)
   FijarImagenIconoVentana( ventana_glfw );

   // Definir las diversas funciones gestoras de eventos que GLFW debe invocar
   // (lo hace en glfwPollEvents o en glfwWaitEvents)
   // (esto debe ser lo último)

   glfwSetFramebufferSizeCallback ( ventana_glfw, FGE_CambioTamano );
   glfwSetKeyCallback             ( ventana_glfw, FGE_PulsarLevantarTecla );
   glfwSetMouseButtonCallback     ( ventana_glfw, FGE_PulsarLevantarBotonRaton );
   glfwSetCursorPosCallback       ( ventana_glfw, FGE_MovimientoRaton );
   glfwSetScrollCallback          ( ventana_glfw, FGE_Scroll );
}

// ---------------------------------------------------------------------
// Método que visualiza la escena en la ventana GLFW, se llama cada vez 
// que hay que refrescar los contenidos de la ventana

void AplicacionIG::visualizarFrame()
{
   using namespace std ;
   CError();

   // asegurarnos de que existe un cauce y una escena
   assert( cauce != nullptr );
   Escena * escena = escenas[ind_escena_act] ; assert( escena != nullptr );

   // Configuración de OpenGL:
   //    + habilitar test de comparación de profundidades para 3D (y 2D)
   //      (no está por defecto: https://www.opengl.org/wiki/Depth_Buffer)
   //    + deshabilitar filtrado de triangulos por su orientación:
   //    + dibujar los polígonos rellenos más atrás que las aristas (fijar el 'polygon offset')
   
   glEnable( GL_DEPTH_TEST );   
   glDisable( GL_CULL_FACE );  
   glEnable( GL_POLYGON_OFFSET_FILL ); 
   glPolygonOffset( 1.0, 1.0 );    
   CError();
 
   // fijar el viewport
   glViewport( 0, 0, ventana_tam_x, ventana_tam_y );
   CError();

   // Establecer color de fondoy limpiar la ventana

   glClearColor( 0.2, 0.25, 0.3, 1.0 );
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   CError();

   // visualizar la escena actual
   escena->visualizarGL( );
   CError();

   // visualizar las normales del objeto.
   if ( apl->visualizar_normales ) 
      escena->visualizarNormales(  );
   


   // visualizar en pantalla el buffer trasero (donde se han dibujado las primitivas)
   glfwSwapBuffers( ventana_glfw );

   // si queremos imprimir los tiempos por cuadro, hacerlo.
   if ( imprimir_tiempos )
      ImprimirFPS();
}


// ---------------------------------------------------------------------
// bucle principal  de gestion de eventos GLFW

void AplicacionIG::buclePrincipalGLFW(  )
{
   terminar_programa   = false ;
   revisualizar_escena = true ;   // forzar visualización la primera vez

   while ( ! terminar_programa  )
   {
      // 1. visualizar escena 

      if ( revisualizar_escena )      //  si ha cambiado algo:
      {                               //
         visualizarFrame();          //     dibujar la escena
         revisualizar_escena = false; //     evitar que se redibuje continuamente
      }

      // 2. determinar si hay animaciones activas
      //
      // hay una animación en curso si están las animaciones activdas por el usuario y
      // además el objeto actual tiene al menos un parámetro animable:

      Objeto3D * objeto = escenas[ind_escena_act]->objetoActual() ; assert( objeto != nullptr );
      const bool animacion_activa = AnimacionesActivadas() && 0 < objeto->leerNumParametros() ;
      
      // 3. procesar eventos

      if ( animacion_activa )                  // si hay alguna animación en curso
      {                                        //
         glfwPollEvents();                     // procesar todos los eventos pendientes, y llamar a la función correspondiente, si está definida
                                               //
         if ( ! revisualizar_escena )          // si no es necesario redibujar la ventana
            if ( ActualizarEstado( *objeto ) ) //  actualiza estado, devuelve 'true' si 'objeto' tiene parámetros animables
                  revisualizar_escena = true ; //  es necesario redibujar pq. el objeto se ha actualizado
      }                                        //
      else                                     // si no hay una animacion en curso
         glfwWaitEvents();                     //   esperar hasta que haya un evento y llamar a la función correspondiente, si está definida

      // 4. determinar si se debe terminar el programa
      //
      // actualiza 'terminar_programa' si GLFW indica que se debe cerrar la ventana
      
      terminar_programa = terminar_programa || glfwWindowShouldClose( ventana_glfw ) ;
   }

   // finalizar la librería GLFW (no se va usar más)
   glfwTerminate(); 

}
