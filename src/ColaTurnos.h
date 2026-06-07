#pragma once
#include <queue>   // Incluye la estructura de datos estandar tipo Cola (FIFO: First-In, First-Out)
#include <vector>  // Incluye el contenedor dinamico secuencial para la exportacion de datos hacia la GUI
using namespace std;
// Clase encargada de administrar la fila de espera de los socios en el gimnasio mediante sus IDs numericos
class ColaTurnos {
private:
    queue<int> cola; // Contenedor FIFO privado que almacena los identificadores enteros de los clientes en espera
public:
    // Agrega el ID de un socio al final de la linea de espera (operacion push/encolar)
    void agregarCliente(int id);
    // Remueve de forma definitiva al cliente que se encuentra al frente de la fila (operacion pop/desencolar)
    void atenderCliente();
    // Consulta y devuelve el ID del proximo cliente a ser atendido sin retirarlo de la fila
    int siguienteCliente();
    // Verifica si el contenedor de turnos se encuentra completamente vacio
    bool vacia();
    // --- Accesores aditivos para la interfaz ---
    // Devuelve el conteo exacto y actual de socios esperando en la cola (util para indicadores KPI)
    int cantidad();
    // Duplica la cola internamente y exporta los IDs en un vector sin alterar el contenedor original de la clase
    vector<int> listar();
};