
/*
El algoritmo de la multiplicacion rusa es una forma distinta de calcular la multiplicacion
de dos numeros enteros n y m. Para ello este algoritmo va multiplicando por 2 el
multiplicador m y dividiendo (sin decimales) por dos el multiplicando n hasta que
n tome el valor 1 y suma todos aquellos multiplicadores cuyos multiplicandos sean
impares. Por ejemplo, para multiplicar 37 y 12 se harian las siguientes iteraciones

Iteración Multiplicando Multiplicador
1 				37 				12
2 				18 				24
3 				9 				48
4 				4 				96
5 				2 				192
6 				1 				384
Con lo que el resultado de multiplicar 37 y 12 seria la suma de los multiplicadores
correspondientes a los multiplicandos impares (en negrita), es decir
37*12=12+48+384=444
Cread un programa para leer dos enteros n y m y calcule su producto utilizando este
algoritmo.
*/

#include <iostream>

using namespace std;

int main(){
	int multiplicando, multiplicador, factor1, factor2, producto;
	
	cout << "\nDime el multiplicando ";
	cin >> multiplicando;
	cout << "\nDime el multiplicador ";
	cin >> multiplicador;
	
	factor1 = multiplicando;
	factor2 = multiplicador;
    producto = 0;
		
	while( factor1 >= 1 ){
		if ( factor1 % 2 != 0 )
			producto = producto + factor2;
		factor1 = factor1 / 2;
		factor2 = factor2 * 2;
	}
	
    cout << "\nEl producto " << multiplicando << " * ";
    cout << multiplicador << " = " << producto << "\n";
}
