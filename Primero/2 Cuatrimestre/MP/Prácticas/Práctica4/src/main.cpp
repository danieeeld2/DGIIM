/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */


#include <iostream>
#include <cstdlib>
#include "language.h"
#include "bag.h"
#include "move.h"
#include "player.h"
#include "movelist.h"
#include <fstream>


using namespace std;

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo);

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    Bag bag;
    Player player;
    Language language;
    Move move;
    Movelist movements,        /// Original list of movements
            legalmovements,    /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    bool encontrado_l = false, encontrado_p = false, encontrado_r = false, lectura = false;
    string id = " ";
    int random;
    ifstream ifile; istream* input=&cin;
    string ifilename = " ";
    
    /// ...
    ///@warning: Complete the code
    /// ...
/*
1. El main() recibe como parámetros obligatorios "-l <ID>" y
"-p <playfile>" y como parámetro opcional "-r <random>" ,
en cualquier orden entre los tres. En este caso, el parámetro
"-p" hace referencia a una partida guardada, la cual, por aho-
ra, sólo tiene los movimientos. Si se especifica "-r" se define
el aleatorio con el número indicado, si no, no se define aleatorio.
 * 
2. Crear una instancia de la clase Language con el anterior ID y
mostrar el conjunto de caracteres permitido para ese lenguaje.
 * 
3. Crear una instancia de la clase Bag, inicializar el generador de
números aleatorios con el número aleatorio anterior, si es que
se ha indicado, y definir su contenido en base al lenguaje que
se ha declarado anteriormente.
 * 
4. Crear una instancia de la clase Player y llenarla por comple-
to con caracteres de la bolsa. Este objeto player deberá estar
siempre ordenado de la A a la Z.
 * 
5. Crear una instancia de la clase bf Movelist llamada original
y leer todos los movimientos desde el fichero indicado en el
parámetro -p usando el método read(...)
 * 
6. Crear una instancia de Movelist llamada legal que contenga
sólo los movimientos de original que están en el diccionario
del lenguaje elegido. Usar, para ello, el método zip(...)
 * 
7. Crear dos instancias adicionales de Movelist y llamarlas accepted
y rejected
 * 
8. Recorrer toda la lista de movimientos leı́da y, por cada uno de
ellos.
a) Si el movimiento está en el diccionario, añadir la palabra a
la lista accepted , marcarla, calcular su puntuación, según
el idioma, y mostrarlo en la pantalla.
b) En otro caso añadirla a la lista rejected y marcarla.
c) Todos estos mensajes en pantalla no afectan a la validación
de la práctica, ası́ que el alumno puede implementarlas a
su propio parecer.
 * 
9. Terminar con la llamada a HallOfFame para visualizar los re-
sultados. Esta llamada es la que se utilizará para validar los
datos.
 * 
10. Si en cualquier momento se presenta un error en los argumen-
tos, en la apertura de ficheros o en la lectura de datos del fiche-
ro, se debe usar la función errorBreak(...) para notificar el error
y parar el programa.
*/
    
    //  Comenzamos comprobando los parámetros recibidos y procesándolos
    
    if(nargs < 5)
        errorBreak(ERROR_ARGUMENTS, "");
    if(nargs > 7)
        errorBreak(ERROR_ARGUMENTS, "");
    if(nargs%2 != 1)
        errorBreak(ERROR_ARGUMENTS, "");
    
    for(int i = 1; i != nargs; i++){
        string param = args[i];
        
        if(param == "-l" && encontrado_l == false){
            encontrado_l = true;
            id = args[i+1];
        }
        
        if(param == "-r" && encontrado_r == false){
            encontrado_r = true;
            random = atoi(args[i+1]);
        }
        
        if(param == "-p" && encontrado_p == false){
            encontrado_p = true;
            ifilename = args[i+1];
            ifile.open(ifilename);
            input =&ifile;
           if(ifile.fail())
                errorBreak(ERROR_OPEN, ifilename);
        }
    }
    
    if(encontrado_l == false || encontrado_p == false)
        errorBreak(ERROR_ARGUMENTS, "");
    
    //  Instancia clase language
    
    language.setLanguage(id);
    cout << endl << "Las letras permitidas son: " << language.getLetterSet();
    
    //  Instancia clase bag
    
    if(encontrado_r)
        bag.setRandom(random);
    bag.define(language);
    
    //  Instancia clase player
    
    player.add(bag.extract(MAXPLAYER));
    
    //  Instancia movelist, original
    
    lectura = movements.read(*input);
    if(!lectura)
        errorBreak(ERROR_DATA, ifilename);
    
    //  Instancia movelist, legal
    
    legalmovements = movements;
    legalmovements.zip(language.getLanguage());
    
    //  Leer legalmovements

    for (int i = 0; i < legalmovements.size(); i++) {
        move = legalmovements.get(i);
        if (player.isValid(move.getLetters())) {
            player.extract(move.getLetters());
            player.add(bag.extract(MAXPLAYER - player.size()));
            move.setScore(move.findScore(language));
            
            cout << "Palabra valida: " << move.getLetters() << endl;
            cout << "Puntos por la palabra: " << move.getScore() << endl;
            
            acceptedmovements.add(move);
        } else {
            rejectedmovements.add(move);
        }
    }
    
    HallOfFame(language, random, bag, player, 
            movements, legalmovements, acceptedmovements, rejectedmovements);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string());
    cout << endl << endl << "ORIGINAL ("<<original.size()<<"): "<<endl; original.print(cout);
    cout << endl << endl << "LEGAL ("<<legal.size()<<"): "<<endl; legal.print(cout);
    cout << endl << endl << "ACCEPTED ("<<accepted.size()<<") SCORE "<<accepted.getScore()<< ": "<<endl; accepted.print(cout);
    cout << endl << endl << "REJECTED ("<<rejected.size()<<"): "<<endl; rejected.print(cout);
    cout << endl;
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>]"<<endl;
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}