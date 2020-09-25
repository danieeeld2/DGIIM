/* Programa para traducir una serie de fórmulas a expresiones
	válidas del lenguaje C++   
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   
   // Primera función
   
   double x;
   double y;
   double imagen;
   
   cout << "\nProcedemos con la primera función" ;
   
   cout << "\n\nIntroduce el valor de x: " ;
   cin >> x ;
   
   cout << "\nIntroduce el valor de y: " ;
   cin >> y ; 
   
   imagen = ( 1 + ( pow(x,2) / y) ) / (pow(x,3) / (1+y) ) ;
   
   cout << "\nLa imágen para la primera función es: " << imagen ;
   
   // Segunda funcón
   
   double h;
   double imagen2;
   
   cout << "\n\nProdecemos con la segunda función" ;
   
   cout << "\n\nIntroduzca el valor de h: " ;
   cin >> h ;
   
   imagen2 = (1 + (1.0/3.0)*sin(h) - (1.0/7.0)*cos(h)) / (2*h) ;  //Si pones 1/3 da un entero y redondea el resultado
   
   cout << "\nLa imágen par la segunda función es: " << imagen2 ;
   
   // Tercera funión
   
   double z;
   double imagen3; 
   
   cout << "\n\nProcedemos con la tercera función" ;
   
   cout << "\n\nIntroduzca el valor de z: " ; 
   cin >> z ;
   
   imagen3 = sqrt (1 + pow( (exp(z)/(z*z)) , 2) ) ;
   
   cout << "\nLa imágen de la tercera función es: " << imagen3 << "\n\n" ;
   
   system ("pause");
}
