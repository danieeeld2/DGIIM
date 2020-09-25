#include <iostream>
#include <string>

using namespace std;

/*
 *@brief Un objeto de la clase Libro representa un libro compuesto por
 * unos autores, un titulo, una editorial y un anio de publicacion
 *
 **/
class Libro{
	private:
         static const int MAXIMO_AUTORES = 3;
         int numero_autores;
		 string autor[MAXIMO_AUTORES];
		 string titulo;
		 string editorial;
		 int anio;
	public:
        /**
         * @brief Constructor por defecto
         * @post Inicializa a un libro sin titulo, editorial, ni autores, con anio 0
         */
        Libro();
        /**
         * @brief Constructor con parametros
         * @param a vector de autores
         * @param n numero de autores
         * @param t titulo del libro
         * @param e editorial del libro
         * @param an anio de publicacion del libro
         * @pre el numero de autores es, como maximo, tres
         */
        Libro( string a[], int n, string t, string e, int an );
        /**
         *@brief Devuelve los autores del libro
         *@param a vector de string donde se encuentran los autores
         *@param n numero de autores
         *@post a y n varian para contener los datos sobre los autores
         */
        void GetAutores( string a[], int & n );
        /**
         *@brief Devuelve el titulo del libro
         */
        string GetTitulo();
        /**
         *@brief Devuelve la editorial del libro
         */
        string GetEditorial();
        /**
         *@brief Devuelve el anio de publicacion del libro
         */
        int GetAnio();
        /**
         *@brief Muestra por consola los datos del libro
         */
        void MostrarLibro();
        /**
         *@brief Compara si dos libros son el mismo o no
         *@retval true si son iguales, false en caso contrario
         *@param otro El libro con el que comparar
         */
        bool CompararLibro( const Libro & otro);
        /*
         *
         * Ampliacion: utilizando operadores
         *
         */
        /**
         *@brief Sobrecarga del operador ==
         *@retval true si son iguales, false en caso contrario
         *@param otro El libro con el que comparar
         */
        bool operator== (const Libro & otro_libro);
        /**
         *@brief Sobrecarga del operador !=
         *@retval false si son iguales, true en caso contrario
         *@param otro El libro con el que comparar
         */
        bool operator!= (const Libro & otro_libro);
};

int main(){
	
    string aut[3]={"pepito grillo","pinocho"};
    Libro libro (aut,2,"Libro de prueba","Kalandraka", 2010);
    Libro libro2 (aut,2,"Libro de prueba2","Kalandraka", 2010);
    
    libro.MostrarLibro();
    libro2.MostrarLibro();
    
    cout << (libro == libro2) << "\n";
    cout << (libro != libro2) << "\n";
}


Libro::Libro(){
    numero_autores = 0;
    titulo = "";
    editorial = "";
    anio = 0;
    for (int i=0; i<MAXIMO_AUTORES; i++)
        autor[i] = "";
}

Libro::Libro( string a[], int n, string t, string e, int an ){
    numero_autores = n;
    for (int i=0; i<n; i++)
        autor[i] = a[i];
    titulo = t;
    editorial = e;
    anio = an;
}

void Libro::GetAutores( string a[], int & n ){
    n = numero_autores;
    for (int i=0; i<numero_autores; i++)
        a[i] = autor[i];
}

string Libro::GetTitulo(){
    return titulo;
}

string Libro::GetEditorial(){
    return editorial;
}

int Libro::GetAnio(){
    return anio;
}

void Libro::MostrarLibro(){
    for (int i=0; i<numero_autores; i++)
        cout << autor[i] << ", ";
    cout << " " << titulo << "; " << editorial << "; " << anio << ".\n";
}

bool Libro::CompararLibro( const Libro & otro_libro){
    bool mismo_titulo = titulo == otro_libro.titulo;
    bool misma_editorial = editorial == otro_libro.editorial;
    return misma_editorial && mismo_titulo;
}

bool Libro::operator== (const Libro & otro_libro){
    bool mismo_titulo = titulo == otro_libro.titulo;
    bool misma_editorial = editorial == otro_libro.editorial;
    return misma_editorial && mismo_titulo;
}

bool Libro::operator!= (const Libro & otro_libro){
    bool mismo_titulo = titulo == otro_libro.titulo;
    bool misma_editorial = editorial == otro_libro.editorial;
    return !(misma_editorial && mismo_titulo);
}
