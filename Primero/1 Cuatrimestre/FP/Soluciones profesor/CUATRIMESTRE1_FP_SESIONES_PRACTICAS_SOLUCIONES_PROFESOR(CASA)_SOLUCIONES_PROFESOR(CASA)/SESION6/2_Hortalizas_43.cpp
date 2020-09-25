
/*
 La Union Europea ha decidido premiar al pais que mas toneladas de hortalizas exporte a lo
 largo del a–o. Se dispone de un registro de transacciones comerciales en el que aparecen
 tres valores en cada apunte. El primer valor es el indicativo del pais (E: Espa–a, F: Francia
 y A: Alemania), el segundo valor es un indicativo de la hortaliza que se ha vendido en una
 transaccion (T: Tomate, P: Patata, E: Espinaca) y el tercer valor indica las toneladas que se
 han vendido en esa transaccion. Dise–ar un programa que lea desde el teclado este registro,
 el cual termina siempre al leer un pa«õs con indicativo Õ@Õ, y que diga quŽ pa’s es el que mas
 hortalizas exporta y las toneladas que exporta. Por ejemplo, con la entrada
 E T 10 E T 4 E P 1 E P 1 E E 2 F T 15 F T 6 F P 20 A E 40 @
 el pais que mas vende es Francia con un total de 41 toneladas.
*/

#include <iostream>

using namespace std;  
   
int main(){
    const char TERMINADOR = '@';
    const string mensaje = "\nIntroduce pais (E, F o A, @ para terminar), hortaliza (T, P o E) y tonelada\n";
    
    int hortalizas_espana, hortalizas_francia, hortalizas_alemania, max_hortalizas;
    hortalizas_espana = hortalizas_francia = hortalizas_alemania = max_hortalizas = 0;
    string max_pais = "Espana";
    char entrada_pais, entrada_hortaliza;
    int entrada_tonelada;
    bool hortaliza_correcta = true, pais_correcto = true;
    
    // Lectura adelantada
    cout << mensaje;
    cin >> entrada_pais;
    
    // Comprobar si entrada correcta
    // Acumular toneladas al pais correspondiente
    // Actualizar el m‡ximo de toneladas
    while ( entrada_pais != '@' ){
        cin >> entrada_hortaliza;
        cin >> entrada_tonelada;

        pais_correcto = ( entrada_pais == 'E' || entrada_pais == 'F' || entrada_pais == 'A' );
        hortaliza_correcta = ( entrada_hortaliza == 'T' || entrada_hortaliza == 'P'
                            || entrada_hortaliza == 'E' );
        
        if ( pais_correcto && hortaliza_correcta ){
            switch ( entrada_pais ){
                case 'E':
                    hortalizas_espana = hortalizas_espana + entrada_tonelada;
                    if ( hortalizas_espana > max_hortalizas ){
                        max_hortalizas = hortalizas_espana;
                        max_pais = "Espana";
                    }
                    break;
                case 'F':
                    hortalizas_francia = hortalizas_francia + entrada_tonelada;
                    if ( hortalizas_francia > max_hortalizas ){
                        max_hortalizas = hortalizas_francia;
                        max_pais = "Francia";
                    }
                    break;
                case 'A':
                    hortalizas_alemania = hortalizas_alemania + entrada_tonelada;
                    if ( hortalizas_alemania > max_hortalizas ){
                        max_hortalizas = hortalizas_alemania;
                        max_pais = "Alemania";
                    }
                    break;
            }
        }
        
        if ( !pais_correcto )
            cout << "\nPais incorrecto\n";
        if ( !hortaliza_correcta )
            cout << "\nHortaliza incorrecta\n";
        
        cout << mensaje;
        cin >> entrada_pais;
    }
    
    cout << "\nEl pais que mas vende es " << max_pais << " con un total de " << max_hortalizas << " toneladas\n";
}
