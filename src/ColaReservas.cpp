#include "ColaReservas.h"
// Agrega una nueva reserva al final de la estructura (operacion de encolar en FIFO)
void ColaReservas::agregarReserva(Reserva reserva) {
    cola.push(reserva); // Inserta el objeto reserva al final de la cola (back)
}
// Extrae y devuelve la reserva que se encuentra al frente de la cola (desencolar)
Reserva ColaReservas::siguiente() {
    if (cola.empty()) // Proteccion: Si la cola se encuentra vacia
        return Reserva(); // Retorna un objeto Reserva vacio por defecto para evitar fallas catastroficas
    Reserva frente = cola.front(); // Captura una copia de la reserva que esta en primer lugar (frente)
    cola.pop(); // Elimina fisicamente el elemento del frente de la estructura, avanzando el inicio al siguiente nodo
    return frente; // Retorna la reserva capturada antes de ser removida
}
// Verifica si la estructura contiene o no elementos almacenados
bool ColaReservas::vacia() {
    return cola.empty(); // Retorna verdadero (true) si la cola no tiene nodos, falso (false) si tiene al menos uno
}
// Devuelve el conteo exacto de reservas que se encuentran actualmente esperando en la cola
int ColaReservas::cantidad() {
    return static_cast<int>(cola.size()); // Convierte y retorna el tamaño de la cola como un entero estandar
}
// Genera un vector con todas las reservas en su orden cronologico FIFO estricto, sin alterar la cola original
vector<Reserva> ColaReservas::listar() {
    vector<Reserva> resultado; // Inicializa el contenedor dinamicamente para el retorno de datos
    queue<Reserva> copia = cola; // Crea un duplicado superficial completo de la cola para poder vaciarla sin dañar la propiedad de la clase
    while (!copia.empty()) // Ciclo de vaciado que se ejecuta mientras queden elementos en el clon
    {
        resultado.push_back(copia.front()); // Introduce el elemento del frente actual en la ultima posicion del vector
        copia.pop(); // Elimina el elemento procesado del frente del clon para avanzar al siguiente registro
    }
    return resultado; // Retorna la lista vectorizada manteniendo el orden original de la fila
}