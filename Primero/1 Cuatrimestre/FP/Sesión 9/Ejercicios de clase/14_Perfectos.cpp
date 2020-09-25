/*	Programa que muestra todos
	los números perfectos en un
	intervalo dado */
	
#include<iostream>

using namespace std;

int Suma_Divisores(int a){
	int divisor;
	int suma;
	
	divisor = 1;
	suma = 0;
	
	while(divisor < a){
		if(a % divisor == 0)
			suma = suma + divisor;
			
		divisor++;
	}
	
	return suma;
};

bool Es_Perfecto (int a){
	int suma;
	
	suma = Suma_Divisores(a);
	
	if(suma == a)
		return true;
	else
		return false;
};

int main(){
	int inicio_intervalo;
	int final_intervalo;
	bool es_perfecto;
	
	cout << "Introduce el inicio del intervalo: ";
	cin >> inicio_intervalo;
	cout << "\nIntroduce el final del intervalo: ";
	cin >> final_intervalo;
	
	cout << "\n\nLos numeros perfectos en ese intervalo son: " << "\n";
	
	for(int i = inicio_intervalo; i <= final_intervalo; i++){
		es_perfecto = Es_Perfecto(i);
		
		if(es_perfecto){
			cout << i << "\n";
			es_perfecto = false;
		}
	}
}

		
