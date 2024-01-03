// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

// Daniel Alconchel Vázquez
// InfoMates

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

Esferas::Esferas(const int num_verts_per, const unsigned nperfiles){
    std::vector<glm::vec3> perfil = std::vector<glm::vec3>();
    float perimetro = (2*M_PI*1.0/(num_verts_per-1));
    for(int i=0; i<num_verts_per; i++){
        perfil.push_back(glm::vec3(cos(i*perimetro),sin(i*perimetro),0.0));
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
      {
         {+1.0, -1.0, +1.0}, // 0
         {+1.0, +1.0, +1.0}, // 1
         {+1.0, +1.0, -1.0}, // 2
         {+1.0, -1.0, -1.0}, // 3


         {-1.0, -1.0, +1.0}, // 4
         {-1.0, +1.0, +1.0}, // 5
         {+1.0, +1.0, +1.0}, // 6
         {+1.0, -1.0, +1.0}, // 7


         {-1.0, -1.0, -1.0}, // 8
         {-1.0, +1.0, -1.0}, // 9
         {-1.0, +1.0, +1.0}, // 10
         {-1.0, -1.0, +1.0}, // 11

         {+1.0, -1.0, -1.0}, // 12
         {+1.0, +1.0, -1.0}, // 13
         {-1.0, +1.0, -1.0}, // 14
         {-1.0, -1.0, -1.0}, // 15


         {+1.0, +1.0, +1.0}, // 16
         {-1.0, +1.0, +1.0}, // 17
         {-1.0, +1.0, -1.0}, // 18
         {+1.0, +1.0, -1.0}, // 19

         {+1.0, -1.0, +1.0}, // 20
         {-1.0, -1.0, +1.0}, // 21
         {-1.0, -1.0, -1.0}, // 22
         {+1.0, -1.0, -1.0} // 23
      };

   triangulos =
      {
         {0, 3, 2},
         {0, 2, 1},

         {4, 7, 6},
         {4, 6, 5},

         {8, 11, 10},
         {8, 10, 9},

         {12, 15, 14},
         {12, 14, 13},

         {16, 19, 18},
         {16, 18, 17},

         {20, 23, 22},
         {20, 22, 21}
      };
      
   cc_tt_ver = {
      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0}
   };

   calcularNormales();
}

Robot::Robot(){

    unsigned ident = 1;

    ponerNombre("robot");
    NodoGrafoEscena *robot = new NodoGrafoEscena();

    /*
    CUERPO DEL ROBOT:
        - Esfera de radio 1
        - Textura de balón de fútbol en el plano XY para darle efecto de velocidad a la bola
        - Bastante brillante
    */

    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("Cuerpo del Robot");
    cuerpo->ponerIdentificador(ident);
    ident++;
    unsigned ind_rot_cuerpo = cuerpo->agregar(rotate(0.0f,vec3{0.0,0.0,1.0}));
    TexturaXY *texturaCuerpo = new TexturaXY("balon.jpeg");
    Material *materialCuerpo = new Material(texturaCuerpo,0.95, 0.85, 0.65, 35.0);
    //cuerpo->ponerColor({0.3,0.3,0.3});
    cuerpo->agregar(materialCuerpo);
    cuerpo->agregar(new Esferas(50,100));

    NodoGrafoEscena *cabeza = new NodoGrafoEscena();
    NodoGrafoEscena *ojos = new NodoGrafoEscena();
    NodoGrafoEscena *ojo1 = new NodoGrafoEscena();
    NodoGrafoEscena *ojo2 = new NodoGrafoEscena();

    /*
    OJOS DEL ROBOT:
        
    */

    Material *materialOjos = new Material(0.75, 0.85, 0.75, 25.0);
    ojos->ponerColor({0.0,0.0,0.0});
    ojo1->ponerNombre("Ojo izquierdo");
    ojo1->ponerIdentificador(ident);
    ident++;
    ojo1->agregar(translate(vec3(-0.25,1.25,0.5)));
    ojo1->agregar(scale(vec3(0.1,0.1,0.1)));
    ojo1->agregar(new Esferas(50,100));
    ojo2->ponerNombre("Ojo derecho");
    ojo2->ponerIdentificador(ident);
    ident++;
    ojo2->agregar(translate(vec3(0.25,1.25,0.5)));
    ojo2->agregar(scale(vec3(0.1,0.1,0.1)));
    ojo2->agregar(new Esferas(50,100));
    ojos->agregar(materialOjos);
    ojos->agregar(ojo1);
    ojos->agregar(ojo2);

    /*
    CABEZA DEL ROBOT:
        
    */

    cabeza->ponerNombre("Cabeza del Robot");
    cabeza->ponerIdentificador(ident);
    ident++;
    Textura *texturaCabeza = new Textura("campo.jpeg");
    Material *materialCabeza = new Material(texturaCabeza, 0.75, 0.85, 0.75, 25.0);
    unsigned ind_rot_cabeza = cabeza->agregar(rotate(0.0f,vec3{0.0,1.0,0.0}));
    cabeza->agregar(ojos);
    cabeza->agregar(translate(vec3(0.0,1.25,0.0)));
    cabeza->agregar(scale(vec3(0.5,0.25,0.5)));
    // cabeza->ponerColor({0.5,0.5,0.5});
    cabeza->agregar(materialCabeza);
    cabeza->agregar(new CuboCabeza());

    NodoGrafoEscena *brazo1 = new NodoGrafoEscena();
    NodoGrafoEscena *brazo2 = new NodoGrafoEscena();

    /*
    BRAZO DEL ROBOT:

    */

    brazo1->ponerNombre("Brazo izquierdo");
    brazo1->ponerIdentificador(ident);
    ident++;
    Textura *texturaBrazoIzq = new Textura("Sevilla.jpeg");
    Material *materialBrazoIzq = new Material(texturaBrazoIzq, 0.75, 0.85, 0.75, 25.0);
    unsigned ind_tras_brazo1 = brazo1->agregar(translate(vec3(0.0,0.0,0.0)));
    brazo1->agregar(rotate(float(M_PI/2),vec3{0.0,0.0,1.0}));
    brazo1->agregar(translate(vec3(0.0,1.0,0.0)));
    brazo1->agregar(materialBrazoIzq);
    brazo1->agregar(new ConoExtremidades(20,20,1.0,0.25));
    brazo2->ponerNombre("Brazo derecho");
    brazo2->ponerIdentificador(ident);
    ident++;
    Textura *texturaBrazoDer = new Textura("Betis.jpeg");
    Material *materialBrazoDer = new Material(texturaBrazoDer, 0.75, 0.85, 0.75, 25.0);
    unsigned ind_tras_brazo2 = brazo2->agregar(translate(vec3(0.0,0.0,0.0)));
    brazo2->agregar(rotate(float(-1*M_PI/2),vec3{0.0,0.0,1.0}));
    brazo2->agregar(translate(vec3(0.0,1.0,0.0)));
    brazo2->agregar(materialBrazoDer);
    brazo2->agregar(new ConoExtremidades(20,20,1.0,0.25));
    
    unsigned ind_tras_cuerpo = robot->agregar(translate(vec3(0.0,0.0,0.0)));
    robot->agregar(cuerpo);
    robot->agregar(cabeza);
    robot->agregar(brazo1);
    robot->agregar(brazo2);
    pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);
    pm_rot_cuerpo = cuerpo->leerPtrMatriz(ind_rot_cuerpo);
    pm_tras_brazo1 = brazo1->leerPtrMatriz(ind_tras_brazo1);
    pm_rot_brazo2 = brazo2->leerPtrMatriz(ind_tras_brazo2);
    agregar(robot);
    pm_tras_cuerpo = robot->leerPtrMatriz(ind_tras_cuerpo);
    
}

unsigned Robot::leerNumParametros() const{
    return 4;
}

void Robot::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
    switch(iParam){
        case 0:
            *pm_rot_cabeza *= rotate(float(M_PI/10000),vec3{0.0,1.0,0.0});
            break;
        case 1:
            *pm_tras_brazo1 = translate(vec3(0.5*sin(2*M_PI*t_sec)-0.5,0.0,0.0));
            break;
        case 2:
            *pm_rot_brazo2 = translate(vec3(0.0,0.5*cos(2*M_PI*t_sec),0.5*sin(2*M_PI*t_sec)));
            break;
        case 3:
            *pm_rot_cuerpo = rotate(float(0.5*cos(2*M_PI*t_sec)),vec3{1.0,0.0,0.0});
            *pm_tras_cuerpo = translate(vec3(0.0,0.0,0.5*sin(2*M_PI*t_sec)));
            break;
            
    }
}