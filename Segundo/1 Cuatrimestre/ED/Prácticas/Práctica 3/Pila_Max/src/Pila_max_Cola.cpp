/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file Pila_max_Cola.cpp
 */

#include "../include/Pila_max_Cola.h"

using namespace std;

template <class T>
Pila_max<T>::Pila_max() {}

template <class T>
Pila_max<T>::~Pila_max() {}

template <class T>
int Pila_max<T>::size() {
    return pila.num_elementos();
}

template <class T>
T Pila_max<T>::max() const {
    return maximo;
}

template <class T>
bool Pila_max<T>::empty() {
    if (pila.num_elementos() == 0)
        return true;
    else
        return false;
}

template <class T>
void Pila_max<T>::pop() {
    pila.quitar();  // El frente de la cola es el tope de la pila
}

template <class T>
elemento<T> Pila_max<T>::tope() const {
    return pila.frente();  // El frente de la cola es el tope de la pila
}

template <class T>
Pila_max<T> &Pila_max<T>::operator=(const Pila_max<T> &p) {
    pila = p.pila;
    maximo = p.maximo;
    return *this;
}

template <class T>
void Pila_max<T>::push(const T &elem) {
    elemento<T> insertar;

    if (pila.vacia()) maximo = elem;
    if (elem > maximo) maximo = elem;

    insertar.dato = elem;
    insertar.maximo = maximo;

    // Hay que añadir el elemento en el frente (que es el tope)
    // pero, la insercción se hace al final de la cola, por lo que:

    Cola<elemento<T>> aux;
    aux.poner(insertar);
    while (!pila.vacia()) {
        aux.poner(pila.frente());
        pila.quitar();
    }

    pila = aux;
}
