/*	Funcion que permite calcular el
	área de cualquier polígono convexo */
	
#include<iostream>
#include<cmath>

using namespace std;

const int MAXIMO = 10;

struct TipoPunto{
	double abcisa;
	double ordenada;
};

struct TipoPoligono{
	TipoPunto puntos[MAXIMO];
	int num_puntos;
};

//////////////////////////////////////////////////////////

double Lado (TipoPunto punto1, TipoPunto punto2){
	double argumento;
	double lado;
	
	argumento = pow((punto1.abcisa - punto2.abcisa), 2) + pow((punto1.ordenada - punto2.ordenada), 2);
	lado = sqrt (argumento);
	
	return lado;
};

//////////////////////////////////////////////////////////////
	
double AreaTriangulo (TipoPunto punto1,TipoPunto punto2, TipoPunto punto3){
	double area_triangulo;
	double lado1;
	double lado2;
	double lado3;
	double F;
	
	lado1 = Lado(punto1, punto2);
	lado2= Lado(punto2, punto3);
	lado3 = Lado(punto3, punto1);
	F = (lado1 + lado2 + lado3) / 2;
	
	area_triangulo = sqrt(F * (F - lado1) * (F - lado2) * (F - lado3));
	
	return area_triangulo;
};

/////////////////////////////////////////////////////////////////

double AreaPoligono (TipoPoligono poligono){
	 double area = 0;

    for (int i=2; i < poligono.num_puntos; i++)
        area = area + AreaTriangulo(poligono.puntos[0], poligono.puntos[i-1], poligono.puntos[i]);
    
	return area;
};

//////////////////////////////////////////////////////////////////

void DatosPunto (TipoPunto &punto){
    cout << "Introduce coordenadas: \n";
    cin >> punto.abcisa >> punto.ordenada;
};

//////////////////////////////////////////////////////////////////

void DatosPoligono (TipoPoligono &poligono){
    cout << "Introduce numero vertices: \n";
    cin >> poligono.num_puntos;
    for (int i=0; i<poligono.num_puntos; i++)
        DatosPunto (poligono.puntos[i]);
};

////////////////////////////////////////////////////////////////

int main(){
	TipoPoligono poligono;
	double area_poligono = 0;
	
	DatosPoligono (poligono);
   area_poligono = AreaPoligono(poligono);
    
	cout << "\nEl area es: " << area_poligono << "\n";
};
	
	

	
	
