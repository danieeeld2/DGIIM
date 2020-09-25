/* Resolver el problema anterior con dos bucles anidados no es eficiente. Se propone ahora
utilizar dos variables, posicion_lectura y posicion_escritura que nos vayan indicando,
en cada momento, la componente que se esta leyendo y el sitio donde tiene que
escribirse. Por ejemplo, supongamos que en un determinado momento la variable
posicion_lectura vale 6 y posicion_escritura, 3. Si la componente en la posicion
6 es una mayuscula, simplemente avanzaremos posicion_lectura. Por el contrario, si
fuese una minuscula, la colocaremos en la posicion 3 y avanzaremos una posicion ambas
variables. Implementad este algoritmo. */

#include<iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de un vector */
    const int LONGITUD_MAXIMA = 10;
    char vector[LONGITUD_MAXIMA];
    
    int componentes_utiles;
    
    cout << "Introducir numero de componentes del vector: ";
    cin >> componentes_utiles;
    
    cout << "Introducir vector: ";
    for (int i = 0 ; i < componentes_utiles ; i++)
        cin >> vector[i];
    // Para espacios en blanco vector[i] = cin.get();
	
    int posicion_escritura = 0;
    
    for (int posicion_lectura = 0; posicion_lectura < componentes_utiles; posicion_lectura++)
        if ( vector[posicion_lectura] < 'A' || vector[posicion_lectura] > 'Z'){
            vector[posicion_escritura] = vector[posicion_lectura];
            posicion_escritura++;
        }
	
    componentes_utiles = posicion_escritura;
    
    cout << "\nEl vector queda: ";
    for (int i = 0; i < componentes_utiles; i++)
        cout << vector[i] << " ";
    cout << "\n";
}
