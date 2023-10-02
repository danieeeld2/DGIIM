// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de cámaras (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de la clase 'Viewport', 'Camara' y derivadas de 'Camara'
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


#include <cmath>     // std::cos, std::sin
#include <algorithm> // std::min, std::max
#include "ig-aux.h" 
#include "camara.h"

// *********************************************************************
// clase: Viewport

// ---------------------------------------------------------------------
// crea viewport de 512 x 512 con origen en (0,0)

Viewport::Viewport() 
{
   org_x    = 0 ;
   org_y    = 0 ;
   ancho    = 512 ;
   alto     = 512  ;
   ratio_yx = float(alto)/float(ancho) ;

   matrizVp    = MAT_Viewport( org_x, org_y, ancho, alto );
   matrizVpInv = MAT_Viewport_inv( org_x, org_y, ancho, alto );
}

// ---------------------------------------------------------------------

Viewport::Viewport( int p_org_x, int p_org_y, int p_ancho, int p_alto )
{
   org_x    = p_org_x ;
   org_y    = p_org_y ;
   ancho    = p_ancho ;
   alto     = p_alto ;
   ratio_yx = float(alto)/float(ancho) ;

   matrizVp    = MAT_Viewport( org_x, org_y, ancho, alto );
   matrizVpInv = MAT_Viewport_inv( org_x, org_y, ancho, alto );
}

// *********************************************************************
// class Camara
// clase base para cámaras

// -------------------------------------------------------------------------------
// fija las matrices model-view y projection en el cauce

void Camara::activar( Cauce & cauce )
{
   actualizarMatrices();
   cauce.fijarMatrizVista( matriz_vista );
   cauce.fijarMatrizProyeccion( matriz_proye );
   //using namespace std ;
   //cout << "Activada cámara: '" << descripcion() << "'" << endl ;
}

// -------------------------------------------------------------------------------
// cambio el valor de 'ratio_vp' (alto/ancho del viewport)

void Camara::fijarRatioViewport( const float nuevo_ratio )
{
   ratio_vp = nuevo_ratio ;
   matrices_actualizadas = false ;
}

// -----------------------------------------------------------------------------
// actualiza 'matriz_vista' y 'matriz_proye' a partir del ratio

void Camara::actualizarMatrices()
{
   using namespace glm ;

   if ( matrices_actualizadas )
      return ;

   matriz_vista = mat4(1.0);
   matriz_proye = scale( vec3{ 1.0f,1.0f/ratio_vp, 1.0f }) ;// MAT_Escalado( 1.0f, 1.0f/ratio_vp, 1.0f );
   matrices_actualizadas = true ;
}
// -----------------------------------------------------------------------------
// lee la descripción de la cámara (y probablemente su estado)

std::string Camara::descripcion()
{
   return "cámara (clase base)" ;
}

// ################################################################################
// class CamaraInteractiva
// clase base (abstracta) para cámaras interactivas (cámaras manipulables)


// ----------------------------------------------------------------------------
// hacer que apunte hacía el punto de atención 'paten' y cambiar de modo a modo examinar
// por defecto imprime mensaje de advertencia de que la cámra no ofrece esta funcionalidad

void CamaraInteractiva::mirarHacia( const glm::vec3 & paten )
{
   using namespace std ;
   cout << "esta cámara no puede apuntar a ningún objeto." << endl ;
}

// ----------------------------------------------------------------------------
// cambiar el modo de la camara al siguiente modo o al primero
// por defecto imprime mensaje de advertencia de que no ofrece esta funcionalidad

void CamaraInteractiva::siguienteModo()
{
   using namespace std ;
   cout << "esta cámara no tiene definidos varios modos de funcionamiento." << endl ;
}

// ******************************************************************
// class CamaraOrbitalSimple
//

// clase para una cámara orbital sencilla que siempre tiene el origen de
// coordenadas del mundo en el centro de la imagen (tiene un modo único)

// ----------------------------------------------------------------------------
// cambia la longitud usando 'dx' y la latitud usando 'dy'

void CamaraOrbitalSimple::desplRotarXY( const float da, const float db )
{
   a = a+da ;
   b = b+db ;
   matrices_actualizadas = false ;
}

// ----------------------------------------------------------------------------
// zoom 'dz' unidades respecto al origen (sin 'atravesarlo' nunca)

void CamaraOrbitalSimple::moverZ( const float dz )
{
   constexpr float
      d_min = 0.2 ,  // distancia mínima al origen
      rc    = 0.04 ; // ratio de crecimiento cuando 'dz=1'

   d = d_min + (d-d_min)*std::pow((1.0f+rc),dz) ;
   matrices_actualizadas = false ;
}

// ----------------------------------------------------------------------------
void CamaraOrbitalSimple::actualizarMatrices()
{
   using namespace glm ;
   matriz_vista = translate( vec3( 0.0, 0.0, -d) ) *          // MAT_Traslacion( { 0.0, 0.0, -d } ) *
                  rotate( radians(b),  vec3( 1.0,0.0,0.0 )) * // MAT_Rotacion( b,  { 1.0,0.0,0.0} ) *
                  rotate( radians(-a), vec3( 0.0,1.0,0.0 )) ; // MAT_Rotacion( -a, { 0.0,1.0,0.0}  ) ;

   constexpr float
      fovy_grad = 60.0,
      near      = 0.05,
      far       = near+1000.0 ;

   matriz_proye = perspective( radians(fovy_grad), 1.0f/ratio_vp, near, far ); //MAT_Perspectiva( fovy_grad, ratio_vp, near, far ); // CUA: ratio_vp es y/x, pero esta función esperael 'aspect', que parece ser x/y
   matrices_actualizadas = true ;
}
// -----------------------------------------------------------------------------
// lee la descripción de la cámara (y probablemente su estado)

std::string CamaraOrbitalSimple::descripcion()
{
   using namespace std ;
   return string("cámara órbital simple, ángulos: a = ") + to_string(a) + ", b = " + to_string(b) ;
}

// ******************************************************************
// class Camara3Modos
// cámara interactiva completa, que puede funcionar en tres modos, y
// que puede centrarse en un punto (pasa a modo examinar)
//
// Los modos son:
//
//   ** modo examinar (o modo orbital), relativo a un punto de atención
//   ** modo primera persona con rotaciones (típico de los videojuegos)
//   ** modo primera persona con desplazamientos  (horizontal o vertical)

static const std::string nombre_modo[3] =
   { "examinar (o modo orbital)",
     "primera persona con rotaciones",
     "primera persona con desplazamientos"
   };

// ----------------------------------------------------------------------------
// convierte unas coordenadas esfericas (a,b,r) a cartesianas (x,y,z)
// ('a' es el ángulo de rotacion en radianes respecto del eje Z, en el plano Y=0)

glm::vec3 Cartesianas( const glm::vec3 & esfericas )
{
   const float
      sa = std::sin(esfericas[0]), ca = std::cos(esfericas[0]),
      sb = std::sin(esfericas[1]), cb = std::cos(esfericas[1]),
      r  = esfericas[2] ;

   return glm::vec3( r*sa*cb, r*sb, r*ca*cb ) ;
}

// ----------------------------------------------------------------------------
// convierte unas coordenadas cartesianas (x,y,z) a esféricas (a,b,r)

glm::vec3 Esfericas( const glm::vec3 & cartesianas )
{
   const float
      x  = cartesianas[0],
      y  = cartesianas[1],
      z  = cartesianas[2],
      r  = std::sqrt( x*x + y*y + z*z ), // longitud del vector  (radio)
      rh = std::sqrt( x*x + z*z );  // longitud de la proyección horizontal

   return glm::vec3 { atan2f(x,z), atan2f(y,rh), r } ;
}

// ----------------------------------------------------------------------------
// comprueba que las conversiones entre cartesianas y esféricas son correctas

void TestCartesianasPolares()
{
   using namespace glm ;

   float max = 0.0 ;
   for( unsigned long i = 0 ; i < 1024*1024 ; i++ )
   {
      const float
         x = float(rand())/float(RAND_MAX),
         y = float(rand())/float(RAND_MAX),
         z = float(rand())/float(RAND_MAX) ;
      const glm::vec3
         cart  = { 2.0f*x-1.0f, 2.0f*y-1.0f, 2.0f*z-1.0f },
         pol   = Esfericas( cart ),
         cart2 = Cartesianas( pol );
      const float
         lsq = length2(cart2-cart); 
      if ( lsq > max )
         max = lsq ;
   }

   using namespace std ;
   cout << "Test: cart2 - cart, max diff sq == " << max << endl ;
}

// ----------------------------------------------------------------------------
// crea una cámara perspectiva con valores por defecto

Camara3Modos::Camara3Modos()
{
   //using namespace std ;
   //cout << "creacion Camara3Modos, origen == " << origen << endl ;
   // (todos los parámetros toman valores por defecto, ver la decl. de la clase)
   matrices_actualizadas = false ;

   // test cartesianas - esfericas
   //TestCartesianasPolares();
}

// ----------------------------------------------------------------------------
// crea una cámara, inicialmente en modo examinar, con el punto
// de atención en el origen, se especifica:
//
// * perspectiva_ini : true si es una camara perspectiva, false si es ortográfica
// * ratio_vp_ini    : ratio del viewport (y/x) inicial
// * origen_ini      : punto de vista inicial (origen marco de cámara)
// * punto_aten_ini  : punto de atención
// * fovy_grad_ini   : si es perspectiva, la apertura de campo vertical, en grados

Camara3Modos::Camara3Modos( const bool perspectiva_ini,
                            const glm::vec3 & origen_ini, const float ratio_vp_ini,
                            const glm::vec3 & punto_aten_ini, const float fovy_grad_ini )
{
   //using namespace std ;
   //cout << "creacion Camara3Modos, origen == " << origen << endl ;
   using namespace glm ;

   assert( 5.0 < fovy_grad_ini && fovy_grad_ini < 178.0 );
   assert( 0.0 <= ratio_vp_ini );
   const float d_sq = length2(punto_aten_ini-origen_ini) ; assert( 0.0 < d_sq );

   // inicializar parámetros con valores distintos a los valores por defecto:
   perspectiva     = perspectiva_ini ;
   punto_atencion  = punto_aten_ini  ;
   ratio_vp        = ratio_vp_ini ;
   org_cartesianas = origen_ini - punto_aten_ini ; assert( 0.01 <= length(org_cartesianas) );
   org_polares     = Esfericas( org_cartesianas );
   fovy_grad       = fovy_grad_ini ;

   actualizarEjesMCV();

   matrices_actualizadas = false ;
}

// ----------------------------------------------------------------------------
// desplazar o rotar la cámara en horizontal 'dx' unidades y en vertical 'dy' unidades
// (en horizontal y en vertical aquí se entiende relativo al marco de camara)

void Camara3Modos::desplRotarXY( const float da, const float db )
{
   switch( modo_actual )
   {
      case ModoCam::examinar :
      {
         // COMPLETAR: práctica 5: rotar la cámara en modo examinar
         //
         // actualizar las dos primeras componentes (ángulos) de las coordenadas polares
         // actualizar las coordenadas cartesianas a partir de las polares
         // .....

         actualizarEjesMCV();
         break ;
      }
      case ModoCam::prim_pers_rot :
      {
         // COMPLETAR: práctica 5: rotar la cámara en modo 1a persona con rotaciones
         //
         // 1. actualizar las dos primeras componentes (ángulos) de las coordenadas polares (igual que en el modo examinar)
         // 2. calcular las nuevas coordenadas cartesianas, y el vector de desplazamiento desde las nuevas a las antiguas
         // 3. restarle al punto de atención ese vector de desplazamiento
         // 4. actualizar las coordenadas cartesianas
         // 5. actualizar los ejes del MCV (actualizarEjesMCV)
         // .....

         actualizarEjesMCV() ;
         break ;
      }
      case ModoCam::prim_pers_despl :
      {
         // COMPLETAR: práctica 5: desplazar la cámara en modo 1a persona con desplazamientos
         //
         // Desplazar el punto de atención 'da' unidades en el eje X de la cámara, y
         // 'db' unidades en el eje Y de la cámara.
         // .....
         // (nota: los ejes no cambian)

         break ;
      }
   }
   matrices_actualizadas = false ;
}
// ----------------------------------------------------------------------------
// acercar/alejar la cámara respecto al punto de atención
// (el eje es el eje Z, relativo al marco de la camara, es decir, perpendicular al plano de visión)

void Camara3Modos::moverZ( const float dz )
{

   switch( modo_actual )
   {
      case ModoCam::examinar :
      {
         // COMPLETAR: práctica 5: mover en Z la cámara en modo 'examinar'
         //
         // actualizar el radio de las coordenadas polares
         // actualizar las coordenadas cartesianas a partir de las polares
         // nota: los ejes no cambian, ni el punto de atención
         // .....

         break ;
      }
      case ModoCam::prim_pers_rot :
      case ModoCam::prim_pers_despl :
      {
         // COMPLETAR: práctica 5: mover en Z la cámara en modo 'primera persona'
         //
         // desplazar el punto de atención 'dz' unidades en el eje Z
         // nota: los ejes no cambian
         // .....

         break ;
      }
   }
   matrices_actualizadas = false ;
}
// ----------------------------------------------------------------------------
// hacer que apunte hacía el punto de atención 'nuevo_punto_aten' y pasar a modo examinar

void Camara3Modos::mirarHacia( const glm::vec3 & nuevo_punto_aten )
{
   // COMPLETAR: práctica 5: mirar hacia un punto y pasar a modo examinar 
   //
   // Actualizar 'punto_atencion', desplazarlo al nuevo punto de atencion
   // Actualizar las coordenadas cartesianas (desplazarlas)
   // Actualizar las coordenadas polares a partir de las cartesianas
   // Poner el modo actual en modo examinar


   // actualizar los ejes del marco de coordenadas del mundo
   actualizarEjesMCV();

   // marcar las matrices como 'no actualizadas'
   matrices_actualizadas = false ;
}
// ----------------------------------------------------------------------------
// cambiar el modo de la camara al siguiente modo o al primero

void Camara3Modos::siguienteModo()
{
   modo_actual = ModoCam( (int(modo_actual)+1) % 3) ;
   using namespace std ;
   cout << "Modo de cámara cambiado a: " << nombre_modo[int(modo_actual)] << "." << endl ;
   matrices_actualizadas = false ;
}
// ----------------------------------------------------------------------------
// Actualiza el array 'eje' a partir de 'org_cartesianas'

void Camara3Modos::actualizarEjesMCV()
{
   using namespace glm ;
   eje[Z] = normalize( org_cartesianas );
   eje[X] = normalize( cross( vec3( 0.0, 1.0, 0.0 ), eje[Z] ) );
   eje[Y] = normalize( cross( eje[Z], eje[X] ) );
}
// ----------------------------------------------------------------------------

void Camara3Modos::actualizarMatrices()
{
   using namespace glm ;
   const vec3      org  = punto_atencion + org_cartesianas ;
   constexpr float near = 0.05,
                   far  = near+1000.0 ;

   matriz_vista = MAT_Vista( eje, org );
   if ( perspectiva )
      matriz_proye = perspective( radians(fovy_grad), 1.0f/ratio_vp, near, far );  // CUA: ratio_vp es y/x, pero esta función esperael 'aspect', que parece ser x/y
   else
   {
      constexpr float s = 8.0 ;
      matriz_proye = ortho( -s/2.0f, +s/2.0f, -s*ratio_vp/2.0f, +s*ratio_vp/2.0f, -20.0f, 100.0f ); // MAT_Ortografica( -s/2.0f, +s/2.0f, -s*ratio_vp/2.0f, +s*ratio_vp/2.0f, -20.0f, 100.0f );
   }
   matrices_actualizadas = true ;
}
// ----------------------------------------------------------------------------

glm::vec3 Camara3Modos::puntoAtencion()
{
   return punto_atencion ;
}
// -----------------------------------------------------------------------------
// lee la descripción de la cámara (y probablemente su estado)

std::string Camara3Modos::descripcion()
{
   return std::string("cámara de 3 modos, ") +
          (perspectiva ? "perspectiva" : "ortográfica") +
          ", modo actual: " + nombre_modo[int(modo_actual)] + ")";
}
