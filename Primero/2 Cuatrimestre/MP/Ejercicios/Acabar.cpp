#include <iostream>
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
	int Getanio(){
		return anio;
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
	void GetInstante(Fecha f, Hora h){
		f = fecha;
		h = hora;
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
	void GetPosicion(double a, double b, double c){
		a = latitud;
		b = longitud;
		c = altura;
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
public:
	Recorrido(bool a){
		if(!a){
			num_puntos = 0;
			activo = true;
			puntos = nullptr;
		}else{
			num_puntos = 1;
			activo = true;

			

		}
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
		

	}
};