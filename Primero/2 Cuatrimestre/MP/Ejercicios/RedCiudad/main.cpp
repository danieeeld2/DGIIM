#include <iostream>
#include <fstream>
#include "RedCiudades.h"
#include <string>
using namespace std;

int main(int argc, char** argv) {
    std::string param;
    if(argc != 2){
        cerr << "Error en los parámetros";
        exit(1);
    }
    param = argv[1];
    RedCiudades A(param);

    for(int i = 0; i < A.NumCiudades(); i++) {
        for(int j = i+1; j < A.NumCiudades(); j++){
            if(A.NoConectadas(i,j)){
                cout << A.MejorEscalaEntre(i,j).nombre << endl;
            }
        }
    }

    return 0;
}
