#pragma once 
#include "Dato.h"
class Nodo {
public:
    Dato dato;
    Nodo* puntero;

    Nodo() { //Constructor de la clase
        puntero = NULL;
    }
};