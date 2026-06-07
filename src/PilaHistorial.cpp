#include "PilaHistorial.h"

void PilaHistorial::registrar(string accion)
{
    historial.push(accion);
}

string PilaHistorial::ultimoMovimiento()
{
    if (historial.empty())
        return "Sin historial";

    return historial.top();
}

bool PilaHistorial::vacia()
{
    return historial.empty();
}