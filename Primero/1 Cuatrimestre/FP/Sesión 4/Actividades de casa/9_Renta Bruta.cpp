/*	Programa que reajusta la renta bruta
	de una persona en función de sus datp¡os fiscales
*/

#include <iostream>
#include <cctype>

using namespace std;
 
int main(){
   const int LIMITE_SALARIO_BAJO = 20000;
   const double IV_RETENCION_PENSIONISTA = 1.01;        
   const double IV_RETENCION_AUTONOMO = 0.97;
   const double IV_RETENCION_SALARIO_BAJO = 1.06;
   const double IV_RETENCION_SALARIO_NORMAL_SOLTERO = 1.1;
   const double IV_RETENCION_SALARIO_NORMAL_CASADO = 1.08;
   const double IV_RETENCION_INCREMENTO_LINEAL = 1.02;  
    
   double renta_bruta, renta_neta, retencion, retencion_final, iv_retencion;
   bool es_autonomo, es_soltero, es_pensionista;
   char opcion; 
    
     
   do{
      cout << "\nIndique si la persona es un trabajador autónomo o no (s/n) ";      
      cin >> opcion;
      opcion = toupper(opcion);
    }
	while 
		(opcion != 'S' && opcion != 'N');    
     
   es_autonomo = opcion == 'S';
     
   do{
      cout << "\nIndique si la persona es pensionista o no (s/n) ";     
      cin >> opcion;
      opcion = toupper(opcion);
    }
	while 
		(opcion != 'S' && opcion != 'N');    
     
   es_pensionista = opcion == 'S';
     
   do{
   	cout << "\nIndique si la persona está soltera o no (s/n) " ;       
      cin >> opcion ;
      opcion = toupper(opcion) ;
    }
	while 
	 	(opcion != 'S' && opcion != 'N') ;    
     
   es_soltero = opcion == 'S';
     
     
   cout << "\nIndique la Renta Bruta: " ;     
   cin >> renta_bruta ;
   cout << "\nIndique la Retención a aplicar (en %): " ;      
   cin >> retencion ;
   	 
   if (es_autonomo)
        iv_retencion = IV_RETENCION_AUTONOMO ;
   else if (es_pensionista)
        iv_retencion = IV_RETENCION_PENSIONISTA ;
   else{
      iv_retencion = IV_RETENCION_INCREMENTO_LINEAL ;
 
   if (renta_bruta < LIMITE_SALARIO_BAJO)
         iv_retencion = iv_retencion * IV_RETENCION_SALARIO_BAJO ; 
   else if (es_soltero)
         iv_retencion = iv_retencion * IV_RETENCION_SALARIO_NORMAL_SOLTERO ;
   else
         iv_retencion = iv_retencion * IV_RETENCION_SALARIO_NORMAL_CASADO ;
   }
 
   retencion_final = retencion * iv_retencion ;
   renta_neta = renta_bruta * (1 - retencion_final/100.0) ;
    
   cout << "\nRenta final = " << renta_neta ;
   cout << "\n\n" ;

   system("pause") ;
}
