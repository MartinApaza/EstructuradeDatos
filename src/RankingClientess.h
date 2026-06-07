#pragma once

#include <vector>

#include "Cliente.h"

using namespace std;

// Reconstruido a partir de RankingClientess.cpp (el .h original llegó vacío).
// Ordenamientos auxiliares sobre vectores de clientes.
class RankingClientess
{
public:

    static void ordenarPorIMC(vector<Cliente>& clientes);

    static void ordenarPorPeso(vector<Cliente>& clientes);

    static void ordenarPorEdad(vector<Cliente>& clientes);
};
