/*	Programa para formar
	una matriz cuadrada simétrica */
	
#include<iostream>

using namespace std;

int main(){
	const int K = 5;
	double matriz[K][K];
	double diagonal[K*K];
	int contador;
	
	//	Primero la matriz y luego el vector
	
	cout << "Introduce los datos de la matriz ";
	
	for(int i = 0; i != K; i++)
		for(int z = 0; z != K; z++)
			cin >> matriz [i][z];
			
	cout << "\nLa matriz introducida es : " << "\n\n";
	
	for(int i = 0; i != K; i++)
		for(int z = 0; z != K; z++){
			cout << matriz [i][z] << "\t";
			contador ++;
			
			if(contador == K){
				cout << "\n";
				contador = 0;
			}
		}
		
	cout << "\nLa diagonal principal es: ";
	
	for(int i = 0; i != K; i++)
		cout << matriz[i][i] << " ";
		
	// Ahora primero el vector y un triangular
	
	cout << "\n\nIntroduce los elementos de la diagonal principal y los que estén por debajo: ";
	cout << "\nSe introduciran como 11, 21, 22,..., 31, 32, 33,..., kk " << "\n";
	
	for(int i = 0; i !=(2*K); i++)
		for(int z = 0; z != i; z++)
			cin >> diagonal[z];
			
	for(int j = 0; j != K; j++){
		for(int x = 0; x !=j; x++){
			cout << diagonal[x] << "\t";
		}
		
		cout << "\n";
	}
	
	cout << "\n\n";
	system("pause");
}
				

		
		
	
	
