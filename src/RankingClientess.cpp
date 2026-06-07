#include "RankingClientess.h"

#include <algorithm>

void RankingClientess::ordenarPorIMC(
    vector<Cliente>& clientes
)
{
    sort(
        clientes.begin(),
        clientes.end(),
        [](Cliente a, Cliente b)
        {
            return a.calcularIMC()
                < b.calcularIMC();
        }
    );
}

void RankingClientess::ordenarPorPeso(
    vector<Cliente>& clientes
)
{
    sort(
        clientes.begin(),
        clientes.end(),
        [](Cliente a, Cliente b)
        {
            return a.getPeso()
                < b.getPeso();
        }
    );
}

void RankingClientess::ordenarPorEdad(
    vector<Cliente>& clientes
)
{
    sort(
        clientes.begin(),
        clientes.end(),
        [](Cliente a, Cliente b)
        {
            return a.getEdad()
                < b.getEdad();
        }
    );
}