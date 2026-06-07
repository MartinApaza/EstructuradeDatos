#include "Asistencia.h" 

// Implementación del constructor vacío. No realiza operaciones iniciales obligatorias.
Asistencia::Asistencia()
{
}

// Implementación del constructor parametrizado. 
Asistencia::Asistencia(int idCliente, string fecha)
{
    this->idCliente = idCliente; // Guarda el valor del parámetro 'idCliente' en la variable miembro de la clase.
    this->fecha = fecha;         // Guarda el valor del parámetro 'fecha' en la variable miembro de la clase.
}

// Devuelve el ID del cliente almacenado en el objeto.
int Asistencia::getIdCliente()
{
    return idCliente;
}

// Devuelve la cadena de texto con la fecha almacenada en el objeto.
string Asistencia::getFecha()
{
    return fecha;
}