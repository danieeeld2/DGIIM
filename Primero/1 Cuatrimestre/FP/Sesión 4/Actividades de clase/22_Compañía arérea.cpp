/*	Programa para calcular el precio de un billete
	de una compañía de avión dada unas determinadas
	condiciones
*/

#include <iostream>

using namespace std;

int main(){
	const int PRECIO_BASE = 150;
	double distancia; 					//	En kilómetros
	const double REBAJA_A = 0.03;
	const double REBAJA_B = 0.04;
	const double REBAJA_C = 0.05;
	const int PROMOCION = 15;
	const double SUBIDA_POR_KILOMETRO = 0.10;
	char opcion1;
	char opcion2;
	bool condicion_promocion;
	bool cliente_previo;
	double precio_final;
	double precio_final_2;
	
	cout << "Introduzca la distancia del vuelo (en km): ";
	cin >> distancia;
	
	/*	Usamos un bucle do-while para preguntar
		al usuario sobre una serie de datos que debe responder
		con sí y no */
	
	do{
		cout << "\nDiga si su vuelo se realiza en la fecha de la promoción o no (s/n) ";
		cin >> opcion1;
		
		opcion1 = toupper (opcion1);
	}while
		(opcion1 != 'S' && opcion1 != 'N');    
     
   condicion_promocion = opcion1 == 'S';
   
   do{
   	cout << "\nDiga si es cliente previo de la empresa o no (s/n) ";
   	cin >> opcion2;
   	
   	opcion2 = toupper (opcion2);
	}while
		(opcion2 != 'S' && opcion2 != 'N');
		
	cliente_previo = opcion2 == 'S';
	
	/*	Para esta parte tendremos en cuenta la forma en la
		que el compilador evalua las variables.
		Comenzamos por las condiciones que implican distancia */
		
	/*	Para el descuento de 15 euros por la promoción, tendremos
		en cuenta que se aplique al principio */
		
	//	Caso A: Si se aplica C se puede aplicar A y B
	
	precio_final = PRECIO_BASE;
	
	if ( condicion_promocion)
		precio_final = PRECIO_BASE - PROMOCION;
	
	if ( distancia > 200 ){
		precio_final = precio_final + ( (distancia - 200) * SUBIDA_POR_KILOMETRO);
		
		if ( distancia > 1100 )
			precio_final = precio_final - (precio_final * REBAJA_B);
		else
			if ( distancia > 600 )
				precio_final = precio_final - (precio_final * REBAJA_A);
   }
   
   if ( cliente_previo )
   	precio_final = precio_final - (precio_final * REBAJA_C);
   	
   cout << "\nEl precio final, aplicando la rebaja C de forma adicional a A y B es: " << precio_final << " euros ";
	
	// CASO B: Si se aplica C no se aplica A y B
	
	precio_final_2 = PRECIO_BASE;
	
	if ( condicion_promocion )
		precio_final_2 = PRECIO_BASE - PROMOCION;
		
	if ( distancia > 200 )
		precio_final_2 = precio_final_2 + ( (distancia - 200) * SUBIDA_POR_KILOMETRO );
		
	if ( cliente_previo )
		precio_final_2 = precio_final_2 - (precio_final_2 * REBAJA_C);
	else
		if ( distancia > 1100 )
			precio_final_2 = precio_final_2 - (precio_final_2 * REBAJA_B);
		else
			if ( distancia > 600 )
				precio_final_2 = precio_final_2 - (precio_final_2 * REBAJA_A);
				
	cout << "\nEl precio final, aplicando la rebaja C de forma exlusiva a A y B es: " << precio_final_2 << " euros ";
	cout << "\n\n";
	
	system ("pause");
}
	
