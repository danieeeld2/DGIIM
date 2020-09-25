/*	Programa para trabajar con una clase
	recta. 
	Apartado A: 
	Defiición de la clase,
	introducir los detos de la recta y cálculo
	de la pendiente
*/

#include<iostream>

using namespace std;

class Recta{
	private:
		double A, B, C;
	public:
		Recta(double coeficiente1, double coeficiente2, double coeficiente3){
			A = coeficiente1;
			B = coeficiente2;
			C = coeficiente3;
		}
		
		void SetRecta(double coeficiente1, double coeficiente2, double coeficiente3){
			A = coeficiente1;
			B = coeficiente2;
			C = coeficiente3;
		}
};
			
int main(){
	double coeficiente1, coeficiente2, coeficiente3;
	double coeficiente4, coeficiente5, coeficiente6;
	Recta Recta1(0,0,0);
	Recta Recta2(0,0,0);
	double pendiente1, pendiente2;
		
	cout << "\nIntroduce los coeficientes de la primera recta (Ax+By+C): ";
	cin >> coeficiente1 >> coeficiente2 >> coeficiente3;
	cout << "\nIntroduce los coeficientes de la segunda recta (Ax+By+C): ";
	cin >> coeficiente4 >> coeficiente5 >> coeficiente6;
	
	Recta1.SetRecta(coeficiente1, coeficiente2, coeficiente3);
	Recta2.SetRecta(coeficiente4, coeficiente5, coeficiente6);
	
	pendiente1 = -(coeficiente1 / coeficiente2);
	pendiente2 = -(coeficiente4 / coeficiente5);
	
	cout << "\nLa pendiente 1 es: " << pendiente1;
	cout << "\nLa pendiente 2 es: " << pendiente2;
	
	cout << "\n\n";
	system("pause");
}
	
