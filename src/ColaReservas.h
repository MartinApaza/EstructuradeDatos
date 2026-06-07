#pragma once
#include <queue>   // Incluye la estructura de datos estandar tipo Cola (FIFO: First-In, First-Out)
#include <vector>  // Incluye el contenedor dinamico secuencial para la exportacion de datos
#include "Reserva.h" // Incluye la definicion de la entidad Reserva que almacenara la cola
using namespace std;
// Clase encargada de administrar el flujo y orden de atencion de las reservas del gimnasio
class ColaReservas {
private:
    queue<Reserva> cola; // Contenedor FIFO privado que aloja y restringe el acceso directo a los objetos Reserva
public:
    // Agrega una reserva al final de la linea de espera (operacion push/encolar)
    void agregarReserva(Reserva reserva);
    // Extrae de forma segura y devuelve la reserva que se encuentra en la primera posicion (operacion pop/desencolar)
    Reserva siguiente();
    // Verifica si el contenedor se encuentra completamente vacio de registros
    bool vacia();
    // Devuelve el conteo exacto de objetos Reserva pendientes por procesar en la fila
    int cantidad();
    // --- Accesor aditivo para la interfaz ---
    // Duplica la cola internamente y exporta todos los elementos en un vector sin corromper el contenedor original
    vector<Reserva> listar();
};