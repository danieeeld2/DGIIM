/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 14 de abril de 2020, 16:36
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */

int CompararCadenas(char *a, char *b);
void InsertarCadenas(char *a, char *b, char fusion[], int c);

int main() {
    char cadena1[] = "Hola";    //  Delimitada por '\0'
    char cadena2[] = "Adios";   //  Delimitada por '\0'
    char *ptr1 = cadena1;   //  Apunta a cadena1[0]
    char *ptr2 = cadena2;   //  Apunta a cadena2[0]
    char fusion[100];
    int posicion = 2;
    char *ptr3 = fusion;
    
    cout << endl << CompararCadenas(ptr1, ptr2) << endl;
    ptr1 = cadena1;   //  Apunta a cadena1[0]
    ptr2 = cadena2;   //  Apunta a cadena2[0]
    InsertarCadenas(ptr1, ptr2, fusion, posicion);
    for(int i = 0; *ptr3  != '\0'; i++){
        cout << *ptr3;
        *(ptr3++);
    }

    return 0;
}

int CompararCadenas(char *a, char *b){
    int contador1 = 0;
    int contador2 = 0;
    
    for(int i = 0; *a != '\0'; i++){
        contador1 = i;
        *(a++);
    }
    for(int i = 0; *b != '\0'; i++){
        contador2 = i;
        *(b++);
    }
    
    if(contador1==contador2)
        return 0;
    if(contador1<contador2)
        return -1;
    if(contador1>contador2)
         return 1;    
};

void InsertarCadenas(char* a, char* b, char fusion[], int c){
    char *ptrauxiliar = fusion;
    
    for(int i=0; i!=c; i++){
        *ptrauxiliar = *a;
        *(ptrauxiliar++);
        *(a++);
    }
    for(int i=0; *b!='\0'; i++){
        *ptrauxiliar = *b;
        *(ptrauxiliar++);
        *(b++);        
    }
    for(int i = 0; *a!='\0'; i++){
        *ptrauxiliar = *a;
        *(ptrauxiliar++);
        *(a++);
    }
    *ptrauxiliar = '\0';
}