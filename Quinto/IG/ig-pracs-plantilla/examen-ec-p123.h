// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

class P1MallaCubo : public MallaInd
{
   public:
      P1MallaCubo();
};

class P2Rejilla : public MallaCuadrado
{
    public:
        P2Rejilla(unsigned n, unsigned m);
};

class P3Cuadrado : public MallaInd
{
    public:
        P3Cuadrado();
};

class EsferaMovil : public MallaRevol {
    public:
        EsferaMovil(const int num_verts_per, const unsigned nperfiles, float radio);
};

class P3Caja : public NodoGrafoEscena
{
    protected:
        mat4 *pm_puerta=nullptr;
        mat4 *pm_bola=nullptr;
    public:
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        P3Caja();
};

#endif