#include<iostream>
#include<vector>

using namespace std;

class Liga{
	private:
		static const int MAX = 5;
		string tabla[MAX][MAX];
		char resultados[MAX][MAX];
	public:
		Liga(){
			for(int i = 0; i != MAX; i++)
				for(int j = 0; j != MAX; j++){
					tabla[i][j] = ' ';
					resultados[i][j] = ' ';
				}					
		}
		
		void SetEquipos(string equipo){
			int posicion;
			posicion = 0;
			
			tabla[posicion][0] = tabla[0][posicion] = equipo;
			posicion++;
		}
		
		void SetResultado(string equipo1, string equipo2, char resultado){
			int posicion1;
			int posicion2;
			
			for(int i = 0; i != MAX; i++)
				if(tabla[0][i] == equipo1)
					posicion1 = i;
					
				
			for(int j = 0; j != MAX; j++)
				if(tabla[j][0] == equipo2)
					posicion2 = j;
					
			resultados[posicion2][posicion1] = resultado;
		}
		
		vector<int> LeerPuntos(string equipo){
			int posicion;
			vector<int> resultado;
			
			for(int i = 0; i != MAX; i++)
				if(tabla[i][0] == equipo)
					posicion = i;
					
			for(int j = 0; j != MAX; j++){
				if(j != posicion)
					switch(resultados[posicion][j]){
						case '1':
							resultado[j] = 3;
						break;
						
						case 'X':
							resultado[j] = 1;
						break;
						
						case '2': 
							resultado[j] = 0;
						break;
					}
			}
			
			return resultado;
		}
};

int main(){
	Liga liga1;
	string equipo;
	string equipo1;
	string equipo2;
	char resultado;
	int numero;
	vector<int> resultados;
	
	cout << "\nIntroduce el número de equipos: ";
	cin >> numero;
	cout << "\nIntroduce el nombre de los equipos: ";
	for(int i = 0; i != numero; i++){
		cin >> equipo;
		liga1.SetEquipos(equipo);
	}
	
	cout << "\nEstablezca el resultado: ";
	cout << "\nEquipo 1: ";
	cin >> equipo1;
	cout << "\nEquipo2: ";
	cin >> equipo2;
	cout << "\nResultado: ";
	cin >> resultado;
	liga1.SetResultado(equipo1,equipo2,resultado);
	
	cout << "\nIntroduce un equipo para ver sus puntos: ";
	cin >> equipo;
	resultados = liga1.LeerPuntos(equipo);
	for(int i = 0; i != numero - 1; i++)
	cout << resultados[i] << " ";
	
	cout << "\n\n";
	system("pause");
}

