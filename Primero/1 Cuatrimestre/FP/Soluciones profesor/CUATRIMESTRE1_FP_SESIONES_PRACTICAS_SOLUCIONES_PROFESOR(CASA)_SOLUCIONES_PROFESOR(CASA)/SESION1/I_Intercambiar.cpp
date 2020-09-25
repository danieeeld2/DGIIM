/*
   Programa que intercambia el valor de valor de dos variables enteras
   Entradas: El valor de las variables enteras
   Salidas:  El valor de las variables, pero intercambiadas x->y, x->y
*/
/*********************************************************************/

#include <iostream>

using namespace std;

int main()
{
    
	int edad_Pedro, edad_Juan;   // Entradas
   
	cout << "\nIntroduzca la edad de Pedro : ";
	cin >> x;
	cout << "\nIntroduzca la edad de Juan : ";
	cin >> y;

    cout << "\nANTES de intercambiar los valores, la edad de Pedro es " << edad_Pedro;
    cout << " y la de Juan, " << edad_Juan;
    
    int edad_Pedro_copia; // variable auxiliar para almacenar edad_Pedro temporalmente
    
    edad_Pedro_copia=edad_Pedro;
    edad_Pedro=edad_Juan; // se cambia el valor de edad_Pedro,
                          // si no lo hubiera guardado en edad_Pedro_copia
                        // se habr’a perdido,
                        // por eso no funciona el c—digo del enunciado
    edad_Juan=edad_Pedro_copia;
    
    cout << "\nDESPUES de intercambiar los valores, la edad de Pedro es " << edad_Pedro;
    cout << " y la de Juan, " << edad_Juan;
}
