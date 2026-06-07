#pragma once

#include <string>

using namespace std;

// Reconstruido a partir de Membresia.cpp (el .h original llegó vacío en el .rar).
class Membresia
{
private:

    int idMembresia;

    string tipo;

    string fechaInicio;
    string fechaFin;

    bool activa;

    double precio;

public:

    Membresia();

    Membresia(
        int id,
        string tipo,
        string inicio,
        string fin,
        bool activa,
        double precio
    );

    int getId() const;

    string getTipo() const;

    string getFechaInicio() const;

    string getFechaFin() const;

    bool estaActiva() const;

    double getPrecio() const;

    void activar();

    void desactivar();
};
