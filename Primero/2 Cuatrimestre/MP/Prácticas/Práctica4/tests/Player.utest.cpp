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
#include "language.h"
#include "bag.h"
#include "player.h"

using namespace std;


int main() {
    Player player;
    string s;
    player.clear();
    cout << "VALIDATING clear(): "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
//    player.add("12345678");
//    cout << "VALIDATING add() (long): "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    player.clear();
    player.add("7654321");
    cout << "METHOD add() (fair): "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    player.clear();
    player.add("");
    cout << "METHOD add() (short): "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    player.clear();
    player.add("7654321");
    cout << "METHOD isValid(): "<<"11  "<< player.isValid("11")<<endl;
    cout << "METHOD  isValid(): "<<"123456789  "<< player.isValid("123456789")<<endl;
    cout << "METHOD  isValid(): "<<"12345  "<< player.isValid("12345")<<endl;
    s="123456789";
    player.clear();
    player.add("7654321");
    player.extract(s);
    cout << "METHOD  extract(long): "<<s+" "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    s="12345";
    player.clear();
    player.add("7654321");
    player.extract(s);
    cout << "METHOD  extract(fair): "<<s+" "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    s="1234567";
    player.clear();
    player.add("7654321");
    player.extract(s);
    cout << "METHOD  extract(full): "<<s+" "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    s="";
    player.clear();
    player.add("7654321");
    player.extract(s);
    cout << "METHOD  extract(short): "<<s+" "<<player.size()<<" "<<toUTF(player.to_string())<<endl;
    return 0;
}
