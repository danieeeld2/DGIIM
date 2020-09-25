/*	Crear una base de datos sobre los ADN de distintas
	especies de Sierra Nevada */
	
#include<iostream>
#include<string>
#include<cctype>

using namespace std;

const int MAXIMO = 1000;

struct Datos{
	char nombre_dato;
	char cadena[MAXIMO];
};

class BaseDatos{
	public:
		Datos Cadena_Datos[MAXIMO];
		
		void ActualizarBase(){
			cout << "\nIntroduce el nombre de la cadena: ";
			cin >> Cadena_Datos.nombre_dato;
			cout << "\nIntroduce la cadena de ADN: ";
			cin >> Cadena_Datos.cadena;
		};
		
		void LeerBase(){
			cout << "\nLos datos de la base son ";
			for(int i = 0; Cadena_Datos[i] != '\0'; i++)
				cout << Cadena_Datos << "\n";
		};		
};

int main(){
	BaseDatos BaseActual;
	char respuesta;
	char opcion;
	
	REGRESO:do{
		do{	
			cout << "\nDesea leer (l), actualizar la base(a) o comparar datos (c) ";
			cin >> opcion;
		}while(opcion != 'l' && opcion != 'c' && opcion != 'a');
		
		switch(opcion){
			case 'l':
				BaseActual.LeerBase(BaseActual.Cadena_Datos);
			break;
			
			case 'a':
				BaseActual.ActualizarBase(BaseActual.Cadena_Datos);
			break;
		};
		
		cout << "\n\n¿Desea finalizar (s/n)? ";
		cin >> respuesta;
	}while(respuesta != 's' && respuesta != 'n');
	
	if(respuesta == 's')
		goto REGRESO;
	else
		cout << "\n\n";
		sysrem("pause");
}
		
		
		
