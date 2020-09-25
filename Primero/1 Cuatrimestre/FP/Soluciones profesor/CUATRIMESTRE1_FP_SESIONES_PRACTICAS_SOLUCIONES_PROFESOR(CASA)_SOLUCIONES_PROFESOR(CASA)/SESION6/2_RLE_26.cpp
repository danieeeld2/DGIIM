
/*
   El metodo RLE (Run Length Encoding) codifica una secuencia de datos formada por
   series de valores identicos consecutivos como una secuencia de parejas de numeros
   (valor de la secuencia y numero de veces que se repite). Esta codificacion es un
   mecanismo de compresion de datos (zip) sin perdidas. Se aplica, por ejemplo, para
   comprimir los ficheros de imagenes en las que hay zonas con los mismos datos (fondo
   blanco, por ejemplo). Realizar un programa que lea una secuencia de numeros
   naturales terminada con un numero negativo y la codifique mediante el metodo RLE.

   Entrada: 1 1 1 2 2 2 2 2 3 3 3 3 3 3 5 -1   
   Salida: 3 1 5 2 6 3 1 5
          (tres veces 1, cinco veces 2, seis veces 3, una vez 5)
*/

#include <iostream> 
using namespace std;  
   
int main(){    
	const int TERMINADOR = -1;	
   int actual, anterior, iguales_hasta_ahora;

   /*
      Idea:
         Llevar dos variables actual y anterior que "apunten"
         al valor leido en un momento dado y al valor anterior, respectivamente.

      Descripcion del algoritmo:

      Mientras que el actual no sea el terminador 
         Avanzar anterior y actual

         Si son iguales
            incrementar la longitud de la secuencia actual
         si no
            Imprimir el anterior junto con la longitud de la secuencia
            y resetear el contador de la longitud actual
            
   */

	cin >> actual;
	iguales_hasta_ahora = 1;

	while (actual != TERMINADOR){     
		anterior = actual;      
		cin >> actual;

		if (anterior == actual)
			iguales_hasta_ahora++;
		else{
			cout << iguales_hasta_ahora << " " << anterior << " ";      
			iguales_hasta_ahora = 1;
		}
	}   

	cout << "\n\n";
}
