
/*
	Formulas Matematicas
*/

#include <iostream>   
#include <cmath>      

using namespace std; 

int main(){ 
/*
   Usamos nombres de variables cortos por su amplia aceptacion en Matematicas.
   Este ejercicio es una excepcion.
   Normalmente, usaremos nombres mas largos que indiquen su semantica.
*/
    const string SEPARADOR = "\n\n*******************************\n\n";
    const string MENSAJE_VALOR_FUNCION = "\nValor de la funcion: ";
    const string MENSAJE_VALOR_ABSCISA = "Introduzca el valor de la abscisa. ";
	double ordenada_funcion_1, ordenada_funcion_2, ordenada_funcion_3;
	double x, y, h;
	double base;
	
	cout << "Primera funcion.\n\n";
	cout << MENSAJE_VALOR_ABSCISA << "Primera coordenada: ";
	cin >> x;
	cout << MENSAJE_VALOR_ABSCISA << "Segunda coordenada: ";
	cin >> y;
	
	ordenada_funcion_1 = (1 + x * x / y) / (x * x * x / (1 + y));  // Tambien podriamos usar pow(x,3)
	
	cout << MENSAJE_VALOR_FUNCION << ordenada_funcion_1;
	
	cout << SEPARADOR;
    cout << "Segunda funcion.\n\n";
    cout << MENSAJE_VALOR_ABSCISA;
	cin >> h;
	
	ordenada_funcion_2 = (1  +  sin(h)/3.0  -  cos(h)/7.0) / (2*h);
	
	cout << MENSAJE_VALOR_FUNCION << ordenada_funcion_2;
	
	cout << SEPARADOR;
	cout << "Tercera funcion.\n\n";
    cout << MENSAJE_VALOR_ABSCISA;
	cin >> x;

	base = exp(x) / (x*x);
	ordenada_funcion_3 = sqrt(1 + base*base);
	
	cout << MENSAJE_VALOR_FUNCION << ordenada_funcion_3;
	
	cout << "\n\n";
	system("pause");
}


  
