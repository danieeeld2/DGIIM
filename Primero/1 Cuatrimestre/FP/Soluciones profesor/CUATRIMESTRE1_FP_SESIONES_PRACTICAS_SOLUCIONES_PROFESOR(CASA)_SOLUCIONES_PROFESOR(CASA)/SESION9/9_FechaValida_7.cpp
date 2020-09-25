/* Escribir un mdulo para saber, dado un anio, mes y dia de entrada, si la fecha indicada es valida o no.
 */

#include <iostream>

using namespace std;

/* Funcion FechaValida
 * @brief Determina si una fecha es valida
 * @param anio, mes y dia son forman la fecha a considerar
 * @return true si es valida, false si no
 */
bool FechaValida (int anio, int mes, int dia);

int main(){
    int anio, mes, dia;
    
    cout << "\nIntroduce fecha (anio, mes y dia)";
    cin >> anio >> mes >> dia;
    
    if ( FechaValida(anio,mes,dia) )
        cout << "\nFecha valida\n";
    else
        cout << "\nFecha no valida\n";
}

bool FechaValida (int anio, int mes, int dia){
    bool mes_valido = mes >= 1 && mes <= 12;
    bool dia_valido_normal = dia >= 1 && dia <= 28;
    bool valido_normal = mes_valido && dia_valido_normal;
    bool bisiesto = (anio % 4 == 0) || ( (anio % 100 != 0) && (anio % 400 == 0) );
    bool dia_31 = (dia == 31) && (mes == 1 || mes == 3 || mes == 5 ||
                                  mes == 7 || mes == 8 || mes == 10 || mes == 12 );
    bool dia_30 = (dia == 30) && (mes != 2) && mes_valido;
    bool dia_29 = (dia == 29) && (mes != 2) && mes_valido;
    bool dia_29_bisiesto = (dia == 29) && (mes == 2) && bisiesto;
    bool fecha_valida = valido_normal || dia_31 || dia_30 || dia_29 || dia_29_bisiesto;
    
    return fecha_valida;
}

