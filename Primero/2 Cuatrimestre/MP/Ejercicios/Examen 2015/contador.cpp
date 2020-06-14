/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>

#include "Frecuencias.h"

int main(int argc, char** argv){
    Frecuencias A;
    std::ifstream ifile;
    
    if(argc > 2){
        std:: cerr << "Error de parámetros";
        exit(1);
    }
    
    if(argc == 2){
        ifile.open(argv[1]);
        if(!ifile){
            std:: cerr << "Error en la apertura de fichero";
            exit(1);
        }
        A.read(ifile);
        ifile.close();
    }else{
        A.read(std::cin);
    }
    
    std::cout << A << std::endl;
    
    return 0;
}