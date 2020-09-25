
/*	
   Programa que calcula e imprime el valor de una gaussiana, dados 
   sus par‡metros (desviaci—n t’pica y esperanza)
   Entradas: par‡metros de la gaussiana (desviacion, esperanza) y
			 la abscisa (x)
   Salidas:  El valor de la ordenada (y), calculada mediante: 

	                                            {        (x-esperanza)^2 }
							                          { -0.5 * (-----------)   }
	                        1                   {        ( desviacion)   }
				y = ----------------------  * e                  
	                            ______
				     desviacion * V 2*PI     
*/
/*********************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	const double PI = 3.1415927; 

	double esperanza, desviacion, x;   // Entrada
	double y;	                       // Salida
	double valor_tipificado, exponente;
   
	cout << "\nIntroduzca el valor del parametro 'esperanza' : ";
	cin >> esperanza;
	cout << "\nIntroduzca el valor del parametro 'desviacion' : ";
	cin >> desviacion;
	cout << "\nIntroduzca el valor de la abscisa: ";
	cin >> x;

   /*
		Observad que no puedo poner  (1/2) * pow( ...) ya que 1 y 2 son literales enteros, 
		por lo que / es la division entera y 1/2 es 0 (esto se ver en el primer tema)
	 	Por eso multiplicamos por 0.5
	*/

	/*
		Para elevar al cuadrado (x - esperanza) / desviacion tenemos las siguientes posibilidades:

		a) ( (x - esperanza) / desviacion ) * ( (x - esperanza) / desviacion )
			Esta solucion no es adecuada ya que repite la evaluacion
			de la misma expresion (x - esperanza) / desviacion dos veces
			Esto es ineficiente y propenso a errores como siempre que se repite codigo.
	
		b) pow ((x - esperanza)/desviacion, 2)
			No repetimos codigo, pero el uso de pow conlleva una recarga computacional importante.
			Si solo vamos a elevar al cuadrado, mejor evitamos el uso de pow.
	
		c) Usando una variable intermedia para almacenar el resultado de la expresion que se va a repetir:
			valor_tipificado = (x - esperanza) / desviacion
			exponente = -0.5 * valor_tipificado * valor_tipificado
	*/
	
	
	/*
		Sobre los nombres de los datos:
			Evitad el uso de nombres de variables genericos: aux, tmp
			En este ejemplo, valor_tipificado es el nombre con el que en Estadistica se conoce
			a la operacion de calcular la distancia de x a la media y ponderar con respecto a la desviacion tipica
	*/

	valor_tipificado = (x - esperanza) / desviacion;
	exponente = -0.5 * valor_tipificado * valor_tipificado;

	y = exp(exponente) / ( desviacion * sqrt(2*PI) );    
   
   /*
		Para dividir por desviacion * sqrt(2*PI) debemos usar parentesis
		ya que / y * tienen la misma precedencia y por tanto se evaluan segun la asociatividad
		de estos operadores, que es de izquierda a derecha (esto se ve en el primer tema)
		Por lo tanto, 
			exp(exponente) / desviacion * sqrt(2*PI); 
		seria, realmente:
			(exp(exponente) / desviacion) * sqrt(2*PI);
		lo cual es incorrecto.
	*/

	cout << "\n\nEl valor de la funcion gaussiana en " << x << " es " << y;
	cout << "\n\n";
}
