#include "DashboardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QColor>
#include <QRectF>
#include "NodoCliente.h"
// ==================================================================
//  SECCION: TarjetaKPI
// ==================================================================
// Constructor: Inicializa un contenedor visual estilizado para desplegar un indicador analitico clave
TarjetaKPI::TarjetaKPI(const QString& titulo, const QString& objNameValor, const QString& pista, QWidget* parent)
    : QFrame(parent)
    , etiquetaValor(nullptr) {
    setObjectName("card"); // Asigna un identificador de objeto global para aplicar estilos CSS (QSS) de tarjetas
    // Diseño interno vertical para acomodar la cabecera, la métrica numerica y la descripcion
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->setContentsMargins(20, 18, 20, 18); // Define los espaciados internos de la caja
    lay->setSpacing(6); // Ajusta la separacion fija entre los componentes verticales de la tarjeta
    // Etiqueta superior que muestra el titulo descriptivo del KPI en letras mayusculas
    QLabel* lblTitulo = new QLabel(titulo.toUpper(), this);
    lblTitulo->setObjectName("cardTitle");
    lay->addWidget(lblTitulo);
    // Control de texto que despliega la métrica dinamica principal de la tarjeta
    etiquetaValor = new QLabel("0", this);
    etiquetaValor->setObjectName(objNameValor); // Asigna ID de estilo para controlar el color/tamaño de la fuente
    lay->addWidget(etiquetaValor);
    // Etiqueta inferior con una breve aclaracion sobre el origen o uso de los datos mostrados
    QLabel* lblPista = new QLabel(pista, this);
    lblPista->setObjectName("kpiHint");
    lblPista->setWordWrap(true); // Permite el salto de linea automatico para evitar desbordes visuales
    lay->addWidget(lblPista);
}
// Metodo de actualizacion: Modifica el texto del indicador numerico de forma dinamica
void TarjetaKPI::setValor(const QString& valor) {
    etiquetaValor->setText(valor); // Reemplaza la cadena actual por el nuevo valor de negocio
}
// ==================================================================
//  SECCION: GraficoBarras
// ==================================================================
// Constructor: Configura los parametros base para la renderizacion manual del grafico estadistico
GraficoBarras::GraficoBarras(QWidget* parent)
    : QWidget(parent) {
    setMinimumHeight(240); // Establece una altura vertical minima restrictiva en pixeles para el lienzo
}
// Carga la estructura de datos interna y solicita el redibujado inmediato del componente grafico
void GraficoBarras::setDatos(const QVector<QPair<QString, int>>& nuevos) {
    datos = nuevos; // Copia el arreglo de pares clave-valor (Nombre de membresia, Cantidad)
    update(); // Notifica al motor de Qt que agende un evento de repintado asincrono (paintEvent)
}
// Manejador de eventos de dibujo: Renderiza de manera manual usando primitivas graficas 2D
void GraficoBarras::paintEvent(QPaintEvent* /*evento*/) {
    QPainter p(this); // Inicializa el objeto pintor asignandolo a este widget como superficie de dibujo
    p.setRenderHint(QPainter::Antialiasing, true); // Activa el suavizado de bordes para figuras geometricas y fuentes
    // Definicion de margenes fisicos de seguridad en pixeles para delimitar la zona util del lienzo
    const int margenIzq = 12;
    const int margenDer = 12;
    const int margenSup = 12;
    const int margenInf = 38; // Espacio libre inferior reservado para imprimir las etiquetas de los ejes
    // Calcula la anchura y la altura efectivas restando los margenes definidos
    const int anchoUtil = width() - margenIzq - margenDer;
    const int altoUtil = height() - margenSup - margenInf;
    // Flujo de seguridad en caso de recibir colecciones vacias o dimensiones de ventana nulas
    if (datos.isEmpty() || altoUtil <= 0 || anchoUtil <= 0)
    {
        p.setPen(QColor("#52525B")); // Define el color del pincel para el texto de advertencia
        p.drawText(rect(), Qt::AlignCenter, "Sin datos para mostrar"); // Pinta el mensaje centralizado
        return; // Aborta la ejecucion del ciclo de pintado
    }
    // Algoritmo para localizar el valor mas alto del arreglo con el fin de calibrar la escala vertical
    int maximo = 1;
    for (const auto& d : datos)
        if (d.second > maximo) maximo = d.second; // Actualiza el limite superior de referencia
    const int n = datos.size(); // Obtiene la cantidad de barras a renderizar
    const int separacion = 18; // Distancia fija en pixeles que dividira horizontalmente a las barras
    // Formula para calcular el ancho proporcional de cada barra en funcion del espacio horizontal util
    const int anchoBarra = (anchoUtil - separacion * (n - 1)) / n;
    // Paleta cromatica ciclica para las columnas del grafico (Lima, Cian, Blanco claro)
    const QColor colores[3] = {
        QColor("#A3E635"),
        QColor("#06B6D4"),
        QColor("#F4F4F5")
    };
    // Configuracion de la tipografia encargada de rotular los valores numericos superiores
    QFont fuenteVal = p.font();
    fuenteVal.setBold(true);
    fuenteVal.setPointSize(11);
    // Configuracion de la tipografia encargada de rotular las descripciones inferiores
    QFont fuenteLbl = p.font();
    fuenteLbl.setPointSize(9);
    // Bucle principal de renderizado: Calcula la geometria e imprime cada columna de datos de forma secuencial
    for (int i = 0; i < n; ++i)
    {
        const int valor = datos[i].second; // Extrae el volumen de socios de la membresia actual
        // Ecuacion de transferencia: Proyecta el valor numerico a una altura proporcional en pixeles
        const int altoBarra = static_cast<int>((static_cast<double>(valor) / maximo) * altoUtil);
        // Calcula las coordenadas fisicas de origen (X, Y) para el rectangulo de la barra actual
        const int x = margenIzq + i * (anchoBarra + separacion);
        const int y = margenSup + (altoUtil - altoBarra);
        QRectF barra(x, y, anchoBarra, altoBarra); // Define el rectangulo con precision de coma flotante
        QColor color = colores[i % 3]; // Selecciona de manera ciclica el color que corresponde a la columna
        p.setBrush(color); // Define el color de relleno para las figuras solidas del pintor
        p.setPen(Qt::NoPen); // Elimina la linea de contorno perimetral para un acabado de diseño limpio
        p.drawRoundedRect(barra, 6, 6); // Dibuja la barra con esquinas redondeadas (6px de radio de curvatura)
        // --- Renderizado del valor numerico (Encima de la columna) ---
        p.setPen(QColor("#F4F4F5")); // Establece color de texto claro
        p.setFont(fuenteVal); // Carga la fuente tipografica configurada para numeros
        p.drawText(QRectF(x, y - 22, anchoBarra, 18), Qt::AlignCenter, QString::number(valor)); // Centra el valor arriba
        // --- Renderizado de la etiqueta identificadora (Debajo de la columna) ---
        p.setPen(QColor("#A1A1AA")); // Establece un tono grisaceo discreto para las etiquetas del eje X
        p.setFont(fuenteLbl); // Carga la fuente tipografica estandar de rotulos
        p.drawText(QRectF(x, height() - margenInf + 6, anchoBarra, 28), Qt::AlignHCenter | Qt::AlignTop, datos[i].first);
    }
}
// ==================================================================
//  SECCION: DashboardWidget
// ==================================================================
// Constructor: Ensambla la distribucion visual de la ventana de control y KPIs del gimnasio
DashboardWidget::DashboardWidget(SistemaGym* sistema, QWidget* parent)
    : QWidget(parent)
    , sistema(sistema)
    , kpiSocios(nullptr)
    , kpiCola(nullptr)
    , kpiReservas(nullptr)
    , kpiMovimiento(nullptr)
    , grafico(nullptr) {
    // Inicializa el organizador vertical principal del panel administrativo
    QVBoxLayout* raiz = new QVBoxLayout(this);
    raiz->setContentsMargins(34, 30, 34, 30);
    raiz->setSpacing(22);
    // --- Cabecera del Panel ---
    QLabel* titulo = new QLabel("Dashboard", this);
    titulo->setObjectName("h1");
    raiz->addWidget(titulo);
    QLabel* subtitulo = new QLabel("Resumen operativo en tiempo real del gimnasio", this);
    subtitulo->setObjectName("subtitle");
    raiz->addWidget(subtitulo);
    // --- Matriz de Tarjetas de Indicadores (KPIs) ---
    QGridLayout* grid = new QGridLayout();
    grid->setSpacing(18); // Define una separacion uniforme entre las tarjetas de la cuadricula
    // Instancia las 4 tarjetas de control inyectando sus titulos, IDs de estilo y descripciones conceptuales
    kpiSocios = new TarjetaKPI("Socios totales", "kpiValue", "Registrados en el arbol AVL", this);
    kpiCola = new TarjetaKPI("En cola de espera", "kpiValueLima", "Turnos pendientes de atender", this);
    kpiReservas = new TarjetaKPI("Reservas activas", "kpiValueCyan", "Sesiones con coach agendadas", this);
    kpiMovimiento = new TarjetaKPI("Ultimo movimiento", "kpiValue", "Registrado en la pila de historial", this);
    // Distribuye horizontalmente las tarjetas dentro de la primera fila (0) del diseno en cuadricula
    grid->addWidget(kpiSocios, 0, 0);
    grid->addWidget(kpiCola, 0, 1);
    grid->addWidget(kpiReservas, 0, 2);
    grid->addWidget(kpiMovimiento, 0, 3);
    raiz->addLayout(grid); // Inserta la rejilla de indicadores al layout de la ventana principal
    // --- Tarjeta de Visualizacion Estadistica (Grafico) ---
    QFrame* tarjetaGrafico = new QFrame(this);
    tarjetaGrafico->setObjectName("card");
    // Diseño vertical para empaquetar el titulo interno y la zona dinamica de dibujo
    QVBoxLayout* layGrafico = new QVBoxLayout(tarjetaGrafico);
    layGrafico->setContentsMargins(22, 20, 22, 18);
    layGrafico->setSpacing(12);
    QLabel* tituloGrafico = new QLabel("AFLUENCIA - SOCIOS POR MEMBRESIA", tarjetaGrafico);
    tituloGrafico->setObjectName("cardTitle");
    layGrafico->addWidget(tituloGrafico);
    // Instancia el lienzo personalizado de dibujo 2D para graficar las barras
    grafico = new GraficoBarras(tarjetaGrafico);
    layGrafico->addWidget(grafico, 1); // Le asigna estiramiento 1 para maximizar su despliegue vertical
    raiz->addWidget(tarjetaGrafico, 1); // Acopla la tarjeta del grafico al diseno raiz
}
// Consulta las estructuras de datos del backend para refrescar los componentes visuales
void DashboardWidget::actualizarDatos() {
    if (!sistema) return; // Validacion de seguridad: Aborta si el puntero al nucleo de logica es nulo
    // --- Extraccion Directa de Metricas desde las Estructuras de Datos del Sistema ---
    kpiSocios->setValor(QString::number(sistema->totalClientes())); // Lee el conteo consolidado de clientes
    kpiCola->setValor(QString::number(sistema->turnosPendientes())); // Consulta el tamaño actual de la cola FIFO de turnos
    kpiReservas->setValor(QString::number(sistema->reservasPendientes())); // Consulta el tamano de la cola de reservas de coaches
    // Recupera la ultima transaccion registrada leyendo el tope de la Pila de Historial
    QString mov = QString::fromStdString(sistema->ultimoMovimiento());
    if (mov.isEmpty()) mov = "Sin actividad"; // Mensaje alternativo si la pila estructural se encuentra vacia
    if (mov.size() > 18) mov = mov.left(17) + "..."; // Algoritmo de truncado preventivo para salvaguardar el diseño de la UI
    kpiMovimiento->setValor(mov); // Actualiza la interfaz con la traza de actividad resultante
    // --- Procesamiento Estadistico: Recorrido Lineal del Listado de Clientes ---
    int basica = 0, premium = 0, vip = 0, otros = 0;
    NodoCliente* actual = sistema->getListaClientes().getCabeza(); // Obtiene la referencia al primer nodo de la lista
    while (actual != nullptr) // Recorre de forma secuencial toda la lista enlazada tradicional de socios
    {
        // Evalua y categoriza al cliente incrementando el acumulador respectivo en base a su ID de Membresia
        switch (actual->dato.getIdMembresia())
        {
        case 1:  ++basica;  break; // ID 1 corresponde a la suscripcion Basica
        case 2:  ++premium; break; // ID 2 corresponde a la suscripcion Premium
        case 3:  ++vip;     break; // ID 3 corresponde a la suscripcion de caracter VIP
        default: ++otros;   break; // Planes no catalogados formalmente dentro del backend de momento
        }
        actual = actual->siguiente; // Avanza el puntero de recorrido al nodo eslabon subsecuente
    }
    // Empaqueta los datos procesados e introduce los resultados estructurados dentro de un QVector
    QVector<QPair<QString, int>> datos;
    datos.append(qMakePair(QString("Basica"), basica));
    datos.append(qMakePair(QString("Premium"), premium));
    datos.append(qMakePair(QString("VIP"), vip));
    if (otros > 0) // Solo incluye la columna de remanentes si existen registros huerfanos o adicionales
        datos.append(qMakePair(QString("Otros"), otros));
    grafico->setDatos(datos); // Despacha el vector estructurado hacia el widget de dibujo para forzar su repintado
}