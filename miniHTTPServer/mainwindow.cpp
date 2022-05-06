#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionSet_Directory, &QAction::triggered, this, &QApplication::aboutQt);
}

MainWindow::~MainWindow()
{
  delete ui;
}

