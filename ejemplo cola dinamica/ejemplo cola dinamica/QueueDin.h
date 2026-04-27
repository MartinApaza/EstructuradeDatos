#pragma once
#include "Nodo.h"
class QueueDin {
private:
    int ITEMS, ITEMSIZE;
    Nodo* cola, * cabeza;

public:
    QueueDin();          // Constructor
    ~QueueDin();         // Destructor

    DATA_TYPE put(DATA_TYPE valor);
    DATA_TYPE get();
    int empty();
};

