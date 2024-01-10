// OpenGL+GLFW+GLEW+GLM includes
// uses OpenGL 3.3 + GLSL 3.3 + GLFW 3 + GLM
 
#ifndef GL_INCLUDES_H
#define GL_INCLUDES_H

// includes de la librería std de C++
#include <iostream>
#include <iomanip>

// includes de OpenGL, GLFW and GLEW
#ifdef __linux__
// -----------------------------------------------
// Includes y definiciones específicos en Linux
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#ifdef __APPLE__
//------------------------------------------------
// Includes y definiciones específicos en macOS
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#else
#ifdef _WIN32
//------------------------------------------------
// Includes y definiciones específicos en Windows
// tener en cuenta esto:
//  https://www.glfw.org/docs/3.0/build.html#build_include
//  https://www.glfw.org/docs/3.0.3/build.html
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// ------------------------------------------------
#else
// Emitir error por sistema operativo no soportado
#error "No puedo determinar el sistema operativo, o no esta soportado"
#endif
#endif
#endif


// includes de GLM
#include <glm/glm.hpp>               // incluye cosas básicas de GLM (vectores y matrices)
#include <glm/gtc/type_ptr.hpp>      // conversion de vectores y matrices hacia/desde 'float *' con 'value_ptr' (https://glm.g-truc.net/0.9.9/api/a00305.html)
#include <glm/gtc/matrix_access.hpp> // acceso a filas y columnas de una matriz, con glm::row( mat4 )
#include <glm/gtx/string_cast.hpp>   // función 'to_string'
#include <glm/gtx/transform.hpp>     // funciones 'scale', 'rotate', 'translate' sin especificar una matriz original (https://glm.g-truc.net/0.9.9/api/a00362.html)


/// aux function to print vectors and matrices

template<class T>
inline std::ostream & operator<< (std::ostream &os, const glm::tvec3<T> &v ) 
{
    return os << "( " << v[0] << ", " << v[1] << ", " << v[2] << " )" ; 
}

template<class T>
inline std::ostream & operator<< (std::ostream &os, const glm::tvec2<T> &v ) 
{
    return os << "( " << v[0] << ", " << v[1] << " )" ;    
}

template<class T>
inline std::ostream & operator<< (std::ostream &os, const glm::tmat4x4<T> &m ) 
{
    using namespace std ;

    const char * izq = "/||\\", * der = "\\||/" ;
    ios estado_anterior( nullptr );

    estado_anterior.copyfmt( os );
    os << endl << fixed << setprecision(7) << showpos ;

    for( unsigned i = 0 ; i < 4 ; i++ )
    {  
        os << izq[i] << " " ;
        for( unsigned j = 0 ; j < 4 ; j++ )
        {   os << setw(15) << m[i][j] ;
            if ( j < 3 ) os << ", " ;
        }
        os << " " << der[i] << endl ;
    }

    os.copyfmt( estado_anterior );
    return os ;
}

// devuelve el nombre de un tipo OpenGL, a partir de 
// la correspondiente constante simbólica
//
inline const std::string NombreTipoGL( const GLenum tipo ) 
{
   std::string name ;

   switch( tipo )
   {
      case GL_FLOAT       : name = "float" ; break ;
      case GL_FLOAT_VEC2  : name = "vec2" ; break ;
      case GL_FLOAT_VEC3  : name = "vec3" ; break ;
      case GL_FLOAT_VEC4  : name = "vec4" ; break ;
      case GL_INT	      : name = "int" ; break ;  
      case GL_INT_VEC2	  : name = "ivec2" ; break ;
      case GL_INT_VEC3	  : name = "ivec3" ; break ;
      case GL_INT_VEC4	  : name = "ivec4" ; break ;
      case GL_UNSIGNED_INT	    : name = "unsigned int" ; break ;
      case GL_UNSIGNED_INT_VEC2	: name = "uvec2" ; break ;
      case GL_UNSIGNED_INT_VEC3	: name = "uvec3" ; break ;
      case GL_UNSIGNED_INT_VEC4	: name = "uvec4" ; break ;
      case GL_BOOL	        : name = "bool" ; break ;
      case GL_BOOL_VEC2	    : name = "bvec2" ; break ;
      case GL_BOOL_VEC3	    : name = "bvec3" ; break ;
      case GL_BOOL_VEC4	    : name = "bvec4" ; break ;
      case GL_FLOAT_MAT2	: name = "mat2" ; break ;
      case GL_FLOAT_MAT3	: name = "mat3" ; break ;
      case GL_FLOAT_MAT4	: name = "mat4" ; break ;
      case GL_FLOAT_MAT2x3	: name = "mat2x3" ; break ;
      case GL_FLOAT_MAT2x4	: name = "mat2x4" ; break ;
      case GL_FLOAT_MAT3x2	: name = "mat3x2" ; break ;
      case GL_FLOAT_MAT3x4	: name = "mat3x4" ; break ;
      case GL_FLOAT_MAT4x2	: name = "mat4x2" ; break ;
      case GL_FLOAT_MAT4x3	: name = "mat4x3" ; break ;
      case GL_SAMPLER_1D	: name = "sampler1D" ; break ;
      case GL_SAMPLER_2D	: name = "sampler2D" ; break ;
      case GL_SAMPLER_3D	    : name = "sampler3D" ; break ;
      case GL_SAMPLER_CUBE	    : name = "samplerCube" ; break ;
      case GL_SAMPLER_1D_SHADOW	: name = "sampler1DShadow" ; break ;
      case GL_SAMPLER_2D_SHADOW	: name = "sampler2DShadow" ; break ;
      case GL_SAMPLER_1D_ARRAY	: name = "sampler1DArray" ; break ;
      case GL_SAMPLER_2D_ARRAY	: name = "sampler2DArray" ; break ;
      case GL_SAMPLER_1D_ARRAY_SHADOW	: name = "sampler1DArrayShadow" ; break ;
      case GL_SAMPLER_2D_ARRAY_SHADOW	: name = "sampler2DArrayShadow" ; break ;
      case GL_SAMPLER_2D_MULTISAMPLE	: name = "sampler2DMS" ; break ;
      case GL_SAMPLER_2D_MULTISAMPLE_ARRAY : name = "sampler2DMSArray" ; break ;
      case GL_SAMPLER_CUBE_SHADOW	    : name = "samplerCubeShadow" ; break ;
      case GL_SAMPLER_BUFFER	        : name = "samplerBuffer" ; break ;
      case GL_SAMPLER_2D_RECT	        : name = "sampler2DRect" ; break ;
      case GL_SAMPLER_2D_RECT_SHADOW    : name = "sampler2DRectShadow" ; break ;
      case GL_INT_SAMPLER_1D	        : name = "isampler1D" ; break ;
      case GL_INT_SAMPLER_2D	        : name = "isampler2D" ; break ;
      case GL_INT_SAMPLER_3D	        : name = "isampler3D" ; break ;
      case GL_INT_SAMPLER_CUBE	      : name = "isamplerCube" ; break ;
      case GL_INT_SAMPLER_1D_ARRAY	  : name = "isampler1DArray" ; break ;
      case GL_INT_SAMPLER_2D_ARRAY	  : name = "isampler2DArray" ; break ;
      case GL_INT_SAMPLER_2D_MULTISAMPLE	   : name = "isampler2DMS" ; break ;
      case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : name = "isampler2DMSArray" ; break ;
      case GL_INT_SAMPLER_BUFFER	    : name = "isamplerBuffer" ; break ;
      case GL_INT_SAMPLER_2D_RECT	    : name = "isampler2DRect" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_1D	: name = "usampler1D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D	: name = "usampler2D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_3D	: name = "usampler3D" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_CUBE	: name = "usamplerCube" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY	: name = "usampler2DArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY	: name = "usampler2DArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE	      : name = "usampler2DMS" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY	: name = "usampler2DMSArray" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_BUFFER	   : name = "usamplerBuffer" ; break ;
      case GL_UNSIGNED_INT_SAMPLER_2D_RECT	: name = "usampler2DRect" ; break ;
      default : assert( false ); break ;
   
   }
   return name ;
}


#endif // GL_INCLUDES_H
