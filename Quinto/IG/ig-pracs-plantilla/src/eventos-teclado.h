// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de eventos de teclado (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaración de:
// **     + función 'FGE_PulsarLevantarTecla'
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

#ifndef EVENTOS_TECLADO_H 
#define EVENTOS_TECLADO_H 

#include "ig-aux.h"  // include cabeceras de opengl / glfw / glew


// ---------------------------------------------------------------------
// F.G. del evento de pulsar o levantar una tecla

void FGE_PulsarLevantarTecla( GLFWwindow* window, int key, int scancode, int action, int mods );
#endif 