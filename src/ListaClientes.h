#pragma once
#include "NodoCliente.h" // Incluye la definición de la estructura NodoCliente para manipular sus punteros

// Clase que implementa una estructura de datos de tipo Lista Enlazada Simple para la gestión de clientes
class ListaClientes {
private:
    NodoCliente* cabeza; // Puntero privado al primer elemento (nodo raíz) de la secuencia lineal
public:
    // Constructor por defecto: Inicializa la estructura de datos estableciendo la cabeza en nulo (lista vacía)
    ListaClientes();
    // Destructor: Recorre secuencialmente la lista para liberar toda la memoria dinámica de los nodos (Heap)
    ~ListaClientes();
    // Inserta un objeto Cliente al final de la lista enlazada (operación de inserción tradicional)
    void insertar(const Cliente& cliente);
    // Busca y remueve físicamente un nodo por su ID, reconectando los punteros adyacentes de forma segura
    bool eliminar(int id);
    // Ejecuta una búsqueda lineal en la lista y retorna un puntero al objeto Cliente si localiza su ID
    Cliente* buscar(int id);
    // Realiza un volcado básico de depuración en la consola estándar con los identificadores de los socios
    void mostrarTodos();
    // Recorre de forma iterativa la secuencia y devuelve el conteo total de nodos registrados
    int cantidad();
    // Método de acceso (Getter): Devuelve la referencia directa al nodo de inicio o cabeza de la lista
    NodoCliente* getCabeza();
};