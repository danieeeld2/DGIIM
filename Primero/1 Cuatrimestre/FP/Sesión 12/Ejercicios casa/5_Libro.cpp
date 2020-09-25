/*	Programa para trabajar con una clase
	que representa un libro */
	
#include<iostream>
#include<string>
#include<cctype>

using namespace std;

/*	Clase que representa un libro,
	donde se considera el título, el 
	autor, editorial y año de
	publicación */
	
class Libro{
	//	Declaración de datos privados	
	private:
		string autor;
		string titulo;
		string editorial;
		int anio;
		
	public:
		//Constructor
		Libro(){					
			autor = " ";
			titulo = " ";
			editorial = " ";
			anio = 0;
		}
		
		//	Introducción de los datos privados
		void	SetLibro(int an, string aut, string tit, string edito){
			autor = aut;
			titulo = tit;
			editorial = edito;
			anio = an; 
		}
		
		//	Operador para mostrar los datos privados
		void	MostrarLibro(){
			cout << "\n\nDatos del libro: ";
			cout << "\nAutor: " << autor;
			cout << "\nTitulo: " << titulo;
			cout << "\nEditorial: " << editorial;
			cout << "\nAño de publicación: " << anio;
		}
		
		//	Operador para comparar dos objetos de la clase
		void Comparar(Libro libro2){
			cout << "\n\nComparemos libros: ";
			cout << "\nAutor 1: " << autor << "\tAutor 2: " << libro2.autor;
			cout << "\nTitulo 1: " << titulo << "\tTitulo 2: " << libro2.titulo;
			cout << "\nEditorial 1: " << editorial << "\tEditorial 2: " << libro2.editorial;
			cout << "\nAño de pulicacion1 : " << anio << "\tAño publicacion 2: " << libro2.anio;
		}
};

//	Operador para pedir los datos al usuario por teclado
void PedirDatos(int anio, string autor, string editorial, string titulo){	
	cout << "\nIntroduzca el nombre del autor: ";
	cin >> autor;
	cout << "Introduzca titulo: ";
	cin >> titulo;
	cout << "Introduzca editorial: ";
	cin >> editorial;
	cout << "Introduzca año de publicación: ";
	cin >> anio;
}

int main(){
	Libro libro1;
	Libro libro2;
	string autor1, editorial1, titulo1;
	string autor2, editorial2, titulo2;
	int anio1, anio2;
	
	cout << "\nIntroduzca los datos del primer libro: ";
	PedirDatos(anio1, autor1, editorial1, titulo1);
	libro1.SetLibro(anio1, autor1, titulo1, editorial1);
	
	cout << "\nIntroduzca los datos del segundo libro: ";
	PedirDatos(anio2, autor2, editorial2, titulo2);
	libro2.SetLibro(anio2, autor2, titulo2, editorial2);
	
	cout << "\nLos datos del libro 1 son: ";
	libro1.MostrarLibro();
	
	cout << "\nComparacion: ";
	libro1.Comparar(libro2);
	
	cout << "\n\n";
	system("pause");
}
