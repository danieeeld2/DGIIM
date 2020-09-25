/* Un poligono puede representarse mediante la siguiente estructura de datos:
struct TipoPunto{
    double abscisa;
    double ordenada;
};
struct TipoPoligono{
    TipoPunto puntos[100];
    int num_puntos;
};
donde num_ptos tiene el numero de puntos del polıgono. Los lados del polıgono estan
constituidos por los pares de puntos (ptos[i], ptos[i+1]) i=0,...,num_ptos-2
y el par (ptos[num_ptos-1],ptos[0]).
Implementar una funcion double AreaPoligono(TipoPoligono poligono)
que calcule el area de un polıgono convexo */

#include <iostream>
#include <cmath>

using namespace std;


const int MAXIMO_PUNTOS = 10;

struct TipoPunto{
	double abscisa;
	double ordenada;
};

struct TipoPoligono{
	TipoPunto vertices[MAXIMO_PUNTOS];
	int numero_vertices;
};

/**
 *@brief Calcula area de un tipo de dato TipoPoligono
 *@pre poligono debe representar un poligono convexo
 *@param poligono dato de tipo TipoPoligono al que se calcula el area
 *@return dato double con el area del poligono
 */
double AreaPoligono(TipoPoligono poligono);
/**
 *@brief Calcula area de un triangulo definido por tres puntos
 *@param punto1, punto2, punto3, son los puntos que forman
 *@return dato double con el area del poligono
 */
double AreaTriangulo( TipoPunto punto1, TipoPunto punto2, TipoPunto punto3);

void LeerPoligono (TipoPoligono & );
void LeerPunto( TipoPunto & );

int main(){
    
    TipoPoligono poligono;
    double area_poligono = 0;
    
    LeerPoligono (poligono);
    area_poligono = AreaPoligono(poligono);
    
	cout << "\nEl area es: " << area_poligono << "\n";
}


double AreaPoligono(TipoPoligono poligono){
    double area = 0;

    for (int i=2; i<poligono.numero_vertices; i++)
        area = area + AreaTriangulo(poligono.vertices[0], poligono.vertices[i-1], poligono.vertices[i]);
    
	return area;
}

double AreaTriangulo( TipoPunto punto1, TipoPunto punto2, TipoPunto punto3){
    double longitud12, longitud13, longitud23;
    double pseudo_media = 0;
    double area = 0;
    
    longitud12 = sqrt( (punto1.abscisa - punto2.abscisa)*(punto1.abscisa - punto2.abscisa)
                      + (punto1.ordenada - punto2.ordenada)*(punto1.ordenada - punto2.ordenada) );
    longitud13 = sqrt( (punto1.abscisa - punto3.abscisa)*(punto1.abscisa - punto3.abscisa)
                      + (punto1.ordenada - punto3.ordenada)*(punto1.ordenada - punto3.ordenada) );
    longitud23 = sqrt( (punto2.abscisa - punto3.abscisa)*(punto2.abscisa - punto3.abscisa)
                      + (punto2.ordenada - punto3.ordenada)*(punto2.ordenada - punto3.ordenada) );
    
    pseudo_media = (longitud12 + longitud23 + longitud13)/2;
    area = sqrt ( pseudo_media * (pseudo_media - longitud12) * (pseudo_media - longitud23) *
                 (pseudo_media - longitud13) );
    
    return area;
}

void LeerPunto (TipoPunto & punto){
    cout << "Introduce coordenadas: \n";
    cin >> punto.abscisa >> punto.ordenada;
}

void LeerPoligono (TipoPoligono & poligono){
    cout << "Introduce numero vertices: \n";
    cin >> poligono.numero_vertices;
    for (int i=0; i<poligono.numero_vertices; i++)
        LeerPunto (poligono.vertices[i]);
}
