/* El Instituto de Investigaciones Biologicas Avanzadas de Guejar Sierra dispone de una base
 de datos de ADN de diversas especies biologicas del Parque Nacional de Sierra Nevada codificadas
 como secuencias de caracteres (A, T, G y C) de distinta longitud segun la especie.
 Esta base de datos se compone de 1000 registros donde cada registro contiene el nombre de
 la especie y la secuencia de su ADN, ambas representadas como cadenas de caracteres (tipo
 string). Ejemplos de la informacion asociada con distintas especies son:
 Nombre: “La mosca del Vinagre”, ADN: “ATAATGGACAAT”
 Nombre: “La lombriz de tierra”, ADN: “GGATACT”
 Nombre: “La ameba verde”, ADN: “AGAGAT”
 El instituto necesita un programa de ordenador que les permita identificar a que especie
 pertenece una toma de ADN que se ha recogido en el campo y analizado en el laboratorio.
 Teniendo en cuenta que las secuencias de ADN analizadas pueden comenzar en cualquier
 posicion de la secuencia. Por ejemplo, las secuencias “GGATACT” y “ACTGGAT” pertenecen
 a la misma especie (“La lombriz de tierra”). Observad que la secuencia es la misma, aunque
 comienza en un punto distinto. Se pide:
  Diseñar las estructuras de datos (tipos de datos, estructuras, clases, vectores, ect.) necesarios
 para almacenar en memoria principal esta base de datos.
  Diseñar una funcion que, a partir de la base de datos y de una secuencia de ADN especıfica nos indique si esta registrada en la base de datos y, en caso afirmativo, cual es el
 nombre de la especie.*/

#include <iostream>
#include <cctype>

using namespace std;

const int LONGITUD_MAXIMA = 100;

struct Especie{
		char nombre[LONGITUD_MAXIMA];
		char ADN[LONGITUD_MAXIMA];
};

struct BaseDatos{
	Especie registro[LONGITUD_MAXIMA];
	int numero_registros;
};

bool CompararCiclicamente ( char cadena1[], char cadena2[] );
int PerteneceBBDD ( char adn[], BaseDatos BBDD );
void LeerBBDD ( BaseDatos & BBDD );
void LeerEspecie ( Especie & especie);

int main (){
	
    BaseDatos BBDD;
    char adn[LONGITUD_MAXIMA];
    int registro;
    
    LeerBBDD (BBDD);
    cout  << "Introduce ADN: \n";
    cin >> adn;
    
    registro = PerteneceBBDD (adn,BBDD);
    
	if (registro != -1)
        cout << "La especie es: \n" << BBDD.registro[registro].nombre << "\n";
	else
		cout << "No esta en la BBDD\n";
	
	
}

bool CompararCiclicamente ( char cadena1[], char cadena2[] ){
    
    bool iguales = false;
    int longitud1 = strlen(cadena1);
    int longitud2 = strlen(cadena2);
    
    if ( longitud1 == longitud2 ){
        for (int i=0; i<longitud1 && !iguales; i++){
            iguales = true;
            for (int j=0; j<longitud1 && iguales; j++)
                if (cadena1[j] != cadena2[(j+i)%longitud1])
                    iguales = false;
        }
    }
    
    return iguales;
}

int PerteneceBBDD ( char adn[], BaseDatos BBDD ){
    
    bool existe = false;
    int registro = -1;
    
    for (int i=0; i<BBDD.numero_registros && !existe; i++)
        if (CompararCiclicamente(adn,BBDD.registro[i].ADN)){
            registro = i;
            existe = true;
        }
    
    return registro;
}

    void LeerBBDD ( BaseDatos & BBDD ){;}
    void LeerEspecie ( Especie & especie){;}
