/*	Programa para trabajar con una
	clase tipo Conjunto */
	
#include<iostream>

using namespace std;

const int MAXELEM = 100;

class Conjunto{
	private:
		int num_elementos;
		int elementos[MAXELEM];
	public:
		Conjunto(){
			num_elementos = 0;
			for(int i = 0; i != MAXELEM; i++)
				elementos[i] = 0;
		}
		
		void SetConjunto(int numero, int element [MAXELEM]){
			num_elementos = numero;
			for(int i = 0; i != num_elementos; i++)
				elementos [i] = element [i];
		}
		
		void MostrarConjunto(){
			cout << "\nEl conjunto es: " << "\n";
			for(int i = 0; i != num_elementos; i++)
				cout << elementos[i] << " ";
		}
		
		bool Se_Encuentra(int a){
			bool se_encuentra = false;
			
			for(int i = 0; i != num_elementos && !se_encuentra; i++)
				if(elementos[i] == a)
					se_encuentra = true;
					
			return se_encuentra;
		}
			
		void Incorporar(int b){
			int intercambiador;
			
			num_elementos++;
			
			if(num_elementos > MAXELEM){
				cout << "\nNo hay tanta memoria reservada ";
				num_elementos--;
			}
			else{
				elementos[num_elementos - 1] = b;
				
				for(int j = num_elementos - 1; j != 0; j--){
					if(elementos[j - 1] > elementos[j]){
						intercambiador = elementos[j];
						elementos[j] = elementos[j - 1];
						elementos[j - 1] = intercambiador;
					}	
				}
			}	 
		}
		
		void Eliminar(int c){
			int intercambiador;
			
			for (int i = 0; i != num_elementos; i++)
				if(elementos[i] == c){
					intercambiador = elementos[i];
					elementos[i] = elementos[i+1];
					elementos[i+1] = intercambiador;
				}
				
			num_elementos--;
			
			for(int i = num_elementos; i != MAXELEM; i++)
				elementos[i] = 0;
		}
	
		void Interseccion(Conjunto conjunto2){
			for(int i = 0; i != num_elementos; i++)
				for(int j = 0; j != conjunto2.num_elementos; j++)
					if(elementos[i] == conjunto2.elementos[j]){;
						cout << elementos[i] << " ";
					}
		}
		
		void Union(Conjunto conjunto2){
			int tope;
			
			if(num_elementos > conjunto2.num_elementos)
				tope = conjunto2.num_elementos;
			else
				tope = num_elementos;
			
			for(int i = 0; i != tope; i++){
				if(elementos[i] == conjunto2.elementos[i])
					cout << elementos[i] << " ";
				else
				 cout << elementos[i] << " " << conjunto2.elementos[i];
			}
				
			if(num_elementos > conjunto2.num_elementos)
				for(int j = tope; j != num_elementos; j++)
					 cout << elementos[j] << " ";
			else
				for(int j = tope; j != conjunto2.num_elementos; j++)
					 cout << conjunto2.elementos[j] << " ";
		}
		
};

///////////////////////////////////////////////////////////////////

void Ordenar(int numero_elementos, int elemento[MAXELEM]){
	int intercambiador = 0;
	
	if(numero_elementos > 0){	
		cin >> elemento[0];	
		for(int i = 1; i != numero_elementos; i++){
			cin >> elemento[i];
		
			for(int j = i; j != 0; j--){
				if(elemento[j - 1] > elemento[j]){
					intercambiador = elemento[j];
					elemento[j] = elemento[j - 1];
					elemento[j - 1] = intercambiador;
				}
			}
		}
	}
};

///////////////////////////////////////////////////////////////////

int main(){
	Conjunto conjunto1, conjunto2;
	int num1, num2;
	int elem1[MAXELEM], elem2[MAXELEM];
	bool se_encuentra;
	char respuesta1, respuesta2;
	bool condicion1, condicion2;
	int numero;
	
	cout << "\nIntroduce los datos del primer conjunto: ";
	cout << "\nIntroduce el número de elementos: ";
	cin >> num1;
	cout << "\nIntroduce los elementos del conjunto: ";
	Ordenar(num1, elem1);
	conjunto1.SetConjunto(num1, elem1);
	
	cout << "\n\nIntroduce los datos del segundo conjunto: ";
	cout << "\nIntroduce el número de elementos: ";
	cin >> num2;
	cout << "\nIntroduce los elementos del conjunto: ";
	Ordenar(num2, elem2);
	conjunto2.SetConjunto(num2, elem2);
	
	condicion1 = respuesta1 != 'a' && respuesta1 != 'e' && respuesta1 != 'b';
	condicion2 = respuesta1 != 'u' && respuesta1 != 'i';
	
	VUELTA:do{
		cout << "\n¿Qué desea hacer? ";
		cout << "\nPulsa 'a' para añadir un elemento ";
		cout << "\nPulsa 'e' para eliminar un elemento ";
		cout << "\nPulsa 'b' para buscar un elemento ";
		cout << "\nPulsa 'u'para calcular la unión ";
		cout << "\nPulsa 'i' para calcular la intersección ";
		cout << "\n";
		cin >> respuesta1;
	}while(!condicion1 && !condicion2);
	
	switch(respuesta1){
		case 'a':
			cout << "\n\nIntroduce el elemento que quieres añadir: ";
			cin >> numero;
			conjunto1.Incorporar(numero);
			
			cout << "\nEl conjunto ahora es: ";
			conjunto1.MostrarConjunto();			
		break;
		
		case 'b':
			cout << "\n\nIntroduce el elemento a buscar: ";
			cin >> numero;
			se_encuentra = conjunto1.Se_Encuentra(numero);
			
			if(se_encuentra)
				cout << "\nEl elemento se encuentra en el conjunto ";
			else
				cout << "\nEl elemento no se encuentra en el conjunto ";
		break;
		
		case 'e':
			cout << "\nIntroduce el elemento que quieres eliminar: ";
			cin >> numero;
			conjunto1.Eliminar(numero);
			
			cout << "\nEl conjunto ahora es: ";
			conjunto1.MostrarConjunto();
		break;
		
		case 'u':
			cout << "\nLa unión es: ";
			conjunto1.Union(conjunto2);		
		break;
		
		case 'i':
			cout << "\nLa intersección es: ";
			conjunto1.Interseccion(conjunto2);
		break;
	};
	
	do{
		cout << "\n\n¿Quiere hacer algo más (s/n)? ";
		cin >> respuesta2;
	}while(respuesta2 != 's' && respuesta2 != 'n');
	
	if(respuesta2 == 's')
		goto VUELTA;
	else
		cout << "\n\n";
		system ("pause");
}
