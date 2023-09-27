// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de animaciones (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaraciones de las funciones:
// **    + ActualizarEstado: actualiza el estado de un objeto 3D
// **    + AnimacionesActivadas: indica si las animaciones están activadas o no
// **    + ProcesarTeclaAnimacion: procesa una pulsación de una tecla estando baja la tecla 'A'
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

#ifndef ANIMACION_H
#define ANIMACION_H

#include "objeto3d.h"
#include "ig-aux.h"

// #####################################
// Funciones usadas para animacion:
// ####################################



// Función  que actuliza periodicamente el estado del objeto
// Si el objeto no tiene parámetros: no hace nada y devuelve false
// En otro caso:
//    calcula el tiempo real transcurrido desde la última llamada a esta función
//    actualiza el estado del objeto, usando ese tiempo transcurrido

bool ActualizarEstado( Objeto3D & objeto ) ;

// devuelve true sii las nimaciones están activadas
bool AnimacionesActivadas() ;

// gestiona una tecla correspondiente a animaciones (se llama cuando se pulsa una
// tecla la vez que la tecla 'A' está pulsada)
bool ProcesarTeclaAnimacion( Objeto3D * objeto, int glfw_key ) ;

#endif // ANIMACION_H
