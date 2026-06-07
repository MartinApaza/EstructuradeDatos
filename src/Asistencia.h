#pragma once 
#include <string> // Inclusión de la librería estándar de C++ para poder utilizar variables de tipo cadena de texto.

using namespace std; // Permite usar elementos de la librería estándar (como string) directamente sin escribir 'std::string'.

class Asistencia
{
private:
    // Atributos privados: Solo se pueden modificar o leer desde dentro de esta misma clase (Encapsulamiento).
    int idCliente; // Variable entera destinada a almacenar el número de identificación único del cliente.
    string fecha;  // Variable de texto destinada a guardar la fecha exacta del ingreso al gimnasio (ej. "2026-06-02").

public:
  

    // Constructor por defecto: Permite al programa reservar espacio en memoria y crear un objeto de asistencia vacío.
    Asistencia();

    // Constructor parametrizado: Permite crear el objeto y asignarle el ID del cliente y la fecha al mismo tiempo.
    Asistencia(
        int idCliente,
        string fecha
    );

    // Método Getter: Una función de solo lectura para obtener de forma segura el ID del cliente desde fuera de la clase.
    int getIdCliente();

    // Método Getter: Una función de solo lectura para obtener de forma segura la fecha registrada desde fuera de la clase.
    string getFecha();
};