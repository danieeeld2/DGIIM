/*	Programa para trabajar con estructuras
	que represente a números racionales
*/

#include <iostream>
#include <algorithm>

using namespace std;

struct Racional{
	int variable_x;
	int variable_y;
};

int main(){
	
	//	A Inicializar un número racional desde el teclado
	
	Racional racional1;
	
	cout << "Introduzca el valor del numerador: " ;
	cin >> racional1.variable_x ;
	
	cout << "\nIntroduzca el valor del denominador: " ;
	cin >> racional1.variable_y ;
	
	cout << "\nEl número racional introducido es: " << racional1.variable_x << "/" << racional1.variable_y ;
	
	//	B Simplificar un número racional a su fracción irreducible
	
	int comun_divisor;
	Racional simplificado;
	
	cout << "\n\nVamos a simplificar el racional" ;
	
	comun_divisor = __gcd (racional1.variable_x , racional1.variable_y ) ;
	
	simplificado.variable_x = racional1.variable_x / comun_divisor ;
	simplificado.variable_y = racional1.variable_y / comun_divisor ;
	
	if ( comun_divisor != 1 ){
		
		if ( simplificado.variable_y == 1)		
			cout << "\nEl racional simplificado es: " << simplificado.variable_x ;
			
		else		
			cout << "\nEl racional simplificado es: " << simplificado.variable_x << "/" << simplificado.variable_y ;
	}
	
	else
		cout << "\nEl número es irreducible " ;
		
	//	C Suma dos numeros racionales
	
	Racional racional2;
	Racional suma;
	int comun_divisor_2;
	Racional suma_simplificada;
	
	cout << "\n\nIntroduzca un nuevo número racional para sumarselo al primero" ;
	
	cout << "\nIntroduzca el valor del numerador: " ;
	cin >> racional2.variable_x ;
	
	cout << "\nIntroduzca el valor del denominador: " ;
	cin >> racional2.variable_y ;
	
	cout << "\nEl segundo racional es: " << racional2.variable_x << "/" << racional2.variable_y ;
	
	suma.variable_x = (racional1.variable_x * racional2.variable_y) + (racional2.variable_x + racional1.variable_y ) ;
	suma.variable_y = racional1.variable_y * racional2.variable_y ;
	
	comun_divisor_2 = __gcd ( suma.variable_x , suma.variable_y ) ;

	suma_simplificada.variable_x = suma.variable_x / comun_divisor_2 ;
	suma_simplificada.variable_y = suma.variable_y / comun_divisor_2 ;
	
	cout << "\nEl resultado de la suma (simplificada si fuera posible) es: " << suma_simplificada.variable_x << "/" << suma_simplificada.variable_y ;
	
	//	D Multiplicar dos racionales
	
	Racional racional3;
	Racional multiplicacion;
	Racional multiplicacion_simplificada;
	int comun_divisor_3;
	
	cout <<"\n\nIntroduzca un nuevo racional para multiplicarlo con el primero" ;
	
	cout << "\nIntroduzca el valor del numerador: " ;
	cin >> racional3.variable_x ;
	
	cout << "\nIntroduzca el valor del denominador: " ;
	cin >> racional3.variable_y ;
	
	multiplicacion.variable_x = racional1.variable_x * racional3.variable_x ;
	multiplicacion.variable_y = racional1.variable_y * racional3.variable_y ;
	
	comun_divisor_3 = __gcd ( multiplicacion.variable_x , multiplicacion.variable_y ) ;
	
	multiplicacion_simplificada.variable_x = multiplicacion.variable_x / comun_divisor_3 ;
	multiplicacion_simplificada.variable_y = multiplicacion.variable_y / comun_divisor_3 ;
	
	cout << "\nLa multiplicación (simplificada si se pudiera es: " ;
	cout << multiplicacion_simplificada.variable_x << "/" << multiplicacion_simplificada.variable_y ;
	
	//	E Evaluar un numero racional
	
	Racional racional4;
	double division;
	
	cout <<"\n\nIntroduzca un nuevo racional para evaluarlo" ;
	
	cout << "\nIntroduzca el valor del numerador: " ;
	cin >> racional4.variable_x ;
	
	cout << "\nIntroduzca el valor del denominador: " ;
	cin >> racional4.variable_y ;
	
	division = (double)racional4.variable_x / racional4.variable_y ;
	
	cout << "\nLa division del numerador entre el denominador es: " << division << "\n\n" ;
			
	system ("pause");
}
	
		
	
		
	
	
