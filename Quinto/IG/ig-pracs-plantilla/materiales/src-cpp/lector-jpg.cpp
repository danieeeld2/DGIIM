// *********************************************************************
// **
// ** Lector de archivos JPG (implementación)
// **
// ** código adaptado a C++11 a partir de:
// ** https://github.com/Tinker-S/libjpeg-sample/blob/master/jpeg_sample.c
// **
// ** Carlos Ureña - 2012- 2019
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


#include <stdlib.h>
#include <string>
#include <iostream>
#include <cassert>
#include <jpeglib.h>


#include "ig-aux.h" // para 'ProcesarNombreArchivo'
#include "lector-jpg.h"

/** -------------------------------------------------------------------- **/
/// @brief abre un archivo para lectura en modo binario (modo="rb")
///        usa 'fopen' en mac y linux, y fopen_s en windows.
/// @param nombre  (char *) - nombre del archivo
/// @return (FILE *), puntero al file, o nullptr si ha habido algún error
///
FILE * abrir_archivo_rb( const char * nombre )
{
#ifdef _WIN32
   FILE * infile = nullptr ; 
   fopen_s( &infile, nombre, "rb" ); 
   return infile ;
#else 
   return fopen( nombre, "rb" );
#endif 
}

//----------------------------------------------------------------------
// función de lectura de una imagen
// devuelve un puntero a los pixels (tres bytes por pixel, por filas)
// escribe en ancho y alto el número de columnas y filas de la imagen, respectivamente.
// El nombre del archivo debe ir sin el 'path', se busca en 'materiales/imgs' y si 
// no está se busca en 'archivos-alumno'
//
// código adaptado a C++11 a partir de:
// https://github.com/Tinker-S/libjpeg-sample/blob/master/jpeg_sample.c

unsigned char * LeerArchivoJPEG( const char *nombre_arch, unsigned &ancho, unsigned &alto )
{
   using namespace std ;

   const std::string nombre_arch_path = BuscarArchivo( nombre_arch, "imgs" );

  //cout << "archivo '" << nombre_arch << "' encontrado en '" << nombre_arch_path << "'." << endl ;
   
   struct jpeg_decompress_struct cinfo;
   struct jpeg_error_mgr         jerr;

   JSAMPROW        row_ptr[1] = { nullptr };
   unsigned long   location   = 0 ;
   unsigned char * buff       = nullptr ;
   FILE *          infile     = abrir_archivo_rb( nombre_arch_path.c_str() );

   if ( ! infile )
   {  
      cerr << "Error leyendo archivo JPEG '" << nombre_arch << "': el archivo no existe o no es legible." << endl ;
      cerr << "(se intenta leer de: " << nombre_arch_path << ")" << endl ;
      exit(1);
   }
   cinfo.err = jpeg_std_error( &jerr );
   jpeg_create_decompress( &cinfo );
   jpeg_stdio_src( &cinfo, infile );
   jpeg_read_header( &cinfo, TRUE );
   jpeg_start_decompress( &cinfo );
   const int num_components  = cinfo.num_components ;

   if ( cinfo.out_color_space != JCS_RGB || num_components != 3 )
   {  cerr << "error leyendo archivo JPEG '" << nombre_arch << "': el formato no es RGB (3 componentes)" << endl ;
      exit(1);
   }
   ancho      = cinfo.output_width;
   alto       = cinfo.output_height ;
   row_ptr[0] = new unsigned char [ ancho*num_components ];
   buff       = new unsigned char [ alto*ancho*num_components ];

   while( cinfo.output_scanline < alto )
	{  jpeg_read_scanlines( &cinfo, row_ptr, 1 );
      for( unsigned long i = 0 ; i < ancho*num_components ; i++ )
         buff[location++] = row_ptr[0][i];
	}
   jpeg_finish_decompress( &cinfo );
   jpeg_destroy_decompress( &cinfo );
   fclose( infile );
   delete [] row_ptr[0] ;

   //cout << "leído archivo jpg" << endl ;

   return buff ;
}
