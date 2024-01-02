// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"
#include "examen-ec-p123.h"

using namespace std;
using namespace glm;

P1MallaCubo::P1MallaCubo()
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
         { +0.0, +1.0, +0.0}, // 8
         { +0.0, -1.0, +0.0}, //9
      } ;



   triangulos =
      {  {3,2,8},{2,8,6},{8,6,7},{3,8,7},{0,1,9},{0,4,9},{1,5,9},{9,4,5},
      {0,1,2},{1,3,2},{0,2,6},{0,6,4},{5,6,4},{5,7,6},{1,3,7},{1,7,5},
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
      {1.0, 0.0, 0.0},
      {0.0, 1.0, 1.0},
   }; 
}

P2Rejilla::P2Rejilla(unsigned n, unsigned m){
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

P3Cuadrado::P3Cuadrado()
{
    vertices={{-1.0,0.0,-1.0},{-1.0,0.0,+1.0},{+1.0,0.0,-1.0},{+1.0,0.0,+1.0}};
    triangulos={{0,1,3},{0,3,2}};
}

EsferaMovil::EsferaMovil(const int num_verts_per, const unsigned nperfiles, float radio){
    vector<vec3> perfil = vector<vec3>();
    float perimetro = 2*M_PI*radio;
    float division_perimtero = perimetro/(num_verts_per-1);
    for(int i=0; i<num_verts_per; i++){
        perfil.push_back(vec3(radio*cos(i*division_perimtero),radio*sin(i*division_perimtero),0.0));
    }
    inicializar(perfil,nperfiles);
}

P3Caja::P3Caja()
{
    NodoGrafoEscena *circulo = new NodoGrafoEscena();
    NodoGrafoEscena *puerta = new NodoGrafoEscena();
    NodoGrafoEscena *p3caja = new NodoGrafoEscena();

    
    p3caja->agregar(rotate(float(M_PI/2),vec3(0.0,0.0,1.0)));
    p3caja->agregar(translate(vec3(1.0,1.0,0.0)));
    p3caja->agregar(new P3Cuadrado());
    

    agregar(new P3Cuadrado());
    agregar(p3caja);
    agregar(rotate(float(M_PI/2),vec3(0.0,1.0,0.0)));
    agregar(p3caja);
    agregar(rotate(float(M_PI/2),vec3(0.0,1.0,0.0)));
    agregar(p3caja);
    agregar(rotate(float(M_PI/2),vec3(0.0,1.0,0.0)));
    agregar(p3caja);
    

    unsigned indice_circulo = circulo->agregar(translate(vec3(0.0,0.0,0.0)));
    circulo->agregar(translate(vec3(0.0,0.35,0.0)));
    circulo->agregar(scale(vec3(0.25,0.25,0.25)));
    circulo->agregar(new EsferaMovil(20,20,1.0));

    unsigned indice_puerta = puerta->agregar(rotate(float(0.0),vec3(1.0,0.0,0.0)));
    puerta->agregar(translate(vec3(0.0,2.0,0,0)));
    puerta->agregar(new P3Cuadrado());

    agregar(puerta);
    agregar(circulo);
    pm_bola = circulo->leerPtrMatriz(indice_circulo);
    pm_puerta = puerta->leerPtrMatriz(indice_puerta);


}

unsigned P3Caja::leerNumParametros() const{
    return 2;
}

void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
    switch(iParam){
        case 0:
            *pm_bola = translate(vec3(0.0,0.5*sin(2*M_PI*t_sec)+0.4,0.0));
        case 1:
            *pm_puerta = rotate((float)M_PI/2*sin(2*M_PI*t_sec),vec3(1.0,0.0,0.0));
    }
}