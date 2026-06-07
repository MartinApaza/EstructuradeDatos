#pragma once

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QString>

#include "SistemaGym.h"

// ------------------------------------------------------------------
//  TarjetaKPI
//  Pequena tarjeta reutilizable: titulo + valor grande + pista.
//  El color del valor se elige con el objectName (kpiValue / Cyan / Lima).
// ------------------------------------------------------------------
class TarjetaKPI : public QFrame
{
    Q_OBJECT

public:

    TarjetaKPI(const QString& titulo,
               const QString& objNameValor,
               const QString& pista,
               QWidget* parent = nullptr);

    void setValor(const QString& valor);

private:

    QLabel* etiquetaValor;
};

// ------------------------------------------------------------------
//  GraficoBarras
//  Widget que dibuja, mediante paintEvent, un grafico de barras simple
//  (sin dependencias externas). Se usa para "Socios por membresia".
// ------------------------------------------------------------------
class GraficoBarras : public QWidget
{
    Q_OBJECT

public:

    explicit GraficoBarras(QWidget* parent = nullptr);

    void setDatos(const QVector<QPair<QString, int>>& datos);

protected:

    void paintEvent(QPaintEvent* evento) override;

private:

    QVector<QPair<QString, int>> datos;
};

// ------------------------------------------------------------------
//  DashboardWidget
//  Pagina de inicio. Lee EN TIEMPO REAL los contadores de las
//  estructuras del SistemaGym y los muestra como KPIs + grafico.
// ------------------------------------------------------------------
class DashboardWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DashboardWidget(SistemaGym* sistema, QWidget* parent = nullptr);

public slots:

    void actualizarDatos();

private:

    SistemaGym* sistema;

    TarjetaKPI* kpiSocios;
    TarjetaKPI* kpiCola;
    TarjetaKPI* kpiReservas;
    TarjetaKPI* kpiMovimiento;

    GraficoBarras* grafico;
};
