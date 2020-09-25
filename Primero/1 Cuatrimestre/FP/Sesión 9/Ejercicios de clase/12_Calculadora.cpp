/*	Módulo que realiza operaciones
	con dos enteros, en función
	de un caracter introducido */
	
#include<iostream>

using namespace std;

//	Necesitamos la del máximo común divisor
// Usamos el algoritmo de Euclides

int MCD (int a, int b){
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
 
int MCM (int a, int b){
	int mcm;
	
	mcm = (a*b)/MCD(a,b);
	
	return mcm;
}

int Operaciones (int a, int b, char c){
	int operacion;
	
	switch (c){
		case 'm':
			operacion = MCM(a,b);
		break;
		
		case 'd':
			operacion = MCD(a,b);
		break;
		
		case '+':
			operacion = a + b;
		break;
		
		case '*':
			operacion = a * b;
		break;
		
		case '-':
			operacion = a - b;
		break;
		
		case '/':
			operacion = a / b;
		break;
	};
	
	return operacion;
}

//	Para comprobar que funiona

	int main(){
		int entero1;
		int entero2;
		char operacion;
		int resultado;
		
		cout << "Introduce un entero: ";
		cin >> entero1;
		cout << "\nIntroduce otro entero: ";
		cin >> entero2;
		
		cout << "\n m para MCM ";
		cout << "\n d para MCD ";
		cout << "\n + para suma ";			
		cout << "\n - para menos ";
		cout << "\n * para multiplicar ";
		cout << "\n / para dividir ";
		cout << "\nIntroduce una operación: ";
			
		cin >> operacion;
		
		resultado = Operaciones(entero1, entero2,operacion);
		
		cout << "\n\nEl resultado es: " << resultado;
		
		cout << "\n\n";
		system("pause");
	}
