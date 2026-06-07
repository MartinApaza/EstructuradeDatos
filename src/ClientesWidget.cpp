#include "ClientesWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QString>

#include "NodoCliente.h"

// ==================================================================
//  RegistroDialog
// ==================================================================
RegistroDialog::RegistroDialog(SistemaGym* sistema, QWidget* parent)
    : QDialog(parent)
    , sistema(sistema)
    , editNombre(nullptr)
    , editApellido(nullptr)
    , spinEdad(nullptr)
    , spinPeso(nullptr)
    , spinAltura(nullptr)
    , editTelefono(nullptr)
    , editCorreo(nullptr)
    , comboMembresia(nullptr)
    , lblError(nullptr)
{
    setWindowTitle("Registrar nuevo socio");
    setModal(true);
    setMinimumWidth(440);

    QVBoxLayout* raiz = new QVBoxLayout(this);
    raiz->setContentsMargins(26, 24, 26, 24);
    raiz->setSpacing(14);

    QLabel* titulo = new QLabel("Nuevo socio", this);
    titulo->setObjectName("h1");
    raiz->addWidget(titulo);

    QGridLayout* form = new QGridLayout();
    form->setHorizontalSpacing(14);
    form->setVerticalSpacing(10);

    auto agregarFila = [&](int fila, const QString& texto, QWidget* campo) {
        QLabel* lbl = new QLabel(texto, this);
        lbl->setObjectName("formLabel");
        form->addWidget(lbl,   fila, 0);
        form->addWidget(campo, fila, 1);
    };

    editNombre   = new QLineEdit(this);
    editNombre->setPlaceholderText("Nombre");
    editApellido = new QLineEdit(this);
    editApellido->setPlaceholderText("Apellido");

    spinEdad = new QSpinBox(this);
    spinEdad->setRange(1, 120);
    spinEdad->setValue(25);

    spinPeso = new QDoubleSpinBox(this);
    spinPeso->setRange(1.0, 400.0);
    spinPeso->setDecimals(1);
    spinPeso->setSuffix(" kg");
    spinPeso->setValue(70.0);

    spinAltura = new QDoubleSpinBox(this);
    spinAltura->setRange(0.5, 2.6);
    spinAltura->setDecimals(2);
    spinAltura->setSingleStep(0.01);
    spinAltura->setSuffix(" m");
    spinAltura->setValue(1.70);

    editTelefono = new QLineEdit(this);
    editTelefono->setPlaceholderText("Telefono");
    editCorreo   = new QLineEdit(this);
    editCorreo->setPlaceholderText("correo@ejemplo.com");

    comboMembresia = new QComboBox(this);
    for (const Membresia& m : sistema->obtenerMembresias())
    {
        QString etiqueta = QString("%1  -  $%2")
            .arg(QString::fromStdString(m.getTipo()))
            .arg(m.getPrecio(), 0, 'f', 0);
        comboMembresia->addItem(etiqueta, m.getId());
    }

    agregarFila(0, "Nombre",    editNombre);
    agregarFila(1, "Apellido",  editApellido);
    agregarFila(2, "Edad",      spinEdad);
    agregarFila(3, "Peso",      spinPeso);
    agregarFila(4, "Altura",    spinAltura);
    agregarFila(5, "Telefono",  editTelefono);
    agregarFila(6, "Correo",    editCorreo);
    agregarFila(7, "Membresia", comboMembresia);

    raiz->addLayout(form);

    lblError = new QLabel("", this);
    lblError->setObjectName("error");
    lblError->setWordWrap(true);
    lblError->hide();
    raiz->addWidget(lblError);

    // --- Botonera ---
    QHBoxLayout* botones = new QHBoxLayout();
    botones->addStretch(1);

    QPushButton* btnCancelar = new QPushButton("Cancelar", this);
    QPushButton* btnGuardar  = new QPushButton("Guardar socio", this);
    btnGuardar->setObjectName("primary");
    btnGuardar->setCursor(Qt::PointingHandCursor);

    botones->addWidget(btnCancelar);
    botones->addWidget(btnGuardar);
    raiz->addLayout(botones);

    connect(btnCancelar, &QPushButton::clicked, this, &QDialog::reject);
    connect(btnGuardar,  &QPushButton::clicked, this, &RegistroDialog::intentarAceptar);
}

void RegistroDialog::intentarAceptar()
{
    const QString nombre   = editNombre->text().trimmed();
    const QString apellido = editApellido->text().trimmed();
    const QString telefono = editTelefono->text().trimmed();
    const QString correo   = editCorreo->text().trimmed();

    auto mostrarError = [&](const QString& msg) {
        lblError->setText(msg);
        lblError->show();
    };

    if (nombre.isEmpty())   { mostrarError("El nombre no puede estar vacio.");   return; }
    if (apellido.isEmpty()) { mostrarError("El apellido no puede estar vacio."); return; }
    if (spinPeso->value() <= 0.0)   { mostrarError("El peso debe ser mayor que cero.");   return; }
    if (spinAltura->value() <= 0.0) { mostrarError("La altura debe ser mayor que cero."); return; }
    if (!correo.contains('@') || !correo.contains('.'))
    {
        mostrarError("Introduce un correo valido (debe contener '@' y '.').");
        return;
    }

    const int idNuevo    = sistema->siguienteIdCliente();
    const int idMembresia = comboMembresia->currentData().toInt();

    capturado = Cliente(
        idNuevo,
        nombre.toStdString(),
        apellido.toStdString(),
        spinEdad->value(),
        static_cast<float>(spinPeso->value()),
        static_cast<float>(spinAltura->value()),
        telefono.toStdString(),
        correo.toStdString(),
        idMembresia
    );

    accept();
}

Cliente RegistroDialog::clienteCapturado() const
{
    return capturado;
}

// ==================================================================
//  ClientesWidget
// ==================================================================
ClientesWidget::ClientesWidget(SistemaGym* sistema, QWidget* parent)
    : QWidget(parent)
    , sistema(sistema)
    , editBusqueda(nullptr)
    , tabla(nullptr)
    , lblEstado(nullptr)
{
    QVBoxLayout* raiz = new QVBoxLayout(this);
    raiz->setContentsMargins(34, 30, 34, 30);
    raiz->setSpacing(18);

    // --- Cabecera ---
    QLabel* titulo = new QLabel("Socios", this);
    titulo->setObjectName("h1");
    raiz->addWidget(titulo);

    QLabel* subtitulo = new QLabel("Busqueda sobre el arbol AVL y alta de nuevos socios", this);
    subtitulo->setObjectName("subtitle");
    raiz->addWidget(subtitulo);

    // --- Barra superior: busqueda + acciones ---
    QHBoxLayout* barra = new QHBoxLayout();
    barra->setSpacing(10);

    editBusqueda = new QLineEdit(this);
    editBusqueda->setPlaceholderText("Buscar por ID (busqueda en AVL) o por nombre...");
    barra->addWidget(editBusqueda, 1);

    QPushButton* btnBuscar = new QPushButton("Buscar", this);
    btnBuscar->setObjectName("cyan");
    btnBuscar->setCursor(Qt::PointingHandCursor);
    barra->addWidget(btnBuscar);

    QPushButton* btnLimpiar = new QPushButton("Ver todos", this);
    btnLimpiar->setCursor(Qt::PointingHandCursor);
    barra->addWidget(btnLimpiar);

    QPushButton* btnRegistrar = new QPushButton("+ Registrar socio", this);
    btnRegistrar->setObjectName("primary");
    btnRegistrar->setCursor(Qt::PointingHandCursor);
    barra->addWidget(btnRegistrar);

    raiz->addLayout(barra);

    // --- Tabla ---
    tabla = new QTableWidget(this);
    tabla->setColumnCount(11);
    QStringList encabezados = {
        "ID", "Nombre", "Apellido", "Edad", "Peso", "Altura",
        "IMC", "Estado", "Membresia", "Telefono", "Correo"
    };
    tabla->setHorizontalHeaderLabels(encabezados);
    tabla->verticalHeader()->setVisible(false);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabla->setSelectionMode(QAbstractItemView::SingleSelection);
    tabla->horizontalHeader()->setStretchLastSection(true);
    tabla->setAlternatingRowColors(false);
    raiz->addWidget(tabla, 1);

    // --- Pie: estado + encolar turno ---
    QHBoxLayout* pie = new QHBoxLayout();
    lblEstado = new QLabel("", this);
    lblEstado->setObjectName("subtitle");
    pie->addWidget(lblEstado, 1);

    QPushButton* btnEncolar = new QPushButton("Encolar turno del socio seleccionado", this);
    btnEncolar->setObjectName("cyan");
    btnEncolar->setCursor(Qt::PointingHandCursor);
    pie->addWidget(btnEncolar);

    raiz->addLayout(pie);

    // --- Conexiones ---
    connect(btnBuscar,    &QPushButton::clicked, this, &ClientesWidget::buscar);
    connect(editBusqueda, &QLineEdit::returnPressed, this, &ClientesWidget::buscar);
    connect(btnLimpiar,   &QPushButton::clicked, this, [this]() {
        editBusqueda->clear();
        refrescarTabla();
    });
    connect(btnRegistrar, &QPushButton::clicked, this, &ClientesWidget::abrirRegistro);
    connect(btnEncolar,   &QPushButton::clicked, this, &ClientesWidget::encolarSeleccionado);

    refrescarTabla();
}

QString ClientesWidget::nombreMembresia(int idMembresia) const
{
    Membresia* m = sistema->obtenerMembresia(idMembresia);
    if (m) return QString::fromStdString(m->getTipo());
    return QString("#%1").arg(idMembresia);
}

void ClientesWidget::poblarTabla(Cliente* unico)
{
    tabla->setRowCount(0);

    auto agregarFila = [&](const Cliente& c) {
        const int fila = tabla->rowCount();
        tabla->insertRow(fila);

        auto celda = [&](int col, const QString& texto) {
            QTableWidgetItem* item = new QTableWidgetItem(texto);
            if (col == 3 || col == 4 || col == 5 || col == 6)
                item->setTextAlignment(Qt::AlignCenter);
            tabla->setItem(fila, col, item);
        };

        celda(0,  QString::number(c.getId()));
        celda(1,  QString::fromStdString(c.getNombre()));
        celda(2,  QString::fromStdString(c.getApellido()));
        celda(3,  QString::number(c.getEdad()));
        celda(4,  QString::number(c.getPeso(), 'f', 1));
        celda(5,  QString::number(c.getAltura(), 'f', 2));
        celda(6,  QString::number(c.calcularIMC(), 'f', 1));
        celda(7,  QString::fromStdString(c.obtenerEstadoIMC()));
        celda(8,  nombreMembresia(c.getIdMembresia()));
        celda(9,  QString::fromStdString(c.getTelefono()));
        celda(10, QString::fromStdString(c.getCorreo()));
    };

    if (unico)
    {
        agregarFila(*unico);
        lblEstado->setText("1 socio encontrado (busqueda directa en AVL).");
        return;
    }

    int total = 0;
    NodoCliente* actual = sistema->getListaClientes().getCabeza();
    while (actual != nullptr)
    {
        agregarFila(actual->dato);
        ++total;
        actual = actual->siguiente;
    }

    lblEstado->setText(QString("%1 socio(s) en el sistema.").arg(total));
}

void ClientesWidget::refrescarTabla()
{
    poblarTabla(nullptr);
}

void ClientesWidget::buscar()
{
    const QString texto = editBusqueda->text().trimmed();

    if (texto.isEmpty())
    {
        refrescarTabla();
        return;
    }

    // Si es numerico: busqueda directa en el AVL (O(log n)).
    bool esNumero = false;
    const int id = texto.toInt(&esNumero);

    if (esNumero)
    {
        Cliente* encontrado = sistema->buscarCliente(id);
        if (encontrado)
        {
            poblarTabla(encontrado);
        }
        else
        {
            tabla->setRowCount(0);
            lblEstado->setText(QString("No existe ningun socio con ID %1.").arg(id));
        }
        return;
    }

    // Si no es numerico: filtro por nombre/apellido (substring) sobre la lista.
    tabla->setRowCount(0);
    const QString patron = texto.toLower();
    int total = 0;

    NodoCliente* actual = sistema->getListaClientes().getCabeza();
    while (actual != nullptr)
    {
        const Cliente& c = actual->dato;
        QString completo = (QString::fromStdString(c.getNombre()) + " " +
                            QString::fromStdString(c.getApellido())).toLower();

        if (completo.contains(patron))
        {
            const int fila = tabla->rowCount();
            tabla->insertRow(fila);
            tabla->setItem(fila, 0,  new QTableWidgetItem(QString::number(c.getId())));
            tabla->setItem(fila, 1,  new QTableWidgetItem(QString::fromStdString(c.getNombre())));
            tabla->setItem(fila, 2,  new QTableWidgetItem(QString::fromStdString(c.getApellido())));
            tabla->setItem(fila, 3,  new QTableWidgetItem(QString::number(c.getEdad())));
            tabla->setItem(fila, 4,  new QTableWidgetItem(QString::number(c.getPeso(), 'f', 1)));
            tabla->setItem(fila, 5,  new QTableWidgetItem(QString::number(c.getAltura(), 'f', 2)));
            tabla->setItem(fila, 6,  new QTableWidgetItem(QString::number(c.calcularIMC(), 'f', 1)));
            tabla->setItem(fila, 7,  new QTableWidgetItem(QString::fromStdString(c.obtenerEstadoIMC())));
            tabla->setItem(fila, 8,  new QTableWidgetItem(nombreMembresia(c.getIdMembresia())));
            tabla->setItem(fila, 9,  new QTableWidgetItem(QString::fromStdString(c.getTelefono())));
            tabla->setItem(fila, 10, new QTableWidgetItem(QString::fromStdString(c.getCorreo())));
            ++total;
        }
        actual = actual->siguiente;
    }

    lblEstado->setText(QString("%1 coincidencia(s) para \"%2\".").arg(total).arg(texto));
}

void ClientesWidget::abrirRegistro()
{
    RegistroDialog dialogo(sistema, this);

    if (dialogo.exec() == QDialog::Accepted)
    {
        Cliente nuevo = dialogo.clienteCapturado();

        // Insercion en lista + AVL + historial (a traves de la fachada)
        sistema->agregarCliente(nuevo);

        // Persistencia inmediata en disco
        sistema->guardarClientesArchivo();

        refrescarTabla();
        emit datosCambiaron();

        QMessageBox::information(this, "Socio registrado",
            QString("Socio #%1 (%2 %3) registrado y guardado en clientes.txt.")
                .arg(nuevo.getId())
                .arg(QString::fromStdString(nuevo.getNombre()))
                .arg(QString::fromStdString(nuevo.getApellido())));
    }
}

void ClientesWidget::encolarSeleccionado()
{
    const int fila = tabla->currentRow();
    if (fila < 0)
    {
        QMessageBox::warning(this, "Sin seleccion",
            "Selecciona primero un socio de la tabla.");
        return;
    }

    const int id = tabla->item(fila, 0)->text().toInt();

    sistema->encolarTurno(id);
    sistema->guardarTurnosArchivo();

    emit datosCambiaron();

    QMessageBox::information(this, "Turno encolado",
        QString("El socio #%1 fue agregado a la cola de turnos.").arg(id));
}
