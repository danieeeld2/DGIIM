// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de eventos de ratón (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaración de las funciones gestoras de eventos (FGEs) producidos 
// ** por el ratón:
// **
// **     + FGE_Scroll - movimiento de la rueda del ratón
// **     + FGE_PulsarLevantarBotonRaton - botones del ratón
// **     + FGE_MovimientoRaton - movimiento del ratón (con un botón pulsado, si no se ignora)
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

#ifndef EVENTOS_RATON_H 
#define EVENTOS_RATON_H 

#include "ig-aux.h"  // include cabeceras de opengl / glfw / glew



// --------------------------------------------------------------------
// función gestora del evento de hacer scroll
// (se registra con 'glfwSetScrollCallback'

void FGE_Scroll( GLFWwindow* window, double xoffset, double yoffset  );

// --------------------------------------------------------------------
// función gestora del evento de pulsar/levantar tecla del ratón
// (se registra con 'glfwSetMouseButtonCallback'

void FGE_PulsarLevantarBotonRaton( GLFWwindow* window, int button, int action, int mods );

// --------------------------------------------------------------------
// función gestora del evento de ratón movido a una nueva posición
// (se registra con 'glfwSetCursorPosCallback'

void FGE_MovimientoRaton( GLFWwindow* window, double xpos, double ypos );
#endif 