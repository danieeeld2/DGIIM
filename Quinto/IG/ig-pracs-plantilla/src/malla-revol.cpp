// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
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
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

   // Partimos de las tablas de vértices y triángulos vacías
   vertices = std::vector<glm::vec3>();
   triangulos = std::vector<glm::uvec3>();
   unsigned int m = perfil.size();
   unsigned int n = num_copias;

   // Completamos vértices
   for(unsigned int i=0; i<n; i++){
      for(unsigned int j=0; j<m; j++){
         // Obtener las coordenadas del punto perfil[j] girado 2pi*i/(n-1) sobre eje Y
         glm::vec3 q,p_j = perfil[j];
         float c = cos(float(2*M_PI*i)/(n-1));
         float s = sin(float(2*M_PI*i)/(n-1));
         q[0] = c*p_j[0] + s*p_j[2];
         q[1] = p_j[1];
         q[2] = -s*p_j[0] + c*p_j[2];

         vertices.push_back(q);
      }
   }

   // Completamos triángulos
   for (unsigned int i = 0; i < n-1; i++){
      for (unsigned int j = 0; j < m-1; j++){
         unsigned int k = i*m + j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch,perfil);
   inicializar(perfil,nperfiles);

}

// Práctica 2: Clases Cilindro, Cono y Esfera

// Cilindro con el centro de la base en el origen, y con radio y altura 1

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("cilindro");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   for(int i=0; i<num_verts_per; i++){
      float altura = i*(1.0/(num_verts_per-1));
      perfil.push_back(glm::vec3(1.0,altura,0.0));
   }
   inicializar(perfil,nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("esfera");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();
   float perimetro = (2*M_PI*1.0/(num_verts_per-1));
   for(int i=0; i<num_verts_per; i++){
      perfil.push_back(glm::vec3(cos(i*perimetro),sin(i*perimetro),0.0));
   }
   inicializar(perfil,nperfiles);
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles){
   ponerNombre("cono");
   std::vector<glm::vec3> perfil = std::vector<glm::vec3>();

   for(int i=0; i<num_verts_per; i++){
      float altura = i*(1.0/(num_verts_per-1));
      float x = (num_verts_per-1-i)*(1.0/(num_verts_per-1));
      perfil.push_back(glm::vec3(x,altura,0.0));
   }
   inicializar(perfil,nperfiles);
}