// *********************************************************************
// **
// ** Gestión de materiales y texturas (declaraciones)
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** Declaraciones de:
// **    + clase 'Textura' (y derivadas 'TexturaXY', 'TexturaXZ')
// **    + clase 'Material' 
// **    + clase 'FuenteLuz'
// **    + clase 'ColFuentesLuz' (y la clase derivada 'Col2Fuentes')
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


#ifndef MATERIALES_HPP
#define MATERIALES_HPP

#include <vector>
#include "ig-aux.h"
#include "lector-jpg.h"



// *********************************************************************
// algunes declaraciones auxiliares importantes

class Material ;
class Textura  ;

//**********************************************************************
// posibles modos de generacion de coords. de textura

typedef enum
{  mgct_desactivada,
   mgct_coords_objeto,
   mgct_coords_ojo
}
   ModoGenCT ;

// *********************************************************************
// Clase Textura:
// ---------------
// clase que encapsula una imagen de textura de OpenGL, así como los
// parámetros relativos a como se aplica  a las primitivas que se dibujen
// mientras está activa

class Textura
{
   public:

   // carga una imagen de textura en la memoria de vídeo, e
   // inicializa los atributos de la textura a valores por defecto.
   // El nombre del archivo debe ir sin el 'path', se busca en 'materiales/imgs' y si 
   // no está se busca en 'archivos-alumno'
   Textura( const std::string & nombreArchivoJPG ) ;

   // libera la memoria dinámica usada por la textura, si hay alguna
   ~Textura() ;

   // activar una textura en un cauce
   void activar( ) ;

   protected: //--------------------------------------------------------

   void enviar() ;    // envia la imagen a la GPU (gluBuild2DMipmaps)

   bool
      enviada       = false ; // true si ha sido enviada, false en otro caso
   GLuint
      ident_textura = -1 ;// 'nombre' o identif. de textura para OpenGL
   unsigned
      ancho         = 0,  // número de columnas de la imagen
      alto          = 0 ; // número de filas de la imagen
   unsigned char *
      imagen        = nullptr ; // pixels de la imagen, por filas.
   ModoGenCT
      modo_gen_ct   = mgct_desactivada ;  // modo de generacion de coordenadas de textura
   float
      coefs_s[4]    = {1.0,0.0,0.0,0.0},   // si 'modo_gen_ct != desactivadas', coeficientes para la coord. S
      coefs_t[4]    = {0.0,1.0,0.0,0.0};   // idem para coordenada T
} ;

// *********************************************************************
// clase: TexturaXY
// ---------------------------------------------------------------------
// textura con generación automática de coords de textura (s=x,t=y)

class TexturaXY : public Textura
{
   public: TexturaXY( const std::string & nom );
} ;
class TexturaXZ : public Textura
{
   public: TexturaXZ( const std::string & nom );
} ;
// *********************************************************************
// Clase Material
// ---------------------------------------------------------------------
// clase que encapsula los atributos de un material, incluyendo la
// textura del mismo.

class Material
{
   public:

   // material por defecto (ver valores iniciales en las declaraciones)
   Material() {} ;

   // crea un material usando el color plano del objeto
   Material( /** const Tupla3f & p_color_ad,**/ const float p_k_amb, const float p_k_dif,
             const float p_k_pse, const float p_exp_pse );

   // crea un material usando una textura
   Material( Textura * p_textura, const float p_k_amb, const float p_k_dif,
             const float p_k_pse, const float p_exp_pse );

   // libera la memoria dinámica ocupada por el material (básicamente la textura)
   ~Material() ;

   // activa un material en el cauce actual.
   void activar(  ) ;

   // poner y leer el nombre del material
   void ponerNombre( const std::string & nuevo_nombre );
   std::string nombre() const ;

   //--------------------------------------------------------
   protected:

   //void coloresCero();// pone todos los colores y reflectividades a cero

   std::string
      nombre_mat = "material anónimo";  // nombre del material

   //Tupla3f
   //   color_ad = { 0.6f, 0.6f, 0.6f }; // color para componentes difusa y ambiental
   Textura *
      textura  = nullptr; // si != nullptr, se usa color de la textura en lugar de 'color_ad'
   float
      k_amb    = 0.2f,     // coeficiente de reflexión ambiente
      k_dif    = 0.8f,     // coeficiente de reflexión difusa
      k_pse    = 0.0f,     // coeficiente de reflexión pseudo-especular
      exp_pse  = 0.0f ;    // exponente de brillo para reflexion pseudo-especular
} ;

//**********************************************************************
// Clase FuenteLuz
// ---------------
// clase que contiene los atributo de una fuente de luz OpenGL

class FuenteLuz
{
   public:

   // inicializa la fuente de luz
   //
   // p_longi_ini == valor inicial del ángulo horizontal en grados
   // p_lati_ini  == idem del ángulo vértical
   // p_color     == color de la fuente de luz (amb, dif y spec )
   FuenteLuz( GLfloat p_longi_ini, GLfloat p_lati_ini, const glm::vec3 & p_color ) ;

   // cambia los atributos de la instancia en respuesta a una pulsación
   // de una tecla 'especial' (según la terminología de 'glut')
   //bool gestionarEventoTeclaEspecial( int key ) ;

   // para fuentes diraccionales, incrementar o decrementar la longitud
   // (en las puntuales no hace nada)
   void actualizarLongi( const float incre );
   // para fuentes diraccionales, incrementar o decrementar la longitud
   // (en las puntuales no hace nada)
   void actualizarLati( const float incre );

   //-------------------------------------------------------------------
   // variables de instancia:

   public:
    float
      longi,      // longitud actual de la fuente direccional (en grados, entre 0 y 360)
      lati ;      // latitud actual de la fuente direccional (en grados, entre -90 y 90)

   protected:
   glm::vec3
      color ;     // color de la fuente de luz (sirve para todas las componentes del MIL)
   
   float
      longi_ini,  // valor inicial de 'longi'
      lati_ini ;  // valor inicial de 'lati'

   friend class ColFuentesLuz ;
} ;

//**********************************************************************
// Clase ConjuntoFuentes
// ---------------
// clase que contiene los atributos de una coleccion de fuentes de luz OpenGL

class ColFuentesLuz
{
   public:

   ColFuentesLuz() ; // crea la colección vacía
   ~ColFuentesLuz() ;

   // inserta una nueva
   void insertar( FuenteLuz * pf ) ;

   // activa esta colección de fuentes en el cauce actual
   void activar(  );

   // pasa a la siguiente fuente de luz (si d==+1), o a la anterior (si d==-1)
   // aborta si 'd' no es -1 o +1, inicialmente es la fuente 0
   void sigAntFuente( int d ) ;

   // devuelve un puntero a la fuente de luz actual
   FuenteLuz * fuenteLuzActual() ;

   private:

   std::vector<FuenteLuz *> vpf ; // vector de punteros a fuentes

   GLint    max_num_fuentes = 0 ; // máximo número de fuentes
   unsigned i_fuente_actual = 0 ; // fuente que se modifica al llamar a 'actualizar' (rota con pg.arriba y pg.abajo)

} ;

// --------------------------------------------------------------------------
// PilaMateriales:clase para un vector (usado como pila FIFO) con punteros a 
// materiales, y además un puntero al material actual.
//
class PilaMateriales 
{
   public:
   
   PilaMateriales() {  }
   void push();   // guarda el material actual en la pila (NO puede ser nulo)
   void activar( Material * nuevo_actual ); // cambia el material actual y lo activa 
   void pop();    // invoca 'activar' para el material en el tope y lo elimina del tope
   
   private:
   std::vector<Material *> vector_materiales ;  // pila de materiales guardados
   Material * actual = nullptr ;                // material actual
} ;

// --------------------------------------------------------------------------
// Actualizar una colección de fuentes en función de una tecla GLFW pulsada
// (se usa el código glfw de la tecla, se llama desde 'main.cpp' con L pulsada)
// devuelve 'true' sii se ha actualizado algo

bool ProcesaTeclaFuenteLuz( ColFuentesLuz * col_fuentes, int glfw_key );

// *********************************************************************
// Clase Col2Fuentes
// ---------------
// derivada de 'ColFuentes' incluye dos fuentes de luz.

class Col2Fuentes : public ColFuentesLuz
{
   public:
      Col2Fuentes() ;
} ;


#endif
