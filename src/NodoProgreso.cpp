#include "NodoProgreso.h"

NodoProgreso::NodoProgreso(
    ProgresoFisico dato
)
{
    this->dato = dato;
    siguiente = nullptr;
}