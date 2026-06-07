#pragma once
#include <string> // Incluye la biblioteca estandar para el manejo de cadenas de texto (string)
using namespace std;
// Clase que define la entidad Coach (Entrenador) del gimnasio con sus datos de perfil y horarios
class Coach {
private: // Atributos privados encargados de encapsular la informacion del entrenador
    int idCoach;          // Identificador unico numerico del entrenador en el sistema
    string nombre;        // Nombre completo del entrenador
    string specialty;   // Area tecnica de especializacion (ej. "Crossfit", "Nutricion", "Pesas")
    string horarioInicio; // Hora de entrada o inicio de su jornada laboral (ej. "08:00")
    string horarioFin;    // Hora de salida o terminacion de su jornada laboral (ej. "16:00")
public: // Metodos publicos que definen la interfaz de interaccion con la clase
    // Constructor por defecto: Inicializa una instancia base o vacia del entrenador
    Coach();
    // Constructor parametrizado: Crea e inicializa un entrenador con todos sus datos obligatorios
    Coach(
        int id,
        string nombre,
        string especialidad,
        string inicio,
        string fin
    );
    // Metodos de Acceso (Getters) con modificador 'const' (garantizan que no alteran el estado del objeto)
    int getId() const;               // Devuelve el identificador unico del entrenador
    string getNombre() const;         // Devuelve el nombre completo del entrenador
    string getEspecialidad() const;   // Devuelve la especialidad tecnica del entrenador
    string getHorarioInicio() const;  // Devuelve la hora de inicio de su turno laboral
    string getHorarioFin() const;     // Devuelve la hora de finalizacion de su turno laboral
};