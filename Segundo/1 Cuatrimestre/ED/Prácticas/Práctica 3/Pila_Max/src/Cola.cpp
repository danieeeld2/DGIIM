/**
  * @file cola.cpp
  * @brief Implementación del TDA Cola
  *
  */
#include <cassert>
#include "../include/Cola.h"
/* _________________________________________________________________________ */


template <class T>
Cola<T>::Cola(const Cola<T> & original){
    if (original.primera!=0){           //Si tiene elementos
        Celda *p = original.primera;      //Copiamos el puntero a la primera celda
        primera =
        ultima = new Celda(p->elemento,0); //Inicializamos la lista de nodos
        p = p->siguiente;                     //Avanzamos el puntero
        while (p!=0){                         //Mientras queden elementos
            ultima->siguiente = new Celda(p->elemento,0); //Copiamos el elemento
            ultima = ultima->siguiente;                   //Avanzamos los punteros
            p = p->siguiente;
        }
    }
    else
        primera = ultima = 0;            //Si no tiene elementos
    num_elem = original.num_elem;
}

/* _________________________________________________________________________ */

template <class T>
Cola<T>::~Cola(){
    Celda * aux;
    while (primera!=0){             //Mientras queden elementos
        aux = primera;                //Copiamos el puntero
        primera = primera->siguiente; //Avanzamos primera
        delete aux;                   //Borramos el nodo
    }
}

/* _________________________________________________________________________ */

template <class T>
Cola<T>& Cola<T>::operator=(const Cola<T> & otra){
    Celda * p;

    if (this != &otra){    //Comprobación de rigor. Si son diferentes objetos
        while (primera!=0){  //Borramos la lista de nodos de la cola *this
            p = primera;
            primera = primera->siguiente;
            delete p;
        }
        if (otra.primera!=0){        //Si la otra cola tiene elementos
            p = otra.primera;          //Copiamos el puntero al primer nodo
            primera=ultima= new Celda(p->elemento,0); //Reservamos el primer nodo
            p=p->siguiente;                           //Avanzamos el puntero
            while (p!=0){                             //Mientras queden elementos
                ultima->siguiente=new Celda(p->elemento,0); //Creamos un nuevo nodo
                ultima=ultima->siguiente;                   //Actualizamos ultima
                p=p->siguiente;                             //Avanzamos el puntero
            }
        }
        else primera=ultima=0;      //Si la otra cola está vacía
        num_elem=otra.num_elem;
    }
    return *this; //Devolvemos el objeto para permitir el encadenamiento (a=b=c)
}

/*_________________________________________________________________________ */

template <class T>
void Cola<T>::poner(const T & elem){
    Celda *aux = new Celda(elem,0);    //Creamos un nuevo nodo
    if (primera==0)                    //Si la lista está vacía,
        primera = ultima = aux;          //primera y ultima apuntan a ese nodo
    else{                      //Si la lista ya tenia nodos,
        ultima->siguiente = aux; //Actualizamos el puntero siguiente del ultimo nodo
        ultima = aux;            //Actualizamos ultima
    }
    num_elem++;                //Incrementamos el numero de elementos
}

/* _________________________________________________________________________ */

template <class T>
void Cola<T>::quitar(){
    assert(primera!=0);             //Si la cola está vacía, abortar
    Celda *aux = primera;           //Copiamos el puntero al primer nodo
    primera = primera->siguiente;   //Actualizamos primera
    delete aux;                     //Borramos el primer nodo
    if (primera == 0)               //Si no quedan nodos,
        ultima=0;                     //actualizamos ultima
    num_elem--;                     //Actualizamos el número de elementos
}