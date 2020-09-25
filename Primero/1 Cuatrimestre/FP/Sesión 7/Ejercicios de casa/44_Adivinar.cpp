/*	Juego: Intenta adivinar el número
	introducido por otro usuario */
	
#include <iostream>

using namespace std;

int main(){
	int numero_a_adivinar;
	int numero_del_jugador;
	bool ganador;
	bool TERMINADOR;
	char respuesta;
	
	cout << "Trata de adivinar el número. En caso de querer finalizar pulsa @ ";
	
	/*	El número a adivinar se introducira en el
	archivo .cpp, para que así el jugador no
	pueda ver de que número se trata */
	
	numero_a_adivinar = 87;
	
	do{
		do{
			cout <<"\n";
			cin >> numero_del_jugador;
		
			if (numero_del_jugador > numero_a_adivinar)
				cout << "\nEl número a adivinar es más pequeño ";
			
			if (numero_del_jugador < numero_a_adivinar)
				cout << "\nEl número a adivinar es más grande ";
		
			ganador = numero_del_jugador == numero_a_adivinar;
			TERMINADOR = numero_del_jugador == '@';
		
		}while(!ganador && !TERMINADOR);
	
	if(ganador)
		cout << "\nHas ganado ";
	else
		cout << "\nHas perdido ";
		
	cout << "\n\n¿Quieres jugar de nuevo (s/n)? ";
	cin >> respuesta;
	
	}while(respuesta == 's');
	
	cout << "\n\n";
	system ("pause");
}
		
	
