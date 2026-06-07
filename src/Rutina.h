#pragma once

#include <string>
#include <vector>

using namespace std;

class Rutina
{
private:

    int id;

    string nombre;

    string objetivo;

    vector<string> ejercicios;

public:

    Rutina();

    Rutina(
        int id,
        string nombre,
        string objetivo
    );

    void agregarEjercicio(
        string ejercicio
    );

    int getId();

    string getNombre();

    string getObjetivo();

    vector<string> getEjercicios();
};