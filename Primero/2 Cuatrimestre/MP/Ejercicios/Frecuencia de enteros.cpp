/*Examen Metodología de la Programación
11 de Junio de 2015*/
#include <iostream>
using namespace std;

struct Pareja{
    int dato;
    int nveces;
};
class Frecuencias{
    private:
        Pareja * parejas;   //  "npares"datos de tipo "Pareja" ordenados por "dato". 0 si no hay parejas;
        int npares;
        void copy(const Frecuencias& orig){
            npares = orig.npares;
            if(parejas != nullptr){
                delete[] parejas;
            }
            parejas = new Pareja[npares];
            parejas = orig.parejas;
        }
    public:
        Frecuencias(){
            npares = 0;
            parejas = nullptr;
        }
        ~Frecuencias(){
            if(parejas != nullptr){
                delete[] parejas;
            }
            parejas = nullptr;
            npares = 0;
        }
        Frecuencias(const Frecuencias& orig){
            npares = 0;
            parejas = nullptr;
            copy(orig);
        }
        Frecuencias& operator=(const Frecuencias& orig){
            if(this !=& orig){
                copy(orig);
            }
            return *this;
        }
        void Add(int a){
            bool repetido = false;
            int pos = 0;
            Pareja *aux = nullptr;
            for(int i = 0; i < npares && (!repetido); i++){
                if(a == parejas[i].dato){
                    repetido = true;
                    pos = i;
                }
            }

            if(repetido){
                parejas[pos].nveces++;
            }else{
                aux = new Pareja[npares];
                for(int i = 0; i < npares; i++){
                    aux[i] = parejas[i];
                }
                if(parejas != nullptr){
                    delete[] parejas;
                }
                parejas = new Pareja[npares+1];
                for(int i = 0; i < npares; i++){
                    parejas[i] = aux[i];
                }
                parejas[npares].dato = a;
                parejas[npares].nveces = 1;
                if(aux != nullptr){
                    delete[] aux;
                }
                aux = nullptr;
                npares++;
            }
        }
        Frecuencias& operator+=(int a){
            Add(a);
            return *this;
        }
        
        void read(ostream& os){
            os << endl;
            for(int i = 0; i < npares; i++){
                os << parejas[i].dato << " " << parejas[i].nveces << endl;
            }
            os << endl;
        }
        ostream& operator<<(ostream& os){
            read(os);
            return os;
        }
};

int main(){
    Frecuencias A;
    A.Add(5);
    A.Add(5);
    A.Add(6);
    A.read(cout);
}