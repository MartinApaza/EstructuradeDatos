#include "QueueDin.h"

// Constructor 
QueueDin::QueueDin() {
    cola = nullptr;
    cabeza = nullptr;
    ITEMS = 0;
    ITEMSIZE = sizeof(DATA_TYPE);
}

// Destructor 
QueueDin::~QueueDin() {
    while (!empty()) {
        get();
    }
}

// Agregar elemento (Final de la cola)
DATA_TYPE QueueDin::put(DATA_TYPE valor) {
    // Si en tu .h es 'Nodo', aquí DEBE ser 'Nodo'
    Nodo* temp = new Nodo;
    if (temp == nullptr) return (DATA_TYPE)-1;

    temp->data = valor;
    temp->next = nullptr;
    ITEMS++;

    if (cabeza == nullptr) {
        cabeza = temp;
        cola = temp;
    }
    else {
        cola->next = temp;
        cola = temp;
    }
    return valor;
}

// Retirar elemento (Frente de la cola)
DATA_TYPE QueueDin::get() {
    if (empty()) return (DATA_TYPE)-1;

    Nodo* temp = cabeza;
    DATA_TYPE d = cabeza->data;

    cabeza = cabeza->next;
    delete temp;
    ITEMS--;

    // Si la cola quedó vacía, el puntero cola no debe apuntar a memoria borrada
    if (cabeza == nullptr) cola = nullptr;

    return d;
}

// Verificar si está vacía
int QueueDin::empty() {
    return ITEMS == 0;
}