#include "EstadisticasGym.h"
// Cuenta y devuelve la cantidad total de asistencias consolidadas en el vector recibido
int EstadisticasGym::totalAsistencias(vector<Asistencia>& lista) {
    return lista.size(); // Retorna el tamaño exacto del contenedor dinámico de registros
}
// Calcula el porcentaje de asistencia del socio aplicando una regla de tres simple
float EstadisticasGym::porcentajeAsistencia(int asistencias, int dias) {
    if (dias == 0) // Control de seguridad: Evita el desborde o caída de la aplicación por división entre cero
        return 0;  // Retorna cero por ciento si no hay días base para el cálculo
    return (asistencias * 100.0f) / dias; // Multiplica por 100.0f para forzar la precisión decimal y divide entre los días totales
}
// Algoritmo de búsqueda que localiza y devuelve el cliente con el mayor registro de asistencias
Cliente EstadisticasGym::clienteMasActivo(vector<Cliente>& clientes, vector<Asistencia>& asistencias) {
    int mejorId = 0; // Almacena temporalmente el ID del cliente con más asistencias detectado hasta el momento
    int maximo = 0;  // Registra la marca máxima o récord de asistencias encontrada
    // Bucle Maestro: Recorre secuencialmente cada uno de los clientes registrados en el sistema
    for (auto& cliente : clientes)
    {
        int contador = 0; // Inicializa un acumulador local para contar los días que ha asistido el cliente actual
        // Bucle Anidado: Escanea la bitácora histórica completa de asistencias del gimnasio
        for (auto& asistencia : asistencias)
        {
            // Evalúa si el registro de asistencia bajo análisis le pertenece al cliente del bucle principal
            if (asistencia.getIdCliente() == cliente.getId())
            {
                contador++; // Incrementa el contador de asistencias del socio en cuestión
            }
        }
        // Condicional de Optimización: Evalúa si el cliente actual superó la marca del cliente anterior más activo
        if (contador > maximo)
        {
            maximo = contador;          // Actualiza el nuevo récord de asistencias máximas
            mejorId = cliente.getId();  // Resguarda el ID del cliente que posee esta marca
        }
    }
    // Bucle de Recuperación: Busca en la colección el objeto Cliente que corresponde al ID ganador (mejorId)
    for (auto& cliente : clientes)
    {
        if (cliente.getId() == mejorId)
        {
            return cliente; // Retorna el objeto Cliente completo con todos sus datos biográficos
        }
    }
    return Cliente(); // Flujo alternativo: Si no hay asistencias o la lista está vacía, devuelve una instancia en blanco
}