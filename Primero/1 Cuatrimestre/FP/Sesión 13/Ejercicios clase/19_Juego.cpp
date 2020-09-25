#include<iostream>

using namespace std;

const int MAX = 20;

class TresenRaya{
	private:
		int tablero[MAX][MAX];
		static const int ficha1 = 1;
		static const int ficha2 = 2;
		int turno;
		int orden;
		int linea;
		
	public:
		TresenRaya(){
			turno = 0;
			orden = 0;
			linea = 0;
			
			for(int i = 0; i != MAX; i++)
				for(int j = 0; j != MAX; j++)
					tablero[i][j] = 0;
		}
		
		void SetTablero(int ord, int lin){
			orden = ord;
			linea = lin;
		}
		
		void MostrarTablero(){
			cout << "\n\n";
			
			for(int i = 0; i != orden; i++){
				for(int j = 0; j != orden; j++)
					cout << tablero[i][j] << " ";
					
				cout << "\n\n";
			}
		}
		
		void ColocarFicha(int pos1, int pos2){
			int ficha;
			turno++;
			
			if(turno % 2 != 0)
				ficha = ficha1;
			else
				ficha = ficha2;
				
			tablero[pos1][pos2] = ficha;
		}
		
		void EliminarFicha(int pos1, int pos2){
			tablero[pos1][pos2] = 0;
		}
		
		bool PosicionValida_1(int pos1, int pos2){
			bool valido;
			
			valido = (tablero[pos1][pos2] == 0) && (pos1 <= orden) && (pos2 <= orden);
			
			return valido;
		}
		
		bool PosicionValida_2(int pos1, int pos2){
			bool valido;
			
			if(turno % 2 != 0)
				valido = (tablero[pos1][pos2] == ficha1);
			else
				valido = (tablero[pos1][pos2] == ficha2);
				
			return valido;
		}
		
		
		int GetTurno(){
			return turno;
		}
		
		bool Raya(){
			bool hay_ganador;
			int contador1;
			int contador2;
			
			contador1 = contador2 = 0;
			
			for(int i = 0; (i != orden) && !hay_ganador; i++){				
				for(int j = 0; j != orden; j++){
					if(tablero[i][j] == ficha1){
						contador1++;
					}
					if(tablero[i][j] == ficha2){
						contador2++;
					}
				}
				
				hay_ganador = contador1 == linea || contador2 == linea;
				
				if(!hay_ganador){
					contador2 = contador1 = 0;
				}
			}
			
			if(!hay_ganador){
				contador2 = contador1 = 0;
				
				for(int i = 0; i != orden; i++){
					if(tablero[i][i] == ficha1){
						contador1++;
					}
					if(tablero[i][i] == ficha2){
						contador2++;
					}
				
				hay_ganador = contador1 == linea || contador2 == linea;
				}
			}
			
			return hay_ganador;
		}
			
		
		void Ganador(){
			bool ganador1;
			bool ganador2;
			bool hay_ganador;
			int contador1;
			int contador2;
			
			contador1 = contador2 = 0;
			
			for(int i = 0; (i != orden) && !hay_ganador; i++){				
				for(int j = 0; j != orden; j++){
					if(tablero[i][j] == ficha1){
						contador1++;
					}
					if(tablero[i][j] == ficha2){
						contador2++;
					}
				}
				
				ganador1 = contador1 == linea;
				ganador2 = contador2 == linea;
				hay_ganador = ganador1 || ganador2;
				
				if(!hay_ganador){
					contador2 = contador1 = 0;
				}
			}
			
			if(!hay_ganador){
				contador2 = contador1 = 0;
				
				for(int i = 0; i != orden; i++){
					if(tablero[i][i] == ficha1){
						contador1++;
					}
					if(tablero[i][i] == ficha2){
						contador2++;
					}
				
				ganador1 = contador1 == linea;
				ganador2 = contador2 == linea;
				hay_ganador = ganador1 || ganador2;
				}
			}
			
			if(ganador1)
				cout << "\n\nGana jugador 1 ";
			if(ganador2)
				cout << "\n\nGana jugador 2 ";
		} 
		
};

int main(){
	TresenRaya juego;
	int orden_tablero;
	int raya;
	char respuesta;
	int pos1;
	int pos2;
	int pos1_1, pos2_2;
	
	do{
		cout << "\nIntroduce el tamaño del tablero: ";
		cin >> orden_tablero;
	}while(orden_tablero > MAX && orden_tablero < 2);
	
	do{
		cout << "\nIntroduce con cuantos elementos en raya ganas: ";
		cin >> raya;
	}while(raya > orden_tablero && raya < 2);
	
	juego.SetTablero(orden_tablero, raya);
	
	do{
		cout << "\n¿Desea leer las instrucciones?(s/n) ";
		cin >> respuesta;
	}while(respuesta != 's' && respuesta != 'n');
	
	if(respuesta == 's'){
		cout << "Para jugar cada jugador colocará una ficha por turno. ";
		cout << "\nUna vez llegado al máximo de fichas por jugador, este deberá mover la ficha a una casilla adyacente. ";
		cout << "\nDebe tenerse en cuenta que las posiciones de las casillas funcionan de la siguiente forma: ";
		cout << "\n";
		cout << "\n0,0  0,1  0,2 ... 0,n ";
		cout << "\n1,0  1,1  1,2 ... 1,n ";
		cout << "\n\n..................... ";
		cout << "\n\n,0  n,1  n,2 ... n,n ";
	}
	
	cout << "\nEmpieza el jugador 1: ";
	
	while(!juego.Raya()){
		VUELTA1:if(juego.GetTurno() <= 2*raya){
			cout << "\nIntroduce donde colocar ficha: ";
			cin >> pos1 >> pos2;
			
			if(juego.PosicionValida_1(pos1,pos2)){
				juego.ColocarFicha(pos1,pos2);
				juego.MostrarTablero();
			}
			else{
				cout << "\nIntroduce una casilla correcta: ";
				goto VUELTA1;
			}				
		}
		
		VUELTA2:if(juego.GetTurno() >= 2*raya){
			cout << "\nIntroduce la posicion de la ficha que quieres mover: ";
			cin >> pos1_1 >> pos2_2;
			
			cout << "\nIntroduce donde colocar ficha: ";
			cin >> pos1 >> pos2;
			
			if(juego.PosicionValida_2(pos1_1, pos2_2) && juego.PosicionValida_1(pos1, pos2)){
				juego.EliminarFicha(pos1_1, pos2_2);
				juego.ColocarFicha(pos1,pos2);
			}
			else{
				cout << "\nIntroduce una casilla correcta: ";
				goto VUELTA2;
			}	
		}
	};
	
	juego.Ganador();
		
	cout << "\n\n";
	system("pause");
}
	
	
