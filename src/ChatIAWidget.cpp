#include "ChatIAWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollBar>
#include <QInputDialog>
#include <QTimer>
#include <QByteArray>
#include <cstdlib>
// Constructor: Inicializa la interfaz grafica del chat y configura los motores de IA
ChatIAWidget::ChatIAWidget(SistemaGym* sistema, QWidget* parent)
    : QWidget(parent)
    , sistema(sistema)
    , botLocal(nullptr)
    , ia(nullptr)
    , areaScroll(nullptr)
    , contenedorBurbujas(nullptr)
    , layoutBurbujas(nullptr)
    , comboModo(nullptr)
    , spinIdContexto(nullptr)
    , editEntrada(nullptr)
    , btnEnviar(nullptr)
    , barraCarga(nullptr) {
    // Instancia el motor de logica local pasando el sistema del gimnasio como origen de datos
    botLocal = new ChatBotIA(sistema); // Se gestiona manualmente su memoria en el destructor
    // Instancia el servicio remoto de OpenAI asignando 'this' para que Qt maneje su destruccion automatica
    ia = new OpenAIService(this);
    // Intenta recuperar la API Key guardada en las variables de entorno del sistema operativo
    const char* envKey = std::getenv("OPENAI_API_KEY");
    if (envKey && envKey[0] != '\0') // Si la variable existe y no esta vacia
        ia->setApiKey(QString::fromUtf8(envKey)); // Configura la API Key por defecto en el servicio de OpenAI
    // Creacion del Layout vertical principal que contendra todos los elementos de la ventana
    QVBoxLayout* raiz = new QVBoxLayout(this);
    raiz->setContentsMargins(34, 30, 34, 24); // Define los margenes externos (izq, sup, der, inf)
    raiz->setSpacing(16); // Espaciado en pixeles entre los bloques de elementos verticales
    // Crea la etiqueta de texto que actua como titulo principal de la interfaz
    QLabel* titulo = new QLabel("Nutricion IA", this);
    titulo->setObjectName("h1"); // Asigna un identificador para aplicar estilos mediante hojas de estilo (QSS)
    raiz->addWidget(titulo); // Agrega el titulo al layout superior
    // Crea la etiqueta de texto para la descripcion secundaria de funciones del asistente
    QLabel* subtitulo = new QLabel("Asistente de entrenamiento y nutricion. Pregunta por IMC, dietas o tu membresia.", this);
    subtitulo->setObjectName("subtitle");
    raiz->addWidget(subtitulo); // Agrega el subtitulo abajo del titulo principal
    // Creacion de un diseño horizontal para agrupar los controles de configuracion en una sola linea
    QHBoxLayout* config = new QHBoxLayout();
    config->setSpacing(10); // Espacio entre controles horizontales
    QLabel* lblModo = new QLabel("Motor:", this);
    lblModo->setObjectName("formLabel");
    config->addWidget(lblModo);
    // Selector desplegable para alternar entre el motor de IA local u offline y el servicio remoto
    comboModo = new QComboBox(this);
    comboModo->addItem("Local (offline)");
    comboModo->addItem("OpenAI (gpt-4o-mini)");
    config->addWidget(comboModo);
    QLabel* lblId = new QLabel("ID socio (contexto):", this);
    lblId->setObjectName("formLabel");
    config->addWidget(lblId);
    // Control numerico para ingresar el ID del cliente y proporcionar contexto personalizado a las consultas
    spinIdContexto = new QSpinBox(this);
    spinIdContexto->setRange(0, 999999); // Limita el rango numerico admitido para IDs de socio
    spinIdContexto->setValue(0); // Valor por defecto inicial
    spinIdContexto->setSpecialValueText("Sin socio"); // Texto a mostrar cuando el valor ingresado sea cero
    config->addWidget(spinIdContexto);
    config->addStretch(1); // Añade un espacio expansivo elastico para empujar los controles previos a la izquierda
    // Boton para abrir la configuracion manual de la clave secreta de la API de OpenAI
    QPushButton* btnAjustes = new QPushButton("Configurar API Key", this);
    btnAjustes->setCursor(Qt::PointingHandCursor); // Cambia el cursor a una mano interactiva al pasar por encima
    config->addWidget(btnAjustes);
    raiz->addLayout(config); // Inserta toda la linea horizontal de configuracion al diseno principal de la ventana
    // Crea la zona con barras de desplazamiento para contener la lista dinamica de mensajes de conversacion
    areaScroll = new QScrollArea(this);
    areaScroll->setWidgetResizable(true); // Hace que el widget interno se adapte automaticamente al tamano del contenedor
    areaScroll->setFrameShape(QFrame::NoFrame); // Elimina los bordes predeterminados de la caja de scroll
    // Widget contenedor que hara de lienzo fisico sobre el cual se pintaran las burbujas de texto
    contenedorBurbujas = new QWidget(areaScroll);
    layoutBurbujas = new QVBoxLayout(contenedorBurbujas); // Layout vertical interno del contenedor de burbujas
    layoutBurbujas->setContentsMargins(4, 4, 4, 4);
    layoutBurbujas->setSpacing(12); // Separacion vertical entre los mensajes de la conversacion
    layoutBurbujas->addStretch(1); // Agrega un espaciador al final que empuja todos los mensajes hacia la parte superior
    areaScroll->setWidget(contenedorBurbujas); // Asigna el contenedor interactivo al area de scroll
    raiz->addWidget(areaScroll, 1); // Añade la zona de scroll al layout principal con un factor de estiramiento 1 (prioritario)
    // Inicializa la barra de progreso que indica que se esta procesando una respuesta de la IA remota
    barraCarga = new QProgressBar(this);
    barraCarga->setRange(0, 0); // Configura el modo indeterminado o infinito (animacion continua de carga)
    barraCarga->setTextVisible(false); // Oculta el porcentaje numerico de carga
    barraCarga->hide(); // La mantiene oculta por defecto hasta que se dispare una peticion remota
    raiz->addWidget(barraCarga); // La coloca justo arriba del cuadro de entrada de texto
    // Creacion del layout horizontal para agrupar la caja de escritura del usuario y su boton de envio
    QHBoxLayout* entrada = new QHBoxLayout();
    entrada->setSpacing(10);
    // Campo de entrada de texto editable para escribir las preguntas del usuario
    editEntrada = new QLineEdit(this);
    editEntrada->setPlaceholderText("Escribe tu pregunta y pulsa Enter...");
    entrada->addWidget(editEntrada, 1); // Toma todo el espacio horizontal libre disponible en la linea
    // Boton interactivo para procesar y enviar el mensaje digitado
    btnEnviar = new QPushButton("Enviar", this);
    btnEnviar->setObjectName("primary");
    btnEnviar->setCursor(Qt::PointingHandCursor);
    entrada->addWidget(btnEnviar);
    raiz->addLayout(entrada); // Agrega la barra inferior de entrada al diseño general del widget
    // Conecta los eventos de interaccion del usuario (clicks y pulsaciones de teclas) con sus funciones de respuesta
    connect(btnEnviar, &QPushButton::clicked, this, &ChatIAWidget::enviarPregunta); // Click en el boton Enviar
    connect(editEntrada, &QLineEdit::returnPressed, this, &ChatIAWidget::enviarPregunta); // Pulsar Enter dentro del campo de texto
    connect(btnAjustes, &QPushButton::clicked, this, &ChatIAWidget::configurarApiKey); // Click en el boton de Ajustes
    // Conecta las señales de respuesta asincronas emitidas por la api de red remota con los receptores visuales del widget
    connect(ia, &OpenAIService::respuestaRecibida, this, &ChatIAWidget::mostrarRespuesta); // Evento de exito al recibir respuesta
    connect(ia, &OpenAIService::errorOcurrido, this, &ChatIAWidget::manejarError); // Evento de falla en la solicitud de red
    // Imprime el mensaje inicial de bienvenida simulando una respuesta automatica del sistema
    agregarBurbuja(
        "Hola, soy tu asistente del gimnasio. Puedo ayudarte con tu IMC, "
        "recomendaciones de dieta y datos de tu membresia. Indica tu ID de "
        "socio arriba para darte respuestas personalizadas.",
        false); // 'false' indica que procede del asistente de IA
}
// Destructor: Libera de la memoria dinamica los recursos que no se gestionan mediante el arbol de objetos de Qt
ChatIAWidget::~ChatIAWidget() {
    delete botLocal; // Libera el puntero del bot local (OpenAIService se destruye solo gracias a su parentesco)
}
// Crea, formatea e inserta un widget de burbuja dentro del historial visual del chat
void ChatIAWidget::agregarBurbuja(const QString& texto, bool esUsuario) {
    // Instancia una fila contenedora invisible para alinear el mensaje en base al remitente
    QWidget* fila = new QWidget(contenedorBurbujas);
    QHBoxLayout* layFila = new QHBoxLayout(fila);
    layFila->setContentsMargins(0, 0, 0, 0);
    layFila->setSpacing(0);
    // Instancia el cuadro o marco estetico que encerrara el texto del mensaje
    QFrame* burbuja = new QFrame(fila);
    burbuja->setObjectName(esUsuario ? "bubbleUser" : "bubbleIA"); // Aplica estilos visuales diferenciados en base al rol
    burbuja->setMaximumWidth(560); // Limita el ancho maximo de la burbuja para legibilidad en pantallas anchas
    // Diseno interno vertical para contener la etiqueta del autor y el texto del cuerpo por separado
    QVBoxLayout* layBurbuja = new QVBoxLayout(burbuja);
    layBurbuja->setContentsMargins(14, 10, 14, 10);
    layBurbuja->setSpacing(4);
    // Etiqueta superior que muestra el remitente ("TU" o "ASISTENTE")
    QLabel* autor = new QLabel(es