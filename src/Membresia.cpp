#include "Membresia.h"

Membresia::Membresia()
{
    idMembresia = 0;
    activa = false;
    precio = 0;
}

Membresia::Membresia(
    int id,
    string tipo,
    string inicio,
    string fin,
    bool activa,
    double precio
)
{
    this->idMembresia = id;

    this->tipo = tipo;

    fechaInicio = inicio;
    fechaFin = fin;

    this->activa = activa;

    this->precio = precio;
}

int Membresia::getId() const
{
    return idMembresia;
}

string Membresia::getTipo() const
{
    return tipo;
}

string Membresia::getFechaInicio() const
{
    return fechaInicio;
}

string Membresia::getFechaFin() const
{
    return fechaFin;
}

bool Membresia::estaActiva() const
{
    return activa;
}

double Membresia::getPrecio() const
{
    return precio;
}

void Membresia::activar()
{
    activa = true;
}

void Membresia::desactivar()
{
    activa = false;
}