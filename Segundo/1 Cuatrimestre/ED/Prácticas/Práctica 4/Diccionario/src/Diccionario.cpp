/**
* @author Daniel Alconchel Vázquez
* @file Diccionario.cpp
*/

#include "../include/Diccionario.h"
using namespace std;

template<class T, class U>
Diccionario<T,U>::Diccionario(){}

template<class T, class U>
void Diccionario<T,U>::Borrar() {
    this->datos.erase(datos.begin(),datos.end());
}

template<class T, class U>
void Diccionario<T,U>::Copiar(const Diccionario<T, U> &D) {
    /*typename list<data<T,U> >::const_iterator it_d;
    typename list<data<T,U> >::iterator it=this->datos.begin();*/

    datos.assign(D.datos.begin(),D.datos.end());

    /*for (it_d=D.datos.begin(); it_d!=D.datos.end();++it_d,++it){
				     this->datos.insert(it,*it_d);
    }*/
}

template<class T, class U>
Diccionario<T,U>::Diccionario(const Diccionario<T, U> &D) {
    Copiar(D);
}

template<class T, class U>
Diccionario<T,U>::~Diccionario() {}

template<class T, class U>
Diccionario<T, U> & Diccionario<T,U>::operator=(const Diccionario<T, U> &D) {
    if (this!=&D){
        Borrar();
        Copiar(D);
    }
    return *this;
}

template<class T, class U>
bool Diccionario<T,U>::Esta_Clave(const T &p, typename list<data<T, U>>::iterator &it_out) {
    if (datos.size()>0){
        typename list<data<T,U> >::iterator it;
        for (it=datos.begin(); it!=datos.end() ;++it){
            if ((*it).clave==p) {
                it_out=it;
                return true;
            }
            else if ((*it).clave>p){
                it_out=it;
                return false;
            }

        }
        it_out=it;
        return false;
    }
    else {
        it_out=datos.end();
        return false;
    }
}

template<class T, class U>
void Diccionario<T,U>::Insertar(const T &clave, const list <U> &info) {
    typename list<data<T,U> >::iterator it;

    if (!Esta_Clave(clave,it)){
        data<T,U> p;
        p.clave = clave;
        p.info_asociada=info;

        datos.insert(it,p);

    }
}

template<class T, class U>
void Diccionario<T,U>::AddSignificado_Palabra(const U &s, const T &p) {
    auto it = datos.begin();
    if(this->Esta_Clave(p, it)){
        (*it).info_asociada.push_back(s);
    } else {
        list<U> l;
        l.push_back(s);
        this->Insertar(p, l);
    }
}

template<class T, class U>
list<U> Diccionario<T,U>::getInfo_Asoc(const T &p) {
    typename list<data<T,U> >::iterator it;

    if (!Esta_Clave(p,it)){
        return list<U>();
    }
    else{
        return (*it).info_asociada;
    }
}

template<class T, class U>
int Diccionario<T,U>::size() const {
    return datos.size();
}

template<class T, class U>
Diccionario<T, U>::iterator::iterator(typename std::list<data<T, U>>::iterator it) {
    this->it = it;
}

template<class T, class U>
Diccionario<T, U>::iterator::iterator() {}

template<class T, class U>
Diccionario<T, U>::iterator::iterator(const Diccionario::iterator &it) {
    this->it = it.it;
}

template<class T, class U>
typename Diccionario<T, U>::iterator &Diccionario<T, U>::iterator::operator=(const Diccionario::iterator &it) {
    this->it = it.it;
    return *this;
}

template<class T, class U>
typename Diccionario<T, U>::iterator &Diccionario<T, U>::iterator::operator++() {
    ++(this->it);
    return *this;
}

template<class T, class U>
typename Diccionario<T, U>::iterator &Diccionario<T, U>::iterator::operator--() {
    --this->it;
    return *this;
}

template<class T, class U>
data<T, U> &Diccionario<T, U>::iterator::operator*() {
    return *it;
}

template<class T, class U>
bool Diccionario<T, U>::iterator::operator!=(const Diccionario::iterator &it) const {
    return this->it != it.it;
}

template<class T, class U>
bool Diccionario<T, U>::iterator::operator==(const Diccionario::iterator &it) const {
    return this->it == it.it;
}


template<class T, class U>
Diccionario<T, U>::const_iterator::const_iterator(typename std::list<data<T, U>>::const_iterator it) {
    this->it = it;
}

template<class T, class U>
Diccionario<T, U>::const_iterator::const_iterator() {}

template<class T, class U>
Diccionario<T, U>::const_iterator::const_iterator(const Diccionario::const_iterator &it) {
    this->it = it.it;
}

template<class T, class U>
typename Diccionario<T, U>::const_iterator &Diccionario<T, U>::const_iterator::operator=(const Diccionario::const_iterator &it) {
    this->it = it.it;
    return *this;
}

template<class T, class U>
typename Diccionario<T, U>::const_iterator &Diccionario<T, U>::const_iterator::operator++() {
    ++(this->it);
    return *this;
}

template<class T, class U>
typename Diccionario<T, U>::const_iterator &Diccionario<T, U>::const_iterator::operator--() {
    --this->it;
    return *this;
}

template<class T, class U>
data<T, U> Diccionario<T, U>::const_iterator::operator*() const{
    return *it;
}

template<class T, class U>
bool Diccionario<T, U>::const_iterator::operator!=(const Diccionario::const_iterator &it) const {
    return this->it != it.it;
}

template<class T, class U>
bool Diccionario<T, U>::const_iterator::operator==(const Diccionario::const_iterator &it) const {
    return this->it == it.it;
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator Diccionario<T,U>::cbegin() const{
	return Diccionario<T,U>::const_iterator(datos.cbegin());
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator Diccionario<T,U>::cend() const{
	return Diccionario<T,U>::const_iterator(datos.cend());
}

template<class T, class U>
typename Diccionario<T,U>::iterator Diccionario<T, U>::begin() {
    return Diccionario<T,U>::iterator(datos.begin());
}

template<class T, class U>
typename Diccionario<T,U>::iterator Diccionario<T, U>::end() {
    return Diccionario<T,U>::iterator(datos.end());
}

/////////////////////////////////////

template<class T, class U>
bool Diccionario<T,U>::empty() {
    if(this->size()==0)
        return true;
    else
        return false;
}

template<class T, class U>
void Diccionario<T,U>::swap(Diccionario<T, U> &dic) {
    Diccionario<T,U> aux;
    aux = dic;
    dic.Copiar(*this);
    this->Copiar(aux);
}

template<class T, class U>
Diccionario<T, U> Diccionario<T,U>::Union(const Diccionario<T, U> &dic) {
    typename  list<data<T,U>>::iterator aux;
    Diccionario<T,U> retorno;
    retorno.Copiar(*this);
    for(auto it=dic.cbegin(); it!=dic.cend(); ++it){
        if(!retorno.Esta_Clave((*it).clave, aux))
            retorno.Insertar((*it).clave, (*it).info_asociada);
    }
    return retorno;
}

template<class T, class U>
void Diccionario<T,U>::Erase(const T &p) {
    auto it = datos.begin();
    if(this->Esta_Clave(p,it))
        datos.erase(it);
}

template<class T, class U>
void Diccionario<T,U>::EraseSignificado(const T &p) {
    auto it = datos.begin();
    if(this->Esta_Clave(p,it))
        (*it).info_asociada.clear();
}

