// ejemplo cola dinamica.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "QueueDin.h"
#include "Nodo.h"

using namespace std;

int main()
{
    QueueDin s;
    DATA_TYPE d;

    // llenando la cola
    for (d = 'A'; d <= 'Z'; d++) {
        s.put(d);
        cout << d << " ";
    }

    cout << endl;
    // vaciando la cola
    while (!s.empty())
        cout << (DATA_TYPE)s.get() << " ";

    cout << "\nPara terminar presione <Enter>...";
    cin.get();
    return 0;
}