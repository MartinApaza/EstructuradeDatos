#pragma once

#include <string>

using namespace std;

class ProgresoFisico
{
private:

    int idCliente;

    string fecha;

    float peso;

    float altura;

public:

    ProgresoFisico();

    ProgresoFisico(
        int idCliente,
        string fecha,
        float peso,
        float altura
    );

    float calcularIMC();

    int getIdCliente();

    string getFecha();

    float getPeso();

    float getAltura();
};

