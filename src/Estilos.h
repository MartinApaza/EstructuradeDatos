#pragma once

#include <QString>

// ------------------------------------------------------------------
//  Estilos  -  Hoja de estilos (QSS) global "Dark Fitness"
//  Paleta:
//    Fondo        #121214
//    Tarjetas     #1A1A1E
//    Bordes       #2A2A30
//    Acento lima  #A3E635  (acciones)
//    Cian         #06B6D4  (metricas)
//    Texto        #F4F4F5 / #A1A1AA / #71717A
// ------------------------------------------------------------------
namespace Estilos
{
    inline QString hojaGlobal()
    {
        return QString::fromUtf8(R"QSS(

* {
    font-family: 'Segoe UI', 'Inter', 'Roboto', sans-serif;
}

QWidget {
    background-color: #121214;
    color: #F4F4F5;
    font-size: 14px;
}

/* ---------- Sidebar ---------- */
QWidget#sidebar {
    background-color: #0E0E10;
    border-right: 1px solid #2A2A30;
}

QLabel#logo {
    color: #A3E635;
    font-size: 20px;
    font-weight: 800;
    padding: 22px 18px 8px 18px;
    letter-spacing: 1px;
}

QLabel#logoSub {
    color: #71717A;
    font-size: 11px;
    font-weight: 600;
    padding: 0px 18px 18px 18px;
    letter-spacing: 2px;
}

QPushButton#navButton {
    text-align: left;
    padding: 13px 16px;
    border: none;
    border-radius: 8px;
    color: #A1A1AA;
    font-size: 15px;
    font-weight: 600;
}
QPushButton#navButton:hover {
    background-color: #1A1A1E;
    color: #F4F4F5;
}
QPushButton#navButton:checked {
    background-color: #1A1A1E;
    color: #A3E635;
    border-left: 3px solid #A3E635;
}

QLabel#sidebarFooter {
    color: #52525B;
    font-size: 11px;
    padding: 12px 18px;
}

/* ---------- Tipografia de paginas ---------- */
QLabel#h1 {
    font-size: 26px;
    font-weight: 800;
    color: #F4F4F5;
}
QLabel#subtitle {
    color: #71717A;
    font-size: 13px;
}

/* ---------- Tarjetas ---------- */
QFrame#card {
    background-color: #1A1A1E;
    border: 1px solid #2A2A30;
    border-radius: 14px;
}
QLabel#cardTitle {
    color: #71717A;
    font-size: 12px;
    font-weight: 700;
    letter-spacing: 1px;
}
QLabel#kpiValue {
    color: #F4F4F5;
    font-size: 34px;
    font-weight: 800;
}
QLabel#kpiValueCyan {
    color: #06B6D4;
    font-size: 34px;
    font-weight: 800;
}
QLabel#kpiValueLima {
    color: #A3E635;
    font-size: 34px;
    font-weight: 800;
}
QLabel#kpiHint {
    color: #52525B;
    font-size: 12px;
}

/* ---------- Botones ---------- */
QPushButton {
    background-color: #26262C;
    color: #F4F4F5;
    border: none;
    border-radius: 8px;
    padding: 10px 16px;
    font-weight: 600;
}
QPushButton:hover  { background-color: #33333A; }
QPushButton:pressed{ background-color: #1F1F24; }
QPushButton:disabled { background-color: #1A1A1E; color: #52525B; }

QPushButton#primary {
    background-color: #A3E635;
    color: #0A0A0A;
    font-weight: 800;
}
QPushButton#primary:hover   { background-color: #B6F25A; }
QPushButton#primary:pressed { background-color: #8FCE2A; }

QPushButton#cyan {
    background-color: #06B6D4;
    color: #0A0A0A;
    font-weight: 800;
}
QPushButton#cyan:hover   { background-color: #22C9E6; }
QPushButton#cyan:pressed { background-color: #0596AE; }

/* ---------- Inputs ---------- */
QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox, QDateEdit, QTimeEdit, QPlainTextEdit {
    background-color: #121214;
    border: 1px solid #2A2A30;
    border-radius: 8px;
    padding: 9px 12px;
    color: #F4F4F5;
    selection-background-color: #A3E635;
    selection-color: #0A0A0A;
}
QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus,
QDateEdit:focus, QTimeEdit:focus {
    border: 1px solid #A3E635;
}
QComboBox::drop-down { border: none; width: 22px; }
QComboBox QAbstractItemView {
    background-color: #1A1A1E;
    border: 1px solid #2A2A30;
    selection-background-color: #A3E635;
    selection-color: #0A0A0A;
    outline: none;
}

/* ---------- Tablas ---------- */
QTableWidget {
    background-color: #1A1A1E;
    border: 1px solid #2A2A30;
    border-radius: 12px;
    gridline-color: #2A2A30;
}
QHeaderView::section {
    background-color: #0E0E10;
    color: #71717A;
    padding: 10px;
    border: none;
    border-bottom: 1px solid #2A2A30;
    font-weight: 700;
}
QTableWidget::item { padding: 6px; }
QTableWidget::item:selected { background-color: #26331A; color: #A3E635; }
QTableCornerButton::section { background-color: #0E0E10; border: none; }

/* ---------- Listas ---------- */
QListWidget {
    background-color: #121214;
    border: 1px solid #2A2A30;
    border-radius: 10px;
    padding: 6px;
}
QListWidget::item { padding: 11px; border-radius: 8px; margin-bottom: 3px; }
QListWidget::item:selected { background-color: #26331A; color: #A3E635; }

/* ---------- Scrollbars ---------- */
QScrollBar:vertical { background: transparent; width: 10px; margin: 2px; }
QScrollBar::handle:vertical { background: #33333A; border-radius: 5px; min-height: 30px; }
QScrollBar::handle:vertical:hover { background: #4A4A52; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QScrollBar:horizontal { background: transparent; height: 10px; margin: 2px; }
QScrollBar::handle:horizontal { background: #33333A; border-radius: 5px; min-width: 30px; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }

/* ---------- ProgressBar (barra de carga IA) ---------- */
QProgressBar {
    background-color: #1A1A1E;
    border: 1px solid #2A2A30;
    border-radius: 6px;
    max-height: 6px;
    text-align: center;
}
QProgressBar::chunk { background-color: #06B6D4; border-radius: 6px; }

/* ---------- Dialogos / Formularios ---------- */
QDialog { background-color: #121214; }
QLabel#formLabel { color: #A1A1AA; font-weight: 600; }
QLabel#error { color: #F87171; font-weight: 600; }

/* ---------- Burbujas de chat ---------- */
QFrame#bubbleUser {
    background-color: #26331A;
    border: 1px solid #3A4D1F;
    border-radius: 14px;
}
QFrame#bubbleIA {
    background-color: #1A1A1E;
    border: 1px solid #2A2A30;
    border-radius: 14px;
}
QLabel#bubbleText { background: transparent; border: none; color: #F4F4F5; }
QLabel#bubbleAuthor { background: transparent; border: none; color: #71717A; font-size: 11px; font-weight: 700; }

)QSS");
    }
}
