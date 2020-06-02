/*Construir una función recursiva que calcula le dascomposición
factorial de un número entero y la guarde en un vector de enteros.
La cabecera debe ser void descomposicion (int n, int * factores, int& num_factores)*/

#include <iostream>
using namespace std;

void descomposicion(int n, int*factores, int& num_factores){
    static int i=2;

    if(n<i){
        num_factores++;
        factores[num_factores-1]=n;
    }else{
        if(n%i == 0){
            num_factores++;
            factores[num_factores-1] = i;
            descomposicion(n/i,factores,num_factores);
        }else{
            i++;
            descomposicion(n, factores, num_factores);
        }
    }


};

int main(){
    int n=2147483646;
    int factor[100];
    int num = 0;
    descomposicion(n,factor,num);
    cout << endl;
    for(int i = 0; i < num; i++)
        cout << factor[i] << ",";
}