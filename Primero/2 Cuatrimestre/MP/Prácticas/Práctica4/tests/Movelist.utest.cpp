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
#include <fstream>
#include <sstream>
#include "language.h"
#include "move.h"
#include "movelist.h"

using namespace std;


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    cout << endl;
    Language langEN("EN"), langES("ES");    

    cout << endl <<"%%%OUTPUT"<<endl;
    if (true) {
        cout << "BASE CONSTRUCTOR :"<<endl;
        Movelist base;
        cout << "   0="<<base.size()<<endl;
        cout << "DESTRUCTOR ";
    }
    if (true) {
        cout << endl << endl << "PARAMETER CONSTRUCTOR :"<<endl;
        Movelist base(2), other(3);
        cout << "  2="<<base.size()<<" 3="<<other.size()<<endl;
        cout << "DESTRUCTOR ";
    }
    if (true) {
        cout <<endl<< endl << "SET/GET::"<<endl;
        Movelist base(2);
        Move move;
        move.set(7,8,'h',"ONE");
        base.set(0,move);
        cout<<"  7="<<base.get(0).getRow()<<" 8="<<base.get(0).getCol()<<
                " ONE="<<base.get(0).getLetters();
        move.set(9,10,'h',"TWO");
        base.set(1,move);
        cout<<" 9="<<base.get(1).getRow()<<" 10="<<base.get(1).getCol()<<
                " TWO="<<base.get(1).getLetters()<<endl;
        cout << "DESTRUCTOR ";
    }
    if (true) {
        cout << endl <<endl << "COPY CONSTRUCTOR/COPY::"<<endl;
        Movelist base(2);
        Move move;
        move.set(7,8,'h',"ONE");
        base.set(0,move);
        move.set(9,10,'h',"TWO");
        base.set(1,move);
        Movelist other(base);
        cout<<"   2="<<other.size();
        cout<<" 7="<<other.get(0).getRow()<<" 8="<<other.get(0).getCol()<<
                " ONE="<<other.get(0).getLetters();
        cout<<" 9="<<other.get(1).getRow()<<" 10="<<other.get(1).getCol()<<
                " TWO="<<other.get(1).getLetters()<<endl;
        cout << endl << "DEEP COPY CONSTRUCTOR/COPY::"<<endl;
        move.set(11,12,'h',"THREE");
        base.set(1,move);
        cout<<"   2="<<base.size();
        cout<<" 7="<<base.get(0).getRow()<<" 8="<<base.get(0).getCol()<<
                " ONE="<<base.get(0).getLetters();
        cout<<" 11="<<base.get(1).getRow()<<" 12="<<base.get(1).getCol()<<
                " THREE="<<base.get(1).getLetters()<<endl;
        cout<<"   2="<<other.size();
        cout<<" 7="<<other.get(0).getRow()<<" 8="<<other.get(0).getCol()<<
                " ONE="<<other.get(0).getLetters();
        cout<<" 9="<<other.get(1).getRow()<<" 10="<<other.get(1).getCol()<<
                " TWO="<<other.get(1).getLetters()<<endl;
        cout << endl << endl << "CLEAR:: ";
        other.clear();
        cout << "0="<<other.size()<<endl;
    }
    cout << endl << endl << "PRINT::"<<endl;
    Movelist base(2);
    Move move;
    move.set(7,8,'h',"ONE");
    move.setScore(1);
    base.set(0,move);
    move.set(9,10,'h',"TWO");
    move.setScore(-1);
    base.set(1,move);
    cout << "   Print: 2="<<base.size()<<" "; base.print(cout);
    cout << endl << "FINDSCORE:: -1="<<base.getScore()<<endl;;
    move.setScore(2);
    base.set(1,move);
    cout << "   Print: 2="<<base.size()<<" "; base.print(cout);
    cout << endl << "FINDSCORE:: 3="<<base.getScore();
    move.set(11,12,'h',"TRES");
    move.setScore(3);
    base.add(move);
    cout << endl << endl << "ADD::"<<endl;
    cout << "   Print: 3="<<base.size()<<" "; base.print(cout);
    move.set(13,14,'h',"FOUR");
    move.setScore(4);
    base.add(move);
    cout << endl << "   Print: 4="<<base.size()<<" "; base.print(cout);
    cout << endl << "FINDSCORE:: 10="<<base.getScore()<<endl;;

    cout << endl << endl << "ZIP::"<<endl;
    base.zip(langEN);
    cout << "   Print: 3="<<base.size()<<" "; base.print(cout);
    cout << endl << "FINDSCORE:: 7="<<base.getScore()<<endl;

    cout << endl << endl << "ZIP::"<<endl;
    base.zip(langES);
    cout << "   Print: 0="<<base.size()<<" "; base.print(cout);
    cout << endl << "FINDSCORE:: 0="<<base.getScore()<<endl;
    base.clear();
    cout << endl << "CLEAR:: 0="<<base.size()<<endl;    
    
    Movelist second;
    move.set(7,8,'h',"ONE");
    move.setScore(1);
    second.add(move);
    move.set(9,10,'h',"TWO");
    move.setScore(2);
    second.add(move);
    move.set(11,12,'h',"TRES");
    move.setScore(3);
    second.add(move);
    move.set(13,14,'h',"FOUR");
    move.setScore(4);
    second.add(move);
    cout << endl << endl << "REMOVE::" << endl << "   Print: 4="<<second.size()<<" "; second.print(cout);
    move.set(9,10,'h',"TWO");
    move.setScore(2);
    second.remove(move);
    cout << endl << "   Print: 3="<<second.size()<<" "; second.print(cout);
    for (int i=0; i<second.size();)
        second.remove(0);
    cout << endl << "   Print: 0="<<second.size()<<" "; second.print(cout);
    cout << endl<<endl<<"READ::";
    string s="H 0 0 UNO H 0 0 DEUX H 0 0 TRES H 0 0 @";
    stringstream is(s);
    second.read(is);
    cout << endl << "   Print: 3="<<second.size()<<" "; second.print(cout);
    cout << endl;
}