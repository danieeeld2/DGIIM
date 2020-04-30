/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>
#include "move.h"
#include "language.h"
#include "player.h"

using namespace std;

Move::Move() {
    row = 0;
    column = 0;
    letters.clear();
    score = 0;
    ishorizontal = false;
}

void Move::set(int r, int c, char h, const std::string& l) {
    row = r;
    column = c;
    letters = l;    
    if(h == 'H' || h == 'h')
        ishorizontal = true;
    if(h == 'V' || h == 'v')
        ishorizontal = false;
}

void Move::setRow(int r) {
    row = r;
}

void Move::setCol(int c) {
    column = c;
}

void Move::setHorizontal(char h) {
    if(h == 'H' || h == 'h')
        ishorizontal = true;
    if(h == 'V' || h == 'v')
        ishorizontal = false;
}

void Move::setLetters(const std::string& l) {
    letters = l;
}

int Move::findScore(const Language& l) const {
    int score = 0;
    const char *s = letters.c_str();
    
    if(!l.query(letters))
        score = -1;
    else{
        for(int i = 0; i != letters.size(); i++)
            score = score + l.getScore(s[i]);
    }
    
    return score;
}

void Move::setScore(int s) {
    score = s;
}

int Move::getScore() const {
    return score;
}

int Move::getRow() const {
    return row;
}

int Move::getCol() const {
    return column;
}

std::string Move::getLetters() const {
    return letters;
}

bool Move::isHorizontal() const {
    return ishorizontal;
}

/*Nota para mi: El cout y el cin so objetos, entonces, en vez de usar
 dichos objetos, podemos usar otros como es en este caso os e is*/

void Move::print(std::ostream& os) {
    char h;
    if(isHorizontal())
        h = 'H';
    else
        h = 'h';
    
    os << h << " " << row << " " << column << " " << letters;
}

void Move::read(std::istream& is) {
    char h;
    int c,r;
    std:string l;
    
    is >> h;
    is >> r;
    is >> c;
    is >> l;
    
    if(is)
        l = toISO(l);
        
    set(r,c,h,l);
}
