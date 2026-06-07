#pragma once

#include <string>

using namespace std;

// Reconstruido a partir de Pago.cpp (el .h original llegó vacío en el .rar).
class Pago
{
private:

    int idPago;

    int idCliente;

    double monto;

    string fecha;

    string metodoPago;

public:

    Pago();

    Pago(
        int idPago,
        int idCliente,
        double monto,
        string fecha,
        string metodo
    );

    int getIdPago() const;

    int getIdCliente() const;

    double getMonto() const;

    string getFecha() const;

    string getMetodo() const;
};
