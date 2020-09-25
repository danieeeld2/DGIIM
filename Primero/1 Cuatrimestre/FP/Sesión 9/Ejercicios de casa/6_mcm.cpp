/*	Implemetar módulo que devuelva
	mínimo común múltiplo */
	
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

//	Para probar que funciona

int main(){
	int numero1;
	int numero2;
	int resultado;
	
	cout << "Introduzca un número: ";
	cin >> numero1;
	cout << "\nIntroduzca otro número: ";
	cin >> numero2;
	
	resultado = MCM(numero1, numero2);
	
	cout << "\n\nEL MCM es : " << resultado << "\n\n";
	
	system("pause");
}
