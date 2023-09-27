// *********************************************************************
// **
// ** Gestión de la selección (declaración)
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** Declaración de las funciones:
// **   + Selección 
// **   + FijarColVertsIdent
// **   + LeerIdentEnPixel
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

#ifndef SELECCION_H
#define SELECCION_H

#include "objeto3d.h"
#include "escena.h"


// calcula un color usando un identificador entero no negativo
glm::vec4 ColorDesdeIdent( const int ident )  ; // 0 ≤ ident < 2^24

// leer un identificador entero codificado en el color de un pixel en el
// framebuffer activo actualmente
int LeerIdentEnPixel( int xpix, int ypix );




#endif // SELECCION_H
