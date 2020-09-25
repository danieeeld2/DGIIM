#include<iostream>

using namespace std;

/**
 *  @brief Clase Fecha
 *
 * Un objeto de la clase Fecha representa una
 * fecha del calendario, compuesta por tres valores enteros que
 * representan, respectivamente, el dia, mes y año. Lo representamos
 * mediante la terna siguiente:
 *
 * (dia, mes, anio).
 */
class Fecha {
    private:
        int  dia;  /**< dia del mes */
        int  mes;  /**< mes del año */
        int  anio; /**< año de la fecha */
        /**
         * @brief Determina si la fecha es valida
         * @return true si es valida, false en caso contrario
         */
        bool EsValida();
        /**
         * @brief Determina si la fecha esta en anio bisiesto
         * @return true si es bisiesto, false si no
         */
        bool EsBisiesto();
    public:
        /**
         *@brief Constructor por defecto
         *@post Inicializa a la fecha 01/01/0
         */
        Fecha();
        /**
         * @brief Constructor de la clase
         * @param d Dia del mes
         * @param m Mes del año
         * @param a Año de la fecha
         * @pre Los parametros d, m y a deben conformar una fecha valida
         * @post si la fecha no es valida, inicializa a 01/01/0
         */
        Fecha(int d, int m, int a);
        /**
         * @brief Constructor de copia
         * @param otro Fecha que se va a copiar
         */
        Fecha(const Fecha & otro );
        /**
         * @brief Modifica la fecha de entrada al la fecha del dia siguiente
         * @post modifica los datos miembro a la fecha siguiente en el calendario
         */
        void Siguiente();
        /**
         * @brief Modifica la fecha de entrada al la fecha del dia siguiente
         * @post modifica los datos miembro a la fecha anterior en el calendario
         */
        void Anterior();
        /**
         * @brief Funcion para mostrar por consola una fecha
         */
        void Mostrar();
        /*
         *
         *
         Ampliacion: usando operadores de incremento y decremento
         *
         *
         */
        /**
         * @brief Sobrecarga del operador de preincremento ++
         * @param n Argumento fantasma (no se utiliza) para distinguir del preincremento
         * @post modifica los datos miembro a la fecha siguiente en el calendario
         */
        Fecha & operator++();
        /**
         * @brief Sobrecarga del operador de predecremento --
         * @param n Argumento fantasma (no se utiliza) para distinguer del predecremento
         * @post modifica los datos miembro a la fecha anterior en el calendario
         */
        Fecha & operator--();
};

int main (){
    Fecha una(28,2,2004);
    Fecha otra(1,1,2004);

    una.Mostrar();
    otra.Mostrar();
    
    una.Siguiente();
    ++una;
    una.Mostrar();
    
    --otra;
    
    otra.Mostrar();
}



bool Fecha::EsValida(){
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

bool Fecha::EsBisiesto(){
    return (anio % 4 == 0) || ( (anio % 100 != 0) && (anio % 400 == 0) );
}

Fecha::Fecha(){
    dia = 1; mes = 1; anio = 0;
}

Fecha::Fecha(int d, int m, int a){
    dia = d;
    mes = m;
    anio = a;
    if ( !EsValida() ){
        dia = 1;
        mes = 1;
        anio = 0;
    }
}

Fecha::Fecha(const Fecha & otro ){
    dia = otro.dia;
    mes = otro.mes;
    anio = otro.anio;
}

void Fecha::Mostrar(){
    cout << dia << "/" << mes << "/" << anio << "\n";
}

void Fecha::Siguiente(){
    int dias_mes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if ((dia < dias_mes[mes - 1]) || (EsBisiesto() && dia < 29))
        dia++;
    else {
        dia = 1;
        if (mes < 12) {
            mes = mes + 1;
        } else {
            mes = 1;
            anio = anio + 1;
        }
    }
}

void Fecha::Anterior(){
    int dias_mes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (dia > 1) {
        dia = dia - 1;
    } else if (mes > 1) {
        mes = mes - 1;
        dia = (mes != 2 ? dias_mes[mes - 1] :
               (EsBisiesto() ? 29 : 28));
    } else {
        dia = 31;
        mes = 12;
        anio = anio - 1;
    }
}

Fecha & Fecha::operator++(){
    Siguiente();
    return *this; // *this significa "el objeto al que se le aplica el método"
}

Fecha & Fecha::operator--(){
    Anterior();
    return *this; // *this significa "el objeto al que se le aplica el método"
}


