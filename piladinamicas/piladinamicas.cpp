#include <iostream>
#include "Nodo.h"
#include "Pila.h"

using namespace std;

int main() {
    Pila l;
    int opcion;

    do {
        system("cls");
        cout << "[:] Pila en lista enlazada" << endl;
        cout << "[1] Push" << endl;
        cout << "[2] Pop" << endl;
        cout << "[3] Mostrar" << endl;
        cout << "[4] Top" << endl;
        cout << "[5] Size" << endl;
        cout << "[0] Salir" << endl;
        cout << "\nIngresa tu opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            l.push();
            break;
        case 2:
            l.pop();
            break;
        case 3:
            l.show();
            break;
        case 4:
            l.top();
            break;
        case 5:
            l.size();
            break;
        case 0:
            return 0;
        default:
            cout << "Por favor ingresa una opcion correcta.\n";
            system("pause");
        }
    } while (opcion != 0);

    return 0;
}