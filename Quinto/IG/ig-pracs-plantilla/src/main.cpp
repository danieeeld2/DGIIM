// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Implementación de la función 'main'.
// ** bucle de eventos y visualización de un cuadro.
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de la función 'main' del programa:
// ** crea el objeto global 'AplicaciónIG' ('apl'), y ejecuta el 
// ** principal de gestión de eventos de GLFW.
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

#include "aplicacion-ig.h"



// evita la necesidad de escribir std::
using namespace std ;

// ---------------------------------------------------------------------
// punto de entrada al programa

int main( int argc, char *argv[] )
{   


   using namespace std ;
   cout << "Prácticas de IG (GIM) - curso 2023-24 (" << NOMBRE_OS << ")" << endl ;

   // Crear el objeto 'apl' con las variables globales de la aplicación 
   // y los diversos parámetros de configuración
   apl = new AplicacionIG(); 
   assert( apl != nullptr );

   // ejecuta el bucle principal de eventos y visualización 
   apl->buclePrincipalGLFW();  

   // se ha terminado normalmente el programa (sin errores)
   delete apl ;
   cout << "Programa terminado normalmente." << endl ;
   return 0;
}
