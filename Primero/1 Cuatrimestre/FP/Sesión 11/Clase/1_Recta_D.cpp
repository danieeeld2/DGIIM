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
		void SetRecta(){
			double coeficiente1, coeficiente2, coeficiente3;
			
			cout << "\nIntroduce los coeficientes de la primera recta (Ax+By+C): ";
			cin >> coeficiente1 >> coeficiente2 >> coeficiente3;
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
		
		double Abcisa(){
			double y;
			double abcisa;
			
			cout << "\nIntroduce un valor de y para la primera recta: ";
			cin >> y;
	
			abcisa = (-C -y * B) / A;
	
			cout << "\nLa ordenada para y = " << y << " es: " << abcisa;	
			
			return abcisa;
		}
			
		double Ordenada(){
			double x;
			double ordenada;
			
			cout << "\n\nIntroduce un valor de x para la primera recta: ";
			cin >> x;
	
			ordenada = (-C -x * A) / B;
	
			cout << "\nLa ordenada para x = " << x << " es: " << ordenada;
			
			return ordenada;
		}
};
			
int main(){
	Recta Recta1;
	Recta Recta2;
		
	Recta1.SetRecta();
	Recta2.SetRecta();
	
	Recta1.Pendiente();
	Recta2.Pendiente();	
	
	Recta1.Abcisa();
	Recta1.Ordenada();	
	
	cout << "\n\n";
	system("pause");
}
	
