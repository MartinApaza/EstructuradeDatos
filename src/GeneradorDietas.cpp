#include "GeneradorDietas.h"
// Analiza el estado fisico del cliente y prescribe de manera automatica un plan nutricional adecuado
Dieta GeneradorDietas::generar(Cliente cliente)
{
    float imc = cliente.calcularIMC(); // Calcula el Indice de Masa Corporal llamando al metodo del socio

    string objetivo; // Variable temporal para almacenar la meta del plan alimenticio
    int calorias;    // Variable temporal para el presupuesto energetico diario en kilocalorias

    // ---- Algoritmo de Evaluacion Nutricional y Asignacion de Metas ----
    if (imc < 18.5f) // Umbral 1: Cliente con Bajo Peso cronico u objetivo de desarrollo
    {
        objetivo = "Aumento de masa muscular"; // Define un enfoque hipercalorico
        calorias = 2800; // Asigna un superavit calorico para estimular la sintesis muscular
    }
    else if (imc < 25.0f) // Umbral 2: Cliente dentro de los rangos de peso Saludable / Normal
    {
        objetivo = "Mantenimiento y rendimiento"; // Define un enfoque normocalorico
        calorias = 2400; // Asigna las calorias de equilibrio para sostener la actividad deportiva habitual
    }
    else if (imc < 30.0f) // Umbral 3: Cliente en rango clasificado como Sobrepeso
    {
        objetivo = "Definicion y perdida de grasa"; // Define un enfoque hipocalorico moderado
        calorias = 2000; // Restringe la ingesta energetica para propiciar la oxidacion de tejidos adiposos
    }
    else // Umbral 4: Caso por defecto, el cliente se encuentra en rango de Obesidad
    {
        objetivo = "Perdida de peso supervisada"; // Define un enfoque de restriccion calorica controlada
        calorias = 1700; // Prescribe un deficit seguro para mitigar riesgos cardiovasculares y metabolicos
    }

    // Instancia y retorna el objeto Dieta vinculando el ID del socio con el plan generado
    return Dieta(cliente.getId(), objetivo, calorias);
}