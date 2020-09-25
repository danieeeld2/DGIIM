#include <iostream>

using namespace std; 

int main () {
    
    int valor;
    double media=0;
    int contador=0;
    
    cout << "\nIntroduce un entero en 0 y 9 (-1 para terminar):" << "\n";
    cin >> valor;
    media += valor;
    contador ++;
    
    while (valor!=-1){
        cout << "\nIntroduce un entero en 0 y 9 (-1 para terminar):" << "\n";
        cin >> valor;
        if (valor != -1){
            media += valor;
            contador ++;
        }
    }
    
    media = media / contador;
    cout << "\nLa media es; "  << media << "\n";
}
