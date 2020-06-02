/*Ejercicio 1 Examen Metodología de la Proogramación II
Septiembre de 2006*/
#include <iostream>
using namespace std;

int Reptecición(char *p, char c){
    static int i = 0;
    static int j = 0;
    if(p[0] == '\0'){
        return 0;
    }
    if(p[i] == c){
        i++;
        j++;
        Reptecición(p,c);
    }else{
        if(p[i] != '\0'){
        i++;
        Reptecición(p,c);
        }else{
            return j;
        }
    }

};

int main(){
    char cadena[10] = {'A','B','B','B','C','C','\0'};
    cout << endl << Reptecición(cadena,'B');
    return 0;
}
