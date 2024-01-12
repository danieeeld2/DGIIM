#include "latapeones.h"

using namespace std;
using namespace glm;

Peon::Peon(int nperfiles) {
    pm_tras = leerPtrMatriz(agregar(translate(vec3(0.0))));
    agregar(new MallaRevolPLY("peon.ply", nperfiles));
}

bool Peon::cuandoClick(const glm::vec3 & centro_oc) {
    *pm_tras = translate(vec3(0.0, 0.0, 1.0));
    return true;
}

Lata::Lata(const std::string & nombre_arch) {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identTapa = 0;
    unsigned identBase = 1;
    unsigned identCara = 2;

    Textura* cocacola = new Textura(nombre_arch);
    Material* materialLata = new Material(cocacola, 0.75, 0.65, 0.25, 50.0);
    Material* materialBases = new Material(0.35, 0.45, 0.25, 50.0);

    NodoGrafoEscena* base = new NodoGrafoEscena();
    NodoGrafoEscena* cara = new NodoGrafoEscena();
    NodoGrafoEscena* tapa = new NodoGrafoEscena();

    base->agregar(materialBases);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 32));
    tapa->agregar(materialBases);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 32));

    cara->agregar(materialLata);
    cara->agregar(new MallaRevolPLY("lata-pcue.ply", 32));

    actual->agregar(base);
    actual->agregar(cara);
    actual->agregar(tapa);

    agregar(actual);
}

LataPeones::LataPeones() {
    NodoGrafoEscena* actual = new NodoGrafoEscena();

    unsigned identPeonMadera = 1;
    unsigned identPeonBlanco = 2;
    unsigned identPeonNegro = 3;
    unsigned identLata = 4;

    TexturaXY* texturaXY_madera = new TexturaXY("text-madera.jpg");
    Material* materialPeonMadera = new Material(texturaXY_madera, 0.5, 0.6, 0.5, 50.0);
    Material* materialPeonBlanco = new Material(0.5, 0.2, 0.5, 5.0);
    Material* materialPeonNegro = new Material(0.01, 0.2, 0.5, 50.0);

    NodoGrafoEscena* peones = new NodoGrafoEscena();
    peones->agregar(translate(vec3(0.0, 0.4, 0.7)));
    peones->agregar(scale(vec3(0.25, 0.25, 0.25)));
    

    Peon* peonMadera = new Peon(32);
    Peon* peonNegro = new Peon(32);
    Peon* peonBlanco = new Peon(32);

    Lata* lata = new Lata("lata-coke.jpg");
    lata->ponerNombre("Lata de Coca-Cola");
    lata->ponerIdentificador(identLata);

    peonMadera->ponerNombre("Peón de madera");
    peonMadera->ponerIdentificador(identPeonMadera);
    peones->agregar(materialPeonMadera);
    peones->agregar(peonMadera);

    peonNegro->ponerNombre("Peón Negro");
    peonNegro->ponerIdentificador(identPeonNegro);
    peones->agregar(translate(vec3(2.5, 0.0, 0.0)));
    peones->agregar(materialPeonNegro);
    peones->agregar(peonNegro);

    peonBlanco->ponerNombre("Peón blanco");
    peonBlanco->ponerIdentificador(identPeonBlanco);
    peones->agregar(translate(vec3(2.5, 0.0, 0.0)));
    peones->agregar(materialPeonBlanco);
    peones->agregar(peonBlanco);


    actual->agregar(peones);

    actual->agregar(lata);

    agregar(actual);
}

// PRACTICA 5

VariasLatasPeones::VariasLatasPeones() {
    unsigned identPepsi = 5;
    unsigned identUGR = 6;

    NodoGrafoEscena* lataPepsi = new NodoGrafoEscena();
    NodoGrafoEscena* lataUGR = new NodoGrafoEscena();

    lataPepsi->ponerNombre("Lata de Pepsi");
    lataPepsi->ponerIdentificador(identPepsi);
    lataPepsi->agregar(translate(vec3(1.0, 0.0, 0.0)));
    lataPepsi->agregar(new Lata("lata-pepsi.jpg"));

    lataUGR->ponerNombre("Lata de la UGR");
    lataUGR->ponerIdentificador(identUGR);
    lataUGR->agregar(translate(vec3(2.0, 0.0, 0.0)));
    lataUGR->agregar(new Lata("window-icon.jpg"));

    agregar(lataPepsi);
    agregar(lataUGR);
}