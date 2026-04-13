#pragma once

#include "Nodo.h"

class Pila {
    Nodo* inicio = new Nodo;
public:
    Pila();
    void push();
    void pop();
    void show();
    void top();
    void size();
};


