#pragma once
#include <string>       // Incluye la biblioteca estandar de manejo de cadenas de texto
#include "SistemaGym.h"  // Incluye la definicion del sistema central del gimnasio para acceder a los datos
using namespace std;
// Clase encargada de simular un asistente virtual para responder consultas de los clientes
class ChatBotIA {
private:
    SistemaGym* sistema; // Puntero al sistema central que permite consultar las bases de datos de clientes y membresias
public:
    // Constructor de la clase: Se encarga de enlazar el asistente virtual con el sistema general del gimnasio
    ChatBotIA(
        SistemaGym* sistema
    );
    // Metodo principal que analiza el texto de la pregunta y genera una respuesta personalizada usando el ID del cliente
    string responder(
        string pregunta,
        int idCliente
    );
};