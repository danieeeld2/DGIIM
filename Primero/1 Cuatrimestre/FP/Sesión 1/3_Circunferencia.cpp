/* Programa para calcular el área y la longitud de una circunferencia
   Implementa las siguientes fórmulas: Área=PI*r^2 
                                       Longitud=2*PI*r
   Necesita: La longitud del radio de la circunferencia
            radio.
   Calcula: El área y la longitud de la circunferencia
            área, longitud.
*/

#include <iostream>  // Inclusión de los recursos de E/S

/*
using namespace std;

int main(){
   double radio;     //Programa Principal (Introduciendo a mano el valor de PI)
   double area;
   double longitud;
   
   cout << "Introduzca la longitud del radio de la circunferencia: " ;
   cin >> radio;
   
   area = 3.1416*radio*radio ;
   cout << "\nEl área de la cincunferencia vale " << area << "\n\n" ;
   
   longitud = 2*3.1416*radio ;
   cout << "\nLa longitud de la circunferencia vale " << longitud << "\n\n" ;
}
*/

/*
using namespace std;

int main(){
   double radio;     //Programa Principal (Introduciendo a mano el valor de PI)
   double area;
   double longitud;
   
   cout << "Introduzca la longitud del radio de la circunferencia: " ;
   cin >> radio;
   
   area = 3.14159*radio*radio ;
   cout << "\nEl área de la cincunferencia vale " << area << "\n\n" ;
   
   longitud = 2*3.14159*radio ;
   cout << "\nLa longitud de la circunferencia vale " << longitud << "\n\n" ;
}
*/


using namespace std;

int main(){
   double radio;        // Programa Principal (Introduciendo PI como variable)
   double area;         // Declaración de las variables
   double longitud;     // radio, area, longitud y pi
   const double PI=3.1415927;
      
   cout << "Introduzca la longitud del radio de la circunferencia: " ;
   cin >> radio;
   
   area = PI*radio*radio ;
   cout << "\nEl área de la cincunferencia vale " << area << "\n\n" ;
   
   longitud = 2*PI*radio ;
   cout << "\nLa longitud de la circunferencia vale " << longitud << "\n\n" ;
   
   system("pause") ;
}

