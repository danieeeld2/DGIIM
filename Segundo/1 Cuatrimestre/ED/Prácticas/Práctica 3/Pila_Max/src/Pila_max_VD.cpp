/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 */

#include "../include/Pila_max_VD.h"

using namespace std;

template<class T>
Pila_max<T>::Pila_max() {
    pila.clear();
    maximo = NULL;
}

template<class T>
Pila_max<T>::~Pila_max() {
    pila.clear();
    maximo = NULL;
}

template<class T>
bool Pila_max<T>::empty() {
    if (pila.size()==0)
        return true;
    else
        return false;
}

template<class T>
int Pila_max<T>::size() {
    return pila.size();
}

template<class T>
void Pila_max<T>::pop() {
    // Recordemos que solo se puede eliminar el elemento del tope
    pila.pop_back();
}

template<class T>
elemento<T> Pila_max<T>::tope() const{
    return pila[pila.size()-1];
}

template<class T>
T Pila_max<T>::max() const {
    return maximo;
}

template<class T>
void Pila_max<T>::push(const T &elem) {
    // Recordemos que solo se puede insertar en el tope
    elemento<T> insertar;
    if(pila.empty())
        maximo = elem;
    if(elem > maximo)
        maximo = elem;

    insertar.maximo = maximo;
    insertar.dato = elem;

    pila.push_back(insertar);
}