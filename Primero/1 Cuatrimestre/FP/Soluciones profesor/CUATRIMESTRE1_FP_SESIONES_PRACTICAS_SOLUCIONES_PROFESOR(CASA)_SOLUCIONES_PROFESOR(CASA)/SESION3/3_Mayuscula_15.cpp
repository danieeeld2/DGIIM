
/*
   Pasar un caracter de mayuscula a minuscula.
*/

#include <iostream>
using namespace std;

int main(){
   /*
   Las mayusculas estan antes que las minusculas en la tabla ASCII.
   Ademas, sabemos que hay el mismo numero de mayusculas que de
   minusculas y obviamente se encuentran en el mismo orden. Por
   tanto, solo necesitamos saber cuantos caracteres hay entre
   'A' y 'a'.

   El orden de 'A' es 65 y el de 'a' 97.
   Por tanto, hay 97-65 = 32 caracteres entre ellos.
   Asi pues, bastaria hacer letra_minuscula = letra_mayuscula + 32

   Problema: Debo conocer el numero "magico" 32.
	Muy posiblemente se me olvide cuando lo necesite en otro programa.	
	*/

	/*
	char letra_minuscula, letra_mayuscula;

   cout << "\nIntroduzca una letra mayúscula  --> ";
   cin >> letra_mayuscula;

   letra_minuscula = letra_mayuscula + 32;      // :-(

   cout << "\nEl caracter " << letra_mayuscula
        << " pasado a minuscula es: " << letra_minuscula;

	*/

	/*
	Solo necesitamos saber cuantos caracteres hay entre 'A' y 'a'.
   Dicho valor me lo da la operacion 'a'-'A', que devuelve 32.
   Obviamente tambien valdria 'b'-'B' o 'c'-'C' ....

   Observad que este metodo tambien funcionaria si las mayusculas
   estuviesen despues de las minusculas en la tabla ASCII
	*/

   char letra_minuscula, letra_mayuscula;
   const int DISTANCIA_MAY_MIN = 'a'-'A';             // :-)

   cout << "\nIntroduzca una letra mayuscula  --> ";
   cin >> letra_mayuscula;

   letra_minuscula = letra_mayuscula + DISTANCIA_MAY_MIN;      // :-)

   cout << "\nEl caracter " << letra_mayuscula
    << " pasado a minuscula es: " << letra_minuscula;

   cout << "\n\n";
}
