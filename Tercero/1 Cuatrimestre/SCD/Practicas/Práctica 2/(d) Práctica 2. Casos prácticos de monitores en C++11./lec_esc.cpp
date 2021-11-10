/**
 * @file lec_esc.cpp
 * @author Daniel Alconchel Vázquez
 */

#include <iostream>
#include <thread>
#include <mutex>
#include "scd.h"

using namespace std;
using namespace scd;

mutex salida;

const int 
    numero_lectores = 4,
    numero_escritores = 3;

//------------------------------------------------------------

class Lec_Esc : public HoareMonitor
{
    private:
        bool escrib;        // true si un escritor está escribiendo, false en caso contrario
        int n_lec;          // número de lectores escribiendo en un momento dado
        CondVar
            lectura,        // variable condición usada por los lectores
            escritura;      // variable condición usada por escritores
    public:
        Lec_Esc();          // constructor
        void ini_lectura();
        void fin_lectura();
        void ini_escritura();
        void fin_escritura();
};

//------------------------------------------------------------

Lec_Esc::Lec_Esc()
{
    n_lec = 0;
    escrib = false;
    lectura = newCondVar();
    escritura = newCondVar();
}

//------------------------------------------------------------

void Lec_Esc::ini_lectura()
{
    if(escrib)              // Si hay un escritor
        lectura.wait();     // lectura tiene que esperar
    
    n_lec++;                // En caso contrario, añadir nuevo lector
    lectura.signal();       // Desbloqueamos los lectores bloqueados
}

//------------------------------------------------------------

void Lec_Esc::fin_lectura()
{
    n_lec--;                // Registramos un lector menos
    if(n_lec == 0)          // Si no quedan lectores
        escritura.signal(); // desbloqueamos a los escritores
}

//------------------------------------------------------------

void Lec_Esc::ini_escritura()
{
    if(n_lec>0 || escrib)   // Si hay lectores o un escritor escribiendo
        escritura.wait();   // bloqueamos el resto de escritores
    
    escrib=true;            // En caso contrario, comienza a escribir escritor
}

//------------------------------------------------------------

void Lec_Esc::fin_escritura()
{
    escrib = false;         // Registramos que ya no hay escritores
    if(!lectura.empty())    // Si hay lectores esperando
        lectura.signal();   // despertamos a uno
    else
        escritura.signal(); // En otro caso, despertamos un escritor
}

//------------------------------------------------------------

void leer(int i)
{
    chrono::milliseconds duration(aleatorio<50,100>());
    salida.lock();
    cout << "Lector " << i << " leyendo (" << duration.count() << " ms)" << endl;
    salida.unlock();
    this_thread::sleep_for(duration);
}

//------------------------------------------------------------

void escribir(int i)
{
    chrono::milliseconds duration(aleatorio<50,100>());
    salida.lock();
    cout << "Escritor " << i << " escribiendo (" << duration.count() << " ms)" << endl;
    salida.unlock();
    this_thread::sleep_for(duration);
}

//------------------------------------------------------------

void espera_escritor(int i)
{
    chrono::milliseconds duration(aleatorio<50,100>());
    salida.lock();
    cout << "Escritor " << i << " descanso (" << duration.count() << " ms)" << endl;
    salida.unlock();
    this_thread::sleep_for(duration);
}


//------------------------------------------------------------

void esperar_lector(int i)
{
    chrono::milliseconds duration(aleatorio<50,100>());
    salida.lock();
    cout << "Lector " << i << " descanso (" << duration.count() << " ms)" << endl;
    salida.unlock();
    this_thread::sleep_for(duration);
}

//------------------------------------------------------------

void funcion_hebra_escritor(MRef<Lec_Esc> monitor, int i)
{
    while(true)
    {
        monitor->ini_escritura();
        escribir(i);
        monitor->fin_escritura();
        espera_escritor(i);
    }
}

//------------------------------------------------------------

void funcion_hebra_lector(MRef<Lec_Esc> monitor, int i)
{
    while(true)
    {
        monitor->ini_lectura();
        leer(i);
        monitor->fin_lectura();
        esperar_lector(i);
    }
}

//------------------------------------------------------------

int main(){
    MRef<Lec_Esc> monitor = Create<Lec_Esc>();
    thread
        escritores[numero_escritores],
        lectores[numero_lectores];
    
    for(int i=0; i<numero_lectores; i++)
        lectores[i] = thread(funcion_hebra_lector, monitor, i);
    for(int i=0; i<numero_escritores; i++)
        escritores[i] = thread(funcion_hebra_escritor, monitor, i);
    for(int i=0; i<numero_lectores;i++)
        lectores[i].join();
    for(int i=0; i<numero_escritores;i++)
        escritores[i].join();
}