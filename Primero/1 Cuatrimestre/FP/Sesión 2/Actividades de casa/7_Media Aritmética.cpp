/*	Programa para calcular la media aritmética muestral y la desviación
	estándar de la altura de tres personas
	Necesitamos: La altura de cada persona
	Calcula: La media aritmética muestral y la desviación estándar
*/

/*	La función a implementar es:
         1    N
         -  media = --- suma (x_i)
         N   i=1
                            ________________________________
                           /   1     N                   
            desviacion =  / ( ---  suma  (x_i - media)^2 )
                         V     N    i=1                
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
	double altura_1;
	double altura_2;
	double altura_3;
	double media;
	double desviacion;
	const double personas = 3;		//	Definimos n como constante
	
	cout << "Introduce la altura de la primera persona: " ;
	cin >> altura_1 ;
	
	cout << "Introduce la altura de la segunda persona: " ;
	cin >> altura_2 ;
	
	cout << "Introduce la altura de la tercera persona: " ;
	cin >> altura_3 ;
	
	media = (altura_1 + altura_2 + altura_3)/personas ;
	
	cout << "\nLa media vale: " << media ;
	
	desviacion = sqrt( (1/personas) * ( pow((altura_1 - media),2) + pow((altura_2 - media),2) + pow((altura_3 - media),2) ) ) ;
	
	cout << "\nLa desviación vale: " << desviacion << "\n" ;
	
	system ("pause");
}
	
