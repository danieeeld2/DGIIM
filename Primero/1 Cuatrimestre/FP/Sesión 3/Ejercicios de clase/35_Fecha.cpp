/*	Programa que implementa una estructura, fecha, del tipo
	dia/mes/año. Suponemos que el usuario introduce datos correctos
*/

#include <iostream>
#include <cstring>

using namespace std;

struct fecha{
	int dia;
	int mes;
	int year;
};

int main(){
	fecha fecha_actual;
	
	// A) Dado un dia, mes y año, asignar estos valores a una variable de tipo fecha
	
	cout << "Intoducir dia: ";
	cin >> fecha_actual.dia ;
	cout << "\nIntroducir mes: " ;
	cin >> fecha_actual.mes ;
	cout << "\nIntroducir año: " ;
	cin >> fecha_actual.year ;
	
	cout << "\n\nLa fecha actual es: " << fecha_actual.dia << "/" << fecha_actual.mes << "/" << fecha_actual.year ;
	
	// B) Día siguiente
	
	fecha fecha_siguiente;
	
	bool situacion1 = ( fecha_actual.dia+1 > 30 && (fecha_actual.mes%2 == 0 || fecha_actual.mes != 8) ) ;
	bool situacion2 = ( fecha_actual.dia+1 > 31 && (fecha_actual.mes%2 != 0 || fecha_actual.mes == 8) ) ;
	bool bisiesto1 = ( fecha_actual.year % 4 == 0 && fecha_actual.year % 100 != 0) || (fecha_actual.year % 400 == 0);
	bool febrero = fecha_actual.mes == 2 ;
	bool bisiesto2 = fecha_actual.dia+1 > 29 ;
	bool bisiesto3 = fecha_actual.dia+1 > 28 ;
	
	bool situacion = situacion1 || situacion2 ;
	bool bisiesto = febrero && (( bisiesto1 && bisiesto2 ) || ( !bisiesto1 && bisiesto3 )) ; 
	
	if ( situacion || bisiesto ){
		fecha_siguiente.dia = 1 ;
		fecha_siguiente.mes = fecha_actual.mes + 1 ;
		fecha_siguiente.year = fecha_actual.year ;
		
		if (fecha_siguiente.mes==13){
			fecha_siguiente.year = fecha_actual.year + 1 ;
			fecha_siguiente.mes = 1 ;
		}
		else
		fecha_siguiente.mes = fecha_siguiente.mes ;
	}
		
	else {
		fecha_siguiente.dia = fecha_actual.dia + 1 ;
		fecha_siguiente.mes = fecha_actual.mes ;
		fecha_siguiente.year = fecha_actual.year ;
	}
	
	cout << "\n\nEl día siguiente es: " << fecha_siguiente.dia << "/" << fecha_siguiente.mes << "/" << fecha_siguiente.year ;
	
	// C) Día anterior
	
	fecha fecha_anterior;
	
	bool situacion4 = fecha_actual.dia-1 < 1 ;
	bool situacion5 = fecha_actual.mes%2 == 0 ;
	bool situacion6 = fecha_actual.mes%2 != 0 ;
	bool bisiesto1_c = ( fecha_actual.year % 4 == 0 && fecha_actual.year % 100 != 0) || (fecha_actual.year % 400 == 0);
	bool marzo = fecha_actual.mes == 3 ;
	bool dia = fecha_actual.dia-1 < 1 ;
	bool mes = fecha_actual.mes-1 < 1 ;
		
	bool bisiesto_c = (marzo && bisiesto1_c) && dia ;
	bool no_bisiesto = (marzo && dia) && !bisiesto1_c ;
	
	if ( situacion4 ){
		
		if ( situacion5 ){
		fecha_anterior.dia = 31 ;
		fecha_anterior.mes = fecha_actual.mes - 1 ;
		fecha_anterior.year = fecha_actual.year ;
		}
		
		if ( situacion6 ){
		fecha_anterior.dia = 30 ;
		fecha_anterior.mes = fecha_actual.mes - 1 ;
		fecha_anterior.year = fecha_actual.year ;
		}
		
		if ( bisiesto_c ){
			fecha_anterior.dia = 29 ;
			fecha_anterior.mes = 2 ;
			fecha_anterior.year = fecha_actual.year ;
		}
		
		if ( no_bisiesto ){
			fecha_anterior.dia = 28 ;
			fecha_anterior.mes = 2 ;
			fecha_anterior.year = fecha_actual.year ;
		}
		
		if (mes){
			fecha_anterior.dia = 31 ;
			fecha_anterior.mes = 12 ;
			fecha_anterior.year = fecha_actual.year - 1 ;
		}
			
	}
	else{
		fecha_anterior.dia = fecha_actual.dia - 1 ;
		fecha_anterior.mes = fecha_actual.mes ;
		fecha_anterior.year = fecha_actual.year ;
	}
	
	cout << "\n\nEl día anterior es: " << fecha_anterior.dia << "/" << fecha_anterior.mes << "/" << fecha_anterior.year ;
	
	//	D) Copiar una variable tipo fecha en otra
	
	/* struct Otro_Tipo{
		fecha fecha_1 ;
		int --- ;
	}
	*/
	
	//	E) Decir si el año es bisiesto o no
	
	bool bisiesto_e = ( fecha_actual.year % 4 == 0 && fecha_actual.year % 100 != 0) || (fecha_actual.year % 400 == 0);
		
	if ( bisiesto_e )
		cout << "\n\nEl año es bisiesto. " << "\n\n" ;
	else
		cout << "\n\nEl año no es bisiesto. " << "\n\n" ;
		
	system ("pause") ;
}
		
		
	
