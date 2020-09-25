
/*
 Un numero perfecto es aquel que es igual a la suma de todos sus divisores positivos excepto
 el mismo. El primer numero perfecto es el 6 ya que sus divisores son 1, 2 y 3 y 6 = 1+2+3.
 Escribir un programa que muestre el mayor numero perfecto que sea menor a un numero dado
 por el usuario.

*/

#include <iostream>

using namespace std;

int main (){
    int numero, perfecto, maximo_perfecto = 0, divisor, maximo_divisor, suma;

    cout << "\nIntroduce un numero: ";
    cin >> numero;
    
    /*ALGORITMO:
		-> Bucle FOR: Examina todos los candidatos a ser números perfectos desde el 6 hasta tope.
		   -> Inicialización de divisor en 1, suma en 0, y cálculo de máximo divisor de cada perfecto candidato.
		   -> While: Mientras divisor sea menor o igual que el máximo:
		   	  -> Si el perfecto es divisible por ese divisor, se añade divisor a la suma
		   	  -> Incrementa en 1 el divisor
  		   -> If: Si la suma es igual a perfecto, existe perfecto:
			  	  -> If: Si el perfecto encontrado es mayor que otro anterior:
			  	  	 	 -> Se cambia el máximo perfecto por ese*/
    
    for (int perfecto = 6; perfecto < numero; perfecto++){
     
        divisor = 1;
        maximo_divisor = perfecto / 2;
        suma = 0;
        
        while ( divisor <= maximo_divisor ){
            if ( perfecto % divisor == 0 )
                suma = suma + divisor;
            divisor++;
        }
    
        if ( suma == perfecto )
            if ( perfecto > maximo_perfecto )
                maximo_perfecto = perfecto;
    }
    
    cout << "El maximo perfecto es: " << maximo_perfecto << "\n\n";
}
