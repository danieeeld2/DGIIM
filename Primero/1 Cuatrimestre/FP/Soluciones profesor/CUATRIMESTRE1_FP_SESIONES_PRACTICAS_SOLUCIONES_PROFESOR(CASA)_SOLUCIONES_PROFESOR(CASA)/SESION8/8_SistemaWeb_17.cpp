/* Se esta disenando un sistema web que recolecta datos personales de un usuario y, en un
 momento dado, debe sugerirle un nombre de usuario (login). Dicho login estara basado
 en el nombre y los apellidos; en concreto estara formado por los N primeros caracteres
 de cada nombre y apellido (en minusculas, unidos y sin espacios en blanco). Por ejemplo,
 si el nombre es Antonio Francisco Molina Ortega y N = 2, el nombre de
 usuario sugerido sera anfrmoor. Debe tener en cuenta que el numero de palabras que forman
 el nombre y los apellidos puede ser cualquiera. Ademas, si N es mayor que alguna
 de las palabras que aparecen en el nombre, se incluira la palabra completa. Por ejemplo,
 si el nombre es Ana Campos de la Blanca y N = 4, entonces la sugerencia sera
 anacampdelablan (observe que se pueden utilizar varios espacios en blanco para separar
 palabras).
 Implementar un programa Codifica que, a partir de una cadena de caracteres formada por
 el nombre y apellidos (separados por uno o mas espacios en blanco) y un entero, calcule otra
 cadena con la sugerencia de login. Para probar el programa leemos una cadena de caracteres
 con la sentencia getline(cin, cadena); (acepta espacios en blanco en la palabra)*/


#include<iostream>
#include<cctype>

using namespace std;

int main(){
    const int LOGITUD_MAXIMA = 100;
    char cadena[LOGITUD_MAXIMA];
    char login[LOGITUD_MAXIMA];
    
    int maximo_caracteres;
    int contador_caracteres = 0;
    int posicion_escritura = 0;
    
    cout << "\nIntroduce nombre (MAX " << LOGITUD_MAXIMA << " caracteres): \n";
    cin.getline(cadena, LOGITUD_MAXIMA);
    
    int longitud = strlen(cadena);
    
	cout << "Introduce un numero entero positivo: ";
    cin >> maximo_caracteres;
	
    /* Algoritmo
     Para cada caracter de la cadena introducida
        si es un espacio en blanco
            se pone a cero el contador de carateres insertados en la palabra actual
        si no
            si no se ha llegado al máximo de caracteres de la palabra
                se escribe en la cadena de salida
     */
    for ( int i=0; i<longitud; i++ ){
        if ( cadena[i] == ' ' )
            contador_caracteres = 0;
        else if ( contador_caracteres < maximo_caracteres ){
            login[posicion_escritura] = tolower(cadena[i]);
            posicion_escritura++;
            contador_caracteres++;
        }
    }
    
    // añadimos el símbolo fin de cadena a la cadena de salida
    login[posicion_escritura] = '\0';
    
    cout << "\nLogin: " << login << "\n";
}
