/* Cread un programa que lea el valor de la edad (dato de tipo entero) y salario (dato de
tipo real) de una persona. Subid el salario un 5% si este es menor de 300 euros y la
persona es mayor de 65 a–os. Imprimid el resultado por pantalla. En caso contrario
imprimid el mensaje "No es aplicable la subida". En ambos casos imprimid
el salario resultante.
Realizad el mismo ejercicio pero subiendo el salario un 4% si es mayor de 65 o menor
de 35 a–os. Ademas, si tambien tiene un salario inferior a 300 euros, se le subira otro
3%.
*/

#include <iostream>

using namespace std;

int main(){
	int edad;
	double salario, salario_final; // la segunda para no variar datos iniciales
	bool salario_bajo;
	bool mayor_edad;
	bool menor_de_35;
	cout << "\n Dime la edad \n";
	cin >> edad;
	cout << "\n Dime el salario \n";
	cin >> salario;
	
	salario_bajo = salario < 300; // almacenamos las posibilidades en variables bool
	mayor_edad = edad > 65;
	menor_de_35 = edad < 35;
	
	if(salario_bajo && mayor_edad){
	 	salario_final = salario + (salario*5)/100;
	 	cout << "\n\n Salario Final = " << salario_final << endl;
	}		
	else
		cout << "\n\n No es aplicable la subida \n\n";
    
    /* Separacion, el porcentaje de subida es lo que cambia...
     
     bool aumento = salario_bajo && mayor_edad;
     double porcentaje = 1;
     
     if(aumento)
        porcentaje = 1.05;
     
     salario_final = salario * porcentaje;
     
     if (aumento)
        cout << "\n\n Salario Final = " << salario_final << endl;
     else
        cout << "\n\n No es aplicable la subida \n\n";
    
    */
    
	cout << "**************\n\n";
	cout << "\n\n Segunda opcion \n\n";
	
	if(mayor_edad || menor_de_35) {
		if(salario_bajo)	{
			salario_final = salario +  (salario*7)/100;
			cout << "\n\n Salario Final = " << salario_final << endl;
		}
		else{
			salario_final = salario + (salario*4)/100;
			cout << "\n\n Salario Final = " << salario_final << endl;
		}
	}	
	else
		cout << "\n\n No es aplicable la subida \n\n";
    
    /* // Separacion, almacenamos las posibilidades en el cambio de porcentaje de subida
       // es un programa que se generaliza mejor, y si hubiera muchas m‡s posibilidades?
     
     bool aumento = mayor_edad || menor_35
     double porcentaje = 1
     
     if (aumento)
        if (salario_bajo)
            porcentaje = 1.07;
        else
            porcentaje = 1.04;
     
     salario_final = salario * porcentaje;
     
     if(aumento)
        cout << "\n\n Salario Final = " << salario_final << endl;
     else
        cout << "\n\n No es aplicable la subida \n\n";
     
    */
		
	return 0;
}
