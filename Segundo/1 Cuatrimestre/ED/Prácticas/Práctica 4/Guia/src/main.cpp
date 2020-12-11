#include <iostream>
#include <sstream>

#include "../include/Guiatlf.h"
    using namespace std;

    int main() {
        Guia_Tlf guia1;
        guia1.insert("Daniel", "634778965");
        guia1.insert("Kiko", "654324576");
        Guia_Tlf guia2;
        guia2 = guia1;
        guia1.insert("Ale", "654776542");
        cout << "Guia1: " << endl << guia1 << endl;
        cout << "Guia2: " << endl << guia2 <<  endl;

        Guia_Tlf guia3;
        guia3 = guia1-guia2;
        Guia_Tlf guia4;
        guia2.insert("Pablo", "643557689");
        guia4 = guia1+guia2;
        cout << "Diferencia: " << endl << guia3 << endl;
        cout << "Suma: " << endl << guia4 << endl;

        cout << "Probamos ahora el operador >>: " << endl << endl;
        stringstream ss;
        ss << guia1;
        Guia_Tlf guia5;
        ss >> guia5;
        cout << "Guia5: " << endl << guia5 << endl;

        cout << endl << "Probamos ahora el resto de funciones: " <<  endl;
        cout << "Funcion empty:" << endl;
        if(guia1.empty())
            cout << "Guia 1 está vacío" << endl;
        else
            cout << "Guia 1 no está vacío"<< endl;

        cout << endl << "Probamos la función swap: " << endl;
        cout << "Intercambianddo Guia 1 y Guia 2" << endl;
        guia1.swap(guia2);
        cout << endl << "Guia1: " << endl << guia1 << endl;
        cout << endl << "Guia2: " << endl << guia2 << endl;

        cout << endl << "Probando a cambiar número de teléfono: " << endl;
        guia2.CambiarTelefono("Kiko", "1111111111");
        cout << endl << guia2 << endl;

        cout << endl << "Probemos a sacar los nombres que empiezan por F" << endl;
        cout << "Imprimiendo la lista: " <<  endl;
        auto lista_F = guia2.Indice('K');
        while (!lista_F.empty()){
            cout << lista_F.front().first << "\t" << "\t" << lista_F.front().second << endl;
            lista_F.pop_front();
        }

        return 0;
    }