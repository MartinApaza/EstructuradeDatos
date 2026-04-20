#pragma once
#include <string>
using namespace std;

class Dato {
public:
    int ID;
    string Titulo;
    string Artista;
    string Genero;
    double Duracion;

    Dato() {
        ID = 0;
        Titulo = "Unknown";
        Artista = "Unknown";
        Genero = "Unknown";
        Duracion = 0.0;
    }
};