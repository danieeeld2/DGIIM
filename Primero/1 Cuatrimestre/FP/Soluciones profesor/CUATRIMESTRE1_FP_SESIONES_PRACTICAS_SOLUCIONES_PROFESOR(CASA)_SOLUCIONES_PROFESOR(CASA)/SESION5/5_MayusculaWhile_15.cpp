
/*
   Pasar un caracter de mayuscula a minuscula, pero leyendo el caracter
   con un filtro de entrada
*/

#include <iostream>
using namespace std;

int main(){
   const int DISTANCIA_MAY_MIN = 'a'-'A';             
   char letra_minuscula, letra_mayuscula;
   
   /*
   Algoritmo:
      Lee una letra, HASTA que sea una mayuscula, es decir, hasta que
      (letra_mayuscula >= 'A') && (letra_mayuscula <= 'Z') sea true

   Equivale a:
         
      Lee una letra, MIENTRAS que NO sea una mayuscula
      es decir, mientras que ! ((letra_mayuscula >= 'A') && (letra_mayuscula <= 'Z'))
      sea true
      es decir, mientras que !(letra_mayuscula >= 'A') || !(letra_mayuscula <= 'Z')
      sea true  (hemos aplicado las leyes de Morgan)
      es decir, mientras que (letra_mayuscula < 'A') || (letra_mayuscula > 'Z')
      sea true
   */
    
	/*
   do{
      cout << "\nIntroduzca una letra mayúscula  --> ";
      cin >> letra_mayuscula;
   }while ((letra_mayuscula < 'A') || (letra_mayuscula > 'Z'));
	*/

	/*
		En este tipo de bucles, en los que la condicion de continuacion
		es del tipo "mientras NO sea valido", podemos usar un bool
		dentro del bucle que facilite la lectura del codigo.
		En cualquier caso, tanto la solucion anterior como la siguiente
		son perfectamente validas.
	*/

	
	bool es_mayuscula;

	do{
      cout << "\nIntroduzca una letra mayúscula  --> ";
      cin >> letra_mayuscula;
      es_mayuscula = (letra_mayuscula >= 'A') && (letra_mayuscula <= 'Z');
   }while (! es_mayuscula);
   
   letra_minuscula = letra_mayuscula + DISTANCIA_MAY_MIN ;
   
   cout << "\nEl caracter " << letra_mayuscula
        << " pasado a minuscula es: " << letra_minuscula;
   
   cout << "\n\n";   
}
