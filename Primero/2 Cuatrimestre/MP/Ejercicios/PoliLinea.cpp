/*Ejercicio 1 Examen Metodología de la Programación II
24 de Junio de 2005*/
#include <iostream>
#include <fstream>
using namespace std;
class Punto{
    private:
        int x,y;    //  Coordenadas de un punto 2D
    public:
        Punto(){
            x = 0;
            y = 0;
        }
        Punto(int a,int b){
            x = a;
            y = b;
        }
        int Getx(){
            return x;
        }
        int Gety(){
            return y;
        }

};

class PoliLinea{
    private:
        Punto *p;   //  Vectores de puntos
        int num;    //  Número de puntos
    public:
        PoliLinea(){
            p = nullptr;
            num = 0;
        }

        PoliLinea(const PoliLinea& orig){
            p = nullptr;
            num = 0;
            copy(orig);
        }

        void copy(const PoliLinea&  orig){
            Punto* aux;
            aux = new Punto[orig.num];
            for(int i = 0; i < orig.num; i++){
                aux[i] = orig.p[i];
            }
            if(p != nullptr){
                delete[] p;
            }
            num = orig.num;
            p = new Punto[num];
            p = aux;
        }

        PoliLinea& operator=(const PoliLinea& orig){
            if(this != &orig){
                copy(orig);
            }
            return *this;
        }

        void add(const Punto& pt){
            Punto* aux = nullptr;
            aux = new Punto[num];
            for(int i = 0; i < num; i++){
                aux[i] = p[i];
            }
            if(p != nullptr){
                delete[] p;
            }
            p = new Punto[num+1];
            for(int i = 0; i < num; i++){
                p[i] = aux[i];
            }
            p[num] = pt;
            num++;
            if(aux != nullptr){
                delete[] aux;
            }
            aux = nullptr;
        }

        PoliLinea& operator+(const Punto& pt){
            add(pt);
            return *this;
        }

        void print(ostream& os){
            os << num << endl;
            for(int i = 0; i < num; i++){
                os << p[i].Getx() << ", " << p[i].Gety() << endl;;
            }
            os << endl;
        }
};
int main(){
    PoliLinea A;
    PoliLinea B;
    Punto C(2,3);
    A + C;
    A.print(cout);
    B = A;
    B.print(cout);
    return 0 ;
}