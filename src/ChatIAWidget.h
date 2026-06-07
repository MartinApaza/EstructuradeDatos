#pragma once
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QProgressBar>
#include <QPushButton>
#include "SistemaGym.h"
#include "ChatBotIA.h"
#include "OpenAIService.h"
// Clase de interfaz de usuario que implementa una ventana de Chat tipo ChatGPT con burbujas alineadas.
// Permite alternar entre un modo local instantaneo y un modo asincrono remoto mediante la API de OpenAI.
class ChatIAWidget : public QWidget {
    Q_OBJECT // Macro obligatoria de Qt que habilita el sistema de señales, ranuras (slots) y meta-objetos
public:
    // Constructor de la clase: Inicializa los componentes graficos y asocia el sistema del gimnasio
    explicit ChatIAWidget(SistemaGym* sistema, QWidget* parent = nullptr);
    // Destructor de la clase: Se encarga de liberar la memoria dinamica de los elementos que no limpia Qt automáticamente
    ~ChatIAWidget() override;
private slots: // Seccion de funciones receptoras de eventos de la interfaz (Slots)
    // Captura el texto de la entrada del usuario, limpia el campo e inicia el procesamiento de la pregunta
    void enviarPregunta();
    // Ranura que se activa cuando OpenAI responde de forma exitosa; dibuja la respuesta en el chat
    void mostrarRespuesta(const QString& texto);
    // Ranura que se dispara si ocurre un fallo de red o autenticacion con la API; muestra el error en la interfaz
    void manejarError(const QString& detalle);
    // Despliega un cuadro de dialogo para que el usuario pueda introducir o cambiar la clave de la API de OpenAI
    void configurarApiKey();
private: // Metodos y variables de soporte interno de la interfaz
    // Crea un contenedor visual para el texto (burbuja) y lo alinea a la derecha (Usuario) o izquierda (IA)
    void agregarBurbuja(const QString& texto, bool esUsuario);
    // Forzar al scrollbar vertical a desplazarse de forma automatica al punto mas bajo de la conversacion
    void desplazarAlFinal();
    // Bloquea los campos de texto/botones y muestra u oculta la barra de carga mientras se espera la respuesta remota
    void fijarOcupado(bool ocupado);
    // Punteros a los componentes de datos del negocio y motores de procesamiento inteligente
    SistemaGym* sistema;       // Enlace al motor de base de datos principal del gimnasio
    ChatBotIA* botLocal;   // Instancia del motor local offline basado en reglas basicas de C++
    OpenAIService* ia;         // Instancia del servicio de comunicacion por red con el modelo GPT de OpenAI
    // Punteros a los componentes graficos del area de visualizacion de mensajes (Chat)
    QScrollArea* areaScroll;         // Contenedor que permite el desplazamiento vertical cuando el chat crece
    QWidget* contenedorBurbujas; // Widget fisico que funciona como lienzo para clavar las burbujas de texto
    QVBoxLayout* layoutBurbujas;     // Organizador lineal vertical para apilar los mensajes en orden cronologico
    // Punteros a los controles y widgets del formulario de entrada de datos y configuracion
    QComboBox* comboModo;      // Selector desplegable para elegir el motor de procesamiento (Local vs OpenAI)
    QSpinBox* spinIdContexto; // Selector numerico para definir el ID del socio actual que consulta el chat
    QLineEdit* editEntrada;    // Caja de texto de una sola linea donde el usuario digita sus consultas
    QPushButton* btnEnviar;      // Boton que el usuario presiona para despachar e introducir su mensaje
    QProgressBar* barraCarga;     // Barra animada indeterminada que simula el estado de espera por red de la IA
};