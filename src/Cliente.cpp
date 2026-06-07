#include "Cliente.h"
// Constructor por defecto: Inicializa una instancia vacia del cliente con ID en cero
Cliente::Cliente() {
    id = 0; // Asigna cero para denotar que no tiene un ID valido asignado aun
}
// Constructor parametrizado: Inicializa todas las propiedades del cliente con los valores recibidos
Cliente::Cliente(int id, string nombre, string apellido, int edad, float peso, float altura, string telefono, string correo, int idMembresia) {
    this->id = id; // Almacena el identificador unico numerico del cliente
    this->nombre = nombre; // Almacena el nombre de pila del cliente
    this->apellido = apellido; // Almacena el apellido paterno/materno del cliente
    this->edad = edad; // Almacena la edad cronologica en años enteros
    this->peso = peso; // Almacena el peso actual del cliente en kilogramos (float)
    this->altura = altura; // Almacena la estatura o altura del cliente en metros (float)
    this->telefono = telefono; // Almacena el numero de contacto telefonico (string)
    this->correo = correo; // Almacena la direccion de correo electronico (string)
    this->idMembresia = idMembresia; // Almacena el ID o codigo de la membresia vinculada
}
// Metodo Getter: Retorna el identificador unico del cliente (metodo constante, no modifica el objeto)
int Cliente::getId() const {
    return id;
}
// Metodo Getter: Retorna la cadena de texto con el nombre del cliente
string Cliente::getNombre() const {
    return nombre;
}
// Metodo Getter: Retorna la cadena de texto con el apellido del cliente
string Cliente::getApellido() const {
    return apellido;
}
// Metodo Getter: Retorna la edad del cliente en años enteros
int Cliente::getEdad() const {
    return edad;
}
// Metodo Getter: Retorna el valor decimal flotante correspondiente al peso
float Cliente::getPeso() const {
    return peso;
}
// Metodo Getter: Retorna el valor decimal flotante correspondiente a la altura
float Cliente::getAltura() const {
    return altura;
}
// Metodo Getter: Retorna la cadena de texto correspondiente al telefono de contacto
string Cliente::getTelefono() const {
    return telefono;
}
// Metodo Getter: Retorna la cadena de texto con el correo electronico registrado
string Cliente::getCorreo() const {
    return correo;
}
// Metodo Getter: Retorna el codigo numerico de la membresia activa del cliente
int Cliente::getIdMembresia() const {
    return idMembresia;
}
// Metodo Setter: Permite actualizar de forma externa el peso del cliente (por ejemplo, tras un pesaje)
void Cliente::setPeso(float peso) {
    this->peso = peso; // Reemplaza el peso actual con el nuevo valor recibido
}
// Metodo Setter: Permite actualizar de forma externa la estatura o altura del cliente
void Cliente::setAltura(float altura) {
    this->altura = altura; // Reemplaza la altura actual con la nueva medida recibida
}
// Realiza el calculo matematico del Indice de Masa Corporal (IMC = peso / altura al cuadrado)
float Cliente::calcularIMC() const {
    return peso / (altura * altura); // Retorna el cociente flotante resultante de la ecuacion
}
// Analiza el IMC calculado y devuelve una etiqueta textual con la clasificacion nutricional oficial
string Cliente::obtenerEstadoIMC() const {
    float imc = calcularIMC(); // Llama a la funcion interna para obtener el valor del IMC actual
    if (imc < 18.5) // Evaluacion 1: Si el valor es estrictamente inferior a 18.5
        return "Bajo peso"; // Retorna el estado correspondiente y termina el flujo
    if (imc < 25) // Evaluacion 2: Si el valor esta entre 18.5 y menos de 25
        return "Normal"; // Retorna el estado correspondiente de peso saludable
    if (imc < 30) // Evaluacion 3: Si el valor esta entre 25 y menos de 30
        return "Sobrepeso"; // Retorna el indicador de sobrepeso
    return "Obesidad"; // Caso por defecto: Si el IMC es igual o mayor a 30, clasifica como obesidad
}