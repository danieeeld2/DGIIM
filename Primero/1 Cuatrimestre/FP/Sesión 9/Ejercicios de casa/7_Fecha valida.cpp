/*	Módulo que determina si 
	una fecha es válida o no */
	
#include<iostream>

using namespace std;

bool Fecha_Valida(int anio, int mes, int dia){
	bool condicion1, condicion2, condicion3;
	bool meses_pares;
	bool febrero;
	bool bisiesto;
	bool es_valido;
	
	condicion1 = anio > 0;
	condicion2 = mes > 0 && mes < 13;
	condicion3 = dia > 0 && dia < 32;
	
	meses_pares = (mes % 2 != 0) && (mes != 7);
	if(meses_pares)
		condicion3 = dia > 0 && dia < 31;
		
	febrero = mes == 2;
	if(febrero)
		condicion3 = dia > 0 && dia < 29;	
		
	bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
	if(febrero && bisiesto)
		condicion3 = dia > 0 && dia < 30;
		
	es_valido = condicion1 && condicion2 && condicion3;
	if(es_valido)
		return true;
	else
		return false;		
}

//	Para comprobar

int main(){
	int dato1, dato2, dato3;
	bool valido;
	
	cout << "Introduce el año: ";
	cin >> dato1;
	cout << "\nIntroduce el mes: ";
	cin >> dato2;
	cout << "\nIntroduce el dia: ";
	cin >> dato3;
	
	valido = Fecha_Valida(dato1, dato2, dato3);
	
	if(valido)
		cout << "\nFecha valida ";
	else
		cout << "\nFecha no valida ";
		
	cout << "\n\n";
	system("pause");
}
	
	
