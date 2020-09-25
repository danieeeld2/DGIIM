
/*
   Programa que calcula el reparto de beneficios entre cuatro destinatarios,
   siendo las proporciones diferentes: el destinatario 1 (dise–ador) recibe
   el doble que los otros tres (fabricantes).

   Entradas: beneficio a repartir
   Salidas:  ganancia del dise–ador y ganancia de los fabricantes
*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main(){
	double beneficio; 	// Dato de entrada

	cout << "\nIntroduzca beneficio obtenido: ";
	cin >> beneficio;

/*
	En esta primera solucion se ofrece la salida pedida,
	pero tiene dos inconvenientes:

	1.	Repetimos el calculo beneficio/5 dos veces.
		Repetir codigo es propenso a errores ya que cualquier actualizacion en el futuro
        nos obliga a modificar todas las instrucciones que contienen dichas repeticiones.

	2.	En la misma sentencia de salida de resultados realizamos los computos.
		Debemos separar las entradas de datos de los computos y de las
		salidas de resultados.
*/

	cout << "\nGanancia de cada fabricante: " << beneficio/5;        // :-(
	cout << "\nGanancia del dise–ador: "      << 2 * beneficio/5;    // :-(
	cout << "\n\n";

	// Lo arreglamos a–adiendo dos variables y realizando los calculos
	// antes de mostrar los resultados.

	double ganancia_diseniador, ganancia_fabricante;  // Datos de salida

	ganancia_fabricante = beneficio/5;
	ganancia_diseniador = 2 * ganancia_fabricante;

	cout << "\nGanancia de cada fabricante: " << ganancia_fabricante;        // :-)
	cout << "\nGanancia del dise–ador: "      << ganancia_diseniador;        // :-)
	cout << "\n\n";

	// Si tuviesemos que modificar el numero de fabricantes de 5 a 6, por ejemplo,
	// bastaria con modificar una unica linea
	//		ganancia_fabricante = beneficio/5;  --> ganancia_fabricante = beneficio/6;
	// mientras que en la solucion inicial, como repetiamos codigo,
	// habia que cambiarlo en dos sitios distintos.

	// Nota: Si el numero de fabricantes es un dato que puede cambiar
	// de una ejecucion a otra del programa, entonces, tendriamos que
	// haber usado una variable y leerla desde el teclado (dispositivo de entrada de datos):

	// double num_fabricantes;
	// cin >> num_fabricantes;
	// ...
	// ganancia_fabricante = beneficio / num_fabricantes;
}
