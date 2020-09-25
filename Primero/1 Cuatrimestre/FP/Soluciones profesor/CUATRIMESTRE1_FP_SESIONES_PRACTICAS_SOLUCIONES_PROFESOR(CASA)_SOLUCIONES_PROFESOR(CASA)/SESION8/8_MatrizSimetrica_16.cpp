#include<iostream>
#include<cmath>

using namespace std;

const int TAMANO_MAXIMO = 10;
const int LONGITUD_MAXIMA = 10 * 11 / 2;

int main(){
    double matriz[TAMANO_MAXIMO][TAMANO_MAXIMO];
    double vector_matriz[LONGITUD_MAXIMA];
    int filas_utiles, longitud;
	
	cout << "Introducir filas: ";
	cin >> filas_utiles;
	
	cout << "Introducir matriz:\n";
	for (int i=0; i<filas_utiles ;i++)
		for (int j=0; j<filas_utiles ;j++)
			cin >> matriz[i][j];
	
    int posicion = 0;
	for (int i=0; i<filas_utiles; i++)
		for (int j=i ; j<filas_utiles; j++){
			vector_matriz[posicion] = matriz[i][j];
			posicion++;
		}
	
	cout << "El vector es: ";
	for (int i=0; i<posicion ; i++)
		cout << vector_matriz[i] << " ";
    cout << "\n";
	
	
	
	cout << "\nIntroducir longitud vector: ";
	cin >> longitud;
	
	cout << "Introducir vector: ";
	for (int i=0; i<longitud; i++)
		cin >> vector_matriz[i];
	
    filas_utiles =(-1+3*sqrt(longitud))/2;
    
    posicion = 0;
    for ( int i=0; i<filas_utiles; i++ )
        for ( int j=i; j<filas_utiles; j++){
            matriz[i][j] = vector_matriz[posicion];
            posicion++;
        }
    
    for (int i=0; i<filas_utiles; i++)
        for (int j=0; j<i; j++)
            matriz[i][j] = matriz[j][i];
	
	for (int i=0; i<filas_utiles; i++){
		for (int j=0; j<filas_utiles; j++)
			cout << matriz[i][j] << " ";
		cout << "\n";
	}
}
