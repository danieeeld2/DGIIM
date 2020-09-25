/*	Programa para trabajar con problemas de precisión y desbordamiento
*/

#include <iostream>
#include <string>

using namespace std;

int main(){
	
	//	Declaración de todas las variables
	
	const string SEPARADOR = "\n--------------------------\n";
	int chico, chico_1, chico_2;
	long grande;
	double resultado, real1, real2; real1;
	double real, otro_real; 
   float real_chico;
   double real_grande;
	
	cout.precision(15);
	
	//	Apartado A
	
	chico_1 = 123456789;
   chico_2 = 123456780;
   chico = chico_1 * chico_2;
	
	cout << " Chico 1 = " << chico_1 << "\n" ;
	cout << " Chico 2 = " << chico_2 << "\n" ;
	cout << " Chico = Chico 1 * Chico 2 =  " << chico << "\n" ;
	
	cout << " Se produce un desbordamiento, ya que el resultado debería ser 15241577639079420\n" ;
	cout << " El resultado es del orden de 10^18, imposible de almacenar en una variable de tipo int\n\n" ;
	
	//	Se produce un claro caso de desbordamiento 
	
	//	Apartado B
	
	cout << SEPARADOR ;
	
	chico_1 = 123456789;
   chico_2 = 123456780;
   grande = chico_1 * chico_2;

   cout << "\nChico 1 = " << chico_1 << "\n" ;
	cout << " Chico 2 = " << chico_2 << "\n" ;
	cout << " Grande = Chico 1 * Chico 2 =  " << grande << "\n" ;
	
	cout << " Se produce un desbordamiento, ya que el resultado debería ser 15241577639079420\n " ;
	cout << " El resultado es del orden de 10^18, imposible de almacenar en una variable de tipo long\n\n " ;	
	
	//	Se produce nuevamente un desbordamiento
	
	//	Apartado C
	
	cout << SEPARADOR ;
	
	real1 = 123.1 ;
	real2 = 124.2 ; 
	resultado = real1*real2 ;
	
	cout << "\nReal 1 = " << real1 << "\n" ;
	cout << " Real 2 = " << real2 << "\n" ;
	cout << " Resultado = Real 1 * Real 2 = " << resultado << "\n" ;
	
	cout << " El resultado debería ser 15289.02, el cual observamos que es correcto\n" ;
	cout << " No se produce desbordamiento \n\n" ;
	
	//	Apartado D
	
	cout << SEPARADOR ;
	
	real1 =  123456789.1 ;
	real2 =  123456789.1 ; 
	resultado = real1*real2 ;
	
	cout << "\nReal 1 = " << real1 << "\n" ;
	cout << " Real 2 = " << real2 << "\n" ;
	cout << " Resultado = Real 1 * Real 2 = " << resultado << "\n" ;
	
	cout << " Debería dar 15241578787227557.72\n" ;
	cout << " Pese a que no dá un error de desbordamiento, si se observa un error de precisión\n\n" ;
	
	//	Apartado E
	
	cout << SEPARADOR ;
	
	real = 2e34 ;
	otro_real = real + 1 ;
	otro_real = otro_real - real ;
	
	cout << "\nReal = " << real << "\n" ;
   cout << " otro_real = real + 1" << "\n" ;
   cout << " otro_real = otro_real - real = " << otro_real << "\n" ;   
   
	cout << " Debería dar 1" << "\n\n" ;
	cout << " Al tratarse de un número tan grende, da un error de precisión\n\n" ;
	
	// Apartado F
	
	cout << SEPARADOR ;
	
	real = 1e+300 ; 
	otro_real = 1e+200 ;
	otro_real = otro_real*real ;
	
	cout << "\nReal = " << real << "\n" ;
	cout << "otro_real = 1e+200" << "\n" ;
	cout << "otro_real = otro_real*real " << otro_real << "\n" ;
	
	cout << "El resultado debería dar 1e+500. Observamos pues un claro problema de desbordamiento " << "\n\n" ;
	
	//	Apartado G

   cout << SEPARADOR ;
	
	real_grande = 2e+150 ;
	real_chico = real_grande ;
	
	cout << "\nreal_grande (tipo double) = " << real_grande << "\n" ;
	cout << " real_chico (tipo float) = " << real_chico << "\n" ;
	cout << " real_chico = real_grande " << "\n" ;
	
	cout << " El valor de real_chico se queda como: " << real_chico << "\n\n" ;
	
	//	Se desborda	
		
	system ("pause");
}
	
	
	
	
	
	
	
