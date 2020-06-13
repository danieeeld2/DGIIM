//
// Created by daniel on 13/6/20.
//

#include <iostream>
#include "RedCiudades.h"

RedCiudades::RedCiudades() {
    num_ciudades = 0;
    info = nullptr;
    distancia = nullptr;
}

void RedCiudades::Allocate(int a) {
    deallocate();
    if(a>0) {
        num_ciudades = a;
        info = new InfoCiudades[a];
        distancia = new double* [a];
        for(int i = 0; i < a; i++){
            distancia[i]  = new double [a];
        }
    }
}

void RedCiudades::deallocate() {
    if(info != nullptr)
        delete [] info;
    info = nullptr;
    if(distancia != nullptr){
        for(int i = 0; i < num_ciudades; i++){
            delete [] distancia[i];
        }
        delete [] distancia;
    }
    distancia = nullptr;
    num_ciudades = 0;
}

RedCiudades::~RedCiudades() {
    deallocate();
}

bool RedCiudades::EstaVacia() {
    if(num_ciudades == 0)
        return true;
    else
        return false;
}

void RedCiudades::copy(const RedCiudades &orig) {
    Allocate(orig.NumCiudades());
    for(int i = 0; num_ciudades; i++){
        info[i].poblacion = orig.PoblacionCiudad(i);
        info[i].nombre = orig.info->nombre;
    }
    for(int i = 0; i < num_ciudades; i++){
        for(int j = 0; j < num_ciudades; j++){
            distancia[i][j] = orig.Distancia(i,j);
        }
    }
}

char *RedCiudades::NombreCiudad(int i) {
    return info[i].nombre;
}

RedCiudades::RedCiudades(const RedCiudades &orig) {
    num_ciudades = 0;
    info = nullptr;
    distancia = nullptr;
    copy(orig);
}

RedCiudades &RedCiudades::operator=(const RedCiudades &orig) {
    if(this != &orig)
        copy(orig);
    return *this;
}

void RedCiudades::print(std::ostream &os) {
    os << num_ciudades << std::endl;
    for(int i = 0; i < num_ciudades; i++){
        os << info[i].poblacion << " " << info[i].nombre << std::endl;
    }
    for(int i = 0; i < num_ciudades; i++){
        for(int j = 0; j < num_ciudades; j++){
            os << Distancia(i,j) << " ";
        }
        os << std::endl;
    }
}

std::ostream &RedCiudades::operator<<(std::ostream &os) {
    print(os);
    return os;
}

bool RedCiudades::read(std::istream &is) {
    std::string aux;
    if(is.fail())
        return false;
    is >> num_ciudades;
    if(is.fail())
        return false;
    Allocate(num_ciudades);
    for(int i = 0; i < num_ciudades; i++){
        if(is.fail())
            return false;
        std::getline(is,aux);
        info->nombre = new char [aux.size()+1];
        for(int i = 0; i < aux.size(); i++){
            info->nombre[i] = aux[i];
        }
        info->nombre[aux.size()] = '\0';
    }
    for(int i = 0; i < num_ciudades; i++){
        for(int j = 0; j < num_ciudades; j++){
            is >> distancia[i][j];
            if(is.fail())
                return false;
        }
    }
    return true;
}

std::istream &RedCiudades::operator>>(std::istream &is) {
    read(is);
    return is;
}

RedCiudades::RedCiudades(std::string ifilename) {
    std::ifstream ifile;
    std::string aux;
    ifile.open(ifilename);
    ifile >> aux;
    if(aux == "RED")
        this->operator>>(ifile);
    else{
        std::cerr << "Falta cadena mágica";
        exit(1);
    }
    ifile.close();
}

void RedCiudades::LeerRedCiudades(std::string ifilename) {
    std::ifstream ifile;
    std::string aux;
    ifile.open(ifilename);
    ifile >> aux;
    if(aux == "RED")
        this->operator>>(ifile);
    else{
        std::cerr << "Falta cadena mágica";
        exit(1);
    }
}

void RedCiudades::EscribitRedCiudades(std::string ifilename) {
    std::ofstream ifile;
    ifile.open(ifilename);
    ifile << "RED" << std::endl;
    this->print(ifile);
    ifile.close();
}

char *RedCiudades::CiudadMejorConectada() {
     int contador1 = 0;
     int contador2 = 0;
     int pos = 0;
     for(int i = 0; i < num_ciudades; i++){
         for(int j = 0; j < num_ciudades; j++){
             if(Distancia(i,j)!=0)
                 contador2++;
         }
         if(contador2>contador1){
             contador1 = contador2;
             pos = i;
         }
         contador2 = 0;
     }
    return info[pos].nombre;
}

InfoCiudades RedCiudades::MejorEscalaEntre(int i, int j) {
    int pos = 0;
    int dis = 0;
    int aux = 0;

    if(NoConectadas(i,j)){
        for(int z = 0; i < num_ciudades; z++){
            aux = Distancia(i,z) + Distancia(z,j);
            if(z != i && z != j && dis != 0){
                if(aux < dis){
                    dis = aux;
                    pos = z;
                }
            }
        }
    }else{
        exit(1);
    }

    return info[pos];
}

bool RedCiudades::NoConectadas(int i, int j) {
    if(Distancia(i,j) == 0)
        return true;
    else
        return false;
}



