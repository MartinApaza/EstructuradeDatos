#pragma once
#include "NodoProgreso.h" // Incluye la definicion de la estructura NodoProgreso para la gestion de punteros

// Clase que implementa una Lista Enlazada Simple dedicada a almacenar las metricas evolutivas del usuario
class ListaProgreso {
private:
    NodoProgreso* cabeza; // Puntero privado al primer elemento (nodo raiz) de la serie temporal de progresos
public:
    // Constructor por defecto: Inicializa la estructura de datos estableciendo la cabeza en nulo (historial vacio)
    ListaProgreso();
    // Inserta un objeto ProgresoFisico optimizadamente al inicio de la lista (operacion con coste constante O(1))
    void insertar(
        ProgresoFisico dato
    );
    // Recorre de forma iterativa la secuencia e imprime un desglose basico de fechas y pesos en la consola estandar
    void mostrar();
    // Escanea secuencialmente la lista enlazada y devuelve el conteo total de registros historicos guardados
    int cantidad();
};
