/**
* @author Daniel Alconchel Vázquez
* @file Diccionario.h
*/

#ifndef PRACTICA_4_DICCIONARIO_H
#define PRACTICA_4_DICCIONARIO_H

#include <list>
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

/**
 * @brief Tipo de elemento que define el diccionario
 * @tparam T tipo de dato asociado
 * @tparam U lista de datos asociados a la clave
 */
template<class T, class U>
struct data{
    T clave;
    list<U> info_asociada;
};

/**
 * @brief Comparador de datos. Ordena dos registros de acuerdo a la clave T
 * @tparam T tipo de dato asociado
 * @tparam U lista de datos asociados a la clave
 * @param d1 instancia del struct data
 * @param d2 instancia del struct data
 * @return el orden
 */
template <class T, class U>
bool operator<(const data<T,U> &d1,const data <T,U>&d2){
    if (d1.clave<d2.clave)
        return true;
    return false;
}

/**
 * @brief T.D.A. Diccionario
 *
 * Instancia de la clase diccionario,implementada a traves
 * del uso de listas de la STL
 * @tparam T tipo de dato asociado
 * @tparam U lista de datos asociados a la clave
 */
template<class T, class U>
class Diccionario{
private:
    list<data<T,U>> datos;  // Representación del diccionario

    /**
     * @brief Copia un diccionario
     * @param D instancia de la clase diccionario
     */
    void Copiar(const Diccionario<T,U>& D);

    /**
     * @brief Borra un diccionario
     */
    void Borrar();
public:
    /**
     * @brief Constructor por defecto
     */
    Diccionario();

    /**
     * @brief Constructor de copias
     * @param D instancia de la clase diccionario
     */
    Diccionario(const Diccionario<T,U> &D);

    /**
     * @brief Destructor
     */
    ~Diccionario();

    /**
     * @brief Sobrecarga del operador deasignación
     */
    Diccionario<T,U> & operator=(const Diccionario<T,U> &D);

    /**
    * @brief Clase iteradora de diccionario
    */
    class const_iterator {
    private:
        typename std::list<data<T, U>>::const_iterator it;
        const_iterator(typename std::list<data<T, U>>::const_iterator it);
        friend class Diccionario<T, U>;

    public:
        const_iterator();
        const_iterator(const const_iterator &it);
        const_iterator &operator=(const const_iterator &it);
        const_iterator &operator++();
        const_iterator &operator--();
        data<T, U> operator*() const;

        bool operator!=(const const_iterator &it) const;
        bool operator==(const const_iterator &it) const;
    };

    class iterator {
    private:
        typename std::list<data<T, U>>::iterator it;
        iterator(typename std::list<data<T, U>>::iterator it);
        friend class Diccionario<T, U>;

    public:
        iterator();
        iterator(const iterator &it);
        iterator &operator=(const iterator &it);
        iterator &operator++();
        iterator &operator--();
        data<T, U> &operator*();

        bool operator!=(const iterator &it) const;
        bool operator==(const iterator &it) const;
    };

    /**
     * @brief Busca la clave p en el diccionario
     * @param p la clave
     * @param it_out iterador a la posición donde está la clave. Si no está, devuelve end()
     * @return true si la clave está @else devuelve false
     */
    bool Esta_Clave(const T &p, typename  list<data<T,U> >::iterator &it_out);

    /**
     * @brief Inserta un nuevo registro en el diccionario. Lo hace a través de
     * la clave e inserta la lista con toda la información asociada a la clave
     * @param clave clave
     * @param info lista asociada
     * @warning Si el diccionario no estuviese ordenado habría que usar la función sort()
     */
    void Insertar(const T& clave,const list<U> &info);

    /**
     * @brief Añade una nueva información asociada a una clave que está en el
     * diccionario. La nueva información e inserta al final de la lista de información.
     * Si no esta la clave la inserta y añade la información asociada
     * @param s información
     * @param p clave
     */
    void AddSignificado_Palabra(const U & s ,const T &p);

    /**
     * @brief Devuelve la información (una lista) asociada a una clave p
     * @param p clave asociada
     * @return Retorna un iterador a la información correspondiente
     */
    list<U>  getInfo_Asoc(const T & p);

    /**
     * @brief Tamaño diccionario
     * @return Devuelve el tamaño
     */
    int size()const;

    /**
     * @brief Devuelve un iterador al principio del diccionario
     * @return iterador al principio del diccionario
     */
    iterator begin();

    /**
     * @brief Devuelve un iterador al final del diccionario
     * @return iterador al final del diccionario
     */
    iterator end();

    /**
     * @brief Devuelve un iterador al principio del diccionario
     * @return iterador al final del diccionario
     */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador al final del diccionario
     * @return iterador al final del diccionario
     */
    const_iterator cend() const;

    // Añadimos 4 funciones que mejoren la funcionalidad de  la clase

    /**
     * @brief Comprueba si el contenedor se encuentra vacío
     * @return true en caso afirmativo @else devuelve false
     */
    bool empty();

    /**
     * @brief Intercambia el contenido de dos diccionarios.
     * @warning Pueden diferir en tamaño
     * @param dic diccionario con el que intercambiar el contenido
     */
    void swap(Diccionario<T,U> &dic);

    /**
     * @brief Introduce en la instancia actual la unión de dos diccionarios
     * @param dic instancia de diccionario a unir
     */
    Diccionario<T,U> Union(const Diccionario<T,U> &dic);

    /**
     * @brief Borra una entrada dada su clave
     * @param p clave
     */
    void Erase(const T &p);

    /**
     * @brief Borra la información asociada a una clave
     * @param p clave asociada
     */
    void EraseSignificado(const T &p);

};

#include "../src/Diccionario.cpp"
#endif //PRÁCTICA_4_DICCIONARIO_H
