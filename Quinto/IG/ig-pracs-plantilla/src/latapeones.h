#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

class Lata : public NodoGrafoEscena {
    public:
        Lata(const std::string & nombre_arch);
};

class Peon : public NodoGrafoEscena {
    public:
        Peon(int nperfiles);
        bool cuandoClick(const glm::vec3 & centro_wc) override;

    protected:
        glm::mat4* pm_tras = nullptr;
};

class VariasLatasPeones : public LataPeones {
    public:
        VariasLatasPeones();
};

#endif