#pragma once

#include <stack>
#include <string>

using namespace std;

class PilaHistorial
{
private:

    stack<string> historial;

public:

    void registrar(string accion);

    string ultimoMovimiento();

    bool vacia();
};
