/*Ejercicio 1 Examen Metodología de la Programación II
16 de Septiembre de 2008*/
#include <iostream>
using namespace std;

struct Coche{
    char* Matricula;
    char* Marca;
    char* Modelo;
    float Km;
    int Precio;
    char* observaciones;
};

class ColeccionCoches{
    private:
        int NumCoches;
        Coche* Coches;

        void copy(const ColeccionCoches& orig){
            if(Coches != nullptr){
                delete[] Coches;
            }
            NumCoches = orig.NumCoches;
            Coches->Km = orig.Coches->Km;
            Coches->Marca = orig.Coches->Marca;
            Coches->Matricula = orig.Coches->Matricula;
            Coches->Modelo = orig.Coches->Modelo;
            Coches->observaciones = orig.Coches->observaciones;
            Coches->Precio = orig.Coches->Precio;
        }
    public:
        ColeccionCoches(){
            NumCoches = 0;
            Coches = nullptr;
        }

        ~ColeccionCoches(){
            if(Coches!= nullptr){
                delete[] Coches;
            }
            Coches = nullptr;
        }

        ColeccionCoches(const ColeccionCoches& orig){
            NumCoches = 0;
            Coches = nullptr;
            copy(orig);
        }

        ColeccionCoches operator=(const ColeccionCoches& orig){
            if(this!=orig){
                copy(orig);
            }
            return *this;
        }
};

