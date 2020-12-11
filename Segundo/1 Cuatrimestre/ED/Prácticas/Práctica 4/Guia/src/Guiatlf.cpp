/**
 * @author Daniel Alconchel Vázquez
 * @file Guiatlf.cpp
 */

#include "../include/Guiatlf.h"
#include <iostream>

Guia_Tlf::Guia_Tlf() {}

Guia_Tlf::Guia_Tlf(const Guia_Tlf &gt) {
    *this=gt;
}

Guia_Tlf::~Guia_Tlf() {}

Guia_Tlf &Guia_Tlf::operator=(const Guia_Tlf &gt) = default;

string & Guia_Tlf::operator[](const string &nombre) {
    return datos[nombre];
}

string Guia_Tlf::gettelefono(const string &nombre) {
    map<string,string>::iterator it=datos.find(nombre);
    if (it==datos.end())
        return string("");
    else return it->second;
}

pair<map<string, string>::iterator, bool> Guia_Tlf::insert(string nombre, string tlf) {
    pair<string,string> p (nombre,tlf);
    pair< map<string,string> ::iterator,bool> ret;

    ret=datos.insert(p);
    return ret;
}

pair<map<string, string>::iterator, bool> Guia_Tlf::insert(pair <string, string> p) {
    pair<map<string,string> ::iterator,bool> ret;

    ret=datos.insert(p);
    return ret;
}

void Guia_Tlf::borrar(const string &nombre) {
    map<string,string>::iterator itlow = datos.lower_bound(nombre); //el primero que tiene dicho nombre
    map<string,string>::iterator itupper = datos.upper_bound(nombre);   //el primero que ya no tiene dicho nombre
    datos.erase(itlow,itupper); //borramos todos aquellos que tiene dicho nombre
}

void Guia_Tlf::borrar(const string &nombre, const string &tlf) {
    map<string,string>::iterator itlow = datos.lower_bound(nombre);     //el primero que tiene dicho nombre
    map<string,string>::iterator itupper = datos.upper_bound(nombre);   //el primero que ya no tiene dicho nombre
    map<string,string>::iterator it;
    bool salir =false;
    for (it=itlow; it!=itupper && !salir;++it){
        if (it->second==tlf){
            datos.erase(it);
            salir =true;
        }
    }
}

int Guia_Tlf::size() const {
    return datos.size();
}

unsigned int Guia_Tlf::contabiliza(const string &nombre) {
    return datos.count(nombre);
}

void Guia_Tlf::clear() {
    datos.clear();
}

Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf &g) {
    Guia_Tlf aux(*this);
    map<string,string>::const_iterator it;
    for (it=g.datos.begin();it!=g.datos.end();++it){
        aux.insert(it->first,it->second);
    }
    return aux;
}

Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf &g) {
    Guia_Tlf aux(*this);
    map<string,string>::const_iterator it;
    for (it=g.datos.begin();it!=g.datos.end();++it){
        aux.borrar(it->first,it->second);
    }
    return aux;
}

ostream &operator<<(std::ostream &os, Guia_Tlf &g) {
    for (auto it = g.cbegin(); it != g.cend(); ++it) {
        os << (*it).first << '\t' << '\t' << (*it).second << std::endl;
    }
    return os;
}

istream & operator>>(istream &is,pair<string,string> &d){
    getline(is,d.first,'\t');
    getline(is,d.second);
    return is;
}

istream &operator>>(std::istream &is, Guia_Tlf &g) {
    g.datos.clear();
    std::pair<std::string, std::string> aInsertar;
    while (is) {
        is >> aInsertar;
        if (is) g.insert(aInsertar);
    }

    return is;
}

Guia_Tlf::iterator::iterator() {}

Guia_Tlf::iterator::iterator(const iterator &it) {
    this->it = it.it;
}

Guia_Tlf::iterator::iterator(map<string, string>::iterator it) {
    this->it = it;
}


Guia_Tlf::iterator &Guia_Tlf::iterator::operator=(const Guia_Tlf::iterator &it){
    this->it = it.it;
    return *this;
}

Guia_Tlf::iterator & Guia_Tlf::iterator::operator++() {
    ++(this->it);
    return *this;
}

Guia_Tlf::iterator & Guia_Tlf::iterator::operator--() {
    --this->it;
    return *this;
}

pair<const std::string, std::string> &Guia_Tlf::iterator::operator*() {
    return *it;
}

bool Guia_Tlf::iterator::operator!=(const iterator &it) const {
    return this->it != it.it;
}

bool Guia_Tlf::iterator::operator==(const iterator &it) const {
    return this->it == it.it;
}

Guia_Tlf::const_iterator::const_iterator(map<string, string>::const_iterator it) {
    this->it = it;
}

Guia_Tlf::const_iterator::const_iterator() {}

Guia_Tlf::const_iterator::const_iterator(const const_iterator &it) {
    this->it = it.it;
}

Guia_Tlf::const_iterator &Guia_Tlf::const_iterator::operator=(const Guia_Tlf::const_iterator &it) {
    this->it = it.it;
    return *this;
}

Guia_Tlf::const_iterator & Guia_Tlf::const_iterator::operator++() {
    ++(this->it);
    return *this;
}

Guia_Tlf::const_iterator & Guia_Tlf::const_iterator::operator--() {
    --this->it;
    return *this;
}

pair<const std::string, std::string> Guia_Tlf::const_iterator::operator*() const {
    return *it;
}

bool Guia_Tlf::const_iterator::operator!=(const const_iterator &it) const {
    return this->it != it.it;
}

bool Guia_Tlf::const_iterator::operator==(const const_iterator &it) const {
    return this->it == it.it;
}

Guia_Tlf::iterator Guia_Tlf::begin() {
    return Guia_Tlf::iterator(datos.begin());
}

Guia_Tlf::iterator Guia_Tlf::end() {
    return Guia_Tlf::iterator(datos.end());
}

Guia_Tlf::const_iterator Guia_Tlf::cend() const {
    return Guia_Tlf::const_iterator(datos.cend());
}

Guia_Tlf::const_iterator Guia_Tlf::cbegin() const {
    return Guia_Tlf::const_iterator(datos.cbegin());
}

bool Guia_Tlf::empty() {
    if(this->size()==0)
        return true;
    else
        return false;
}

void Guia_Tlf::swap(Guia_Tlf &g) {
    Guia_Tlf aux;
    aux = g;
    g=(*this);
    *this=aux;
}

void Guia_Tlf::CambiarTelefono(const string &p, const string &t) {
    this->borrar(p);
    this->insert(p,t);
}


list<pair<const string, string>> Guia_Tlf::Indice(const char letter) const {
    list<pair<const string ,string>> aux;
    bool Esta;
    for(auto it : datos){
        if(!it.first.empty()){
            if(it.first[0]==letter)
                Esta = true;
            else
                Esta = false;
        }
        else
            Esta = false;
        if(Esta)
            aux.push_back(it);
    }
    return aux;
}