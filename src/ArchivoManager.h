#pragma once

#include <string>

#include "ListaClientes.h"
#include "ColaTurnos.h"
#include "ColaReservas.h"

using namespace std;

//  Formatos de archivo (separador ';'):
//    clientes.txt : id;nombre;apellido;edad;peso;altura;telefono;correo;idMembresia
//    turnos.txt   : idCliente            (un id por linea)
//    reservas.txt : idReserva;idCliente;idCoach;fecha;hora
// ------------------------------------------------------------------
class ArchivoManager
{
public:

    // --- Clientes ---
    static void guardarClientes(
        ListaClientes& lista,
        const string& nombreArchivo = "clientes.txt"
    );

    static void cargarClientes(
        ListaClientes& lista,
        const string& nombreArchivo = "clientes.txt"
    );

    // --- Turnos (cola FIFO de ids de cliente) ---
    static void guardarTurnos(
        ColaTurnos& cola,
        const string& nombreArchivo = "turnos.txt"
    );

    static void cargarTurnos(
        ColaTurnos& cola,
        const string& nombreArchivo = "turnos.txt"
    );

    // --- Reservas (cola FIFO de objetos Reserva) ---
    static void guardarReservas(
        ColaReservas& cola,
        const string& nombreArchivo = "reservas.txt"
    );

    static void cargarReservas(
        ColaReservas& cola,
        const string& nombreArchivo = "reservas.txt"
    );
};
