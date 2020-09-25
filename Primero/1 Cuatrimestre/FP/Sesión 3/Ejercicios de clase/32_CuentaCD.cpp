/*	Dada la estructura del enunciado, comentar que tipo de dato
	contiene cada variable e identificar si hay algún error
*/

#include <iostream>
#include <cstring>

using namespace std;

struct CuentaCD{
	double saldo;
	double tasa_de_interes;
	int plazo;
	char inicial1;
	char inicial2;
};

int main (){
	CuentaCD cuenta;
	
	/* Vamos a comentar los casos que nos da el ejercicio:
	
		a) cuenta.saldo   
		Almacena un dato tipo double y está correctamente definida
		
		b) cuenta.tasa_de_interes
		Almacena un dato tipo double y está correctamente definida
		
		c) CuentaCD.plazo
		No almacena nada ya que está mal definida. No esta llamando
		a ninguna variable, ya que se ha usado el nombre de la
		estructura y no la variable que hemos definido para
		esa determinada estructura
		
		d) cuenta_ahorros.inicial1
		No almacena nada ya que no hemos definido ninguna variable
		con el nobre cuenta_ahorros
		
		e) cuenta.inicial2
		Esta correctamente definida y almacena un dato tipo char,
		el cual, podemos considerar como entero, ya que los datos almacenados
		en variables tipo char son convertidos a enteros cuando aparecen
		en expresiones usando, generalmente, el código ASCII
		
		f) cuenta
		No almacena nada, ya que no indica a que variable dentro de la estructura
		debe llamar el compilador para que almacene un determinado dato
	*/
}
