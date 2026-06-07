#include "ProgresoFisico.h"

ProgresoFisico::ProgresoFisico()
{

}

ProgresoFisico::ProgresoFisico(
    int idCliente,
    string fecha,
    float peso,
    float altura
)
{
    this->idCliente = idCliente;
    this->fecha = fecha;
    this->peso = peso;
    this->altura = altura;
}

float ProgresoFisico::calcularIMC()
{
    return peso /
        (altura * altura);
}

int ProgresoFisico::getIdCliente()
{
    return idCliente;
}

string ProgresoFisico::getFecha()
{
    return fecha;
}

float ProgresoFisico::getPeso()
{
    return peso;
}

float ProgresoFisico::getAltura()
{
    return altura;
}