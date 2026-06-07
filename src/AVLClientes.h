#pragma once
#include "NodoAVL.h" // Incluye la definicion de la estructura de los nodos que componen el arbol
// Clase que gestiona la estructura de un Arbol Binario de Busqueda Auto-Balanceado (AVL) para clientes
class AVLClientes {
private:
    NodoAVL* raiz; // Puntero al nodo principal o base del arbol (punto de entrada a toda la estructura)
    // Calcula y devuelve la altura de un nodo para determinar si existe desequilibrio
    int altura(NodoAVL* nodo);
    // Calcula el factor de equilibrio (altura izquierda - altura derecha) para saber si requiere rotacion
    int balance(NodoAVL* nodo);
    // Realiza una rotacion simple hacia la derecha sobre un nodo para corregir un desbalance izquierdo
    NodoAVL* rotarDerecha(NodoAVL* y);
    // Realiza una rotacion simple hacia la izquierda sobre un nodo para corregir un desbalance derecho
    NodoAVL* rotarIzquierda(NodoAVL* x);
    // Metodo recursivo privado que busca la posicion correcta e inserta un nuevo cliente manteniendo el balance AVL
    NodoAVL* insertar(NodoAVL* nodo, const Cliente& cliente);
    // Metodo recursivo privado que recorre los nodos comparando IDs para localizar un cliente especifico
    NodoAVL* buscar(NodoAVL* nodo, int id);
public:
    // Constructor de la clase: se encarga de inicializar el arbol asignando la raiz como vacia (nullptr)
    AVLClientes();
    // Metodo publico para agregar un cliente; recibe el objeto y arranca la insercion recursiva desde la raiz
    void insertar(const Cliente& cliente);
    // Metodo publico de busqueda; recibe un ID y devuelve un puntero directo a los datos del cliente si existe
    Cliente* buscar(int id);
};