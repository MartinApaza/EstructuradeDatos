#include "Pago.h"

Pago::Pago()
{
    idPago = 0;
    idCliente = 0;
    monto = 0;
}

Pago::Pago(
    int idPago,
    int idCliente,
    double monto,
    string fecha,
    string metodo
)
{
    this->idPago = idPago;

    this->idCliente = idCliente;

    this->monto = monto;

    this->fecha = fecha;

    metodoPago = metodo;
}

int Pago::getIdPago() const
{
    return idPago;
}

int Pago::getIdCliente() const
{
    return idCliente;
}

double Pago::getMonto() const
{
    return monto;
}

string Pago::getFecha() const
{
    return fecha;
}

string Pago::getMetodo() const
{
    return metodoPago;
}