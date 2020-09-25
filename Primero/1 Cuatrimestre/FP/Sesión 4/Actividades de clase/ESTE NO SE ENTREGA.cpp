/*
   Leer 3 enteros.
   Calcular la media y la desviacion tipica.
   Decir, para cada valor, si esta por encima o por debajo de la media
*/

#include <iostream>
#include <cmath>
#include <string> 

using namespace std;

int main(){
    const string MENSAJE_ENTRADA_DATOS = "\nIntroduzca un valor de altura en cm --> ";
    const string MENSAJE_MENOR = " es menor o igual que su media\n";
    const string MENSAJE_MAYOR = " es mayor que su media\n";
    double altura1, altura2, altura3;
    double media, desviacion;
	double distancia_a_media_1, distancia_a_media_2, distancia_a_media_3;
    
    cout << MENSAJE_ENTRADA_DATOS;
    cin >> altura1;
    cout << MENSAJE_ENTRADA_DATOS;
    cin >> altura2;
    cout << MENSAJE_ENTRADA_DATOS;
    cin >> altura3;
    
    media = (altura1 + altura2 + altura3) / 3.0;
    distancia_a_media_1 = altura1 - media;
	distancia_a_media_2 = altura2 - media;
	distancia_a_media_3 = altura3 - media;

	desviacion = sqrt(	(	distancia_a_media_1 * distancia_a_media_1 +
									distancia_a_media_2 * distancia_a_media_2 +
									distancia_a_media_3 * distancia_a_media_3 
								) 
								/ 3.0
					      );
   
   cout << "\nMedia aritmetica: " << media;
   cout << "\nDesviacion tipica: " << desviacion;
   cout << "\n\n";
   
   /*
   Debemos usar tres condicionales seguidos.
   Dependiendo del resultado de la evaluacion de la condicion,
	se imprimira un mensaje u otro.
   */
   
   if (altura1 > media){
      cout <<  altura1 << MENSAJE_MAYOR;
   else
      cout <<  altura1 << MENSAJE_MENOR;
      
   if (altura2 > media)
      cout <<  altura2 << MENSAJE_MAYOR;
   else
      cout <<  altura2 << MENSAJE_MENOR;
   
   if (altura3 > media)
      cout <<  altura3 << MENSAJE_MAYOR;
   else
      cout <<  altura3 << MENSAJE_MENOR;   

   cout << "\n\n";   
}
