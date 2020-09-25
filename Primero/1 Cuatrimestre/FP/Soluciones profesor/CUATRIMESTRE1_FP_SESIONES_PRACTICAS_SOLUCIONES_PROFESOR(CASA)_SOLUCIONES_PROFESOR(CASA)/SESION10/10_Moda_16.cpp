#include <iostream>

using namespace std;

struct FrecuenciaCaracter{
	char caracter;
	int frecuencia;
};

 /**
  *@brief Ordena lexicograficamente los caracteres de una secuencia
  *@param cadena char[] que va a ser ordenado
  *@pre cadena debe ser una cadena tipo c (termina en '\0'
  *@return no devuelve nada, pero la entrada puede ser modificada
  */
void OrdenarSecuencia ( char cadena[] );
/**
 *@brief Busca el caracter con mas apariciones en una cadena de caracteres
 *@param cadena char[] donde buscar el caracter mas frecuente
 *@return Devuelve un dato tipo FrecuenciaCaracter con el caracter mas frecuente
 *        y el numero de apariciones
 *@pre cadena debe tener sus caracteres ordenados lexicograficamente
 */
FrecuenciaCaracter BuscarModa ( char cadena[] );

int main (){
    const int TAMANO_MAXIMO = 100;
	char cadena[TAMANO_MAXIMO];
    FrecuenciaCaracter moda;
    
	cout << "Introduce una frase:\n";
	cin.getline(cadena, TAMANO_MAXIMO);
	
    OrdenarSecuencia( cadena );
	moda = BuscarModa(cadena);
	
	cout << "La moda es " << moda.caracter << ". Se repite " << moda.frecuencia << " veces\n";
}

FrecuenciaCaracter BuscarModa ( char cadena[] ){
    FrecuenciaCaracter SalidaModa;
    int caracter_anterior = cadena[0];
    int caracter = caracter_anterior;
    int repeticiones = 1;
    int moda = caracter_anterior;
    int apariciones_moda = repeticiones;
    
    /* Algoritmo:
     * calcula la subsecuencia maxima de caracteres repetidos,
     * y el caracter que la produce
     */
    int i = 1;
    while ( caracter != '\0' ){
        caracter = cadena[i];
        if ( caracter == caracter_anterior )
            repeticiones++;
        else
            if ( repeticiones > apariciones_moda ){
                moda = caracter_anterior;
                apariciones_moda = repeticiones;
                repeticiones = 1;
            }
        caracter_anterior = caracter;
        i++;
    }
    
    SalidaModa.caracter = moda;
    SalidaModa.frecuencia = apariciones_moda;
    
    return SalidaModa;
}

void OrdenarSecuencia ( char cadena[] ){
    // utilizar cualquier algoritmo de ordenacion
    ;
}
