#version 330 core



// buen ejemplo aquí:
// http://joshbeam.com/articles/getting_started_with_glsl/
//
// para ver como hacer bind de una (o varias) texturas:
// https://www.opengl.org/wiki/Sampler_(GLSL)#Language_Definition


// Número máximo de fuentes de luz que el programa puede soportar
const int max_num_luces = 8 ;

// --------------------------------------------------------------------
// Parámetros de entrada uniform (constantes en cada primitiva)
// (iguales en fragment y vertex shader)

// 1. tipo de normales para iluminación
uniform bool  u_usar_normales_tri ; // true --> normal triángulo, false --> normal interpolada de los vértices

// 2. matrices de transformación y proyección
uniform mat4  u_mat_modelado ;    // matriz de modelado actual
uniform mat4  u_mat_modelado_nor; // matriz de modelado para normales (traspuesta inversa de la anterior)
uniform mat4  u_mat_vista ;       // matriz de vista (mundo --> camara)
uniform mat4  u_mat_proyeccion ;  // matriz de proyeccion

// 3. parámetros relativos a texturas
uniform bool  u_eval_text ;       // false --> no evaluar texturas, true -> evaluar textura en FS, sustituye a (v_color)
uniform int   u_tipo_gct ;        // tipo gen.cc.tt. (0=desact, 1=objeto, 2=camara)
uniform vec4  u_coefs_s ;         // coefficientes para G.CC.TT. (coordenada 's')
uniform vec4  u_coefs_t ;         // coefficientes para G.CC.TT. (coordenada 't')

// 4. parámetros relativos evaluación de iluminación
uniform bool  u_eval_mil ;        // evaluar el MIL sí (true) o no (false) --> si es que no, usar color plano actual
uniform float u_mil_ka ;          // color de la componente ambiental del MIL (Ka)
uniform float u_mil_kd ;          // color de la componente difusa del MIL (Kd)
uniform float u_mil_ks ;          // color de la componente pseudo-especular del MIL (Ks)
uniform float u_mil_exp ;         // exponente de la componente pseudo-especular del MIL (e)

// 5. parámetros de las fuentes de luces actuales
uniform int   u_num_luces ;                     // número de luces activas, si u_eval_mil == true
uniform vec4  u_pos_dir_luz_ec[max_num_luces] ; // posición/dirección de cada luz
uniform vec3  u_color_luz[max_num_luces] ;      // color o intensidad de cada fuente de luz

// 6. 'sampler' de textura
uniform sampler2D u_tex ;         // al ser el primer 'sampler', está ligado a la unidad 0 de u_texturas


// Valores de entrada (atributos de vértices, valores distintos para cada vértice)
// (los enteros que definen las 'locations' deben ser coherentes con el código de la app)

layout( location = 0 ) in vec3 in_posicion_occ ;   // posición del vértice en coordenadas de objeto
layout( location = 1 ) in vec3 in_color ;          // color del vértice
layout( location = 2 ) in vec3 in_normal_occ  ;    // normal del vértice 
layout( location = 3 ) in vec2 in_coords_textura ; // coordenadas de textura del vértice 

// Valores calculados como salida ('out' aquí, 'in' en el fragment shader, distintos de cada vértice)

out vec4 v_posic_ecc ;   // posicion del punto (en coords de camara)
out vec4 v_color ;       // color del vértice (interpolado a los pixels)
out vec3 v_normal_ecc;   // normal  (en coords. de cámara)
out vec2 v_coord_text;   // coordenadas de textura
out vec3 v_vec_obs_ecc ; // vector hacia el observador (en coords de cámara)

// ------------------------------------------------------------------------------
// calculo de los parámetros de salida (io_... y gl_Position)

vec2 CoordsTextura() // calcula las coordenadas de textura
{
   if ( ! u_eval_text )            // si no se están evaluando las coordenadas de textura
      return vec2( 0.0, 0.0 );     //     devuelve las coordenadas (0.0,0.0)
   if ( u_tipo_gct == 0 )          // texturas activadas, generacion desactivada
      return in_coords_textura.st; //     devuelve las coords. de glTexCoords o tabla

   vec4 pos_ver ;
   if ( u_tipo_gct == 1 )         // generacion en coordenadas de objeto
      pos_ver = vec4( in_posicion_occ, 1.0 ) ;        //    usar las coords originales (objeto)
   else                         // generacion en coords de cámara
      pos_ver = v_posic_ecc ;     //    usar las coordenadas de cámara

   return vec2( dot(pos_ver,u_coefs_s), dot(pos_ver,u_coefs_t) );
}

// ------------------------------------------------------------------------------
// devuelve el vector al obervador, a partir de pos. ECC, y en función de 
// si la matriz de proyec. es ortogonal (a==0), o es perspectiva (a==-1)

vec3 VectorObservadorVS( vec4 pos_ecc )
{
   float pm23 = u_mat_proyeccion[2][3],   // -1 si es perspectiva, 0 si es ortográfica.
         pm33 = u_mat_proyeccion[3][3];   // 0 si es perspectiva,  1 si es ortográfica.

   // código "largo" (para explicar lo que se hace)
   //
   // if ( pm23 == 0 &&  pm33 == 1.0 )    // si proyección es ortográfica
   //    return vec3( 0.0, 0.0, 1.0 );  //    devolver +Z
   // else                              // si es perspectiva
   //    return (-pos_ecc).xyz ;        //    devolver vector hacia el foco de la cámara (origen en ECC)

   // código "corto" (eficiente), equivalente
   return pm23*(pos_ecc.xyz) + vec3(0.0, 0.0, pm33 );
}
// ------------------------------------------------------------------------------

void main()
{
   vec4 posic_wcc  = u_mat_modelado * vec4( in_posicion_occ, 1.0 ) ; // posición del vértice en coords. de mundo
   vec3 normal_wcc = (u_mat_modelado_nor * vec4(in_normal_occ,0)).xyz ;

   // calcular las variables de salida
   v_posic_ecc    = u_mat_vista*posic_wcc ;
   v_normal_ecc   = (u_mat_vista*vec4(normal_wcc,0.0)).xyz ;
   v_vec_obs_ecc  = VectorObservadorVS( v_posic_ecc );  // ver la función arriba
   v_color        = vec4( in_color, 1 ) ;  // color fijado con in_color .....
   v_coord_text   = CoordsTextura();
   
   vec4 pos = u_mat_proyeccion * v_posic_ecc ; 
   gl_Position   = pos ; 
}
