/*	Programa para llevar a cabo la contabilidad
	de una empresa, que tiene tres sucusales */
	
#include <iostream>

using namespace std;

int main(){
	
	int sucursal;
	int codigo_producto;
	int numero_ventas;
	const int TERMINADOR = -1;
	int contador;
	int ventas1;
	int ventas2;
	int ventas3;
	
	contador = 0;	
	sucursal = 0;
	codigo_producto = 0;
	numero_ventas = 0;
	ventas1 = 0;
	ventas2 = 0;
	ventas3 = 0;
	
	while ( sucursal != TERMINADOR ){
		do{
			cout << "\n\nIntroduzca una sucursal: ";
			cin >> sucursal;
			
			if(contador == 1 )
				cout << "\nSolo tienes tres sucursales (1,2,3). En caso de querer finalizar, introduce -1 ";
				
			contador++;
		}while ( sucursal != -1 && sucursal != 1 && sucursal != 2 && sucursal != 3 );
		
		if ( sucursal == TERMINADOR )
			cout << "\nEl programa finalizará. ";
		else{
		
		contador = 0;		//	Reiniciamos contador
		
		do{
			cout << "\nIntroduzca el código del producto: ";
			cin >> codigo_producto;
			
			if(contador == 1 )
				cout << "\nSolo tienes tres códigos de producto (1,2,3) ";
				
			contador++;
		}while ( codigo_producto != -1 && codigo_producto != 1 && codigo_producto != 2 && codigo_producto != 3 );
		
		cout << "\nIntroduzca número de unidades vendidas: ";
		cin >> numero_ventas;
		
		cout << "\nSUCURSAL: " << sucursal;
		cout << "\nPRODUCTO: " << codigo_producto;
		cout << "\nUNIDADES VENDIDAS: " <<	numero_ventas;	
		
		contador = 0;		//	Reiniciamos contador
		
		if ( sucursal == 1 )
			ventas1 = ventas1 + numero_ventas;
		
		if ( sucursal == 2 )
			ventas2 = ventas2 + numero_ventas;
			
		if ( sucursal == 3 )
			ventas3 = ventas3 + numero_ventas;
			
		cout << "\n\nMayor número de ventas: ";
		
		if ( ventas1 > ventas2 ){
			cout << "\nSUCURSAL: 1 ";
			cout << "\nTOTAL DE VENTAS: " << ventas1;
		}
		else{
			if ( ventas2 > ventas3 ){
				cout << "\nSUCURSAL: 2 ";
				cout << "\nTOTAL DE VENTAS: " << ventas2;
			}
			else{ 
				cout << "\nSUCURSAL: 3 ";
				cout << "\nTOTAL DE VENTAS: " << ventas3;	
			}
		}
		}
	};
	
	cout << "\n\n";
	
	system ("pause");
}
