
/*	
Programa que simula la devolucion de cambio de una maquina
*/
/*********************************************************************/

#include <iostream>
using namespace std;

int main()
{

   int precio, cantidad; // Datos de entrada
   int monedas_euro, monedas_50, monedas_20, monedas_10, monedas_5; // salidas
   int valor_pendiente;

   // Entrada
   cout << "\nIntroduce el precio (cent.): ";
   cin >> precio;
   cout << "\nIntroduce cantidad de dinero (cent.): ";
   cin >> cantidad;
   
   valor_pendiente = cantidad - precio; // calculo valor a devolver
   monedas_euro = valor_pendiente / 100; // calculo monedas de euro
   valor_pendiente = valor_pendiente - monedas_euro * 100; // actualizacion valor a devolver
   monedas_50 = valor_pendiente / 50; // monedas de 50
   valor_pendiente = valor_pendiente - monedas_50 * 50; // actualizacion valor a devolver
   monedas_20 = valor_pendiente / 20; // monedas de 20
   valor_pendiente = valor_pendiente - monedas_20 * 20; // actualizacion valor a devolver
   monedas_10 = valor_pendiente / 10; // monedas de 10
   valor_pendiente = valor_pendiente - monedas_10 * 10; // actualizacion valor a devolver
   monedas_5 = valor_pendiente / 5; // monedas de 5
   valor_pendiente = valor_pendiente - monedas_5 * 5; // actualizacion valor a devolver
    
    
   cout << "\nMonedas de euro:  " << monedas_euro;
   cout << "\nMonedas de 50 cent.: " << monedas_50;
   cout << "\nMonedas de 20 cent.:  " << monedas_20;
   cout << "\nMonedas de 10 cent.:  " << monedas_10;
   cout << "\nMonedas de 5 cent.:  " << monedas_5 << "\n";
}
