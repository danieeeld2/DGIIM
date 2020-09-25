/* Programa para calcular el dinero obtenido gracias a la oferta de un banco.
   Implementa la fórmula: total=capital+capital*(interes/100)
   Necesita: El dinero depositado y el interés del banco
            capital, intereses.
   Calcula: El dinero generado en un año
            total
*/

#include <iostream>  // Inclusión de los recursos de E/S

/*
using namespace std;

int main(){                      //Programa Principal (Caso 1, introducimos el capital inicial)
   double capital;               //Declaraión de variables
   double intereses;             //El capital, el interés y el total
   double total;
   
   cout << "Introduzca capital ingresado: ";
   cin >> capital;
   cout << "Introduzca el interés del banco: ";
   cin >> intereses;
   
   total = capital+capital*(intereses/100);
   
   cout << "\nEl total es de " << total << "\n\n" ;
   
   system ("pause");
}
*/


using namespace std;

int main(){                      //Programa Principal (Caso 2, el capital inicial es el total anterior)
   double capital;               //Declaraión de variables
   double intereses;             //El capital y el total
   
   cout << "Introduzca capital ingresado: ";
   cin >> capital;
   cout << "Introduzca el interés del banco: ";
   cin >> intereses;
   
   capital = capital+capital*(intereses/100);
   
   cout << "\nEl capital total es de " << capital << "\n\n" ;
   
   system ("pause");
}
