#include "ListaProgreso.h"
#include <iostream>
using namespace std;
// Constructor por defecto: Inicializa el punto de acceso (cabeza) de la lista enlazada como nulo
ListaProgreso::ListaProgreso() {
    cabeza = nullptr; // Define que el historial de progreso arranca completamente vacio
}
// Agrega un nuevo registro de avance fisico optimizadamente al inicio de la estructura (coste O(1))
void ListaProgreso::insertar(ProgresoFisico dato) {
    NodoProgreso* nuevo = new NodoProgreso(dato); // Reserva memoria en el Heap e instancia el nuevo nodo con su dato

    nuevo->siguiente = cabeza; // El nuevo nodo apunta a lo que antes era el primer elemento (antigua cabeza)

    cabeza = nuevo; // La cabeza de la lista se actualiza para que ahora apunte al nuevo nodo insertado
}
// Recorre secuencialmente la lista para volcar en la consola estandar las fechas y pesos registrados
void ListaProgreso::mostrar() {
    NodoProgreso* aux = cabeza; // Puntero auxiliar calibrado en el inicio de la secuencia para el recorrido

    while (aux) // Ciclo iterativo que se ejecuta mientras el puntero auxiliar no sea nulo ( nullptr )
    {
        cout
            << aux->dato.getFecha()
            << " Peso: "
            << aux->dato.getPeso()
            << endl; // Imprime los atributos de la metrica fisica del nodo actual

        aux = aux->siguiente; // Avanza el puntero auxiliar al nodo eslabon subsecuente de la lista
    }
}
// Cuenta de manera iterativa el volumen total de registros de progreso almacenados en la secuencia
int ListaProgreso::cantidad() {
    int c = 0; // Inicializa un acumulador numerico local en cero

    NodoProgreso* aux = cabeza; // Configura el puntero auxiliar en la cabeza de la lista para iniciar el escaneo

    while (aux) // Bucle de conteo que recorre elemento por elemento la estructura
    {
        c++; // Incrementa el acumulador por cada nodo util de progreso detectado

        aux = aux->siguiente; // Mueve la posicion del puntero auxiliar hacia el nodo de adelante
    }

    return c; // Retorna el entero que representa la cardinalidad exacta del historial de progreso
}