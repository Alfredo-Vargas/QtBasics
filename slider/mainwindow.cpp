#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sa = new SliderArray();
    // ui->groupBoxTestArea->
    // ui->groupBoxTestArea->addWidget(sa);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// QUESTIONS:
// 1. How to avoid the red lines in the Init GroupBox ?
// 2. It is better to specify qint32 or just use int ?
// 3. How to interpret "Call to Delete Constructor"? Example (sliderarray.cpp):
    // Is foreach discouraged? why?
    // for (QSlider s : qAsConst(*m_slidersPointers)) {
    // }
    // QSlider s = m_slidersPointers->at(i);
// 4.
