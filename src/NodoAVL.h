#pragma once

#include "Cliente.h"

class NodoAVL
{
public:

    Cliente cliente;

    NodoAVL* izquierda;
    NodoAVL* derecha;

    int altura;

    NodoAVL(const Cliente& cliente)
    {
        this->cliente = cliente;

        izquierda = nullptr;
        derecha = nullptr;

        altura = 1;
    }
};
