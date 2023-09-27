// *********************************************************************
// **
// ** Lector de archivos PLY (vértices y caras únicamente)
// ** Implementación
// **
// ** Carlos Ureña - 2012- 2019
// **
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <cassert>


#include "ig-aux.h" 
#include "lector-ply.h"

// modelos ply en:
   // http://graphics.im.ntu.edu.tw/~robin/courses/cg03/model/
   // http://people.sc.fsu.edu/~jburkardt/data/ply/ply.html
   // univ stanford ?

using namespace std ;

//**********************************************************************
// constantes y funciones auxiliares (privadas)

static constexpr streamsize tam_buffer = streamsize(10L)*streamsize(1024L) ;

// clase que contiene el estado del proceso de parsing de un archivo, y
// proporciona diversos métodos para hacer dicho parsing

class LectorPLY
{
   public:

   ifstream       src ;                        // stream de entrada
   char           buffer[ (unsigned long)tam_buffer ]; // buffer para leer hasta fin de línea
   unsigned long  num_linea_actual = 0 ;       // número de linea que está siendo procesada
   std::string    nom_archivo      = "none" ;  // nombre del archivo que está siendo procesado
   unsigned long  num_vertices     = 0;        // número de vértices según cabecera del ply
   unsigned long  num_caras        = 0;        // número de caras según cabecera del ply

   LectorPLY() {}

   void abrirArchivo  ( const std::string & p_nombre_archivo ) ;
   void leerCabecera  ( const bool lee_num_caras ) ;
   void leerVertices  ( std::vector<glm::vec3> & vertices  ) ;
   void leerCaras     ( std::vector<glm::uvec3> & caras   ) ;
   void leerRestoLinea() ;
   void error         ( const char *msg_error ) ;
} ;

//**********************************************************************
// funcion principal de lectura

void LeerPLY
(
   const std::string &       nombre_archivo_pse, // entrada: nombre de archivo
   std::vector<glm::vec3> &  vertices,           // salida:  vector de coords. de vert.
   std::vector<glm::uvec3> & caras               // salida:  vector de triángulos (índices)
)
{
   using namespace std ;
   LectorPLY lector ;

   lector.abrirArchivo( nombre_archivo_pse ) ;
   lector.leerCabecera( true ) ;
   lector.leerVertices( vertices ) ;
   lector.leerCaras   ( caras ) ;

   //cout << "archivo ply '" << lector.nom_archivo << "' leido: núm. vértices == " << vertices.size() << ", núm caras == " << caras.size() << endl << flush ;
}

//**********************************************************************

void LeerVerticesPLY
(
   const std::string &  nombre_archivo_pse,
   vector<glm::vec3> &    vertices
)
{
   using namespace std ;
   LectorPLY lector  ;

   lector.abrirArchivo( nombre_archivo_pse ) ;
   lector.leerCabecera( false ) ;
   lector.leerVertices( vertices ) ;

   //cout << "archivo ply '" << lector.nom_archivo << "' leido (únicamente vértices) : núm. vértices == " << vertices.size() << endl << flush ;
}

//**********************************************************************

void LectorPLY::leerRestoLinea()
{
   src.getline( buffer, tam_buffer );
   num_linea_actual ++ ;
}

//**********************************************************************

void LectorPLY::abrirArchivo( const std::string & p_nombre_archivo )
{
   using namespace std ;
   string token ;

   num_vertices     = 0 ;
   num_caras        = 0 ;
   num_linea_actual = 0 ;

   nom_archivo = p_nombre_archivo ;
   if ( nom_archivo.substr( nom_archivo.find_last_of(".")+1 ) != "ply" )
      nom_archivo += ".ply" ;


   // const std::string  
   //    nom_archivo_path_1    = PathCarpetaMateriales() + "/plys/" + nom_archivo ,
   //    nom_archivo_procesado = ProcesarNombreArchivo( nom_archivo_path_1 );

   const std::string nom_archivo_path = BuscarArchivo( nom_archivo, "plys" );

   src.open( nom_archivo_path.c_str() ) ; // abrir (¿en modo lectura?)
   assert( src.is_open());

   src >> token ;

   if ( token != "ply" )
      error("el archivo de entrada no comienza con 'ply'.");

   leerRestoLinea();

   //cout << "leyendo archivo ply '" + nombre_archivo + "'" << endl ;
}

//**********************************************************************

void LectorPLY::leerCabecera( const bool lee_num_caras )
{
   string        token ;
   unsigned      state       = 0; // 0 antes de leer 'element vertex' (o 'element face'), 1 antes de leer 'element face', 2 después
   bool          en_cabecera = true ;
   long long int nv          = 0,
                 nc          = 0 ;

   // leer cabecera:

   while( en_cabecera )
   {
      if ( src.eof() )
         error("fin de archivo prematuro antes de end_header");

     src >> token ;

     if ( token == "end_header" )
     {  if ( state != 2 )
           error("no encuentro 'element vertex' o 'element face' en la cabecera");
        leerRestoLinea();
        en_cabecera = false ;
     }
     else if ( token == "comment" )
     {  leerRestoLinea();
     }
     else if ( token == "format" )
     {  src >> token ;
        if ( token != "ascii" )
        {  string msg = string("el formato del ply no es 'ascii', es '")+token+"', no lo puedo leer" ;
           error(msg.c_str());
        }
        leerRestoLinea();
     }
     else if ( token == "element" )
     {  src >> token ;
        if ( token == "vertex" )
        {  if ( state != 0 )
              error("la línea 'element vertex' va después de 'element face'");
           src >> nv ;
           //cout << "  numero de vértices == " << nv << endl ;
           state = lee_num_caras ? 1 : 2 ;
        }
        else if ( lee_num_caras && token == "face" )
        {  if ( state != 1 )
              error("'element vertex' va después de 'element face'");
           src >> nc ;
           //cout << "  número de caras == " << nc << endl ;
           state = 2 ;
        }
        else
        {  //cout << "  elemento '" + token + "' ignorado." << endl ;
        }
        leerRestoLinea();
     }
     else if ( token == "property" )
     {  leerRestoLinea();
     }
   } // end of while( en_cabecera )

   if ( nv <= 0 )
      error("no se ha encontrado el número de vértices, o bien es 0 o negativo");


   if ( lee_num_caras ) if ( nc <= 0 )
      error("no se ha encontrado el número de caras, o bien es 0 o negativo");

   if ( nv > numeric_limits<int>::max() )
      error("el número de vértices es superior al valor 'int' más grande posible.");

   if ( lee_num_caras )
   if ( nc > numeric_limits<int>::max() )
      error("el número de caras es superior al valor 'int' más grande posible.");

   num_vertices = unsigned(nv) ;
   num_caras    = unsigned(nc) ;
}

//**********************************************************************

void LectorPLY::leerVertices( std::vector<glm::vec3> & vertices  )
{
   using namespace glm ;
   
   string token ;

   vertices.resize( num_vertices );

   for( unsigned long long iv = 0 ; iv < num_vertices ; iv++ )
   {
      if ( src.eof() )
         error("encontrado fin de archivo prematuro en la lista de vértices.");
      long double x,y,z ;
      src >> x >> y >> z ;
      leerRestoLinea();
      vertices[iv] = vec3( float(x), float(y), float(z) );
   }
   //cout << "  fin de la lista de vértices" << endl << flush ;
}

//**********************************************************************

void LectorPLY::leerCaras( std::vector<glm::uvec3> & caras )
{
   using namespace glm ;
   
   string        token ;
   constexpr int nvc = 3 ;

   assert( nvc > 2 ) ; // tipicamente, 3 o 4.

   //cout << "  leyendo " << num_caras << " caras ...." << endl << flush ;

   caras.resize( num_caras );

   for( unsigned long long ifa = 0 ; ifa < num_caras ; ifa++ )
   {
      if ( src.eof() )
         error("fin de archivo prematuro en la lista de caras");

      unsigned nv ; src >> nv ;
      //cout << "reading face #" << ifa << " with " << nv << " vertexes: " ;

      if ( nv != nvc )
         error("encontrada una cara con un número de vértices distinto de 3.");

      //long long       iv[nvc] ;
      //const long long base = ifa*nvc ;

      uvec3 cara_leida ; assert( nvc == 3 ); //;-)

      for ( unsigned ivc = 0 ; ivc < nvc ; ivc++ )
      {
         src >> cara_leida[ivc] ;
         if ( num_vertices <= cara_leida[ivc] )
            error("encontrado algún índice de vértice igual o superior al número de vértices");
         caras[ ifa ] = cara_leida ;
      }
      leerRestoLinea();
   }
   //cout << "  fin de la lista de caras." << endl ;
}

//**********************************************************************

void LectorPLY::error( const char *msg_error )
{
   using namespace std ;
   cout << "error leyendo archivo ply '" << msg_error << "' en la línea " << num_linea_actual << endl
        << "programa terminado." << endl
        << flush ;

   exit(1);
}
