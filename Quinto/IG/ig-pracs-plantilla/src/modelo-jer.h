// Daniel Alconchel Vázquez 
// Informática y Matemáticas

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

class Esferas : public MallaRevol {
    public:
        Esferas(const int num_verts_per, const unsigned nperfiles, float radio);
};

class ConoExtremidades : public MallaRevol {
    public:
        ConoExtremidades(const int num_verts_per, const unsigned nperfiles, float altura, float radio);
};

class CuboCabeza : public MallaInd {
    public:
        CuboCabeza();
};

class Robot : public NodoGrafoEscena {
    protected:
        mat4 *pm_tras_ojos = nullptr;
        mat4 *pm_rot_cabeza = nullptr;
    public:
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        Robot();
};

#endif