/* Para obtener una lista de todos los numeros primos menores que un determinado numero n,
se puede utilizar la Criba de Eratostenes. Ese metodo consiste en hacer una lista de todos
los numeros desde 2 hasta n-1. Tomamos el 2 y tachamos todos los multiplos de 2. Luego
tomamos el siguiente numero que se encuentra despues de 2 y que este sin tachar, tachando
de nuevo todos sus multiplos. Repetimos este paso hasta que se acaben los numeros. Los
numeros que quedaron sin tachar son los que no tienen divisores (salvo el 1 y el mismo),
o sea, los primos. Escribir un programa que obtenga los numeros primos menores que un
determinado numero n utilizando el metodo anterior.*/

#include<iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de un vector */
    const int LONGITUD_MAXIMA = 51;
    bool candidatos[LONGITUD_MAXIMA];
    int numero;
    
    candidatos[0] = candidatos[1] = false;
    for (int i=2; i<LONGITUD_MAXIMA; i++)
        candidatos[i] = true;
    
    cout << "Introducir numero (maximo 50): ";
    cin >> numero;
    
	for (int i = 2; i < numero; i++)
        for (int j=i+1; j < numero; j++)
            if ( j % i == 0)
                candidatos[j] = false;
    
    
	for (int i = 0; i < numero; i++)
        if (candidatos[i])
            cout << i << " ";
    cout << "\n";
}
