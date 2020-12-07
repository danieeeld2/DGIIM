/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file Cola_max.cpp
 */

#include "../include/Cola_max.h"

using namespace std;

template<class T>
Cola_max<T>::Cola_max() {
    maximo = NULL;
}

template<class T>
Cola_max<T>::~Cola_max<T>() {
    maximo = NULL;
    while(!cola.empty())
        cola.pop();
}

template<class T>
int Cola_max<T>::size() const {
    return cola.size();
}

template<class T>
bool Cola_max<T>::vacio() const {
    return cola.empty();
}

template<class T>
void Cola_max<T>::Eliminar() {
    // El frente de la cola es el tope de la pila
    cola.pop();
}

template<class T>
elemento<T> Cola_max<T>::Front() const {
    return cola.top();  // El frente de la cola es el tope de la pila
}

template<class T>
elemento<T> Cola_max<T>::Back() const {
    stack<elemento<T>> aux1, aux2;
    aux1 = cola;

    while(!aux1.empty()) {
        aux2.push(aux1.top());
        aux1.pop();
    }

    return aux2.top();
}

template<class T>
void Cola_max<T>::Insertar(const T &elemen) {
    stack<elemento<T>> aux;
    elemento<T> insertar;

    /* 	La insercción en la pila se hace también en el tope,
    	pero hemos considerado el tope de la pila como el
		frente de la cola, luego hay que invertir la pila para 
		hacer la insercción y que quede asi en el back y volverla a invertir
		para que esté correctamente ordenado */

    if(cola.empty())
        maximo = elemen;
    if(elemen > maximo)
        maximo = elemen;

    insertar.maximo = maximo;
    insertar.dato = elemen;

    while(!cola.empty()){
        aux.push(cola.top());
        cola.pop();
    }
    aux.push(insertar);

    while(!aux.empty()){
        cola.push(aux.top());
        aux.pop();
    }
}
