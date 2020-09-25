/* Implementar un programa que intercambie dos componentes de un vector de enteros. Por
 ejemplo, si el vector es (1,2,5,3), y el usuario intercambia las componentes 1 y 3, se quedaria
 como (5,2,1,3). El programa debe comprobar si las componentes son correctas
*/

#include<iostream>

using namespace std;

int main(){
    /* Establecemos maximo de componentes de reserva */
	const int LONGITUD_MAXIMA = 10;
	int vector[LONGITUD_MAXIMA];
    
    int componentes_utiles;
    int coordenada1, coordenada2, intercambio;
	
    /* Insercion de datos por el usuario */
	cout << "\nIntroducir longitud del vector (maximo 10) : ";
	cin >> componentes_utiles;
    while ( componentes_utiles <= 0 )
        cin >> componentes_utiles;
	
	cout << "\nIntroducir vector: ";
	for(int i = 0 ; i < componentes_utiles ; i++)
		cin >> vector[i];
	
    cout << "\nIntroducir primera coordenada: ";
    cin >> coordenada1;
    while ( coordenada1 < 0 || coordenada1 >= componentes_utiles )
        cin >> coordenada1;
    
    cout << "\nIntroducir segunda coordenada: ";
    cin >> coordenada2;
    while ( coordenada2 < 0 || coordenada2 >= componentes_utiles )
        cin >> coordenada2;
    
	/* Intercambio valores de las coordenadas del vector
     utilizando una variable auxiliar de memoria */
	intercambio = vector[coordenada1];
	vector[coordenada1] = vector[coordenada2];
	vector[coordenada2] = intercambio;
	
    /* salida por pantalla del vector resultante */
	for(int i = 0 ; i < componentes_utiles ; i++)
		cout << vector[i] << " ";
    cout << "\n";
	
}
