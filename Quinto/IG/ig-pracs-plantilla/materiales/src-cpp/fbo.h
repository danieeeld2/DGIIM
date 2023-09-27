// *********************************************************************
// **
// ** Gestión de un Framebuffer object (clase Framebuffer) (declaración)
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

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "ig-aux.h"

class Framebuffer
{
   public:
      // crea un 'framebuffer object' en la memoria de la GPU
      Framebuffer( const int pancho, const int palto );

      // activa este 'framebuffer object', se hará rendering sobre él
      // si el alto o el ancho especificado es distinto del actual
      // se destruye el framebuffer en la GPU y se crea uno nuevo con estas
      // dimensiones
      void activar( const int pancho, const int palto );

      // activa el framebuffer por defecto (identificador 0)
      void desactivar();

      // leer el ancho y alto en pixels de este framebuffer
      int leerAncho() const ;
      int leerAlto() const ;

      // leer el color de un pixel del framebuffer
      // 'ix' debe estar entre 0 y el ancho (sin incluir)
      // 'iy' debe de estar entre 0 y el alto (sin incluir)
      // si no hay error, escribe en RGB el valor del pixel.
      void leerPixel( const int ix, const int iy, unsigned char * rgb );

      // devuelve el identificador actual del fbo (!=0)
      GLuint leerIdent() const { return fboId ; }

      // libera la memoria que ocupa en la GPU
      ~Framebuffer();

      GLuint leerTextId() { return textId ; }

   private:
      void inicializar( const int pancho, const int palto );
      void destruir();
      void comprobarEstado();

      GLuint fboId  = 0,  // identificador del framebuffer
             textId = 0,  // identificador de la textura de color asociada al framebuffer  (necesario?)
             rbId   = 0;  // identificador del z-buffer asociado al framebuffer (necesario?)
      int    ancho  = 0,  // ancho del framebuffer, en pixels
             alto   = 0;  // alto del framebuffer, en pixels
};

#endif
