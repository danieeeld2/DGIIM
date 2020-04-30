/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>
#include <cassert>
#include "move.h"
#include "language.h"
#include "movelist.h"

using namespace std;


bool Movelist::print(std::ostream &os, bool scores) const {
    bool res=true;
    for (int i=0; i<size() && res; i++) {
        get(i).print(os);
        if (scores)
            os << " ("<<get(i).getScore()<<") - ";
        else
            os << " - ";
        if (os.bad())
            res=false;
    }
    return res;
}

void Movelist::allocate(int n) {
    if (moves != nullptr)
        delete[]moves;
    
    moves = new Move[n];
}

void Movelist::deallocate() {
    if (moves != nullptr) {
        delete []moves;
        moves = nullptr;
    }
}

void Movelist::add(const Move& mov) {
    Move *copia = nullptr;
    
    if (nMove > 0)
        copia = new Move[nMove];
    
    for(int i = 0; i<nMove; i++)
        copia[i] = moves[i];
    
    deallocate();
    nMove++;
    allocate(nMove);
    
    for(int i = 0; i < nMove-1; i++)
        moves[i] = copia[i];
    moves[nMove-1] = mov;

    if (copia != nullptr)
        delete []copia;
    copia = nullptr;
    
}

void Movelist::remove(int p) {
    assert(p >= 0 && p < size());

    Move *temp = new Move[--nMove];

    for (int i = p; i < size(); i++)
        moves[i] = moves[i + 1];

    for (int i = 0; i < nMove; i++)
        temp[i] = moves[i];

    deallocate();
    moves = temp;
}

int Movelist::find(const Move& mov) const {
    int posicion;
    bool row, column, horizontal, letters, score;
    bool iguales = false;
    
    for(int i = 0; i < nMove && (!iguales); i++){
        row = mov.getRow() == moves[i].getRow();
        column = mov.getCol() == moves[i].getCol();
        horizontal = mov.isHorizontal() == moves[i].isHorizontal();
        letters = mov.getLetters() == moves[i].getLetters();
        score = mov.getScore() == moves[i].getScore();
        iguales = row && column && horizontal && letters && score;
        
        if(iguales)
            posicion = i;
        else 
            posicion = -1;
    }
    
    return posicion;
}


void Movelist::remove(const Move &mov){
    int posicion = find(mov);
    if(posicion != -1)
        remove(posicion);
}

void Movelist::zip(const Language& l) {
    for(int i = 0; i < nMove; i++){
        if(moves[i].getLetters().size() < 2 || l.query(moves[i].getLetters()) == false){
            for(int j = i; j < nMove-1 ; j++){
                moves[j] = moves[j+1];
            }
            --nMove;
            --i;
        }
    }
}

void Movelist::clear() {
    if(moves != nullptr){
        deallocate();
        nMove = 0;
        moves = nullptr;
    }
}

int Movelist::getScore() const {
    int score = 0;
    
    for(int i = 0; i < nMove && score != -1; i++){
        score = score + moves[i].getScore();
        if(moves[i].getScore() == -1)
            score = -1;
    }
    
    return score;
}

Move Movelist::get(int p) const{
    if(p >= 0 && p<size())
        return moves[p];
}

bool Movelist::read(std::istream& is) {
    Move mov;
    string l = "";
    char h = 'h';
    int col = 0, row = 0;
    do {
        if (is.eof() || !is)
            return false;
        try {
            is >> h;
            is >> row;
            is >> col;
            is >> l;
            if (l != "@") {
                mov.set(row, col, h, l);
                add(mov);
            }
        }        catch (...) {
            return false;
        }
    } while (l != "@");
    return true;
}

void Movelist::set(int p, const Move& m) {
    if(p>=0 && p<size())
        moves[p] = m;
}


void Movelist::copy(const Movelist& ml) {
    if(moves != nullptr)
        deallocate();
    
    nMove = ml.size();
    allocate(nMove);
    
    for(int i = 0; i < nMove; i++)
        set(i, ml.get(i));
}

Movelist Movelist::operator =(const Movelist& orig){
    if(this != &orig)
        copy(orig);
    return *this;
}


Movelist::Movelist(const Movelist& orig) {
    moves = nullptr;

    nMove = 0;

    copy(orig);
}

Movelist::Movelist(int nmov){
    moves = new Move[nmov];
    nMove = nmov;
}

Movelist::~Movelist() {
    deallocate();
}

Movelist::Movelist() {
    nMove = 0;
    moves = nullptr;
}
