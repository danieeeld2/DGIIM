/* Implementar en C++ un modulo para aceptar/cancelar mensajes de confirmacion. El modulo
 debera mostrar por pantalla el mensaje ¿Confirmar (S/N)?, y unicamente aceptara las pulsaciones
 de las teclas S y N (mayusculas o minusculas). El modulo devolvera false si se pulso
 la N o true si se pulso S.
 */

#include <iostream>

using namespace std;

bool Confirmacion ();

int main(){
    Confirmacion ();
}

bool Confirmacion (){
    char entrada, entrada_minuscula;
    bool confirmacion = false;
    bool salida = false;
    
    cout << "Confirmar (S/N)?\n";
    
    while ( !confirmacion ){
        cin >> entrada;
        entrada_minuscula = tolower(entrada);
        confirmacion = entrada_minuscula!='n' && entrada_minuscula!='s';
    }
    
    if ( entrada_minuscula!='n' )
        salida = true;
    
    return salida;
}

