#include "Dieta.h"
// Constructor por defecto: Inicializa una instancia vacía del plan alimenticio
Dieta::Dieta() {}
// Constructor parametrizado: Inicializa las propiedades de la dieta con los valores recibidos
Dieta::Dieta(int id, string objetivo, int calorias) {
    this->id = id; // Almacena el identificador único numérico de la dieta
    this->objetivo = objetivo; // Almacena la meta física del plan (ej. "Volumen", "Definición")
    this->calorias = calorias; // Almacena el tope o presupuesto calórico diario asignado (int)
}
// Método Getter: Retorna la cadena de texto con el objetivo nutricional del plan
string Dieta::getObjetivo() {
    return objetivo;
}
// Método Getter: Retorna la cantidad total de calorías diarias configuradas en la dieta
int Dieta::getCalorias() {
    return calorias;
}