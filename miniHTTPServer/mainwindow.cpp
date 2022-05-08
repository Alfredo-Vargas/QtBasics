#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
  connect(ui->actionSet_Directory, &QAction::triggered, this, &MainWindow::chooseRootDirectory);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::chooseRootDirectory(void) {
  QFileDialog myFD;
  myFD.setFileMode(QFileDialog::DirectoryOnly);

  m_rootDir = QFileDialog::getExistingDirectory(
      this, "/home/alfredo/projects/QtBasics/miniHTTPServer/");
  qDebug() << m_rootDir;
}
