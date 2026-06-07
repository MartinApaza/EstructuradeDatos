#pragma once
#include <QMainWindow>    // Clase base para construir la ventana principal con barra de menus, estado y docks
#include <QPushButton>    // Control de boton estandar utilizado para los elementos de navegacion
#include <QStackedWidget> // Contenedor de diseño apilado que aloja e intercambia las diferentes pantallas
#include <QButtonGroup>   // Contenedor logico que gestiona la exclusividad del estado de los botones (solo uno activo)
#include "SistemaGym.h"   // Fachada central del backend inyectada para el acceso inter-estructural de datos

// Declaraciones hacia adelante (Forward Declarations) para optimizar el tiempo de compilacion reduciendo dependencias circulares
class DashboardWidget;
class ClientesWidget;
class TurnosWidget;
class ChatIAWidget;

// Clase encargada de orquestar la interfaz grafica global (UI) y la navegacion por pestañas del sistema
class MainWindow : public QMainWindow {
    Q_OBJECT // Macro obligatoria de Qt para habilitar el sistema de Meta-Objetos (Señales, Ranuras y Propiedades)

public:
    // Constructor explicito: Recibe el puntero al nucleo de logica del sistema y opcionalmente el widget padre
    explicit MainWindow(SistemaGym* sistema, QWidget* parent = nullptr);

private slots: // Ranuras privadas (Slots) encargadas de responder a eventos de la interfaz o señales de submodulos
    // Permuta la vista del QStackedWidget hacia el indice especificado y dispara las rutinas de refresco
    void cambiarPagina(int indice);

    // Captura las modificaciones de datos en los subwidgets operativos para forzar la actualizacion del Dashboard
    void alCambiarDatos();

private: // Metodos y atributos internos de soporte arquitectonico de la interfaz
    // Factoria encargada de instanciar, estilizar y conectar los botones de navegacion de la barra lateral
    QPushButton* crearBotonNav(const QString& texto, int indice);

    // Configura los layouts verticales, titulos, logotipos y el grupo de botones dentro del contenedor sidebar
    void construirSidebar(QWidget* contenedor);

    // Pointers de control e infraestructura de datos de la aplicacion
    SistemaGym* sistema;       // Instancia compartida del motor de reglas de negocio y bases de datos en memoria RAM
    QStackedWidget* paginas;   // Componente de UI encargado del intercambio dinamico de pantallas en el area central
    QButtonGroup* grupoNav;    // Gestor logico de seleccion exclusiva para los botones del menu lateral

    // Punteros a los componentes especializados (vistas independientes) empotrados dentro del QStackedWidget
    DashboardWidget* dashboard; // Panel central de control, graficos de barras e indicadores KPI
    ClientesWidget* clientes;  // Modulo de altas, bajas, busquedas y visualizacion del Arbol AVL de socios
    TurnosWidget* turnos;    // Gestor operativo de la cola de atencion y asignacion automatica de entrenadores
    ChatIAWidget* chat;      // Asistente conversacional inteligente para el diseño automatizado de planes de dieta
};
