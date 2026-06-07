#pragma once

#include <string>

using namespace std;

class Reserva
{
private:

    int idReserva;

    int idCliente;

    int idCoach;

    string fecha;

    string hora;

public:

    Reserva();

    Reserva(
        int idReserva,
        int idCliente,
        int idCoach,
        string fecha,
        string hora
    );

    int getIdReserva();

    int getIdCliente();

    int getIdCoach();

    string getFecha();

    string getHora();
};