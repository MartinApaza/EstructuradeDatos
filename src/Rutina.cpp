#include "Rutina.h"

Rutina::Rutina()
{

}

Rutina::Rutina(
    int id,
    string nombre,
    string objetivo
)
{
    this->id = id;
    this->nombre = nombre;
    this->objetivo = objetivo;
}

void Rutina::agregarEjercicio(
    string ejercicio
)
{
    ejercicios.push_back(
        ejercicio
    );
}

int Rutina::getId()
{
    return id;
}

string Rutina::getNombre()
{
    return nombre;
}

string Rutina::getObjetivo()
{
    return objetivo;
}

vector<string> Rutina::getEjercicios()
{
    return ejercicios;
}