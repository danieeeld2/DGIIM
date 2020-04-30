/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include <string.h>
#include "bag.h"
#include "player.h"


///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos);

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr);

//  Función auxiliar

/**
 * @brief Returns a character's frequency contained in a string
 * @param s The string
 * @param a the character
 * @return Character's frequency
 */
int frequency(std::string s, char a);

//  Implementación de métodos de la clase

Player::Player(){
    letters[0] = '\0';  //  El final del string viene determinado por esta 
                        //  simbología, por lo que ahora mismo el string estaría vacío
}

int Player::size() const{
    return strlen(letters);
}

std::string Player::to_string() const{
    std::string s(letters);
    return s;
}

void Player::clear(){
    for(int i = 0; i <= MAXPLAYER; i++)
        letters[i] = '\0';
}

bool Player::isValid(const std::string s) const{
    /*  Para ver si un movimiento es correcto habría que mirar:
            - Si el número de letras empleadas es menor o igual a las que posee el jugador
            - Si la frecuencia empleada en cada letra es menor o igual a las que posee el jugador*/
    
    bool valido = true;
    const char *l = s.c_str();  //  Convertimos el string en un puntero constante
    int contador1 = 0;
    int contador2 = 0;
    
    if(s.size() > size())   //  Comparamos el numero de letras del jugador con las del movimiento
        valido = false;     //  Si el movimiento es mayor que las letras disponibles no es válido
    
    for(int i = 0; i != s.size() && valido == true; i++){
        contador2 = frequency(s, l[i]); //  Frecuencia de la letra almacenada en la posición i-ésima del string s
                
        for(int j = 0; j != size(); j++){
            if(l[i] == letters[j])
                contador1++;
        }
        
        if(contador2 > contador1)   //  Compara si la frecuencia de la letra que se usa en el moviiento es válida
            valido = false;
        
        contador1 = contador2 = 0;
    }
    
    return valido;    
}

bool Player::extract(const std::string s){
    const char *l = s.c_str();  //  Convertimos el string en un puntero constante
    bool supported = false;
    int posicion = 0;
    
    if(isValid(s)){
        supported = true;
        
        for(int i = 0; i != s.size(); i++){
            for(int j = 0; j != size(); j++)
                if(letters[j] == l[i])
                    posicion = j;
            
                    
        removeCString(letters, posicion);
        }
    }
    
    return supported;
}
    

void Player::add(std::string frombag){
    if((strlen(letters) + frombag.size()) <= MAXPLAYER){
        int siz = size();
        
        for(int i = size(); i < MAXPLAYER+1;i++)
            letters[i] = frombag[i - siz];
        
        sortCString(letters);
    }
}

void removeCString(char *cstr, int pos){
    for(int i = pos; cstr[i] != '\0'; i++){
        cstr[i] = cstr[i+1];
    }
}

void sortCString(char *cstr){
    char minimo;
    int pos_minimo;
    
    for(int i = 0; cstr[i] != '\0'; i++){
        minimo = cstr[i];
        pos_minimo = i;
        
        for(int j = i; cstr[j]; j++){
            if(minimo > cstr[j]){
                minimo = cstr[j];
                pos_minimo = j;
            }
        }
        
        cstr[pos_minimo] = cstr [i];
        cstr[i] = minimo;
    }
}

int frequency(std::string s, char a){
    int frecuencia = 0;
    const char *l = s.c_str();
    
    for(int i = 0; i != s.size(); i++)
        if(l[i] == a)
            frecuencia++;
    
    return frecuencia;
}



