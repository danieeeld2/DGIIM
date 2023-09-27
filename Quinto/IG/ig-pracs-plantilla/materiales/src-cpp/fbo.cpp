// *********************************************************************
// **
// ** Gestión de un Framebuffer object (clase Framebuffer) (implementación)
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
#include "fbo.h"

// ---------------------------------------------------------------------------------

Framebuffer::Framebuffer( const int pancho, const int palto )
{
   inicializar( pancho, palto );
}
// ---------------------------------------------------------------------------------

void Framebuffer::inicializar( const int pancho, const int palto )
{
   assert( fboId == 0 );
   assert( rbId  == 0 );
   assert( textId == 0 );
   assert( ancho == 0 );
   assert( alto == 0 );

   // leer y comprobar parámetros, comprobar y resetear errores previos de OpenGL
   ancho = pancho; assert( 2 < ancho );
   alto  = palto;  assert( 2 < alto );
   CError();

   // crear frame buffer (identificador 'fboId')
   glGenFramebuffers( 1, &fboId );
   CError();
   assert( 0 < fboId );

   // crear buffer o textura de color (identificador 'textid')
   //( reserva memoria en la GPU, sin asignar valores a los pixels)
   glGenTextures( 1, &textId );
   assert( 0 < textId );
   glBindTexture( GL_TEXTURE_2D, textId );
   constexpr GLint  cb_internal_format = GL_RGB;
   constexpr GLenum cb_format          = GL_RGB,
                    cb_type            = GL_UNSIGNED_BYTE ;
   glTexImage2D( GL_TEXTURE_2D, 0, cb_internal_format, ancho, alto, 0, cb_format, cb_type, nullptr );
   CError();

   // configurar buffer de color
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   CError();

   // adjuntar textura de color al framebuffer (como 'color attachment')
   glBindFramebuffer( GL_FRAMEBUFFER, fboId );
   glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textId, 0 );
   CError();

   // crear el render buffer (el z-buffer de framebuffer) (identificador en 'rbId')
   glGenRenderbuffers( 1, &rbId );
   assert( 0 < rbId );
	glBindRenderbuffer( GL_RENDERBUFFER, rbId );
   const GLenum rb_internal_format = GL_DEPTH_COMPONENT ;
   glRenderbufferStorage( GL_RENDERBUFFER, rb_internal_format, ancho, alto );
   CError();

   // adjuntar el z-buffer al framebuffer (como 'depth attachment')
   glBindFramebuffer( GL_FRAMEBUFFER, fboId );
   glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbId );
   CError();

   // hecho: comprobar que el estado es el correcto
   comprobarEstado( );

   // volver a activar el framebuffer y texura por defecto (el inicial de OpenGL)
   glBindFramebuffer( GL_FRAMEBUFFER, 0 );
   glBindTexture( GL_TEXTURE_2D, 0 );
}
// ------------------------------------------------------------------------------

void Framebuffer::activar( const int pancho, const int palto )
{
   assert( fboId != 0 );
   if ( ancho != pancho || alto != palto )
   {
      destruir();
      inicializar( pancho, palto );
   }
   glBindFramebuffer( GL_FRAMEBUFFER, fboId );
   CError();
}
// ------------------------------------------------------------------------------

void Framebuffer::desactivar()
{
   CError();
   glBindFramebuffer( GL_FRAMEBUFFER, 0 );
   CError();
}
// ------------------------------------------------------------------------------

int Framebuffer::leerAncho() const
{
   return ancho ;
}
// ------------------------------------------------------------------------------

int Framebuffer::leerAlto() const
{
   return alto ;
}


// ------------------------------------------------------------------------------

Framebuffer::~Framebuffer()
{
   destruir();
}
// ------------------------------------------------------------------------------

void Framebuffer::destruir()
{
   CError();
   glDeleteTextures( 1, &textId );
   glDeleteRenderbuffers( 1, &rbId );
   glBindFramebuffer( GL_FRAMEBUFFER, 0 );
   glDeleteFramebuffers( 1, &fboId );
   CError();

   fboId  = 0 ;
   rbId   = 0 ;
   textId = 0 ;
   ancho  = 0 ;
   alto   = 0 ;
}
// ------------------------------------------------------------------------------

void Framebuffer::comprobarEstado()
{
   using namespace std ;

   GLenum status;
   bool ok = false ;
   glBindFramebuffer( GL_FRAMEBUFFER, fboId ) ;
   CError();
   status = (GLenum) glCheckFramebufferStatus( GL_FRAMEBUFFER );

   switch( status )
   {
      case GL_FRAMEBUFFER_COMPLETE:
         ok = true ;
         break;

      case GL_FRAMEBUFFER_UNSUPPORTED:
         cout << "Unsupported framebuffer format" << endl ;
         break;

      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
         cout << "Framebuffer incomplete, missing attachment" << endl ;
         break;

      case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
         cout << "Framebuffer incomplete, missing draw buffer" << endl ;
         break;

      case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
         cout << "Framebuffer incomplete, missing read buffer" << endl ;
         break;

      #ifdef GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT
      case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT:
         cout << "Framebuffer incomplete, duplicate attachment" << endl ;
         break;
      #endif

      #ifdef GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
      case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
         cout << "Framebuffer incomplete, attached images must have same dimensions" << endl ;
         break;
      #endif

      #ifdef GL_FRAMEBUFFER_INCOMPLETE_FORMATS
      case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
         cout << "Framebuffer incomplete, attached images must have same format" << endl ;
         break;
      #endif

      default:
         cout << "unknown framebuffer status (?)" << endl ;
         break ;
   }

	if ( ! ok )
	{
      cout << "unable to initialize FBO due to reason above." << endl ;
	   exit(1);
	}
}
