#include <iostream>
#include "Nodo.h"
using namespace std;

// PROTOTIPOS
void Encolar(Nodo*& inicio, Nodo*& fin);
void Desencolar(Nodo*& inicio, Nodo*& fin);
void Mostrar(Nodo* inicio);

int main() {
    Nodo* inicio = NULL, * fin = NULL;
    int opc;

    do {
        cout << "\n===== MENU COLA DE MUSICAS =====" << endl;
        cout << "1. Ver si la cola esta vacia" << endl;
        cout << "2. Encolar musica" << endl;
        cout << "3. Desencolar musica" << endl;
        cout << "4. Mostrar todas las musicas" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc) {
        case 1:
            if (inicio == NULL)
                cout << "La cola esta vacia" << endl;
            else
                cout << "Hay elementos en la cola" << endl;
            break;

        case 2:
            Encolar(inicio, fin);
            break;

        case 3:
            Desencolar(inicio, fin);
            break;

        case 4:
            Mostrar(inicio);
            break;

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opcion invalida" << endl;
        }

    } while (opc != 5);

    return 0;
}