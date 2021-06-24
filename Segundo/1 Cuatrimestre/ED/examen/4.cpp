#include<iostream>
#include<list>
#include<set>

using namespace std;

bool proper_subset(list<set<int>> &L){
    list<set<int>>:: iterator it1, it2;
    it1 = L.begin();
    it2= L.begin();
    ++it2;

    while(it2 != L.end()){
        set<int> aux1, aux2;
        aux1 = *it1;
        aux2 = *it2;

        // Comprobamos si son el mismo conjunto
        if(aux1 == aux2)
            return false;
        else{   // Comprobamos que los elementos de uno pertenecen a otro
            set<int>::iterator i1;
            i1 = aux1.begin();
            while(i1 != aux1.end()){
                if(aux2.find(*i1) == aux2.end())
                    return false;
                ++i1;
            }
        }

        ++it1;
        ++it2;
    }
    return true;
}

int main(){
    set<int> A1, A2, A3;
    list<set<int>> A;
    A1.insert(1);
    A1.insert(2);
    A2.insert(1);
    A2.insert(2);
    A2.insert(3);
    A3.insert(1);
    A3.insert(2);
    A3.insert(3);
    A3.insert(4);
    A.push_back(A1);
    A.push_back(A2);
    A.push_back(A3);
    if(proper_subset(A)){
        cout << "Cumple la condición" << endl;
    }else{
        cout << "No cumple la condición" << endl;
    }

    return 0;

}