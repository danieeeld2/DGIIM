/* Programa para calular la distancia que han recorrido 
   dos locomotoras, las cuales viajan en sentidos contrarios 
   a velocidades constante, v1, v2.


*/

#include <iostream>

using namespace std;

int main (){
	
   double v1;              // Velocidad de la primera locomotora
   double v2;              // Velocidad de la segunda locomotora
   double dist_inicial;    // Distancia incial del 2 respecto al 1
   double tiempo;
   double dist1;           // Distancia recorrida por la primera locomotora
   double dist2;           // Distancia recorrida por la segunda locomotora
   
   cout << "Introduzca la velocidad de la primera locomotora en m/s: " ;
   cin >> v1 ;
   
   cout << "Introduzca la velocidad de la segunda locomotora en m/s: " ;
   cin >> v2 ;
   
   cout << "Introduzca la distancia inicial que separa a ambas locomotoras en metros: " ;
   cin >> dist_inicial ;
   
   tiempo = dist_inicial/(v1+v2) ;
   
   dist1 = v1*tiempo ;
   
   cout << "\nLa primera locomotora recorre: " << dist1 << "  metros" ;
   
   dist2 = v2*tiempo ;
   
   cout << "\n\nLa segunda locomotora recorre: " << dist2 << "  metros" << "\n\n" ;
   
   system ("pause");
}
