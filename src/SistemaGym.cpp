#include "SistemaGym.h"

#include "ArchivoManager.h"
#include "NodoCliente.h"

SistemaGym::SistemaGym()
{
    siguienteReserva = 1;

    // Catalogo de membresias por defecto para que la GUI y el ChatBot
    // tengan datos coherentes desde el primer arranque.
    membresias.push_back(
        Membresia(1, "Basica", "01/01/2026", "31/12/2026", true, 150)
    );

    membresias.push_back(
        Membresia(2, "Premium", "01/01/2026", "31/12/2026", true, 250)
    );

    membresias.push_back(
        Membresia(3, "VIP", "01/01/2026", "31/12/2026", true, 400)
    );
}

// ================= API original =================

void SistemaGym::agregarCliente(const Cliente& cliente)
{
    listaClientes.insertar(cliente);

    avlClientes.insertar(cliente);

    historial.registrar(
        "Socio agregado: #" + to_string(cliente.getId())
        + " " + cliente.getNombre()
    );
}

Cliente* SistemaGym::buscarCliente(int id)
{
    return avlClientes.buscar(id);
}

bool SistemaGym::eliminarCliente(int id)
{
    bool eliminado = listaClientes.eliminar(id);

    if (eliminado)
    {
        historial.registrar("Socio eliminado: #" + to_string(id));
    }

    return eliminado;
}

int SistemaGym::totalClientes()
{
    return listaClientes.cantidad();
}

void SistemaGym::agregarPago(const Pago& pago)
{
    pagos.push_back(pago);

    historial.registrar(
        "Pago registrado: $" + to_string((int)pago.getMonto())
    );
}

void SistemaGym::agregarCoach(const Coach& coach)
{
    coaches.push_back(coach);
}

void SistemaGym::agregarMembresia(const Membresia& membresia)
{
    membresias.push_back(membresia);
}

Membresia* SistemaGym::obtenerMembresia(int id)
{
    for (auto& m : membresias)
    {
        if (m.getId() == id)
            return &m;
    }

    return nullptr;
}

vector<Coach>& SistemaGym::obtenerCoaches()
{
    return coaches;
}

vector<Pago>& SistemaGym::obtenerPagos()
{
    return pagos;
}

string SistemaGym::ultimoMovimiento()
{
    return historial.ultimoMovimiento();
}

// ================= Accesores aditivos =================

ListaClientes& SistemaGym::getListaClientes()
{
    return listaClientes;
}

ColaTurnos& SistemaGym::getColaTurnos()
{
    return colaTurnos;
}

ColaReservas& SistemaGym::getColaReservas()
{
    return colaReservas;
}

vector<Membresia>& SistemaGym::obtenerMembresias()
{
    return membresias;
}

int SistemaGym::siguienteIdCliente()
{
    int maximo = 0;

    NodoCliente* actual = listaClientes.getCabeza();

    while (actual != nullptr)
    {
        if (actual->dato.getId() > maximo)
            maximo = actual->dato.getId();

        actual = actual->siguiente;
    }

    return maximo + 1;
}

int SistemaGym::siguienteIdReserva()
{
    return siguienteReserva;
}

bool SistemaGym::existeCliente(int id)
{
    return avlClientes.buscar(id) != nullptr;
}

// ================= Turnos =================

void SistemaGym::encolarTurno(int idCliente)
{
    colaTurnos.agregarCliente(idCliente);

    historial.registrar(
        "Turno encolado: socio #" + to_string(idCliente)
    );
}

int SistemaGym::atenderTurno()
{
    if (colaTurnos.vacia())
        return -1;

    int id = colaTurnos.siguienteCliente();

    colaTurnos.atenderCliente();

    historial.registrar(
        "Turno atendido: socio #" + to_string(id)
    );

    return id;
}

int SistemaGym::turnosPendientes()
{
    return colaTurnos.cantidad();
}

// ================= Reservas =================

void SistemaGym::encolarReserva(Reserva reserva)
{
    colaReservas.agregarReserva(reserva);

    if (reserva.getIdReserva() >= siguienteReserva)
        siguienteReserva = reserva.getIdReserva() + 1;

    historial.registrar(
        "Reserva registrada: #" + to_string(reserva.getIdReserva())
    );
}

Reserva SistemaGym::atenderReserva()
{
    Reserva r = colaReservas.siguiente();

    historial.registrar(
        "Reserva atendida: #" + to_string(r.getIdReserva())
    );

    return r;
}

int SistemaGym::reservasPendientes()
{
    return colaReservas.cantidad();
}

// ================= Persistencia =================

void SistemaGym::cargarDesdeArchivos()
{
    // 1) Clientes -> lista enlazada
    ArchivoManager::cargarClientes(listaClientes);

    // 2) Reconstruir el AVL a partir de la lista para mantener ambos
    //    indices sincronizados (la lista preserva el orden de insercion;
    //    el AVL da busqueda O(log n) por id).
    NodoCliente* actual = listaClientes.getCabeza();

    while (actual != nullptr)
    {
        avlClientes.insertar(actual->dato);
        actual = actual->siguiente;
    }

    // 3) Turnos y reservas
    ArchivoManager::cargarTurnos(colaTurnos);
    ArchivoManager::cargarReservas(colaReservas);

    // 4) Ajustar el contador de reservas al maximo id existente
    vector<Reserva> rs = colaReservas.listar();

    for (Reserva& r : rs)
    {
        if (r.getIdReserva() >= siguienteReserva)
            siguienteReserva = r.getIdReserva() + 1;
    }

    historial.registrar("Datos cargados desde disco");
}

void SistemaGym::guardarClientesArchivo()
{
    ArchivoManager::guardarClientes(listaClientes);
}

void SistemaGym::guardarTurnosArchivo()
{
    ArchivoManager::guardarTurnos(colaTurnos);
}

void SistemaGym::guardarReservasArchivo()
{
    ArchivoManager::guardarReservas(colaReservas);
}

void SistemaGym::guardarTodo()
{
    guardarClientesArchivo();
    guardarTurnosArchivo();
    guardarReservasArchivo();
}
