/* Implementar un modulo en C++ que tenga como entrada un caracter.
 a. Si el argumento es una letra mayuscula, debera devolver su correspondiente minuscula.
 b. Si el argumento NO es una letra mayuscula, devolvera el mismo caracter.
 */

#include <iostream>

using namespace std;

/* Funcion Minuscula
 * @brief Convierte mayuscula a minuscula, el resto lo deja invariante
 * @param caracter es el caracter a considerar
 * @return el caracter en minuscula, si caracter es una mayuscula, o el mismo, en otro caso
 */
char ConvierteMinuscula (char caracter);

int main(){
    char caracter;
    char caracter_minuscula;
    
    cout << "\nIntroduce caracter: ";
    cin >> caracter;
    
    caracter_minuscula = ConvierteMinuscula(caracter);
    
    cout << caracter_minuscula << "\n";
}

char ConvierteMinuscula (char caracter){
    char salida;
    
    if ( caracter >= 'A' || caracter <= 'Z' )
        salida = tolower(caracter);
    else
        salida = caracter;
    
    return salida;
}

