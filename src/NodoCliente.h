#pragma once
#include "Cliente.h"

class NodoCliente
{
public:

    Cliente dato;

    NodoCliente* siguiente;

    NodoCliente(const Cliente& cliente)
    {
        dato = cliente;
        siguiente = nullptr;
    }
};