#include "TurnosWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <vector>

#include "NodoCliente.h"
#include "Reserva.h"

TurnosWidget::TurnosWidget(SistemaGym* sistema, QWidget* parent)
    : QWidget(parent)
    , sistema(sistema)
    , lblTituloTurnos(nullptr)
    , listaTurnos(nullptr)
    , comboSocioTurno(nullptr)
    , bannerAtendido(nullptr)
    , lblTituloReservas(nullptr)
    , listaReservas(nullptr)
    , comboSocioReserva(nullptr)
    , spinCoach(nullptr)
    , editFecha(nullptr)
    , editHora(nullptr)
{
    QVBoxLayout* raiz = new QVBoxLayout(this);
    raiz->setContentsMargins(34, 30, 34, 30);
    raiz->setSpacing(18);

    // --- Cabecera ---
    QLabel* titulo = new QLabel("Turnos y reservas", this);
    titulo->setObjectName("h1");
    raiz->addWidget(titulo);

    QLabel* subtitulo = new QLabel("Cola de espera (FIFO) y agenda de sesiones con coach", this);
    subtitulo->setObjectName("subtitle");
    raiz->addWidget(subtitulo);

    // --- Dos columnas ---
    QHBoxLayout* columnas = new QHBoxLayout();
    columnas->setSpacing(18);

    // ============ Panel TURNOS ============
    QFrame* cardTurnos = new QFrame(this);
    cardTurnos->setObjectName("card");
    QVBoxLayout* layT = new QVBoxLayout(cardTurnos);
    layT->setContentsMargins(22, 20, 22, 20);
    layT->setSpacing(12);

    lblTituloTurnos = new QLabel("EN ESPERA (0)", cardTurnos);
    lblTituloTurnos->setObjectName("cardTitle");
    layT->addWidget(lblTituloTurnos);

    bannerAtendido = new QLabel("", cardTurnos);
    bannerAtendido->setObjectName("kpiHint");
    bannerAtendido->setWordWrap(true);
    bannerAtendido->hide();
    layT->addWidget(bannerAtendido);

    listaTurnos = new QListWidget(cardTurnos);
    layT->addWidget(listaTurnos, 1);

    QPushButton* btnAtender = new QPushButton("ATENDER SIGUIENTE", cardTurnos);
    btnAtender->setObjectName("primary");
    btnAtender->setCursor(Qt::PointingHandCursor);
    layT->addWidget(btnAtender);

    // Fila de alta de turno
    QHBoxLayout* altaTurno = new QHBoxLayout();
    comboSocioTurno = new QComboBox(cardTurnos);
    altaTurno->addWidget(comboSocioTurno, 1);

    QPushButton* btnAgregarTurno = new QPushButton("Encolar", cardTurnos);
    btnAgregarTurno->setObjectName("cyan");
    btnAgregarTurno->setCursor(Qt::PointingHandCursor);
    altaTurno->addWidget(btnAgregarTurno);

    layT->addLayout(altaTurno);

    columnas->addWidget(cardTurnos, 1);

    // ============ Panel RESERVAS ============
    QFrame* cardReservas = new QFrame(this);
    cardReservas->setObjectName("card");
    QVBoxLayout* layR = new QVBoxLayout(cardReservas);
    layR->setContentsMargins(22, 20, 22, 20);
    layR->setSpacing(12);

    lblTituloReservas = new QLabel("RESERVAS ACTIVAS (0)", cardReservas);
    lblTituloReservas->setObjectName("cardTitle");
    layR->addWidget(lblTituloReservas);

    listaReservas = new QListWidget(cardReservas);
    layR->addWidget(listaReservas, 1);

    // Formulario de reserva
    QLabel* lblSocio = new QLabel("Socio", cardReservas);
    lblSocio->setObjectName("formLabel");
    layR->addWidget(lblSocio);
    comboSocioReserva = new QComboBox(cardReservas);
    layR->addWidget(comboSocioReserva);

    QHBoxLayout* filaCoach = new QHBoxLayout();
    QLabel* lblCoach = new QLabel("Coach #", cardReservas);
    lblCoach->setObjectName("formLabel");
    filaCoach->addWidget(lblCoach);
    spinCoach = new QSpinBox(cardReservas);
    spinCoach->setRange(1, 99);
    spinCoach->setValue(1);
    filaCoach->addWidget(spinCoach, 1);
    layR->addLayout(filaCoach);

    QHBoxLayout* filaFechaHora = new QHBoxLayout();
    editFecha = new QDateEdit(QDate::currentDate(), cardReservas);
    editFecha->setCalendarPopup(true);
    editFecha->setDisplayFormat("yyyy-MM-dd");
    filaFechaHora->addWidget(editFecha, 1);

    editHora = new QTimeEdit(QTime(8, 0), cardReservas);
    editHora->setDisplayFormat("HH:mm");
    filaFechaHora->addWidget(editHora, 1);
    layR->addLayout(filaFechaHora);

    QHBoxLayout* botonesReserva = new QHBoxLayout();
    QPushButton* btnReservar = new QPushButton("Reservar sesion", cardReservas);
    btnReservar->setObjectName("primary");
    btnReservar->setCursor(Qt::PointingHandCursor);
    botonesReserva->addWidget(btnReservar, 1);

    QPushButton* btnAtenderReserva = new QPushButton("Atender reserva", cardReservas);
    btnAtenderReserva->setObjectName("cyan");
    btnAtenderReserva->setCursor(Qt::PointingHandCursor);
    botonesReserva->addWidget(btnAtenderReserva, 1);
    layR->addLayout(botonesReserva);

    columnas->addWidget(cardReservas, 1);

    raiz->addLayout(columnas, 1);

    // --- Conexiones ---
    connect(btnAtender,        &QPushButton::clicked, this, &TurnosWidget::atenderSiguienteTurno);
    connect(btnAgregarTurno,   &QPushButton::clicked, this, &TurnosWidget::encolarTurnoDesdeCombo);
    connect(btnReservar,       &QPushButton::clicked, this, &TurnosWidget::crearReserva);
    connect(btnAtenderReserva, &QPushButton::clicked, this, &TurnosWidget::atenderSiguienteReserva);

    refrescarTodo();
}

QString TurnosWidget::nombreSocio(int id) const
{
    Cliente* c = sistema->buscarCliente(id);
    if (c)
        return QString::fromStdString(c->getNombre()) + " " +
               QString::fromStdString(c->getApellido());
    return "Socio desconocido";
}

void TurnosWidget::recargarCombos()
{
    comboSocioTurno->clear();
    comboSocioReserva->clear();

    NodoCliente* actual = sistema->getListaClientes().getCabeza();
    while (actual != nullptr)
    {
        const Cliente& c = actual->dato;
        QString etiqueta = QString("#%1 - %2 %3")
            .arg(c.getId())
            .arg(QString::fromStdString(c.getNombre()))
            .arg(QString::fromStdString(c.getApellido()));

        comboSocioTurno->addItem(etiqueta, c.getId());
        comboSocioReserva->addItem(etiqueta, c.getId());

        actual = actual->siguiente;
    }
}

void TurnosWidget::refrescarTurnos()
{
    listaTurnos->clear();

    std::vector<int> ids = sistema->getColaTurnos().listar();
    int posicion = 1;
    for (int id : ids)
    {
        QString texto = QString("%1.  #%2  -  %3")
            .arg(posicion)
            .arg(id)
            .arg(nombreSocio(id));
        listaTurnos->addItem(texto);
        ++posicion;
    }

    lblTituloTurnos->setText(QString("EN ESPERA (%1)").arg(ids.size()));
}

void TurnosWidget::refrescarReservas()
{
    listaReservas->clear();

    std::vector<Reserva> reservas = sistema->getColaReservas().listar();
    for (Reserva r : reservas)
    {
        QString texto = QString("Reserva #%1  -  Socio #%2  con Coach #%3\n%4 a las %5")
            .arg(r.getIdReserva())
            .arg(r.getIdCliente())
            .arg(r.getIdCoach())
            .arg(QString::fromStdString(r.getFecha()))
            .arg(QString::fromStdString(r.getHora()));
        listaReservas->addItem(texto);
    }

    lblTituloReservas->setText(QString("RESERVAS ACTIVAS (%1)").arg(reservas.size()));
}

void TurnosWidget::refrescarTodo()
{
    recargarCombos();
    refrescarTurnos();
    refrescarReservas();
}

void TurnosWidget::atenderSiguienteTurno()
{
    if (sistema->turnosPendientes() == 0)
    {
        QMessageBox::information(this, "Cola vacia",
            "No hay turnos pendientes por atender.");
        return;
    }

    const int idAtendido = sistema->atenderTurno();
    sistema->guardarTurnosArchivo();

    if (idAtendido >= 0)
    {
        bannerAtendido->setText(QString("Atendido: socio #%1 (%2)")
            .arg(idAtendido)
            .arg(nombreSocio(idAtendido)));
        bannerAtendido->show();
    }

    refrescarTurnos();
    emit datosCambiaron();
}

void TurnosWidget::encolarTurnoDesdeCombo()
{
    if (comboSocioTurno->count() == 0)
    {
        QMessageBox::warning(this, "Sin socios",
            "Primero registra socios en el modulo Socios.");
        return;
    }

    const int id = comboSocioTurno->currentData().toInt();

    sistema->encolarTurno(id);
    sistema->guardarTurnosArchivo();

    refrescarTurnos();
    emit datosCambiaron();
}

void TurnosWidget::crearReserva()
{
    if (comboSocioReserva->count() == 0)
    {
        QMessageBox::warning(this, "Sin socios",
            "Primero registra socios en el modulo Socios.");
        return;
    }

    const int idSocio = comboSocioReserva->currentData().toInt();
    const int idCoach = spinCoach->value();
    const int idReserva = sistema->siguienteIdReserva();

    const QString fecha = editFecha->date().toString("yyyy-MM-dd");
    const QString hora  = editHora->time().toString("HH:mm");

    Reserva reserva(idReserva, idSocio, idCoach,
                    fecha.toStdString(), hora.toStdString());

    sistema->encolarReserva(reserva);
    sistema->guardarReservasArchivo();

    refrescarReservas();
    emit datosCambiaron();

    QMessageBox::information(this, "Reserva creada",
        QString("Reserva #%1 agendada para el socio #%2 con el coach #%3.")
            .arg(idReserva).arg(idSocio).arg(idCoach));
}

void TurnosWidget::atenderSiguienteReserva()
{
    if (sistema->reservasPendientes() == 0)
    {
        QMessageBox::information(this, "Sin reservas",
            "No hay reservas pendientes por atender.");
        return;
    }

    Reserva atendida = sistema->atenderReserva();
    sistema->guardarReservasArchivo();

    refrescarReservas();
    emit datosCambiaron();

    QMessageBox::information(this, "Reserva atendida",
        QString("Reserva #%1 del socio #%2 marcada como atendida.")
            .arg(atendida.getIdReserva())
            .arg(atendida.getIdCliente()));
}
