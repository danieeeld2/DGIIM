// Daniel Alconchel Vázquez
// InfoMates

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

Esferas::Esferas(const int num_verts_per, const unsigned nperfiles, float radio){
    vector<vec3> perfil = vector<vec3>();
    float perimetro = 2*M_PI*radio;
    float division_perimtero = perimetro/(num_verts_per-1);
    for(int i=0; i<num_verts_per; i++){
        perfil.push_back(vec3(radio*cos(i*division_perimtero),radio*sin(i*division_perimtero),0.0));
    }
    inicializar(perfil,nperfiles);
}

ConoExtremidades::ConoExtremidades(const int num_verts_per, const unsigned nperfiles, float altura, float radio){
    vector<vec3> perfil = vector<vec3>();
    float altura_x = altura/(num_verts_per-1);
    for(int i=0; i<num_verts_per; i++){
        float x = (num_verts_per-1-i)*(radio/(num_verts_per-1));
        perfil.push_back(vec3(x,altura_x*i,0.0));
    }
    inicializar(perfil,nperfiles);
}

CuboCabeza::CuboCabeza(){
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

Robot::Robot(){
    ponerNombre("robot");
    NodoGrafoEscena *robot = new NodoGrafoEscena();

    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    cuerpo->ponerColor({0.3,0.3,0.3});
    cuerpo->agregar(new Esferas(20,20,1.0));

    NodoGrafoEscena *cabeza = new NodoGrafoEscena();
    NodoGrafoEscena *ojos = new NodoGrafoEscena();
    NodoGrafoEscena *ojo1 = new NodoGrafoEscena();
    NodoGrafoEscena *ojo2 = new NodoGrafoEscena();
    
    unsigned ind_tras_ojos = ojos->agregar(translate(vec3(0.0,0.0,0.0)));
    ojos->ponerColor({0.0,0.0,0.0});
    ojo1->agregar(translate(vec3(-0.25,1.25,0.5)));
    ojo1->agregar(scale(vec3(0.1,0.1,0.1)));
    ojo1->agregar(new Esferas(20,20,1.0));
    ojo2->agregar(translate(vec3(0.25,1.25,0.5)));
    ojo2->agregar(scale(vec3(0.1,0.1,0.1)));
    ojo2->agregar(new Esferas(20,20,1.0));
    ojos->agregar(ojo1);
    ojos->agregar(ojo2);

    unsigned ind_rot_cabeza = cabeza->agregar(rotate(0.0f,vec3{0.0,1.0,0.0}));
    cabeza->agregar(ojos);
    cabeza->agregar(translate(vec3(0.0,1.25,0.0)));
    cabeza->agregar(scale(vec3(0.5,0.25,0.5)));
    cabeza->ponerColor({0.5,0.5,0.5});
    cabeza->agregar(new CuboCabeza());
    

    robot->agregar(cuerpo);
    robot->agregar(cabeza);
    pm_tras_ojos = ojos->leerPtrMatriz(ind_tras_ojos);
    pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);
    agregar(robot);
}

unsigned Robot::leerNumParametros() const{
    return 2;
}

void Robot::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
    switch(iParam){
        case 0:
            *pm_tras_ojos = translate(vec3(0.5*sin(2*M_PI*t_sec),0.0,0.0));
            break;
        case 1:
            *pm_rot_cabeza = rotate(float(0.5*sin(2*M_PI*t_sec)),vec3{0.0,1.0,0.0});
            break;
    }
}