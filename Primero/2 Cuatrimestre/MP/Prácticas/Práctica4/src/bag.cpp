/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <fstream>
#include <cassert>
#include <random>
#include <algorithm>
#include "bag.h"
#include "language.h"

///@warning Fill missing #include

using namespace std;

/**
 * @brief Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 * @warning TO BE FULLY IMPLEMENTED. 
 * @warning Check parameters const/&/* and their types
 */
void removeVector(char *s, int &n, int p);


// Main methods

Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

///@warning Implement all the methods

// Auxiliary functions 

void shuffleVector(char *s, int n, int id) {
    vector <char> aux(s, s+n);
    unsigned seed = id;
    std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed));
    for (int i=0; i<n; i++)
        s[i] = aux[i];    
}

void removeVector(char *s, int &n, int p){
    for(int i = p; i < n - 1; i++){
        s[i] = s[i+1];
    }
    n--;
}

//  Bag class functions
char Bag::get(int p) const {
    assert (p <=  nletters && p >= 0);
    return letters[p];
}

void Bag::set(int p, char c) {
    assert (p <= MAXBAG && p >= 0);
    letters[p] = c;
}

void Bag::setRandom(int p){
    id = p;
}

void Bag::define(const Language &l) {
//    nletters=0;
//    string letters = l.getLetterSet();
//    for(int i = 0; i < letters.size(); i++){
//        for(int j = 0; j < l.getFrequency(letters[i]); j++){
//            set(nletters, letters[i]);
//            nletters++;
//        }
//    }
//    shuffleVector(this->letters, nletters, id);
    ifstream ifile("build/bags.data");
    string mybag, mylang;
    int myrandom;
    bool found=false;

    if (!ifile) return;
    while (!ifile.eof() && !found) {
        ifile >> mylang >> myrandom >> mybag;
        if (ifile && mylang==l.getLanguage() && myrandom == this->id)
            found = true;
    }
    ifile.close();
    if (found)
        this->set(toISO(mybag));
    else
        this->set("");
}

int Bag::size() const{
    return nletters;
}

string Bag::to_string() const{
    string str;
    str.resize(nletters);
    for(int i = 0; i < nletters; i++)
        str[i] = get(i);
    return str;
}

void Bag::set(string s) {
    for(int i = 0; i < s.size(); i++)
        set(i, s[i]);
    nletters = s.size();
}

string Bag::extract(int n){
    int number_to_extract = n;
    string str = "";
    if(n > nletters)
        number_to_extract = nletters;
    for(int i = 0; i < number_to_extract; i++)
        str.push_back(get(i));
    for(int i = 0; i < number_to_extract; i++)
        removeVector(letters, nletters, 0);
    return str;
}