/*	Programa que imprime un vector
	cuyas componentes son las componentes
	de otros dos vectores, de 
	forma ascendente */
	
#include<iostream>

using namespace std;

int main(){
	const int LONGITUD1 = 5;
	const int LONGITUD2 = 4;
	int vector1[LONGITUD1];
	int vector2[LONGITUD2];
	int vector_resultante[LONGITUD1 + LONGITUD2];
	int intercambiador;
	int posicion1;
	int posicion2;
	
	cout << "Introduce las coordenadas del primer vector: ";
	cin >> vector1[0];
	for(int i = 1; i != LONGITUD1; i++){
		cin >> vector1[i];
		
		if(vector1[i-1] > vector1[i]){
			intercambiador = vector1[i];
			vector1[i] = vector1[i-1];
			vector1[i-1] = intercambiador;
		}
	}
	
	cout << "\nIntroduce las coordenadas del segundo vector: ";
	cin >> vector2[0];
	for(int i = 1; i != LONGITUD2; i++){
		cin >> vector2[i];
		
		if(vector2[i-1] > vector2[i]){
			intercambiador = vector2[i];
			vector2[i] = vector2[i-1];
			vector2[i-1] = intercambiador;
		}
	}	
	
	posicion1 = 0;
	posicion2 = 0;
	
	for(int z = 0; z != LONGITUD1 + LONGITUD2; z++){
		if(posicion2 == LONGITUD2)
			posicion2 = 0;
		if(posicion1 == LONGITUD1)
			posicion1 = 0;
			
		if(vector1[posicion1] > vector2[posicion2]){
			vector_resultante[z] = vector2[posicion2];
			posicion2++;
		}
		else{
			if(vector1[posicion1] < vector2[posicion2]){
				vector_resultante[z] = vector1[posicion1];
				posicion1++;
			}
			else{
				vector_resultante[z] = vector2[posicion2];
				z++;
				vector_resultante[z] = vector1[posicion1];
				posicion1++;
				posicion2++;
			}
		}
	}
	
	cout << "\n\nEl vector resultante es: " << "\n\n";
	for(int j = 0; j != LONGITUD1 + LONGITUD2; j++)
		cout << vector_resultante[j] << " ";
		
	cout << "\n\n";
	system("pause");
}
			
