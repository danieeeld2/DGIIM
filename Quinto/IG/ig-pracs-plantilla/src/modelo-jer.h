// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

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
        Esferas(const int num_verts_per, const unsigned nperfiles);
};

class ConoExtremidades : public MallaRevol {
    public:
        ConoExtremidades(const int num_verts_per, const unsigned nperfiles, float altura, float radio);
};

class CuboCabeza : public MallaInd {
    public:
        // Sustituimos por el Cubo24, pensado para iluminacion y normales
        CuboCabeza();
};

class Robot : public NodoGrafoEscena {
    protected:
        mat4 *pm_rot_cabeza = nullptr;
        mat4 *pm_rot_cuerpo = nullptr;
        mat4 *pm_tras_brazo1 = nullptr;
        mat4 *pm_rot_brazo2 = nullptr;
        mat4 *pm_tras_cuerpo = nullptr;
    public:
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        Robot();
};

#endif