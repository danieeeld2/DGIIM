// -----------------------------------------------------------------------------
// Daniel Alconchel Vázquez
// Gasolinera con Paso de Mensajes
// -----------------------------------------------------------------------------

#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

const int
    num_coches = 10,
    num_surtidores = 5;
const int 
    etiq_entrar = 1,
    etiq_salir = 0;
const int
    ID_GASOLINERA = 0,
    num_procesos = num_coches+1;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

void funcion_coche(int id)
{
    int dato = 0;
    while(true)
    {
        cout << "Coche " << id << ": Quiere entrar a repostar" << endl;
        MPI_Ssend(&dato,1,MPI_INT,ID_GASOLINERA,etiq_entrar,MPI_COMM_WORLD);
        cout << "Coche " << id << ": reposta" << endl;
        this_thread::sleep_for(milliseconds(aleatorio<50,100>()));
        cout << "Coche " << id << ": Sale de repostar" << endl;
        MPI_Ssend(&dato,1,MPI_INT,ID_GASOLINERA,etiq_salir,MPI_COMM_WORLD);
    }
}

void funcion_gasolinera()
{
    int
        dato = 0,
        etiq_valida = 0,
        libres = num_surtidores;
    MPI_Status
        estado;
    while(true)
    {
        etiq_valida = libres > 0 ? MPI_ANY_TAG : etiq_salir;
        MPI_Recv(&dato,1,MPI_INT,MPI_ANY_SOURCE,etiq_valida,MPI_COMM_WORLD,&estado);
        if(estado.MPI_TAG == etiq_entrar)
            libres--;
        else
            libres++;
    }
}

int main(int argc, char **argv)
{
    int
        id,
        num_procesos_actuales;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actuales);

    if(num_procesos == num_procesos_actuales)
    {
        if(id == ID_GASOLINERA)
            funcion_gasolinera();
        else
            funcion_coche(id);
    }else{
        if(id == 0)
        {
            cerr << endl
                 << "El número de procesos esperado es: " << num_procesos << endl
                 << "El número de procesos en ejecución es: " << num_procesos_actuales << endl
                 << "(programa abortado)" << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
