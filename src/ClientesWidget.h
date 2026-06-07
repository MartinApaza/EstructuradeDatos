#pragma once
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTableWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLabel>
#include "SistemaGym.h"
#include "Cliente.h"
// ==================================================================
//  SECCION: RegistroDialog
// ==================================================================
// Clase que define la ventana emergente modal para la captura y alta de nuevos socios
class RegistroDialog : public QDialog {
    Q_OBJECT // Macro de Qt para dar soporte a señales, ranuras (slots) y al compilador MOC
public:
    // Constructor del dialogo: Configura los componentes del formulario y asocia el sistema base
    explicit RegistroDialog(SistemaGym* sistema, QWidget* parent = nullptr);
    // Metodo de acceso: Devuelve el objeto Cliente estructurado y validado tras cerrar el dialogo con exito
    Cliente clienteCapturado() const;
private slots:
    // Slot encargado de interceptar el boton guardar, validar los campos y aceptar o rechazar la transaccion
    void intentarAceptar();
private:
    SistemaGym* sistema; // Puntero al sistema central para consultas de ID consecutivo y membresias
    // Punteros a los diferentes controles de entrada de texto, numeros y seleccion del formulario
    QLineEdit* editNombre;      // Entrada para el nombre del socio
    QLineEdit* editApellido;    // Entrada para el apellido del socio
    QSpinBox* spinEdad;        // Control numerico entero para la edad
    QDoubleSpinBox* spinPeso;        // Control numerico decimal para el peso (kg)
    QDoubleSpinBox* spinAltura;      // Control numerico decimal para la estatura (m)
    QLineEdit* editTelefono;    // Entrada para el numero telefonico
    QLineEdit* editCorreo;      // Entrada para el email institucional o personal
    QComboBox* comboMembresia;  // Selector desplegable con la lista de membresias del gimnasio
    QLabel* lblError;        // Etiqueta de texto para renderizar mensajes de error en la validacion
    Cliente capturado; // Objeto temporal donde se ensamblan los datos antes de confirmar el guardado
};
// ==================================================================
//  SECCION: ClientesWidget
// ==================================================================
// Clase que define el panel principal para la administracion, visualizacion y busqueda de socios
class ClientesWidget : public QWidget {
    Q_OBJECT // Macro fundamental de Qt para habilitar el sistema de meta-objetos
public:
    // Constructor de la interfaz de socios: Diseña la tabla y los controles superiores de busqueda
    explicit ClientesWidget(SistemaGym* sistema, QWidget* parent = nullptr);
    // Vacia la tabla y la vuelve a cargar por completo llamando de forma interna a poblarTabla(nullptr)
    void refrescarTabla();
signals:
    // Señal emitida hacia otras ventanas del sistema para avisar que la lista de socios fue modificada
    void datosCambiaron();
private slots:
    // Ejecuta la logica de busqueda: AVL rapido si es ID numerico, o lineal sobre la lista si es por nombre
    void buscar();
    // Instancia y abre la subventana RegistroDialog; si se confirma, procesa e inserta el nuevo socio
    void abrirRegistro();
    // Captura la fila seleccionada de la tabla e introduce al socio en la cola FIFO de turnos del gimnasio
    void encolarSeleccionado();
private:
    // Metodo interno para insertar datos en la tabla (si recibe un puntero, dibuja solo ese; si es nulo, dibuja todos)
    void poblarTabla(Cliente* unico);
    // Metodo de soporte: Mapea el ID de membresia de un cliente y retorna su nombre en texto (ej. "VIP")
    QString nombreMembresia(int idMembresia) const;
    SistemaGym* sistema; // Puntero de interconexion con el backend y la fachada general del gimnasio
    // Punteros a los elementos de control e interfaz de este panel de administracion
    QLineEdit* editBusqueda; // Campo de texto superior donde el usuario digita el ID o nombre a filtrar
    QTableWidget* tabla;        // Rejilla o cuadricula principal donde se listan las hileras de socios
    QLabel* lblEstado;    // Etiqueta en el pie del widget que informa la cantidad de registros o resultados
};