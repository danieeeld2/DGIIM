#include <iostream>
#include "Punto3D.h"
#include "Trayectoria.h"
#include "Vuelo.h"
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
    const char *param;
    double valor;
    string ifilename1, ifilename2;

    /*Recibe 2 nombres de fichero y un double*/
    if(argc != 4) {
        cerr << "Error en el número de los argumentos";
        std::exit(1);
    }
    for(int i = 1; i<argc; i++){
        param = argv[i];
        if(i == 1)
            ifilename1 = param;
        if(i == 2)
            ifilename2 = param;
        if(i == 3)
            valor = atof(param);
    }

    Vuelo A(ifilename1);
    Vuelo B(ifilename2);

    if(A<B) {
        A.print(cout);
        if(A.calcularDistanciaMediaTrayectorias()<valor)
            cout << "Cumple la condición de cercanía" << endl;
        else
            cout << "No cumple la condición de cercanía" << endl;
    }else {
        B.print(cout);
        if(B.calcularDistanciaMediaTrayectorias() < valor)
            cout << "Cumple la condición de cercanía" << endl;
        else
            cout << "No cumple la condición de cercanía" << endl;
    }

    cout << endl << endl;
    return 0;
}
