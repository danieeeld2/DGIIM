/*	Programa para trabajar con polinomios de grado 3
	máximo 
*/

#include <iostream>

using namespace std;

struct Polinomio{
	double incognita;
	double termino_independiente;
	double coeficiente1;
	double coeficiente2;
	double coeficiente3;
	double imagen;
};

int main(){
		
	//	A: Inicializar un polinomio a partir de los coeficientes dados por valores desde teclado.
	
	Polinomio polinomio1;
	
	cout << "Introducir polinomio de grado máximo 3" ;
	
	cout << "\nIntroducir coeficiente de x^3: " ;
	cin >> polinomio1.coeficiente3 ;
	cout << "\nIntroducir coeficiente de x^2: " ;
	cin >> polinomio1.coeficiente2 ;
	cout << "\nIntroducir coeficiente de x: " ;
	cin >> polinomio1.coeficiente1 ;
	cout << "\nIntroducir término independiente: " ;
	cin >> polinomio1.termino_independiente ;
	
	if ( polinomio1.coeficiente3 == 0 ){
		
		if ( polinomio1.coeficiente2 == 0 )
			cout << "\n\nEl polinomio es: " << polinomio1.coeficiente1 << "x + " << polinomio1.termino_independiente ;
			
		else
			cout << "\n\nEl polinomio es: " << polinomio1.coeficiente2 << "x^2 + " << polinomio1.coeficiente1 << "x + " << polinomio1.termino_independiente ;
			
	}
	
	else
	cout << "\n\nEl polinomio es: " << polinomio1.coeficiente3 << "x^3 + " << polinomio1.coeficiente2 << "x^2 + " << polinomio1.coeficiente1 << "x + " << polinomio1.termino_independiente ;
	
	// B: Sumar dos polinomios
	
		Polinomio polinomio2;
		Polinomio suma; 
		
	cout << "\n\nIntroducir un nuevo polinomio" ;
	
	cout << "\nIntroducir coeficiente de x^3: " ;
	cin >> polinomio2.coeficiente3 ;
	cout << "\nIntroducir coeficiente de x^2: " ;
	cin >> polinomio2.coeficiente2 ;
	cout << "\nIntroducir coeficiente de x: " ;
	cin >> polinomio2.coeficiente1 ;
	cout << "\nIntroducir término independiente: " ;
	cin >> polinomio2.termino_independiente ;
	
	if ( polinomio2.coeficiente3 == 0 ){
		
		if ( polinomio2.coeficiente2 == 0 )
			cout << "\n\nEl polinomio es: " << polinomio2.coeficiente1 << "x + " << polinomio2.termino_independiente ;
			
		else
			cout << "\n\nEl polinomio es: " << polinomio2.coeficiente2 << "x^2 + " << polinomio2.coeficiente1 << "x + " << polinomio2.termino_independiente ;
			
	}
	
	else
	cout << "\n\nEl polinomio es: " << polinomio2.coeficiente3 << "x^3 + " << polinomio2.coeficiente2 << "x^2 + " << polinomio2.coeficiente1 << "x + " << polinomio2.termino_independiente ;
	
	cout << "\n\nLa suma de polinomios se realiza término a término " ;
	
	suma.coeficiente3 = polinomio1.coeficiente3 + polinomio2.coeficiente3 ;
	suma.coeficiente2 = polinomio1.coeficiente2 + polinomio2.coeficiente2 ;
	suma.coeficiente1 = polinomio1.coeficiente1 + polinomio2.coeficiente1 ;
	suma.termino_independiente = polinomio1.coeficiente1 + polinomio2.termino_independiente ;
	
	cout << "\n\nLa suma sería: " ,
	cout << suma.coeficiente3 << "x^3 + " << suma.coeficiente2 << "x^2 + " << suma.coeficiente1 << "x + " << suma.termino_independiente ;
	
	//	C Evaluar la función en x
	
	cout << "\n\nPara el primer polinomio, dadle un valor a x : " ;
	cin >> polinomio1.incognita ;
	
	//	Para que quede más limpio vamos a hacerlo por partes
	
	double parte3;
	double parte2;
	double parte1;
	
	parte3 = polinomio1.coeficiente3 * polinomio1.incognita * polinomio1.incognita * polinomio1.incognita ;	//	Evitamos la función pow, ya que es lenta de inicializar
	parte2 = polinomio1.coeficiente2 * polinomio1.incognita * polinomio1.incognita ;
	parte1 = polinomio1.coeficiente1 * polinomio1.incognita ;
	
	polinomio1.incognita = parte3 + parte2 + parte1 + polinomio1.termino_independiente ;
	
	cout << "\n\nLa primera función en x = " << polinomio1.incognita << " vale: " << polinomio1.incognita << "\n\n" ,
	
	system ("pause") ;
}
	
	
	
