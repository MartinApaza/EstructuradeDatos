#include "MainWindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "DashboardWidget.h"
#include "ClientesWidget.h"
#include "TurnosWidget.h"
#include "ChatIAWidget.h"
// Constructor: Inicializa y acopla los componentes estructurales de la interfaz de usuario principal
MainWindow::MainWindow(SistemaGym* sistema, QWidget* parent)
    : QMainWindow(parent)
    , sistema(sistema)
    , paginas(nullptr)
    , grupoNav(nullptr)
    , dashboard(nullptr)
    , clientes(nullptr)
    , turnos(nullptr)
    , chat(nullptr) {
    setWindowTitle("GymManager Pro"); // Establece el titulo oficial en la barra de la ventana
    resize(1180, 760); // Define las dimensiones iniciales por defecto de la aplicacion en pixeles

    // --- Widget central con layout horizontal: sidebar + stack ---
    QWidget* central = new QWidget(this); // Instancia el contenedor contenedor raiz de la ventana
    QHBoxLayout* raiz = new QHBoxLayout(central); // Layout horizontal para dividir Sidebar (Izquierda) de Contenido (Derecha)
    raiz->setContentsMargins(0, 0, 0, 0); // Elimina los bordes perifericos del diseno
    raiz->setSpacing(0); // Elimina la separacion entre los bloques adyacentes

    // --- Sidebar (Barra de Navegacion Lateral) ---
    QWidget* sidebar = new QWidget(central);
    sidebar->setObjectName("sidebar"); // ID para aplicar estilos CSS (QSS) de fondo y bordes a la barra
    sidebar->setFixedWidth(230); // Fija el ancho horizontal de la barra lateral de control
    construirSidebar(sidebar); // Delega la creacion interna de logotipos y botones de la barra
    raiz->addWidget(sidebar); // Acopla el control al layout de la izquierda

    // --- Paginas (QStackedWidget - Gestor de Vistas) ---
    paginas = new QStackedWidget(central); // Instancia el contenedor de pantallas indexadas

    // Instancia los sub-widgets inyectandoles el puntero a las estructuras del backend
    dashboard = new DashboardWidget(sistema, paginas);
    clientes = new ClientesWidget(sistema, paginas);
    turnos = new TurnosWidget(sistema, paginas);
    chat = new ChatIAWidget(sistema, paginas);

    // Registra secuencialmente las pantallas dentro del apilador para asociar sus indices
    paginas->addWidget(dashboard);   // Indice logico 0
    paginas->addWidget(clientes);    // Indice logico 1
    paginas->addWidget(turnos);      // Indice logico 2
    paginas->addWidget(chat);        // Indice logico 3

    raiz->addWidget(paginas, 1); // Agrega el stack a la derecha, con factor de estiramiento 1 para maximizarlo

    setCentralWidget(central); // Registra el contenedor integrado como el widget central de la QMainWindow

    // --- Mecanismo de Comunicacion Reactiva (Signals & Slots) ---
    // Cuando los modulos operativos alteran registros en memoria, notifican a la ventana principal para recalcular los KPIs
    connect(clientes, &ClientesWidget::datosCambiaron, this, &MainWindow::alCambiarDatos);
    connect(turnos, &TurnosWidget::datosCambiaron, this, &MainWindow::alCambiarDatos);

    // Estado inicial de la aplicacion
    paginas->setCurrentIndex(0); // Posiciona al usuario visualmente sobre el Dashboard al arrancar
    dashboard->actualizarDatos(); // Fuerza al dashboard a consultar las estructuras para renderizar las graficas
}
// Ensambla los componentes visuales de la barra de control izquierda (Logos, botones, footer)
void MainWindow::construirSidebar(QWidget* contenedor) {
    QVBoxLayout* lay = new QVBoxLayout(contenedor); // Layout vertical interno para alinear los controles hacia abajo
    lay->setContentsMargins(12, 4, 12, 12); // Establece el colchon de aire o margenes internos de la barra
    lay->setSpacing(6); // Separacion fija entre cada boton de navegacion

    // --- Elementos de Identidad de Marca (Branding) ---
    QLabel* logo = new QLabel("GYM//PRO", contenedor);
    logo->setObjectName("logo"); // Aplica fuente tipografica estilizada y tamano destacado por QSS
    lay->addWidget(logo);

    QLabel* sub = new QLabel("MANAGEMENT SUITE", contenedor);
    sub->setObjectName("logoSub"); // Texto complementario secundario con menor contraste
    lay->addWidget(sub);

    // --- Grupo de Control de Botones Radiales ---
    grupoNav = new QButtonGroup(this); // Instancia el gestor de logica de exclusion
    grupoNav->setExclusive(true); // Garantiza que solo un boton de navegacion este activo a la vez

    // Instancia y configura de forma secuencial cada boton de navegacion de la suite
    QPushButton* bDash = crearBotonNav("Dashboard", 0);
    QPushButton* bSoc = crearBotonNav("Socios", 1);
    QPushButton* bTur = crearBotonNav("Turnos", 2);
    QPushButton* bChat = crearBotonNav("Nutricion IA", 3);

    // Introduce las instancias de boton al layout vertical
    lay->addWidget(bDash);
    lay->addWidget(bSoc);
    lay->addWidget(bTur);
    lay->addWidget(bChat);

    bDash->setChecked(true); // Activa visualmente el boton del Dashboard para reflejar el estado inicial

    lay->addStretch(1); // Introduce un resorte elastico mecanico que empuja los elementos superiores hacia arriba y el pie hacia abajo

    // --- Pie de Pagina de la Sidebar ---
    QLabel* footer = new QLabel("v1.0  -  Estructuras de Datos", contenedor);
    footer->setObjectName("sidebarFooter");
    footer->setWordWrap(true);
    lay->addWidget(footer);
}
// Factoria de Botones: Instancia, asocia indices de navegacion y conecta los disparadores de clics
QPushButton* MainWindow::crearBotonNav(const QString& texto, int indice) {
    QPushButton* boton = new QPushButton(texto); // Instancia el control con su rotulo descriptivo
    boton->setObjectName("navButton"); // Enlaza estilos CSS globales para botones personalizados del menu lateral
    boton->setCheckable(true); // Habilita el comportamiento conmutador (mantiene el estado presionado)
    boton->setCursor(Qt::PointingHandCursor); // Transforma el puntero del mouse en mano interactiva al sobrevolarlo

    grupoNav->addButton(boton, indice); // Incorpora el boton al grupo exclusivo asignandole un ID numerico

    // Conecta el clic del boton a una expresion lambda que invoca al metodo encargado de permutar las pantallas
    connect(boton, &QPushButton::clicked, this, [this, indice]() {
        cambiarPagina(indice); // Cambia el index del stack pasando el identificador capturado
        });

    return boton; // Retorna el boton configurado listo para ser anexado al layout de la barra
}
// Control de ruteo interno: Cambia el widget visible y dispara las rutinas de refresco correspondientes
void MainWindow::cambiarPagina(int indice) {
    paginas->setCurrentIndex(indice); // Mueve el index del QStackedWidget para desplegar la nueva pantalla

    // ---- Orquestador de Sincronizacion de datos en transicion ----
    switch (indice)
    {
    case 0: dashboard->actualizarDatos(); break; // Refresca graficas e indicadores clave de rendimiento (KPIs)
    case 1: clientes->refrescarTabla();   break; // Reconstruye las filas de la tabla leyendo el arbol AVL / Lista de socios
    case 2: turnos->refrescarTodo();      break; // Refresca las listas de colas de espera dinamicas
    default: break; // Pantallas estaticas o sin requerimientos inmediatos de recarga
    }
}
// Slot interceptor: Actua como puente de sincronizacion cuando hay cambios internos en los modulos
void MainWindow::alCambiarDatos() {
    dashboard->actualizarDatos(); // Mantiene la pantalla de control centralizada al dia ante altas, bajas o modificaciones
}