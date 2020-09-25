/* Implementar una clase para trabajar con
	complejos */
	
#include<iostream>

using namespace std;

class Complejos{
	private:
		double real, imaginaria;
	public:
		void SetComplejo(){
			double a, b;
			
			cout << "\nIntroduce la parte real: ";
			cin >> a;
			cout << "\nIntroduce la parte imaginaria: ";
			cin >> b;
			
			real = a;
			imaginaria = b;
		}
		
		void LeerComplejo(){
			cout << "\nEl complejo es: " << real << " + i(" << imaginaria << ")";
		}
		
		void Suma(Complejos complejo2){
			double suma_real, suma_imaginaria;
			
			suma_real = real + complejo2.real;
			suma_imaginaria = imaginaria + complejo2.imaginaria;
			
			cout << "\nLa suma es: " << suma_real << " + i(" << suma_imaginaria << ")";
		}
		
		void Resta(Complejos complejo2){
			double resta_real, resta_imaginaria;
			
			resta_real = real - complejo2.real;
			resta_imaginaria = imaginaria - complejo2.imaginaria;
			
			cout << "\nLa resta es: " << resta_real << " + i(" << resta_imaginaria << ")";
		}
		
		void Multiplicacion(Complejos complejo2){
			double parte_real, parte_imaginaria;
			
			parte_real = (real * complejo2.real) - (imaginaria * complejo2.imaginaria);
			parte_imaginaria = (real * complejo2.imaginaria) + (imaginaria * complejo2.real);
			
			cout << "\nLa multiplicación es: " << parte_real << " + i(" << parte_imaginaria << ")";
		}
};

int main(){
	Complejos Complejo1;
	Complejos Complejo2;
	
	Complejo1.SetComplejo();
	Complejo2.SetComplejo();
	
	Complejo1.Suma(Complejo2);
	Complejo1.Resta(Complejo2);
	Complejo1.Multiplicacion(Complejo2);	
	
	cout << "\n\n";
	system("pause");
}
