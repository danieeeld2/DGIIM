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
    Bag bag;
    string s;
    bag.set("");
    cout << "Method set()/size() empty "<<bag.size()<<endl;
    bag.set("1234567");
    cout << "Method set()/size() 1234567 "<<bag.size()<<endl;
    bag.set("");
    cout << "Method to_string() empty "<<bag.to_string()<<endl;
    bag.set("1234567");
    cout << "Method to_string() 1234567 "<<bag.to_string()<<endl;
    bag.set("1234567");
    bag.extract(0);
    cout << "Method extract(0) "<<bag.to_string()<<endl;
    bag.set("1234567");
    bag.extract(3);
    cout << "Method extract(3) "<<bag.to_string()<<endl;
    bag.set("1234567");
    bag.extract(13);
    cout << "Method extract(13) "<<bag.to_string()<<endl;
    bag.set("1234567");
    bag.extract(3);
    bag.extract(3);
    cout << "Method extract(3+3) "<<bag.to_string()<<endl;
    bag.extract(3);
    bag.extract(3);
    bag.extract(3);
    cout << "Method extract(3+3+3) "<<bag.to_string()<<endl;
    return 0;
}
