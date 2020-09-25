/*	Programa para calcular el área de un triángulo.
	El usuario debe introducir la medida de los lados y
	el ángulo que estos forman.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main (){
   double a;      //Lado 1
   double b;      //Lado 2
   double angulo;
   double area;
   const double PI = 3.14159;
   
   cout << "Introduzca el valor del lado 1 en centímetros: " ;
   cin >> a;
   
   cout << "Introduzca el valor del lado 2 en centímetros: " ;
   cin >> b;
   
   cout << "Introducir el valor del ángulo que forman los dos lados en grados: " ;
   cin >> angulo ;
   
   area = (1.0/2.0)*a*b*sin(angulo * (PI/180.0)) ;	//	Pasamos los grados a radianes
   
   cout << "\nEl área vale: " << area << "\n\n" ;
   
   system ("pause");
}
   
