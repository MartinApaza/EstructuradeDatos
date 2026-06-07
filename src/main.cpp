#include <QApplication>
#include <QDir>
#include <QFont>
#include "MainWindow.h"
#include "SistemaGym.h"
#include "Estilos.h"
// ------------------------------------------------------------------
//  Punto de entrada de la aplicacion GymManager Pro.
// ------------------------------------------------------------------
int main(int argc, char* argv[]) {
    // 1. Inicializa el motor grafico y el bucle de eventos principal de Qt pasando los argumentos de consola
    QApplication app(argc, argv);

    // Configura los metadatos de identidad de la aplicacion para la gestion de rutas y registros del sistema
    QApplication::setApplicationName("GymManager Pro");
    QApplication::setOrganizationName("Estructuras de Datos");

    // 2. Define y configura una tipografia estandarizada (Segoe UI, 10pt) para homogeneizar la interfaz premium
    QFont fuente("Segoe UI", 10);
    app.setFont(fuente);

    // 3. Aplica la hoja de estilos CSS (QSS) global cargando la paleta "Dark Fitness" desde la clase estatica Estilos
    app.setStyleSheet(Estilos::hojaGlobal());

    // 4. Cambia el directorio de trabajo activo a la ruta del binario para garantizar una persistencia deterministica de los .txt
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    // 5. Instancia el nucleo de logica de negocio (Backend) del gimnasio que aloja las estructuras de datos (AVL, Listas, Colas)
    SistemaGym sistema;
    // Ejecuta el parsing y la lectura inicial de los archivos de texto para rellenar las estructuras en memoria RAM
    sistema.cargarDesdeArchivos();

    // 6. Instancia la ventana principal (Frontend), inyectandole la direccion de memoria del sistema mediante un puntero
    MainWindow ventana(&sistema);
    ventana.show(); // Hace visible el contenedor e inicia la renderizacion de los componentes de la interfaz de usuario

    // 7. Arranca el bucle infinito de eventos de Qt (captura de clics, repintados, etc.) y bloquea el flujo hasta cerrar la GUI
    int codigo = app.exec();

    // 8. Flujo de apagado: Vuelca de manera obligatoria el estado de la RAM de vuelta a los archivos fisicos de texto antes de morir
    sistema.guardarTodo();

    // Retorna el codigo de salida del bucle de Qt al sistema operativo (0 si la ejecucion fue limpia y exitosa)
    return codigo;
}