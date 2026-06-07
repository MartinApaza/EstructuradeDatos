#pragma once

#include "ProgresoFisico.h"

class NodoProgreso
{
public:

    ProgresoFisico dato;

    NodoProgreso* siguiente;

    NodoProgreso(
        ProgresoFisico dato
    );
};
