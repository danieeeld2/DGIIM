/**
  * @file Racional.h
  * @brief Fichero cabecera del TDA Racional
  *
  */

#ifndef __RACIONAL
#define __RACIONAL

#include <iostream>

using namespace std;

/**
  *  @brief T.D.A. Racional
  *
  * Una instancia @e c del tipo de datos abstracto @c Racional es un objeto
  * del conjunto de los números racionales, compuestos por dos valores enteros
  * que representan, respectivamente, numerador y denominador. Lo representamos
  *
  * num/den
  *
  * Un ejemplo de su uso:
  * @include usoRacional.cpp
  *
  * @author 
  * @date Octubre 2017
  */

class Racional {

 private:
/**
  * @page repConjunto Rep del TDA Racional
  *
  * @section invConjunto Invariante de la representación
  *
  * El invariante es \e rep.den!=0
  *
  * @section faConjunto Función de abstracción
  *
  * Un objeto válido @e rep del TDA Racional representa al valor
  *
  * (rep.num,rep.den)
  *
  */

  int num; /**< numerador */
  int den; /**< denominador */

 public:

/**
  * @brief Constructor por defecto de la clase. Crea el numero racional 0/1
  */
  Racional();

/**
  * @brief Constructor de la clase
  * @param n numerador del racional a construir
  * @param d denominador del racional a construir
  * @return Crea el numero racional n/d
  * @pre d debe ser distinto de cero
  */
  Racional(int n, int d);  
  // Racional(int n=0, int d=1): num(n),den(d) {}

/**
  * @brief Constructor de copias de la clase
  * @param c.num numerador del racional a construir
  * @param c.den denominador del racional a construir
  */
  Racional (const Racional& c);  

/**
  * @brief Numerador
  * @return Devuelve el numerador del racional
  */ 
  int numerador ();

/**
  * @brief Denominador
  * @return Devuelve el denominador del racional
  */
  int denominador();

/**
  * @brief Asignación de un racional
  * @param n numerador del racional a asignar
  * @param d denominador del racional a asignar
  * @return Asigna al objeto implícito el numero racional n/d
  * @pre d debe ser distinto de cero
  */   
  void asignar(int n, int d);

/**
  * @brief Compara dos racionales
  * @param r racional a comparar
  * @return Devuelve 0 si este objeto es igual a r, 
  *                  <0 si este objeto es menor que r, 
  *                  >0 si este objeto es mayor que r 
  */   
  bool comparar(Racional r);

/**
  * @brief Imprime un racional en el formato "(n/d)";
  */
  void  print();

/**
  * @brief Suma dos racionales
  * @param r racional a sumar con el objeto implicito
  */
  Racional operator+(const Racional & r);

  /**
  * @brief Multiplicación de dos racionales
  * @param r racional a multiplicar con el objeto implicito
  */
  Racional operator*(const Racional & r);

  
/**
  * @brief Sobrecarga del operador +=
  * @param r racional a sumar con el objeto implícito
  */ 
  void operator+=(const Racional &r);
  
/**
  * @brief Sobrecarga del operador ==
  * @param r racional a comparar con el objeto implícito
  * @return Devuelve 0 si este objeto es igual a r
  */  
  bool operator ==(const Racional &r);

/**
  * @brief Salida de un racional a ostream
  * @param os stream de salida
  * @param r Racional a escribir
  * @post Se obtiene en \a os la cadena (num/den) con \e num,den los valores
  *   del numerador y denominador de \a r
  */
  friend ostream& operator<< (ostream& os, const Racional& r);

/**
  * @brief Entrada de un Racional desde istream
  * @param is stream de entrada
  * @param r Racional que recibe el valor
  * @retval El Racional leído en r
  * @pre La entrada tiene el formato (num/den) con \e num,\e den los valores
  *   del numerador y denominador
  */
  friend istream& operator>> (istream& is, Racional& r);

/**
  * @brief Convierte un racional en irreducible;
  */
  Racional  simplifica();

/**
  * @brief suma dos racionales
  * @param r racional a sumar con el objeto implícito
*/

/************* INCLUIR OTRAS FUNCIONES y OPERADORES *********/

/* Por ejemplo:
   la funcion irreducible que nos convierta un racional r
   en irreducible, ej. 12/4 -> 3/1
   la funcion real que devuelva el valor real asociado al racional
   ej, 1/2 -> 0.5

   Operador de resta, multiplicacion, division,etc.  
*/
 
};

#endif
