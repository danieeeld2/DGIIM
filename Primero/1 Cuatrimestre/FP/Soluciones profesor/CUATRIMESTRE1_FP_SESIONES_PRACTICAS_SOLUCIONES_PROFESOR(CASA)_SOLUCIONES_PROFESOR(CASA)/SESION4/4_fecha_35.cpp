#include <iostream>

using namespace std; 

struct Fecha{
    int anio, mes, dia;
};


int main () {
    Fecha fecha;
    
    cout << "\nIntroduce la fecha actual en formato: dia (1-31), mes (1-12), año.\n";
    cin >> fecha.dia >> fecha.mes >> fecha.anio;

    Fecha fecha_antes = fecha, fecha_despues = fecha;
    fecha_despues.dia++;
    fecha_antes.dia--;
    // años conflictivos
    bool bisiesto = (fecha.anio % 4 == 0) && (fecha.anio % 100 != 0) 
	|| ((fecha.anio % 100 == 0) && (fecha.anio % 400 == 0));
    // dias conflictivos
    bool dia_31 = fecha.dia == 31;
    bool dia_30 = fecha.dia == 30;
    bool dia_28 = fecha.dia == 28;
    bool dia_29 = fecha.dia == 29;
    bool dia_1 = fecha.dia == 1;
    // meses
    bool mes_31a = (fecha.mes == 1) || (fecha.mes == 3) || (fecha.mes == 5);
    bool mes_31b = (fecha.mes == 7) || (fecha.mes == 8) || (fecha.mes == 10);
    bool mes_31 = mes_31a || mes_31b;
    bool mes_dic = fecha.mes == 12;
    bool mes_feb = fecha.mes == 2;
    bool mes_30 = !(mes_31 || mes_dic || mes_feb);
    
    bool mes_mar = fecha.mes == 3;
    bool mes_ene = fecha.mes == 1;
    bool mes_post_31a = (fecha.mes == 2) || (fecha.mes == 4) || (fecha.mes == 6);
    bool mes_post_31b = (fecha.mes == 8) || (fecha.mes == 9) || (fecha.mes == 11);
    bool mes_post_31 = mes_post_31a || mes_post_31b;
    bool mes_post_30 = (fecha.mes == 5) || (fecha.mes == 7) ||
    (fecha.mes == 10) || (fecha.mes == 12);
    // variable para el dia siguiente
    bool conflictivo_despues = dia_31 || (dia_30 && mes_30) ||
    (mes_feb && dia_29) || (mes_feb && dia_28 && !bisiesto);
    // distincion de casos para el dia antes
    int casos = 1;
    if (mes_post_30)
        casos = 2;
    if (mes_mar)
        casos = 3;
    
    // calculo dia siguiente
    if (conflictivo_despues){
        fecha_despues.dia = 1;
        fecha_despues.mes++;
        if ( mes_dic ){
            fecha_despues.mes = 1;
            fecha_despues.anio++;
        }
    }
    // calculo dia antes
    if (dia_1){
        fecha_antes.mes--;
        switch (casos){
            case 1:
                fecha_antes.dia = 31;
                if (fecha.mes == 1){
                    fecha_antes.mes = 12;
                    fecha_antes.anio--;
                }
                break;
            case 2:
                fecha_antes.dia = 30;
                break;
            case 3:
                if (bisiesto)
                   fecha_antes.dia = 29;
                else
                    fecha_antes.dia = 28;
        }
    }
    
    cout << "\nLa fecha actual es: " << fecha.dia << "/" << fecha.mes << "/" << fecha.anio << endl;
    cout << "\nMañana es: " << fecha_despues.dia << "/" << fecha_despues.mes << "/" << fecha_despues.anio << endl;
    cout << "\nAyer fue: " << fecha_antes.dia << "/" << fecha_antes.mes << "/" << fecha_antes.anio << endl;
}
