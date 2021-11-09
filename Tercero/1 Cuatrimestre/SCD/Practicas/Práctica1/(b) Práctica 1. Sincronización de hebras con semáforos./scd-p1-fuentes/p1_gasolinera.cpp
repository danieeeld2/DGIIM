/**
 * @file p1_gasolinera.cpp
 * @author Daniel Alconchel Vázquez
 * @brief Gasolinera
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std;
using namespace scd;
using namespace chrono;

// Semáforos
Semaphore
    surtidores_gasolina(3),     // Semáforo que controla los surtidores de gasolina. Se inicializa a 3 porque
                                // al principio están los tres libres
    surtidores_gasoil(2);       // Semáforo que controla los surtidores de gasoil. Se inicializa a 2 porque 
                                // al principio están los dos libres
// Tipos de coche
enum coche
{
    GASOLINA,
    GASOIL,
};

// Cerrojo auxiliar para la salida
mutex salida;

//-------------------------------------------------------------------------------

void repostar(int numero_coche, coche tipo)
{
    // Calcula milisegundos aleatorios de la acción de repostar
    milliseconds duration(aleatorio<10,300>());
    salida.lock();
    cout << "Coche " << numero_coche << " " << (tipo == coche::GASOLINA ? "gasolina: " : "gasoil: ") << "empieza a repostar " << duration.count() << "ms" << endl;
    salida.unlock();

    // Hacemos que la hebra espera el tiempo equivalente a la duracion de la acción repostar
    this_thread::sleep_for(duration);

    salida.lock();
    cout << "Coche " << numero_coche << " " << (tipo == coche::GASOLINA ? "gasolina: " : "gasoil: ") << "termina de repostar" << endl;
    salida.unlock();
}

//-------------------------------------------------------------------------------

void esperar(int numero_coche, coche tipo)
{
    // Calcula milisegundos aleatorios de la acción de esperar
    milliseconds duration(aleatorio<10,300>());
    salida.lock();
    cout << "Coche " << numero_coche << " " << (tipo == coche::GASOLINA ? "gasolina: " : "gasoil: ") << "espera fuera " << duration.count() << "ms" << endl;
    salida.unlock();

    // Hacemos que la hebra espera el tiempo equivalente a la duracion de la acción esperar
    this_thread::sleep_for(duration);

    salida.lock();
    cout << "Coche " << numero_coche << " " << (tipo == coche::GASOLINA ? "gasolina: " : "gasoil: ") << " termina de esperar" << endl;
    salida.unlock();
}

//-------------------------------------------------------------------------------

void funcion_hebra_gasolina(int num)
{
    while(true){
        sem_wait(surtidores_gasolina);
        repostar(num,coche::GASOLINA);
        sem_signal(surtidores_gasolina);
        esperar(num,coche::GASOLINA);
    }
}

//-------------------------------------------------------------------------------

void funcion_hebra_gasoil(int num)
{
    while(true){
        sem_wait(surtidores_gasoil);
        repostar(num,coche::GASOIL);
        sem_signal(surtidores_gasoil);
        esperar(num,coche::GASOIL);
    }
}

//-------------------------------------------------------------------------------

int main()
{
    thread coches[10];
    // Coches gasolina
    for(int i=0; i<10;i++)
        coches[i] = i<6 ? thread(funcion_hebra_gasolina,i) : thread(funcion_hebra_gasoil, i);
    for(int i=0; i<10; i++)
        coches[i].join();

    return 0;
}