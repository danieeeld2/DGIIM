/**
 * @author Daniel Alconchel Vázquez
 * @file Guiatlf.h
 */

#ifndef GUIA_GUIATLF_H
#define GUIA_GUIATLF_H

#include <map>
#include <iostream>
#include <string>
#include <list>
using namespace std;

istream & operator>>(istream &is,pair<string,string> &d);

/**
 * @brief T.D.A. Guía de Teléfono
 *
 * Instancia que representa una guía de teléfono a través de un map. Las
 * claves serán los nombres, mientras que la información asociada
 * será los números de teléfono
 */
class Guia_Tlf {
private:
    map<string ,string> datos; // Si admitieramos que hubiera nombres repetidos tendríamos que usar multimap
public:
    /**
     * @brief Constructor por defecto
     */
    Guia_Tlf();

    /**
     * @brief Constructor de copia
     * @param gt instancia clase Guia_Tlf a copiar
     */
    Guia_Tlf(const Guia_Tlf &gt);

    /**
     * @brief Destructor de la clase
     */
    ~Guia_Tlf();

    /**
     * @brief Sobrecarga del operador de asignación
     * @param gt instancia de la clase Guia_Tlf
     * @return
     */
    Guia_Tlf & operator=(const Guia_Tlf &gt);

    /**
     * @brief Sobrecarga operador []
     * @param nombre clave
     * @return Devuelve la clave con la información asociada
     */
    string & operator[](const string &nombre);

    /**
     * @brief Devuelve el número de teléfono asociado a una persona (clave)
     * @param nombre nombre de la persona
     * @return Su número de teléfono
     */
    string gettelefono(const string &nombre);

    /**
     * @brief Inserta un nuevo teléfono
     * @param nombre clave dek nuevo teléfono (persona asociada)
     * @param tlf número de teléfono
     * @return Un pair donde dirst apunta al nuevo elemento insertado y bool es true si se ha insertado correctamente @else devuelve false
     */
    pair<map<string,string>::iterator,bool>  insert(string nombre, string tlf);

    /**
     * @brief Inserta un nuevo teléfono
     * @param p pair con el nombre de la persona y el teléfono asociado
     * @return Un pair donde dirst apunta al nuevo elemento insertado y bool es true si se ha insertado correctamente @else devuelve false
     */
    pair<map<string,string>::iterator,bool>  insert(pair<string,string> p);

    /**
     * @brief Borra un teléfono
     * @param nombre que se quiere borrar
     * @note En caso de que fuese un multimap borraría todos con ese nombre
     */
    void borrar(const string &nombre);

    /**
     * @brief Borra un teléfono
     * @param nombre que se quiere borrar
     * @param tlf teléfono asociado
     * @note Esta funcion nos permite borrar solamente aquel que coincida en nombre y tlf
     * @note Con map siempre hay uno con multimap puede existir mas de uno
     */
    void borrar(const string &nombre,const string &tlf);

    /**
     * @brief Número de teléfono
     * @return El número de telefonos asociados
     */
    int size() const;

    /**
     * @brief Contabiliza cuantos números de teléfono tenemos asociados a un nombre
     * @param nombre nombre sobre el que queremos consultar
     * @return Número de teléfonos asociados al nombre
     * @note Como estamos usando map, debe ser 0 o 1. En caso de multimap si pueden ser más
     */
    unsigned int contabiliza(const string &nombre);

    /**
     * @brief Limpia la guía
     */
     void clear();

    /**
     * @brief Unión de guías de teléfono
     * @param g guía que se une
     * @return Una nueva guía resultado de unir el objeto al que apunta this y g
     */
    Guia_Tlf operator+(const Guia_Tlf & g);

    /**
     * @brief Diferencia de guías de teléfono
     * @param g guía que se une
     * @return Una nueva guía resultado de la diferencia del objeto al que apunta this y g
     */
    Guia_Tlf operator-(const Guia_Tlf & g);

    /**
     * @brief Escritura de la guía de teléfonos
     * @param os flujode salida. Es modificado
     * @param g guía de teléfonos que se escribe en el flujo
     * @return El flujo de salida
     */
    friend ostream &operator<<(std::ostream &os, Guia_Tlf &g) ;

    /**
     * @brief Lectura de la guía de teléfonos
     * @param is flujo de entrada. Es modificado
     * @param g guía de teléfonos. Es modificado
     * @return El flujo de entrada
     */
    friend istream & operator>>(istream & is, Guia_Tlf & g);

    // Añadimos las clases iteradoras

    /**
     * @brief Clase iteradora de la clase Guia_Tlf
     */
    class const_iterator{
    private:
        map<string ,string>::const_iterator it;
        const_iterator(map<string,string>::const_iterator it);
        friend class Guia_Tlf;

    public:
        const_iterator();
        const_iterator(const const_iterator &it);
        const_iterator &operator=(const const_iterator &it);
        const_iterator &operator++();
        const_iterator &operator--();
        pair<const string ,string> operator*() const;
        bool operator!=(const const_iterator &it) const;
        bool operator==(const const_iterator &it) const;
    };

    /**
     * @brief Clase iteradora de la clase Guia_Tlf
     */
    class iterator{
    private:
        map<string ,string>::iterator it;
        iterator(map<string,string>::iterator it);
        friend class Guia_Tlf;
    public:
        iterator();
        iterator(const iterator &it);
        iterator &operator=(const iterator &it);
        iterator &operator++();
        iterator &operator--();
        pair<const string,string> &operator*();
        bool operator!=(const iterator &it) const;
        bool operator==(const iterator &it) const;
    };

    /**
     * @brief Devuelve un iterador al principio de la guía
     * @return iterador al principio de la guía
     */
    iterator begin();

    /**
     * @brief Devuelve un iterador a despues del último elemento de la guía
     * @return iterador a despues del último elemento de la guía
     */
    iterator end();

    /**
     * @brief Devuelve un iterador al principio de la guía
     * @return iterador al principio de la guía
     */
    const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador a despues del último elemento de la guía
     * @return iterador a despues del último elemento de la guía
     */
    const_iterator cend() const;

    // Añadimos 4 funciones

    /**
     * @brief Comrpueba si el contenedor esta vacío
     * @return
     */
    bool empty();

    /**
     * @brief Intercambia el contenido entre el contenedor al que apunta this y el contenedor g
     * @param g instancia Guia_Tlf
     */
    void swap(Guia_Tlf& g);

    /**
     * @brief Dado una clave, permite cambiar su número de teléfono asociada
     * @param p clave
     * @param t telefono
     */
    void CambiarTelefono(const string &p, const string &t);

    /**
     * @brief Devuelve todos los números de aquellas personas cuyos nombres empiecen por letter
     * @param letter letra por la que debe empezar por el nombre
     * @return lista de los números y nombres
     */
    list<pair<const string, string>> Indice(const char letter) const;

};

#endif //GUIA_GUIATLF_H
