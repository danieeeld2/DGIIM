#include <iostream>

using namespace std;

/**
*  @brief Clase Complejo
*
* Un objeto c de la clase Complejo representa un
* numero complejo, compuestos por dos valores flotantes que
* representan, respectivamente, la parte real e imaginaria. Lo representamos
*
* (r,i)
*/
class Complejo {
private:
    double real; /**< representa la parte real del complejo */
    double imaginaria; /**< representa la parte imaginaria del complejo */
public:
    /**
     * @brief Constructor sin parametros de la clase
     * @post asigna el complejo (0,0), es decir, 0+0*i
     */
    Complejo(){
        real = 0;
        imaginaria = 0;
    }
    /**
     * @brief Constructor con parametros de la clase
     * @param r Parte real del complejo a construir
     * @param i Parte imaginaria del complejo a construir
     */
    Complejo(double r, double i): real(r),imaginaria(i) {}
    /**
     * @brief Devuelve la parte real de un complejo
     * @return la parte real del complejo
     */
    double GetReal() const {
        return real;
    }
    /**
     * @brief Devuelve la parte imaginaria de un complejo
     * @return la parte imaginaria del complejo
     */
    double GetImaginaria() const {
        return imaginaria;
    }
    /**
     * @brief Suma de complejos
     * @param sumando Segundo sumando
     * @return La suma de los complejos
     * @example Complejo suma = c.Suma(d);
     */
    Complejo Suma ( const Complejo & sumando ){
        Complejo suma;
        suma.real = real + sumando.real;
        suma.imaginaria = imaginaria + sumando.imaginaria;
        
        return suma;
    }
    /**
     * @brief diferencia de complejos
     * @param sustraendo El sustraendo
     * @return La diferencia de los complejos
     * @example Complejo diferencia = c.Resta(d);
     */
    Complejo Resta ( const Complejo & sustraendo ){
        Complejo resta;
        resta.real = real - sustraendo.real;
        resta.imaginaria = imaginaria - sustraendo.imaginaria;
        
        return resta;
    }
    /**
     * @brief producto de complejos
     * @param multiplicador El multiplicador
     * @return El producto de los complejos
     * @example Complejo prod = c.Producto(d);
     */
    Complejo Producto ( const Complejo & multiplicador ){
        Complejo producto;
        producto.real = real * multiplicador.real -  imaginaria * multiplicador.imaginaria;
        producto.imaginaria = real * multiplicador.imaginaria + imaginaria * multiplicador.real;
        
        return producto;
    }
    /**
     * @brief fucion para mostrar por consola un complejo
     */
    void Mostrar(){
        cout << real << "+" << imaginaria << "i" << "\n";
    }
    /*
     *
     *
     Usando operadores aritmeticos
     *
     *
     */
    /**
     * @brief Operador aritmético +
     * @param sumando Segundo sumando
     * @return La suma de los complejos
     * @example Complejo suma = c + d;
     */
    Complejo operator+ ( const Complejo & sumando ){
        Complejo suma;
        suma.real = real + sumando.real;
        suma.imaginaria = imaginaria + sumando.imaginaria;
        
        return suma;
    }
    /**
     * @brief Operador aritmetico -
     * @param sustraendo El sustraendo
     * @return La diferencia de los complejos
     * @example Complejo resta = c + d;
     */
    Complejo operator- ( const Complejo & sustraendo ){
        Complejo resta;
        resta.real = real - sustraendo.real;
        resta.imaginaria = imaginaria - sustraendo.imaginaria;
        
        return resta;
    }
    /**
     * @brief Sobrecarga operador *
     * @param multiplicador El multiplicador
     * @return El producto de los complejos
     * @example Complejo prod = c * d;
     */
    Complejo operator* ( const Complejo & multiplicador ){
        Complejo producto;
        producto.real = real * multiplicador.real -  imaginaria * multiplicador.imaginaria;
        producto.imaginaria = real * multiplicador.imaginaria + imaginaria * multiplicador.real;
        
        return producto;
    }
};

int main(){
    double real1, real2, imaginario1, imaginario2;
	cout << "\nIntroduzca dos complejos:\n";
    cin >> real1 >> imaginario1 >> real2 >> imaginario2;
    
    Complejo complejo1(real1,imaginario1), complejo2(real2, imaginario2);
    
    Complejo suma = complejo1 + complejo2;
    Complejo diferencia = complejo1 - complejo2;
    Complejo producto = complejo1 * complejo2;
    
    suma.Mostrar();
    diferencia.Mostrar();
    producto.Mostrar();
}
