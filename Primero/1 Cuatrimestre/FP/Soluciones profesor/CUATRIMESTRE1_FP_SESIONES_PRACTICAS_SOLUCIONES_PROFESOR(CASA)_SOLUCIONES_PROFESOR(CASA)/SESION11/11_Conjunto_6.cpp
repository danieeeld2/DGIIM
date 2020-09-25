#include <iostream>

using namespace std;

/**
 * @brief Clase Conjunto. Un objeto c de la clase Conjunto representa un
 * conjunto de valores enteros
 */
class Conjunto{
	private:
		static const int MAXIMO_ELEMENTOS = 100; /**< tamaño maximo del conjunto */
		int elementos[MAXIMO_ELEMENTOS]; /**< representa el conjunto de enteros  */
        int cardinal; /**< numero de elementos del conjunto */
	public:
        /**
         * @brief Constructor sin parametros. Inicializa al conjunto vacio
         */
        Conjunto();
        /**
         * @brief Constructor con parametros
         * @param card cardinal del conjunto
         * @param elem elementos del vector
         * @pre elem debe tener los elementos ordenados
         */
        Conjunto(int card, int elem[]);
        /**
         * @brief Constructor de copia
         * @param otro El objeto de la clase Conjunto a copiar
         */
        Conjunto (const Conjunto & otro);
        /**
         * @brief Determina si un entero pertenece al conjunto
         * @param numero entero a determinar su pertenencia al conjunto
         * @pre elem debe tener los elementos ordenados
         */
        bool Pertenece (int numero) const; // atencion! funcion const, no modifica el objeto
        /**
         * @brief Aniade un elemento al conjunto
         * @param numero el numero a aniadir
         * @post si numero ya se encuentra en el conjunto, no hace nada
         */
        void Aniadir(int numero);
        /**
         * @brief Elimina un elemento al conjunto
         * @param numero el numero a eliminar
         * @post si numero NO se encuentra en el conjunto, no hace nada
         */
        void Eliminar(int numero);
        /**
         * @brief Calcula la union de dos conjuntos
         * @param otro Conjunto para hacer la union con *this (el objeto al que se le aplica el operador)
         * @retval Devuelve el conjunto union
         */
        Conjunto Union(Conjunto otro);
        /**
         * @brief Calcula la interseccion de dos conjuntos
         * @param otro Conjunto para hacer la interseccion con *this (el objeto al que se le aplica el operador)
         * @retval Devuelve el conjunto interseccion
         */
        Conjunto Interseccion(Conjunto otro);
        /**
         * @brief Muestra por pantalla un conjunto
         * @post Muestra los enteros del conjunto separados con un espacio en blanco
         */
        void Mostrar();
    
    /* Ampliacion: Otra forma, con operadores */
    
        Conjunto operator+(const Conjunto & otro);
        Conjunto operator*(const Conjunto & otro);
        /* Otra sobrecarga de +, para añadir un numero */
        Conjunto operator+ (int numero);
        /* Otra sobrecarga de -, para eliminar un numero */
        Conjunto operator-(int numero);
    /* Este operador no pertenece a la clase, pero si que se declara aqui */
    friend ostream & operator<< ( ostream & flujo, const Conjunto & c);
};


int main (){
    
    int vector1[10] = {0,1,3,6,7,8,9,13,15,20};
    int vector2[9] = {0,2,3,7,13,23,25,30,32};
    
    Conjunto c1(10,vector1);
    Conjunto c2(9,vector2);
    
    c1.Mostrar();
    c2.Mostrar();
    
    Conjunto inter = c1.Interseccion(c2);
    inter.Mostrar();

    Conjunto uni = c1.Union(c2);
    uni.Mostrar();
    
    uni.Aniadir(36);
    uni.Mostrar();
   
    uni = uni - 0;
    uni = uni - 36;
    uni = uni - 15;
    uni.Mostrar();
    
    (inter + 14).Mostrar();
    
    cout << c1 << c2 << uni;
}


Conjunto::Conjunto(){
    cardinal = 0;
}

Conjunto::Conjunto(int card, int elem[]){
    /*
     * Una extension: que ordene y quite repetidos de los datos iniciales
     Ordenar(card,elem);
     EliminarRepetidos(card,elem);
     */
    cardinal = card;
    for (int i=0; i<cardinal; i++)
        elementos[i] = elem[i];
}

Conjunto::Conjunto (const Conjunto & otro){
    cardinal = otro.cardinal;
    for (int i=0; i<cardinal; i++)
        elementos[i] = otro.elementos[i];
}


bool Conjunto::Pertenece (int numero) const{
    /*
     Algoritmo: busqueda secuencial
     otra opcion: busqueda binaria
     */
    bool esta = false;
    for (int i=0; i<cardinal && !esta; i++)
        if (elementos[i] == numero)
            esta = true;
    return esta;
}

void Conjunto::Aniadir(int numero){
    /* Algoritmo: Si no se ha llenado el vector y numero no esta en el
                    - copia cada coordenada en la siguiente para los numeros
                      mayores que numero (empezando por el final)
                    - Despues copia numero en la ultima coordenada tratada
     */
    if ( cardinal < MAXIMO_ELEMENTOS && !Pertenece(numero) ){
        int posicion = cardinal;
        while ( posicion > 0 && elementos[posicion-1] > numero ){
            elementos[posicion] = elementos[posicion-1];
            posicion--;
        }
        elementos[posicion] = numero;
        cardinal++;
    }
}

void Conjunto::Eliminar(int numero){
    /* Algoritmo:
        Recorremos el conjunto hasta encontrar numero
        Desde esa coordenada hasta cardinal:
            Copiamos el contenido de la coordenada i+1 en la i-esima
        Decremento de cardinal
     */
    int posicion = 0;
    bool encontrado = false;
    while ( !encontrado && posicion < cardinal ){
        if (elementos[posicion] == numero)
            encontrado = true;
        else
            posicion++;
    }
    
    if ( encontrado ){
        for (int i=posicion; i<cardinal-1; i++)
            elementos[i] = elementos[i+1];
            cardinal--;
    }
}

Conjunto Conjunto::Union(Conjunto otro){
    /* Con mas cohesion de la clase
     * (interaccionan mas los metodos entre ellos)
     */
    Conjunto uni(otro);
    
    for (int i=0; i<cardinal; i++)
         uni.Aniadir(elementos[i]);
    
    return uni;
    
    /* Esto es más eficiente, pero menos claro
     * Se recorren ambos vectores, seleccionando el elemento
     * mas pequeño de los dos vectores en cada momento y añadiendolo al conjunto union
     * Cuando uno de los vectores se ha añadido completamente
     * se añade el los que faltan del otro vector
     */
    /*
    Conjunto uni;
    int posicion = 0;
    int posicion_otro = 0;
    
    while ( posicion < cardinal && posicion_otro < otro.cardinal ){
        if ( elementos[posicion] < otro.elementos[posicion_otro] ){
            uni.elementos[uni.cardinal] = elementos[posicion];
            posicion++;
        }
        else if ( elementos[posicion] > otro.elementos[posicion_otro] ){
            uni.elementos[uni.cardinal] = otro.elementos[posicion_otro];
            posicion_otro++;
        }
        else{
            uni.elementos[uni.cardinal] = otro.elementos[posicion_otro];
            posicion_otro++;
            posicion++;
        }
        uni.cardinal++;
    }
    
    if ( posicion >= cardinal )
        for (int i=posicion_otro; i<otro.cardinal; i++){
            uni.elementos[uni.cardinal] = otro.elementos[i];
            uni.cardinal++;
        }
    else
        for (int i=posicion; i<cardinal; i++){
            uni.elementos[uni.cardinal] = elementos[i];
            uni.cardinal++;
        }
    return uni;
     */
}

Conjunto Conjunto::Interseccion(Conjunto otro){
    /* Con mas cohesion de la clase
     * (interaccionan mas los metodos entre ellos)
     */
    Conjunto interseccion;
    
    for (int i=0; i<cardinal; i++)
        if ( otro.Pertenece(elementos[i] ) )
            interseccion.Aniadir(elementos[i]);
    
    return interseccion;

    /* Esto es más eficiente, pero menos claro
     * Se recorren ambos vectores hasta que termina uno de ellos:
     *  si los elementos considerados son iguales, se añade y aumentan los contadores
     *  si no, se incrementa el contador del vector con el elemento mas pequeño
     */
    /*
    Conjunto interseccion;
    int posicion = 0;
    int posicion_otro = 0;
    int posicion_interseccion = 0;
    while ( posicion < cardinal && posicion_otro < otro.cardinal ){
        if ( elementos[posicion] < otro.elementos[posicion_otro] )
            posicion++;
        else if ( elementos[posicion] > otro.elementos[posicion_otro] )
            posicion_otro++;
        else{
            interseccion.elementos[posicion_interseccion] = elementos[posicion];
            posicion_interseccion++;
            posicion++;
            posicion_otro++;
        }
    }
    interseccion.cardinal = posicion_interseccion-1;
    return interseccion;
     */
}

void Conjunto::Mostrar(){
    if (cardinal == 0)
        cout << "EmptySet";
    else
        for (int i=0; i<cardinal; i++)
            cout << elementos[i] << " ";
    cout << "\n";
}

/*
 *
 * Ampliacion: otra forma mas avanzada, con operadores
 *
 */

Conjunto Conjunto::operator+( const Conjunto & otro){
    Conjunto uni(otro);
    for (int i=0; i<cardinal; i++)
        uni.Aniadir(elementos[i]);
    return uni;
}

Conjunto Conjunto::operator*( const Conjunto & otro){
    Conjunto interseccion;
    for (int i=0; i<cardinal; i++)
        if ( otro.Pertenece(elementos[i] ) )
            interseccion.Aniadir(elementos[i]);
    return interseccion;
}

Conjunto Conjunto::operator+ (int numero){
    Conjunto salida = *this; // *this significa "el objeto al que le aplico la funcion"
    salida.Aniadir(numero);
    return salida;
}

Conjunto Conjunto::operator-(int numero){
    Conjunto salida = *this; // *this significa "el objeto al que le aplico la funcion"
    salida.Eliminar(numero);
    return salida;
}

ostream & operator<< ( ostream & flujo, const Conjunto & c){
    if (c.cardinal == 0)
        cout << "EmptySet";
    else
        for (int i=0; i<c.cardinal; i++)
            cout << c.elementos[i] << " ";
    cout << "\n";
    
    return flujo;
}


