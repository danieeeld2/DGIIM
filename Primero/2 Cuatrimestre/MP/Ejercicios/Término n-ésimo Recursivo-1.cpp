/*Ejercicio 5 Examen Metodología de la Programación II
15 de Septiembre de 2010*/
#include <iostream>
using namespace std;

class Solucion{
    private:
        double solucion;
    public:
        double RecursiveSolution(int termino){
            static double solution;
            if(termino == 0){
               return solution=1;
            }
            if(termino == 1){
                return solution = 1;
            }else{
                solution = RecursiveSolution(termino-1);
                solution = solution*(((2*((2*termino)-1))/(termino+1)));
                return solution;
            }
        }
        
        void Solution(int a){
            solucion = RecursiveSolution(a);
        }

        double GetSolution(){
            return solucion;
        }
};

int main(){
    Solucion A;
    A.Solution(6);
    cout << endl << A.GetSolution() << endl;
    return 0;
}