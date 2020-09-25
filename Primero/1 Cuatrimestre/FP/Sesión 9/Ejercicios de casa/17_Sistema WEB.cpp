/*	Generador de nombres
	de usuario mediante la combinación
	de n caracteres del nombre
	y los apellidos */
	
#include<iostream>

using namespace std;

int main(){
	const int K = 30;
	char matriz_datos[K][K];
	int fila;
	int ultima_fila;
	int n_caracteres;
	
	cout << "Introduzca su nombre y apellidos: ";
	cout << "\nRecuerde usar espacios en blaco entre letras. ";
	cout << "Introduzca º para cambiar de palabra y @ para terminar de introducir datos " << "\n\n";
	
	fila = 0;
	
	for(int i = 0; i != K; i++){
		cin >> matriz_datos[fila][i];
		
		if(matriz_datos[fila][i] == 'º'){
			fila++;
			i = -1;
		}
		
		if(matriz_datos[fila][i] == '@')
			i = K - 1;
	}
	
	cout << "\nIntroduce el número de caracteres de cada palabra ";
	cin >> n_caracteres;
	
	cout <<	"\n\nSu nombre de usuario será: ";
	
	ultima_fila = fila;
	
	for(int z = 0; z != ultima_fila; z++)
		for(int i = 0; i != n_caracteres; i++)
			cout << matriz_datos[z][i];		
			
	cout << "\n\n";
	system("pause");
}
	
