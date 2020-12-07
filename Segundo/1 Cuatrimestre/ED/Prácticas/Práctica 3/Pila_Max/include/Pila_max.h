/**
 * @author Daniel Alconchel Vázquez y Mario García Márquez
 * @file Pila_max.h
 */

#ifndef PILA_MAX_PILA_MAX_H
#define PILA_MAX_PILA_MAX_H

#include <cassert>
#include <iostream>

using namespace std;

#define CUAL_COMPILA 1
#if CUAL_COMPILA==1
#include "./Pila_max_VD.h"
#elif CUAL_COMPILA==2
#include "./Pila_max_Cola.h"
#endif


#endif //PILA_MAX_PILA_MAX_H
