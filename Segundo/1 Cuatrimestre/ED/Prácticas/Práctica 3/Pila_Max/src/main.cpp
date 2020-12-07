#include <iostream>
#include "../include/Pila_max.h"

using namespace std;

int main(){
    Pila_max<int> pila;
    int i;
    for(i=10; i>=0; i--)
        pila.push(i);
    while (!pila.empty()){
        elemento<int> x = pila.tope();
        cout << x << endl;
        pila.pop();
    }
    return 0;
}