/*
 Calculo del area de un triangulo
 */

#include <iostream>
#include <cmath>

using namespace std;

int main(){
	double lado1, lado2, angulo, area;
	const double PI = 3.1416;
	
	cout << "\nIntroduzca el valor del primer lado: " ;
	cin >> lado_a ;
	cout << "\nIntroduzca el valor del segundo lado: " ;
	cin >> lado_b ;
	cout << "\nIntoduzca el angulo que forman ambos lados: " ;
	cin >> angulo ;
	
	
	angulo = (2*PI*angulo) / 360 ; // Todos son double, no hay problema de division
	lado_a = lado_a / 100 ;
	lado_b = lado_b / 100 ;
	
	area = lado_a * lado_b * sin(angulo) / 2 ;
	
	
	cout << "\nEl area del triangulo es: " << area << endl ;
}
