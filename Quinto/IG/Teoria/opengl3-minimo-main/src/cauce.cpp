// Ejemplo mínimo de código OpenGL, usa OpenGL 3.3 + GLSL 3.3

#include <iostream>
#include <iomanip>

#include "cauce.h"

// ---------------------------------------------------------------------------------------------

GLchar   Cauce::log_buffer[ Cauce::log_long_max ] ; //  buffer para log 
GLsizei  Cauce::log_long ;                           // longitud actual del buffer (en chars)

// ---------------------------------------------------------------------------------------------
// Basic pipeline shaders sources

const char * const fuente_vertex_shader = R"glsl(
   #version 330 core

   // Parámetros uniform (variables de entrada iguales para todos los vértices en cada primitiva)

   uniform mat4 u_mat_modelview;  // variable uniform: matriz de transformación de posiciones
   uniform mat4 u_mat_proyeccion; // variable uniform: matriz de proyección
   uniform bool u_usar_color_plano; // 1 --> usar color plano, 0 -> usar color interpolado

   // Atributos de vértice (variables de entrada distintas para cada vértice)
   // (las posiciones de posición siempre deben estar en la 'location' 0)

   layout( location = 0 ) in vec3 atrib_posicion ; // atributo 0: posición del vértice
   layout( location = 1 ) in vec3 atrib_color ;    // atributo 1: color RGB del vértice

   // output variables, going to the geometry shader

   out      vec3 var_color_interpolado ; // color RGB del vértice (el mismo que proporciona la aplic.)
   flat out vec3 var_color_plano  ; // color RGB del 'provoking vertex'

   // función principal que se ejecuta una vez por vértice
   void main()
   {
      // copiamos color recibido en el color de salida, tal cual
      var_color_interpolado = atrib_color ;
      var_color_plano       = atrib_color ;

      // calcular las posiciones del vértice en posiciones de mundo y escribimos 'gl_Position'
      // (se calcula multiplicando las cordenadas por la matrices 'modelview' y 'projection')
      gl_Position = u_mat_proyeccion * u_mat_modelview * vec4( atrib_posicion, 1);
   }
)glsl";

// ------------------------------------------------------------------------------------------------------

const char * const fuente_fragment_shader = R"glsl(
    #version 330 core

   uniform bool u_usar_color_plano;     // false -> usar color interpolado, true --> usar color plano, 
   in      vec3 var_color_interpolado ; // color interpolado en el pixel.
   flat in vec3 var_color_plano ;       // color (plano) producido por el 'provoking vertex'
   layout( location = 0 ) out vec4 out_color_fragmento ; // variable de salida (color del pixel)
   
   void main()
   {
      if ( u_usar_color_plano )
         out_color_fragmento = vec4( var_color_plano, 1.0 ) ; // el color del pixel es el color interpolado
      else 
         out_color_fragmento = vec4( var_color_interpolado, 1.0 ); // el color plano (de un único vértice)
   }
)glsl";

// ---------------------------------------------------------------------------------------------

Cauce::Cauce()
{
   using namespace std ;

   crearObjetoPrograma();
   inicializarUniforms();
   imprimeInfoUniforms();

   cout << "Cauce creado sin errores." << endl ;
}

// ---------------------------------------------------------------------------------------------

void Cauce::inicializarUniforms()
{
   loc_mat_modelview  = leerLocation( "u_mat_modelview" );      
   loc_mat_proyeccion = leerLocation( "u_mat_proyeccion" );     
   loc_usar_color_plano = leerLocation( "u_usar_color_plano" );     
}
// ---------------------------------------------------------------------------------------------

void Cauce::imprimeInfoUniforms()
{
   using namespace std ;
   assert( 0 < id_prog );
   assert( glGetError() == GL_NO_ERROR );

   GLint n_uniforms;
   glGetProgramiv( id_prog, GL_ACTIVE_UNIFORMS, &n_uniforms );
   cout << "Cuenta de parámetros uniform activos: " << n_uniforms << endl ;

   for ( int i = 0; i < n_uniforms; i++ )
   {
      GLenum tipo;       // tipo de la variable (float, vec3 or mat4, etc)  
      GLint  n_entradas; // si es array, número de entradas, en otro caso 1.
      glGetActiveUniform( id_prog, (GLuint)i, log_long_max, &log_long, &n_entradas, &tipo, log_buffer);
      cout << "   Uniform " << i << ": " << log_buffer << " (" << NombreTipoGL(tipo) << " x" << n_entradas << ")." << endl ;
   }
   assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

GLuint Cauce::compilarAdjuntarShader
(  
   GLenum       shader_type,         // uno de GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
   const char * shader_description,  // texto descriptivo por si hay error ('vertex shader', 'fragment shader', etc...)
   const char * shader_source        // código fuente del shader
)
{  using namespace std ;
   assert( shader_type == GL_VERTEX_SHADER || 
           shader_type == GL_GEOMETRY_SHADER || 
           shader_type == GL_FRAGMENT_SHADER ) ;

   assert( shader_source != nullptr );
   assert( id_prog > 0 );

   assert( glGetError() == GL_NO_ERROR );

   const GLuint shader_id     = glCreateShader( shader_type );
   GLint        source_length = strlen( shader_source );

   glShaderSource( shader_id, 1, (const GLchar **) &shader_source, &source_length ) ;
   glCompileShader( shader_id ) ;

   glGetShaderInfoLog( shader_id, log_long_max, &log_long, log_buffer );
   if ( log_long > 0 )
   {
      cout << shader_description << " compilation log: " << endl ;
      cout << log_buffer << endl ;
   }

   GLint compile_status ;
   glGetShaderiv( shader_id, GL_COMPILE_STATUS, &compile_status );

   if ( compile_status != GL_TRUE )
   {
      cout << "Compilation errors, aborting." << endl ;
      exit(1);
   }

   glAttachShader( id_prog, shader_id );
   assert( glGetError() == GL_NO_ERROR );
   return shader_id ;
}
// ---------------------------------------------------------------------------------------------
// Gets uniform location + warns if it is not active.

GLint Cauce::leerLocation( const char * name )
{
   using namespace std ;
   assert( name != nullptr );
   assert( id_prog > 0 );

   const GLint location = glGetUniformLocation( id_prog, name ); 

   if ( location == -1 )
      cout << "Warning: uniform '" << name << "' is not declared or not used." << endl ;
   
   return location ;
}
// ---------------------------------------------------------------------------------------------

void Cauce::crearObjetoPrograma( )
{
   // check preconditions
   using namespace std ;
   assert( fuente_vertex_shader != nullptr );
   assert( fuente_fragment_shader != nullptr );
   assert( id_prog == 0 );
   assert( glGetError() == GL_NO_ERROR );
   
   // crear el programa, compilar los shaders
   id_prog = glCreateProgram() ;  assert( id_prog > 0 );
   id_frag_shader = compilarAdjuntarShader( GL_VERTEX_SHADER,   "vertex shader",   fuente_vertex_shader );
   id_vert_shader = compilarAdjuntarShader( GL_FRAGMENT_SHADER, "fragment shader", fuente_fragment_shader );
   

   // enlazar el programa y ver si ha habido errores
   GLint estado_prog ;
   glLinkProgram( id_prog ) ;   
   assert( glGetError() == GL_NO_ERROR );

   glGetProgramInfoLog( id_prog, log_long_max, &log_long, log_buffer );
   if ( log_long > 0 )
   {
      cout << "Log de enlazado del objeto programa:" << endl ;
      cout << log_buffer << endl ;
   }
   
   glGetProgramiv( id_prog, GL_LINK_STATUS, &estado_prog );
   if ( estado_prog != GL_TRUE )
   {  
      cout << "Errores al enlazar el objeto programa. Aborto." << endl ;
      exit(1);
   }
   
   // activar (usar) el programa
   glUseProgram( id_prog );
   assert( glGetError() == GL_NO_ERROR );
   cout << "El objeto programa se ha creado sin problemas." << endl ; 
}

// ---------------------------------------------------------------------------------------------
// use (activate) this program object for following draw operations

   
void Cauce::activar()
{
   assert( id_prog > 0 );
   assert( glGetError() == GL_NO_ERROR );
   glUseProgram( id_prog );
   assert( glGetError() == GL_NO_ERROR );
}

// ---------------------------------------------------------------------------------------------

void Cauce::fijarColor( const glm::vec3 & nuevo_color )
{
   color = nuevo_color ;
   glVertexAttrib3f(	ind_atrib_colores, color.r, color.g, color.b );
}
// -----------------------------------------------------------------------------

void Cauce::pushColor()
{
   pila_colores.push_back( color );
}
// -----------------------------------------------------------------------------

void Cauce::popColor()
{
   using namespace glm ;
   assert( pila_colores.size() > 0 );
   const vec3 c = pila_colores[ pila_colores.size()-1] ;
   pila_colores.pop_back();
   fijarColor( c );
}

// ---------------------------------------------------------------------------------------------

void Cauce::fijarUsarColorPlano( const bool nuevo_usar_color_plano )
{
   assert( loc_usar_color_plano != -1 ); 
   assert( glGetError() == GL_NO_ERROR );
   glUniform1i( loc_usar_color_plano, nuevo_usar_color_plano );
   assert( glGetError() == GL_NO_ERROR );
}
// ---------------------------------------------------------------------------------------------

void Cauce::fijarMatrizProyeccion( const glm::mat4 & new_projection_mat )
{
   assert( loc_mat_proyeccion != -1 ); 
   assert( glGetError() == GL_NO_ERROR );
   mat_proyeccion = new_projection_mat ;
   glUniformMatrix4fv( loc_mat_proyeccion, 1, GL_FALSE, glm::value_ptr(mat_proyeccion) );
   assert( glGetError() == GL_NO_ERROR );
}
// ---------------------------------------------------------------------------------------------

void Cauce::resetMM()
{
   assert( loc_mat_modelview != -1 );  
   assert( glGetError() == GL_NO_ERROR );
   mat_modelview = glm::mat4( 1.0f );
   pila_mat_modelview.clear();
   glUniformMatrix4fv( loc_mat_modelview, 1, GL_FALSE, glm::value_ptr(mat_modelview) );
   assert( glGetError() == GL_NO_ERROR );
}
// ---------------------------------------------------------------------------------------------

void Cauce::pushMM()
{
   pila_mat_modelview.push_back( mat_modelview );
}
// ---------------------------------------------------------------------------------------------

void Cauce::compMM( const glm::mat4 & mat )
{
   assert( loc_mat_modelview >= 0 );
   mat_modelview = mat_modelview * mat ;
   glUniformMatrix4fv( loc_mat_modelview, 1, GL_FALSE, glm::value_ptr(mat_modelview) );
}
// ---------------------------------------------------------------------------------------------

void Cauce::popMM()
{
   assert( loc_mat_modelview >= 0 );
   assert( pila_mat_modelview.size() > 0 );
   mat_modelview = pila_mat_modelview[ pila_mat_modelview.size()-1 ] ;
   pila_mat_modelview.pop_back();
   glUniformMatrix4fv( loc_mat_modelview, 1, GL_FALSE, glm::value_ptr(mat_modelview) );
}
// --------------------------------------------------------------------------------------------
