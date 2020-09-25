
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
      Lee una letra, HASTA que sea una mayúscula,

      es decir, hasta que (letra_mayuscula >= 'A') && (letra_mayuscula <= 'Z')
      sea true

   Equivale a:
         
      Lee una letra, MIENTRAS que NO sea una mayúscula
      
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
		En este tipo de bucles, en los que la condición de continuación
		es del tipo "mientras NO sea válido", podemos usar un bool
		dentro del bucle que facilite la lectura del código.
		En cualquier caso, tanto la solución anterior como la siguiente
		son perfectamente válidas.
	*/

	
	bool es_mayuscula;

	do{
      cout << "\nIntroduzca una letra mayúscula  --> ";
      cin >> letra_mayuscula;
		es_mayuscula = (letra_mayuscula >= 'A') && (letra_mayuscula <= 'Z');
   }while (! es_mayuscula);
   
   letra_minuscula = letra_mayuscula + DISTANCIA_MAY_MIN ;
   
   cout << "\nEl carácter " << letra_mayuscula  
        << " pasado a minúscula es: " << letra_minuscula;
   
   cout << "\n\n";   
   system("pause");
}
