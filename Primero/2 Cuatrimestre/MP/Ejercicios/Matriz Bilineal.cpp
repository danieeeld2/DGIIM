/*Ejercicio 2 Examen Metodología de la Programación 
Septiembre de 2011*/
#include <iostream>
using namespace std;

class MatrizBS{
    private:
        int orden;  //  Orden de la matriz
        int resto;  //  Valor de los elementos de fuera de la diagonal
        int *diagonal;  //  Vector dinámico que almacena los valores de las diagonales
                        //  Como almacena dos diagonales tiene el doble de dimensión que orden
        void copy(const MatrizBS& orig){
            if(diagonal != nullptr){
                delete[] diagonal;
            }
            orden = orig.orden;
            resto = orig.resto;
            diagonal = new int[2*orden];
            for(int i = 0; i < 2*orden; i++){
                diagonal[i] = orig.diagonal[i];
            }
        }
    public:
        MatrizBS(){
            orden = 4;
            resto = 0;
            diagonal = new int[8];
            for(int i = 0; i < 8; i++){
                diagonal[i] = 1;
            }
        }
        MatrizBS(int n, int a,int* b){
            orden = n;
            resto = a;
            for(int i = 0; i < 2*n; i++){
                diagonal[i] = b[i];
            }
        }
        MatrizBS& operator=(const MatrizBS& orig){
            if(this != &orig){
                copy(orig);
            }
            return *this;
        }
};
