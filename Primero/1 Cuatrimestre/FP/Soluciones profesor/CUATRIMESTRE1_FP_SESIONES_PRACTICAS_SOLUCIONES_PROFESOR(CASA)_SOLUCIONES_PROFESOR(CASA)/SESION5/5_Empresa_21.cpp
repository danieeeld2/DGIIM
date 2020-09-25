
/*
Una empresa que tiene tres sucursales decide llevar la contabilidad de las ventas
de sus productos a lo largo de una semana. Para ello registra cada venta con tres
numeros, el identificador de la sucursal (1,2 o 3), el codigo del producto (1, 2 o 3) y
el numero de unidades vendidas. Dise–ar un programa que lea desde el teclado una
serie de registros compuestos por sucursal, producto, unidades y diga cual
es la sucursal que mas productos ha vendido. La serie de datos termina cuando la
sucursal introducida vale -1. Por ejemplo, con la serie de datos
1 2 10
1 2 4
1 1 1
1 1 1
1 3 2
2 2 15
2 2 6
2 1 20
3 3 40
-1
Se puede ver que la sucursal que mas productos ha vendido es la numero 2 con
41 unidades totales. La salida del programa debera seguir exactamente el siguiente
formato:

SUCURSAL: 2
VENTAS: 41

Para comprobar que el programa funciona correctamente, cread un fichero de texto y
re-dirigid la entrada a dicho fichero.
*/


#include <iostream> 
#include <string>  

using namespace std;
    
int main(){  	
    const int TERMINADOR = -1;
    int identif_sucursal,  identif_sucursal_max_ventas, cod_producto, unidades_vendidas;
    int num_ventas_1, num_ventas_2, num_ventas_3, num_max_ventas;
    string mensaje_entrada;
   
    mensaje_entrada = "\nSe procede a leer datos del fichero ... \n";
    cout << mensaje_entrada;
   
    num_max_ventas = num_ventas_1 = num_ventas_2 = num_ventas_3 = 0;
    identif_sucursal_max_ventas = 0;   // Por si no se introduce ninguna sucursal valida
   
    /* Algoritmo:
      
      Mientras que la sucursal sea distinto a -1
         Leer datos de la sucursal
         Actualizar numero de unidades vendidas de la sucursal que se haya introducido
         Actualizar el Maximo (de numero de ventas con la correspondiente sucursal)
     */

    cin >> identif_sucursal;
   
    while (identif_sucursal != TERMINADOR){
      cin >> cod_producto;
      cin >> unidades_vendidas;
      
      if (identif_sucursal == 1)
         num_ventas_1 = num_ventas_1 + unidades_vendidas;
      else if (identif_sucursal == 2)
         num_ventas_2 = num_ventas_2 + unidades_vendidas;
      else if (identif_sucursal == 3)
         num_ventas_3 = num_ventas_3 + unidades_vendidas;
      
      if (num_ventas_1 > num_max_ventas){
         num_max_ventas = num_ventas_1;  
         identif_sucursal_max_ventas = 1;
      }       
      else if (num_ventas_2 > num_max_ventas){
         num_max_ventas = num_ventas_2;  
         identif_sucursal_max_ventas = 2;
      }       
      else if (num_ventas_3 > num_max_ventas){
         num_max_ventas = num_ventas_3;  
         identif_sucursal_max_ventas = 3;
      }        
		// Si identif_sucursal es distinto de 1,2,3 no actualiza ningún num_ventas_i
      
      cin >> identif_sucursal;      
   }
   
   cout << "\nSUCURSAL: " << identif_sucursal_max_ventas;
   cout << "\nVENTAS: " << num_max_ventas << "\n";
   
}
