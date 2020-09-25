
#include <iostream>
#include <vector>

using namespace std;

class Frase{
	private:
		vector<char> cadena;
	public:
		void SetCadena(vector<char>& vec){
			cadena = vec;
		}
		void MostrarCadena(){
			for(int i=0; i<cadena.size(); i++){
				cout << cadena[i];
			}
		}
		void EliminarBlancosIniciales(){
			bool espacio = false;
			bool palabra = false;
			vector<char> vector;
			
			for(int i=0; i<cadena.size(); i++){
				espacio = cadena[i] == ' ';
				
				if(!espacio && !palabra){
					palabra = true;
				}
				
				if(palabra){
					vector.push_back(cadena[i]);
				}
			}
			SetCadena(vector);
		}
		void EliminarBlancosFinales(){
			int posicion_UltPalabra;
			vector<char> vector;
			
			for(int i=0; i<cadena.size(); i++){
				if(cadena[i] != ' '){
					posicion_UltPalabra = i;
				}
			}
			
			for(int i=0; i<=posicion_UltPalabra; i++){
				vector.push_back(cadena[i]);
			}
			SetCadena(vector);
		}
		int NumeroPalabras(){
			int contador_palabras=1;
			bool palabra_detectada = false;
			
			for(int i=0; i<cadena.size(); i++){
				if(cadena[i] == ' ' && cadena[i+1] != ' '){
					palabra_detectada = true;
				}
				if(palabra_detectada){
					contador_palabras++;
					palabra_detectada = false;
				}
			}
			return contador_palabras;
		}
		int FindPalabra(int numeroPalabra){
			int contador = 0;
			int posicion;
			bool buscando = true;
			bool acabar = false;
			
			if (numeroPalabra <= NumeroPalabras()){			
				for (int i=0; i<cadena.size() && acabar == false; i++){
					if(buscando){
						if(cadena[i] != ' '){
							contador++;
							if(contador == numeroPalabra){
								acabar = true;
								posicion = i;
							}
							buscando = false;
						}
					}
					else{
						if(cadena[i] == ' '){
							buscando = true;
						}
					}
				}
			}
			else{
				cout << "El numero de palabra no es valido.";
				posicion = -1;
			}
			
			return posicion;
		}
		void BorrarPalabra(int numeroPalabra){
			int posicion = FindPalabra(numeroPalabra);
			while(cadena[posicion] != ' '){
				for (int i=posicion; i<cadena.size(); i++){
					cadena[i] = cadena[i+1];					
				}
				cadena.pop_back();
			}
		}
		void MoverPalabraFinal(int numeroPalabra){
			int posicion = FindPalabra(numeroPalabra);
			int contador = posicion;
			
			while(cadena[contador] != ' '){				
				cadena.push_back(cadena[contador]);
				contador++;
			}
			BorrarPalabra(numeroPalabra);
		}
};

void LeerFrase(Frase& phrase){
	int i=1;
	char caracter;
	vector<char> vec_parameter;
	
	cout << "INSERTE CADENA >>> ";
	do{
	    cin.get(caracter);
		if(caracter != '#'){
			vec_parameter.push_back(caracter);
		}
	}while(caracter != '#');
	
	phrase.SetCadena(vec_parameter);
}

int main(){
	Frase frase;
	
	LeerFrase(frase);
	
	cout << "CADENA INICIAL: (inicio)";
	frase.MostrarCadena();
	cout << "(fin)";
	frase.EliminarBlancosIniciales();
	cout << "\nCADENA SIN ESPACIOS INICIALES: ";
	frase.MostrarCadena();
	frase.EliminarBlancosFinales();
	cout << "\nCADENA SIN ESPACIOS FINALES: ";
	frase.MostrarCadena();
	cout << "(fin)";
	cout << "\n\nNumero Palabras: " << frase.NumeroPalabras();
}
