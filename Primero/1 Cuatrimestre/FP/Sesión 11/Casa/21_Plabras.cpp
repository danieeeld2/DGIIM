/*	Programa que dice si dos
	palabras son iguales segun el siguiente
	criterio:
	La primera y última letra son iguales
	y el resto de letras tambien, pero
	pueden estar desordenadas */
	
#include<iostream>

using namespace std;

const int MAXIMO = 20;

int Longitud(char palabra[MAXIMO]){
	int contador;
	contador = 0;
	
	for(int i = 0; palabra[i] != '\0'; i++)
		contador++;
		
	return contador;
};

////////////////////////////////////7

bool Son_Iguales(char palabra1[MAXIMO], char palabra2[MAXIMO]){
	int longitud_palabra1;
	int longitud_palabra2;
	bool son_iguales;
	bool condicion1;
	char vector_auxiliar[MAXIMO];
	
	son_iguales = false;
	
	longitud_palabra1 = Longitud(palabra1);
	longitud_palabra2 = Longitud(palabra2);
	
	condicion1 = (palabra1[0] == palabra2[0]) && (palabra1[longitud_palabra1] == palabra2[longitud_palabra2]);
	
	if(longitud_palabra1 == longitud_palabra2){
		if(condicion1){
			for(int i = 0; palabra2[i] != '\0'; i++)
				vector_auxiliar[i] = palabra2[i];
				
			son_iguales = true;
				
			for(int i = 1; i != longitud_palabra1 && son_iguales; i++){
				son_iguales = false;
				
				for(int j = 1; j != longitud_palabra1 && !son_iguales; j++){
					if(palabra1[i] == vector_auxiliar[j]){
					son_iguales = true;
						vector_auxiliar[j] = 'º';
					}
				}
			}
		}
	}
	
	return son_iguales;
};

//////////////////////////////////////////////////////////////////

int main(){
	char palabra1[MAXIMO];
	char palabra2[MAXIMO];
	bool son_iguales;
	
	cout << "Introduce una palabra: ";
	cin.getline(palabra1, MAXIMO);
	cout << "\nIntroduce otra palabra: ";
	cin.getline(palabra2,MAXIMO);
	
	son_iguales = Son_Iguales(palabra1, palabra2);
	
	if(son_iguales)
		cout << "\nSí ";
	else
		cout << "\nNo ";
		
	cout << "\n\n";
	system("pause");
}
	
