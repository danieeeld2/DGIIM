#include<iostream>

using namespace std;

class Bicicleta{
	private:
		int posicion_P;
		int posicion_E;
		static const int MAX = 20;
		
		bool Riesgo1(){
			bool condicion1;
			
			condicion1 = posicion_E == 1 && posicion_P >= 5;
			
			return condicion1;
		}
		
		bool Riesgo2(){
			bool condicion2;
			
			condicion2 = posicion_E == 2 && (posicion_P == 1 || posicion_P == 7);
			
			return condicion2;
		}
		
		bool Riesgo3(){
			bool condicion3;
			
			condicion3 = posicion_E == 3 && posicion_E <= 3;
			
			return condicion3;
		}
			
		bool Condicion_Estrella(){
			bool condicion;
			
			condicion = (posicion_E >= 1 && posicion_E <= 3);

			return condicion;
		}
		
		bool Condicion_Pinion(){
			bool condicion;
			
			condicion = (posicion_P >= 1 && posicion_P <= 7);
			
			return condicion;
		}
		
	public:
		Bicicleta(){
			posicion_P = 1;
			posicion_E = 1;
		}
		
		void Instrucciones(char instrucciones[MAX]){
			for(int i = 0; instrucciones[i] != '#'; i++){
				if(instrucciones[i] == 'E'){
					switch (instrucciones[i + 1]){ 
						case 'S':
							posicion_E ++;
						break;
						
						case 'T':
							posicion_E++;
							posicion_E++;
						break;
						
						case 'B':
							posicion_E--;
						break;
						
						case 'C':
							posicion_E--;
							posicion_E--;
						break;
					};
					
					if(!Condicion_Estrella()){
						if(posicion_E < 1)
							posicion_E = 1;
						
						if(posicion_E > 3)
							posicion_E = 3;
					}	
				}
				
				if(instrucciones[i] == 'P'){
					switch(instrucciones[i + 1]){
						case 'S':
							posicion_P ++;
						break;
						
						case 'B':
							posicion_P--;
						break;
					};
					
					if(!Condicion_Pinion()){
						if(posicion_P < 1)
							posicion_P = 1;
							
						if(posicion_P > 7)
							posicion_P = 7;
					}
				}
			}
				
			if(Riesgo1() || Riesgo2() || Riesgo3()){
				cout << "\nRiesgo de rotura; se cambiará a una marcha segura: ";
				posicion_P = 4;
			}
		}
		
		void Mostrar(){
			cout << "\nLa bici esta: ";
			cout << "\nEstrella: " << posicion_E;
			cout << "\nPiñón: " << posicion_P;
		}
	};
	
int main(){
	Bicicleta bici1;
	char instrucciones[20];
	
	cout << "\nIntroduce instrucciones: ";
	for(int i = 0; instrucciones[i] != '#'; i++)
		cin >> instrucciones[i];
		
	bici1.Instrucciones(instrucciones);
	bici1.Mostrar();

	cout << "\n\n";
	system("pause");
}
