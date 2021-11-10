/**
 * @file p2_gasolinera.cpp
 * @author Daniel Alconchel Vázquez
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "scd.h"

using namespace std;
using namespace scd;

const int
    num_coches_gasolina=6,
    num_coches_gasoil=4,
    num_coches=num_coches_gasoil+num_coches_gasolina;
    
class Gasolinera : public HoareMonitor{
    private:
        const int 
            surtidores_gasolina=3,
            surtidores_gasoil=4;
        int 
            surtidores_gasolina_libres,
            surtidores_gasoil_libres;
        CondVar
            espera_gasoil,
            espera_gasolina;
    public:
        Gasolinera();
        void entra_coche_gasoil(int i);
        void sale_coche_gasoil(int i);
        void entra_coche_gasolina(int i);
        void sale_coche_gasolina(int i);
};

//----------------------------------------------------------------

Gasolinera::Gasolinera()
{
    surtidores_gasoil_libres = surtidores_gasoil;
    surtidores_gasolina_libres = surtidores_gasolina;
    espera_gasoil = newCondVar();
    espera_gasolina = newCondVar();
}

//----------------------------------------------------------------

void Gasolinera::entra_coche_gasoil(int i)
{
    if(surtidores_gasoil_libres == 0)
        espera_gasoil.wait();
    surtidores_gasoil_libres--;
    assert(surtidores_gasoil_libres>=0);
    cout    << "Coche gasoil " << i << " entra a repostar. Quedan " << surtidores_gasoil_libres
            << " surtidores de gasoil libres" << endl;
}

//----------------------------------------------------------------

void Gasolinera::sale_coche_gasoil(int i)
{
    surtidores_gasoil_libres++;
    assert(surtidores_gasoil_libres<=surtidores_gasoil);
    cout    << "Coche gasoil " << i << " sale de repostar. Quedan " << surtidores_gasoil_libres
            << " surtidores de gasoil libres" << endl;
    espera_gasoil.signal();
}

//----------------------------------------------------------------

void Gasolinera::entra_coche_gasolina(int i)
{
    if(surtidores_gasolina_libres == 0)
        espera_gasolina.wait();
    surtidores_gasolina_libres--;
    assert(surtidores_gasolina_libres>=0);
    cout    << "Coche gasolina " << i << " entra a repostar. Quedan " << surtidores_gasolina_libres
            << " surtidores de gasolina libres" << endl;
}

//----------------------------------------------------------------

void Gasolinera::sale_coche_gasolina(int i)
{
    surtidores_gasolina_libres++;
    assert(surtidores_gasolina_libres<=surtidores_gasolina);
    cout    << "Coche gasolina " << i << " sale de repostar. Quedan " << surtidores_gasolina_libres
            << " surtidores de gasolina libres" << endl;
    espera_gasolina.signal();
}

//----------------------------------------------------------------

void espera_gasolina_dentro(int i)
{
    chrono::milliseconds duration(aleatorio<100,300>());
    cout << "Coche gasolina " << i << " repostando(" << duration.count() << " ms)" << endl;
    this_thread::sleep_for(duration);
    cout << "Coche gasolina " << i << " termina de repostar" <<endl;
}

//----------------------------------------------------------------

void esperar_fuera_gasolina(int i)
{
    chrono::milliseconds duration(aleatorio<100,300>());
    cout << "Coche gasolina " << i << " esperando fuera (" << duration.count() << " ms)" << endl;
    this_thread::sleep_for(duration);
    cout << "Coche gasolina " << i << " termina de esperar";
}

//----------------------------------------------------------------

void funcion_hebra_gasolina(int i, MRef<Gasolinera> monitor)
{
    while(true)
    {
        monitor->entra_coche_gasolina(i);
        espera_gasolina_dentro(i);
        monitor->sale_coche_gasolina(i);
        esperar_fuera_gasolina(i);
    }
}

//----------------------------------------------------------------

void espera_gasoil_dentro(int i)
{
    chrono::milliseconds duration(aleatorio<100,300>());
    cout << "Coche gasoil " << i << " repostando(" << duration.count() << " ms)" << endl;
    this_thread::sleep_for(duration);
    cout << "Coche gasoil " << i << " termina de repostar" <<endl;
}

//----------------------------------------------------------------

void esperar_fuera_gasoil(int i)
{
    chrono::milliseconds duration(aleatorio<100,300>());
    cout << "Coche gasoil " << i << " esperando fuera (" << duration.count() << " ms)" << endl;
    this_thread::sleep_for(duration);
    cout << "Coche gasoil " << i << " termina de esperar";
}

//----------------------------------------------------------------

void funcion_hebra_gasoil(int i, MRef<Gasolinera> monitor)
{
    while(true)
    {
        monitor->entra_coche_gasoil(i);
        espera_gasoil_dentro(i);
        monitor->sale_coche_gasoil(i);
        esperar_fuera_gasoil(i);
    }
}

//----------------------------------------------------------------

int main(){
    MRef<Gasolinera> monitor = Create<Gasolinera>();
    thread 
        coches_gasolina[num_coches_gasolina],
        coches_gasoil[num_coches_gasoil];
    for(int i=0; i<num_coches_gasolina; i++)
        coches_gasolina[i] = thread(funcion_hebra_gasolina,i,monitor);
    for(int i=0; i<num_coches_gasoil; i++)
        coches_gasoil[i] = thread(funcion_hebra_gasoil,i,monitor);
    for(int i=0; i<num_coches_gasolina; i++)
        coches_gasolina[i].join();
    for(int i=0; i<num_coches_gasoil; i++)
        coches_gasoil[i].join();
    
}