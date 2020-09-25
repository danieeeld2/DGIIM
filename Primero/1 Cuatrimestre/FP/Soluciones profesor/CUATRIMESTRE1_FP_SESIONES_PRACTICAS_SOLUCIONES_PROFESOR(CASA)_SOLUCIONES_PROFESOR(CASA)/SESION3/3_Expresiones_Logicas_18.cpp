
/*
    Escribid una expresion logica que sea verdadera si
    una variable de tipo caracter llamada letra
    es una letra minuscula y falso en otro caso.
       
    Escribid una expresion logica que sea verdadera si
    una variable de tipo entero llamada edad 
    es menor de 18 o mayor de 65.
    
    IMPORTANTE: Cuando se imprime por pantalla (con cout) una expresion
    logica que es true, se imprime 1. Si es false, se imprime un 0.
    En el tema 2 veremos la razon.
*/

#include <iostream>
using namespace std;

int main(){
    
    bool expresion_a = 2 + 3 < 5 + 8;
    cout << "2+3<5+8: " << expresion_a << endl;
    
    // Es un dato booleano, y devuelve 1 (true), se recomiendan los parŽntesis
    
    bool expresion_b = 2 < 3 < 4;
    cout << "2 < 3 < 4: " << expresion_b << endl;
    
    // Es un dato booleano, y devuelve 1 (true) siempre, pero
    // no es correcto, si cambiamos 2 y 3, siempre devuelve
    // true (por ejemplo, con 2<1<4). Primero se evalua 2<3, devuelve 1 (true)
    // y luego compara 1<4.
    

    double expresion_c = 7/3 + 4.0;
    cout << "7/3 + 4.0: " << expresion_c << endl;
    
    // dato double que almacena 6
    
    int x = 4, y = 4, z = 4;
    bool expresion_d = ((x == 4) && (y == 3)) || ((z != 2) == (1 != 2));
    cout << "x == 4 && y == 3 || z! = 2 == 1! = 2: " << expresion_d << endl;
    
    // dato booleano, pero hay que colocar parentesis, el resultado depende de eso
    
    int xx;
    bool expresion_e = xx <= 4 || xx >= 4;
    cout << "x <= 4 || x >= 4: " << expresion_e << endl;
    
    // expresion booleana correcta que siempre devuelve 1 (true)
    
    bool expresion_f = xx < 4 && xx > 4;
    cout << "x < 4 || x > 4: " << expresion_f << endl;
    
    // expresion booleana correcta que siempre devuelve 0 (false)
    
    z=4;
    char a='s';
    bool expresion_g = z > 6 || (a < 'z' && a > 'a') || z < 6;
    cout << "z > 6 || a < 'z' && a > 'a' || z < 6: " << expresion_g << endl;
    
    // expresion booleana, necesita parentesis, entonces devolvera un valor
    // dependiendo de como los pongamos
}
