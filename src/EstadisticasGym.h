#pragma once
#include <vector>     // Incluye el contenedor secuencial de la biblioteca estandar (std::vector)
#include "Asistencia.h" // Incluye la entidad Asistencia para el conteo de bitacoras historicas
#include "Cliente.h"    // Incluye la entidad Cliente para la resolucion del socio mas activo
using namespace std;
// Clase de utilidades analiticas encargada de procesar metricas y estadisticas de rendimiento del gimnasio
class EstadisticasGym {
public: // Todos los metodos se declaran 'static' para ser invocados directamente sin instanciar la clase
    // Cuenta y devuelve la cantidad total de asistencias acumuladas dentro de la bitacora en formato vector
    static int totalAsistencias(
        vector<Asistencia>& lista
    );
    // Realiza el calculo porcentual de asistencia en base a los dias totales, previniendo divisiones por cero
    static float porcentajeAsistencia(
        int asistencias,
        int dias
    );
    // Ejecuta un algoritmo de busqueda anidada inter-estructural para localizar al objeto Cliente con mas asistencias
    static Cliente clienteMasActivo(
        vector<Cliente>& clientes,
        vector<Asistencia>& asistencias
    );
};