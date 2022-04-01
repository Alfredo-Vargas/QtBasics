#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sa = new SliderArray();

    // How to implement the custom widget?
    // ui->sliderArray->addWidget(sa);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// QUESTIONS:
// 1. How to avoid the red lines in the Init GroupBox  (for label and spinbox)?
// 2. It is better to specify qint32 or just use int ?
// 3. How to add my custom widget to the MainWindow?
//    ui->sliderArray->addWdget(sa);  // does not work
//    ui->centralWidget->addWidget(?);  // but I cannot specify the position in this way
