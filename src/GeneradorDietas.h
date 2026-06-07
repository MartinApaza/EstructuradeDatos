#pragma once
#include "Cliente.h" // Incluye la definición de la entidad Cliente para poder analizar sus parámetros físicos (IMC)
#include "Dieta.h"   // Incluye la entidad Dieta para poder instanciar y retornar el plan alimenticio generado

// Clase de servicio encargada de la generación automatizada de regímenes alimenticios adaptados
class GeneradorDietas {
public:
    // Método estático que evalúa la condición física de un socio y prescribe una dieta específica
    // Se declara 'static' para ser invocado directamente (GeneradorDietas::generar) sin necesidad de instanciar la clase
    static Dieta generar(
        Cliente cliente
    );
};