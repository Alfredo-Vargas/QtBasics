#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QString chosenFile = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "/home/pacha/projects/QtBasics/testTemplate/extra/",
      tr("Image Files (*.png *.jpg *.bmp)"));
  m_pix->load("chosenFile");
  qDebug() << "pix was loaded";
  ui->needle->setPixmap(*m_pix);
}

MainWindow::~MainWindow()
{
  delete m_pix;
  delete ui;
}

