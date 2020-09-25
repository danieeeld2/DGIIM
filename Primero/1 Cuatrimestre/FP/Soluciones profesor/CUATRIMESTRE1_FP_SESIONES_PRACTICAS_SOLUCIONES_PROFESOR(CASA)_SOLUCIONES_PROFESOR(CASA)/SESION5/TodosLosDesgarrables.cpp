/*
Un numero entero n se dice que es desgarrable (torn) si al dividirlo en dos partes
izda y dcha, el cuadrado de la suma de ambas partes es igual a n. Por ejemplo,
88209 es desgarrable ya que (88 + 209)^2 = 88209. Cread un programa que lea un
entero n e indique si es o no desgarrable.
*/

#include <iostream>

using namespace std;

void desgar (int numero);

int main(){
    int numero;
    
    cin >> numero;
    
    for (int i=1;i<=numero;i++)
        desgar(i);
    
}

void desgar (int numero){
    int izquierda, derecha, cuadrado, potencia_10;
    bool desgarrable = false;
    
    izquierda = numero;
    derecha = 0;
    cuadrado = 0;
    potencia_10 = 10;
    
    while ( izquierda > 9 && !desgarrable){
        izquierda = numero / potencia_10;
        derecha = numero % potencia_10;
        cuadrado = (izquierda + derecha) * (izquierda + derecha);
        potencia_10 = potencia_10 * 10;
        desgarrable = (numero == cuadrado);
    }
    
    
    if ( desgarrable )
        cout << "\nEl numero " << numero << " es desgarrable" << "\n";
    
}


