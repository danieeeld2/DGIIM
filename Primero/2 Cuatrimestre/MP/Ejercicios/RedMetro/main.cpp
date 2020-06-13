#include <iostream>
#include "RedMetro.h"
#include "Linea.h"
#include "InfoParada.h"
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    string param;
    ifstream ifile1,ifile2;
    RedMetro A,B;

    if(argc != 3){
        cerr << "Error en los argumentos";
        exit(1);
    }
    for(int i = 1; i < argc; i++){
        param = argv[i];
        if(i == 1){
            ifile1.open(param);
            A.operator>>(ifile1);
            ifile1.close();
        }
        if(i == 2){
            ifile2.open(param);
            B.operator>>(ifile2);
            ifile2.close();
        }
    }

    if(A.operator>(B)){
        cout << "A es mejor red que B" << endl;
        for(int i = 0; i < A.GetNumLineas(); i++){
            if(A.EstaTotalmenteOperativa(i)){
                cout << "La línea " << i << " está totalmente operativa" << endl;
            }else{
                cout << "La línea "<< i << " no está totalmente operativa" << endl;
            }
        }
        cout << "La línea mejor conectada es:" << endl;
        A.MejorConectada().print(cout);
    }else{
        cout << "B es mejor red que A" << endl;
        for(int i = 0; i < B.GetNumLineas(); i++){
            if(B.EstaTotalmenteOperativa(i)){
                cout << "La línea " << i << " está totalmente operativa" << endl;
            }else{
                cout << "La línea "<< i << " no está totalmente operativa" << endl;
            }
        }
        cout << "La linea mejor conectada es: " << endl;
        B.MejorConectada().print(cout);
    }

    return 0;
}
