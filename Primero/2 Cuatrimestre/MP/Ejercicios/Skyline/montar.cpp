/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Skyline.h"
using namespace std;

int main(int argc, char** argv) {
    SkyLine A;
    double a,b,c;
    string ifilename;
    
    do{
        cin >> a >> b >> c;
        if(a != b){
            A.add(a,b,c);
        }    
    }while(a!=b);
    
    A.Salvar(ifilename);
    
    
    return 0;
}

