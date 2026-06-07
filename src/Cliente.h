#pragma once
#include <string> // Incluye la biblioteca estandar para el manejo de cadenas de texto (string)
using namespace std;
// Clase que define la entidad Cliente (Socio) del gimnasio con sus datos personales y medicos
class Cliente {
private: // Atributos privados encargados de encapsular la informacion del cliente
    int id;               // Identificador unico numerico del socio en el sistema
    string nombre;        // Nombre de pila del cliente
    string apellido;      // Apellido del cliente
    int edad;             // Edad cronologica del socio en años enteros
    float peso;           // Peso corporal actual medido en kilogramos
    float altura;         // Estatura o altura medida en metros
    string telefono;      // Numero telefonico de contacto
    string correo;        // Direccion de correo electronico
    int idMembresia;      // Codigo identificador del plan o membresia contratada por el cliente
public: // Metodos publicos que definen la interfaz de interaccion con la clase
    // Constructor por defecto: Inicializa un cliente base o vacio en el sistema
    Cliente();
    // Constructor parametrizado: Crea e inicializa un cliente con todos sus datos obligatorios
    Cliente(
        int id,
        string nombre,
        string apellido,
        int edad,
        float peso,
        float altura,
        string telefono,
        string correo,
        int idMembresia
    );
    // Metodos de Acceso (Getters) con modificador 'const' (garantizan que no alteran el estado del objeto)
    int getId() const;             // Devuelve el identificador unico del cliente
    string getNombre() const;       // Devuelve el nombre del cliente
    string getApellido() const;     // Devuelve el apellido del cliente
    int getEdad() const;            // Devuelve la edad del cliente
    float getPeso() const;          // Devuelve el peso del cliente
    float getAltura() const;        // Devuelve la altura del cliente
    string getTelefono() const;     // Devuelve el numero telefonico de contacto
    string getCorreo() const;       // Devuelve el correo electronico registrado
    int getIdMembresia() const;     // Devuelve el identificador de la membresia activa
    // Metodos de Modificacion (Setters) para actualizar los atributos fisicos del cliente
    void setPeso(float peso);       // Modifica y actualiza el peso corporal del cliente
    void setAltura(float altura);   // Modifica y actualiza la estatura del cliente
    // Metodos de Logica de Negocio y Evaluacion Nutricional
    float calcularIMC() const;      // Ejecuta la formula matematica para calcular el Indice de Masa Corporal
    string obtenerEstadoIMC() const; // Clasifica textualmente el IMC (Bajo peso, Normal, Sobrepeso, Obesidad)
};