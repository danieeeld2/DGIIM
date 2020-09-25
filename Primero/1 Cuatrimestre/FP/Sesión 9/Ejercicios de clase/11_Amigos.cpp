/*	Diseñar un módulo que determine
	si dos números son amigos
	y; posteriormente, un programa
	que muestre todas las parejas de amigos
	que hay en un intervalo */
	
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

bool Son_Amigos(int a, int b){
	int suma1;
	int suma2;
	
	suma1 = Suma_Divisores(a);
	suma2 = Suma_Divisores(b);
	
	if(suma1 == b && suma2 == a)
		return true;
	else
		return false;
};

int main(){
	int entero1;
	int entero2;
	bool amigos;
	int inicio_intervalo;
	int final_intervalo;
	
	//	Programa que dice i dos enteros son amigos
	
	cout << "Introduce un entero: ";
	cin >> entero1;
	cout << "\nIntroduce otro entero: ";
	cin >> entero2;
	
	amigos = Son_Amigos(entero1, entero2);
	
	if(amigos)
		cout << "\n\nSon amigos ";
	else
		cout << "\n\nNo son amigos ";
		
	//	Programa que dice las parejas de amigos que hay en un intervalo
	
	cout << "\n\nIntroduce el incio del intervalo: ";
	cin >> inicio_intervalo;
	cout << "\nIntroduce el final del intervalo: ";
	cin >> final_intervalo;
	
	cout << "\n\nLas parejas en dicho intervalo son: " << "\n";
	for(int i = inicio_intervalo; i != final_intervalo; i++){
		for(int z = inicio_intervalo + 1; z <= final_intervalo && !amigos; z++){
			amigos = Son_Amigos(i,z);
			
			if(amigos && i != z)
				cout << i << ", " << z << "\n";
		}
		amigos = false;
	}
	
	cout << "\n\n";
	system("pause");
}
