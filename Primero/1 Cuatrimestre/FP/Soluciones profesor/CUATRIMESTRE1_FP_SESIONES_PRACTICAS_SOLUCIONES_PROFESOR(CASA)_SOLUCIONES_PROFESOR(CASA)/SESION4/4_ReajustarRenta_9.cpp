/
/*
 Reajustar renta.
 
 * Bajar un 3% la retencion fiscal a los autonomos
 * Para los no autonomos:
 - Se sube un 1% la retencion fiscal a todos los pensionistas.
 - Al resto de trabajadores se le sube un 2% la retencion fiscal.
 Una vez hecha esta subida lineal del 2 %, se le aplica
 (sobre el resultado anterior) las siguientes subidas adicionales,
 dependiendo de su estado civil y niveles de ingresos:
 1) Subir un 6% la retencion fiscal a las rentas de trabajo
 inferiores a 20.000 euros
 2) Subir un 8% la retencion fiscal a los casados con rentas
 de trabajo superiores a 20.000 euros
 3) Subir un 10% la retencion fiscal a los solteros con
 rentas de trabajo superiores a 20.000 euros
 
 Computo de porcentajes de incremento (Matematicas de tercero de la ESO).
 
 Supongamos un producto cuyo precio es P.
 1)    Un incremento del 3%, por ejemplo, se traduce en que el precio
 final del producto sera
 P+(P * 3/100) = P + 3P/100 = (100P + 3P)/100 = 103P/100 = 1.03*P
 2)    Una rebaja del 3%, por ejemplo, se traduce en que el precio final
 del producto sera 0.97*P
 3)    La aplicacion sucesiva de incrementos supone ir multiplicando
 sucesivamente los incrementos porcentuales.
 P.e. Si subimos un 3% y al resultado le aplicamos otra subida del
 5%, el precio final es 1.03*1.05*P
 
 Entradas:
 * Si la persona es un trabajador autonomo o no
 * Si es pensionista o no
 * Estado civil
 * Renta bruta (total de ingresos obtenidos)
 * Retencion
 
 */
/*********************************************************************/

#include <iostream>
using namespace std;

int main(){
    const double INDICE_VARIACION_PENSIONISTA = 1.01;
    const double INDICE_VARIACION_AUTONOMO = 0.97;
    const double INDICE_VARIACION_SALARIO_BAJO = 1.06;
    const double INDICE_VARIACION_SALARIO_NORMAL_SOLTERO = 1.1;
    const double INDICE_VARIACION_SALARIO_NORMAL_CASADO = 1.08;
    const double INDICE_VARIACION_INCREMENTO_LINEAL = 1.02;
    
    double renta_bruta, renta_neta, retencion, indice_variacion_retencion;
    bool es_autonomo, es_soltero, es_pensionista;
    

    // Lectura
    
    // Lectura de las propiedades binarias es_autonomo,
    // es_pensionista y es_soltero. Observe como se asigna
    // el valor bool adecuado de manera indirecta
    
    char opcionSN;
    
    cout << "Autonomo (S/N)? : ";
    cin >> opcionSN;
    es_autonomo = (toupper(opcionSN) == 'S');
    
    cout << "Pensionista (S/N)? : ";
    cin >> opcionSN;
    es_pensionista = (toupper(opcionSN) == 'S');
    
    cout << "Soltero (S/N)? : ";
    cin >> opcionSN;
    es_soltero = (toupper(opcionSN) == 'S');
    
    // Lectura de valores numericos
    
    cout << "Retencion inicial : ";
    cin >> retencion_inicial;
    
    cout << "Renta bruta : ";
    cin >> renta_bruta;

	if (es_autonomo)
		indice_variacion_retencion = INDICE_VARIACION_AUTONOMO;
	else if (es_pensionista)
		indice_variacion_retencion = INDICE_VARIACION_PENSIONISTA;
    else{
        indice_variacion_retencion = INDICE_VARIACION_INCREMENTO_LINEAL;
        if (renta_bruta < 20000)
            indice_variacion_retencion = indice_variacion_retencion * INDICE_VARIACION_SALARIO_BAJO;
        else if (es_soltero)
            indice_variacion_retencion = indice_variacion_retencion * INDICE_VARIACION_SALARIO_NORMAL_SOLTERO;
        else
            indice_variacion_retencion = indice_variacion_retencion * INDICE_VARIACION_SALARIO_NORMAL_CASADO;
    }

	retencion = indice_variacion_retencion * retencion;
	renta_neta = renta_bruta * (1 - retencion/100.0);

	cout << "\nRenta final = " << renta_neta;
    cout << "\n\n";
}

