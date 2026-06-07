#include "ListaClientes.h"
#include <iostream>
using namespace std;
// Constructor por defecto: Inicializa el punto de acceso (cabeza) de la lista enlazada como nulo
ListaClientes::ListaClientes() {
    cabeza = nullptr; // Define que la lista arranca completamente vacia
}
// Destructor de la clase: Se encarga de liberar secuencialmente toda la memoria dinamica reservada en el Heap
ListaClientes::~ListaClientes() {
    NodoCliente* actual = cabeza; // Puntero auxiliar para iniciar el recorrido de la lista desde el primer nodo
    while (actual != nullptr) // Ciclo que se mantiene activo mientras no se alcance el final de la estructura
    {
        NodoCliente* temp = actual; // Guarda temporalmente la direccion de memoria del nodo actual
        actual = actual->siguiente; // Mueve el puntero de recorrido al nodo consecutivo de la secuencia
        delete temp; // Libera de forma segura la memoria dinamica que ocupaba el nodo respaldado
    }
}
// Agrega un nuevo registro al final de la estructura (operacion de insercion con coste O(n))
void ListaClientes::insertar(const Cliente& cliente) {
    NodoCliente* nuevo = new NodoCliente(cliente); // Reserva memoria en el Heap e instancia un nuevo nodo con el dato
    if (cabeza == nullptr) // Validacion: Evalua si la lista se encuentra vacia
    {
        cabeza = nuevo; // Convierte al nuevo nodo en la cabeza de la lista enlazada
        return; // Concluye la ejecucion de la rutina
    }
    NodoCliente* actual = cabeza; // Puntero para rastrear secuencialmente la posicion de insercion
    while (actual->siguiente != nullptr) // Avanza por la lista hasta localizar el ultimo nodo de la secuencia
    {
        actual = actual->siguiente; // Desplaza el puntero de control al nodo eslabon subsecuente
    }
    actual->siguiente = nuevo; // Enlaza el puntero 'siguiente' del antiguo ultimo nodo hacia el nuevo nodo
}
// Ejecuta un algoritmo de busqueda lineal (coste O(n)) sobre la secuencia para hallar un ID especifico
Cliente* ListaClientes::buscar(int id) {
    NodoCliente* actual = cabeza; // Comienza el escaneo secuencial desde el nodo inicial (cabeza)
    while (actual != nullptr) // Explora la lista hasta encontrar el elemento o topar con el final de la estructura
    {
        if (actual->dato.getId() == id) // Evalua si el ID del nodo actual coincide con el buscado
            return &actual->dato; // Retorna la direccion de memoria exacta del objeto Cliente hallado
        actual = actual->siguiente; // Avanza el puntero de control al proximo nodo de la lista
    }
    return nullptr; // Retorna un puntero nulo en caso de no localizar coincidencias en la secuencia
}
// Remueve fisicamente un nodo de la estructura por su ID y reestructura los enlaces de forma segura
bool ListaClientes::eliminar(int id) {
    if (cabeza == nullptr) // Validacion de seguridad: Si la lista esta vacia, no hay nada que eliminar
        return false; // Finaliza la funcion notificando el fallo
    // ---- CASO ESPECIAL: El elemento a eliminar se encuentra en la Cabeza (Primer nodo) ----
    if (cabeza->dato.getId() == id)
    {
        NodoCliente* temp = cabeza; // Resguarda la direccion de memoria de la actual cabeza de la lista
        cabeza = cabeza->siguiente; // Desplaza el inicio de la lista hacia el segundo nodo de la secuencia
        delete temp; // Destruye el nodo huerfano original liberando su espacio de memoria
        return true; // Confirma la ejecucion exitosa de la eliminacion
    }
    // ---- CASO GENERAL: El elemento se encuentra en una posicion intermedia o al final ----
    NodoCliente* actual = cabeza; // Puntero auxiliar para analizar de forma adelantada la secuencia
    while (actual->siguiente != nullptr) // Recorre la lista evaluando siempre el nodo que le sigue al actual
    {
        if (actual->siguiente->dato.getId() == id) // Si el siguiente nodo contiene el ID que se desea borrar
        {
            NodoCliente* borrar = actual->siguiente; // Guarda el puntero del nodo objetivo que sera eliminado
            actual->siguiente = actual->siguiente->siguiente; // Salta el nodo a borrar reconectando la secuencia con el posterior
            delete borrar; // Libera la memoria dinamica de la estructura eliminada del flujo
            return true; // Notifica la correcta remocion del nodo
        }
        actual = actual->siguiente; // Avanza el puntero de control al nodo consecutivo
    }
    return false; // Retorna falso si concluyo el escaneo lineal completo y no se hallo el ID solicitado
}
// Imprime por consola de comandos un volcado basico de identificadores y nombres de pila de la lista
void ListaClientes::mostrarTodos() {
    NodoCliente* actual = cabeza; // Inicia el recorrido estructural desde el origen
    while (actual != nullptr) // Ciclo de impresion secuencial
    {
        cout
            << actual->dato.getId()
            << " "
            << actual->dato.getNombre()
            << endl; // Despliega los atributos basicos del socio actual en una linea
        actual = actual->siguiente; // Avanza el puntero al nodo subsecuente de la coleccion
    }
}
// Cuenta de manera iterativa el volumen total de nodos enlazados dentro de la estructura
int ListaClientes::cantidad() {
    int c = 0; // Inicializa un acumulador numerico local
    NodoCliente* actual = cabeza; // Configura el puntero de escaneo en la cabeza de la lista
    while (actual != nullptr) // Bucle de conteo que avanza de nodo en nodo
    {
        c++; // Incrementa el acumulador por cada elemento util detectado
        actual = actual->siguiente; // Mueve la posicion del puntero al nodo de adelante
    }
    return c; // Retorna el entero que representa la cardinalidad exacta de la lista
}
// Metodo de acceso: Devuelve el puntero al nodo raiz o cabeza de la lista enlazada
NodoCliente* ListaClientes::getCabeza() {
    return cabeza; // Retorna la referencia directa al punto de entrada estructural
}