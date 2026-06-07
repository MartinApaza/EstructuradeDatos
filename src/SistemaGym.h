#pragma once

#include <vector>
#include <string>

#include "Cliente.h"
#include "Membresia.h"
#include "Pago.h"
#include "Coach.h"

#include "ListaClientes.h"
#include "AVLClientes.h"

#include "PilaHistorial.h"
#include "ColaTurnos.h"
#include "ColaReservas.h"
#include "Reserva.h"

using namespace std;

// ------------------------------------------------------------------
//  SistemaGym  (fachada del backend)
// ------------------------------------------------------------------
//  Se conservan TODOS los metodos originales. Se AGREGAN, de forma aditiva:
//   - acceso a las estructuras internas para que la GUI pueda recorrerlas
//   - cola de reservas (no existia en el original)
//   - generacion de ids consecutivos
//   - encolado/atencion de turnos y reservas con registro en historial
//   - persistencia real a disco a traves de ArchivoManager
// ------------------------------------------------------------------
class SistemaGym
{
private:

    ListaClientes listaClientes;

    AVLClientes avlClientes;

    vector<Membresia> membresias;

    vector<Pago> pagos;

    vector<Coach> coaches;

    PilaHistorial historial;

    ColaTurnos colaTurnos;

    ColaReservas colaReservas;   // <-- aditivo

public:

    SistemaGym();

    // ---------- API original ----------
    void agregarCliente(const Cliente& cliente);

    Cliente* buscarCliente(int id);

    bool eliminarCliente(int id);

    int totalClientes();

    void agregarPago(const Pago& pago);

    void agregarCoach(const Coach& coach);

    void agregarMembresia(const Membresia& membresia);

    Membresia* obtenerMembresia(int id);

    vector<Coach>& obtenerCoaches();

    vector<Pago>& obtenerPagos();

    string ultimoMovimiento();

    // ---------- Accesores aditivos para la GUI ----------
    ListaClientes& getListaClientes();

    ColaTurnos& getColaTurnos();

    ColaReservas& getColaReservas();

    vector<Membresia>& obtenerMembresias();

    int siguienteIdCliente();

    int siguienteIdReserva();

    bool existeCliente(int id);

    // ---------- Turnos ----------
    void encolarTurno(int idCliente);

    int atenderTurno();              // devuelve el id atendido o -1 si vacia

    int turnosPendientes();

    // ---------- Reservas ----------
    void encolarReserva(Reserva reserva);

    Reserva atenderReserva();        // desencola y devuelve la siguiente

    int reservasPendientes();

    // ---------- Persistencia (ArchivoManager) ----------
    void cargarDesdeArchivos();      // lectura inicial de los .txt

    void guardarClientesArchivo();

    void guardarTurnosArchivo();

    void guardarReservasArchivo();

    void guardarTodo();

private:

    int siguienteReserva;            // contador interno para ids de reserva
};
