/**
* @author Daniel Alconchel Vázquez
 * @file Función 1
*/

#include <iostream>
#include <list>

using namespace std;

/**
 * @brief Función que predice la próxima jugada de una persona en el
 * juego de priedra, papel o tijera, teniendo en cuenta las elecciones que
 * hizo en jugadas anteriores
 * @param H lista de la STL, que almacena las jugadas anteriores
 * @warning El valor 1 representa "piedra", el valor 2 representa "papel"
 * y el valor 3, "tijeras"
 * @param n Número de rondas a tener en cuenta
 * @warning Se toma las últimas n rondas
 * @return El valor esperado  que juegue
 */
int ppt(list<int> &H, int n);

int main(){
    list<int> jugadas;
    int entrada = 0;
    int tam = 0;

    cout << "Introduce las jugadas anteriores" << endl;
    cout << "-1 para acabar de introducir" << endl;
    while (entrada!=-1){
        cin >> entrada;
        if(entrada!=-1)
            jugadas.push_back(entrada);
    }
    cout << "Introduce el tamaño de la subsecuencia " <<endl;
    cin >> tam;

    cout << endl << "La siguiente jugada es: " << ppt(jugadas,tam) << endl;

    return 0;
};

int ppt(list<int> &H, int n){
    list<int> secuencia, aux, aux1;
    bool encontrado;
    int contador, resultado, desplazamiento;

    for(int i=0; i<n; i++){
        secuencia.push_back(H.back());
        H.pop_back();
    }

    aux1 = H;
    aux = secuencia;
    contador = 0;
    desplazamiento = 0;
    while(!H.empty() && !encontrado){
        if(H.back() == secuencia.front()){
            contador++;
            secuencia.pop_front();
        } else{
            contador = 0;
            secuencia = aux;
        }
        
        desplazamiento++;
        H.pop_back();

        if(contador==n)
            encontrado = true;
        else if(H.empty()){ 
            cerr << "No se ha jugado esta secuencia previamemte" << endl;
            return 0;
        }
    }

    if(desplazamiento != n)
        for(int i=0; i<desplazamiento-n-1; i++)
            aux1.pop_back();
    else
        for(int i=0; i<desplazamiento-1; i++)
            aux1.pop_back();

    resultado = aux1.back();

    return resultado;
}