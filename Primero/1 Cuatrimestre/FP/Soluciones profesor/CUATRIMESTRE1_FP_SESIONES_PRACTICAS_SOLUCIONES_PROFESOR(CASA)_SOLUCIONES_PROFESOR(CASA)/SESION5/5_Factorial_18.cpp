
/*
   Computo del factorial y potencia de un numero.
   Factorial:
      n! = 1 si n=0
      n! = n(n-1)(n-2)...1 si n>=1
   Potencia:
      x^n = x x ... x  (n veces)
*/

/*
	Como el factorial de n es un numero mucho mas grande que n,
	usamos un long long para almacenar el resultado.
	Aun asi, el maximo factorial que podemos almacenar en un long long es el factorial de 20!!
	Factorial(20) = 2432902008176640000 

	Consultad esta web para realizar computos de factoriales con numeros grandes:
	http://www.nitrxgen.net/factorialcalc.php
*/

#include <iostream> 
using namespace std;  
   
int main(){    
    long long factorial;
	int numero;
	int multiplicando;

	cout << "\nIntroduzca un entero entre 0 y 20: ";
	cin >> numero;

	/*
	Algoritmo:

		Inicializar factorial a 1

		Recorrer los enteros entre 2 y n
        Acumular el producto de cada entero en factorial
	*/

	factorial = 1;

	for (multiplicando = 2; multiplicando <= numero ; multiplicando++)
		factorial = factorial * multiplicando;

	cout << "\nEl factorial de " << numero << " es " << factorial;

	/////////////////////////////////////////////////////////////

	double base;
	int exponente;
	double potencia;

	cout << "\n\nIntroduzca la base: ";
	cin >> base;
	cout << "\nIntroduzca el exponente: ";
	cin >> exponente;

	/*
	Algoritmo:

		Inicializar potencia a 1 (base ^ 0 = 1)

		Repetir tantas veces como diga el exponente
        Acumular el producto de base en potencia
	*/

	potencia = 1.0;

	for (int i = 1; i <= exponente; i++)
		potencia = potencia * base;

	cout << "\n" << base << " elevado a " << exponente << " es igual a " << potencia;

	// Observad que si exponente fuese cero, la variable potencia se quedaria con 1,
	// lo que es correcto ya que base elevado a 0 es siempre 1

    cout << "\n\n";
}
