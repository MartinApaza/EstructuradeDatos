#pragma once
#include <string> // Incluye la biblioteca estandar para el manejo de cadenas de texto (string)
using namespace std;
// Clase que define la entidad Dieta para la planificacion y asignacion nutricional de los socios
class Dieta {
private: // Atributos privados encargados de encapsular la informacion del plan alimenticio
    int id;           // Identificador unico numerico de la dieta en el sistema
    string objetivo;  // Meta deportiva o fisica vinculada al plan (ej. "Definicion", "Volumen", "Mantenimiento")
    int calorias;     // Cantidad total de energia o presupuesto calorico diario (medido en kcal)
public: // Metodos publicos que definen la interfaz de interaccion con la clase
    // Constructor por defecto: Inicializa una instancia base o vacia de la dieta
    Dieta();
    // Constructor parametrizado: Crea e inicializa un plan nutricional con todos sus datos obligatorios
    Dieta(
        int id,
        string objetivo,
        int calorias
    );
    // Metodos de Acceso (Getters) para recuperar las propiedades encapsuladas
    string getObjetivo(); // Devuelve la descripcion textual de la meta u objetivo del plan
    int getCalorias();    // Devuelve el valor entero correspondiente a las kilocalorias diarias
};