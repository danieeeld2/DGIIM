/*Ejercicio 3 Examen Metodología de la Proogramación II
Septiembre de 2006*/
#include <iostream>
using namespace std;

class Menu{
    private:
        char *titulo;   //  Encabezado que le damos al menú(O si no existe)
        char **opc;     //  Cadenas que describen cada una de las opciones
        int nopc;       //  Número de opciones actualmente en el menú
        void copy(const Menu& orig){
            char *aux1 = nullptr;
            char **aux2 = nullptr;
            aux1 = new char[orig.nopc];
            for(int i = 0; i < orig.nopc; i++){
                auxi[1] = orig.titulo[i];
            }
            aux2 = new char*[orig.nopc];
            for(int i = 0; i < orig.nopc; i++){
                aux2[i] = new char[orig.nopc];
            }
            for(int i = 0; i < orig.nopc; i++){
                for(int j = 0; j < orig.nopc; j++){
                    aux2[i][j] = orig.opc[i][j];
                }
            }
            deallocate();
            allocate(orig.nopc);
            nopc = orig.nopc;
            opc = aux2;
            titulo = aux1;
            
        }
        void deallocate(){
            if(titulo != nullptr){
                delete[] titulo;
            }
            titulo = nullptr;
            if(opc != nullptr){
                for(int i = 0; i < nopc; i++){
                    delete [] opc[i];
                }
                delete[] opc;
            }
            opc = nullptr;
            nopc = 0;
        }
        void allocate(int a){
            nopc = a;
            titulo = new char[a];
            opc = new char*[a];
            for(int i = 0; i < a; i++){
                opc[i] = new char[a];
            }
        }
    public:
        Menu(){
            titulo = 'O';
            opc = nullptr;
            nopc = 0;
        }
        Menu(const Menu& orig){
            titulo = 'O';
            opc = nullptr;
            nopc = 0;
            copy(orig);
        }
        ~Menu(){
            deallocate();
        }
        Menu& operator=(const Menu& orig){
            if(orig != &this){
                copy(orig);
            }
            return *this;
        }
        void SetTitulo(char* a){
            if(titulo != nullptr){
                delete[] titulo;
            }
        
        }

}