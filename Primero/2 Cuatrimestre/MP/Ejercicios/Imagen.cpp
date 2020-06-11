/*Examen Metodología de la Programación 11 de Julio de 2019*/
#include <iostream>
#include <fstream>
using namespace std;

class Imagen{
    private:
    // PRE: 0 <= filas,columnas 
    int filas, columnas;

    // PRE: 0 <= valores[i][j] <= 255  
    // 0 <= i < filas, 0 <= j < columnas
    int ** valores; // Valores de luminosidad
    Comentarios comentarios;
    public:
    /*Supongamos los siguientes métodos:
    Imagen(const Imagen & otro); // Constructor de copia
    int getNumFilas() const; // Devuelve el num. de filas
    int getNumColumnas() const; // Devuelve el num. de columnas
    friend ostream & operator<<(ostream & out, const Imagen & img); // Salida
    const Comentarios & getComentarios (void) const; // Devuelve una referencia a los comentarios*/
    Imagen();
    ~Imagen();
    Imagen(string ifilename);
    Imagen(int f, int c, int v=0);
    void allocate(int a, int b);
    void deallocate();
    void copy(const Imagen& orig);
    Imagen& operator=(const Imagen& orig);
    bool read(istream& is);
    istream& operator>>(istream&is);
};

class Comentarios{
    private:
    // PRE: 0 <= numComentarios
    int numComentarios;
    string * losComentarios;
    public:
    /*Comentarios(const Comentarios & otro);  // Constructor de copia
    int getNumComentarios() const; // Devuelve el n ́umero de comentarios
    Comentarios & operator=(const Comentarios & otro);  // Operador =
    friend istream & operator>>(istream & in,  Comentarios & c); // Entrada
    friend ostream & operator<<(ostream & out, const Comentarios & c); // Salida*/
    Comentarios();
    ~Comentarios();
    //Métodos auxiliares para acelerar proceso
    void deallocate();
    void allocate(int a);
    void copy(const Comentarios& orig);
    void add(string s);
    //----------
    Comentario& operator+=(const Comentarios& orig);
    istream& operator>>(istream& is, Comentarios& cm);
};

//  Ejercicio 1
Comentarios::Comentarios(){
    numComentarios = 0;
    losComentarios = nullptr;
}
/*Al ser una clase que usa memoria dinámica es necesario crear un destructor*/*
Comentarios::~Comentarios(){
    deallocate();   //  Mirar método abajo
}
//  Métodos auxiliares
void Comentarios::allocate(int a){
    deallocate();
    numComentarios = a;
    losComentarios = new string[a];
}
void Comentarios::deallocate(){
    if(losComentarios != nullptr){
        delete[] losComentarios;
    }
    losComentarios = nullptr;
    numComentarios = 0;
}
void Comentarios::copy(const Comentarios& orig){
    deallocate();
    numComentarios = orig.numComentarios;
    allocate(numComentarios);
    for(int i = 0; i < numComentarios; i++){
        losComentarios[i] = orig.losComentarios[i];
    }
}
void Comentarios::add(string s){
    Comentarios aux;
    aux.copy(*this);
    deallocate;
    allocate(aux.numComentarios+1);
    for(int i = 0; i < numComentarios-1; i++){
        losComentarios[i] = aux.losComentarios[i];
    }
    losComentarios[numComentarios-1] = s;
}
/*Operador+=*/
Comentarios Comentarios::operator+=(const Comentarios& orig){
    Comentarios aux;
    aux.numComentarios = orig.losComentarios + losComentarios;
    aux.allocate(numComentarios);
    for(int i = 0; i < aux.numComentarios; i++){
        if(i < losComentarios){
            aux.losComentarios[i] = losComentarios[i];
        }else{
            aux.losComentarios[i] = orig.losComentarios[i-numComentarios];
        }
    }
    return aux;
}

//  Ejercicio 2
Imagen::Imagen(){
    columnas = 0;
    filas = 0;
    valores = nullptr;
    comentarios.add("#Creada vacía")
}
void Imagen::deallocate(){
    if(valores != nullptr){
        for(int i = 0; i < filas; i++){
            delete[] valores[i];
        }
        delete[] valores;
    }
    valores = nullptr;
    filas = 0;
    columnas = 0
}
void Imagen::allocate(int a, int b){
    deallocate();
    filas = a;
    columnas = b;
    valores = new int*[filas];
    for(int i = 0; i < filas; i++){
        valores[i] = new int[columnas];
    }
}
Imagen::Imagen(int f, int c, int v=0){
    string s;
    allocate(f,c);
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            valores[i][j] = v;
        }
    }
    s = "#Creado a "+to_string(f)+"x"+to_string(c)+" a valor "+to_string(v);
    comentarios.add(s);
}

void Imagen::copy(const Imagen& orig){
    deallocate();
    allocate(orig.filas,orig.columnas);
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            valores[i][j] = orig.valores[i][j];
        }
    }
    comentarios.deallocate();
    //comentarios.allocate(orig.comentarios.getNumComentarios())   //Se supone implementado
    //for(int i = 0; i < orig.comenatrios.getNumComentarios(); i++){
    //    comentarios.losComentarios[i] = orig.comentarios.losComentarios[i]
    //}
}

Imagen Imagen::operator=(const Imagen& orig){
    if(this != orig){
        copy(orig);
    }
    return *this;
}

/*Si debería implementarse por si usamos algun objeto auxiliar de la clase
en algún método*/

Imagen::~Imagen(){
    deallocate();
}

/*Ejercicio 3*/
istream Comentarios::operator>>(istream& is, Comentarios& cm){
    //  Se supone implementado    
}

bool Imagen::read(istream& is){
    Comentarios cm;
    int f, c, max;

    is >> cm;
    if(is.eof())
        return false;
    comentarios.copy(cm);
    is >> f >> c >> max;
    if(is.eof())
        return false;
    filas = f;
    columnas = c;
    allocate(f,c);
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            is >> valores[i][j];
            if(is.eof() || valores[i][j] > max)
                return false;
        }
    }
    return true;   
}

istream Imagen::operator>>(istream& is){
    read(is);
    return is;
}

Imagen::Imagen(string ifilename){
    ifstream ifile;
    string cadena;
    Imagen();   //Por si falla
    ifile.open(ifilename);
    if(!file)
        cerr << "Error de apertura del fichero";
    else{
        getline(ifile, cadena);
        if(cadena == "P2")
            ifile >> *this;
        ifile.close();
    }
}