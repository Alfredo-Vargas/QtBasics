#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *myCentral = new QWidget;

    m_layout = new QHBoxLayout(myCentral);
    m_lineEdit = new QLineEdit(myCentral);
    m_button = new QPushButton("zoek", myCentral);
    m_layout->addWidget(m_lineEdit);
    m_layout->addWidget(m_button);
    setCentralWidget(myCentral);
}

MainWindow::~MainWindow()
{
}

