#include <iostream>
#include <list>

#include "../include/Diccionario.h"
using namespace std;

int main() {
    Diccionario<string, string> Dic;
    Dic.Insertar("Presentacion", list<string>());
    Dic.AddSignificado_Palabra("Hola, me llamo Daniel", "Presentacion");
    Dic.AddSignificado_Palabra("Estudio en el DGIIM", "Presentacion");
    Dic.Insertar("Seguimos", list<string>());
    Dic.AddSignificado_Palabra("Probando Probando", "Seguimos");
    Dic.Insertar("Despedida", list<string>());
    Dic.AddSignificado_Palabra("Hasta Luego", "Despedida");
    Diccionario<string, string> Dic2;
    Dic2.Insertar("EyEy", list<string>());
    Dic2.AddSignificado_Palabra("Veamos como funciona", "EyEy");

    cout << "Imprimiendo el diccionario por pantalla: " << endl;
    for(auto it=Dic.begin(); it!=Dic.end(); ++it){
        cout << (*it).clave << ":" << endl;
        for(auto it2=(*it).info_asociada.begin(); it2!=(*it).info_asociada.end(); ++it2){
            cout << "\t" << *it2 << endl;
        }
    }
    cout << endl << "Imprimiendo información asociada a la clave Presentacion:" << endl;
    auto i=Dic.getInfo_Asoc("Presentacion");
    for(auto& it : i){
        cout << it << ", ";
    }

    cout << endl << "Vamos a probar ahora las funciones que hemos añadido: " << endl;

    cout << endl;

    cout << "Probando función empty" << endl;
    if(Dic.empty())
        cout << "El diccionario está vacío" << endl;
    else
        cout << "El diccionario no está vacío" << endl;

    cout << endl;

    cout << "Probando función swap" << endl;
    Dic.swap(Dic2);
    cout << "Imprimiendo los diccionarios" << endl;
    cout << "Diccionario 1:" << endl;
    for(auto it=Dic.begin(); it!=Dic.end(); ++it){
        cout << (*it).clave << ":" << endl;
        for(auto it2=(*it).info_asociada.begin(); it2!=(*it).info_asociada.end(); ++it2){
            cout << "\t" << *it2 << endl;
        }
    }
    cout << "Diccionario 2:" << endl;
    for(auto it=Dic2.begin(); it!=Dic2.end(); ++it){
        cout << (*it).clave << ":" << endl;
        for(auto it2=(*it).info_asociada.begin(); it2!=(*it).info_asociada.end(); ++it2){
            cout << "\t" << *it2 << endl;
        }
    }

    cout << endl;

    cout << "Probando función Union:" << endl;
    Diccionario<string, string> Union;
    Union=Dic.Union(Dic2);
    cout << "Imprimiendo la unión de los diccionarios: " << endl;
    for(auto it=Union.begin(); it!=Union.end(); ++it){
        cout << (*it).clave << ":" << endl;
        for(auto it2=(*it).info_asociada.begin(); it2!=(*it).info_asociada.end(); ++it2){
            cout << "\t" << *it2 << endl;
        }
    }

    cout << endl;

    cout << "Probando funciones de borrado: " << endl;
    Dic2.Erase("Seguimos");
    Dic2.EraseSignificado("Presentacion");
    cout << "Imprimiendo diccionario:" << endl;
    for(auto it=Dic2.begin(); it!=Dic2.end(); ++it){
        cout << (*it).clave << ":" << endl;
        for(auto it2=(*it).info_asociada.begin(); it2!=(*it).info_asociada.end(); ++it2){
            cout << "\t" << *it2 << endl;
        }
    }

    cout << endl;
    return 0;
}