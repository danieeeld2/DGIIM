/*
 Escribe una funcion que lea una cadena, busque un caracter en ella y devuelva si se encuentra
o no.
 */


#include <iostream>

using namespace std;


/**
 *@brief Funciom que busca un caracter en una cadena de caracteres
 *@param cadena char[] (termina en '\0') donde buscar
 *@param caracter char a ser buscado
 *@return true si la encuentra, false en caso contrario
 *@pre cadena debe ser una cadena de caracteres tipo C (debe terminar en '\0')
 */
bool BuscaCaracter ( char cadena[] , char caracter );

int main(){
    const int TAMANO_MAXIMO = 100;
	
    char cadena[TAMANO_MAXIMO];
	char caracter;
    bool encontrado;
	
	cout << "Introduce una frase: \n";
	cin.getline(cadena, TAMANO_MAXIMO);
	
	cout << "Introduce un caracter: ";
	cin >> caracter;
	
    encontrado = BuscaCaracter (cadena,caracter);
	
	if (encontrado)
		cout << "El caracter esta en la cadena\n";
	else
		cout << "El caracter no esta en la cadena\n";
}


bool BuscaCaracter ( char cadena[] , char caracter ){
    int i = 0;
    bool encuentra = false;
    
    /* Algoritmo
     * Mientras no haya encontrado el caracter o '\0'
     * Si el carcater actual a analizar de la cadena es caracter, devuelve true
     * Si no, pasa al siguiente
     */
    while ( cadena[i] != '\0' && !encuentra )
        if (cadena[i] == caracter)
            encuentra = true;
        else
            i++;
        
    return encuentra;
}
