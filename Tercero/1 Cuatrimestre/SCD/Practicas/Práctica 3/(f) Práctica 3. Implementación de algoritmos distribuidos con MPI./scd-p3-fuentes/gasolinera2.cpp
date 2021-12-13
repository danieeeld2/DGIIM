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
    num_tipos_combustibles = 3,
    num_surtidores[num_tipos_combustibles] = {3,2,1};
const int 
    etiq_entrar[num_tipos_combustibles] = {1,2,3},
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
    const int tipo = aleatorio<0,num_tipos_combustibles-1>();
    while(true)
    {
        cout << "Coche " << id << " tipo " << tipo << ": quiere repostar" << endl;
        MPI_Ssend(&tipo,1,MPI_INT,ID_GASOLINERA,etiq_entrar[tipo],MPI_COMM_WORLD);
        cout << "Coche " << id << " tipo " << tipo << ": reposta" << endl;
        this_thread::sleep_for(milliseconds(aleatorio<50,100>()));
        MPI_Ssend(&tipo,1,MPI_INT,ID_GASOLINERA,etiq_salir,MPI_COMM_WORLD);
        cout << "Coche " << id << " tipo " << tipo << ": sale de reposta" << endl;
    }   
}

void funcion_gasolinera()
{
    int 
        dato = 0,
        etiq_valida = 0,
        esperando = 0,
        surtidores[num_tipos_combustibles];
    MPI_Status
        estado;
    
    for(int i=0; i<num_tipos_combustibles; i++)
        surtidores[i] = num_surtidores[i];
    
    while(true)
    {
        // Prioridad: Ver si alguien quiere salir
        MPI_Iprobe(MPI_ANY_SOURCE,etiq_salir,MPI_COMM_WORLD,&esperando,&estado);
        if(esperando)
        {
            // Si hay alguno esperando lo liberamos
            MPI_Recv(&dato,1,MPI_INT,MPI_ANY_SOURCE,etiq_salir,MPI_COMM_WORLD,&estado);
            surtidores[dato]++; // EN dato se almacena tipo enviado por proceso coche
        }

        // En otro caso vemos si alguien quiere entrar por cada tipo de combustible
        for(int i=0; i<num_tipos_combustibles; i++)
        {
            if(surtidores[i])
            {
                // Si hay surtidores disponibles, vemos si alguien quiere entrar
                MPI_Iprobe(MPI_ANY_SOURCE,etiq_entrar[i],MPI_COMM_WORLD,&esperando,&estado);
                if(esperando)
                {
                    // Hay al menos uno que quiere entrar
                    MPI_Recv(&dato,1,MPI_INT,MPI_ANY_SOURCE,etiq_entrar[i],MPI_COMM_WORLD,&estado);
                    surtidores[i]--;
                }
            }
        }
        this_thread::sleep_for(milliseconds(20));
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