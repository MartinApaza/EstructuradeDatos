#include "Coach.h"
// Constructor por defecto: Inicializa una instancia vacia del entrenador con ID en cero
Coach::Coach() {
    idCoach = 0; // Asigna cero para denotar que no tiene un ID valido asignado de momento
}
// Constructor parametrizado: Inicializa todas las propiedades del entrenador con los valores recibidos
Coach::Coach(int id, string nombre, string especialidad, string inicio, string fin) {
    idCoach = id; // Almacena el identificador unico numerico del entrenador
    this->nombre = nombre; // Almacena el nombre completo del entrenador
    this->especialidad = especialidad; // Almacena el area tecnica de especializacion (ej. "Cardio", "Pesas")
    horarioInicio = inicio; // Almacena la hora de entrada o inicio de jornada laboral (string)
    horarioFin = fin; // Almacena la hora de salida o finalizacion de jornada laboral (string)
}
// Metodo Getter: Retorna el identificador unico del entrenador (metodo constante, no modifica el objeto)
int Coach::getId() const {
    return idCoach;
}
// Metodo Getter: Retorna la cadena de texto con el nombre del entrenador
string Coach::getNombre() const {
    return nombre;
}
// Metodo Getter: Retorna la especialidad tecnica asignada al entrenador
string Coach::getEspecialidad() const {
    return especialidad;
}
// Metodo Getter: Retorna la cadena que representa la hora de apertura de su turno
string Coach::getHorarioInicio() const {
    return horarioInicio;
}
// Metodo Getter: Retorna la cadena que representa la hora de cierre de su turno
string Coach::getHorarioFin() const {
    return horarioFin;
}