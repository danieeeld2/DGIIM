/*	Modulo para calcular la
	moda de un vector de caracteres
*/

#include<iostream>

using namespace std;

struct FrecuenciaCaracter{
	char caracter;
	int frecuencia;
};


FrecuenciaCaracter Moda (char cadena[]);
void OrdenarCadena (char vector[]);

int main(){
	const int LONGITUD_MAXIMA = 40;
	char cadena[LONGITUD_MAXIMA];
	FrecuenciaCaracter Resultado;
	
	cout << "Introduzca la cadena de caracteres: ";
	cin.getline(cadena, LONGITUD_MAXIMA);
	
	OrdenarCadena(cadena);
	Resultado = Moda(cadena);
	
	cout << "\nEl caracter es " << Resultado.caracter << " y se repite " << Resultado.frecuencia;
	
	cout << "\n\n";
	system("pause");
};	

//	Primero necesitamos ordenar el vector
//	Para ello usamos cualquier algoritmo de ordenación

void OrdenarCadena (char vector[]){
	int posicion_minimo;
	char minimo;
	char intercambia;
	
	for (int izda = 0; vector[izda] != '\0'; izda++){
		minimo = vector[izda];
		posicion_minimo = izda;
	
		for (int i = izda + 1; vector[i] != '\0'; i++){
			if (vector[i] < minimo){
				minimo = vector[i];
				posicion_minimo = i;
			}
		}
		
		intercambia = vector[izda];
		vector[izda] = vector[posicion_minimo];
		vector[posicion_minimo] = intercambia;
	}
}

/*	Comparamos una componente
	del vector y la anterior. Si son iguales
	aumenta las repeticiones y si son distintos
	analiza si el aracter anterior es la moda
	o no */

FrecuenciaCaracter Moda (char vector[]){
	FrecuenciaCaracter Salida;
	int repeticiones = 1;
	int moda = 0;
	char caracter;
	
	for(int i = 1; vector[i-1] != '\0'; i++){
		if(vector[i] == vector[i-1])
			repeticiones++;
		else{
			if(repeticiones > moda){
			moda = repeticiones;
			caracter = vector[i-1];
			repeticiones = 1;
			};
		};
	};
	
	Salida.caracter = caracter;
	Salida.frecuencia = moda;
	
	return Salida;
}
	
			
			
		
