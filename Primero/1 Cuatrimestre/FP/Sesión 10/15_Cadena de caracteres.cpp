/*	Módulo que dado una cadena
	de caracteres dice si
	un caracter se encuentra en la 
	cadena */
	
#include<iostream>

using namespace std;

bool Encuentra_Caracter (char vector[], char a){
	bool caracter_esta;
	caracter_esta = false;
	
	for(int i = 0; vector[i] != '\0' && !caracter_esta; i++)
		if(vector[i] == a)
			caracter_esta = true;
			
	return caracter_esta;
};

int main(){
	const int LONGITUD = 50;
	char vector[LONGITUD];
	char letra;
	bool encontrado;
	
	cout << "Introduce una cadena de caracteres: ";
	cin.getline(vector, LONGITUD);
	
	cout << "\nIntroduzca la letra que quiere buscar: ";
	cin >> letra;
	
	encontrado = Encuentra_Caracter(vector, letra);
	
	if(encontrado)
		cout << "\n\nEl caracter se encuentra en la cadena ";
	else
		cout << "\n\nEl caracter no se encuentra en la cadena ";
		
	cout << "\n\n";
	system("pause");
}
