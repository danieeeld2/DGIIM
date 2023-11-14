// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')

   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //

   if(dvao == nullptr){
      dvao = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones,vertices));
      dvao->agregar(new DescrVBOInds(triangulos));
      if(cc_tt_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver));
      if(col_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_colores,col_ver));
      if(nor_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_normales,nor_ver));
   }

   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'

   dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce

   if(tieneColor())
      cauce->popColor();
}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   if(cc_tt_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_coord_text,0);
   if(col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores,0);
   if(nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales,0);
   //    2. Dibujar la malla (únicamente visualizará los triángulos)
   dvao->draw(GL_TRIANGLES);
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   if(cc_tt_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_coord_text,1);
   if(col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores,1);
   if(nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales,1);
}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................

   LeerPLY(nombre_arch,vertices,triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

Tetraedro::Tetraedro()
:  MallaInd( "tetraedro 4 vértices" )
{
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { +1.0, -1.0, -1.0 }, // 1
         { +0.0, +1.0, -1.0 }, // 2
         { +0.0, +0.0, +1.0 }, // 3
      } ;

   triangulos = {
      {0,1,2}, {0,1,3}, {1,2,3}, {0,2,3}
   };

   ponerColor({0.5, 0.5, 0.5});
}

// -----------------------------------------------------------------------------------------------

CuboColores::CuboColores()
:  MallaInd("cubo 8 vétices a color")
{
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver = {
      {0.0, 0.0, 0.0}, // 0
      {0.0, 0.0, 1.0}, // 1
      {0.0, 1.0, 0.0}, // 2
      {0.0, 1.0, 1.0}, // 3
      {1.0, 0.0, 0.0}, // 4
      {1.0, 0.0, 1.0}, // 5
      {1.0, 1.0, 0.0}, // 6
      {1.0, 1.0, 1.0}, // 7
   };  
}

// -----------------------------------------------------------------------------------------------

/*
Calcular ángulos -> La medida de cada angulo es 2pi/n_vertices
En la circunferencia_
Cada vertice sera -> x_i=centro_x+radio*cos(angulo*i)
                     y_i=centro_y+radio*sin(angulo*i)
                     z_i=0
El resto:
Cada vertice será el punto medio entre dos vertices de la circunferencia
                     x_i=(x_i-1+x_i+1)/2
                     y_i=(y_i-1+y_i+1)/2
En este caso lo que vamos a hacer es calcular los vertices en la circ. de mitad de radio
*/


EstrellaZ::EstrellaZ(int n)
:  MallaInd("Estrella Z")
{
   float radio = 0.5f;
   float angulo = ((2*M_PI*radio)/n);
   float centro_x = 0.5f;
   float centro_y = 0.5f;
   float centro_z = 0.0f;

   for(int i=0;i<2*n;i++){
      if(i%2 == 0)
         vertices.push_back({centro_x+radio*cos(angulo*i),centro_y+radio*sin(angulo*i),centro_z});
      else
         vertices.push_back({centro_x+(radio/2.0f)*cos(angulo*i),centro_y+(radio/2.0f)*sin(angulo*i),centro_z});
   }
   vertices.push_back({centro_x,centro_y,centro_z});
   for(int i=0; i<2*n+1; i++){
      triangulos.push_back({i,(i+1)%(2*n),2*n});
   }
   for(int i=0; i<2*n; i++){
      col_ver.push_back(vertices[i]);
   }
   col_ver.push_back({1.0,1.0,1.0});   
}

// ****************************************************************************

CasaX::CasaX()
: MallaInd("Casa X"){
   vertices =
      {  { -1.5, -1.0, -1.0 }, // 0
         { -1.5, -1.0, +1.0 }, // 1
         { -1.5, +1.0, -1.0 }, // 2
         { -1.5, +1.0, +1.0 }, // 3
         { +1.5, -1.0, -1.0 }, // 4
         { +1.5, -1.0, +1.0 }, // 5
         { +1.5, +1.0, -1.0 }, // 6
         { +1.5, +1.0, +1.0 }, // 7
         { +1.5, +1.5, 0.0},
         { -1.5, +1.5, 0.0}
      } ;
   
   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         {2,3,9}, {6,7,8},
         {3,7,8}, {3,9,8},
         {9,2,6}, {6,8,9}
      } ;

   for(int i=0; i<vertices.size(); i++) {
      col_ver.push_back(vertices[i]);
   }
}

// ****************************************************************************

// Plano perpendicular al eje si lo corta en 90º

MallaTriangulo::MallaTriangulo()
: MallaInd("Malla Triangulo") {
   vertices = {
      {-0.5, 0.0, 0.0},
      {+0.5, 0.0, 0.0},
      {0.0, sqrt(2), 0.0}
   };
   triangulos = {
      {0,1,2}
   };
}

// ****************************************************************************

MallaCuadrado::MallaCuadrado()
: MallaInd("Malla Cuadrado") {
   vertices = {
      {-1.0,0.0,-1.0},
      {+1.0,0.0,-1.0},
      {-1.0,0.0,+1.0},
      {+1.0,0.0,+1.0}
   };
   triangulos = {
      {0,1,2},
      {1,3,2}
   };
}

// ****************************************************************************

MallaPiramideL::MallaPiramideL()
: MallaInd("Malla PiramideL") {
   vertices =
      {  { 0, 0, 2 }, 
         { 0, 0, 0 },  
         { 1, 0, 2 }, 
         { 1, 0, 1 }, 
         { 2, 0, 1 },  
         {2,0,0}, 
         {0,3,0}, 
      } ;

      triangulos =
      {  {0,2,3},{0,1,5} // X-
         ,{3,4,5},{3,6,4},{1,6,5},{1,6,0},{2,3,6}
      } ;

}

// ****************************************************************************

PiramideEstrellaZ::PiramideEstrellaZ(unsigned n)
: MallaInd("Piramide Z") {
   float centro_x = 0.5f;
   float centro_y = 0.5f;
   float centro_z = 0.0f;
   float radio = 0.5f;
   float angulo = ((2*M_PI*radio)/n);
   for(int i=0; i<2*n; i++){
      if(i%2 == 0){
         vertices.push_back({centro_x+radio*cos(angulo*i),centro_y+radio*sin(angulo*i),centro_z});
      }else{
         vertices.push_back({centro_x+(radio/2.0f)*cos(angulo*i),centro_y+(radio/2.0f)*sin(angulo*i),centro_z});
      }
   }
   vertices.push_back({centro_x,centro_y,centro_z});
   vertices.push_back({centro_x,centro_y,1.5f});
   for(int i=0; i<2*n+1; i++){
      triangulos.push_back({i,(i+1)%(2*n),2*n});
      triangulos.push_back({i,(i+1)%(2*n),2*n+1});
   }
   for(int i=1;i<2*n+2; i++){
      col_ver.push_back(vertices[i]);
   }
   col_ver.push_back({1.0f,1.0f,1.0f});
}

// ****************************************************************************

RejillaY::RejillaY(unsigned n, unsigned m){
   assert(n > 1 && m > 1);
   float escala_n = 1.0f/(n-1);
   float escala_m = 1.0f/(m-1);
   for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
         vertices.push_back({i*escala_n,0.0f,j*escala_m});
      }
   }
   for(int i=0; i<n-1; i++){
      for(int j=0; j<m-1; j++){
         triangulos.push_back({i*m+j,i*m+j+1,(i+1)*m+j});
         triangulos.push_back({i*m+j+1,(i+1)*m+j+1,(i+1)*m+j});
      }
   }
   for(int i=0;i<vertices.size(); i++){
      col_ver.push_back(vertices[i]);
   }
}

// ****************************************************************************

MallaTorre::MallaTorre(unsigned n)
: MallaInd("Torre") {
   assert(n > 1);
   unsigned int j = 0;
   vertices = {};

   vertices.push_back({+0.5,0,+0.5});// k
   vertices.push_back({-0.5,0,+0.5});// k+1
   vertices.push_back({-0.5,0,-0.5});// k+2
   vertices.push_back({+0.5,0,-0.5});// k+3


   for(unsigned i = 1; i <= n; ++i)
   {
      j += 4;
      vertices.push_back({+0.5,i,+0.5});// k
      vertices.push_back({-0.5,i,+0.5});// k+1
      vertices.push_back({-0.5,i,-0.5});// k+2
      vertices.push_back({+0.5,i,-0.5});// k+3

      triangulos.push_back({j-4, j-3, j});
      triangulos.push_back({j-3, j+1, j});

      triangulos.push_back({j-3, j-2, j+1});
      triangulos.push_back({j-2, j+2, j+1});

      triangulos.push_back({j-2, j-1, j+2});
      triangulos.push_back({j-1, j+3, j+2});

      triangulos.push_back({j-1, j-4, j+3});
      triangulos.push_back({j-4, j, j+3});
   }
   
}