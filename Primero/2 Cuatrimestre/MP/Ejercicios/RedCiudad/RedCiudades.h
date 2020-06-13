//
// Created by daniel on 13/6/20.
//

#ifndef REDCIUDAD_REDCIUDADES_H
#define REDCIUDAD_REDCIUDADES_H
#include <istream>
#include <fstream>
#include <string>
#include <cstring>

struct InfoCiudades{
    char *nombre;   //Nombre
    int poblacion;  //Num.Habs
};

class RedCiudades{
private:
    int num_ciudades;   //Número de ciudades
    InfoCiudades *info; //info[i]: info de la ciudad i
    double **distancia; //distancia[i][j]: distancia entre las ciudades i y j
    void Allocate(int a);
    void deallocate();
    void copy(const RedCiudades& orig);
    bool read(std::istream& is);
    void print(std::ostream& os);
public:
    RedCiudades();
    RedCiudades(const RedCiudades& orig);
    RedCiudades(std::string ifilename);
    ~RedCiudades();
    bool EstaVacia();
    inline int NumCiudades() const{return num_ciudades;}
    inline double Distancia(int i, int j) const {return distancia[i][j];}
    char* NombreCiudad(int i);
    inline int PoblacionCiudad(int i) const {return info[i].poblacion;}
    RedCiudades& operator=(const RedCiudades& orig);
    std::ostream& operator<<(std::ostream& os);
    std::istream& operator>>(std::istream& is);
    void LeerRedCiudades(std::string ifilename);
    void EscribitRedCiudades(std::string ifilename);
    char* CiudadMejorConectada();
    InfoCiudades MejorEscalaEntre(int i, int j);
    bool NoConectadas(int i, int j);
};

#endif //REDCIUDAD_REDCIUDADES_H
