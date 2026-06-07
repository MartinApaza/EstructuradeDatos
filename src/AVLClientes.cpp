#include "AVLClientes.h"
#include <algorithm>
using namespace std;
// Constructor de la clase: Inicializa el arbol sin elementos (vacio)
AVLClientes::AVLClientes() {
    raiz = nullptr; // Define el puntero raiz como nulo al inicio
}
// Obtiene la altura de un nodo para el calculo del factor de equilibrio
int AVLClientes::altura(NodoAVL* nodo) {
    if (nodo == nullptr) // Si el nodo no existe (es nulo)
        return 0; // Su altura es cero
    return nodo->altura; // Retorna la altura guardada en la estructura del nodo
}
// Calcula el factor de balance o equilibrio restando la altura izquierda menos la derecha
int AVLClientes::balance(NodoAVL* nodo) {
    if (nodo == nullptr) // Si el nodo es nulo
        return 0; // El balance es neutro (cero)
    return altura(nodo->izquierda) - altura(nodo->derecha); // Retorna la resta de las alturas de sus subarboles
}
// Realiza una rotacion simple a la derecha para balancear el arbol cuando se inclina a la izquierda
NodoAVL* AVLClientes::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda; // Almacena el hijo izquierdo de y en una variable temporal x
    NodoAVL* t2 = x->derecha; // Almacena el subarbol derecho de x en una variable temporal t2
    x->derecha = y; // El nodo y pasa a ser ahora el hijo derecho de x
    y->izquierda = t2; // El subarbol t2 pasa a ser el nuevo hijo izquierdo de y
    // Recalcula la altura del nodo y basandose en el maximo entre sus nuevos hijos + 1
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    // Recalcula la altura del nodo x basandose en el maximo entre sus nuevos hijos + 1
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    return x; // Retorna x, que se convierte en la nueva raiz de este subarbol rotado
}
// Realiza una rotacion simple a la izquierda para balancear el arbol cuando se inclina a la derecha
NodoAVL* AVLClientes::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha; // Almacena el hijo derecho de x en una variable temporal y
    NodoAVL* t2 = y->izquierda; // Almacena el subarbol izquierdo de y en una variable temporal t2
    y->izquierda = x; // El nodo x pasa a ser ahora el hijo izquierdo de y
    x->derecha = t2; // El subarbol t2 pasa a ser el nuevo hijo derecho de x
    // Recalcula la altura del nodo x basandose en el maximo entre sus nuevos hijos + 1
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    // Recalcula la altura del nodo y basandose en el maximo entre sus nuevos hijos + 1
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    return y; // Retorna y, que se convierte en la nueva raiz de este subarbol rotado
}
// Metodo recursivo interno para insertar un nuevo cliente en la posicion correcta del AVL
NodoAVL* AVLClientes::insertar(NodoAVL* nodo, const Cliente& cliente) {
    if (nodo == nullptr) // Caso base: Si llega a una posicion vacia, crea y retorna el nuevo nodo con el cliente
        return new NodoAVL(cliente);
    // Compara el ID del nuevo cliente con el ID del nodo actual para decidir la ruta
    if (cliente.getId() < nodo->cliente.getId()) {
        nodo->izquierda = insertar(nodo->izquierda, cliente); // Si es menor, avanza e inserta en el subarbol izquierdo
    }
    else {
        nodo->derecha = insertar(nodo->derecha, cliente); // Si es mayor o igual, avanza e inserta en el subarbol derecho
    }
    // Actualiza la altura del nodo actual en el camino de regreso de la recursion
    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
    int b = balance(nodo); // Obtiene el factor de balance actual del nodo para verificar si se desequilibro
    if (b > 1) // Si el balance es mayor a 1, significa que esta sobrecargado hacia la izquierda
        return rotarDerecha(nodo); // Corrige el desequilibrio aplicando una rotacion a la derecha
    if (b < -1) // Si el balance es menor a -1, significa que esta sobrecargado hacia la derecha
        return rotarIzquierda(nodo); // Corrige el desequilibrio aplicando una rotacion a la izquierda
    return nodo; // Retorna el puntero del nodo (sin cambios si permanecio balanceado)
}
// Metodo publico para insertar un cliente, inicia el proceso recursivo desde la raiz principal
void AVLClientes::insertar(const Cliente& cliente) {
    raiz = insertar(raiz, cliente); // Asigna a la raiz el resultado del arbol balanceado tras la insercion
}
// Metodo recursivo privado para buscar un cliente por su ID en el arbol
NodoAVL* AVLClientes::buscar(NodoAVL* nodo, int id) {
    if (nodo == nullptr) // Caso base 1: Si llega a un nodo nulo, el ID no existe en el arbol
        return nullptr;
    if (id == nodo->cliente.getId()) // Caso base 2: Si encuentra el ID, retorna el nodo actual
        return nodo;
    if (id < nodo->cliente.getId()) // Si el ID buscado es menor que el del nodo actual
        return buscar(nodo->izquierda, id); // Continua la busqueda recursiva por la rama izquierda
    return buscar(nodo->derecha, id); // Si el ID buscado es mayor, continua la busqueda por la rama derecha
}
// Metodo publico de busqueda que retorna un puntero directo al objeto Cliente si lo halla
Cliente* AVLClientes::buscar(int id) {
    NodoAVL* encontrado = buscar(raiz, id); // Llama a la funcion interna de busqueda empezando desde la raiz
    if (encontrado == nullptr) // Si la busqueda interna retorno nulo
        return nullptr; // Retorna un puntero nulo indicando que no se encontro al cliente
    return &encontrado->cliente; // Retorna la direccion de memoria de la propiedad cliente dentro del nodo hallado
}