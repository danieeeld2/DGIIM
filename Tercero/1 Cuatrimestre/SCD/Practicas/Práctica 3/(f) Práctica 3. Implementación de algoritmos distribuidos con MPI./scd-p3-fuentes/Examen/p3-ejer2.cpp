// -----------------------------------------------------------------------------
// Daniel Alconchel Vázquez
// 49617109
// Filósofos (Con Camarero)
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
    num_filosofos = 8,                // número de filósofos
    num_filo_ten = 2 * num_filosofos, // número de filósofos y tenedores
    num_procesos = num_filo_ten + 2,  // número de procesos total (filosofos+tenedor+2*camarero)
    etiq_sentarse = 0,
    etiq_levantarse = 1,
    etiq_propina = 2,
    id_camarero_0 = num_procesos - 2,
    id_camarero_1 = num_procesos - 1;

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

// ---------------------------------------------------------------------

void funcion_filosofos(int id)
{
   int id_ten_izq = (id + 1) % num_filo_ten,                //id. tenedor izq.
       id_ten_der = (id + num_filo_ten - 1) % num_filo_ten; //id. tenedor der.
   int valor = 0;
   int id_valido;

   while (true)
   {
      int camarero = aleatorio<0,1>();
      if(camarero == 0)
         id_valido = id_camarero_0;
      else
         id_valido = id_camarero_1;
      int mesa;
      if(camarero == 0)
         mesa = 0;
      else
         mesa = 1;
      cout << "Filosofo " << id << " quiere sentarse en la mesa " << mesa << endl;
      MPI_Ssend(&valor, 1, MPI_INT, id_valido, etiq_sentarse, MPI_COMM_WORLD);
      cout << "Filosofo " << id << " se sienta en la mesa " << mesa << endl;

      cout << "Filósofo " << id << " solicita ten. izq." << id_ten_izq << endl;
      // ... solicitar tenedor izquierdo (completar)
      MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq, 0, MPI_COMM_WORLD);
      cout << "Filósofo " << id << " solicita ten. der." << id_ten_der << endl;
      // ... solicitar tenedor derecho (completar)
      MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, 0, MPI_COMM_WORLD);

      cout << "Filósofo " << id << " comienza a comer" << endl;
      sleep_for(milliseconds(aleatorio<10, 100>()));

      cout << "Filósofo " << id << " suelta ten. izq. " << id_ten_izq << endl;
      // ... soltar el tenedor izquierdo (completar)
      MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq, 0, MPI_COMM_WORLD);
      cout << "Filósofo " << id << " suelta ten. der. " << id_ten_der << endl;
      // ... soltar el tenedor derecho (completar)
      MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, 0, MPI_COMM_WORLD);

      int propina = aleatorio<3,5>();
      MPI_Ssend(&valor, 1, MPI_INT, id_valido, etiq_levantarse, MPI_COMM_WORLD);
      cout << "Filosofo " << id << " se levanta de la mesa " << mesa << endl;
      MPI_Send(&propina,1,MPI_INT,id_valido,etiq_propina,MPI_COMM_WORLD);
      cout << "Filósofo " << id << " deja una propina de " << propina << " a camarero " << mesa << endl;

      cout << "Filosofo " << id << " comienza a pensar" << endl;
      sleep_for(milliseconds(aleatorio<10, 100>()));
   }
}
// ---------------------------------------------------------------------

void funcion_tenedores(int id)
{
   int valor, id_filosofo; // valor recibido, identificador del filósofo
   MPI_Status estado;      // metadatos de las dos recepciones

   while (true)
   {
      // ...... recibir petición de cualquier filósofo (completar)
      MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
      // ...... guardar en 'id_filosofo' el id. del emisor (completar)
      id_filosofo = estado.MPI_SOURCE;
      cout << "Ten. " << id << " ha sido cogido por filo. " << id_filosofo << endl;

      // ...... recibir liberación de filósofo 'id_filosofo' (completar)
      MPI_Recv(&valor, 1, MPI_INT, id_filosofo, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
      cout << "Ten. " << id << " ha sido liberado por filo. " << id_filosofo << endl;
   }
}

// ---------------------------------------------------------------------

void funcion_camarero(int id)
{
   int libres = (num_filosofos-1)/2;
   int valor,
       tag_valido;
   MPI_Status estado;
   int suma_propina = 0,
       num_propinas_Recibidas = 0;

   while (true)
   {
      if (libres == 0)
         tag_valido = etiq_levantarse; // Si están todos sentados, solo pueden levantarse
      else  
         tag_valido = MPI_ANY_TAG;  // En otro caso pueden sentarse, levantarse o dar propina

      MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_valido, MPI_COMM_WORLD, &estado);

      switch (estado.MPI_TAG)
      {
      case etiq_levantarse:
         libres++;
         break;
      
      case etiq_propina:
         num_propinas_Recibidas++;
         suma_propina += valor;
         cout << "El camarero " << id << " recibe una propina de " << valor << " del filósofo " << estado.MPI_SOURCE
              << ".Ha recibido en total " << num_propinas_Recibidas << " propinas" << endl;
         break;

      default: // Sentarse
         libres--;
         break;
      }
   }
}

// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
   int id_propio, num_procesos_actual;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actual);

   if (num_procesos == num_procesos_actual)
   {
      // ejecutar la función correspondiente a 'id_propio'
      if (id_propio == id_camarero_0)
         funcion_camarero(0);
      else if(id_propio == id_camarero_1)
         funcion_camarero(1);
      else if (id_propio % 2 == 0)     // si es par
         funcion_filosofos(id_propio); //   es un filósofo
      else                             // si es impar
         funcion_tenedores(id_propio); //   es un tenedor
   }
   else
   {
      if (id_propio == 0) // solo el primero escribe error, indep. del rol
      {
         cout << "el número de procesos esperados es:    " << num_procesos << endl
              << "el número de procesos en ejecución es: " << num_procesos_actual << endl
              << "(programa abortado)" << endl;
      }
   }

   MPI_Finalize();
   return 0;
}

// ---------------------------------------------------------------------
