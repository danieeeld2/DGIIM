// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 

using namespace glm;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   if (apl->iluminacion)
      pila_materiales->push();

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')

   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

  

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
    for( unsigned i = 0 ; i < entradas.size() ; i++ )
      {
      switch( entradas[i].tipo )
         {
         case TipoEntNGE::objeto : // entrada objeto:
            entradas[i].objeto->visualizarGL();//llamar recursivamente a visualizarGL
         break ;
         case TipoEntNGE::transformacion : // entrada transf.:
            cauce->compMM( *(entradas[i].matriz)); // componer matriz
         break ;
         case TipoEntNGE::material : // si la entrada es de tipo ’material’
            if ( apl->iluminacion ) // y si está activada la iluminación
            pila_materiales->activar( entradas[i].material );
         break ;
      }
   }


   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();
   

   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if(tieneColor()){
      cauce->popColor();
   }



   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)
   if (apl->iluminacion){
      pila_materiales->pop();
   }


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 

   cauce->pushMM();

   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').

   for(int i=0;i<entradas.size();i++){
      if(entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->visualizarGeomGL();
      }else if(entradas[i].tipo == TipoEntNGE::transformacion){
         cauce->compMM(*(entradas[i].matriz));
      }
   }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   cauce->popMM();

   // .......

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   cauce->pushMM();
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   for (int i = 0; i < entradas.size(); i++) {
      if (entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarNormalesGL();
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entradas[i].matriz);
   }
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   cauce->popMM();

   // .......

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent').
   int ident = leerIdentificador();
   if (ident != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(ident));
   }

   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   cauce->pushMM();

   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   for (int i = 0; i < entradas.size(); i++) {
      if (entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarModoSeleccionGL();
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entradas[i].matriz);
   }

   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   cauce->popMM();

   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........
   if (ident != -1)
      cauce->popColor();


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   entradas.push_back(entrada);
   return entradas.size()-1; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //

   if(indice >= entradas.size()){
      std::cerr << "Error: indice fuera de rango" << std::endl;
      exit(1);
   }else if(entradas[indice].tipo != TipoEntNGE::transformacion){
      std::cerr << "Error: la entrada no es de tipo transformacion" << std::endl;
      exit(1);
   }else if(entradas[indice].matriz == nullptr){
      std::cerr << "Error: el puntero a la matriz es nulo" << std::endl;
      exit(1);
   }

   return entradas[indice].matriz;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   
   if (centro_calculado)
      return;
   
   int contadorCentros = 0;
   mat4 matrizModelado(1.0f);
   vec3 centroAcumulado = vec3(0.0, 0.0, 0.0);

   for (unsigned int i = 0; i < entradas.size(); i++){
      if (entradas[i].tipo == TipoEntNGE::transformacion){
         matrizModelado = matrizModelado * (*entradas[i].matriz);
      }
      else if (entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->calcularCentroOC();
         centroAcumulado = centroAcumulado + vec3(matrizModelado * vec4(entradas[i].objeto->leerCentroOC(),1.0f));
         contadorCentros++;
      }
   }

   for (int i = 0; i < 3; i++) {
      centroAcumulado[i] /= contadorCentros;
   }
   ponerCentroOC( centroAcumulado);
   centro_calculado = true;

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   if (ident_busc == leerIdentificador()) {
      *objeto = this;
      centro_wc = leerCentroOC();
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   mat4 matrizmod = mmodelado;

   for(int i=0; i<entradas.size(); i++){
        if(entradas[i].tipo == TipoEntNGE::objeto){
            if(entradas[i].objeto->buscarObjeto(ident_busc, matrizmod, objeto, centro_wc)) return true;
        }
        else if(entradas[i].tipo == TipoEntNGE::transformacion) matrizmod = matrizmod*(*entradas[i].matriz);
   }



   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

// *****************************************************************************

GrafoCubos::GrafoCubos(){

   // base
   NodoGrafoEscena *base = new NodoGrafoEscena();
   base->agregar(translate(vec3(-0.5,-0.5,-0.5)));
   base->agregar(new Wall(pm_rot1));
   agregar(base);

   //Perpendicular al eje X negativo
   NodoGrafoEscena *ejexneg = new NodoGrafoEscena();
   ejexneg->agregar(translate(vec3(-0.5,0.5,-0.5)));
   ejexneg->agregar(rotate(-(float)M_PI/2,vec3{0,0,1}));
   ejexneg->agregar(new Wall(pm_rot2));
   agregar(ejexneg);

   //Techo
   NodoGrafoEscena *techo = new NodoGrafoEscena();
   techo->agregar(translate(vec3(-0.5,0.5,0.5)));
   techo->agregar(rotate((float)M_PI,vec3{1,0,0}));
   techo->agregar(new Wall(pm_rot3));
   agregar(techo);

   //Perpendicular al eje X positivo
   NodoGrafoEscena *ejexpos = new NodoGrafoEscena();
   ejexpos->agregar(translate(vec3(0.5,-0.5,-0.5)));
   ejexpos->agregar(rotate((float)M_PI/2,vec3{0,0,1}));
   ejexpos->agregar(new Wall(pm_rot4));
   agregar(ejexpos);

   //Perpendicular al eje Z negativo
   NodoGrafoEscena *ejezneg = new NodoGrafoEscena();
   ejezneg->agregar(translate(vec3(0.5,-0.5,-0.5)));
   ejezneg->agregar(rotate((float)M_PI,vec3{0,1,1}));
   ejezneg->agregar(new Wall(pm_rot5));
   agregar(ejezneg);

   //Perpendicular al eje Z positivo
   NodoGrafoEscena *ejezpos = new NodoGrafoEscena();
   ejezpos->agregar(translate(vec3(0.5,-0.5,0.5)));
   ejezpos->agregar(rotate((float)M_PI/2,vec3{0,0,1}));
   ejezpos->agregar(rotate(3*(float)M_PI/2,vec3{1,0,0}));
   ejezpos->agregar(new Wall(pm_rot6));
   agregar(ejezpos);

}

Wall::Wall(mat4 * &pm_rot){

   NodoGrafoEscena  *pared = new NodoGrafoEscena();
   pared->agregar(new RejillaY(20,20));
   agregar(pared);

   NodoGrafoEscena * cubo = new NodoGrafoEscena();
   
   cubo->agregar(translate(vec3(0.5,-0.25,0.5)));
   cubo->agregar(scale(vec3(0.125,0.25,0.125)));
   unsigned ind = cubo->agregar(rotate(0.0f,vec3{0,1,0}));
   cubo->agregar(new Cubo());
   agregar(cubo);
   pm_rot = cubo->leerPtrMatriz(ind);

}

void GrafoCubos::fijarRot1( const float alpha ){
    *pm_rot1 = rotate( alpha, vec3{0, 1, 0} );
}

void GrafoCubos::fijarRot2( const float alpha ){
    *pm_rot2 = rotate( alpha, vec3{0, 1, 0} );
}

void GrafoCubos::fijarRot3( const float alpha ){
    *pm_rot3 = rotate( alpha, vec3{0, 1, 0} );
}

void GrafoCubos::fijarRot4( const float alpha ){
    *pm_rot4 = rotate( alpha, vec3{0, 1, 0} );
}

void GrafoCubos::fijarRot5( const float alpha ){
    *pm_rot5 = rotate( alpha, vec3{0, 1, 0} );
}

void GrafoCubos::fijarRot6( const float alpha ){
    *pm_rot6 = rotate( alpha, vec3{0, 1, 0} );
}

unsigned GrafoCubos::leerNumParametros() const {
   return 6;
}

void GrafoCubos::actualizarEstadoParametro( const unsigned iParam, const float tSec ){
    assert( iParam < leerNumParametros() );
    switch (iParam)
    {
    case 0:
         fijarRot1(2.5*tSec);
         fijarRot2(2.5*tSec);
         fijarRot3(2.5*tSec);
         fijarRot4(2.5*tSec);
         fijarRot5(2.5*tSec);
         fijarRot6(2.5*tSec);
      break;
    }
}

// ****************************************************************************************************


NodoCubo24::NodoCubo24(){
   agregar( new Material( new Textura("window-icon.jpg") , 0.5, 0.3, 0.7, 100.0) );
   agregar( new Cubo24() );
}



