#include "ColaTurnos.h"
// Agrega el ID de un cliente al final de la linea de espera (operacion de encolar)
void ColaTurnos::agregarCliente(int id) {
    cola.push(id); // Inserta el identificador numerico en la ultima posicion (back) de la cola
}
// Remueve de la fila al cliente que se encuentra al inicio de la espera (operacion de desencolar)
void ColaTurnos::atenderCliente() {
    if (!cola.empty()) // Proteccion estructural: Solo procede si la cola contiene elementos
        cola.pop(); // Elimina fisicamente el elemento del frente, moviendo la fila hacia adelante
}
// Consulta y devuelve el ID del proximo cliente en ser atendido sin removerlo de la estructura
int ColaTurnos::siguienteCliente() {
    if (cola.empty()) // Validacion de seguridad: Si la cola se encuentra vacia
        return -1; // Retorna -1 como codigo de error para indicar que no hay clientes en espera
    return cola.front(); // Retorna el valor numerico almacenado en el primer nodo (frente) de la cola
}
// Evalua si existen o no turnos pendientes por procesar en la fila
bool ColaTurnos::vacia() {
    return cola.empty(); // Retorna verdadero (true) si el contenedor no tiene elementos, falso (false) si tiene registros
}
// Obtiene el conteo total y exacto de personas en la fila de turnos de atencion
int ColaTurnos::cantidad() {
    return static_cast<int>(cola.size()); // Convierte el tamano de la estructura de datos a un entero convencional
}
// Exporta la lista completa de IDs de socios en su orden cronologico FIFO riguroso, resguardando la cola original
vector<int> ColaTurnos::listar() {
    vector<int> resultado; // Inicializa el contenedor dinamico secuencial para la salida de datos
    queue<int> copia = cola; // Genera un duplicado superficial del contenedor para poder vaciarlo sin alterar la clase
    while (!copia.empty()) // Bucle de extraccion que se ejecuta mientras queden elementos dentro del clon de la cola
    {
        resultado.push_back(copia.front()); // Introduce el identificador del frente actual al final del vector
        copia.pop(); // Descarta el elemento procesado del clon para desplazar el frente al siguiente ID
    }
    return resultado; // Retorna la coleccion vectorizada manteniendo el orden original de llegada
}