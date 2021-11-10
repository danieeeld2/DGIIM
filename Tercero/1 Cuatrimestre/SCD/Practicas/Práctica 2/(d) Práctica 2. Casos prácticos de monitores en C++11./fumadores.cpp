/**
 * @file fumadores.cpp
 * @author Daniel Alconchel Vázquez * 
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "scd.h"

using namespace std;
using namespace scd;

const int num_fumadores = 3;

// Creación del monitor
class Estanco : public HoareMonitor
{
    private:
        CondVar
            cola_fumar[num_fumadores],      // Cola de los fumadores
            cola_estanquero;                // Cola estanquero
        int ingrediente;                    // Valor del ingrediente
        const int sin_ingredientes = -1;    // Valor auxiliar que controla si hay o no ingredientes
    public:
        Estanco();                          // Constructor
        void obtenerIngrediente(int i);     // Obtener ingrediente del fumador i
        void ponerIngrediente(int i);       // Colocar ingrediente del fumador i
        void esperarRecogidaIngrediente();  // Simula el retardo de recoger el ingrediente
};

//----------------------------------------------------------------------

Estanco::Estanco()
{
    cola_estanquero = newCondVar();
    ingrediente = sin_ingredientes;
    for(int i=0; i<num_fumadores; i++)
        cola_fumar[i] = newCondVar();
}

//----------------------------------------------------------------------

void Estanco::ponerIngrediente(int i)
{
    ingrediente = i;
    cout << "Estanquero: Coloca ingrediente " << i << endl;
    cola_fumar[i].signal();     // Llama al fumador i
}

//----------------------------------------------------------------------

void Estanco::obtenerIngrediente(int i)
{
    if(ingrediente!=i){
        cola_fumar[i].wait();   // Si no es el ingrediente de dicho fumador, se bloquea
    }
    cout << "Fumador " << i << ": Coge ingrediente " << i << endl;
    ingrediente = sin_ingredientes;
    cola_estanquero.signal();   // Desbloquea al estanquero
}

//----------------------------------------------------------------------

void Estanco::esperarRecogidaIngrediente()
{
    cout << "Estanquero: Espera recogida de ingrediente" << endl;
    if(ingrediente != sin_ingredientes)
        cola_estanquero.wait(); // Bloquea estnquero hasta que recojan ingrediente
}

//----------------------------------------------------------------------

int ProducirIngrediente()
{
    chrono::milliseconds duration(aleatorio<10,100>());
    this_thread::sleep_for(duration);
    const int num_ingrediente = aleatorio<0,num_fumadores-1>();
    cout << "Estanquero: Produciendo ingrediente " << num_ingrediente <<" (" << duration.count() << " ms)" << endl;
    return num_ingrediente;
}

//----------------------------------------------------------------------

void fumar(int i)
{
    chrono::milliseconds duration(aleatorio<200,300>());
    cout << "Fumador " << i << ": Empieza a fuma (" << duration.count() << " ms)" << endl;
    this_thread::sleep_for(duration);
    cout << "Fumador " << i << ": Termina de fumar" << endl;
}

//----------------------------------------------------------------------

void funcion_hebra_estanquero(MRef<Estanco> monitor)
{
    while(true){
        int ingrediente = ProducirIngrediente();
        monitor->ponerIngrediente(ingrediente);
        monitor->esperarRecogidaIngrediente();
    }
}

//----------------------------------------------------------------------

void funcion_hebra_fumador(MRef<Estanco> monitor, int i)
{
    while(true){
        monitor->obtenerIngrediente(i);
        fumar(i);
    }
}

//----------------------------------------------------------------------

int main(){
    thread  hebra_fumadores[num_fumadores],
            hebra_estanquero;
    MRef<Estanco> monitor = Create<Estanco>();

    hebra_estanquero = thread(funcion_hebra_estanquero,monitor);
    for(int i=0; i<num_fumadores; i++)
        hebra_fumadores[i] = thread(funcion_hebra_fumador, monitor, i);
    hebra_estanquero.join();
    return 0;
}