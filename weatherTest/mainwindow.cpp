#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionAbout_Qt, &QAction::triggered, this, &QApplication::aboutQt);
  // to save/load files
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveToFile);
  connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadFromFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile() { 

}


void MainWindow::loadFromFile() { 

}


