#include <iostream>
#include <vector>
using namespace std;

struct ParejaCaracterEntero{
	char caracter;
	int numero;
};

class VectorParejasCaracterEntero{
	private:		
		vector<ParejaCaracterEntero> elementos;
	public:
		VectorParejasCaracterEntero(vector<ParejaCaracterEntero> parejas){
			elementos = parejas;
		}
		int GetLength(){
			int longitud = elementos.size();		
			return longitud;
		}
		char GetCaracter(int posicion){
			char caracter = elementos[posicion].caracter;			
			return caracter;
		}
		
		int GetVeces(int posicion){
			int veces = elementos[posicion].numero;
			return veces;
		}
		void IntroducirDatos(){
			char respuesta, continuar;
			int veces;
			ParejaCaracterEntero pareja;
			
			do{
				cout << "\n\nINSERTE CARACTER A ELIMINAR: ";
				cin >> respuesta;
				cout << "INSERTE VECES A ELIMINAR CARACTER " << respuesta << ": ";
				cin >> veces;
				
				pareja.caracter = respuesta;
				pareja.numero = veces;
				
				elementos.push_back(pareja);
				
				cout << "DESEA CONTINUAR?[Y/N]: ";
				cin >> continuar;			
			}while(continuar == 'Y');
		}
		void MostrarParejas(){
			cout << "[";
			cout << "(" << elementos[0].caracter << "," << elementos[0].numero << ")";
			
			for (int i=1; i<elementos.size()-1; i++){
				cout << ",(" << elementos[i].caracter << "," << elementos[i].numero << ")";
			}
			
			if(elementos.size() > 1){
				cout << ",(" << elementos[elementos.size()-1].caracter << "," << elementos[elementos.size()-1].numero << ")";
			}
			cout << "]";
		}
};

class Frase{
	private:
		vector<char> caracteres;
	public:
		Frase(vector<char> frase){
			caracteres = frase;
		}
		Borrar(VectorParejasCaracterEntero parejas){
			int contador = 0;
			for(int i=0; i<parejas.GetLength(); i++){
				for (int j=0; j<caracteres.size() && contador<parejas.GetVeces(i); j++){
					if(caracteres[j] == parejas.GetCaracter(i)){
						EliminarLetra(j);
						contador++;
					}
				}
				contador = 0;
			}
		}
		void EliminarLetra(int posicion){
			for (int i=posicion; i<caracteres.size(); i++){
				caracteres[i] = caracteres[i+1];				
			}
			caracteres.pop_back();
		}
		void PedirFrase(){
			char respuesta;
			
			cout << "Introduce una frase acabando con #: ";
			cin.get(respuesta);
			
			while(respuesta != '#'){
				caracteres.push_back(respuesta);
				cin.get(respuesta);
			}
		}
		void Mostrar(){
			cout << "\nLa frase es: ";
			for (int i=0; i<caracteres.size(); i++){
				cout << caracteres[i];
			}
		}
};

int main(){
	vector<char> vec;
	vec = {'k','i','o'};
	Frase phrase(vec);
	VectorParejasCaracterEntero parejas;
	
	phrase.Mostrar();
	parejas.IntroducirDatos();
	parejas.MostrarParejas();
	phrase.Borrar(parejas);
	phrase.Mostrar();
}
