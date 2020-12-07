/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file Cola_max.h
 */

#ifndef PRACTICA_3_COLA_MAX_H
#define PRACTICA_3_COLA_MAX_H

#include <iostream>
#include <stack>

template<class T>
/**
* @brief Representación elementos de la pila
* @param T tipo de elemento
*/
struct elemento{
    T dato;
    T maximo;
};

template<class T>
/**
 * @brief TDA Cola Máximo
 * Representación de una cola, a través de la pila stack de la STL, de
 * una cola con máximo
 * @warning Se introducen los elementos por el "back" de la cola y se eliminan por el "front"
 */
class Cola_max {
private:
    std::stack<elemento<T>> cola; //  Representacón de la cola con máximo
    T maximo;   // Valor máximo de la cola

public:
    /**
     * @brief Constructor por defecto
     */
    Cola_max();

    /**
     * @brief Destructor de la clase
     */
    ~Cola_max();

    /**
     * @brief Inserta un elemento en la cola
     * @param T elemento a insertar
     * @warning Los elementos se insertan en el back
     */
    void Insertar(const T &elemen);

    /**
     * @brief Elimina un elemento de la cola
     * @warning Los elementos se eliminan en el front
     */
    void Eliminar();

    /**
     * @brief Consulta el front de la cola
     * @return Front de la cola
     */
    elemento<T> Front() const;

    /**
     * @brief Consulta el back de la cola
     * @return Back de la cola
     */
    elemento<T> Back() const;

    /**
     * @brief Comprueba si la cola está vacía
     * @return true en caso afirmativo y false en caso contrario
     */
    bool vacio() const;

    /**
     * @brief Devuelve el tamaño de la cola
     * @return Tamaño de la cola
     */
    int size() const;
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

#include "../src/Cola_max.cpp"

#endif
