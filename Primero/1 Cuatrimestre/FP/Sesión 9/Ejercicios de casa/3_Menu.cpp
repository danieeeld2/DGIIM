/*	Módulo para aceptar
	o cancelar mensajes de 
	confirmación */
	
#include<iostream>

using namespace std;

bool Confirmacion_Mensajes(char respuesta){
	do{
		cout << "\n¿Confirmar(S/N)? ";
		cin >> respuesta;
		
		if(respuesta == 's')
			respuesta = 'S';
			
		if(respuesta == 'n')
			respuesta = 'N';
	}while(respuesta != 'S' && respuesta != 'N');
	
	if(respuesta == 'S')
		return true;
	else
		return false;
};

//	Para comprobar

int main(){
	char confirmacion;
	bool respuesta;
	
	respuesta = Confirmacion_Mensajes(confirmacion);
	
	cout << "\n\n" << respuesta;
	
	cout << "\n\n";
	system("pause");
}


