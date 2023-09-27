// *********************************************************************
// **
// ** Gestión del cauce gráfico (clase 'Cauce') (implementación)
// **
// ** Copyright (C) 2017-2022 Carlos Ureña
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
#include "cauce.h" 

GLsizei Cauce::report_buffer_long = 0 ;
GLchar  Cauce::report_buffer[ Cauce::report_buffer_long_max ] ;

// *****************************************************************************
// Cauce programable (OpenGL 3.3)
// -----------------------------------------------------------------------------


Cauce::Cauce()
{
   crearObjetoPrograma();
   inicializarUniforms();
   imprimeInfoUniforms();  

   using namespace std ;
   cout << "Shaders compilados y objeto 'Cauce' creado con éxito." << endl ;
}
// ---------------------------------------------------------------------------

// compila y enlaza el objeto progama 
// (deja nombre en 'id_prog', debe ser 0 antes)

void Cauce::crearObjetoPrograma()
{
   using namespace std ;
   assert( id_prog == 0 );
   CError();

   // inicializar los nombres de los archivos fuente 
   const std::string 
      nombre_completo_frag = PathCarpetaMateriales() + "/src-shaders/cauce33-frag.glsl" ,
      nombre_completo_vert = PathCarpetaMateriales() + "/src-shaders/cauce33-vert.glsl" ;

   // crear el objeto programa y compilar y adjuntarle los shaders
   id_prog        = glCreateProgram(); assert( id_prog > 0 );
   id_frag_shader = compilarAdjuntarShader( GL_FRAGMENT_SHADER, nombre_completo_frag );
   id_vert_shader = compilarAdjuntarShader( GL_VERTEX_SHADER,   nombre_completo_vert );
   
	// enlazar programa y ver errores
	glLinkProgram( id_prog );
   GLint resultado ;
   glGetProgramiv( id_prog, GL_LINK_STATUS, &resultado );

   // si ha habido errores, abortar
   if ( resultado != GL_TRUE )
   {  
      glGetProgramInfoLog( id_prog, report_buffer_long_max, &report_buffer_long, report_buffer);
      cout << "Error al enlazar el objeto programa:" << endl
           << report_buffer << flush
           << "Programa abortado." << endl << std::flush ;
      exit(1);
   }
   CError();
}
// ---------------------------------------------------------------------------

// lee las 'locations' de todos los uniforms
// y les da un valor inicial por defecto.
void Cauce::inicializarUniforms()
{
   CError();
   glUseProgram( id_prog );
   CError();
   // obtener las 'locations' de los parámetros uniform

   loc_mat_modelado      = leerLocation( "u_mat_modelado" );
   loc_mat_modelado_nor  = leerLocation( "u_mat_modelado_nor" );
   loc_mat_vista         = leerLocation( "u_mat_vista" );
   loc_mat_proyeccion    = leerLocation( "u_mat_proyeccion" );
   loc_eval_mil          = leerLocation( "u_eval_mil" );
   loc_usar_normales_tri = leerLocation( "u_usar_normales_tri" );
   loc_eval_text         = leerLocation( "u_eval_text" );
   loc_tipo_gct          = leerLocation( "u_tipo_gct" );
   loc_coefs_s           = leerLocation( "u_coefs_s" );
   loc_coefs_t           = leerLocation( "u_coefs_t" );
   loc_mil_ka            = leerLocation( "u_mil_ka" );
   loc_mil_kd            = leerLocation( "u_mil_kd" );
   loc_mil_ks            = leerLocation( "u_mil_ks" );
   loc_mil_exp           = leerLocation( "u_mil_exp" );
   loc_num_luces         = leerLocation( "u_num_luces" );
   loc_pos_dir_luz_ec    = leerLocation( "u_pos_dir_luz_ec" );
   loc_color_luz         = leerLocation( "u_color_luz" );

   // dar valores iniciales por defecto a los parámetros uniform
 
  

   glUniformMatrix4fv( loc_mat_modelado,     1, GL_FALSE, value_ptr(mat_modelado) );
   glUniformMatrix4fv( loc_mat_modelado_nor, 1, GL_FALSE, value_ptr(mat_modelado_nor) );
   glUniformMatrix4fv( loc_mat_vista,        1, GL_FALSE, value_ptr(mat_vista) );
   glUniformMatrix4fv( loc_mat_proyeccion,   1, GL_FALSE, value_ptr(mat_proyeccion) );

   glUniform1ui( loc_eval_mil,          eval_mil );
   glUniform1ui( loc_usar_normales_tri, usar_normales_tri );
   glUniform1ui( loc_eval_text,         eval_text  );
   glUniform1i ( loc_tipo_gct,          tipo_gct );

   glUniform4fv( loc_coefs_s, 1, coefs_s );
   glUniform4fv( loc_coefs_t, 1, coefs_t );

   glUniform1f( loc_mil_ka,  0.2 );
   glUniform1f( loc_mil_kd,  0.8 );
   glUniform1f( loc_mil_ks,  0.0 );
   glUniform1f( loc_mil_exp, 0.0 );

   glUniform1i( loc_num_luces, 0 ); // por defecto: 0 fuentes de luz activas
   CError();
   
   glUseProgram( 0 );

   
   CError();
}
// ---------------------------------------------------------------------------


// imprime los nombres y tipos de los uniform del programa 
// (para debug)
void Cauce::imprimeInfoUniforms()
{
   using namespace std ;
   assert( 0 < id_prog );
   CError();

   GLint n_uniforms;
   glGetProgramiv( id_prog, GL_ACTIVE_UNIFORMS, &n_uniforms );

   cout << "Cuenta de parámetros uniform activos: " << n_uniforms << endl ;

   for ( int i = 0; i < n_uniforms; i++ )
   {
      GLenum tipo;       // tipo de la variable (float, vec3 or mat4, etc)  
      GLint  n_entradas; // si es array, número de entradas, en otro caso 1.
      glGetActiveUniform( id_prog, (GLuint)i, report_buffer_long_max, 
                          &report_buffer_long, &n_entradas, &tipo, report_buffer );

      cout << "     Uniform " << i << ": " << report_buffer << " (" << NombreTipoGL(tipo) << " x" << n_entradas << ")." << endl ;
      CError();
   }

   CError();
}

// ---------------------------------------------------------------------------

GLuint Cauce::compilarAdjuntarShader
(  
   GLenum              tipo_shader,         
   const std::string & nombre_archivo      
)
{  
   using namespace std ;
   assert( tipo_shader == GL_VERTEX_SHADER || 
           tipo_shader == GL_GEOMETRY_SHADER || 
           tipo_shader == GL_FRAGMENT_SHADER ) ;

   assert( id_prog > 0 );

   CError();

   const GLchar * fuente_shader   = leerArchivo( nombre_archivo );
   const GLuint   id_shader       = glCreateShader( tipo_shader );
   GLint          longitud_fuente = strlen( fuente_shader );

   glShaderSource( id_shader, 1, (const GLchar **) &fuente_shader, &longitud_fuente ) ;
   glCompileShader( id_shader ) ;

   glGetShaderInfoLog( id_shader, report_buffer_long_max, &report_buffer_long, report_buffer );
   if ( report_buffer_long > 0 )
   {
      cout << "Log de compilación de '" << QuitarPath( nombre_archivo ) << "': " << endl ;
      cout << report_buffer << endl ;
   }
   GLint compile_status ;
   glGetShaderiv( id_shader, GL_COMPILE_STATUS, &compile_status );
   if ( compile_status != GL_TRUE )
   {
      cout << "Errores al compilar. Aborto." << endl ;
      exit(1);
   }
   glAttachShader( id_prog, id_shader );
   CError();

   return id_shader ;
}
//----------------------------------------------------------------------
// devuelve la 'location' de un uniform.
// (si no se encuentra, aborta)

GLint Cauce::leerLocation( const char * name )
{
   using namespace std ;
   assert( name != nullptr );
   assert( id_prog > 0 );

   const GLint location = glGetUniformLocation( id_prog, name ); 
   CError();

   if ( location == -1 )
      cout << "Advertencia: la variable uniform '" << name << "' no está declarada o no se usa." << endl ;
      
   return location ;
}
//----------------------------------------------------------------------

void Cauce::activar()
{
   //log("activo cauce ",descripcion());
   CError();
   assert( 0 < id_prog );
   glUseProgram( id_prog );
   CError();
}

// -----------------------------------------------------------------------------
// devuelve el color actual

glm::vec4 Cauce::leerColorActual() const
{
   return glm::vec4( color.r, color.g, color.b, 1.0 );
}

//----------------------------------------------------------------------
// lee un archivo completo como texto  y devuelve una cadena terminada
// en cero con el contenido
// (el resultado está en el heap y debería borrarse con 'delete [] p')

char * Cauce::leerArchivo( const std::string & nombreArchivo )
{
	using namespace std ;

	ifstream file( nombreArchivo.c_str(), ios::in|ios::binary|ios::ate );

	if ( ! file.is_open())
	{  cout << "imposible abrir archivo para lectura (" << nombreArchivo << ") - termino" << endl << flush ;
		exit(0);
	}
	size_t	numBytes	= file.tellg();
	char *	bytes		= new char [numBytes+2];

	file.seekg (0, ios::beg);
	file.read (bytes, numBytes);
	file.close();

	bytes[numBytes]=0 ;
	bytes[numBytes+1]=0 ;

	return bytes ;
}
// //----------------------------------------------------------------------
// // crea, carga y compila un shader nuevo
// // si hay algún error, aborta
// // si todo va bien, devuelve el código de opengl del shader

// GLuint Cauce::compilarShader( const std::string & nombreArchivo, GLenum tipoShader )
// {
//    using namespace std ;
//    GLuint idShader ; // resultado: identificador de shader

//    CError() ;

//    // crear shader nuevo, obtener identificador (tipo GLuint)
//    idShader = glCreateShader( tipoShader );

//    // leer archivo fuente de shader en memoria, asociar fuente al shader, liberar memoria:
//    const GLchar * fuente = leerArchivo( nombreArchivo );
//    glShaderSource( idShader, 1, & fuente, nullptr );
//    delete [] fuente ;
//    fuente = nullptr ;

//    // compilar y comprobar errores
//    glCompileShader( idShader );
//    GLint resultado ;
//    glGetShaderiv( idShader, GL_COMPILE_STATUS, &resultado );

//    // si hay errores, abortar
//    if ( resultado != GL_TRUE )
//    {
//       const GLsizei maxt = 1024L*10L ;
//       GLsizei       tam ;
//       GLchar        buffer[maxt] ;

//       glGetShaderInfoLog( idShader, maxt, &tam, buffer);
//       cout << "error al compilar archivo '" << nombreArchivo << "'" << endl
//            << buffer << flush
//            << "programa abortado" << endl << std::flush ;
//       exit(1);
//    }
//    CError() ;
// 	return idShader ;
// }
// -----------------------------------------------------------------------------
// fijar el color actual (equiv glColor3f en el antiguo cauce fijo)

void Cauce::fijarColor( const float r, const float g, const float b )
{
   CError();
   color = { r,g,b } ; // registra color en el objeto cauce
   glVertexAttrib3f( ind_atrib_colores, r, g, b  ); // cambia valor atributo
   CError();
}
// -----------------------------------------------------------------------------
// inserta una copia del color actual en el tope de la pila de colores

void Cauce::pushColor()
{
   pila_colores.push_back( color );
}

// -----------------------------------------------------------------------------
// extrae un color de la pila de colores y lo fija como color actual.

void Cauce::popColor()
{
   using namespace glm ;
   assert( pila_colores.size() > 0 );
   const vec3 c = pila_colores[ pila_colores.size()-1] ;
   pila_colores.pop_back();
   fijarColor( c );
}

// -----------------------------------------------------------------------------
// fijar la matriz de vista y resetear las matrices de modelado y vista,
// (vacía la pila de modelado y de normales, igual que el cauce fijo)

void Cauce::fijarMatrizVista( const glm::mat4 & nue_mat_vista )
{
   using namespace glm ;
   assert( 0 < id_prog );

   mat_vista = nue_mat_vista ;
   glUseProgram( id_prog );
   glUniformMatrix4fv( loc_mat_vista, 1, GL_FALSE, value_ptr( mat_vista ) );
   
   pila_mat_modelado.clear();
   pila_mat_modelado_nor.clear();

   mat_modelado     = mat4( 1.0f ); //MAT_Ident();
   mat_modelado_nor = mat4( 1.0f ); //MAT_Ident();

   actualizarUniformsMatricesMN();

   CError();
}
// -----------------------------------------------------------------------------

void Cauce::fijarMatrizProyeccion( const glm::mat4 & nue_mat_proyeccion )
{
   assert( 0 < id_prog );
   mat_proyeccion = nue_mat_proyeccion ;

   // debug:
   // using namespace std ;
   // cout << "Cauce::fijarMatrizProyeccion: mat(3,2)      == " << mat_proyeccion(3,2) << endl ;
   // cout << "                              en offset +11 == " << ((float *)mat_proyeccion)[11] << endl ;
   // fin debug 
   
   glUseProgram( id_prog );
   glUniformMatrix4fv( loc_mat_proyeccion, 1, GL_FALSE, value_ptr( mat_proyeccion ) );
   CError();
}
//-----------------------------------------------------------------------------

void Cauce::fijarEvalText( const bool nue_eval_text, const int nue_text_id  )
{
   CError();
   eval_text = nue_eval_text ;

   if ( eval_text )
   {
      assert( -1 < nue_text_id );
      glActiveTexture( GL_TEXTURE0 ) ; // creo que necesario en el cauce prog., probar
      glBindTexture( GL_TEXTURE_2D, nue_text_id );
      glUniform1ui( loc_eval_text, true );
      CError();
   }
   else
   {
      glUniform1ui( loc_eval_text, false );
      CError();
   }
   CError();
}
//-----------------------------------------------------------------------------

void Cauce::fijarTipoGCT( const int nue_tipo_gct,
                           const float * coefs_s, const float * coefs_t )
{
   assert( 0 <= nue_tipo_gct && nue_tipo_gct <= 2 );

   tipo_gct = nue_tipo_gct ;

   if ( tipo_gct != 0 )
   {
      assert( coefs_s != nullptr );
      assert( coefs_t != nullptr );
   }

   //glUniform1i( loc_tipo_gct, tipo_gct  ? 1 : 0 );
   glUniform1i( loc_tipo_gct, tipo_gct );

   if ( tipo_gct == 1 || tipo_gct == 2 )
   {
      glUniform4fv( loc_coefs_s, 1, coefs_s );
      glUniform4fv( loc_coefs_t, 1, coefs_t );
   }
   CError();
}


// -----------------------------------------------------------------------------

void Cauce::fijarEvalMIL( const bool nue_eval_mil  )
{
   eval_mil = nue_eval_mil ; // registra valor en el objeto Cauce.
   glUseProgram( id_prog );  // activa el programa 
   glUniform1ui( loc_eval_mil, eval_mil   ); // cambia parámetro del shader
   CError();
}
// -----------------------------------------------------------------------------

void Cauce::fijarUsarNormalesTri ( const bool nue_usar_normales_tri )
{
   usar_normales_tri = nue_usar_normales_tri ;
   glUseProgram( id_prog );
   glUniform1ui( loc_usar_normales_tri, usar_normales_tri );
   CError();
}

// -----------------------------------------------------------------------------

void Cauce::fijarParamsMIL( const float k_amb, const float k_dif,
                            const float k_pse, const float exp_pse )  
{
   assert( -1 < loc_mil_ka );
   assert( -1 < loc_mil_kd );
   assert( -1 < loc_mil_ks );
   assert( -1 < loc_mil_exp );

   glUseProgram( id_prog );
   glUniform1f( loc_mil_ka,   k_amb );
   glUniform1f( loc_mil_kd,   k_dif );
   glUniform1f( loc_mil_ks,   k_pse );
   glUniform1f( loc_mil_exp,  exp_pse );

   CError();
}



void Cauce::fijarFuentesLuz( const std::vector<glm::vec3> & color,
                                        const std::vector<glm::vec4> & pos_dir_wc  )
{
   using namespace glm ;
   const unsigned nl = color.size();
   assert( 0 < nl && nl <= maxNumFuentesLuz() );
   assert( nl == pos_dir_wc.size() );

   assert( 0 < id_prog );
   glUseProgram( id_prog );

   std::vector<vec4> pos_dir_ec ;

   for( unsigned i = 0 ; i < nl ; i++ )
   {
      using namespace std ;
      // cout << endl << endl ;
      // cout << "Cauce::fijarFuentesLuz: long sq antes == " << pos_dir_wc[i].lengthSq()  << endl ;
      const vec4 l = mat_vista * pos_dir_wc[i ] ;
      //cout << "Cauce::fijarFuentesLuz: i == " << i << ", pos_dir_wc[" << i << "] == " << pos_dir_wc[i] <<  endl ;
      pos_dir_ec.push_back( l );
   }
   glUniform1i( loc_num_luces, nl );
   glUniform3fv( loc_color_luz, nl, (const float *)color.data() );
   glUniform4fv( loc_pos_dir_luz_ec, nl, (const float *)pos_dir_ec.data() );
}
// -----------------------------------------------------------------------------
// inserta copia de la matriz de modelado actual (en el tope de la pila)

void Cauce::pushMM()
{
   pila_mat_modelado.push_back( mat_modelado );
   pila_mat_modelado_nor.push_back( mat_modelado_nor );
}

// -----------------------------------------------------------------------------
// extrae tope de la pila y sustituye la matriz de modelado actual

void Cauce::popMM()
{
   CError();
   const unsigned n = pila_mat_modelado.size() ;
   assert( 0 < n );
   assert( n == pila_mat_modelado_nor.size() );

   mat_modelado     = pila_mat_modelado[n-1] ;
   mat_modelado_nor = pila_mat_modelado_nor[n-1] ;

   pila_mat_modelado.pop_back();
   pila_mat_modelado_nor.pop_back();


   actualizarUniformsMatricesMN();
   //log("sale");
}


// -----------------------------------------------------------------------------
// compone matriz de modelado actual con la matriz dada.

void Cauce::compMM( const glm::mat4 & mat_componer )
{
   using namespace glm ;
   CError();

   const mat4 mat_componer_nor = inverseTranspose( mat_componer ) ;

   mat_modelado     = mat_modelado     * mat_componer ;
   mat_modelado_nor = mat_modelado_nor * mat_componer_nor ;

   actualizarUniformsMatricesMN();
   CError();
}
// -----------------------------------------------------------------------------

void Cauce::actualizarUniformsMatricesMN()
{
   //log("entra");
   assert( 0 < id_prog );
   assert( -1 < loc_mat_modelado );
   assert( -1 < loc_mat_modelado_nor );

   CError();
   glUseProgram( id_prog );
   glUniformMatrix4fv( loc_mat_modelado,     1, GL_FALSE, value_ptr( mat_modelado ) );
   glUniformMatrix4fv( loc_mat_modelado_nor, 1, GL_FALSE, value_ptr( mat_modelado_nor ));
   CError();
   //log("sale");
}
// -----------------------------------------------------------------------------
// lee el nombre o descripción del cauce

std::string Cauce::descripcion()
{
   return "programable (OpenGL 'moderno')" ;
}



// ----------------------------------------------------------------------------
// devuelve el nombre de un tipo de OpenGL a partir de la constante simbólica

const std::string  NombreTipoGL( const GLenum tipo )
{
   std::string p ;

   switch( tipo )
   {
      case GL_FLOAT       : p = "float" ; break ;
      case GL_FLOAT_VEC2  : p = "vec2" ; break ;
      case GL_FLOAT_VEC3  : p = "vec3" ; break ;
      case GL_FLOAT_VEC4  : p = "vec4" ; break ;
      case GL_INT	        : p = "int" ; break ;  
      case GL_INT_VEC2	  : p = "ivec2" ; break ;
      case GL_INT_VEC3	  : p = "ivec3" ; break ;
      case GL_INT_VEC4	  : p = "ivec4" ; break ;
      case GL_UNSIGNED_INT	      : p = "unsigned int" ; break ;
      case GL_UNSIGNED_INT_VEC2	: p = "uvec2" ; break ;
      case GL_UNSIGNED_INT_VEC3	: p = "uvec3" ; break ;
      case GL_UNSIGNED_INT_VEC4	: p = "uvec4" ; break ;
      case GL_BOOL	   : p = "bool" ; break ;
      case GL_BOOL_VEC2	: p = "bvec2" ; break ;
      case GL_BOOL_VEC3	: p = "bvec3" ; break ;
      case GL_BOOL_VEC4	: p = "bvec4" ; break ;
      case GL_FLOAT_MAT2	: p = "mat2" ; break ;
      case GL_FLOAT_MAT3	: p = "mat3" ; break ;
      case GL_FLOAT_MAT4	: p = "mat4" ; break ;
      case GL_FLOAT_MAT2x3	: p = "mat2x3" ; break ;
      case GL_FLOAT_MAT2x4	: p = "mat2x4" ; break ;
      case GL_FLOAT_MAT3x2	: p = "mat3x2" ; break ;
      case GL_FLOAT_MAT3x4	: p = "mat3x4" ; break ;
      case GL_FLOAT_MAT4x2	: p = "mat4x2" ; break ;
      case GL_FLOAT_MAT4x3	: p = "mat4x3" ; break ;
      case GL_SAMPLER_1D	: p = "sampler1D" ; break ;
      case GL_SAMPLER_2D	: p = "sampler2D" ; break ;
      case GL_SAMPLER_3D	: p = "sampler3D" ; break ;
      case GL_SAMPLER_CUBE	: p = "samplerCube" ; break ;
      case GL_SAMPLER_1D_SHADOW	: p = "sampler1DShadow" ; break ;
      case GL_SAMPLER_2D_SHADOW	: p = "sampler2DShadow" ; break ;
      case GL_SAMPLER_1D_ARRAY	: p = "sampler1DArray" ; break ;
      case GL_SAMPLER_2D_ARRAY	: p = "sampler2DArray" ; break ;
      case GL_SAMPLER_1D_ARRAY_SHADOW	: p = "sampler1DArrayShadow" ; break ;
      case GL_SAMPLER_2D_ARRAY_SHADOW	: p = "sampler2DArrayShadow" ; break ;
      case GL_SAMPLER_2D_MULTISAMPLE	: p = "sampler2DMS" ; break ;
      case GL_SAMPLER_2D_MULTISAMPLE_ARRAY : p = "sampler2DMSArray" ; break ;
      case GL_SAMPLER_CUBE_SHADOW	  : p = "samplerCubeShadow" ; break ;
      case GL_SAMPLER_BUFFER	        : p = "samplerBuffer" ; break ;
      case GL_SAMPLER_2D_RECT	        : p = "sampler2DRect" ; break ;
      case GL_SAMPLER_2D_RECT_SHADOW  : p = "sampler2DRectShadow" ; break ;
      case GL_INT_SAMPLER_1D	        : p = "isampler1D" ; break ;
      case GL_INT_SAMPLER_2D	        : p = "isampler2D" ; break ;
      case GL_INT_SAMPLER_3D	        : p = "isampler3D" ; break ;
      case GL_INT_SAMPLER_CUBE	     : p = "isamplerCube" ; break ;
      case GL_INT_SAMPLER_1D_ARRAY	  : p = "isampler1DArray" ; break ;
      case GL_INT_SAMPLER_2D_ARRAY	  : p = "isampler2DArray" ; break ;
      case GL_INT_SAMPLER_2D_MULTISAMPLE	     : p = "isampler2DMS" ; break ;
      case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : p = "isampler2DMSArray" ; break ;
      case GL_INT_SAMPLER_BUFFER	         : p = "isamplerBuffer" ; break ;
      case GL_INT_SAMPLER_2D_RECT	      : p = "isampler2DRect" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_1D	   : p = "usampler1D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D	   : p = "usampler2D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_3D	   : p = "usampler3D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_CUBE	: p = "usamplerCube" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY	: p = "usampler2DArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY	: p = "usampler2DArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE	      : p = "usampler2DMS" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY	: p = "usampler2DMSArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_BUFFER	   : p = "usamplerBuffer" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_RECT	: p = "usampler2DRect" ; break ;
      default : assert( false ); break ;
   
   }
   return p ;
}

