/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file Pila_max_Cola.h
 */

#ifndef PILA_MAX_PILA_MAX_COLA_H
#define PILA_MAX_PILA_MAX_COLA_H

#include <iostream>

#include "Cola.h"

/**
 * @brief Struct que representa cada posición de la pila
 * @tparam T tipo de dato
 */
template <class T>
struct elemento {
    T dato;    // Elemento a almacenar
    T maximo;  // Elemento máximo
};

/**
 * @brief T.D.A. Pila_max
 *
 * Implementado usando colas template
 * @tparam T tipo de dato
 */
template <class T>
class Pila_max {
   private:
    T maximo;                // Maximo de la pila
    Cola<elemento<T>> pila;  // Representación de la pila

   public:
    /**
     * @brief Constructor de la clase
     */
    Pila_max();

    /**
     * @brief Destructor de la clase
     */
    ~Pila_max();

    /**
     * @brief Comprueba si la pila está vacía
     * @return Devuelve true en caso afirmativo @else devuelve false
     */
    bool empty();

    /**
     * @return Devuelve tamaño de la pila
     */
    int size();

    /**
     * @brief Inserta un elemento
     * @warning Como es una pila, solo se puede insertar en el tope
     * @param T elemento a insertar
     */
    void push(const T &elem);

    /**
     * @brief Quita un elemento
     * @warning Como es una pila, solo puede quitar elementos del tope
     */
    void pop();

    /**
     * @brief Acceso al tope
     * @return Devuelve el elemento que hay en el tope
     */
    elemento<T> tope() const;

    /**
     * @return Devuelve el máximo de la pila
     */
    T max() const;

    /**
     * @brief Sobrecarga operador =
     * @param p instancia pila_max
     * @return instancia pila_max
     */
    Pila_max<T> &operator=(const Pila_max<T> &p);
};

/**
 * @brief Método para la lectura de un dato tipo elemento @see elemento
 * @tparam T tipo de dato del struct
 * @param os flujo de lectura
 * @param elem elemento a leer
 * @return Lectura
 */
template <class T>
std::ostream &operator<<(std::ostream &os, const elemento<T> &elem) {
    os << "Elemento: " << elem.dato << " "
       << "Máximo: " << elem.maximo;
    return os;
};

#include "../src/Pila_max_Cola.cpp"

#endif  // PILA_MAX_PILA_MAX_COLA_H
