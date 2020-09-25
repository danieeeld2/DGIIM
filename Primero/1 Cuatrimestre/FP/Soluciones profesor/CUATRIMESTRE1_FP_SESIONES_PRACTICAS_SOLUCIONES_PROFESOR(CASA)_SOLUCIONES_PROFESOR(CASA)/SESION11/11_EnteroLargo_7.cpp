#include <iostream>

using namespace std;

/**
 *  @brief Clase EnteroLargo
 *
 * Un objeto c de la clase EnteroLargo representa un
 * entero, compuesto por una lista de cifras que representan sus digitos
 * y un signo.
 */
class EnteroLargo{
	private:
		static const int MAXIMA_LONGITUD = 100; /**< maxima longitud posible del entero */
        bool signo; /**< signo del entero */
		int longitud; /**< longitud real del entero */
		int digitos[MAXIMA_LONGITUD]; /**< vector de digitos del entero */
	public:
        /**
         *@brief Constructor por defecto
         *@post inicializa al entero 0
         */
        EnteroLargo();
        /**
         *@brief Constructor a partir de un entero
         *@param entero El entero del que construir el objeto
         */
        EnteroLargo(int entero);
        /**
         *@brief Constructor a partir de una lista de enteros
         *@param l longitud de la lista
         *@param d lista de enteros
         *@param sig signo del entero, 1 para positivo o cero, 0 para negativo
         */
        EnteroLargo(int l, int d[MAXIMA_LONGITUD], bool sig);
        /**
         *@brief Cambia el signo de un entero (multiplica por -1)
         *@retval El entero con el signo cambiado
         */
        EnteroLargo CambiarSigno ();
        /**
         *@brief Compara dos enteros
         *@param otro el entero con el que comparar
         *@retval true si el entero es menor que otro, false en otro caso
         */
        bool EsMenor(EnteroLargo otro);
        /**
         *@brief Compara dos enteros
         *@param otro el entero con el que comparar
         *@retval true si son iguales, false en otro caso
         */
        bool EsIgual(EnteroLargo otro);
        /**
         *@brief Compara dos enteros
         *@param otro el entero con el que comparar
         *@retval true si el entero es mayor que otro, false en otro caso
         */
        bool EsMayor(EnteroLargo otro);
        /**
         *@brief Funcion para mostrar por consola el entero
         */
        void MostrarEntero();
        /**
         *@brief Funcion para sumar dos enteros
         *@param otro El otro sumando
         *@retval el entero suma
         */
        EnteroLargo Suma( EnteroLargo otro); // No esta completo, solo positivos
        /**
         *@brief Funcion para restar dos enteros
         *@param otro El sustraendo
         *@retval el entero diferencia
         */
        EnteroLargo Resta( EnteroLargo otro); // sin implementar
        /**
         *@brief Funcion para multiplicar dos enteros
         *@param otro El multiplicador
         *@retval el entero productp
         */
        EnteroLargo Producto( EnteroLargo otro); // sin implementar
        /*
         *
         * Ampliacion: utilizando operadores
         *
         */
        bool operator< (EnteroLargo otro);
        bool operator> (EnteroLargo otro);
        bool operator== (EnteroLargo otro);
        bool operator!= (EnteroLargo otro);
        bool operator>= (EnteroLargo otro);
        bool operator<= (EnteroLargo otro);
};

int main(){
    int vector1[] = {1,4,3,4,5,1,9};
    int vector2[] = {7,4,5,3,2,6,4};
    int entero = 3024;
    
    EnteroLargo entero1(7,vector1,0);
    EnteroLargo entero2(7,vector2,0);
    EnteroLargo entero3(entero);
    
    entero1.MostrarEntero();
    entero2.MostrarEntero();
    entero3.MostrarEntero();
    
    
    cout << ( entero1 < entero2 ) << "\n";
    cout << ( entero1 > entero2 ) << "\n";
    cout << ( entero1 == entero2 ) << "\n";
    cout << ( entero1 != entero2 ) << "\n";
}


EnteroLargo::EnteroLargo(){
    longitud = 1;
    digitos[0] = 0;
}

EnteroLargo::EnteroLargo(int entero){
    int remanente;
    longitud = 0;
    
    if ( entero < 0 ){
        remanente = - entero;
        signo = 0;
    }
    else{
        remanente = entero;
        signo = 1;
    }
    
    while ( remanente != 0 ){
        digitos[longitud] = remanente % 10;
        longitud++;
        remanente = remanente / 10;
    }
}

EnteroLargo::EnteroLargo(int l, int d[MAXIMA_LONGITUD], bool sig){
    signo = sig;
    longitud = l;
    for (int i=0; i<longitud; i++)
        digitos[i] = d[i];
}

EnteroLargo EnteroLargo::CambiarSigno (){
    EnteroLargo opuesto(longitud,digitos,!signo);
    return opuesto;
}

bool EnteroLargo::EsMenor(EnteroLargo otro){
    bool es_menor = true;
    
    if ( signo && !otro.signo )
        es_menor = false;
    
    if ( signo && otro.signo ){
        if ( longitud == otro.longitud ){
            int i = longitud-1;
            while ( digitos[i] == otro.digitos[i] && i>=0)
                i--;
            if ( i>=0 && digitos[i] > otro.digitos[i] )
                es_menor = false;
        }
        if ( longitud > otro.longitud )
            es_menor = false;
    }
    
    if ( !signo && !otro.signo ){
        if ( longitud == otro.longitud ){
            int i = longitud-1;
            while ( digitos[i] == otro.digitos[i] && i>=0)
                i--;
            if ( i>=0 && digitos[i] < otro.digitos[i] )
                es_menor = false;
        }
        if ( longitud < otro.longitud )
            es_menor = false;
    }
    
    return es_menor;
}

bool EnteroLargo::EsIgual(EnteroLargo otro){
    bool es_igual = true;
    
    if ( longitud == otro.longitud && signo == otro.signo ){
        for (int i=0; i<longitud && es_igual; i++)
            if ( digitos[i] != otro.digitos[i] )
                es_igual = false;
    }
    else
        es_igual = false;
    
    return es_igual;
}

bool EnteroLargo::EsMayor(EnteroLargo otro){
    return !EsIgual(otro) && !EsMenor(otro);
}

bool EnteroLargo::operator< (EnteroLargo otro){
    return EsMenor(otro);
}

bool EnteroLargo::operator> (EnteroLargo otro){
    return EsMayor(otro);
}

bool EnteroLargo::operator== (EnteroLargo otro){
    return EsIgual(otro);
}

bool EnteroLargo::operator!= (EnteroLargo otro){
    return !EsIgual(otro);
}

bool EnteroLargo::operator>= (EnteroLargo otro){
    return EsIgual(otro) || EsMayor(otro);
}

bool EnteroLargo::operator<= (EnteroLargo otro){
    return EsIgual(otro) || EsMenor(otro);
}

EnteroLargo EnteroLargo::Suma( EnteroLargo otro){
    int acarreo = 0;
    EnteroLargo suma;
    
    if ( signo && otro.signo ){
        suma.signo = true;
        while ( suma.longitud < longitud && suma.longitud < otro.longitud ){
            suma.digitos[suma.longitud] = (digitos[suma.longitud] + otro.digitos[suma.longitud] + acarreo)%10;
            if ( digitos[suma.longitud] + otro.digitos[suma.longitud] + acarreo > 9 )
                acarreo = 1;
            else
                acarreo = 0;
            suma.longitud++;
        }
        if ( longitud <= suma.longitud ){
            for (int i=suma.longitud; i<otro.longitud; i++){
                suma.digitos[i] = (otro.digitos[i] + acarreo) % 10;
                if ( otro.digitos[i] + acarreo > 9)
                    acarreo = 1;
                else
                    acarreo = 0;
                suma.longitud++;
            }
            if ( acarreo == 1 ){
                suma.digitos[suma.longitud] = 1;
                suma.longitud++;
            }
        }
        else{
            for (int i=suma.longitud; i<longitud; i++){
                suma.digitos[i] = (digitos[i] + acarreo) % 10;
                if ( digitos[i] + acarreo > 9)
                    acarreo = 1;
                else
                    acarreo = 0;
            }
            if ( acarreo == 1 ){
                suma.digitos[suma.longitud] = 1;
                suma.longitud++;
            }
        }
    }
    
    if ( signo && !otro.signo ){}
    if ( !signo && otro.signo ){}
    if ( !signo && !otro.signo ){
        suma = CambiarSigno().Suma(otro.CambiarSigno());
    }
    
    return suma;
}

EnteroLargo EnteroLargo::Resta( EnteroLargo otro){return otro;}
EnteroLargo EnteroLargo::Producto( EnteroLargo otro){return otro;}

void EnteroLargo::MostrarEntero(){
    if (signo == 0)
        cout << "-";
    for (int i=longitud-1; i>=0; i--)
        cout << digitos[i];
    cout << "\n";
}
