#include<iostream>
#include<vector>
#include<list>

using namespace std;

class matriz_singular{
    private:
    /*  La idea va a consistir en que cada posicion del vector representa
        una fila de la matriz y la lista asociada a dicha posicion almacena los 
        elementos de dicha fila */
    vector<list<int>> datos;

    public:

    int operator()(int fil, int colum){   // Suponemos que introduce una posición valida
        list<int>::iterator it;
        it = datos[fil].begin();
        for(int i=1; i<colum; i++){
            ++it;
        }
        return *it;
    };

    class iterator{
        private:
        vector<list<int>>::iterator it1, final1;
        list<int>::iterator it2, final2;
        public:
        iterator(){}

        bool operator==(const iterator &i){
            return i.it1 == it1 && i.it2 == it2;
        }

        bool operator!=(const iterator &i){
            return i.it1 != it1 && i.it2 != it2;
        }

        int& operator*(){
            return (*it2);
        }

        iterator & operator++(){
            ++it2;              // Se me ha olvidado poner la condicion par
            if(it2 == final2){
                ++it1;
                it2 = (*it1).begin();
                final2 = (*it1).end();
            }
            return *this;
        }

        friend class matriz_singular;
    };

    iterator begin() {
        iterator i;
        i.it1 = datos.begin();
        i.final1 = datos.end();

        i.it2 = (*i.it1).begin();
        i.final2 = (*i.it1).end();
        
        if(*i % 2 == 0)
            ++i;

        return i;
    }

    iterator end() {
        iterator i;
        i.it1 = datos.end();
        i.final1 = datos.end();
        i.it2 = (*i.it1).end();
        i.final2 = (*i.it1).end();
        return i;
    }
};