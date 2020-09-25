/* Crear un struct Permutacion para representar una permutacion, como funcion biyectiva
 de {1, ..., n} en {1, ..., n}. Para almacenar la permutacion usaremos como dato miembro
un vector de enteros (la imagen de 1,2,...,n). Ademas, tendra otro dato miembro de tipo
entero para almacenar su longitud. Escribir un programa que:
(a) solicite al usuario una permutacion
(b) compruebe si la permutacion es correcta, es decir, que contiene todos los enteros sin
repetir. Por ejemplo, (1,2,3,6,5,4) es una permutacion correcta pero no lo es (1,2,6,5,3,3)
(tiene el 3 repetido y le falta el 4).
(c) calcule el cuadrado de la permutacion (la composicion consigo misma)
Amplia el ultimo punto para que calcule la potencia k-sima de la permutacion, para un k dado.
*/

#include<iostream>

using namespace std;

const int LONGITUD_MAXIMA = 10;

struct Permutacion{
	int imagen[LONGITUD_MAXIMA];
	int longitud;
};

int main(){
	Permutacion permutacion;
    Permutacion cuadrado;
    Permutacion kesima;
    bool repetidos = false;
    int potencia_k;
	
    /* Ejercicio a */
	cout << "Introduce longitud de la permutacion ";
	cin >> permutacion.longitud;
	
	cout << "Introduce la permutacion: ";
	for (int i=0; i < permutacion.longitud; i++)
		cin >> permutacion.imagen[i];
	
    /* Ejercicio b */
	for (int i=0; i<permutacion.longitud && !repetidos; i++)
		for (int j=i+1; j<permutacion.longitud && !repetidos; j++)
			if ( permutacion.imagen[i] == permutacion.imagen[j] )
				repetidos = true;
	
    if (repetidos)
        cout << "\nNo es una permutacion\n";
    else
        cout << "\nSi es una permutacion\n";
    
    /* Ejercicio c */
	
    cuadrado = permutacion;
    
    for (int i=0; i<cuadrado.longitud; i++)
        cuadrado.imagen[i] = permutacion.imagen[permutacion.imagen[i]];
    
    for (int i=0; i<cuadrado.longitud; i++)
        cout << cuadrado.imagen[i] << " ";
    cout << "\n";
    
    /* Ejercicio d */
    
    kesima = permutacion;
    
    cout << "\nIntroduce potencia: ";
    cin >> potencia_k;
    
    for (int i=0; i<kesima.longitud; i++)
        for (int j=0; j<potencia_k; j++)
            kesima.imagen[i] = permutacion.imagen[permutacion.imagen[i]];
    
    for (int i=0; i<kesima.longitud; i++)
        cout << kesima.imagen[i] << " ";
    cout << "\n";	
}
