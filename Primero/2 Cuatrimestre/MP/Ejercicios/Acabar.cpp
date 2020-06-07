#include <iostream>
#include <fstream>
using namespace std;

class Fecha{
private:
	int dia;
	int mes;
	int anio;
public:
	int Getdia(){
		return dia;
	}

	int Getmes(){
		return mes;
	}
	int Getanio(){
		return anio;
	}
	void Set(int a, int b, int c){
		dia = a;
		mes = b;
		anio = c;
	}
};

class Hora{
private:
	int hora;
	int minuto;
	int segundo;
public:
	int Gethora(){
		return hora;
	}
	int Getminuto(){
		return minuto;
	}
	int Getsegundo(){
		return segundo;
	}
	void Set(int a, int b, int c){
		hora = a;
		minuto = b;
		segundo = c;
	}
};

class Instante{
private:
	Fecha fecha;
	Hora hora;
public:
	Fecha Getfecha(){
		return fecha;
	}
	Hora Gethora(){
		return hora;
	}
	Fecha Getfecha(){
		return fecha;
	}
	Hora Gethora(){
		return hora;
	}
	void Set(Fecha f, Hora h){
		fecha = f;
		hora = h;
	}
};

class Punto{
private:
	double latitud;
	double longitud;
	double altura;
public:
	double Getlatitud(){
		return latitud;
	}
	double Getlongitud(){
		return longitud;
	}
	double Getaltura(){
		return altura;
	}
	Punto GetPosicion(double a, double b, double c){
		Punto aux;
		aux.latitud = a;
		aux.longitud = b;
		aux.altura = c;
		return aux;
	}
	void Set(double a, double b, double c){
		latitud = a;
		longitud = b;
		altura = c;
	}
};

struct PuntoDeRecorrido{
	Punto punto;
	Instante instante;
};

class Recorrido{
private:
	PuntoDeRecorrido *puntos;	//	Puntero a un array de "num_puntos" datos "PuntoDeRecorrido"
	int num_puntos;	//	Número de puntos del recorrido
	bool activo;	//	Indica si el recorrido está activo
	void copy(const Recorrido& orig){
		if(puntos != nullptr)
			delete[] puntos;
		puntos = new PuntoDeRecorrido[num_puntos];
		for(int i = 0; i < orig.num_puntos; i++){
			puntos[i] = orig.puntos[i];
		}
		num_puntos = orig.num_puntos;
		activo = orig.activo;
	}
public:
	Recorrido(bool a){
		if(!a){
			num_puntos = 0;
			activo = true;
			puntos = nullptr;
		}else{
			num_puntos = 1;
			activo = true;
			puntos = new PuntoDeRecorrido[1];
			puntos[0].punto = GetPosicion(a,b,c);	//	El ejercicio nos dice que supongamos que funciona
			punto[0].instante = GetInstante(f,h);	//	El ejercicio nos dice que supongamos que funciona
		}
	}
	Recorrido(Recorrido a){
		num_puntos = 0;
		activo = true;
		puntos = nullptr;
		copy(a);
	}
	~Recorrido(){
		if(puntos != nullptr){
			delete[] puntos;
		}
		puntos = nullptr;
		num_puntos = 0;
		activo = true;
	}
	void FinRecorrido(PuntoDeRecorrido a){
		PuntoDeRecorrido aux = nullptr;
		aux = new PuntoDeRecorrido[num_puntos];
		for(int i = 0; i < num_puntos; i++){
			aux[i] = puntos[i];
		}
		if(puntos != nullptr)
			delete[] puntos;
		puntos = new PuntoDeRecorrido[num_puntos+1];
		for(int i = 0; i < num_puntos; i++){
			puntos[i] = aux[i];
		}
		puntos[num_puntos] = a;
		num_puntos++;
		if(aux != nullptr)
			delete[] aux;
		aux = nullptr;
	}
	Recorrido& operator=(const Recorrido& orig){
		if(this != orig){
			copy(orig)
		}
		return *this;
	}
	int DistanciRecorrido(){
		int suma = 0;
		for(int i = 0; i < num_puntos-1; i++){
			suma = suma + puntos[i].DistanciaAPunto(puntos[i+1]);	//	Nos dicen que supongamos que la función existe y funciona
		}
		return suma;
	}
	int TiemporRecorrido(){
		int suma = 0;
		for(int i = 0; i < num_puntos-1; i++){
			suma = suma + puntos[i].IntervaloTiempo(puntos[i+1]);	//	Nos dicen que supongamos que la función existe y funcion
		}
	}
	double VelocidadMedia(){
		return DistanciRecorrido/TiemporRecorrido;
	}
	void print(ostream& os){
		os << RECORRIDO_MP << endl;
		os << puntos[0].instante.Getfecha().Getdia() << puntos[0].instante.Getfecha().Getmes() << puntos[0].instante.Getfecha().Getanio() << endl;
		os << puntos[0].instante.Gethora().Gethora() << puntos[0].instante.Gethora().Getminuto() << puntos[0].instante.Gethora().Getsegundo() << endl;
		os << puntos[num_puntos-1].instante.Getfecha().Getdia() << puntos[num_puntos-1].instante.Getfecha().Getmes() << puntos[num_puntos-1].instante.Getfecha().Getanio() << endl;
		os << puntos[num_puntos-1].instante.Gethora().Gethora() << puntos[num_puntos-1].instante.Gethora().Getminuto() << puntos[num_puntos-1].instante.Gethora().Getsegundo() << endl;
		os << num_puntos;
		for(int i = 0; i < num_puntos; i++){
			os << puntos[i]
		}


	}

};