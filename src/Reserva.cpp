#include "Reserva.h"

Reserva::Reserva()
{

}

Reserva::Reserva(
    int idReserva,
    int idCliente,
    int idCoach,
    string fecha,
    string hora
)
{
    this->idReserva = idReserva;
    this->idCliente = idCliente;
    this->idCoach = idCoach;
    this->fecha = fecha;
    this->hora = hora;
}

int Reserva::getIdReserva()
{
    return idReserva;
}

int Reserva::getIdCliente()
{
    return idCliente;
}

int Reserva::getIdCoach()
{
    return idCoach;
}

string Reserva::getFecha()
{
    return fecha;
}

string Reserva::getHora()
{
    return hora;
}