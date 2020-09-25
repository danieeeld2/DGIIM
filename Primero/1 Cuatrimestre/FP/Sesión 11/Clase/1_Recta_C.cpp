/*	Programa para trabajar con una clase
	recta. 
	Apartado B: 
	Defiición de la clase,
	introducir los detos de la recta y cálculo
	de la pendiente, pero esta vez como método
	público.
	Además, obterner la ordenada y abcisa;
	dado un x y un y;	
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
		
		double Pendiente(){
			double pendiente;
			pendiente = - (A / B);
			
			cout << "\nLa pendiente de la recta es: " << pendiente;
			
			return pendiente;
		}
};
			
int main(){
	double coeficiente1, coeficiente2, coeficiente3;
	double coeficiente4, coeficiente5, coeficiente6;
	Recta Recta1(0,0,0);
	Recta Recta2(0,0,0);
	double x, y;
	double ordenada, abcisa;
		
	cout << "\nIntroduce los coeficientes de la primera recta (Ax+By+C): ";
	cin >> coeficiente1 >> coeficiente2 >> coeficiente3;
	cout << "\nIntroduce los coeficientes de la segunda recta (Ax+By+C): ";
	cin >> coeficiente4 >> coeficiente5 >> coeficiente6;
	
	Recta1.SetRecta(coeficiente1, coeficiente2, coeficiente3);
	Recta2.SetRecta(coeficiente4, coeficiente5, coeficiente6);
	
	Recta1.Pendiente();
	Recta2.Pendiente();	
	
	cout << "\n\nIntroduce un valor de x para la primera recta: ";
	cin >> x;
	
	ordenada = (-coeficiente3 -x * coeficiente1) / coeficiente2;
	
	cout << "\nLa ordenada para x = " << x << " es: " << ordenada;
	
	cout << "\nIntroduce un valor de y para la primera recta: ";
	cin >> y;
	
	abcisa = (-coeficiente3 -y * coeficiente2) / coeficiente1;
	
	cout << "\nLa ordenada para y = " << y << " es: " << abcisa;	
	
	cout << "\n\n";
	system("pause");
}
	
