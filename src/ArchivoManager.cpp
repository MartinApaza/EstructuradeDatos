#include "ArchivoManager.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "Cliente.h"
#include "NodoCliente.h"
#include "Reserva.h"

using namespace std;

// ====================== CLIENTES ======================

void ArchivoManager::guardarClientes(
    ListaClientes& lista,
    const string& nombreArchivo
)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    NodoCliente* actual = lista.getCabeza();

    while (actual != nullptr)
    {
        Cliente c = actual->dato;

        archivo
            << c.getId() << ";"
            << c.getNombre() << ";"
            << c.getApellido() << ";"
            << c.getEdad() << ";"
            << c.getPeso() << ";"
            << c.getAltura() << ";"
            << c.getTelefono() << ";"
            << c.getCorreo() << ";"
            << c.getIdMembresia()
            << "\n";

        actual = actual->siguiente;
    }

    archivo.close();
}

void ArchivoManager::cargarClientes(
    ListaClientes& lista,
    const string& nombreArchivo
)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    string linea;

    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        stringstream ss(linea);

        string dato;
        string campos[9];

        int i = 0;

        while (i < 9 && getline(ss, dato, ';'))
        {
            campos[i++] = dato;
        }

        if (i == 9)
        {
            try
            {
                Cliente c(
                    stoi(campos[0]),
                    campos[1],
                    campos[2],
                    stoi(campos[3]),
                    stof(campos[4]),
                    stof(campos[5]),
                    campos[6],
                    campos[7],
                    stoi(campos[8])
                );

                lista.insertar(c);
            }
            catch (...)
            {
                // Linea corrupta: se ignora y se continua con el resto.
            }
        }
    }

    archivo.close();
}

// ====================== TURNOS ======================

void ArchivoManager::guardarTurnos(
    ColaTurnos& cola,
    const string& nombreArchivo
)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    vector<int> ids = cola.listar();

    for (int id : ids)
        archivo << id << "\n";

    archivo.close();
}

void ArchivoManager::cargarTurnos(
    ColaTurnos& cola,
    const string& nombreArchivo
)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    string linea;

    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        try
        {
            cola.agregarCliente(stoi(linea));
        }
        catch (...)
        {
        }
    }

    archivo.close();
}

// ====================== RESERVAS ======================

void ArchivoManager::guardarReservas(
    ColaReservas& cola,
    const string& nombreArchivo
)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    vector<Reserva> reservas = cola.listar();

    for (Reserva r : reservas)
    {
        archivo
            << r.getIdReserva() << ";"
            << r.getIdCliente() << ";"
            << r.getIdCoach() << ";"
            << r.getFecha() << ";"
            << r.getHora()
            << "\n";
    }

    archivo.close();
}

void ArchivoManager::cargarReservas(
    ColaReservas& cola,
    const string& nombreArchivo
)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
        return;

    string linea;

    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        stringstream ss(linea);

        string dato;
        string campos[5];

        int i = 0;

        while (i < 5 && getline(ss, dato, ';'))
        {
            campos[i++] = dato;
        }

        if (i == 5)
        {
            try
            {
                Reserva r(
                    stoi(campos[0]),
                    stoi(campos[1]),
                    stoi(campos[2]),
                    campos[3],
                    campos[4]
                );

                cola.agregarReserva(r);
            }
            catch (...)
            {
            }
        }
    }

    archivo.close();
}
