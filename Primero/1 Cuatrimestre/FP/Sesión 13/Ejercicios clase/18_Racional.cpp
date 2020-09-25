#include<iostream>

using namespace std;

class Racional{
	private:
		int numerador;
		int denominador;
		
		int MCD(int a, int b){
  			int t;
   		int intercambiador;
   
   		if (b > a){
   			intercambiador = b;
   			b = a;
   			a = intercambiador;
  			}
  			
			if(b == 0)
   			return a;
   		else{
   	  		while (a > 0){
      			t = a;
     				a = b % a;
    					b = t;
				}
     		}
          
     		return b;
 		}; 
 		
	public:
		Racional(){
			numerador = 1;
			denominador = 1;
		}
		
		Racional(int a, int b){
			numerador = a;
			denominador = b;
		}
		
		void SetRacional(int a, int b){
			numerador = a;
			denominador = b;
		}
		
		void Simplificar(){
			if(numerador % denominador == 0){
				numerador = numerador / denominador;
				denominador = 1;
			}
			else{		
 				for(int i = 1; MCD(numerador, denominador) != 1; i++){
 					if(numerador % i == 0 && denominador % i == 0){
 						numerador = numerador / i;
 						denominador = denominador / i;
 					}
 				}
 			}
 		}
		
		int Comparar(Racional rac2){
			double racional1;
			double racional2;
			int numero;
			
			racional1 = numerador / denominador;
			racional2 = rac2.numerador / rac2.denominador;
			
			if(racional1 > racional2)
				numero = 1;
			if(racional2 == racional1)
				numero = 0;
			if(racional1 < racional2)
				numero = -1;
				
			return numero;
		}
		
		
		int GetNumerador(){
			return numerador;
		}
		
		int GetDenominador(){
			return denominador;
		}
};

int main(){
	Racional racional1(6,2);
	Racional racional2(4,10);
	
	cout << "\nLas fracciones son: ";
	cout << "\n" << racional1.GetNumerador() << " / " << racional1.GetDenominador();
	cout << "\n" << racional2.GetNumerador() << " / " << racional2.GetDenominador();
	
	racional1.Simplificar();
	racional2.Simplificar();
	
	cout << "\n\nLas fracciones simplificadas son: ";
	cout << "\n" << racional1.GetNumerador() << " / " << racional1.GetDenominador();
	cout << "\n" << racional2.GetNumerador() << " / " << racional2.GetDenominador();
	
	switch(racional1.Comparar(racional2)){
		case 1:
			cout << "\n\n" << racional1.GetNumerador() << " / " << racional1.GetDenominador() << " mayor que ";
			cout << racional2.GetNumerador() << " / " << racional2.GetDenominador();
		break;
		
		case 0:
			cout << "\n\n" << racional1.GetNumerador() << " / " << racional1.GetDenominador() << " igual que ";
			cout << racional2.GetNumerador() << " / " << racional2.GetDenominador();
		break;
		
		case -1:
			cout << "\n\n" << racional1.GetNumerador() << " / " << racional1.GetDenominador() << " menor que ";
			cout << racional2.GetNumerador() << " / " << racional2.GetDenominador();
	};
	
	cout << "\n\n";
}
