#include "ChatBotIA.h"
// Constructor de la clase: Recibe y almacena un puntero al sistema central del gimnasio
ChatBotIA::ChatBotIA(SistemaGym* sistema) {
    this->sistema = sistema; // Guarda la referencia del sistema para poder acceder a los datos de los clientes y membresias
}
// Metodo principal que analiza el texto de la pregunta y genera una respuesta personalizada para el cliente
string ChatBotIA::responder(string pregunta, int idCliente) {
    // Utiliza el sistema del gimnasio para buscar al cliente en la base de datos mediante su ID
    Cliente* cliente = sistema->buscarCliente(idCliente);
    if (cliente == nullptr) // Si el puntero es nulo, significa que el cliente no esta registrado
    {
        return "Cliente no encontrado"; // Retorna un mensaje de error y finaliza la funcion
    }
    // Busca si la palabra "imc" esta contenida en cualquier parte de la cadena de texto de la pregunta
    if (pregunta.find("imc") != string::npos)
    {
        // Calcula el Indice de Masa Corporal del cliente, lo convierte a texto y lo devuelve en la respuesta
        return "Tu IMC es: " + to_string(cliente->calcularIMC());
    }
    // Busca si la palabra "peso" esta contenida dentro de la pregunta del usuario
    if (pregunta.find("peso") != string::npos)
    {
        // Obtiene el peso actual del objeto cliente, lo convierte a texto y concatena la unidad "kg"
        return "Tu peso actual es " + to_string(cliente->getPeso()) + " kg";
    }
    // Busca si la palabra "membresia" esta presente en la consulta formulada
    if (pregunta.find("membresia") != string::npos)
    {
        // Solicita al sistema el objeto Membresia utilizando el codigo o ID de membresia que tiene asociado el cliente
        Membresia* m = sistema->obtenerMembresia(cliente->getIdMembresia());
        if (m) // Si se encontro la membresia (el puntero es valido y no es nulo)
        {
            // Obtiene el nombre o tipo de la membresia (ej. "VIP", "Mensual") y construye la respuesta
            return "Tu membresia es " + m->getTipo();
        }
    }
    // Caso por defecto: Si la pregunta no coincidio con ninguna de las palabras clave anteriores
    return "No pude entender la consulta";
}