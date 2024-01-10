// Shader program object wrapper class

#ifndef CAUCE_H
#define CAUCE_H

#include <vector>
#include "glincludes.h"


// ****************************************************************************************

// Clase para el cauce de funcionalidad programable (OpenGL 3.3 o superior)
//
class Cauce
{
   public: 

   // crea un objeto cauce vacío
   Cauce() ;

   // compila un shader y lo adjunta al objeto programa 'id_prog' (que debe ser >0)
   //
   // @param shader_type        (GLenum) one of: GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
   // @param shader_description (const char *) text description for error log ('vertex shader', 'fragment shader', etc...)
   // @param shader_source      (const char *) source string
   //
   GLuint compilarAdjuntarShader(  GLenum shader_type, const char * shader_description, const char * shader_source );
                                       
   // lee la 'location' de un uniform, da una advertencia si no está activo
   // @param name (conat char *) - uniform name in the shaders sources
   //
   GLint leerLocation( const char * name );

   // crea, compila y usa el objeto programa
   void crearObjetoPrograma( );

   // lee las 'locations' de los parámetros uniforms y los inicializa 
   void inicializarUniforms();

   // imprime los nombres y tipos de los uniform del programa (para debug)
   void imprimeInfoUniforms();

   // usar (activar) el objeto programa para las siguientes operaciones de visualización
   void activar();

   // Fija el color actual (valor por defecto del aributo de color)
   // @param nuevo_color (glm::vec3) nuevo color para visualizaciones sin tabla de colores. 
   //
   void fijarColor( const glm::vec3 & nuevo_color );

   // fija el valor de 'usar_color_plano'  
   // @param nuevo_usar_color_plano (bool) - nuevo valor del booleano 
   //
   void fijarUsarColorPlano( const bool nuevo_usar_color_plano );

   // inserta una copia del color actual en el tope de la pila de colores
   void pushColor();

   // extrae un color de la pila de colores y lo fija como color actual.
   void popColor();

   // resets the modelview matrix (MM) stack and set modelview to identity
   void resetMM();

   // pushes a copy of the current modelview matrix on top of the modelview matrix stack
   void pushMM();

   // componese the current modelview matrix with a new matrix
   // @param mat (mat4) -- matrix to componse
   //
   void compMM( const glm::mat4 & mat );
   
   // removes the current matrix on top of the modelview matrix stack (cannot be empty)
   void popMM();

   // sets the projection matrix
   void fijarMatrizProyeccion( const glm::mat4 & new_projection_mat );

   // índice del atributo de posiciones (debe ser 0)
   static constexpr GLuint ind_atrib_posiciones = 0 ; 

   // índice del atributo 'color de vértice' 
   static constexpr GLuint ind_atrib_colores = 1 ;

   // número total de atributos que gestiona este cauce (0->positions, 1->colors)
   static constexpr GLuint num_atribs = 2 ;
   
   protected: // ---------------------------
   
   // nombres de objeto programa y objetos shaders
   GLuint id_prog        = 0 , // nombre o identificador del objeto programa
          id_frag_shader = 0 , // nombre o identificador del objeto shader (fragment shader)
          id_vert_shader = 0 ; // nombre o identificador del objeto shader (vertex shader)

   // variables estáticas con información del log errores
   static constexpr GLsizei  log_long_max = 1024*16 ;     //  longitud máxima en chars del buffer para log 
   static           GLchar   log_buffer[ log_long_max ] ; //  buffer para log 
   static           GLsizei  log_long ;                   // longitud actual del buffer

   // pila de colores 
   std::vector<glm::vec3> pila_colores ;  

   // variables con valores actuales de los uniforms y locations asociados

   glm::vec3 color                = { 0.0, 0.0, 0.0 }; // color actual
   GLint     loc_usar_color_plano = -1 ;               // location for the uniform 'use flat color'
   
   glm::mat4              mat_modelview      = glm::mat4(1.0);  // current modelview matrix (initially equal to the identity matrix)
   std::vector<glm::mat4> pila_mat_modelview ;                 // stack for saved modelview matrices
   GLint                  loc_mat_modelview  = -1 ;             // uniform location for the modelview matrix
   
   glm::mat4 mat_proyeccion     = glm::mat4(1.0);  // current projection matrix (initially equal to the identity matrix)
   GLint     loc_mat_proyeccion = -1 ;             // uniform location for projection matrix
   
   
};


// returns a string with the name of a type from its corresponding OpenGL symbolic constant 
const std::string  typeName( const GLenum type );

#endif
