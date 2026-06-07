#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QTimeEdit>

#include "SistemaGym.h"

// ------------------------------------------------------------------
//  TurnosWidget
//  Dos paneles lado a lado:
//    - ColaTurnos : lista FIFO + boton "ATENDER SIGUIENTE"
//    - ColaReservas : lista FIFO + alta de reservas con coach/fecha/hora
//  Cada operacion desencola/encola y persiste el estado en disco.
// ------------------------------------------------------------------
class TurnosWidget : public QWidget
{
    Q_OBJECT

public:

    explicit TurnosWidget(SistemaGym* sistema, QWidget* parent = nullptr);

    void refrescarTodo();

signals:

    void datosCambiaron();

private slots:

    void atenderSiguienteTurno();

    void encolarTurnoDesdeCombo();

    void crearReserva();

    void atenderSiguienteReserva();

private:

    void refrescarTurnos();

    void refrescarReservas();

    void recargarCombos();

    QString nombreSocio(int id) const;

    SistemaGym* sistema;

    // Panel turnos
    QLabel*       lblTituloTurnos;
    QListWidget*  listaTurnos;
    QComboBox*    comboSocioTurno;
    QLabel*       bannerAtendido;

    // Panel reservas
    QLabel*       lblTituloReservas;
    QListWidget*  listaReservas;
    QComboBox*    comboSocioReserva;
    QSpinBox*     spinCoach;
    QDateEdit*    editFecha;
    QTimeEdit*    editHora;
};
