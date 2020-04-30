/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"

using namespace std;


int main() {
    Move move;
    istream *input;
    string s="HOLA", s2="H 0 0 UNO H 0 0 DOS";
    stringstream is(s2);
    Language lang("ES");

    cout << "CONSTRUCTOR: "<< toUTF(move.getLetters())<<endl;
    move.set(0,0,'h',s);
    cout << "METHOD set(,,,): "<< toUTF(move.getLetters())<<endl;
    s="ADIOS";
    move.setLetters(s);
    cout << "METHOD setLetters(): "<< toUTF(move.getLetters())<<endl;
    move.read(is);
    cout << "METHOD read(): "<< toUTF(move.getLetters())<<endl;
    move.read(is);
    cout << "METHOD read(): "<< toUTF(move.getLetters())<<endl;
    s="MESAS";
    move.set(0,0,'h',s);
    cout << "METHOD findScore("<<toUTF(move.getLetters())<<"): "<< move.findScore(lang)<<endl;
    s="ADIEU";
    move.set(0,0,'h',s);
    cout << "METHOD findScore("<<toUTF(move.getLetters())<<"): "<< move.findScore(lang)<<endl;
    return 0;
}
